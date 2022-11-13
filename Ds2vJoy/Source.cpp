#include "stdafx.h"
#include "Source.h"

unsigned __stdcall inputloop(void* v)
{
	((Source*)v)->InputLoop();
	return 0;
}
unsigned __stdcall outputloop(void* v)
{
	((Source*)v)->OutputLoop();
	return 0;
}

//-----------------------------------------------------------------------------
// Called once for each enumerated joystick
// We construct a device interface list
//-----------------------------------------------------------------------------
BOOL CALLBACK Source::ListOfJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	Source* dlg;
	dlg = reinterpret_cast<Source*>(pContext);

	if (dlg)
	{
		WCHAR* guidString;
		if (SUCCEEDED(StringFromCLSID(pdidInstance->guidInstance, &guidString)))
		{
			tape.DevicesList.push_back({
				pdidInstance->tszProductName,
				HIWORD(pdidInstance->guidProduct.Data1),
				LOWORD(pdidInstance->guidProduct.Data1),
				guidString
			});
		}
		delete[] guidString;

		return DIENUM_CONTINUE;
	}
	else
		return FALSE;
}

//-----------------------------------------------------------------------------
// Called once for each enumerated joystick
// If we find one, create a device interface on it
//-----------------------------------------------------------------------------
BOOL CALLBACK Source::EnumJoysticksCallback1(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	Source* dlg;
	dlg = reinterpret_cast<Source*>(pContext);

	if (dlg)
		return dlg->_EnumJoysticksCallback1(pdidInstance, pContext);
	else
		return FALSE;
}

BOOL CALLBACK Source::_EnumJoysticksCallback1(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	auto pEnumContext = static_cast<DI_ENUM_CONTEXT*>(pContext);

	// Check each DirectInput device to see if it's the one selectionned in settings
	if (wcslen(tape.Device1))
	{
		WCHAR* guidString;
		if (SUCCEEDED(StringFromCLSID(pdidInstance->guidInstance, &guidString)))
		{
			if (wcscmp(guidString, tape.Device1))
				return DIENUM_CONTINUE;
		}
		else
			return DIENUM_CONTINUE;
		delete[] guidString;
	}
	else
	// Skip anything other than the perferred joystick device as defined by the control panel
	{
		if (pEnumContext->bPreferredJoyCfgValid && !IsEqualGUID(pdidInstance->guidInstance, pEnumContext->pPreferredJoyCfg->guidInstance))
			return DIENUM_CONTINUE;
	}

	// Obtain an interface to the enumerated joystick.
	HRESULT hr = m_diInterface->CreateDevice(pdidInstance->guidInstance, &m_diJoystick1, nullptr);

	// (Maybe the user unplugged it while we were in the middle of enumerating it)
	if (FAILED(hr))
		return DIENUM_CONTINUE;

	// Save product name
	swprintf_s(m_diProductName1, MAX_PATH, L"%s", pdidInstance->tszProductName);

	// Stop enumeration
	return DIENUM_STOP;
}

//-----------------------------------------------------------------------------
// Callback function for enumerating objects (axes, buttons, POVs) on a joystick
// This function enables user interface elements for objects that are found to exist,
// and scales axes min/max values
//-----------------------------------------------------------------------------
BOOL CALLBACK Source::EnumObjectsCallback1(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext)
{
	Source* dlg;
	dlg = reinterpret_cast<Source*>(pContext);

	if (dlg)
		return dlg->_EnumObjectsCallback1(pdidoi, pContext);
	else
		return FALSE;
}

BOOL CALLBACK Source::_EnumObjectsCallback1(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext)
{
	auto hDlg = static_cast<HWND>(pContext);
	auto pEnumContext = static_cast<DI_ENUM_CONTEXT*>(pContext);

	// For axes that are returned, scale min/max values
	if (pdidoi->dwType & DIDFT_AXIS || pdidoi->dwType & DIDFT_RELAXIS || pdidoi->dwType & DIDFT_ABSAXIS)
	{
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = pdidoi->dwType;
		diprg.lMin = 0;
		diprg.lMax = 65535;

		// Set the range for the axis
		if (FAILED(m_diJoystick1->SetProperty(DIPROP_RANGE, &diprg.diph)))
			return DIENUM_STOP;

		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwHow = DIPH_BYID;
		dipdw.diph.dwObj = pdidoi->dwType;
		dipdw.dwData = 0;

		// Set no dead zone
		if (FAILED(m_diJoystick1->SetProperty(DIPROP_DEADZONE, &dipdw.diph)))
			return DIENUM_STOP;
	}

	// Set the UI to reflect what objects the joystick supports
	if (pdidoi->guidType == GUID_XAxis) { m_diXAxis1 = true;	}
	else if (pdidoi->guidType == GUID_YAxis) { m_diYAxis1 = true; }
	else if (pdidoi->guidType == GUID_ZAxis) { m_diZAxis1 = true; }
	else if (pdidoi->guidType == GUID_RxAxis) { m_diRXAxis1 = true; }
	else if (pdidoi->guidType == GUID_RyAxis) { m_diRYAxis1 = true; }
	else if (pdidoi->guidType == GUID_RzAxis) { m_diRZAxis1 = true; }
	else if (pdidoi->guidType == GUID_Slider) { m_diSliderCount1++; }
	else if (pdidoi->guidType == GUID_POV) { m_diPOVCount1++; }
	else if (pdidoi->guidType == GUID_Button) { m_diButtonCount1++; }
	return DIENUM_CONTINUE;
}

//-----------------------------------------------------------------------------
// Called once for each enumerated joystick
// If we find one, create a device interface on it
//-----------------------------------------------------------------------------
BOOL CALLBACK Source::EnumJoysticksCallback2(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	Source* dlg;
	dlg = reinterpret_cast<Source*>(pContext);

	if (dlg)
		return dlg->_EnumJoysticksCallback2(pdidInstance, pContext);
	else
		return FALSE;
}

BOOL CALLBACK Source::_EnumJoysticksCallback2(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	auto pEnumContext = static_cast<DI_ENUM_CONTEXT*>(pContext);

	// Check each DirectInput device to see if it's the one selectionned in settings
	if (wcslen(tape.Device2))
	{
		WCHAR* guidString;
		if (SUCCEEDED(StringFromCLSID(pdidInstance->guidInstance, &guidString)))
		{
			if (wcscmp(guidString, tape.Device2))
				return DIENUM_CONTINUE;
		}
		else
			return DIENUM_CONTINUE;
		delete[] guidString;
	}
	else
		return DIENUM_CONTINUE;

	// Obtain an interface to the enumerated joystick.
	HRESULT hr = m_diInterface->CreateDevice(pdidInstance->guidInstance, &m_diJoystick2, nullptr);

	// (Maybe the user unplugged it while we were in the middle of enumerating it)
	if (FAILED(hr))
		return DIENUM_CONTINUE;

	// Save product name
	swprintf_s(m_diProductName2, MAX_PATH, L"%s", pdidInstance->tszProductName);

	// Stop enumeration
	return DIENUM_STOP;
}

//-----------------------------------------------------------------------------
// Callback function for enumerating objects (axes, buttons, POVs) on a joystick
// This function enables user interface elements for objects that are found to exist,
// and scales axes min/max values
//-----------------------------------------------------------------------------
BOOL CALLBACK Source::EnumObjectsCallback2(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext)
{
	Source* dlg;
	dlg = reinterpret_cast<Source*>(pContext);

	if (dlg)
		return dlg->_EnumObjectsCallback2(pdidoi, pContext);
	else
		return FALSE;
}

BOOL CALLBACK Source::_EnumObjectsCallback2(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext)
{
	auto hDlg = static_cast<HWND>(pContext);
	auto pEnumContext = static_cast<DI_ENUM_CONTEXT*>(pContext);

	// For axes that are returned, scale min/max values
	if (pdidoi->dwType & DIDFT_AXIS || pdidoi->dwType & DIDFT_RELAXIS || pdidoi->dwType & DIDFT_ABSAXIS)
	{
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = pdidoi->dwType;
		diprg.lMin = 0;
		diprg.lMax = 65535;

		// Set the range for the axis
		if (FAILED(m_diJoystick2->SetProperty(DIPROP_RANGE, &diprg.diph)))
			return DIENUM_STOP;

		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwHow = DIPH_BYID;
		dipdw.diph.dwObj = pdidoi->dwType;
		dipdw.dwData = 0;

		// Set no dead zone (program controll it)
		if (FAILED(m_diJoystick2->SetProperty(DIPROP_DEADZONE, &dipdw.diph)))
			return DIENUM_STOP;
	}

	// Set the UI to reflect what objects the joystick supports
	if (pdidoi->guidType == GUID_XAxis) { m_diXAxis2 = true; }
	else if (pdidoi->guidType == GUID_YAxis) { m_diYAxis2 = true; }
	else if (pdidoi->guidType == GUID_ZAxis) { m_diZAxis2 = true; }
	else if (pdidoi->guidType == GUID_RxAxis) { m_diRXAxis2 = true; }
	else if (pdidoi->guidType == GUID_RyAxis) { m_diRYAxis2 = true; }
	else if (pdidoi->guidType == GUID_RzAxis) { m_diRZAxis2 = true; }
	else if (pdidoi->guidType == GUID_Slider) { m_diSliderCount2++; }
	else if (pdidoi->guidType == GUID_POV) { m_diPOVCount2++; }
	else if (pdidoi->guidType == GUID_Button) { m_diButtonCount2++; }
	return DIENUM_CONTINUE;
}

Source::Source()
{
}

Source::~Source()
{
	Close(true);
	CloseHandle(m_hREvent);
	CloseHandle(m_hWEvent);
}

//Receive callback
void Source::SetCallback(SourceCallback cb, void* param)
{
	m_callback = cb;
	m_callbackdata = param;
}

void Source::Init()
{
	m_oRead.hEvent = m_hREvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_oWrite.hEvent = m_hWEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_buttons[SourceButton::Button_None].		setConstant(0);
	m_buttons[SourceButton::EMPTY].				setConstant(0);
	m_buttons[SourceButton::MIDDLE].			setConstant(32767);
	m_buttons[SourceButton::FULL].				setConstant(65535);
	m_buttons[SourceButton::QUARTER1].			setConstant(16384);
	m_buttons[SourceButton::QUARTER2].			setConstant(49151);
	m_buttons[SourceButton::THIRD1].			setConstant(21845);
	m_buttons[SourceButton::THIRD2].			setConstant(43690);
	m_buttons[SourceButton::TEN].				setConstant(6554);
	m_buttons[SourceButton::TWENTY].			setConstant(13107);
	m_buttons[SourceButton::THIRTY].			setConstant(19661);
	m_buttons[SourceButton::FORTY].				setConstant(26214);
	m_buttons[SourceButton::SIXTY].				setConstant(39321);
	m_buttons[SourceButton::SEVENTY].			setConstant(45874);
	m_buttons[SourceButton::EIGHTY].			setConstant(52428);
	m_buttons[SourceButton::NINETY].			setConstant(58981);

	m_buttons[SourceButton::LX].				setAxis(SrceOffsetsID::Offset_LX, SrceOffsetsID::Offset_LY, SrceAxisID::Axis_X);
	m_buttons[SourceButton::LX_INV].			setAxisInv(SrceOffsetsID::Offset_LX, SrceOffsetsID::Offset_LY, SrceAxisID::Axis_X);
	m_buttons[SourceButton::LX_SNIPER].			setAxisSniper(SrceOffsetsID::Offset_LX, SrceOffsetsID::Offset_LY);

	m_buttons[SourceButton::LY].				setAxis(SrceOffsetsID::Offset_LY, SrceOffsetsID::Offset_LX, SrceAxisID::Axis_Y);
	m_buttons[SourceButton::LY_INV].			setAxisInv(SrceOffsetsID::Offset_LY, SrceOffsetsID::Offset_LX, SrceAxisID::Axis_Y);
	m_buttons[SourceButton::LY_SNIPER].			setAxisSniper(SrceOffsetsID::Offset_LY, SrceOffsetsID::Offset_LX);

	m_buttons[SourceButton::AXISL_TR_LEFT].		setAxisTriggerLU(SrceOffsetsID::Offset_LX);
	m_buttons[SourceButton::AXISL_TR_UP].		setAxisTriggerLU(SrceOffsetsID::Offset_LY);
	m_buttons[SourceButton::AXISL_TR_RIGHT].	setAxisTriggerRD(SrceOffsetsID::Offset_LX);
	m_buttons[SourceButton::AXISL_TR_DOWN].		setAxisTriggerRD(SrceOffsetsID::Offset_LY);

	m_buttons[SourceButton::AXISL_LEFT].		setAxisLU(SrceOffsetsID::Offset_LX);
	m_buttons[SourceButton::AXISL_UP_LEFT].		setAxisDUL(SrceOffsetsID::Offset_LY, SrceOffsetsID::Offset_LX);
	m_buttons[SourceButton::AXISL_UP].			setAxisLU(SrceOffsetsID::Offset_LY);
	m_buttons[SourceButton::AXISL_UP_RIGHT].	setAxisDUR(SrceOffsetsID::Offset_LY, SrceOffsetsID::Offset_LX);
	m_buttons[SourceButton::AXISL_RIGHT].		setAxisRD(SrceOffsetsID::Offset_LX);
	m_buttons[SourceButton::AXISL_DOWN_RIGHT].	setAxisDDR(SrceOffsetsID::Offset_LY, SrceOffsetsID::Offset_LX);
	m_buttons[SourceButton::AXISL_DOWN].		setAxisRD(SrceOffsetsID::Offset_LY);
	m_buttons[SourceButton::AXISL_DOWN_LEFT].	setAxisDDL(SrceOffsetsID::Offset_LY, SrceOffsetsID::Offset_LX);

	m_buttons[SourceButton::RX].				setAxis(SrceOffsetsID::Offset_RX, SrceOffsetsID::Offset_RY, SrceAxisID::Axis_Z);
	m_buttons[SourceButton::RX_INV].			setAxisInv(SrceOffsetsID::Offset_RX, SrceOffsetsID::Offset_RY, SrceAxisID::Axis_Z);
	m_buttons[SourceButton::RX_SNIPER].			setAxisSniper(SrceOffsetsID::Offset_RX, SrceOffsetsID::Offset_RY);

	m_buttons[SourceButton::RY].				setAxis(SrceOffsetsID::Offset_RY, SrceOffsetsID::Offset_RX, SrceAxisID::Axis_RZ);
	m_buttons[SourceButton::RY_INV].			setAxisInv(SrceOffsetsID::Offset_RY, SrceOffsetsID::Offset_RX, SrceAxisID::Axis_RZ);
	m_buttons[SourceButton::RY_SNIPER].			setAxisSniper(SrceOffsetsID::Offset_RY, SrceOffsetsID::Offset_RX);

	m_buttons[SourceButton::AXISR_TR_LEFT].		setAxisTriggerLU(SrceOffsetsID::Offset_RX);
	m_buttons[SourceButton::AXISR_TR_UP].		setAxisTriggerLU(SrceOffsetsID::Offset_RY);
	m_buttons[SourceButton::AXISR_TR_RIGHT].	setAxisTriggerRD(SrceOffsetsID::Offset_RX);
	m_buttons[SourceButton::AXISR_TR_DOWN].		setAxisTriggerRD(SrceOffsetsID::Offset_RY);

	m_buttons[SourceButton::AXISR_LEFT].		setAxisLU(SrceOffsetsID::Offset_RX);
	m_buttons[SourceButton::AXISR_UP_LEFT].		setAxisDUL(SrceOffsetsID::Offset_RY, SrceOffsetsID::Offset_RX);
	m_buttons[SourceButton::AXISR_UP].			setAxisLU(SrceOffsetsID::Offset_RY);
	m_buttons[SourceButton::AXISR_UP_RIGHT].	setAxisDUR(SrceOffsetsID::Offset_RY, SrceOffsetsID::Offset_RX);
	m_buttons[SourceButton::AXISR_RIGHT].		setAxisRD(SrceOffsetsID::Offset_RX);
	m_buttons[SourceButton::AXISR_DOWN_RIGHT].	setAxisDDR(SrceOffsetsID::Offset_RY, SrceOffsetsID::Offset_RX);
	m_buttons[SourceButton::AXISR_DOWN].		setAxisRD(SrceOffsetsID::Offset_RY);
	m_buttons[SourceButton::AXISR_DOWN_LEFT].	setAxisDDL(SrceOffsetsID::Offset_RY, SrceOffsetsID::Offset_RX);

	m_buttons[SourceButton::L2_TRIGGER].		setTrigger(SrceOffsetsID::Offset_L2, 0);
	m_buttons[SourceButton::L2_TRIGGER_33].		setTrigger(SrceOffsetsID::Offset_L2, 12336);
	m_buttons[SourceButton::L2_TRIGGER_66].		setTrigger(SrceOffsetsID::Offset_L2, 43176);
	m_buttons[SourceButton::L2_TRIGGER_100].	setTrigger(SrceOffsetsID::Offset_L2, 65278);
	
	m_buttons[SourceButton::R2_TRIGGER].		setTrigger(SrceOffsetsID::Offset_R2, 0);
	m_buttons[SourceButton::R2_TRIGGER_33].		setTrigger(SrceOffsetsID::Offset_R2, 12336);
	m_buttons[SourceButton::R2_TRIGGER_66].		setTrigger(SrceOffsetsID::Offset_R2, 43176);
	m_buttons[SourceButton::R2_TRIGGER_100].	setTrigger(SrceOffsetsID::Offset_R2, 65278);

	m_buttons[SourceButton::SLO].				setAxis(SrceOffsetsID::Offset_SL0, SrceOffsetsID::Offset_SL1, SrceAxisID::Axis_SL0);
	m_buttons[SourceButton::SLO_INV].			setAxisInv(SrceOffsetsID::Offset_SL0, SrceOffsetsID::Offset_SL1, SrceAxisID::Axis_SL0);
	m_buttons[SourceButton::SLO_SNIPER].		setAxisSniper(SrceOffsetsID::Offset_SL0, SrceOffsetsID::Offset_SL1);

	m_buttons[SourceButton::SL1].				setAxis(SrceOffsetsID::Offset_SL1, SrceOffsetsID::Offset_SL0, SrceAxisID::Axis_SL1);
	m_buttons[SourceButton::SL1_INV].			setAxisInv(SrceOffsetsID::Offset_SL1, SrceOffsetsID::Offset_SL0, SrceAxisID::Axis_SL1);
	m_buttons[SourceButton::SL1_SNIPER].		setAxisSniper(SrceOffsetsID::Offset_SL1, SrceOffsetsID::Offset_SL0);
	
	m_buttons[SourceButton::DI_X].				setAxisSolo(SrceOffsetsID::Offset_LX, SrceAxisID::Axis_DIX);
	m_buttons[SourceButton::DI_X_INV].			setAxisInvSolo(SrceOffsetsID::Offset_LX, SrceAxisID::Axis_DIX);
	m_buttons[SourceButton::DI_X_TRIGGER].		setTrigger(SrceOffsetsID::Offset_LX, 0);
	m_buttons[SourceButton::DI_Y].				setAxisSolo(SrceOffsetsID::Offset_LY, SrceAxisID::Axis_DIY);
	m_buttons[SourceButton::DI_Y_INV].			setAxisInvSolo(SrceOffsetsID::Offset_LY, SrceAxisID::Axis_DIY);
	m_buttons[SourceButton::DI_Y_TRIGGER].		setTrigger(SrceOffsetsID::Offset_LY, 0);
	m_buttons[SourceButton::DI_Z].				setAxisSolo(SrceOffsetsID::Offset_RX, SrceAxisID::Axis_DIZ);
	m_buttons[SourceButton::DI_Z_INV].			setAxisInvSolo(SrceOffsetsID::Offset_RX, SrceAxisID::Axis_DIZ);
	m_buttons[SourceButton::DI_Z_TRIGGER].		setTrigger(SrceOffsetsID::Offset_RX, 0);
	m_buttons[SourceButton::DI_RZ].				setAxisSolo(SrceOffsetsID::Offset_RY, SrceAxisID::Axis_DIRX);
	m_buttons[SourceButton::DI_RZ_INV].			setAxisInvSolo(SrceOffsetsID::Offset_RY, SrceAxisID::Axis_DIRX);
	m_buttons[SourceButton::DI_RZ_TRIGGER].		setTrigger(SrceOffsetsID::Offset_RY, 0);
	m_buttons[SourceButton::DI_RX].				setAxisSolo(SrceOffsetsID::Offset_L2, SrceAxisID::Axis_DIRY);
	m_buttons[SourceButton::DI_RX_INV].			setAxisInvSolo(SrceOffsetsID::Offset_L2, SrceAxisID::Axis_DIRY);
	m_buttons[SourceButton::DI_RX_TRIGGER].		setTrigger(SrceOffsetsID::Offset_L2, 0);
	m_buttons[SourceButton::DI_RY].				setAxisSolo(SrceOffsetsID::Offset_R2, SrceAxisID::Axis_DIRZ);
	m_buttons[SourceButton::DI_RY_INV].			setAxisInvSolo(SrceOffsetsID::Offset_R2, SrceAxisID::Axis_DIRZ);
	m_buttons[SourceButton::DI_RY_TRIGGER].		setTrigger(SrceOffsetsID::Offset_R2, 0);
	m_buttons[SourceButton::DI_SL0].			setAxisSolo(SrceOffsetsID::Offset_SL0, SrceAxisID::Axis_SLIDER1);
	m_buttons[SourceButton::DI_SL0_INV].		setAxisInvSolo(SrceOffsetsID::Offset_SL0, SrceAxisID::Axis_SLIDER1);
	m_buttons[SourceButton::DI_SL0_TRIGGER].	setTrigger(SrceOffsetsID::Offset_SL0, 0);
	m_buttons[SourceButton::DI_SL1].			setAxisSolo(SrceOffsetsID::Offset_SL1, SrceAxisID::Axis_SLIDER2);
	m_buttons[SourceButton::DI_SL1_INV].		setAxisInvSolo(SrceOffsetsID::Offset_SL1, SrceAxisID::Axis_SLIDER2);
	m_buttons[SourceButton::DI_SL1_TRIGGER].	setTrigger(SrceOffsetsID::Offset_SL1, 0);
		
	m_buttons[SourceButton::SQUARE].			setButton(SrceOffsetsID::Offset_BUTTON1, 0b1);
	m_buttons[SourceButton::CROSS].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b10);
	m_buttons[SourceButton::CIRCLE].			setButton(SrceOffsetsID::Offset_BUTTON1, 0b100);
	m_buttons[SourceButton::TRIANGLE].			setButton(SrceOffsetsID::Offset_BUTTON1, 0b1000);
	m_buttons[SourceButton::L1].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b10000);
	m_buttons[SourceButton::R1].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b100000);
	m_buttons[SourceButton::L2].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b1000000);
	m_buttons[SourceButton::R2].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b10000000);
	m_buttons[SourceButton::SHARE].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b100000000);
	m_buttons[SourceButton::OPTIONS].			setButton(SrceOffsetsID::Offset_BUTTON1, 0b1000000000);
	m_buttons[SourceButton::L3].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b10000000000);
	m_buttons[SourceButton::R3].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b100000000000);
	m_buttons[SourceButton::PS].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b1000000000000);
	m_buttons[SourceButton::TOUCH].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b10000000000000);
	m_buttons[SourceButton::MUTE].				setButton(SrceOffsetsID::Offset_BUTTON1, 0b100000000000000);
	m_buttons[SourceButton::Button16].			setButton(SrceOffsetsID::Offset_BUTTON1, 0b1000000000000000);

	m_buttons[SourceButton::L1R1].				setSimultaneous(SrceOffsetsID::Offset_BUTTON1, 0b10000, SrceOffsetsID::Offset_BUTTON1, 0b100000, SourceButton::L1R1);
	m_buttons[SourceButton::L2R2].				setSimultaneous(SrceOffsetsID::Offset_BUTTON1, 0b1000000, SrceOffsetsID::Offset_BUTTON1, 0b10000000, SourceButton::L2R2);

	m_buttons[SourceButton::TOUCHUP].			setTouch(SrceOffsetsID::Offset_BUTTON1, 0b10000000000000, 8);
	m_buttons[SourceButton::TOUCHPAD].			setTouch(SrceOffsetsID::Offset_BUTTON1, 0b10000000000000, 0);
	m_buttons[SourceButton::TOUCH1].			setTouch(SrceOffsetsID::Offset_BUTTON1, 0b10000000000000, 1);
	m_buttons[SourceButton::TOUCH2].			setTouch(SrceOffsetsID::Offset_BUTTON1, 0b10000000000000, 2);
	m_buttons[SourceButton::TOUCH3].			setTouch(SrceOffsetsID::Offset_BUTTON1, 0b10000000000000, 3);
	m_buttons[SourceButton::TOUCH4].			setTouch(SrceOffsetsID::Offset_BUTTON1, 0b10000000000000, 4);
	m_buttons[SourceButton::TOUCHL].			setTouch(SrceOffsetsID::Offset_BUTTON1, 0b10000000000000, 5);
	m_buttons[SourceButton::TOUCHR].			setTouch(SrceOffsetsID::Offset_BUTTON1, 0b10000000000000, 6);

	m_buttons[SourceButton::Button17].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b1);
	m_buttons[SourceButton::Button18].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b10);
	m_buttons[SourceButton::Button19].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b100);
	m_buttons[SourceButton::Button20].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b1000);
	m_buttons[SourceButton::Button21].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b10000);
	m_buttons[SourceButton::Button22].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b100000);
	m_buttons[SourceButton::Button23].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b1000000);
	m_buttons[SourceButton::Button24].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b10000000);
	m_buttons[SourceButton::Button25].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b100000000);
	m_buttons[SourceButton::Button26].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b1000000000);
	m_buttons[SourceButton::Button27].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b10000000000);
	m_buttons[SourceButton::Button28].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b100000000000);
	m_buttons[SourceButton::Button29].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b1000000000000);
	m_buttons[SourceButton::Button30].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b10000000000000);
	m_buttons[SourceButton::Button31].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b100000000000000);
	m_buttons[SourceButton::Button32].			setButton(SrceOffsetsID::Offset_BUTTON2, 0b1000000000000000);

	m_buttons[SourceButton::DPAD_LEFT].			setButton(SrceOffsetsID::Offset_DPAD, 0b1);
	m_buttons[SourceButton::DPAD_UP].			setButton(SrceOffsetsID::Offset_DPAD, 0b10);
	m_buttons[SourceButton::DPAD_RIGHT].		setButton(SrceOffsetsID::Offset_DPAD, 0b100);
	m_buttons[SourceButton::DPAD_DOWN].			setButton(SrceOffsetsID::Offset_DPAD, 0b1000);
	m_buttons[SourceButton::DPAD2_LEFT].		setButton(SrceOffsetsID::Offset_DPAD, 0b10000);
	m_buttons[SourceButton::DPAD2_UP].			setButton(SrceOffsetsID::Offset_DPAD, 0b100000);
	m_buttons[SourceButton::DPAD2_RIGHT].		setButton(SrceOffsetsID::Offset_DPAD, 0b1000000);
	m_buttons[SourceButton::DPAD2_DOWN].		setButton(SrceOffsetsID::Offset_DPAD, 0b10000000);
	m_buttons[SourceButton::DPAD3_LEFT].		setButton(SrceOffsetsID::Offset_DPAD, 0b100000000);
	m_buttons[SourceButton::DPAD3_UP].			setButton(SrceOffsetsID::Offset_DPAD, 0b1000000000);
	m_buttons[SourceButton::DPAD3_RIGHT].		setButton(SrceOffsetsID::Offset_DPAD, 0b10000000000);
	m_buttons[SourceButton::DPAD3_DOWN].		setButton(SrceOffsetsID::Offset_DPAD, 0b100000000000);
	m_buttons[SourceButton::DPAD4_LEFT].		setButton(SrceOffsetsID::Offset_DPAD, 0b1000000000000);
	m_buttons[SourceButton::DPAD4_UP].			setButton(SrceOffsetsID::Offset_DPAD, 0b10000000000000);
	m_buttons[SourceButton::DPAD4_RIGHT].		setButton(SrceOffsetsID::Offset_DPAD, 0b100000000000000);
	m_buttons[SourceButton::DPAD4_DOWN].		setButton(SrceOffsetsID::Offset_DPAD, 0b1000000000000000);

	m_buttons[SourceButton::BATTERY].			setData(SourceButton::BATTERY);
	m_buttons[SourceButton::BATTERY0].			setData(SourceButton::BATTERY0);
	m_buttons[SourceButton::BATTERY1].			setData(SourceButton::BATTERY1);
	m_buttons[SourceButton::BATTERY2].			setData(SourceButton::BATTERY2);
	m_buttons[SourceButton::BATTERY3].			setData(SourceButton::BATTERY3);
	m_buttons[SourceButton::BATTERY4].			setData(SourceButton::BATTERY4);
	m_buttons[SourceButton::BATTERY5].			setData(SourceButton::BATTERY5);
	m_buttons[SourceButton::BATTERY6].			setData(SourceButton::BATTERY6);
	m_buttons[SourceButton::BATTERY7].			setData(SourceButton::BATTERY7);
	m_buttons[SourceButton::BATTERY8].			setData(SourceButton::BATTERY8);
	m_buttons[SourceButton::BATTERY9].			setData(SourceButton::BATTERY9);
	m_buttons[SourceButton::USB].				setButton(SrceOffsetsID::Offset_DIVERSE, 0b1);
	m_buttons[SourceButton::EARS].				setButton(SrceOffsetsID::Offset_DIVERSE, 0b10);
	m_buttons[SourceButton::MIC].				setButton(SrceOffsetsID::Offset_DIVERSE, 0b100);
	m_buttons[SourceButton::BT].				setButton(SrceOffsetsID::Offset_DIVERSE, 0b1000);
	m_buttons[SourceButton::FINGER].			setButton(SrceOffsetsID::Offset_DIVERSE, 0b10000);
	m_buttons[SourceButton::FINGERS].			setButton(SrceOffsetsID::Offset_DIVERSE, 0b100000);
	m_buttons[SourceButton::DS_ACTIVE].			setButton(SrceOffsetsID::Offset_DIVERSE, 0b1000000);
	m_buttons[SourceButton::DS4_ACTIVE].		setButton(SrceOffsetsID::Offset_DIVERSE, 0b10000000);
	m_buttons[SourceButton::DS5_ACTIVE].		setButton(SrceOffsetsID::Offset_DIVERSE, 0b100000000);
	m_buttons[SourceButton::DI_ACTIVE].			setButton(SrceOffsetsID::Offset_DIVERSE, 0b1000000000);
	
	m_buttons[SourceButton::DS_SELECTED].		setData(SourceButton::DS_SELECTED);
	m_buttons[SourceButton::DS4_SELECTED].		setData(SourceButton::DS4_SELECTED);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	m_buttons[SourceButton::DS5_SELECTED].		setData(SourceButton::DS5_SELECTED);
	m_buttons[SourceButton::DI_SELECTED].		setData(SourceButton::DI_SELECTED);
	m_buttons[SourceButton::INACTIVITY_5MN].	setData(SourceButton::INACTIVITY_5MN);
	m_buttons[SourceButton::INACTIVITY_10MN].	setData(SourceButton::INACTIVITY_10MN);
	m_buttons[SourceButton::INACTIVITY_15MN].	setData(SourceButton::INACTIVITY_15MN);
	m_buttons[SourceButton::INACTIVITY_30MN].	setData(SourceButton::INACTIVITY_30MN);
	m_buttons[SourceButton::NO_MOVEMENT_5MN].	setData(SourceButton::NO_MOVEMENT_5MN);
	m_buttons[SourceButton::NO_MOVEMENT_10MN].	setData(SourceButton::NO_MOVEMENT_10MN);
	m_buttons[SourceButton::NO_MOVEMENT_15MN].	setData(SourceButton::NO_MOVEMENT_15MN);
	m_buttons[SourceButton::NO_MOVEMENT_30MN].	setData(SourceButton::NO_MOVEMENT_30MN);
	
	m_buttons[SourceButton::SISAXIS_STANCE].	setData(SourceButton::SISAXIS_STANCE);
	m_buttons[SourceButton::SISAXIS_ZONE].		setData(SourceButton::SISAXIS_ZONE);
	m_buttons[SourceButton::SISAXIS_STANCE1].	setData(SourceButton::SISAXIS_STANCE1);
	m_buttons[SourceButton::SISAXIS_STANCE2].	setData(SourceButton::SISAXIS_STANCE2);
	m_buttons[SourceButton::SISAXIS_STANCE3].	setData(SourceButton::SISAXIS_STANCE3);
	m_buttons[SourceButton::SISAXIS_STANCE4].	setData(SourceButton::SISAXIS_STANCE4);
	m_buttons[SourceButton::SISAXIS_STANCE5].	setData(SourceButton::SISAXIS_STANCE5);
	m_buttons[SourceButton::SISAXIS_ZONE1].		setData(SourceButton::SISAXIS_ZONE1);
	m_buttons[SourceButton::SISAXIS_ZONE2].		setData(SourceButton::SISAXIS_ZONE2);
	m_buttons[SourceButton::SISAXIS_ZONE3].		setData(SourceButton::SISAXIS_ZONE3);
	m_buttons[SourceButton::SISAXIS_ZONE4].		setData(SourceButton::SISAXIS_ZONE4);
	m_buttons[SourceButton::SISAXIS_ZONE5].		setData(SourceButton::SISAXIS_ZONE5);
	
	m_buttons[SourceButton::SISAXIS_ROLL].			setAxisSolo(SrceOffsetsID::Offset_ROLL, SrceAxisID::Axis_ROLL);
	m_buttons[SourceButton::SISAXIS_ROLL_INV].		setAxisInvSolo(SrceOffsetsID::Offset_ROLL, SrceAxisID::Axis_ROLL);
	m_buttons[SourceButton::SISAXIS_ROLL_TRIGGER].	setTrigger(SrceOffsetsID::Offset_ROLL_TRIGGER, 0);
	m_buttons[SourceButton::SISAXIS_LEFT1].			setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b1);
	m_buttons[SourceButton::SISAXIS_LEFT2].			setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b10);
	m_buttons[SourceButton::SISAXIS_LEFT3].			setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b100);
	m_buttons[SourceButton::SISAXIS_LEFT4].			setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b1000);
	m_buttons[SourceButton::SISAXIS_LEFT5].			setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b10000);
	m_buttons[SourceButton::SISAXIS_LEFT6].			setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b100000);
	m_buttons[SourceButton::SISAXIS_LEFT7].			setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b1000000);
	m_buttons[SourceButton::SISAXIS_RIGHT1].		setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b10000000);
	m_buttons[SourceButton::SISAXIS_RIGHT2].		setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b100000000);
	m_buttons[SourceButton::SISAXIS_RIGHT3].		setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b1000000000);
	m_buttons[SourceButton::SISAXIS_RIGHT4].		setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b10000000000);
	m_buttons[SourceButton::SISAXIS_RIGHT5].		setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b100000000000);
	m_buttons[SourceButton::SISAXIS_RIGHT6].		setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b1000000000000);
	m_buttons[SourceButton::SISAXIS_RIGHT7].		setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b10000000000000);
	m_buttons[SourceButton::SISAXIS_ROLL_CENTER].	setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b100000000000000);
	m_buttons[SourceButton::SISAXIS_RIGHT].			setButton(SrceOffsetsID::Offset_ROLL_BUTTONS, 0b1000000000000000);
	
	m_buttons[SourceButton::SISAXIS_YAW].			setAxisSolo(SrceOffsetsID::Offset_YAW, SrceAxisID::Axis_YAW);
	m_buttons[SourceButton::SISAXIS_YAW_INV].		setAxisInvSolo(SrceOffsetsID::Offset_YAW, SrceAxisID::Axis_YAW);
	m_buttons[SourceButton::SISAXIS_YAW_TRIGGER].	setTrigger(SrceOffsetsID::Offset_YAW_TRIGGER, 0);
	m_buttons[SourceButton::SISAXIS_ANTI1].			setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b1);
	m_buttons[SourceButton::SISAXIS_ANTI2].			setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b10);
	m_buttons[SourceButton::SISAXIS_ANTI3].			setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b100);
	m_buttons[SourceButton::SISAXIS_ANTI4].			setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b1000);
	m_buttons[SourceButton::SISAXIS_ANTI5].			setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b10000);
	m_buttons[SourceButton::SISAXIS_ANTI6].			setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b100000);
	m_buttons[SourceButton::SISAXIS_ANTI7].			setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b1000000);
	m_buttons[SourceButton::SISAXIS_CLOCK1].		setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b10000000);
	m_buttons[SourceButton::SISAXIS_CLOCK2].		setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b100000000);
	m_buttons[SourceButton::SISAXIS_CLOCK3].		setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b1000000000);
	m_buttons[SourceButton::SISAXIS_CLOCK4].		setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b10000000000);
	m_buttons[SourceButton::SISAXIS_CLOCK5].		setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b100000000000);
	m_buttons[SourceButton::SISAXIS_CLOCK6].		setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b1000000000000);
	m_buttons[SourceButton::SISAXIS_CLOCK7].		setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b10000000000000);
	m_buttons[SourceButton::SISAXIS_YAW_CENTER].	setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b100000000000000);
	m_buttons[SourceButton::SISAXIS_CLOCK].			setButton(SrceOffsetsID::Offset_YAW_BUTTONS, 0b1000000000000000);
	
	m_buttons[SourceButton::SISAXIS_PITCH].			setAxisSolo(SrceOffsetsID::Offset_PITCH, SrceAxisID::Axis_PITCH);
	m_buttons[SourceButton::SISAXIS_PITCH_INV].		setAxisInvSolo(SrceOffsetsID::Offset_PITCH, SrceAxisID::Axis_PITCH);
	m_buttons[SourceButton::SISAXIS_PITCH_TRIGGER].	setTrigger(SrceOffsetsID::Offset_PITCH_TRIGGER, 0);
	m_buttons[SourceButton::SISAXIS_REAR1].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b1);
	m_buttons[SourceButton::SISAXIS_REAR2].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b10);
	m_buttons[SourceButton::SISAXIS_REAR3].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b100);
	m_buttons[SourceButton::SISAXIS_REAR4].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b1000);
	m_buttons[SourceButton::SISAXIS_REAR5].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b10000);
	m_buttons[SourceButton::SISAXIS_REAR6].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b100000);
	m_buttons[SourceButton::SISAXIS_REAR7].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b1000000);
	m_buttons[SourceButton::SISAXIS_FORE1].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b10000000);
	m_buttons[SourceButton::SISAXIS_FORE2].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b100000000);
	m_buttons[SourceButton::SISAXIS_FORE3].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b1000000000);
	m_buttons[SourceButton::SISAXIS_FORE4].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b10000000000);
	m_buttons[SourceButton::SISAXIS_FORE5].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b100000000000);
	m_buttons[SourceButton::SISAXIS_FORE6].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b1000000000000);
	m_buttons[SourceButton::SISAXIS_FORE7].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b10000000000000);
	m_buttons[SourceButton::SISAXIS_PITCH_CENTER].	setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b100000000000000);
	m_buttons[SourceButton::SISAXIS_FORE].			setButton(SrceOffsetsID::Offset_PITCH_BUTTONS, 0b1000000000000000);
	
	m_buttons[SourceButton::SISAXIS_SIDEWARD].			setAxisSolo(SrceOffsetsID::Offset_SIDEWARD, SrceAxisID::Axis_SIDEWARD);
	m_buttons[SourceButton::SISAXIS_SIDEWARD_INV].		setAxisInvSolo(SrceOffsetsID::Offset_SIDEWARD, SrceAxisID::Axis_SIDEWARD);
	m_buttons[SourceButton::SISAXIS_SIDEWARD_TRIGGER].	setTrigger(SrceOffsetsID::Offset_SIDEWARD_TRIGGER, 0);
	m_buttons[SourceButton::SISAXIS_WEST1].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b1);
	m_buttons[SourceButton::SISAXIS_WEST2].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b10);
	m_buttons[SourceButton::SISAXIS_WEST3].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b100);
	m_buttons[SourceButton::SISAXIS_WEST4].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b1000);
	m_buttons[SourceButton::SISAXIS_WEST5].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b10000);
	m_buttons[SourceButton::SISAXIS_WEST6].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b100000);
	m_buttons[SourceButton::SISAXIS_EAST1].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b1000000);
	m_buttons[SourceButton::SISAXIS_EAST2].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b10000000);
	m_buttons[SourceButton::SISAXIS_EAST3].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b100000000);
	m_buttons[SourceButton::SISAXIS_EAST4].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b1000000000);
	m_buttons[SourceButton::SISAXIS_EAST5].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b10000000000);
	m_buttons[SourceButton::SISAXIS_EAST6].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b100000000000);
	m_buttons[SourceButton::SISAXIS_SIDEWARD_CENTER].	setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b1000000000000);
	m_buttons[SourceButton::SISAXIS_EAST].				setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b10000000000000);
	m_buttons[SourceButton::SISAXIS_GEAR_REAR].			setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b100000000000000);
	m_buttons[SourceButton::SISAXIS_GEAR_1].			setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b1000000000000000);
	
	m_buttons[SourceButton::SISAXIS_TOWARD].			setAxisSolo(SrceOffsetsID::Offset_TOWARD, SrceAxisID::Axis_TOWARD);
	m_buttons[SourceButton::SISAXIS_TOWARD_INV].		setAxisInvSolo(SrceOffsetsID::Offset_TOWARD, SrceAxisID::Axis_TOWARD);
	m_buttons[SourceButton::SISAXIS_TOWARD_TRIGGER].	setTrigger(SrceOffsetsID::Offset_TOWARD_TRIGGER, 0);
	m_buttons[SourceButton::SISAXIS_BACKWARD1].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b1);
	m_buttons[SourceButton::SISAXIS_BACKWARD2].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b10);
	m_buttons[SourceButton::SISAXIS_BACKWARD3].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b100);
	m_buttons[SourceButton::SISAXIS_BACKWARD4].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b1000);
	m_buttons[SourceButton::SISAXIS_BACKWARD5].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b10000);
	m_buttons[SourceButton::SISAXIS_BACKWARD6].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b100000);
	m_buttons[SourceButton::SISAXIS_FORWARD1].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b1000000);
	m_buttons[SourceButton::SISAXIS_FORWARD2].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b10000000);
	m_buttons[SourceButton::SISAXIS_FORWARD3].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b100000000);
	m_buttons[SourceButton::SISAXIS_FORWARD4].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b1000000000);
	m_buttons[SourceButton::SISAXIS_FORWARD5].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b10000000000);
	m_buttons[SourceButton::SISAXIS_FORWARD6].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b100000000000);
	m_buttons[SourceButton::SISAXIS_TOWARD_CENTER].		setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b1000000000000);
	m_buttons[SourceButton::SISAXIS_FORWARD].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b10000000000000);
	m_buttons[SourceButton::SISAXIS_GEAR_2].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b100000000000000);
	m_buttons[SourceButton::SISAXIS_GEAR_3].			setButton(SrceOffsetsID::Offset_TOWARD_BUTTONS, 0b1000000000000000);
	m_buttons[SourceButton::SISAXIS_GEAR_REAR].			setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b100000000000000);
	m_buttons[SourceButton::SISAXIS_GEAR_1].			setButton(SrceOffsetsID::Offset_SIDEWARD_BUTTONS, 0b1000000000000000);
	
	m_buttons[SourceButton::SISAXIS_TOWARD].		setAxisSolo(SrceOffsetsID::Offset_TOWARD, SrceAxisID::Axis_TOWARD);
	m_buttons[SourceButton::SISAXIS_TOWARD_INV].	setAxisInvSolo(SrceOffsetsID::Offset_TOWARD, SrceAxisID::Axis_TOWARD);
	m_buttons[SourceButton::SISAXIS_LEVEL_TRIGGER].	setTrigger(SrceOffsetsID::Offset_LEVEL_TRIGGER, 0);
	m_buttons[SourceButton::SISAXIS_SOUTH1].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b1);
	m_buttons[SourceButton::SISAXIS_SOUTH2].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b10);
	m_buttons[SourceButton::SISAXIS_SOUTH3].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b100);
	m_buttons[SourceButton::SISAXIS_SOUTH4].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b1000);
	m_buttons[SourceButton::SISAXIS_SOUTH5].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b10000);
	m_buttons[SourceButton::SISAXIS_SOUTH6].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b100000);
	m_buttons[SourceButton::SISAXIS_NORTH1].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b1000000);
	m_buttons[SourceButton::SISAXIS_NORTH2].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b10000000);
	m_buttons[SourceButton::SISAXIS_NORTH3].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b100000000);
	m_buttons[SourceButton::SISAXIS_NORTH4].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b1000000000);
	m_buttons[SourceButton::SISAXIS_NORTH5].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b10000000000);
	m_buttons[SourceButton::SISAXIS_NORTH6].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b100000000000);
	m_buttons[SourceButton::SISAXIS_LEVEL_CENTER].	setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b1000000000000);
	m_buttons[SourceButton::SISAXIS_NORTH].			setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b10000000000000);
	m_buttons[SourceButton::SISAXIS_GEAR_4].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b100000000000000);
	m_buttons[SourceButton::SISAXIS_GEAR_5].		setButton(SrceOffsetsID::Offset_LEVEL_BUTTONS, 0b1000000000000000);

	m_buttons[SourceButton::SISAXIS_WHEEL].		setData(SourceButton::SISAXIS_WHEEL);
	m_buttons[SourceButton::SISAXIS_QUARTER].	setData(SourceButton::SISAXIS_QUARTER);

	m_buttons[SourceButton::MOUSE_AXEX].		setAxis(SrceOffsetsID::Offset_MOUSE_AXEX, SrceOffsetsID::Offset_MOUSE_AXEY, SrceAxisID::Axis_MOUSEX);
	m_buttons[SourceButton::MOUSE_AXEY].		setAxis(SrceOffsetsID::Offset_MOUSE_AXEY, SrceOffsetsID::Offset_MOUSE_AXEX, SrceAxisID::Axis_MOUSEY);

	m_buttons[SourceButton::MOUSE_SCROLL_DOWN_HIGH].	setButton(SrceOffsetsID::Offset_MOUSE_AXEZ, 0b1);
	m_buttons[SourceButton::MOUSE_SCROLL_DOWN].			setButton(SrceOffsetsID::Offset_MOUSE_AXEZ, 0b10);
	m_buttons[SourceButton::MOUSE_SCROLL_UP].			setButton(SrceOffsetsID::Offset_MOUSE_AXEZ, 0b100);
	m_buttons[SourceButton::MOUSE_SCROLL_UP_HIGH].		setButton(SrceOffsetsID::Offset_MOUSE_AXEZ, 0b1000);

	m_buttons[SourceButton::MOUSE_LEFT].		setTrigger(SrceOffsetsID::Offset_MOUSE_LEFT, 4112);
	m_buttons[SourceButton::MOUSE_RIGHT].		setTrigger(SrceOffsetsID::Offset_MOUSE_RIGHT, 4112);
	m_buttons[SourceButton::MOUSE_UP].			setTrigger(SrceOffsetsID::Offset_MOUSE_UP, 4112);
	m_buttons[SourceButton::MOUSE_DOWN].		setTrigger(SrceOffsetsID::Offset_MOUSE_DOWN, 4112);

	m_buttons[SourceButton::KBD_ACTIVE].		setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b1);
	m_buttons[SourceButton::MSE_ACTIVE].		setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b10);
	m_buttons[SourceButton::MSE_DI_ACTIVE].		setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b100);
	m_buttons[SourceButton::MOUSE_LBUTTON].		setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b1000);
	m_buttons[SourceButton::MOUSE_MBUTTON].		setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b10000);
	m_buttons[SourceButton::MOUSE_RBUTTON].		setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b100000);
	m_buttons[SourceButton::MOUSE_XBUTTON1].	setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b1000000);
	m_buttons[SourceButton::MOUSE_XBUTTON2].	setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b10000000);
	m_buttons[SourceButton::MOUSE_BUTTON6].		setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b100000000);
	m_buttons[SourceButton::MOUSE_BUTTON7].		setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b1000000000);
	m_buttons[SourceButton::MOUSE_BUTTON8].		setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b10000000000);
	m_buttons[SourceButton::KID_F1].			setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b100000000000);
	m_buttons[SourceButton::KID_F2].			setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b1000000000000);
	m_buttons[SourceButton::KID_F3].			setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b10000000000000);
	m_buttons[SourceButton::KID_F4].			setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b100000000000000);
	m_buttons[SourceButton::KID_F5].			setButton(SrceOffsetsID::Offset_KEYBOARD1, 0b1000000000000000);

	m_buttons[SourceButton::KID_F6].			setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b1);
	m_buttons[SourceButton::KID_F7].			setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b10);
	m_buttons[SourceButton::KID_F8].			setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b100);
	m_buttons[SourceButton::KID_F9].			setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b1000);
	m_buttons[SourceButton::KID_F10].			setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b10000);
	m_buttons[SourceButton::KID_F11].			setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b100000);
	m_buttons[SourceButton::KID_F12].			setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b1000000);
	m_buttons[SourceButton::KID_0].				setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b10000000);
	m_buttons[SourceButton::KID_1].				setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b100000000);
	m_buttons[SourceButton::KID_2].				setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b1000000000);
	m_buttons[SourceButton::KID_3].				setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b10000000000);
	m_buttons[SourceButton::KID_4].				setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b100000000000);
	m_buttons[SourceButton::KID_5].				setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b1000000000000);
	m_buttons[SourceButton::KID_6].				setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b10000000000000);
	m_buttons[SourceButton::KID_7].				setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b100000000000000);
	m_buttons[SourceButton::KID_8].				setButton(SrceOffsetsID::Offset_KEYBOARD2, 0b1000000000000000);

	m_buttons[SourceButton::KID_9].				setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b1);
	m_buttons[SourceButton::KID_OEM_MINUS].		setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b10);
	m_buttons[SourceButton::KID_OEM_PLUS].		setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b100);
	m_buttons[SourceButton::KID_OEM_1].			setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b1000);
	m_buttons[SourceButton::KID_OEM_2].			setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b10000);
	m_buttons[SourceButton::KID_OEM_3].			setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b100000);
	m_buttons[SourceButton::KID_OEM_4].			setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b1000000);
	m_buttons[SourceButton::KID_OEM_5].			setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b10000000);
	m_buttons[SourceButton::KID_OEM_6].			setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b100000000);
	m_buttons[SourceButton::KID_OEM_7].			setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b1000000000);
	m_buttons[SourceButton::KID_OEM_8].			setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b10000000000);
	m_buttons[SourceButton::KID_OEM_102].		setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b100000000000);
	m_buttons[SourceButton::KID_OEM_COMMA].		setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b1000000000000);
	m_buttons[SourceButton::KID_OEM_PERIOD].	setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b10000000000000);
	m_buttons[SourceButton::KID_A].				setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b100000000000000);
	m_buttons[SourceButton::KID_B].				setButton(SrceOffsetsID::Offset_KEYBOARD3, 0b1000000000000000);

	m_buttons[SourceButton::KID_C].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b1);
	m_buttons[SourceButton::KID_D].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b10);
	m_buttons[SourceButton::KID_E].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b100);
	m_buttons[SourceButton::KID_F].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b1000);
	m_buttons[SourceButton::KID_G].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b10000);
	m_buttons[SourceButton::KID_H].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b100000);
	m_buttons[SourceButton::KID_I].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b1000000);
	m_buttons[SourceButton::KID_J].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b10000000);
	m_buttons[SourceButton::KID_K].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b100000000);
	m_buttons[SourceButton::KID_L].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b1000000000);
	m_buttons[SourceButton::KID_M].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b10000000000);
	m_buttons[SourceButton::KID_N].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b100000000000);
	m_buttons[SourceButton::KID_O].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b1000000000000);
	m_buttons[SourceButton::KID_P].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b10000000000000);
	m_buttons[SourceButton::KID_Q].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b100000000000000);
	m_buttons[SourceButton::KID_R].				setButton(SrceOffsetsID::Offset_KEYBOARD4, 0b1000000000000000);

	m_buttons[SourceButton::KID_S].				setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b1);
	m_buttons[SourceButton::KID_T].				setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b10);
	m_buttons[SourceButton::KID_U].				setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b100);
	m_buttons[SourceButton::KID_V].				setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b1000);
	m_buttons[SourceButton::KID_W].				setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b10000);
	m_buttons[SourceButton::KID_X].				setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b100000);
	m_buttons[SourceButton::KID_Y].				setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b1000000);
	m_buttons[SourceButton::KID_Z].				setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b10000000);
	m_buttons[SourceButton::KID_ESCAPE].		setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b100000000);
	m_buttons[SourceButton::KID_TAB].			setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b1000000000);
	m_buttons[SourceButton::KID_RETURN].		setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b10000000000);
	m_buttons[SourceButton::KID_SPACE].			setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b100000000000);
	m_buttons[SourceButton::KID_BACK].			setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b1000000000000);
	m_buttons[SourceButton::KID_DELETE].		setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b10000000000000);
	m_buttons[SourceButton::KID_INSERT].		setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b100000000000000);
	m_buttons[SourceButton::KID_NUMLOCK].		setButton(SrceOffsetsID::Offset_KEYBOARD5, 0b1000000000000000);

	m_buttons[SourceButton::KID_LSHIFT].		setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b1);
	m_buttons[SourceButton::KID_RSHIFT].		setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b10);
	m_buttons[SourceButton::KID_LCONTROL].		setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b100);
	m_buttons[SourceButton::KID_RCONTROL].		setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b1000);
	m_buttons[SourceButton::KID_LWIN].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b10000);
	m_buttons[SourceButton::KID_RWIN].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b100000);
	m_buttons[SourceButton::KID_LMENU].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b1000000);
	m_buttons[SourceButton::KID_RMENU].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b10000000);
	m_buttons[SourceButton::KID_LEFT].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b100000000);
	m_buttons[SourceButton::KID_UP].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b1000000000);
	m_buttons[SourceButton::KID_RIGHT].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b10000000000);
	m_buttons[SourceButton::KID_DOWN].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b100000000000);
	m_buttons[SourceButton::KID_PRIOR].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b1000000000000);
	m_buttons[SourceButton::KID_NEXT].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b10000000000000);
	m_buttons[SourceButton::KID_END].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b100000000000000);
	m_buttons[SourceButton::KID_HOME].			setButton(SrceOffsetsID::Offset_KEYBOARD6, 0b1000000000000000);

	m_buttons[SourceButton::KID_NUMPAD0].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b1);
	m_buttons[SourceButton::KID_NUMPAD1].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b10);
	m_buttons[SourceButton::KID_NUMPAD2].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b100);
	m_buttons[SourceButton::KID_NUMPAD3].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b1000);
	m_buttons[SourceButton::KID_NUMPAD4].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b10000);
	m_buttons[SourceButton::KID_NUMPAD5].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b100000);
	m_buttons[SourceButton::KID_NUMPAD6].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b1000000);
	m_buttons[SourceButton::KID_NUMPAD7].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b10000000);
	m_buttons[SourceButton::KID_NUMPAD8].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b100000000);
	m_buttons[SourceButton::KID_NUMPAD9].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b1000000000);
	m_buttons[SourceButton::KID_DIVIDE].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b10000000000);
	m_buttons[SourceButton::KID_MULTIPLY].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b100000000000);
	m_buttons[SourceButton::KID_SUBTRACT].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b1000000000000);
	m_buttons[SourceButton::KID_ADD].			setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b10000000000000);
	m_buttons[SourceButton::KID_SEPARATOR].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b100000000000000);
	m_buttons[SourceButton::KID_DECIMAL].		setButton(SrceOffsetsID::Offset_KEYBOARD7, 0b1000000000000000);

	InitDIClient(true);

	//Get XInput outside program, even when no focus, with XInputGetState_DLL instead of XInputGetState
	{
		HINSTANCE	hXInputdll;
		FARPROC		hXInputdll_GetProcessID;
		//Create an HINSTANCE of the xinput1_4.dll
		hXInputdll = LoadLibrary(L"xinput1_4.dll");

		//Get the address of ordinal 100 which is XInputGetState
		if (hXInputdll != NULL)
		{
			hXInputdll_GetProcessID = GetProcAddress(HMODULE(hXInputdll), (LPCSTR)100);

			//Assign it to XInputGetState_DLL for easier use
			XInputGetState_DLL = XIDLLFUNC(hXInputdll_GetProcessID);

			FreeLibrary(hXInputdll);
		}
	}
}

void Source::ListOfJoysticks()
{
	if (m_diInterface == NULL)
		return;

	tape.DevicesList.clear();
	DIJOYCONFIG PreferredJoyCfg = {};
	DI_ENUM_CONTEXT enumContext;
	enumContext.pPreferredJoyCfg = &PreferredJoyCfg;
	enumContext.bPreferredJoyCfgValid = false;
	m_diInterface->EnumDevices(DI8DEVCLASS_GAMECTRL, ListOfJoysticksCallback, &enumContext, DIEDFL_ATTACHEDONLY | DIEDFL_INCLUDEHIDDEN);
}

BOOL Source::InitDIClient(bool verbose)
{
	// Create a DInput object
	if (SUCCEEDED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_diInterface, nullptr)))
	{
		if (verbose)
			echo(I18N.di_client_connected);

		// Initialize the direct input interface for the mouse.
		if (SUCCEEDED(m_diInterface->CreateDevice(GUID_SysMouse, &m_diMouse, NULL)))
		{
			// Set the data format for the mouse using the pre-defined mouse data format.
			if (SUCCEEDED(m_diMouse->SetDataFormat(&c_dfDIMouse2)))
			{
				// Set the cooperative level of the mouse to share with other programs.
				if (SUCCEEDED(m_diMouse->SetCooperativeLevel(tape.Ds2hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
				{
					// Acquire the mouse.
					if (SUCCEEDED(m_diMouse->Acquire()))
					{
						{
							DIPROPRANGE diprg;
							diprg.diph.dwSize = sizeof(DIPROPRANGE);
							diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
							diprg.diph.dwHow = DIPH_DEVICE;
							diprg.diph.dwObj = 0;
							diprg.lMin = 0;
							diprg.lMax = 65535;
							HRESULT hr = m_diMouse->SetProperty(DIPROP_RANGE, &diprg.diph);
						}
						
						{
							DIPROPDWORD dipdw;
							dipdw.diph.dwSize = sizeof(DIPROPDWORD);
							dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
							dipdw.diph.dwHow = DIPH_DEVICE;
							dipdw.diph.dwObj = 0;
							dipdw.dwData = DIPROPAXISMODE_ABS;
							HRESULT hr = m_diMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
							m_diMouseActive = true;
						}
					}
				}
			}
		}
		return TRUE;
	}
	else
	{
		if (verbose)
			echo(I18N.di_failed_acquire);
		return FALSE;
	}
}

BOOL Source::Active()
{
	if (tape.ActualSource == 4)
		return m_xiConnected;
	else if (tape.ActualSource == 3)
	{
		if (wcslen(tape.Device1) && wcslen(tape.Device2))
			return (m_diJoystick1 != NULL && m_diJoystick2 != NULL);
		else
			return m_diJoystick1 != NULL;
	}
	else if (tape.ActualSource)
		return dsHandle != INVALID_HANDLE_VALUE;
	else
		return FALSE;
}

BOOL Source::PreOpen(bool verbose)
{
	tape.ActualSource = 0;

	if (tape.PreferredSource == 4)
	{
		DWORD dwResult = XInputGetState_DLL(tape.XInputDevice, &m_xiController);
		if (dwResult == ERROR_SUCCESS)
		{
			m_xiConnected = true;
			tape.ActualSource = 4;
			return TRUE;
		}
		else
		{
			m_xiConnected = false;
			return FALSE;
		}
	}
	else if (tape.PreferredSource == 3)
	{
		m_diTween = false;
		m_bBluetooth = false;
		if (m_diInterface == NULL)
			if (!InitDIClient(verbose))
				return FALSE;

		DIJOYCONFIG PreferredJoyCfg = {};
		DI_ENUM_CONTEXT enumContext;
		enumContext.pPreferredJoyCfg = &PreferredJoyCfg;
		enumContext.bPreferredJoyCfgValid = false;

		Microsoft::WRL::ComPtr<IDirectInputJoyConfig8> pJoyConfig;
		if (FAILED(m_diInterface->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&pJoyConfig)))
			return FALSE;

		// This function is expected to fail if no joystick is attached
		PreferredJoyCfg.dwSize = sizeof(PreferredJoyCfg);
		for (int i = 0; true; i++)
		{
			HRESULT hr = (pJoyConfig->GetConfig(i, &PreferredJoyCfg, DIJC_GUIDINSTANCE));
			if (SUCCEEDED(hr))
			{
				enumContext.bPreferredJoyCfgValid = true;
				break;
			}
			else if (hr == DIERR_NOMOREITEMS)
				return FALSE;
		}

		// Look for a simple joystick we can use for this sample program.
		if (FAILED(m_diInterface->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback1, &enumContext, DIEDFL_ATTACHEDONLY | DIEDFL_INCLUDEHIDDEN)))
			return FALSE;

		// Make sure we got a joystick
		if (!m_diJoystick1)
			return FALSE;

		// Set the data format to c_dfDIJoystick2 a predefined extended data format with passing a DIJOYSTATE2 structure to GetJoystickState()
		if (FAILED(m_diJoystick1->SetDataFormat(&c_dfDIJoystick2)))
			return FALSE;

		// Set the cooperative level to let DInput know how this device
		// should interact with the system and with other DInput applications
		if (FAILED(m_diJoystick1->SetCooperativeLevel(tape.Ds2hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
			return FALSE;

		m_dipoll1 = true;
		m_diXAxis1 = false;
		m_diYAxis1 = false;
		m_diZAxis1 = false;
		m_diRXAxis1 = false;
		m_diRYAxis1 = false;
		m_diRZAxis1 = false;
		m_diSliderCount1 = 0;
		m_diPOVCount1 = 0;
		m_diButtonCount1 = 0;
		// Enumerate the joystick objects
		if (FAILED(m_diJoystick1->EnumObjects(EnumObjectsCallback1, (VOID*)tape.Ds2hWnd, DIDFT_ALL)))
			return FALSE;

		if (wcslen(tape.Device1) && wcslen(tape.Device2))
		{
			DIJOYCONFIG PreferredJoyCfg = {};
			DI_ENUM_CONTEXT enumContext;
			enumContext.pPreferredJoyCfg = &PreferredJoyCfg;
			enumContext.bPreferredJoyCfgValid = false;

			Microsoft::WRL::ComPtr<IDirectInputJoyConfig8> pJoyConfig;
			if (FAILED(m_diInterface->QueryInterface(IID_IDirectInputJoyConfig8, (void**)&pJoyConfig)))
				return FALSE;

			// This function is expected to fail if no joystick is attached
			PreferredJoyCfg.dwSize = sizeof(PreferredJoyCfg);
			for (int i = 0; true; i++)
			{
				HRESULT hr = (pJoyConfig->GetConfig(i, &PreferredJoyCfg, DIJC_GUIDINSTANCE));
				if (SUCCEEDED(hr))
				{
					enumContext.bPreferredJoyCfgValid = true;
					break;
				}
				else if (hr == DIERR_NOMOREITEMS)
					return FALSE;
			}

			// Look for a simple joystick we can use for this sample program.
			if (FAILED(m_diInterface->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback2, &enumContext, DIEDFL_ATTACHEDONLY | DIEDFL_INCLUDEHIDDEN)))
				return FALSE;

			// Make sure we got a joystick
			if (!m_diJoystick2)
				return FALSE;

			// Set the data format to c_dfDIJoystick2 a predefined extended data format with passing a DIJOYSTATE2 structure to GetJoystickState()
			if (FAILED(m_diJoystick2->SetDataFormat(&c_dfDIJoystick2)))
				return FALSE;

			// Set the cooperative level to let DInput know how this device
			// should interact with the system and with other DInput applications
			if (FAILED(m_diJoystick2->SetCooperativeLevel(tape.Ds2hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
				return FALSE;

			m_dipoll2 = true;
			m_diXAxis2 = false;
			m_diYAxis2 = false;
			m_diZAxis2 = false;
			m_diRXAxis2 = false;
			m_diRYAxis2 = false;
			m_diRZAxis2 = false;
			m_diSliderCount2 = 0;
			m_diPOVCount2 = 0;
			m_diButtonCount2 = 0;
			// Enumerate the joystick objects
			if (FAILED(m_diJoystick2->EnumObjects(EnumObjectsCallback2, (VOID*)tape.Ds2hWnd, DIDFT_ALL)))
				return FALSE;

			m_diTween = true;
		}

		tape.ActualSource = 3;
		return TRUE;
	}
	else if (tape.PreferredSource)
	{
		int ndsType = 0;
		m_bBluetooth = false;

		GUID guid;
		HidD_GetHidGuid(&guid);
		hDevInfo = SetupDiGetClassDevs(&guid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
		if (hDevInfo == 0)
		{
			SetupDiDestroyDeviceInfoList(hDevInfo);
			return FALSE;
		}
		SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
		DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData);

		detail = 0;
		DWORD RequiredSize;

		for (int i = 0; SetupDiEnumDeviceInterfaces(hDevInfo, 0, &guid, i, &DeviceInterfaceData) != 0; i++)
		{
			RequiredSize = 0;
			SetupDiGetDeviceInterfaceDetail(hDevInfo, &DeviceInterfaceData, NULL, 0, &RequiredSize, NULL);
			if (RequiredSize == 0)
				continue;

			if (detail != 0)
				free(detail);

			if (dsHandle != INVALID_HANDLE_VALUE)
			{
				if (dsHandle)
					CloseHandle(dsHandle);
				dsHandle = INVALID_HANDLE_VALUE;
			}

			if (m_OutputBuf != NULL)
			{
				free(m_OutputBuf);
				m_OutputBuf = NULL;
			}

			if (m_InputBuf != NULL)
			{
				free(m_InputBuf);
				m_InputBuf = NULL;
			}

			detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(RequiredSize);
			if (detail == 0)
				continue;

			detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			DWORD dwRequiredSize;
			if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &DeviceInterfaceData, detail, RequiredSize, &dwRequiredSize, NULL))
				continue;

			dsHandle = CreateFile(detail->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);

			if (dsHandle == INVALID_HANDLE_VALUE)
				continue;

			Attributes.Size = sizeof(Attributes);
			if (dsHandle == 0)
				continue;
			if (!HidD_GetAttributes(dsHandle, &Attributes))
				continue;
			if (dsVendorID != Attributes.VendorID)
				continue;

			if (0x5C4 == Attributes.ProductID || 0x9CC == Attributes.ProductID || 0xBA0 == Attributes.ProductID)
			{
				if (tape.PreferredSource == 1 && SerialTest(1, verbose)) { tape.ActualSource = 1; return TRUE; }
			}
			else if (0x0CE6 == Attributes.ProductID)
			{
				if (tape.PreferredSource == 2 && SerialTest(2, verbose)) { tape.ActualSource = 2; return TRUE; }
			}

			continue;
		}

		CloseHandle(dsHandle);
		dsHandle = INVALID_HANDLE_VALUE;
		return FALSE;
	}
	return TRUE;
}

BOOL Source::SetSerial(const WCHAR* szTarget)
{
	if (wcslen(szTarget) + 1 > MAX_Serial_Length)
		return FALSE;
	wcscpy_s(m_TargetSerial, wcslen(szTarget) + 1, szTarget);

	return TRUE;
}

BOOL Source::SerialTest(int devicetype, bool verbose)
{
	memset(dsSerial, 0, sizeof(dsSerial));

	if (m_bBluetooth)
	{
		if (!HidD_GetSerialNumberString(dsHandle, dsSerial, sizeof(dsSerial)))
			return FALSE;

		if (devicetype == 2)
		{
			unsigned char buf[78] = { 5 };
			if (!HidD_GetFeature(dsHandle, buf, sizeof(buf)))
				return FALSE;
		}
	}
	else
	{
		if (devicetype == 2)
		{
			unsigned char buf[78] = { 9 };
			if (!HidD_GetFeature(dsHandle, buf, sizeof(buf)))
				return FALSE;
			swprintf_s(dsSerial, MAX_Serial_Length, L"%02x%02x%02x%02x%02x%02x", buf[6], buf[5], buf[4], buf[3], buf[2], buf[1]);
		}
		else
		{
			unsigned char buf[16] = { 18 };
			if (!HidD_GetFeature(dsHandle, buf, sizeof(buf)))
				return FALSE;
			swprintf_s(dsSerial, MAX_Serial_Length, L"%02x%02x%02x%02x%02x%02x", buf[6], buf[5], buf[4], buf[3], buf[2], buf[1]);
			if (buf[6] == 192 && buf[5] == 19 && ((buf[4] & 0b11110000) >> 4) == 3)	//Skip ViGem DS4
				return FALSE;
		}
	}

	if (0 != m_TargetSerial[0] && _wcsicmp(m_TargetSerial, dsSerial) != 0 && verbose)
	{
		if (devicetype == 2)
			echo(I18N.ds_skip_controller, L"DualSense", dsSerial);
		else
			echo(I18N.ds_skip_controller, L"DualShock", dsSerial);
		return FALSE;
	}

	return TRUE;
}

BOOL Source::Open(HWND hWnd, bool verbose)
{
	if (tape.ActualSource == 4)
	{
		if (m_xiConnected)
		{
			if (verbose)
				echo(I18N.xi_pad_acquired, tape.XInputDevice + 1);
		}
		else
			return FALSE;
	}
	else if (tape.ActualSource == 3)
	{
		if (verbose)
			firstflag = true;
		// Poll the device to read the current state
		HRESULT hr1;
		HRESULT hr2;
		DIJOYSTATE2 js1;
		DIJOYSTATE2 js2;
		hr1 = m_diJoystick1->Poll();
		if (m_diTween)
			hr2 = m_diJoystick2->Poll();
		else
			hr2 = DI_NOEFFECT;

		if (SUCCEEDED(hr1) && SUCCEEDED(hr2))
		{
			switch (hr1)
			{
			case DI_OK:
			{
				m_dipoll1 = true;
				break;
			}
			case DI_NOEFFECT:
			{
				m_dipoll1 = false;
				break;
			}
			}
			if (verbose)
				echo(I18N.di_pad_acquired, m_diProductName1);

			if (m_diTween)
			{
				switch (hr2)
				{
				case DI_OK:
				{
					m_dipoll2 = true;
					break;
				}
				case DI_NOEFFECT:
				{
					m_dipoll2 = false;
					break;
				}
				}
				if (verbose)
					echo(I18N.di_pad_acquired, m_diProductName2);
			}
		}
		else
		{
			bool returnfalse = false;
			if (!SUCCEEDED(hr1))
			{
				m_dipoll1 = true;
				switch (hr1)
				{
				case DIERR_NOTACQUIRED:
				{
					if (tape.MappingPaused)
						returnfalse = true;
					else
					{
						hr1 = m_diJoystick1->Acquire();
						if (SUCCEEDED(hr1))
						{
							if (hr1 == DI_OK)
								echo(I18N.di_pad_acquired, m_diProductName1);
							break;
						}
						else
						{
							if (verbose)
								echo(I18N.di_failed_acquire);
							returnfalse = true;
						}
					}
					break;
				}
				case DIERR_NOTINITIALIZED:
				{
					if (!PreOpen())
					{
						if (verbose)
							echo(I18N.di_wait);
						returnfalse = true;
					}
					break;
				}
				case DIERR_INPUTLOST:
				{
					if (FAILED(m_diJoystick1->Acquire()))
					{
						if (verbose)
							echo(I18N.di_busy);
						returnfalse = true;
					}
					break;
				}
				case E_PENDING: { break; }
				case DIERR_INVALIDPARAM:
				case DIERR_OTHERAPPHASPRIO: { returnfalse = true; }
				}
			}
			if (!SUCCEEDED(hr2) && m_diTween)
			{
				m_dipoll2 = true;
				switch (hr2)
				{
				case DIERR_NOTACQUIRED:
				{
					if (tape.MappingPaused)
						returnfalse = true;
					else
					{
						hr2 = m_diJoystick2->Acquire();
						if (SUCCEEDED(hr2))
						{
							if (hr2 == DI_OK)
								echo(I18N.di_pad_acquired, m_diProductName2);
							break;
						}
						else
						{
							if (verbose)
								echo(I18N.di_failed_acquire);
							returnfalse = true;
						}
					}
					break;
				}
				case DIERR_NOTINITIALIZED:
				{
					if (!PreOpen())
					{
						if (verbose)
							echo(I18N.di_wait);
						returnfalse = true;
					}
					break;
				}
				case DIERR_INPUTLOST:
				{
					if (FAILED(m_diJoystick2->Acquire()))
					{
						if (verbose)
							echo(I18N.di_busy);
						returnfalse = true;
					}
					break;
				}
				case E_PENDING: { break; }
				case DIERR_INVALIDPARAM:
				case DIERR_OTHERAPPHASPRIO: { returnfalse = true; }
				}
			}
			if (returnfalse)
				return FALSE;
		}
	}
	else if (tape.ActualSource)
	{
		if (verbose)
			firstflag = true;

		if (dsHandle == INVALID_HANDLE_VALUE)
			return FALSE;

		PHIDP_PREPARSED_DATA PreparsedData;
		if (!HidD_GetPreparsedData(dsHandle, &PreparsedData))
			return FALSE;

		HIDP_CAPS cap;
		NTSTATUS r = HidP_GetCaps(PreparsedData, &cap);
		HidD_FreePreparsedData(PreparsedData);
		if (r != HIDP_STATUS_SUCCESS)
			return FALSE;

		//Buffer settings for sending and receiving
		m_inputLen = cap.InputReportByteLength;
		m_outputLen = cap.OutputReportByteLength;
		m_bBluetooth = m_inputLen > 64;

		if (tape.ActualSource == 2)
		{
			if (verbose)
				echo(I18N.ds_connect_controller, L"DualSense", dsSerial);
			char buf[64] = { 0x20 };
			if (!HidD_GetFeature(dsHandle, buf, sizeof(buf)))
			{
				echo(I18N.ds_firmware_fail);

				DWORD errorcode = GetLastError();
				LPVOID lpMsgBuf;
				FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
				echo(L"%d = %s", errorcode, (LPTSTR)lpMsgBuf);
				LocalFree(lpMsgBuf);
				return FALSE;
			}

			if (verbose)
				echo(I18N.ds_version, buf[45], buf[44]);
		}
		else if (verbose)
			echo(I18N.ds_connect_controller, L"DualShock", dsSerial);

		//Secure send / receive buffer
		m_InputBuf = (byte*)malloc(m_inputLen);
		m_OutputBuf = (byte*)malloc(m_outputLen);
		if (m_OutputBuf)
			memset(m_OutputBuf, 0, m_outputLen);
		if (m_InputBuf)
			memset(m_InputBuf, 0, m_inputLen);

		if (tape.ActualSource == 2)
		{
			if (m_bBluetooth)
			{
				m_OutputBuf[0] = 0x31;
				m_outputOffset = 1;
			}
			else
				m_outputOffset = 0;
			m_crcerrorcount = 0;
		}
		else
		{
			if (m_bBluetooth)
			{
				m_OutputBuf[0] = 0x11;
				m_OutputBuf[1] = 0x80;
				m_OutputBuf[3] = 0xFF;
				m_outputOffset = 6;
			}
			else
			{
				m_OutputBuf[0] = 0x05;
				m_OutputBuf[1] = 0xFF;
				m_outputOffset = 4;
			}
		}

		m_write_count = m_write_count2 = 0;

		if (detail != 0)
			free(detail);

		SetupDiDestroyDeviceInfoList(hDevInfo);
		m_hThread2 = (HANDLE)_beginthreadex(NULL, 0, outputloop, this, 0, &m_threadID2);

		firstflaglost = true;
		if (firstflag)
		{
			if (tape.ActualSource == 2)
				echo(I18N.ds_connection_started, L"DualSense");
			else
				echo(I18N.ds_connection_started, L"DualShock");
			firstflag = false;
		}
	}
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, inputloop, this, 0, &m_threadID);

	switch (tape.ActualSource)
	{
	case 1:
	case 2:
	{
		if (m_hThread == NULL || m_hThread2 == NULL)
		{
			echo(I18N.ds_failed_thread);
			return FALSE;
		}
		else
			SetThreadAffinityMask(m_hThread, 1);
		break;
	}
	case 3:
	{
		if (m_hThread == NULL)
		{
			echo(I18N.di_failed_thread);
			return FALSE;
		}
		else
			SetThreadAffinityMask(m_hThread, 1);
		break;
	}
	case 4:
	{
		if (m_hThread == NULL)
		{
			echo(I18N.xi_failed_thread);
			return FALSE;
		}
		else
			SetThreadAffinityMask(m_hThread, 1);
		break;
	}
	case 0:
	{
		if (m_hThread == NULL)
			return FALSE;
		else
			SetThreadAffinityMask(m_hThread, 1);
		break;
	}
	}

	return TRUE;
}

BOOL Source::Close(bool end)
{
	tape.ActualSource = 0;

	if (m_hThread && !m_threadShutdown)
	{
		m_threadShutdown = true;
		if (m_hThread != NULL)
			WaitForSingleObject(m_hThread, 100);
		m_write_cv.notify_one();
		if (m_hThread2 != NULL)
			WaitForSingleObject(m_hThread2, 100);
		m_hThread = NULL;
		m_hThread2 = NULL;
		m_write_count = m_write_count2 = 0;

		if (!end)
			m_threadShutdown = false;
	}

	memset(&tape.ReceivedData, 0, sizeof(tape.ReceivedData));
	memset(&m_receivedLast, 0, sizeof(m_receivedLast));
	memset(&m_receivedTouch, 0, sizeof(m_receivedTouch));
	if (m_callback)
		m_callback(true, m_callbackdata);

	if (end)
	{
		if (m_diMouse)
		{
			m_diMouse->Unacquire();
			m_diMouse->Release();
			m_diMouse = NULL;
		}
	}

	{
		m_xiConnected = false;
	}

	{
		m_diTween = false;
		if (m_diJoystick1)
			m_diJoystick1->Unacquire();
		if (m_diJoystick1)
			m_diJoystick1->Release();
		m_diJoystick1 = nullptr;
		if (m_diJoystick2)
			m_diJoystick2->Unacquire();
		if (m_diJoystick2)
			m_diJoystick2->Release();
		m_diJoystick2 = nullptr;
	}

	if (dsHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(dsHandle);
		dsHandle = INVALID_HANDLE_VALUE;
	}

	if (m_OutputBuf != NULL)
	{
		free(m_OutputBuf);
		m_OutputBuf = NULL;
	}

	if (m_InputBuf != NULL)
	{
		free(m_InputBuf);
		m_InputBuf = NULL;
	}

	memset(dsSerial, 0, sizeof(dsSerial));
	Clear();

	return FALSE;
} 

//Instruct the sending thread
BOOL Source::Write()
{
	m_write_count++;
	m_write_cv.notify_one();

	return TRUE;
}

//Receive loop from DS4
void Source::InputLoop()
{
	static std::chrono::system_clock::time_point looplast = std::chrono::system_clock::now();
	static std::chrono::system_clock::time_point loopnow = std::chrono::system_clock::now();

	while (!m_threadShutdown)
	{
		loopnow = std::chrono::system_clock::now();
		int loopdelay = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::microseconds(20) - (loopnow - looplast)).count();
		if (loopdelay > 0)
			uSleep(loopdelay);
		looplast = loopnow;

		memset(&tape.ReceivedData, 0, sizeof(tape.ReceivedData));
		memset(&m_receivedTouch, 0, sizeof(m_receivedTouch));
		static bool updateflag = false;
		updateflag = false;

		if (tape.ActualSource == 4)
		{
			DWORD dwResult = XInputGetState_DLL(tape.XInputDevice, &m_xiController);
			if (dwResult == ERROR_SUCCESS)
			{
				m_xiConnected = true;
				_parseXInput();
			}
			else
			{
				echo(I18N.xi_busy);
				Close();
				return;
			}
		}
		else if (tape.ActualSource == 3)
		{			
			if (m_diInterface == NULL || m_diJoystick1 == NULL)
			{
				echo(I18N.di_pad_unacquired, m_diProductName1);
				Close();
				return;
			}
			if (m_diTween && m_diJoystick2 == NULL)
			{
				echo(I18N.di_pad_unacquired, m_diProductName2);
				Close();
				return;
			}
			
			if (m_dipoll1)
			{
				HRESULT hr = m_diJoystick1->Poll();
			
				if (SUCCEEDED(hr))
				{
					if (hr == DI_NOEFFECT)
						m_dipoll1 = false;
				}
				else
				{
					switch (hr)
					{
					case DIERR_NOTACQUIRED:
					{
						if (FAILED(m_diJoystick1->Acquire()))
						{
							echo(I18N.di_pad_unacquired, m_diProductName1);
							Close();
							return;
						}
						break;
					}
					case DIERR_NOTINITIALIZED:
					{
						echo(I18N.di_pad_unacquired, m_diProductName1);
						Close();
						return;
					}
					case DIERR_INPUTLOST:
					{
						if (FAILED(m_diJoystick1->Acquire()))
						{
							echo(I18N.di_busy);
							Close();
							return;
						}
						break;
					}
					}
				}
			}
			if (m_diTween && m_dipoll2)
			{
				HRESULT hr = m_diJoystick2->Poll();
			
				if (SUCCEEDED(hr))
				{
					if (hr == DI_NOEFFECT)
						m_dipoll2 = false;
				}
				else
				{
					switch (hr)
					{
					case DIERR_NOTACQUIRED:
					{
						if (FAILED(m_diJoystick2->Acquire()))
						{
							echo(I18N.di_pad_unacquired, m_diProductName2);
							Close();
							return;
						}
						break;
					}
					case DIERR_NOTINITIALIZED:
					{
						echo(I18N.di_pad_unacquired, m_diProductName2);
						Close();
						return;
					}
					case DIERR_INPUTLOST:
					{
						if (FAILED(m_diJoystick1->Acquire()))
						{
							echo(I18N.di_busy);
							Close();
							return;
						}
						break;
					}
					}
				}
			}
			
			_parseDirectInput();
		}
		else if (tape.ActualSource)
		{
			if (!_read())
				break;

			if (m_receivedLength == 0)
			{
				if (tape.ActualSource == 2)
					echo(I18N.ds_disconnect_controller, L"DualSense");
				else
					echo(I18N.ds_disconnect_controller, L"DualShock");
				break;
			}

			if (!_parse())
			{
				if (tape.ActualSource == 2)
					echo(I18N.ds_failed_parse, L"DualSense");
				else
					echo(I18N.ds_failed_parse, L"DualShock");
				break;
			}
		}
		
		if (tape.KeyboardActive || tape.KeyboardActivetmp)
			_parseKeyboard();
		
		if (tape.MouseActive || tape.MouseActivetmp)
			_parseMouse();

		//Determine if the state is changing
		if (memcpy(m_receivedLast, tape.ReceivedData, sizeof(tape.ReceivedData)) != 0)
		{
			if (m_bBluetooth && tape.ActualSource < 3)
			{
				if (_btcrc())
				{
					updateflag = true;
					if (m_crcerrorcount > 0)
						echo(I18N.ds_bt_crc, m_crcerrorcount);
					m_crcerrorcount = 0;
				}
				else
				{
					m_crcerrorcount++;
					if (m_crcerrorcount % 500 == 0)
						echo(I18N.ds_bt_crc, m_crcerrorcount);
				}
			}
			else
				updateflag = true;
		}
		
		if (tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] || tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] || tape.ReceivedData[SrceOffsetsID::Offset_DPAD])
			tape.lastButton = std::chrono::system_clock::now();
		if ((tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] & 0x3FFF) || (tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] & 0x3FFF) || (tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] & 0x3FFF))
			tape.lastMove = std::chrono::system_clock::now();

		//Callback
		if (m_callback)
			m_callback(updateflag, m_callbackdata);
	}

	if (tape.ActualSource)
		Close();
}

void Source::Clear()
{
	memset(&tape.ReceivedData, 0, sizeof(tape.ReceivedData));
	memset(&m_receivedLast, 0, sizeof(m_receivedLast));
	memset(&m_receivedTouch, 0, sizeof(m_receivedTouch));
}

//Send loop to DS4
void Source::OutputLoop()
{
	while (!m_threadShutdown)
	{
		if (tape.ActualSource < 3)
		{
			while (m_write_count != m_write_count2)
			{
				m_write_count2 = m_write_count;
				if (!_prewrite())
					goto EndOutputLoop;
			}
			std::unique_lock<std::mutex> lk(m_mutex);
			m_write_cv.wait(lk);
		}
	}

EndOutputLoop:
	Close();
}

void Source::SetLED(byte R, byte G, byte B)
{
	m_Red = R;
	m_Green = G;
	m_Blue = B;
}

void Source::SetOrangeLED(byte val)
{
	static bool terminating = false;
	if (terminating)
		return;

	if (val == 0xFF)
	{
		terminating = true;
		m_Orange = 0;
		Write();
	}
	else
	{
		static int lastval = 0;
		if (val != lastval)
		{
			if ((val >= 0 && val < 3) && (m_Orange != val))
			{
				if ((val == 0) && (tape.BatteryLevel < 11))
				{
					if (m_Orange != 2)
					{
						m_Orange = 2;
						Write();
					}
				}
				else
				{
					if (m_Orange != val)
					{
						m_Orange = val;
						Write();
					}
				}
			}
			lastval = val;
		}
	}
}

void Source::SetWhiteLED(byte led)
{
	static bool terminating = false;
	if (terminating)
		return;

	if (led == 0xFF)
	{
		terminating = true;
		m_White = 0x00;
		Write();
	}
	else if (led != m_White)
	{
		m_White = led;
		Write();
	}
}

void Source::SetTriggers(int val)
{
	if (tape.PreferredSource != 2)
		return;

	if ((val >= 0 && val < 4) && (m_Triggers != val))
		m_Triggers = val;
}

//Send LED and Motor information
BOOL Source::_prewrite()
{
	if (dsHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	if (tape.ActualSource == 2)
	{
		m_OutputBuf[m_outputOffset] = 0x02;
		m_OutputBuf[m_outputOffset + 1] = 0x01 | 0x02 | 0x04 | 0x08;
													// 0x01 Set the main motors (also requires flag 0x02)
													// 0x02 Set the main motors (also requires flag 0x01)
													// 0x04 Set the right trigger motor
													// 0x08 Set the left trigger motor
													// 0x10 Enable modification of audio volume
													// 0x20 Enable internal speaker (even while headset is connected)
													// 0x40 Enable modification of microphone volume
													// 0x80 Enable internal mic (even while headset is connected)
		m_OutputBuf[m_outputOffset + 2] = 0x01 | 0x04 | 0x10;
													// 0x01 Toggling microphone LED, 0x02 Toggling Audio/Mic Mute
													// 0x04 Toggling LED strips on the sides of the Touchpad, 0x08 Turn off all LED lights
													// 0x10 Toggle player LED lights below Touchpad, 0x20 ???
													// 0x40 Adjust overall motor/effect power, 0x80 ???

		m_OutputBuf[m_outputOffset + 3] = m_Left;
		m_OutputBuf[m_outputOffset + 4] = m_Right;
//		m_OutputBuf[m_outputOffset + 5] = ;			// Internal speaker volume
//		m_OutputBuf[m_outputOffset + 6] = ;			// Internal microphone volume
//		m_OutputBuf[m_outputOffset + 7] = ;			// 0x01 Enable internal microphone,
													// 0x10 Disable attached headphones (must set 0x20 as well)
													// 0x20 Enable internal speaker
		m_OutputBuf[m_outputOffset + 8] = 0x00;
		m_OutputBuf[m_outputOffset + 9] = m_Orange;	// Mute button LED. 0x01 = Solid. 0x02 = Pulsating
		m_OutputBuf[m_outputOffset + 10] = 0x00;	// 0x10 microphone mute, 0x40 audio mute

		switch(m_Triggers)
		{
		case 0:
		{
			m_OutputBuf[m_outputOffset + 11] = 0x00;	// right trigger motor mode (0 = no resistance, 1 = continuous resistance, 2 = section resistance, 0x20 and 0x04 enable additional effects together with 1 and 2 (configuration yet unknown), 252 = likely a calibration program* / PS Remote Play defaults this to 5; bit 4 only disables the motor?)
			m_OutputBuf[m_outputOffset + 12] = 0x00;	// right trigger start of resistance section 0-255 (0 = released state; 0xb0 roughly matches trigger value 0xff); in mode 26 this field has something to do with motor re-extension after a press-release-cycle (0 = no re-extension)
			m_OutputBuf[m_outputOffset + 13] = 0x00;	// (mode1) amount of force exerted; 0-255
														// (mode2) end of resistance section (>= begin of resistance section is enforced); 0xff makes it behave like mode1
														// (supplemental mode 4+20) flag(s?) 0x02 = do not pause effect when fully pressed
			m_OutputBuf[m_outputOffset + 14] = 0x00;	// right trigger force exerted in range (mode2), 0-255
			m_OutputBuf[m_outputOffset + 15] = 0x00;	// strength of effect near release state (requires supplement modes 4 and 20)
			m_OutputBuf[m_outputOffset + 16] = 0x00;	// strength of effect near middle (requires supplement modes 4 and 20)
			m_OutputBuf[m_outputOffset + 17] = 0x00;	// strength of effect at pressed state (requires supplement modes 4 and 20)
			m_OutputBuf[m_outputOffset + 20] = 0x00;	// effect actuation frequency in Hz (requires supplement modes 4 and 20)

			m_OutputBuf[m_outputOffset + 22] = 0x00;	// left trigger motor mode (0 = no resistance, 1 = continuous resistance, 2 = section resistance, 0x20 and 0x04 enable additional effects together with 1 and 2 (configuration yet unknown), 252 = likely a calibration program* / PS Remote Play defaults this to 5; bit 4 only disables the motor?)
			m_OutputBuf[m_outputOffset + 23] = 0x00;	// left trigger start of resistance section 0-255 (0 = released state; 0xb0 roughly matches trigger value 0xff); in mode 26 this field has something to do with motor re-extension after a press-release-cycle (0 = no re-extension)
			m_OutputBuf[m_outputOffset + 24] = 0x00;	// (mode1) amount of force exerted; 0-255
														// (mode2) end of resistance section (>= begin of resistance section is enforced); 0xff makes it behave like mode1
														// (supplemental mode 4+20) flag(s?) 0x02 = do not pause effect when fully pressed
			m_OutputBuf[m_outputOffset + 25] = 0x00;	// left trigger: (mode2) amount of force exerted within range; 0-255
			m_OutputBuf[m_outputOffset + 26] = 0x00;	// strength of effect near release state (requires supplement modes 4 and 20)
			m_OutputBuf[m_outputOffset + 27] = 0x00;	// strength of effect near middle (requires supplement modes 4 and 20)
			m_OutputBuf[m_outputOffset + 28] = 0x00;	// strength of effect at pressed state (requires supplement modes 4 and 20)
			m_OutputBuf[m_outputOffset + 31] = 0x00;	// effect actuation frequency in Hz (requires supplement modes 4 and 20)
			break;
		}
		case 1 :
		{
			m_OutputBuf[m_outputOffset + 11] = 0x21;
			m_OutputBuf[m_outputOffset + 12] = 0x18;
			m_OutputBuf[m_outputOffset + 13] = 0x00;
			m_OutputBuf[m_outputOffset + 14] = 0x00;
			m_OutputBuf[m_outputOffset + 15] = 0x00;
			m_OutputBuf[m_outputOffset + 16] = 0x00;
			m_OutputBuf[m_outputOffset + 17] = 0x00;
			m_OutputBuf[m_outputOffset + 20] = 0x00;

			m_OutputBuf[m_outputOffset + 22] = 0x21;
			m_OutputBuf[m_outputOffset + 23] = 0x18;
			m_OutputBuf[m_outputOffset + 24] = 0x00;
			m_OutputBuf[m_outputOffset + 25] = 0x00;
			m_OutputBuf[m_outputOffset + 26] = 0x00;
			m_OutputBuf[m_outputOffset + 27] = 0x00;
			m_OutputBuf[m_outputOffset + 28] = 0x00;
			m_OutputBuf[m_outputOffset + 31] = 0x00;
			break;
		}
		case 2:
		{
			m_OutputBuf[m_outputOffset + 11] = 0x02;
			m_OutputBuf[m_outputOffset + 12] = 0x88;
			m_OutputBuf[m_outputOffset + 13] = 0xBB;
			m_OutputBuf[m_outputOffset + 14] = 0xFF;
			m_OutputBuf[m_outputOffset + 15] = 0x00;
			m_OutputBuf[m_outputOffset + 16] = 0x00;
			m_OutputBuf[m_outputOffset + 17] = 0x00;
			m_OutputBuf[m_outputOffset + 20] = 0x00;

			m_OutputBuf[m_outputOffset + 22] = 0x02;
			m_OutputBuf[m_outputOffset + 23] = 0x88;
			m_OutputBuf[m_outputOffset + 24] = 0xBB;
			m_OutputBuf[m_outputOffset + 25] = 0xFF;
			m_OutputBuf[m_outputOffset + 26] = 0x00;
			m_OutputBuf[m_outputOffset + 27] = 0x00;
			m_OutputBuf[m_outputOffset + 28] = 0x00;
			m_OutputBuf[m_outputOffset + 31] = 0x00;
			break;
		}
		case 3:
		{
			m_OutputBuf[m_outputOffset + 11] = 0x21;
			m_OutputBuf[m_outputOffset + 12] = 0x88;
			m_OutputBuf[m_outputOffset + 13] = 0xBB;
			m_OutputBuf[m_outputOffset + 14] = 0xFF;
			m_OutputBuf[m_outputOffset + 15] = 0xFF;	//First blockade
			m_OutputBuf[m_outputOffset + 16] = 0xFF;	//Ending resistance
			m_OutputBuf[m_outputOffset + 17] = 0xFF;	//Middle resistamce
			m_OutputBuf[m_outputOffset + 20] = 0xFF;	//Ending Intensity (Frequency)

			m_OutputBuf[m_outputOffset + 22] = 0x21;
			m_OutputBuf[m_outputOffset + 23] = 0x88;
			m_OutputBuf[m_outputOffset + 24] = 0xBB;
			m_OutputBuf[m_outputOffset + 25] = 0xFF;
			m_OutputBuf[m_outputOffset + 26] = 0xFF;
			m_OutputBuf[m_outputOffset + 27] = 0xFF;
			m_OutputBuf[m_outputOffset + 28] = 0xFF;
			m_OutputBuf[m_outputOffset + 31] = 0xFF;
			break;
		}
		}

//		m_OutputBuf[m_outputOffset + 37] = ;		// Volume of internal speaker (0-7, Default 4)
		m_OutputBuf[m_outputOffset + 38] = 0x00;
		m_OutputBuf[m_outputOffset + 39] = 0x01;	// 0x01 Enabled LED brightness (value in index 42)
													// 0x02 Uninterruptable blue LED pulse (action in index 41)
		m_OutputBuf[m_outputOffset + 42] = 0x02;	// 0x00 High Brightness, 0x01 Medium Brightness, 0x02 Low Brightness
		m_OutputBuf[m_outputOffset + 43] = 0x02;
		m_OutputBuf[m_outputOffset + 44] = m_White;	// Player LED lights below Touchpad.
													// Bitmask 0x00-0x1F from left to right with 0x04 being the center LED.
													// Bit 0x20 sets the brightness immediately with no fade in
		m_OutputBuf[m_outputOffset + 45] = m_Red;
		m_OutputBuf[m_outputOffset + 46] = m_Green;
		m_OutputBuf[m_outputOffset + 47] = m_Blue;
	}
	else
	{
		m_OutputBuf[m_outputOffset] = m_Left;
		m_OutputBuf[m_outputOffset + 1] = m_Right;
		m_OutputBuf[m_outputOffset + 2] = m_Red;
		m_OutputBuf[m_outputOffset + 3] = m_Green;
		m_OutputBuf[m_outputOffset + 4] = m_Blue;
	}

	return _write();
}

BOOL Source::_write()
{
	if (m_bBluetooth)
	{
		if (tape.ActualSource == 2)
		{
			unsigned int crc = crc32_16bytes(m_OutputBuf, 74, 0xEADA2D49);
			m_OutputBuf[74] = (crc);
			m_OutputBuf[75] = (crc >> 8);
			m_OutputBuf[76] = (crc >> 16);
			m_OutputBuf[77] = (crc >> 24);
		}
		else
		{
			if (HidD_SetOutputReport(dsHandle, m_OutputBuf, 78))//78 fixed m_outputLen
				return TRUE;
			if (!m_threadShutdown && dsHandle != INVALID_HANDLE_VALUE)
				echo(I18N.ds_failed_send_cmd, L"DS(BT)", GetLastError());
			return FALSE;
		}
	}
	ResetEvent(m_oWrite.hEvent);

	DWORD n;
	if (WriteFile(dsHandle, m_OutputBuf, (m_bBluetooth) ? 78 : m_outputLen, &n, &m_oWrite))
		return TRUE;
	else if (GetLastError() == ERROR_IO_PENDING)
	{
		if (WaitForSingleObject(m_oWrite.hEvent, 5000) != WAIT_OBJECT_0)
		{
			if (dsHandle != INVALID_HANDLE_VALUE)
			{
				CancelIo(dsHandle);
				WaitForSingleObject(m_oWrite.hEvent, INFINITE);
			}
		}
		else
		{
			if (GetOverlappedResult(dsHandle, &m_oWrite, &n, false))
				return TRUE;
		}
	}

	DWORD errorcode = GetLastError();
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	if (!m_threadShutdown && dsHandle != INVALID_HANDLE_VALUE)
		echo(I18N.ds_failed_send_cmd, (m_bBluetooth) ? L"DS(BT)" : L"DS(USB)", errorcode);

	echo(L"%d = %s", errorcode, (LPTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);

	return FALSE;
}

//Receive
BOOL Source::_read()
{
	if (dsHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD n;
	ResetEvent(m_oRead.hEvent);

	if (ReadFile(dsHandle, m_InputBuf, m_inputLen, &n, &m_oRead))
	{
		m_receivedLength = n;
		return TRUE;
	}

	if (GetLastError() == ERROR_IO_PENDING)
	{
		if (WaitForSingleObject(m_oRead.hEvent, 5000) != WAIT_OBJECT_0)
		{
			if (dsHandle != INVALID_HANDLE_VALUE)
			{
				CancelIo(dsHandle);
				WaitForSingleObject(m_oRead.hEvent, INFINITE);
			}
		}
		else
		{
			if (GetOverlappedResult(dsHandle, &m_oRead, &n, false))
			{
				m_receivedLength = n;
				return TRUE;
			}
		}
	}

	DWORD errorcode = GetLastError();

	switch (errorcode)
	{
	case ERROR_DEVICE_NOT_CONNECTED:
	{
		if (!m_threadShutdown && dsHandle != INVALID_HANDLE_VALUE)
		{
			if (firstflaglost)
			{
				firstflag = true;
				firstflaglost = false;
				echo(I18N.ds_wait);
			}
		}
		break;
	}
	default:
	{
		if (!m_threadShutdown && dsHandle != INVALID_HANDLE_VALUE)
			echo(I18N.ds_failed_recv, L"DS", errorcode);
		break;
	}
	}

	return FALSE;
}

//CRC check of received data
BOOL Source::_btcrc()
{
	unsigned int crc = crc32_16bytes(m_InputBuf, 74, 0x73D37CF3);
	unsigned int src = *(unsigned int*)&m_InputBuf[74];

	return crc == src;
}

//Analysis of received data
BOOL Source::_parse()
{
/*
							DualShock		DualSense		Bitwise
	LX						0				0				0b11111111
	LY						1				1				0b11111111
	RX						2				2				0b11111111
	RY						3				3				0b11111111
	DPad					4				7				0b00001111	neutral: 0x8, N: 0x0, NE: 0x1, E: 0x2, SE: 0x3, S: 0x4, SW: 0x5, W: 0x6, NW: 0x7
	Square					4				7				0b00010000
	Cross					4				7				0b00100000
	Circle					4				7				0b01000000
	Triangle				4				7				0b10000000
	L1						5				8				0b00000001
	R1						5				8				0b00000010
	L2						5				8				0b00000100
	R2						5				8				0b00001000
	Share					5				8				0b00010000
	Option					5				8				0b00100000
	L3						5				8				0b01000000
	R3						5				8				0b10000000
	PS						6				9				0b00000001
	TouchPadClick			6				9				0b00000010
	Counter					6				6				0b11111100	0b11111111 This is incremented for each report.
	Mute					 				9				0b00000100
	Counter									9				0b11111000
	LeftTrigger				7				4				0b11111111
	RightTrigger			8				5				0b11111111
	Timestamp				9+10 			11-14						in 5.33ms
	Unused					11				10
	Acceleration Pitch		12				15
	Acceleration Yaw		14				17
	Acceleration Roll		16				19
	Pitch					13				16							Angular velocity [millimeter rad / s]
	Yaw						15				18
	Roll					17				20
	Acceleration Sideward	18				21
	Acceleration Toward		20				23
	Acceleration Level		22				25
	Sideward				19				22							Gyrocompass
	Toward					21				24
	Level					23				26
	Unused/Unknown			24-28			27-28
	Battery level			29				52				0b00001111
	Battery Full							52							0b00010000	???
	USB						29				52				0b00010000	0b00100000
	MIC						29				53				0b00100000	0b00000001
	MicroPhone				29				53				0b01000000	0b00000010
	Pairing									53							0b00000100
	Unused									53							0b00001000
	Optional peripheral state				53							0b11110000
	Unused					29								0b10000000
	Unused					30-31
											29+30						Timestamp (unit is probably 5.33ms)

	Packets					32 											Number of trackpad packets 0x00 to 0x04
	>Packet1 Counter		33 				31				0b11111111
	Finger1 id				34				32				0b01111111
	Finger1 active			34				32				0b10000000
	Finger1 coordinates		35-37			33-35			0b11111111	0b11111111 0b11111111
	Finger2 id				38 				36				0b01111111
	Finger2 active			38				36				0b10000000
	Finger2 coordinates		39-41			37-39			0b11111111	0b11111111 0b11111111
	>Packet2				42-50
	>Packet3				51-59
	>Packet4				60-68

	Unknown					69-70
	CRC-32					71-74										4 bytes at start, 4=ReportID (0x01) HID Report ID for reporting
*/

	byte* buffer = m_InputBuf,
		* bufferEnd = m_InputBuf + m_receivedLength;

	if (m_bBluetooth)
	{
		if (tape.ActualSource == 2)
		{
			if (m_InputBuf[0] != 0x31)
				return TRUE;
			buffer += 2;
		}
		else
		{
			if (m_InputBuf[0] != 0x11)
				return TRUE;
			buffer += 3;
		}
	}
	else
	{
		if (m_InputBuf[0] != 0x01)
			return TRUE;
		buffer += 1;
	}

	if (m_receivedLength < 42)
	{
		//echo(I18N.ds_bt_size);
		return FALSE;
	}

	unsigned char dpad = 0;
	//Sisaxis offsets
	byte _Roll		= 20;	// Left		Right		Velocity
	byte _Yaw		= 18;	// Anti		Clock
	byte _Pitch		= 16;	// Rear		Fore
	byte _Sideward	= 22;	// West		East		Gyrocompass
	byte _Toward	= 24;	// Forward	Backward
	byte _Level		= 26;	// South	North

	if (tape.ActualSource == 2)
	{
		//Button state
		dpad = buffer[7] & 0xF;
		tape.ReceivedData[SrceOffsetsID::Offset_L2] = buffer[4] * 257;
		tape.ReceivedData[SrceOffsetsID::Offset_R2] = buffer[5] * 257;
		tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= ((buffer[7] & 0b11110000) >> 4);
		tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (buffer[8] << 4);
		tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= ((buffer[9] & 0b111) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_DIVERSE] |= ((buffer[52] & 0b00100000) >> 5);
		tape.ReceivedData[SrceOffsetsID::Offset_DIVERSE] |= ((buffer[53] & 0b00000011) << 1);
		tape.ReceivedData[SrceOffsetsID::Offset_DIVERSE] |= (1 << 8);

		//Battery level
		tape.BatteryLevel = (buffer[52] & 0x0F) * 10;
		tape.BatteryCharge = (tape.BatteryLevel == 100) ? false : ((buffer[52] & 0x20) ? true : false);

		//Touch information
		memcpy(m_receivedTouch, buffer + 32, 8);
	}
	else if(tape.ActualSource == 1)
	{
		//Sisaxis offsets
		_Roll		= 17;
		_Yaw		= 15;
		_Pitch		= 13;
		_Sideward	= 19;
		_Toward		= 21;
		_Level		= 23;

		//Button state
		dpad = buffer[4] & 0xF;
		tape.ReceivedData[SrceOffsetsID::Offset_L2] = buffer[7] * 257;
		tape.ReceivedData[SrceOffsetsID::Offset_R2] = buffer[8] * 257;
		tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= ((buffer[4] & 0b11110000) >> 4);
		tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (buffer[5] << 4);
		tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= ((buffer[6] & 0b11) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_DIVERSE] |= ((buffer[29] & 0b01110000) >> 4);
		tape.ReceivedData[SrceOffsetsID::Offset_DIVERSE] |= (1 << 7);

		//Battery level
		bool BatteryChargetmp = (buffer[29] & 0x10) ? true : false;
		tape.BatteryLevel = min(10, ((buffer[29] & 0x0F) + ((tape.BatteryCharge) ? 0 : 1))) * 10;
		tape.BatteryCharge = (tape.BatteryLevel == 100) ? false : BatteryChargetmp;

		//Touch information
		memcpy(m_receivedTouch, buffer + 34, 8);
	}
	else
	{
		tape.BatteryCharge = false;
		tape.BatteryLevel = 100;
	}

	//Button state
	tape.ReceivedData[SrceOffsetsID::Offset_LX] = buffer[0] * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_LY] = buffer[1] * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_RX] = buffer[2] * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_RY] = buffer[3] * 257;

	tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= ((dpad == 5 || dpad == 6 || dpad == 7) ? 1 : 0);
	tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 7 || dpad == 0 || dpad == 1) ? 1 : 0) << 1);
	tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 1 || dpad == 2 || dpad == 3) ? 1 : 0) << 2);
	tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 3 || dpad == 4 || dpad == 5) ? 1 : 0) << 3);

	tape.ReceivedData[SrceOffsetsID::Offset_DIVERSE] |= (isBT() << 3);
	tape.ReceivedData[SrceOffsetsID::Offset_DIVERSE] |= (((TouchActive(0) ^ TouchActive(1)) ? 1 : 0) << 4);
	tape.ReceivedData[SrceOffsetsID::Offset_DIVERSE] |= (((TouchActive(0) && TouchActive(1)) ? 1 : 0) << 5);
	tape.ReceivedData[SrceOffsetsID::Offset_DIVERSE] |= (1 << 6);

	//Sisaxis
	//0 back, 1 leaned, 2 sat, 3 leaning
	tape.Zone = (buffer[_Toward] > 127) ? ((buffer[_Level] < 128) ? 0 : 1) : ((buffer[_Level] > 127) ? 2 : 3);
	if (tape.zoneChange)
	{
		tape.zoneChange = false;
		//0 back, 1 leaned, 2 leaned + sat, 3 sat, 4 leaning
		tape.Stance = (buffer[_Toward] > 127) ? ((buffer[_Level] < 128) ? 0 : ((buffer[_Level] < 226) ? 2 : 1)) : ((buffer[_Level] > 127) ? ((buffer[_Level] < 226) ? 2 : 3) : 4);
	}

	//Roll & Roll Trigger
	float RollResult = (buffer[_Roll] < 128) ? (126 - 2.25 * max(0, min(72, buffer[_Roll]) - 16)) : min(255, (128 + 2.25 * (max(0, min(73, 255 - buffer[_Roll]) - 16))));
	tape.ReceivedData[SrceOffsetsID::Offset_ROLL] = RollResult * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_ROLL_TRIGGER] = (tape.ReceivedData[SrceOffsetsID::Offset_ROLL] > 32267 && tape.ReceivedData[SrceOffsetsID::Offset_ROLL] < 33268) ? 0 : ((tape.ReceivedData[SrceOffsetsID::Offset_ROLL] < 32768) ? ((32767 - tape.ReceivedData[SrceOffsetsID::Offset_ROLL]) * 2) : (((tape.ReceivedData[SrceOffsetsID::Offset_ROLL] - 32767) * 2) - 1));

	if (RollResult <= 127.5)		//Roll Left
	{
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult > 124) ? 1 : 0) << 14);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult < 125) ? 1 : 0) << 0);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult < 105) ? 1 : 0) << 1);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult < 85) ? 1 : 0) << 2);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult < 57) ? 1 : 0) << 3);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult < 26) ? 1 : 0) << 4);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult < 2) ? 1 : 0) << 5);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult == 0) ? 1 : 0) << 6);
	}
	else							//Roll Right
	{
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (1 << 15);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult < 131) ? 1 : 0) << 14);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult > 130) ? 1 : 0) << 7);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult > 150) ? 1 : 0) << 8);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult > 170) ? 1 : 0) << 9);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult > 198) ? 1 : 0) << 10);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult > 229) ? 1 : 0) << 11);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult > 253) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_ROLL_BUTTONS] |= (((RollResult == 255) ? 1 : 0) << 13);
	}

	//Yaw & Yaw Trigger
	float YawResult = (buffer[_Yaw] < 128) ? (126 - 1.96875 * max(0, min(80, buffer[_Yaw]) - 16)) : min(255, (128 + 1.96875 * (max(0, min(81, 255 - buffer[_Yaw]) - 16))));
	tape.ReceivedData[SrceOffsetsID::Offset_YAW] = YawResult * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_YAW_TRIGGER] = (tape.ReceivedData[SrceOffsetsID::Offset_YAW] > 32267 && tape.ReceivedData[SrceOffsetsID::Offset_YAW] < 33268) ? 0 : ((tape.ReceivedData[SrceOffsetsID::Offset_YAW] < 32768) ? ((32767 - tape.ReceivedData[SrceOffsetsID::Offset_YAW]) * 2) : (((tape.ReceivedData[SrceOffsetsID::Offset_YAW] - 32767) * 2) - 1));

	if (YawResult <= 127.5)			//Yaw Anti
	{
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult > 124) ? 1 : 0) << 14);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult < 125) ? 1 : 0) << 0);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult < 105) ? 1 : 0) << 1);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult < 93) ? 1 : 0) << 2);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult < 59) ? 1 : 0) << 3);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult < 36) ? 1 : 0) << 4);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult < 7) ? 1 : 0) << 5);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult == 0) ? 1 : 0) << 6);
	}
	else							//Yaw Clock
	{
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (1 << 15);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult < 131) ? 1 : 0) << 14);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult > 130) ? 1 : 0) << 7);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult > 150) ? 1 : 0) << 8);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult > 162) ? 1 : 0) << 9);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult > 196) ? 1 : 0) << 10);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult > 219) ? 1 : 0) << 11);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult > 248) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_YAW_BUTTONS] |= (((YawResult == 250) ? 1 : 0) << 13);
	}

	//Pitch & Pitch Trigger
	float PitchResult = (buffer[_Pitch] < 128) ? (126 - 3 * max(0, min(58, buffer[_Pitch]) - 16)) : min(255, (128 + 2.1 * (max(0, min(77, 255 - buffer[_Pitch]) - 16))));
	tape.ReceivedData[SrceOffsetsID::Offset_PITCH] = PitchResult * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_PITCH_TRIGGER] = (tape.ReceivedData[SrceOffsetsID::Offset_PITCH] > 32267 && tape.ReceivedData[SrceOffsetsID::Offset_PITCH] < 33268) ? 0 : ((tape.ReceivedData[SrceOffsetsID::Offset_PITCH] < 32768) ? ((32767 - tape.ReceivedData[SrceOffsetsID::Offset_PITCH]) * 2) : (((tape.ReceivedData[SrceOffsetsID::Offset_PITCH] - 32767) * 2) - 1));

	if (PitchResult <= 127.5)		//Pitch Rear
	{
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult > 124) ? 1 : 0) << 14);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult < 125) ? 1 : 0) << 0);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult < 105) ? 1 : 0) << 1);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult < 93) ? 1 : 0) << 2);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult < 53) ? 1 : 0) << 3);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult < 27) ? 1 : 0) << 4);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult < 2) ? 1 : 0) << 5);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult == 0) ? 1 : 0) << 6);
	}
	else							//Pitch Fore
	{
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (1 << 15);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult < 131) ? 1 : 0) << 14);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult > 130) ? 1 : 0) << 7);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult > 150) ? 1 : 0) << 8);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult > 162) ? 1 : 0) << 9);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult > 202) ? 1 : 0) << 10);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult > 228) ? 1 : 0) << 11);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult > 253) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_PITCH_BUTTONS] |= (((PitchResult == 250) ? 1 : 0) << 13);
	}

	//Toward & Toward Trigger
	static byte Towards[56] = { 0 };
	for (int i = 0; i < 55; i++)
		Towards[i] = Towards[i + 1];
	Towards[55] = (buffer[_Toward] < 128) ? (128 + min(127, buffer[_Toward] * 4)) : (127 - min(127, (255 - buffer[_Toward]) * 4));
	float TowardResult = 0;
	for (int i = 0; i < 56; i++)
		TowardResult += Towards[i];
	TowardResult = TowardResult / 56;
	tape.ReceivedData[SrceOffsetsID::Offset_TOWARD] = (TowardResult >= 125 && TowardResult <= 130) ? 32767 : TowardResult * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_TRIGGER] = ((tape.ReceivedData[SrceOffsetsID::Offset_TOWARD] < 32768) ? ((32767 - tape.ReceivedData[SrceOffsetsID::Offset_TOWARD]) * 2) : (((tape.ReceivedData[SrceOffsetsID::Offset_TOWARD] - 32767) * 2) - 1));
	
	if (TowardResult <= 127.5)		//Backward
	{
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult > 124) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult < 125) ? 1 : 0) << 0);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult < 105) ? 1 : 0) << 1);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult < 85) ? 1 : 0) << 2);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult < 65) ? 1 : 0) << 3);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult < 35) ? 1 : 0) << 4);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult < 10) ? 1 : 0) << 5);
	}
	else							//Forward
	{
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 13);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult < 131) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult > 130) ? 1 : 0) << 6);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult > 150) ? 1 : 0) << 7);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult > 170) ? 1 : 0) << 8);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult > 190) ? 1 : 0) << 9);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult > 220) ? 1 : 0) << 10);
		tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (((TowardResult > 245) ? 1 : 0) << 11);
	}

	//Level & Level Trigger
	static byte Levels[56] = { 0 };
	for (int i = 0; i < 55; i++)
		Levels[i] = Levels[i + 1];
	Levels[55] = (buffer[_Level] < 128) ? (127 - min(127, buffer[_Level] * 4)) : (128 + min(127, (255 - buffer[_Level]) * 4));
	float LevelResult = 0;
	for (int i = 0; i < 56; i++)
		LevelResult += Levels[i];
	LevelResult = LevelResult / 56;
	tape.ReceivedData[SrceOffsetsID::Offset_LEVEL] = (LevelResult >= 125 && LevelResult <= 130) ? 32767 : LevelResult * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_TRIGGER] = ((tape.ReceivedData[SrceOffsetsID::Offset_LEVEL] < 32768) ? ((32767 - tape.ReceivedData[SrceOffsetsID::Offset_LEVEL]) * 2) : (((tape.ReceivedData[SrceOffsetsID::Offset_LEVEL] - 32767) * 2) - 1));

	if (LevelResult <= 127.5)		//South
	{
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult > 124) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult < 125) ? 1 : 0) << 0);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult < 105) ? 1 : 0) << 1);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult < 85) ? 1 : 0) << 2);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult < 65) ? 1 : 0) << 3);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult < 35) ? 1 : 0) << 4);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult < 10) ? 1 : 0) << 5);
	}
	else							//North
	{
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 13);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult < 131) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult > 130) ? 1 : 0) << 6);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult > 150) ? 1 : 0) << 7);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult > 170) ? 1 : 0) << 8);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult > 190) ? 1 : 0) << 9);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult > 220) ? 1 : 0) << 10);
		tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (((LevelResult > 245) ? 1 : 0) << 11);
	}

	//Sideward & Sideward Trigger
	static byte Sidewards[56] = { 0 };
	for (int i = 0; i < 55; i++)
		Sidewards[i] = Sidewards[i + 1];
	Sidewards[55] = (buffer[_Sideward] < 128) ? (127 - min(127, buffer[_Sideward] * 4)) : (128 + min(127, (255 - buffer[_Sideward]) * 4));
	float SidewardResult = 0;
	for (int i = 0; i < 56; i++)
		SidewardResult += Sidewards[i];
	SidewardResult = SidewardResult / 56;
	tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD] = SidewardResult * 257;
	unsigned short SidewardResultDeadZone = (SidewardResult >= 125 && SidewardResult <= 130) ? 32767 : SidewardResult * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_TRIGGER] = ((SidewardResultDeadZone < 32768) ? ((32767 - SidewardResultDeadZone) * 2) : (((SidewardResultDeadZone - 32767) * 2) - 1));

	if (SidewardResult <= 127.5)	//West
	{
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((TowardResult < 128) ? 1 : 0) << 13);
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult > 124) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult < 125) ? 1 : 0) << ((TowardResult < 128) ? 6 : 0));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult < 105) ? 1 : 0) << ((TowardResult < 128) ? 7 : 1));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult < 85) ? 1 : 0) << ((TowardResult < 128) ? 8 : 2));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult < 65) ? 1 : 0) << ((TowardResult < 128) ? 9 : 3));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult < 35) ? 1 : 0) << ((TowardResult < 128) ? 10 : 4));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult < 10) ? 1 : 0) << ((TowardResult < 128) ? 11 : 5));
	}
	else							//East
	{
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((TowardResult < 128) ? 0 : 1) << 13);
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult < 131) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult > 130) ? 1 : 0) << ((TowardResult < 128) ? 0 : 6));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult > 150) ? 1 : 0) << ((TowardResult < 128) ? 1 : 7));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult > 170) ? 1 : 0) << ((TowardResult < 128) ? 2 : 8));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult > 190) ? 1 : 0) << ((TowardResult < 128) ? 3 : 9));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult > 220) ? 1 : 0) << ((TowardResult < 128) ? 4 : 10));
		tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (((SidewardResult > 245) ? 1 : 0) << ((TowardResult < 128) ? 5 : 11));
	}

	//Wheel & Quarter & Gears
	SidewardResult = SidewardResult * 257;
	switch (tape.Stance)
	{
	case 0:	//back
	{
		if (TowardResult <= 127.5 && LevelResult <= 127.5)
		{
			if (TowardResult > 91) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14);		//Rear
			else if (TowardResult > 73) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 15); //Gear1
			else if (TowardResult > 55) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 14);	//Gear2
			else if (TowardResult > 36) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 15);	//Gear3
			else if (TowardResult > 18) tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 14);	//Gear4
			else tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);							//Gear5
			TowardResult = TowardResult * 257;
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = max(0, min(65535, (((1 + ((32767.5 - TowardResult)) / 63993) * (65535 - SidewardResult - 32767.5)) + 32767.5)));
			tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = (32767.5 - TowardResult) * 2;
		}
		else
		{
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = m_receivedLast[SrceOffsetsID::Offset_WHEEL];
			if (LevelResult > 127.5)
			{
				tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = 65535;
				tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);	//Rear
			}
			else
				tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14); //Gear5
		}
		break;
	}
	case 1:	//leaned
	{
		if (TowardResult <= 127.5 && LevelResult >= 127.5)
		{
			if (TowardResult < 36) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14);		//Rear
			else if (TowardResult < 55) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 15); //Gear1
			else if (TowardResult < 73) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 14);	//Gear2
			else if (TowardResult < 91) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 15);	//Gear3
			else if (TowardResult < 109) tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 14);	//Gear4
			else tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);							//Gear5
			TowardResult = TowardResult * 257;
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = max(0, min(65535, (((1 + ((32767.5 - TowardResult)) / 63993) * (SidewardResult - 32767.5)) + 32767.5 )));
			tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = TowardResult * 2;
		}
		else
		{
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = m_receivedLast[SrceOffsetsID::Offset_WHEEL];
			if (TowardResult > 127.5)
			{
				tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = 65535;
				tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);	//Rear
			}
			else
				tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14); //Gear5
		}
		break;
	}
	case 2:	//leaned + sat
	{
		if (LevelResult >= 127.5)
		{
			if (TowardResult < 73) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14);		//Rear
			else if (TowardResult < 109) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 15);//Gear1
			else if (TowardResult < 146) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 14);	//Gear2
			else if (TowardResult < 182) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 15);	//Gear3
			else if (TowardResult < 219) tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 14);	//Gear4
			else tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);							//Gear5
			TowardResult = TowardResult * 257;
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = max(0, min(65535, (((1 + ((TowardResult <= 32767.5) ? (TowardResult - 32767.5) : (32767.5 - TowardResult)) / 63993) * (SidewardResult - 32767.5)) + 32767.5)));
			tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = TowardResult;
		}
		else
		{
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = (buffer[_Sideward] < 128) ? 0 : 65535;
			if (TowardResult > 127.5)
			{
				tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = 65535;
				tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);	//Rear
			}
			else
				tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14); //Gear5
		}
		break;
	}
	case 3:	//sat
	{
		if (TowardResult >= 127.5 && buffer[_Level] >= 127.5)
		{
			if (TowardResult < 164) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14);		//Rear
			else if (TowardResult < 182) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 15);//Gear1
			else if (TowardResult < 200) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 14);	//Gear2
			else if (TowardResult < 219) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 15);	//Gear3
			else if (TowardResult < 237) tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 14);	//Gear4
			else tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);							//Gear5
			TowardResult = TowardResult * 257;
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = max(0, min(65535, (((1 + ((TowardResult - 32767.5)) / 63993) * (SidewardResult - 32767.5)) + 32767.5)));
			tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = (TowardResult - 32767.5) * 2;
		}
		else
		{
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = m_receivedLast[SrceOffsetsID::Offset_WHEEL];
			if (TowardResult > 127.5)
			{
				tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = 65535;
				tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);	//Rear
			}
			else
				tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14); //Gear5
		}
		break;
	}
	case 4:	//leaning
	{
		if (TowardResult >= 127.5 && LevelResult <= 127.5)
		{
			if (TowardResult > 219) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14);		//Rear
			else if (TowardResult > 200) tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 15);//Gear1
			else if (TowardResult > 182) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 14);	//Gear2
			else if (TowardResult > 164) tape.ReceivedData[SrceOffsetsID::Offset_TOWARD_BUTTONS] |= (1 << 15);	//Gear3
			else if (TowardResult > 146) tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 14);	//Gear4
			else tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);							//Gear5
			TowardResult = TowardResult * 257;
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = max(0, min(65535, (((1 + ((TowardResult - 32767.5)) / 63993) * (SidewardResult - 32767.5)) + 32767.5)));
			tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = (65535 - TowardResult) * 2;
		}
		else
		{
			tape.ReceivedData[SrceOffsetsID::Offset_WHEEL] = m_receivedLast[SrceOffsetsID::Offset_WHEEL];
			if (LevelResult < 127.5)
			{
				tape.ReceivedData[SrceOffsetsID::Offset_QUARTER] = 65535;
				tape.ReceivedData[SrceOffsetsID::Offset_LEVEL_BUTTONS] |= (1 << 15);	//Rear
			}
			else
				tape.ReceivedData[SrceOffsetsID::Offset_SIDEWARD_BUTTONS] |= (1 << 14); //Gear5
		}
		break;
	}
	}

	return TRUE;
}

//Analysis of DirectInput received data
BOOL Source::_parseDirectInput()
{
	DIJOYSTATE2 JoyState1;
	if (FAILED(m_diJoystick1->GetDeviceState(sizeof(DIJOYSTATE2), &JoyState1)))
	{
		if (firstflag)
		{
			echo(I18N.di_wait);
			firstflag = false;
		}
	}
	DIJOYSTATE2 JoyState2 = JoyState1;
	if (m_diTween)
		if (FAILED(m_diJoystick2->GetDeviceState(sizeof(DIJOYSTATE2), &JoyState2)))
		{
			if (firstflag)
			{
				echo(I18N.di_wait);
				firstflag = false;
			}
		}

	switch (tape.diDispatch[Dispatch_LX])
	{
	case DIAxisID_1_X: { if (m_diXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState1.lX; } break; }
	case DIAxisID_1_Y: { if (m_diYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState1.lY; } break; }
	case DIAxisID_1_Z: { if (m_diZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState1.lZ; } break; }
	case DIAxisID_1_RX: { if (m_diRXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState1.lRx; } break; }
	case DIAxisID_1_RY: { if (m_diRYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState1.lRy; } break; }
	case DIAxisID_1_RZ: { if (m_diRZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState1.lRz; } break; }
	case DIAxisID_1_SL0: { if (m_diSliderCount1) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState1.rglSlider[0]; } break; }
	case DIAxisID_1_SL1: { if (m_diSliderCount1 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState1.rglSlider[1]; } break; }
	case DIAxisID_2_X: { if (m_diXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState2.lX; } break; }
	case DIAxisID_2_Y: { if (m_diYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState2.lY; } break; }
	case DIAxisID_2_Z: { if (m_diZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState2.lZ; } break; }
	case DIAxisID_2_RX: { if (m_diRXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState2.lRx; } break; }
	case DIAxisID_2_RY: { if (m_diRYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState2.lRy; } break; }
	case DIAxisID_2_RZ: { if (m_diRZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState2.lRz; } break; }
	case DIAxisID_2_SL0: { if (m_diSliderCount2) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState2.rglSlider[0]; } break; }
	case DIAxisID_2_SL1: { if (m_diSliderCount2 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_LX] = JoyState2.rglSlider[1]; } break; }
	}

	switch (tape.diDispatch[Dispatch_LY])
	{
	case DIAxisID_1_X: { if (m_diXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState1.lX; } break; }
	case DIAxisID_1_Y: { if (m_diYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState1.lY; } break; }
	case DIAxisID_1_Z: { if (m_diZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState1.lZ; } break; }
	case DIAxisID_1_RX: { if (m_diRXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState1.lRx; } break; }
	case DIAxisID_1_RY: { if (m_diRYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState1.lRy; } break; }
	case DIAxisID_1_RZ: { if (m_diRZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState1.lRz; } break; }
	case DIAxisID_1_SL0: { if (m_diSliderCount1) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState1.rglSlider[0]; } break; }
	case DIAxisID_1_SL1: { if (m_diSliderCount1 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState1.rglSlider[1]; } break; }
	case DIAxisID_2_X: { if (m_diXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState2.lX; } break; }
	case DIAxisID_2_Y: { if (m_diYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState2.lY; } break; }
	case DIAxisID_2_Z: { if (m_diZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState2.lZ; } break; }
	case DIAxisID_2_RX: { if (m_diRXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState2.lRx; } break; }
	case DIAxisID_2_RY: { if (m_diRYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState2.lRy; } break; }
	case DIAxisID_2_RZ: { if (m_diRZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState2.lRz; } break; }
	case DIAxisID_2_SL0: { if (m_diSliderCount2) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState2.rglSlider[0]; } break; }
	case DIAxisID_2_SL1: { if (m_diSliderCount2 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_LY] = JoyState2.rglSlider[1]; } break; }
	}

	switch (tape.diDispatch[Dispatch_RX])
	{
	case DIAxisID_1_X: { if (m_diXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState1.lX; } break; }
	case DIAxisID_1_Y: { if (m_diYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState1.lY; } break; }
	case DIAxisID_1_Z: { if (m_diZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState1.lZ; } break; }
	case DIAxisID_1_RX: { if (m_diRXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState1.lRx; } break; }
	case DIAxisID_1_RY: { if (m_diRYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState1.lRy; } break; }
	case DIAxisID_1_RZ: { if (m_diRZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState1.lRz; } break; }
	case DIAxisID_1_SL0: { if (m_diSliderCount1) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState1.rglSlider[0]; } break; }
	case DIAxisID_1_SL1: { if (m_diSliderCount1 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState1.rglSlider[1]; } break; }
	case DIAxisID_2_X: { if (m_diXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState2.lX; } break; }
	case DIAxisID_2_Y: { if (m_diYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState2.lY; } break; }
	case DIAxisID_2_Z: { if (m_diZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState2.lZ; } break; }
	case DIAxisID_2_RX: { if (m_diRXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState2.lRx; } break; }
	case DIAxisID_2_RY: { if (m_diRYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState2.lRy; } break; }
	case DIAxisID_2_RZ: { if (m_diRZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState2.lRz; } break; }
	case DIAxisID_2_SL0: { if (m_diSliderCount2) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState2.rglSlider[0]; } break; }
	case DIAxisID_2_SL1: { if (m_diSliderCount2 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_RX] = JoyState2.rglSlider[1]; } break; }
	}

	switch (tape.diDispatch[Dispatch_RY])
	{
	case DIAxisID_1_X: { if (m_diXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState1.lX; } break; }
	case DIAxisID_1_Y: { if (m_diYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState1.lY; } break; }
	case DIAxisID_1_Z: { if (m_diZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState1.lZ; } break; }
	case DIAxisID_1_RX: { if (m_diRXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState1.lRx; } break; }
	case DIAxisID_1_RY: { if (m_diRYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState1.lRy; } break; }
	case DIAxisID_1_RZ: { if (m_diRZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState1.lRz; } break; }
	case DIAxisID_1_SL0: { if (m_diSliderCount1) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState1.rglSlider[0]; } break; }
	case DIAxisID_1_SL1: { if (m_diSliderCount1 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState1.rglSlider[1]; } break; }
	case DIAxisID_2_X: { if (m_diXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState2.lX; } break; }
	case DIAxisID_2_Y: { if (m_diYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState2.lY; } break; }
	case DIAxisID_2_Z: { if (m_diZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState2.lZ; } break; }
	case DIAxisID_2_RX: { if (m_diRXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState2.lRx; } break; }
	case DIAxisID_2_RY: { if (m_diRYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState2.lRy; } break; }
	case DIAxisID_2_RZ: { if (m_diRZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState2.lRz; } break; }
	case DIAxisID_2_SL0: { if (m_diSliderCount2) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState2.rglSlider[0]; } break; }
	case DIAxisID_2_SL1: { if (m_diSliderCount2 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_RY] = JoyState2.rglSlider[1]; } break; }
	}

	switch (tape.diDispatch[Dispatch_L2TR])
	{
	case DIAxisID_1_X: { if (m_diXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState1.lX; } break; }
	case DIAxisID_1_Y: { if (m_diYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState1.lY; } break; }
	case DIAxisID_1_Z: { if (m_diZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState1.lZ; } break; }
	case DIAxisID_1_RX: { if (m_diRXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState1.lRx; } break; }
	case DIAxisID_1_RY: { if (m_diRYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState1.lRy; } break; }
	case DIAxisID_1_RZ: { if (m_diRZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState1.lRz; } break; }
	case DIAxisID_1_SL0: { if (m_diSliderCount1) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState1.rglSlider[0]; } break; }
	case DIAxisID_1_SL1: { if (m_diSliderCount1 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState1.rglSlider[1]; } break; }
	case DIAxisID_2_X: { if (m_diXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState2.lX; } break; }
	case DIAxisID_2_Y: { if (m_diYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState2.lY; } break; }
	case DIAxisID_2_Z: { if (m_diZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState2.lZ; } break; }
	case DIAxisID_2_RX: { if (m_diRXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState2.lRx; } break; }
	case DIAxisID_2_RY: { if (m_diRYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState2.lRy; } break; }
	case DIAxisID_2_RZ: { if (m_diRZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState2.lRz; } break; }
	case DIAxisID_2_SL0: { if (m_diSliderCount2) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState2.rglSlider[0]; } break; }
	case DIAxisID_2_SL1: { if (m_diSliderCount2 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_L2] = JoyState2.rglSlider[1]; } break; }
	}

	switch (tape.diDispatch[Dispatch_R2TR])
	{
	case DIAxisID_1_X: { if (m_diXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState1.lX; } break; }
	case DIAxisID_1_Y: { if (m_diYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState1.lY; } break; }
	case DIAxisID_1_Z: { if (m_diZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState1.lZ; } break; }
	case DIAxisID_1_RX: { if (m_diRXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState1.lRx; } break; }
	case DIAxisID_1_RY: { if (m_diRYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState1.lRy; } break; }
	case DIAxisID_1_RZ: { if (m_diRZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState1.lRz; } break; }
	case DIAxisID_1_SL0: { if (m_diSliderCount1) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState1.rglSlider[0]; } break; }
	case DIAxisID_1_SL1: { if (m_diSliderCount1 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState1.rglSlider[1]; } break; }
	case DIAxisID_2_X: { if (m_diXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState2.lX; } break; }
	case DIAxisID_2_Y: { if (m_diYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState2.lY; } break; }
	case DIAxisID_2_Z: { if (m_diZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState2.lZ; } break; }
	case DIAxisID_2_RX: { if (m_diRXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState2.lRx; } break; }
	case DIAxisID_2_RY: { if (m_diRYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState2.lRy; } break; }
	case DIAxisID_2_RZ: { if (m_diRZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState2.lRz; } break; }
	case DIAxisID_2_SL0: { if (m_diSliderCount2) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState2.rglSlider[0]; } break; }
	case DIAxisID_2_SL1: { if (m_diSliderCount2 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_R2] = JoyState2.rglSlider[1]; } break; }
	}

	switch (tape.diDispatch[Dispatch_SL0])
	{
	case DIAxisID_1_X: { if (m_diXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState1.lX; } break; }
	case DIAxisID_1_Y: { if (m_diYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState1.lY; } break; }
	case DIAxisID_1_Z: { if (m_diZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState1.lZ; } break; }
	case DIAxisID_1_RX: { if (m_diRXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState1.lRx; } break; }
	case DIAxisID_1_RY: { if (m_diRYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState1.lRy; } break; }
	case DIAxisID_1_RZ: { if (m_diRZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState1.lRz; } break; }
	case DIAxisID_1_SL0: { if (m_diSliderCount1) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState1.rglSlider[0]; } break; }
	case DIAxisID_1_SL1: { if (m_diSliderCount1 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState1.rglSlider[1]; } break; }
	case DIAxisID_2_X: { if (m_diXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState2.lX; } break; }
	case DIAxisID_2_Y: { if (m_diYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState2.lY; } break; }
	case DIAxisID_2_Z: { if (m_diZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState2.lZ; } break; }
	case DIAxisID_2_RX: { if (m_diRXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState2.lRx; } break; }
	case DIAxisID_2_RY: { if (m_diRYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState2.lRy; } break; }
	case DIAxisID_2_RZ: { if (m_diRZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState2.lRz; } break; }
	case DIAxisID_2_SL0: { if (m_diSliderCount2) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState2.rglSlider[0]; } break; }
	case DIAxisID_2_SL1: { if (m_diSliderCount2 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_SL0] = JoyState2.rglSlider[1]; } break; }
	}

	switch (tape.diDispatch[Dispatch_SL1])
	{
	case DIAxisID_1_X: { if (m_diXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState1.lX; } break; }
	case DIAxisID_1_Y: { if (m_diYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState1.lY; } break; }
	case DIAxisID_1_Z: { if (m_diZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState1.lZ; } break; }
	case DIAxisID_1_RX: { if (m_diRXAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState1.lRx; } break; }
	case DIAxisID_1_RY: { if (m_diRYAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState1.lRy; } break; }
	case DIAxisID_1_RZ: { if (m_diRZAxis1) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState1.lRz; } break; }
	case DIAxisID_1_SL0: { if (m_diSliderCount1) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState1.rglSlider[0]; } break; }
	case DIAxisID_1_SL1: { if (m_diSliderCount1 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState1.rglSlider[1]; } break; }
	case DIAxisID_2_X: { if (m_diXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState2.lX; } break; }
	case DIAxisID_2_Y: { if (m_diYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState2.lY; } break; }
	case DIAxisID_2_Z: { if (m_diZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState2.lZ; } break; }
	case DIAxisID_2_RX: { if (m_diRXAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState2.lRx; } break; }
	case DIAxisID_2_RY: { if (m_diRYAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState2.lRy; } break; }
	case DIAxisID_2_RZ: { if (m_diRZAxis2) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState2.lRz; } break; }
	case DIAxisID_2_SL0: { if (m_diSliderCount2) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState2.rglSlider[0]; } break; }
	case DIAxisID_2_SL1: { if (m_diSliderCount2 > 1) { tape.ReceivedData[SrceOffsetsID::Offset_SL1] = JoyState2.rglSlider[1]; } break; }
	}

	unsigned short dpad = -1;
	switch (tape.diDispatch[Dispatch_DPAD])
	{
	case DIPOVID_1_1: { if (m_diPOVCount1) { dpad = JoyState1.rgdwPOV[0]; } break; }
	case DIPOVID_1_2: { if (m_diPOVCount1 > 1) { dpad = JoyState1.rgdwPOV[1]; } break; }
	case DIPOVID_1_3: { if (m_diPOVCount1 > 2) { dpad = JoyState1.rgdwPOV[2]; } break; }
	case DIPOVID_1_4: { if (m_diPOVCount1 > 3) { dpad = JoyState1.rgdwPOV[3]; } break; }
	case DIPOVID_2_1: { if (m_diPOVCount2) { dpad = JoyState2.rgdwPOV[0]; } break; }
	case DIPOVID_2_2: { if (m_diPOVCount2 > 1) { dpad = JoyState2.rgdwPOV[1]; } break; }
	case DIPOVID_2_3: { if (m_diPOVCount2 > 2) { dpad = JoyState2.rgdwPOV[2]; } break; }
	case DIPOVID_2_4: { if (m_diPOVCount2 > 3) { dpad = JoyState2.rgdwPOV[3]; } break; }
	}
	if (dpad != -1)
	{
		dpad = dpad / 4500;
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= ((dpad == 5 || dpad == 6 || dpad == 7) ? 1 : 0);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 7 || dpad == 0 || dpad == 1) ? 1 : 0) << 1);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 1 || dpad == 2 || dpad == 3) ? 1 : 0) << 2);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 3 || dpad == 4 || dpad == 5) ? 1 : 0) << 3);
	}

	dpad = -1;
	switch (tape.diDispatch[Dispatch_DPAD2])
	{
	case DIPOVID_1_1: { if (m_diPOVCount1) { dpad = JoyState1.rgdwPOV[0]; } break; }
	case DIPOVID_1_2: { if (m_diPOVCount1 > 1) { dpad = JoyState1.rgdwPOV[1]; } break; }
	case DIPOVID_1_3: { if (m_diPOVCount1 > 2) { dpad = JoyState1.rgdwPOV[2]; } break; }
	case DIPOVID_1_4: { if (m_diPOVCount1 > 3) { dpad = JoyState1.rgdwPOV[3]; } break; }
	case DIPOVID_2_1: { if (m_diPOVCount2) { dpad = JoyState2.rgdwPOV[0]; } break; }
	case DIPOVID_2_2: { if (m_diPOVCount2 > 1) { dpad = JoyState2.rgdwPOV[1]; } break; }
	case DIPOVID_2_3: { if (m_diPOVCount2 > 2) { dpad = JoyState2.rgdwPOV[2]; } break; }
	case DIPOVID_2_4: { if (m_diPOVCount2 > 3) { dpad = JoyState2.rgdwPOV[3]; } break; }
	}
	if (dpad != -1)
	{
		dpad = dpad / 4500;
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 5 || dpad == 6 || dpad == 7) ? 1 : 0) << 4);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 7 || dpad == 0 || dpad == 1) ? 1 : 0) << 5);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 1 || dpad == 2 || dpad == 3) ? 1 : 0) << 6);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 3 || dpad == 4 || dpad == 5) ? 1 : 0) << 7);
	}

	dpad = -1;
	switch (tape.diDispatch[Dispatch_DPAD3])
	{
	case DIPOVID_1_1: { if (m_diPOVCount1) { dpad = JoyState1.rgdwPOV[0]; } break; }
	case DIPOVID_1_2: { if (m_diPOVCount1 > 1) { dpad = JoyState1.rgdwPOV[1]; } break; }
	case DIPOVID_1_3: { if (m_diPOVCount1 > 2) { dpad = JoyState1.rgdwPOV[2]; } break; }
	case DIPOVID_1_4: { if (m_diPOVCount1 > 3) { dpad = JoyState1.rgdwPOV[3]; } break; }
	case DIPOVID_2_1: { if (m_diPOVCount2) { dpad = JoyState2.rgdwPOV[0]; } break; }
	case DIPOVID_2_2: { if (m_diPOVCount2 > 1) { dpad = JoyState2.rgdwPOV[1]; } break; }
	case DIPOVID_2_3: { if (m_diPOVCount2 > 2) { dpad = JoyState2.rgdwPOV[2]; } break; }
	case DIPOVID_2_4: { if (m_diPOVCount2 > 3) { dpad = JoyState2.rgdwPOV[3]; } break; }
	}
	if (dpad != -1)
	{
		dpad = dpad / 4500;
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 5 || dpad == 6 || dpad == 7) ? 1 : 0) << 8);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 7 || dpad == 0 || dpad == 1) ? 1 : 0) << 9);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 1 || dpad == 2 || dpad == 3) ? 1 : 0) << 10);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 3 || dpad == 4 || dpad == 5) ? 1 : 0) << 11);
	}

	dpad = -1;
	switch (tape.diDispatch[Dispatch_DPAD4])
	{
	case DIPOVID_1_1: { if (m_diPOVCount1) { dpad = JoyState1.rgdwPOV[0]; } break; }
	case DIPOVID_1_2: { if (m_diPOVCount1 > 1) { dpad = JoyState1.rgdwPOV[1]; } break; }
	case DIPOVID_1_3: { if (m_diPOVCount1 > 2) { dpad = JoyState1.rgdwPOV[2]; } break; }
	case DIPOVID_1_4: { if (m_diPOVCount1 > 3) { dpad = JoyState1.rgdwPOV[3]; } break; }
	case DIPOVID_2_1: { if (m_diPOVCount2) { dpad = JoyState2.rgdwPOV[0]; } break; }
	case DIPOVID_2_2: { if (m_diPOVCount2 > 1) { dpad = JoyState2.rgdwPOV[1]; } break; }
	case DIPOVID_2_3: { if (m_diPOVCount2 > 2) { dpad = JoyState2.rgdwPOV[2]; } break; }
	case DIPOVID_2_4: { if (m_diPOVCount2 > 3) { dpad = JoyState2.rgdwPOV[3]; } break; }
	}
	if (dpad != -1)
	{
		dpad = dpad / 4500;
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 5 || dpad == 6 || dpad == 7) ? 1 : 0) << 12);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 7 || dpad == 0 || dpad == 1) ? 1 : 0) << 13);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 1 || dpad == 2 || dpad == 3) ? 1 : 0) << 14);
		tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((dpad == 3 || dpad == 4 || dpad == 5) ? 1 : 0) << 15);
	}

	unsigned short button = tape.diDispatch[Dispatch_SQUARE];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= ((JoyState2.rgbButtons[button - 65]) ? 1 : 0);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= ((JoyState1.rgbButtons[button - 1]) ? 1 : 0);

	button = tape.diDispatch[Dispatch_CROSS];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 1);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 1);

	button = tape.diDispatch[Dispatch_CIRCLE];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 2);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 2);

	button = tape.diDispatch[Dispatch_TRIANGLE];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 3);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 3);

	button = tape.diDispatch[Dispatch_L1];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 4);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 4);

	button = tape.diDispatch[Dispatch_R1];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 5);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 5);

	button = tape.diDispatch[Dispatch_L2];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 6);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 6);

	button = tape.diDispatch[Dispatch_R2];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 7);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 7);

	button = tape.diDispatch[Dispatch_SHARE];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 8);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 8);

	button = tape.diDispatch[Dispatch_OPTIONS];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 9);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 9);

	button = tape.diDispatch[Dispatch_L3];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 10);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 10);

	button = tape.diDispatch[Dispatch_R3];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 11);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 11);

	button = tape.diDispatch[Dispatch_PS];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 12);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 12);

	button = tape.diDispatch[Dispatch_TOUCH];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 13);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 13);

	button = tape.diDispatch[Dispatch_MUTE];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 14);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 14);

	button = tape.diDispatch[Dispatch_BUTTON16];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 15);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 15);

	button = tape.diDispatch[Dispatch_BUTTON17];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= ((JoyState2.rgbButtons[button - 65]) ? 1 : 0);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= ((JoyState1.rgbButtons[button - 1]) ? 1 : 0);

	button = tape.diDispatch[Dispatch_BUTTON18];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 1);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 1);

	button = tape.diDispatch[Dispatch_BUTTON19];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 2);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 2);

	button = tape.diDispatch[Dispatch_BUTTON20];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 3);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 3);

	button = tape.diDispatch[Dispatch_BUTTON21];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 4);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 4);

	button = tape.diDispatch[Dispatch_BUTTON22];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 5);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 5);

	button = tape.diDispatch[Dispatch_BUTTON23];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 6);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 6);

	button = tape.diDispatch[Dispatch_BUTTON24];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 7);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 7);

	button = tape.diDispatch[Dispatch_BUTTON25];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 8);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 8);

	button = tape.diDispatch[Dispatch_BUTTON26];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 9);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 9);

	button = tape.diDispatch[Dispatch_BUTTON27];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 10);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 10);

	button = tape.diDispatch[Dispatch_BUTTON28];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 11);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 11);

	button = tape.diDispatch[Dispatch_BUTTON29];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 12);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 12);

	button = tape.diDispatch[Dispatch_BUTTON30];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 13);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 13);

	button = tape.diDispatch[Dispatch_BUTTON31];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 14);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 14);

	button = tape.diDispatch[Dispatch_BUTTON32];
	if (button)
		if (button > DIButtonID_1_64)
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState2.rgbButtons[button - 65]) ? 1 : 0) << 15);
		else
			tape.ReceivedData[SrceOffsetsID::Offset_BUTTON2] |= (((JoyState1.rgbButtons[button - 1]) ? 1 : 0) << 15);

	return TRUE;
}

//Analysis of XInput received data
BOOL Source::_parseXInput()
{
	WORD wButtons = m_xiController.Gamepad.wButtons;

	tape.ReceivedData[SrceOffsetsID::Offset_L2] = m_xiController.Gamepad.bLeftTrigger * 257;
	tape.ReceivedData[SrceOffsetsID::Offset_R2] = m_xiController.Gamepad.bRightTrigger * 257;

	tape.ReceivedData[SrceOffsetsID::Offset_LX] = m_xiController.Gamepad.sThumbLX + 32768;
	tape.ReceivedData[SrceOffsetsID::Offset_LY] = m_xiController.Gamepad.sThumbLY + 32768;
	tape.ReceivedData[SrceOffsetsID::Offset_RX] = m_xiController.Gamepad.sThumbRX + 32768;
	tape.ReceivedData[SrceOffsetsID::Offset_RY] = m_xiController.Gamepad.sThumbRY + 32768;

	tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= ((wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? 1 : 0);
	tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((wButtons & XINPUT_GAMEPAD_DPAD_UP) ? 1 : 0) << 1);
	tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? 1 : 0) << 2);
	tape.ReceivedData[SrceOffsetsID::Offset_DPAD] |= (((wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? 1 : 0) << 3);

	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= ((wButtons & XINPUT_GAMEPAD_X) ? 1 : 0);								// SQUARE
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_A) ? 1 : 0) << 1);							// CROSS
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_B) ? 1 : 0) << 2);							// CIRCLE
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_Y) ? 1 : 0) << 3);							// TRIANGLE
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? 1 : 0) << 4);				// L1
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 1 : 0) << 5);			// R1
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((m_xiController.Gamepad.bLeftTrigger) ? 1 : 0) << 6);					// L2
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((m_xiController.Gamepad.bRightTrigger) ? 1 : 0) << 7);				// R2
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_BACK) ? 1 : 0) << 8);						// SHARE
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_START) ? 1 : 0) << 9);						// OPTIONS
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? 1 : 0) << 10);				// L3
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? 1 : 0) << 11);				// R3
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_GUIDE) ? 1 : 0) << 12);					// PS
	tape.ReceivedData[SrceOffsetsID::Offset_BUTTON1] |= (((wButtons & XINPUT_GAMEPAD_UNKNOWN) ? 1 : 0) << 14);					// MUTE

	DWORD dwResult = XInputGetBatteryInformation(tape.XInputDevice, BATTERY_DEVTYPE_GAMEPAD, &m_xiBattery);
	if (dwResult == ERROR_SUCCESS)
	{
		switch (m_xiBattery.BatteryType)
		{
		case BATTERY_TYPE_DISCONNECTED:
		case BATTERY_TYPE_UNKNOWN:
		{
			tape.BatteryLevel = 0;
			tape.BatteryCharge = false;
			break;
		}
		case BATTERY_TYPE_WIRED:
		{
			tape.BatteryLevel = 100;
			tape.BatteryCharge = true;
			break;
		}
		case BATTERY_TYPE_ALKALINE:
		case BATTERY_TYPE_NIMH:
		{
			switch (m_xiBattery.BatteryLevel)
			{
			case BATTERY_LEVEL_EMPTY: { tape.BatteryLevel = 10; break; }	// Charge is between	0%		and		10%
			case BATTERY_LEVEL_LOW: { tape.BatteryLevel = 40; break; }		// Charge is between	10%		and		40%
			case BATTERY_LEVEL_MEDIUM: { tape.BatteryLevel = 70; break; }	// Charge is between	40%		and		70%
			case BATTERY_LEVEL_FULL: { tape.BatteryLevel = 100; break; }	// Charge is between	70%		and		100%
			default: { tape.BatteryLevel = 100; break; }
			}
			tape.BatteryCharge = false;
			break;
		}
		}
	}
	else
	{
		tape.BatteryLevel = 0;
		tape.BatteryCharge = false;
	}

	return TRUE;
}

//Analysis of Mouse received data
BOOL Source::_parseMouse()
{
	GetCursorPos(&tape.mousepoint);
	if (tape.W > tape.H)
	{
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_AXEX] = (unsigned short)min(65535, ((((tape.mousepoint.x - tape.w) * tape.proportianality) + tape.w) * 65535) / tape.W);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_AXEY] = (unsigned short)min(65535, (tape.mousepoint.y * 65535) / tape.H);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_LEFT] = (unsigned short)((tape.mousepoint.x < tape.w) ? (((tape.w - tape.mousepoint.x) * 65535 * tape.proportianality) / tape.w) : 0);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_RIGHT] = (unsigned short)((tape.mousepoint.x > tape.w) ? (((tape.mousepoint.x - tape.w) * 65535 * tape.proportianality) / tape.w) : 0);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_UP] = (unsigned short)((tape.mousepoint.y < tape.h) ? (((tape.h - tape.mousepoint.y) * 65535) / tape.h) : 0);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_DOWN] = (unsigned short)((tape.mousepoint.y > tape.h) ? (((tape.mousepoint.y - tape.h) * 65535) / tape.h) : 0);
	}
	else
	{
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_AXEX] = (unsigned short)min(65535, (tape.mousepoint.x * 65535) / tape.W);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_AXEY] = (unsigned short)min(65535, ((((tape.mousepoint.y - tape.h) * tape.proportianality) + tape.h) * 65535) / tape.H);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_LEFT] = (unsigned short)((tape.mousepoint.x < tape.w) ? (((tape.w - tape.mousepoint.x) * 65535) / tape.w) : 0);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_RIGHT] = (unsigned short)((tape.mousepoint.x > tape.w) ? (((tape.mousepoint.x - tape.w) * 65535) / tape.w) : 0);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_UP] = (unsigned short)((tape.mousepoint.y < tape.h) ? (((tape.h - tape.mousepoint.y) * 65535 * tape.proportianality) / tape.h) : 0);
		tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_DOWN] = (unsigned short)((tape.mousepoint.y > tape.h) ? (((tape.mousepoint.y - tape.h) * 65535 * tape.proportianality) / tape.h) : 0);
	}

	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (1														 << 1);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1 : 0)	 << 3);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_MBUTTON) & 0x8000) ? 1 : 0)	 << 4);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 1 : 0)	 << 5);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_XBUTTON1) & 0x8000) ? 1 : 0)	 << 6);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_XBUTTON2) & 0x8000) ? 1 : 0)	 << 7);
	
	if (m_diMouse)
	{
		// Read the mouse device.
		DIMOUSESTATE2 m_mouseState;
		HRESULT hr = m_diMouse->GetDeviceState(sizeof(DIMOUSESTATE2), (LPVOID)&m_mouseState);
		if (FAILED(hr))
		{
			// If the mouse lost focus or was not acquired then try to get control back.
			if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
				m_diMouse->Acquire();
			else
				return FALSE;
		}

		if (m_mouseState.lZ >= 240)			{ tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_AXEZ] |= (1			<< 3); }	//SCROLLUP_HIGH
		else if (m_mouseState.lZ >= 120)	{ tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_AXEZ] |= (1			<< 2); }	//SCROLLUP_LOW
		else if (m_mouseState.lZ <= -240)	{ tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_AXEZ] |= 1; }					//SCROLLDOWN_HIGH
		else if (m_mouseState.lZ <= -120)	{ tape.ReceivedData[SrceOffsetsID::Offset_MOUSE_AXEZ] |= (1			<< 1); }	//SCROLLDOWN_LOW
		
		tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (1									<< 2);	//MSE_DI_ACTIVE
		tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (m_mouseState.rgbButtons[5]			<< 8);	//MOUSE_BUTTON6
		tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (m_mouseState.rgbButtons[6]			<< 9);	//MOUSE_BUTTON7
		tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (m_mouseState.rgbButtons[7]			<< 10);	//MOUSE_BUTTON8
	}
	return TRUE;
}

//Analysis of Keyboard received data
BOOL Source::_parseKeyboard()
{
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= 1;
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_F1) & 0x8000) ? 1 : 0)			 << 11);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_F2) & 0x8000) ? 1 : 0)			 << 12);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_F3) & 0x8000) ? 1 : 0)			 << 13);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_F4) & 0x8000) ? 1 : 0)			 << 14);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD1] |= (((GetAsyncKeyState(VK_F5) & 0x8000) ? 1 : 0)			 << 15);
	
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= ((GetAsyncKeyState(VK_F6) & 0x8000) ? 1 : 0);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_F7) & 0x8000) ? 1 : 0)			 << 1);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_F8) & 0x8000) ? 1 : 0)			 << 2);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_F9) & 0x8000) ? 1 : 0)			 << 3);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_F10) & 0x8000) ? 1 : 0)		 << 4);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_F11) & 0x8000) ? 1 : 0)		 << 5);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_F12) & 0x8000) ? 1 : 0)		 << 6);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_0) & 0x8000) ? 1 : 0)			 << 7);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_1) & 0x8000) ? 1 : 0)			 << 8);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_2) & 0x8000) ? 1 : 0)			 << 9);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_3) & 0x8000) ? 1 : 0)			 << 10);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_4) & 0x8000) ? 1 : 0)			 << 11);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_5) & 0x8000) ? 1 : 0)			 << 12);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_6) & 0x8000) ? 1 : 0)			 << 13);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_7) & 0x8000) ? 1 : 0)			 << 14);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD2] |= (((GetAsyncKeyState(VK_8) & 0x8000) ? 1 : 0)			 << 15);

	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= ((GetAsyncKeyState(VK_9) & 0x8000) ? 1 : 0);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_MINUS) & 0x8000) ? 1 : 0)	 << 1);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_PLUS) & 0x8000) ? 1 : 0)	 << 2);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_1) & 0x8000) ? 1 : 0)		 << 3);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_2) & 0x8000) ? 1 : 0)		 << 4);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_3) & 0x8000) ? 1 : 0)		 << 5);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_4) & 0x8000) ? 1 : 0)		 << 6);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_5) & 0x8000) ? 1 : 0)		 << 7);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_6) & 0x8000) ? 1 : 0)		 << 8);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_7) & 0x8000) ? 1 : 0)		 << 9);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_8) & 0x8000) ? 1 : 0)		 << 10);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_102) & 0x8000) ? 1 : 0)	 << 11);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_COMMA) & 0x8000) ? 1 : 0)	 << 12);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) ? 1 : 0)	 << 13);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_A) & 0x8000) ? 1 : 0)			 << 14);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD3] |= (((GetAsyncKeyState(VK_B) & 0x8000) ? 1 : 0)			 << 15);

	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= ((GetAsyncKeyState(VK_C) & 0x8000) ? 1 : 0);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_D) & 0x8000) ? 1 : 0)			 << 1);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_E) & 0x8000) ? 1 : 0)			 << 2);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_F) & 0x8000) ? 1 : 0)			 << 3);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_G) & 0x8000) ? 1 : 0)			 << 4);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_H) & 0x8000) ? 1 : 0)			 << 5);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_I) & 0x8000) ? 1 : 0)			 << 6);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_J) & 0x8000) ? 1 : 0)			 << 7);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_K) & 0x8000) ? 1 : 0)			 << 8);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_L) & 0x8000) ? 1 : 0)			 << 9);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_M) & 0x8000) ? 1 : 0)			 << 10);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_N) & 0x8000) ? 1 : 0)			 << 11);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_O) & 0x8000) ? 1 : 0)			 << 12);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_P) & 0x8000) ? 1 : 0)			 << 13);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_Q) & 0x8000) ? 1 : 0)			 << 14);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD4] |= (((GetAsyncKeyState(VK_R) & 0x8000) ? 1 : 0)			 << 15);

	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= ((GetAsyncKeyState(VK_S) & 0x8000) ? 1 : 0);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_T) & 0x8000) ? 1 : 0)			 << 1);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_U) & 0x8000) ? 1 : 0)			 << 2);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_V) & 0x8000) ? 1 : 0)			 << 3);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_W) & 0x8000) ? 1 : 0)			 << 4);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_X) & 0x8000) ? 1 : 0)			 << 5);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_Y) & 0x8000) ? 1 : 0)			 << 6);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_Z) & 0x8000) ? 1 : 0)			 << 7);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_ESCAPE) & 0x8000) ? 1 : 0)		 << 8);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_TAB) & 0x8000) ? 1 : 0)		 << 9);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_RETURN) & 0x8000) ? 1 : 0)		 << 10);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0)		 << 11);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_BACK) & 0x8000) ? 1 : 0)		 << 12);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_DELETE) & 0x8000) ? 1 : 0)		 << 13);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_INSERT) & 0x8000) ? 1 : 0)		 << 14);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD5] |= (((GetAsyncKeyState(VK_NUMLOCK) & 0x8000) ? 1 : 0)	 << 15);

	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6]	|= ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) ? 1 : 0);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_RSHIFT) & 0x8000) ? 1 : 0)		 << 1);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_LCONTROL) & 0x8000) ? 1 : 0)	 << 2);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_RCONTROL) & 0x8000) ? 1 : 0)	 << 3);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_LWIN) & 0x8000) ? 1 : 0)		 << 4);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_RWIN) & 0x8000) ? 1 : 0)		 << 5);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_LMENU) & 0x8000) ? 1 : 0)		 << 6);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_RMENU) & 0x8000) ? 1 : 0)		 << 7);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_LEFT) & 0x8000) ? 1 : 0)		 << 8);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_UP) & 0x8000) ? 1 : 0)			 << 9);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_RIGHT) & 0x8000) ? 1 : 0)		 << 10);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_DOWN) & 0x8000) ? 1 : 0)		 << 11);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_PRIOR) & 0x8000) ? 1 : 0)		 << 12);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_NEXT) & 0x8000) ? 1 : 0)		 << 13);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_END) & 0x8000) ? 1 : 0)		 << 14);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD6] |= (((GetAsyncKeyState(VK_HOME) & 0x8000) ? 1 : 0)		 << 15);

	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= ((GetAsyncKeyState(VK_NUMPAD0) & 0x8000) ? 1 : 0);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) ? 1 : 0)	 << 1);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) ? 1 : 0)	 << 2);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) ? 1 : 0)	 << 3);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_NUMPAD4) & 0x8000) ? 1 : 0)	 << 4);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_NUMPAD5) & 0x8000) ? 1 : 0)	 << 5);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_NUMPAD6) & 0x8000) ? 1 : 0)	 << 6);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_NUMPAD7) & 0x8000) ? 1 : 0)	 << 7);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_NUMPAD8) & 0x8000) ? 1 : 0)	 << 8);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_NUMPAD9) & 0x8000) ? 1 : 0)	 << 9);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_DIVIDE) & 0x8000) ? 1 : 0)		 << 10);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_MULTIPLY) & 0x8000) ? 1 : 0)	 << 11);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) ? 1 : 0)	 << 12);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_ADD) & 0x8000) ? 1 : 0)		 << 13);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_SEPARATOR) & 0x8000) ? 1 : 0)	 << 14);
	tape.ReceivedData[SrceOffsetsID::Offset_KEYBOARD7] |= (((GetAsyncKeyState(VK_DECIMAL) & 0x8000) ? 1 : 0)	 << 15);

	return TRUE;
}

void Source::DisconnectBT()
{
	if (!isBT())
		return;

	BLUETOOTH_ADDRESS dsAddr;
	int ic = 5;
	for (int i = 0; i < 12; i++)
	{
		byte hex = (byte)dsSerial[i];
		if ('0' <= hex && hex <= '9')
			hex -= '0';
		else if ('a' <= hex && hex <= 'f')
			hex -= 'a' - 10;
		else if ('A' <= hex && hex <= 'F')
			hex -= 'A' - 10;
		else
			hex = 0;
		if (i & 1)
		{
			dsAddr.rgBytes[ic] |= hex;
			ic--;
		}
		else
			dsAddr.rgBytes[ic] = hex << 4;
	}
	Close();

	BLUETOOTH_FIND_RADIO_PARAMS param = { 0 };
	param.dwSize = sizeof(BLUETOOTH_FIND_RADIO_PARAMS);

	HANDLE radio = 0;
	HBLUETOOTH_RADIO_FIND find = BluetoothFindFirstRadio(&param, &radio);
	if (find)
	{
		do
		{
			BLUETOOTH_RADIO_INFO info = { 0 };
			info.dwSize = sizeof(BLUETOOTH_RADIO_INFO);
			if (BluetoothGetRadioInfo(radio, &info) == ERROR_SUCCESS)
			{
				DWORD n;
				if (DeviceIoControl(radio, 0x41000c, &dsAddr, sizeof(dsAddr), 0, 0, &n, 0))
				{
					CloseHandle(radio);
					return;
				}
			}
			CloseHandle(radio);
		} while (BluetoothFindNextRadio(find, &radio));
	}
}

SourceButton* Source::GetButton(SrceButtonID id)
{
	if (id >= SrceButtonID::Button_None && id < SrceButtonID::Keyboard_Count)
		return &m_buttons[id];

	return &m_buttons[0];
}

BOOL Source::isBT()
{
	return m_bBluetooth;
}

BOOL Source::TouchActive(bool i)
{
	return (m_receivedTouch[((i) ? 4 : 0)] & 0b10000000) == 0;
}

int Source::TouchX(bool i)
{
	return ((m_receivedTouch[2 + ((i) ? 4 : 0)] & 0x0F) << 8) | m_receivedTouch[1 + ((i) ? 4 : 0)];
}

int Source::TouchY(bool i)
{
	return (m_receivedTouch[2 + ((i) ? 4 : 0)] >> 4) | (m_receivedTouch[3 + ((i) ? 4 : 0)] << 4);
}

BYTE Source::TouchId(bool i)
{
	return m_receivedTouch[((i) ? 4 : 0)] & 0b1111111;
}

void Source::String()
{
	wchar_t buf[MAX_PATH];
	wchar_t* offset = buf;

	if (tape.ActualSource == 2)
		offset += swprintf_s(offset, MAX_PATH, L"%3d:  %d (%d,%d)    %3d:  %d (%d,%d)"
			, TouchId(0), TouchActive(0), TouchX(0), TouchY(0)
			, TouchId(1), TouchActive(1), TouchX(1), TouchY(1));
	else
		offset += swprintf_s(offset, MAX_PATH, L"%d (%d,%d)    %d (%d,%d)"
			, TouchActive(0), TouchX(0), TouchY(0)
			, TouchActive(1), TouchX(1), TouchY(1));

	if (buf != offset)
		echo(buf);
}

WCHAR* Source::DIAxisString(DIAxisID id)
{
	switch (id)
	{
	case DIAxisID_none: return I18N.EMPTY;
	case DIAxisID_1_X: return I18N.Dispatch_1_X;
	case DIAxisID_1_Y: return I18N.Dispatch_1_Y;
	case DIAxisID_1_Z: return I18N.Dispatch_1_Z;
	case DIAxisID_1_RX: return I18N.Dispatch_1_RX;
	case DIAxisID_1_RY: return I18N.Dispatch_1_RY;
	case DIAxisID_1_RZ: return I18N.Dispatch_1_RZ;
	case DIAxisID_1_SL0: return I18N.Dispatch_1_SL0;
	case DIAxisID_1_SL1: return I18N.Dispatch_1_SL1;
	case DIAxisID_2_X: return I18N.Dispatch_2_X;
	case DIAxisID_2_Y: return I18N.Dispatch_2_Y;
	case DIAxisID_2_Z: return I18N.Dispatch_2_Z;
	case DIAxisID_2_RX: return I18N.Dispatch_2_RX;
	case DIAxisID_2_RY: return I18N.Dispatch_2_RY;
	case DIAxisID_2_RZ: return I18N.Dispatch_2_RZ;
	case DIAxisID_2_SL0: return I18N.Dispatch_2_SL0;
	case DIAxisID_2_SL1: return I18N.Dispatch_2_SL1;
	default: return I18N.WHICH;
	}
}

WCHAR* Source::DIPOVString(DIPOVID id)
{
	switch (id)
	{
	case DIPOVID_none: return I18N.EMPTY;
	case DIPOVID_1_1: return I18N.Dispatch_1_POV1;
	case DIPOVID_1_2: return I18N.Dispatch_1_POV2;
	case DIPOVID_1_3: return I18N.Dispatch_1_POV3;
	case DIPOVID_1_4: return I18N.Dispatch_1_POV4;
	case DIPOVID_2_1: return I18N.Dispatch_2_POV1;
	case DIPOVID_2_2: return I18N.Dispatch_2_POV2;
	case DIPOVID_2_3: return I18N.Dispatch_2_POV3;
	case DIPOVID_2_4: return I18N.Dispatch_2_POV4;
	default: return I18N.WHICH;
	}
}

WCHAR* Source::DIButtonString(DIButtonID id)
{
	if (id == DIButtonID_none)
		return I18N.EMPTY;
	else if (DIButtonID_none < id && id <= DIButtonID_1_64)
	{
		static WCHAR buf[10];
		swprintf_s(buf, 10, I18N.Dispatch_BUTTON, 1, id - DIButtonID_1_1 + 1);
		return buf;
	}
	else if (DIButtonID_2_1 <= id && id < DIButtonID_Count)
	{
		static WCHAR buf[10];
		swprintf_s(buf, 10, I18N.Dispatch_BUTTON, 2, id - DIButtonID_2_1 + 1);
		return buf;
	}

	return I18N.WHICH;
}
