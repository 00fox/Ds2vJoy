#include "stdafx.h"
#include "Source.h"
#include "Ds2vJoy.h"
#include "crc32.h"

unsigned __stdcall inputloop(void* v)
{
	((dsDevice*)v)->InputLoop();
	return 0;
}
unsigned __stdcall outputloop(void* v)
{
	((dsDevice*)v)->OutputLoop();
	return 0;
}

dsDevice::dsDevice() :
	m_callback(0), m_callbackdata(0)
{
	m_oRead.hEvent = m_hREvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_oWrite.hEvent = m_hWEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	PreOpen();
	AssignOffsets();
}

dsDevice::~dsDevice()
{
	Close();
	CloseHandle(m_hREvent);
	CloseHandle(m_hWEvent);
}

BOOL dsDevice::Active()
{
	return dsHandle != INVALID_HANDLE_VALUE;
}

void dsDevice::PreOpen()
{
	int ndsType = 0;

	GUID guid;
	HidD_GetHidGuid(&guid);
	hDevInfo = SetupDiGetClassDevs(&guid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hDevInfo == 0)
	{
		SetupDiDestroyDeviceInfoList(hDevInfo);
		return;
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

		dsHandle = CreateFile(
			detail->DevicePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			NULL,
			NULL);

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
			if (tape.PreferredDS == 1 && SerialTest(1)) { tape.ActualDS = 1; return; }
		}
		else if (0x0CE6 == Attributes.ProductID)
		{
			if (tape.PreferredDS == 2 && SerialTest(2)) { tape.ActualDS = 2; return; }
		}

		continue;
	}

	if (!tape.PreferredDS)
		tape.ActualDS = 2;
	CloseHandle(dsHandle);
	dsHandle = INVALID_HANDLE_VALUE;
}

BOOL dsDevice::SerialTest(int devicetype)
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
			wsprintf(dsSerial, L"%02x%02x%02x%02x%02x%02x", buf[6], buf[5], buf[4], buf[3], buf[2], buf[1]);
		}
		else
		{
			unsigned char buf[16] = { 18 };
			if (!HidD_GetFeature(dsHandle, buf, sizeof(buf)))
				return FALSE;
			wsprintf(dsSerial, L"%02x%02x%02x%02x%02x%02x", buf[6], buf[5], buf[4], buf[3], buf[2], buf[1]);
		}
	}

	if (0 != m_TargetSerial[0] && _wcsicmp(m_TargetSerial, dsSerial) != 0)
	{
		if (devicetype == 2)
			echo(I18N.SkipController, L"DualSense", dsSerial);
		else
			echo(I18N.SkipController, L"DualShock", dsSerial);
		return FALSE;
	}

	return TRUE;
}

void dsDevice::AssignOffsets()
{
	//DualShock
	int OffsetLX = 0;
	int OffsetLY = 1;
	int OffsetRX = 2;
	int OffsetRY = 3;
	int OffsetDPad = 4;
	int OffsetSquare = 4;
	int OffsetCross = 4;
	int OffsetCircle = 4;
	int OffsetTriangle = 4;
	int OffsetL1 = 5;
	int OffsetR1 = 5;
	int OffsetL2 = 5;
	int OffsetR2 = 5;
	int OffsetShare = 5;
	int OffsetOption = 5;
	int OffsetL3 = 5;
	int OffsetR3 = 5;
	int OffsetPS = 6;
	int OffsetTouchPadClick = 6;
	int OffsetCounter = 6;
	int OffsetLeftTrigger = 7;
	int OffsetRightTrigger = 8;
	int OffsetBattery = 11;
	int OffsetPacketCounter = 33;
	int OffsetFinger1 = 34;
	int OffsetFinger2 = 38;

	//DualSense
	int OffsetMute = 9;
	if (tape.ActualDS == 2)
	{
		OffsetLeftTrigger = 4;
		OffsetRightTrigger = 5;
		OffsetCounter = 6;
		OffsetDPad = 7;
		OffsetSquare = 7;
		OffsetCross = 7;
		OffsetCircle = 7;
		OffsetTriangle = 7;
		OffsetL1 = 8;
		OffsetR1 = 8;
		OffsetL2 = 8;
		OffsetR2 = 8;
		OffsetShare = 8;
		OffsetOption = 8;
		OffsetL3 = 8;
		OffsetR3 = 8;
		OffsetPS = 9;
		OffsetTouchPadClick = 9;
		OffsetTouch = 32;
		OffsetBatteryLevel = 52;
	};

	m_buttons[dsButton::none].setConstant(0);
	m_buttons[dsButton::LX].setAxis(m_receivedData + OffsetLX, m_receivedData + OffsetLY, 0);
	m_buttons[dsButton::LY].setAxis(m_receivedData + OffsetLY, m_receivedData + OffsetLX, 1);
	m_buttons[dsButton::RX].setAxis(m_receivedData + OffsetRX, m_receivedData + OffsetRY, 2);
	m_buttons[dsButton::RY].setAxis(m_receivedData + OffsetRY, m_receivedData + OffsetRX, 3);
	m_buttons[dsButton::L3].setButton(m_receivedData + OffsetL3, 0b1000000);
	m_buttons[dsButton::DPAD_LEFT].setDPad(m_receivedData + OffsetDPad, dsButton::Type_DPadLEFT);
	m_buttons[dsButton::DPAD_UP].setDPad(m_receivedData + OffsetDPad, dsButton::Type_DPadUP);
	m_buttons[dsButton::DPAD_RIGHT].setDPad(m_receivedData + OffsetDPad, dsButton::Type_DPadRIGHT);
	m_buttons[dsButton::DPAD_DOWN].setDPad(m_receivedData + OffsetDPad, dsButton::Type_DPadDOWN);
	m_buttons[dsButton::SHARE].setButton(m_receivedData + OffsetShare, 0b10000);
	m_buttons[dsButton::OPTIONS].setButton(m_receivedData + OffsetOption, 0b100000);
	m_buttons[dsButton::SQUARE].setButton(m_receivedData + OffsetSquare, 0b10000);
	m_buttons[dsButton::TRIANGLE].setButton(m_receivedData + OffsetTriangle, 0b10000000);
	m_buttons[dsButton::CIRCLE].setButton(m_receivedData + OffsetCircle, 0b1000000);
	m_buttons[dsButton::CROSS].setButton(m_receivedData + OffsetCross, 0b100000);
	m_buttons[dsButton::R3].setButton(m_receivedData + OffsetR3, 0b10000000);
	m_buttons[dsButton::PS].setButton(m_receivedData + OffsetPS, 0b1);
	m_buttons[dsButton::TOUCH].setTouch(m_receivedData + OffsetTouchPadClick, 0b10, 7);
	m_buttons[dsButton::MUTE].setButton(m_receivedData + OffsetMute, 0b100, true);
	m_buttons[dsButton::L1].setButton(m_receivedData + OffsetL1, 0b1);
	m_buttons[dsButton::R1].setButton(m_receivedData + OffsetR1, 0b10);
	m_buttons[dsButton::L2].setButton(m_receivedData + OffsetL2, 0b100);
	m_buttons[dsButton::R2].setButton(m_receivedData + OffsetR2, 0b1000);
	m_buttons[dsButton::L2TRIGGER].setTrigger(m_receivedData + OffsetLeftTrigger, 0);
	m_buttons[dsButton::R2TRIGGER].setTrigger(m_receivedData + OffsetRightTrigger, 0);
	m_buttons[dsButton::EMPTY].setConstant(0);
	m_buttons[dsButton::MIDDLE].setConstant(127);
	m_buttons[dsButton::FULL].setConstant(255);
	m_buttons[dsButton::LXINV].setAxisInv(m_receivedData + OffsetLX, m_receivedData + OffsetLY, 0);
	m_buttons[dsButton::LYINV].setAxisInv(m_receivedData + OffsetLY, m_receivedData + OffsetLX, 1);
	m_buttons[dsButton::RXINV].setAxisInv(m_receivedData + OffsetRX, m_receivedData + OffsetRY, 2);
	m_buttons[dsButton::RYINV].setAxisInv(m_receivedData + OffsetRY, m_receivedData + OffsetRX, 3);
	m_buttons[dsButton::SNIPER_LX].setAxisSniper(m_receivedData + OffsetLX, m_receivedData + OffsetLY);
	m_buttons[dsButton::SNIPER_LY].setAxisSniper(m_receivedData + OffsetLY, m_receivedData + OffsetLX);
	m_buttons[dsButton::SNIPER_RX].setAxisSniper(m_receivedData + OffsetRX, m_receivedData + OffsetRY);
	m_buttons[dsButton::SNIPER_RY].setAxisSniper(m_receivedData + OffsetRY, m_receivedData + OffsetRX);
	m_buttons[dsButton::AXISL_TR_LEFT].setAxisTriggerLU(m_receivedData + OffsetLX);
	m_buttons[dsButton::AXISL_TR_UP].setAxisTriggerLU(m_receivedData + OffsetLY);
	m_buttons[dsButton::AXISL_TR_RIGHT].setAxisTriggerRD(m_receivedData + OffsetLX);
	m_buttons[dsButton::AXISL_TR_DOWN].setAxisTriggerRD(m_receivedData + OffsetLY);
	m_buttons[dsButton::AXISR_TR_LEFT].setAxisTriggerLU(m_receivedData + OffsetRX);
	m_buttons[dsButton::AXISR_TR_UP].setAxisTriggerLU(m_receivedData + OffsetRY);
	m_buttons[dsButton::AXISR_TR_RIGHT].setAxisTriggerRD(m_receivedData + OffsetRX);
	m_buttons[dsButton::AXISR_TR_DOWN].setAxisTriggerRD(m_receivedData + OffsetRY);
	m_buttons[dsButton::AXISL_LEFT].setAxisLU(m_receivedData + OffsetLX);
	m_buttons[dsButton::AXISL_UP_LEFT].setAxisDUL(m_receivedData + OffsetLY, m_receivedData + OffsetLX);
	m_buttons[dsButton::AXISL_UP].setAxisLU(m_receivedData + OffsetLY);
	m_buttons[dsButton::AXISL_UP_RIGHT].setAxisDUR(m_receivedData + OffsetLY, m_receivedData + OffsetLX);
	m_buttons[dsButton::AXISL_RIGHT].setAxisRD(m_receivedData + OffsetLX);
	m_buttons[dsButton::AXISL_DOWN_RIGHT].setAxisDDR(m_receivedData + OffsetLY, m_receivedData + OffsetLX);
	m_buttons[dsButton::AXISL_DOWN].setAxisRD(m_receivedData + OffsetLY);
	m_buttons[dsButton::AXISL_DOWN_LEFT].setAxisDDL(m_receivedData + OffsetLY, m_receivedData + OffsetLX);
	m_buttons[dsButton::AXISR_LEFT].setAxisLU(m_receivedData + OffsetRX);
	m_buttons[dsButton::AXISR_UP_LEFT].setAxisDUL(m_receivedData + OffsetRY, m_receivedData + OffsetRX);
	m_buttons[dsButton::AXISR_UP].setAxisLU(m_receivedData + OffsetRY);
	m_buttons[dsButton::AXISR_UP_RIGHT].setAxisDUR(m_receivedData + OffsetRY, m_receivedData + OffsetRX);
	m_buttons[dsButton::AXISR_RIGHT].setAxisRD(m_receivedData + OffsetRX);
	m_buttons[dsButton::AXISR_DOWN_RIGHT].setAxisDDR(m_receivedData + OffsetRY, m_receivedData + OffsetRX);
	m_buttons[dsButton::AXISR_DOWN].setAxisRD(m_receivedData + OffsetRY);
	m_buttons[dsButton::AXISR_DOWN_LEFT].setAxisDDL(m_receivedData + OffsetRY, m_receivedData + OffsetRX);
	m_buttons[dsButton::TOUCHUP].setTouch(m_receivedData + OffsetTouchPadClick, 0b10, 8);
	m_buttons[dsButton::TOUCHPAD].setTouch(m_receivedData + OffsetTouchPadClick, 0b10, 0);
	m_buttons[dsButton::TOUCH1].setTouch(m_receivedData + OffsetTouchPadClick, 0b10, 1);
	m_buttons[dsButton::TOUCH2].setTouch(m_receivedData + OffsetTouchPadClick, 0b10, 2);
	m_buttons[dsButton::TOUCH3].setTouch(m_receivedData + OffsetTouchPadClick, 0b10, 3);
	m_buttons[dsButton::TOUCH4].setTouch(m_receivedData + OffsetTouchPadClick, 0b10, 4);
	m_buttons[dsButton::TOUCHL].setTouch(m_receivedData + OffsetTouchPadClick, 0b10, 5);
	m_buttons[dsButton::TOUCHR].setTouch(m_receivedData + OffsetTouchPadClick, 0b10, 6);
	m_buttons[dsButton::L2TRIGGER_33].setTrigger(m_receivedData + OffsetLeftTrigger, 48);
	m_buttons[dsButton::R2TRIGGER_33].setTrigger(m_receivedData + OffsetRightTrigger, 48);
	m_buttons[dsButton::L2TRIGGER_66].setTrigger(m_receivedData + OffsetLeftTrigger, 168);
	m_buttons[dsButton::R2TRIGGER_66].setTrigger(m_receivedData + OffsetRightTrigger, 168);
	m_buttons[dsButton::L2TRIGGER_100].setTrigger(m_receivedData + OffsetLeftTrigger, 254);
	m_buttons[dsButton::R2TRIGGER_100].setTrigger(m_receivedData + OffsetRightTrigger, 254);
	m_buttons[dsButton::L1R1].setSimultaneous(m_receivedData + OffsetL1, 0b1, m_receivedData + OffsetR1, 0b10);
	m_buttons[dsButton::L2R2].setSimultaneous(m_receivedData + OffsetL2, 0b100, m_receivedData + OffsetR2, 0b1000);
	m_buttons[dsButton::MOUSE_AXEX].SetMouseAxis(m_receivedMData);
	m_buttons[dsButton::MOUSE_AXEY].SetMouseAxis(m_receivedMData + 1);
	m_buttons[dsButton::MOUSE_LEFT].SetMouseTrigger(m_receivedMData + 2);
	m_buttons[dsButton::MOUSE_RIGHT].SetMouseTrigger(m_receivedMData + 3);
	m_buttons[dsButton::MOUSE_UP].SetMouseTrigger(m_receivedMData + 4);
	m_buttons[dsButton::MOUSE_DOWN].SetMouseTrigger(m_receivedMData + 5);
	m_buttons[dsButton::KID_LBUTTON].SetKeyboard(m_receivedMData + 6, 0b1);
	m_buttons[dsButton::KID_MBUTTON].SetKeyboard(m_receivedMData + 6, 0b10);
	m_buttons[dsButton::KID_RBUTTON].SetKeyboard(m_receivedMData + 6, 0b100);
	m_buttons[dsButton::KID_XBUTTON1].SetKeyboard(m_receivedMData + 6, 0b1000);
	m_buttons[dsButton::KID_XBUTTON2].SetKeyboard(m_receivedMData + 6, 0b10000);
	m_buttons[dsButton::KID_F1].SetKeyboard(m_receivedKData + 0, 0b1);
	m_buttons[dsButton::KID_F2].SetKeyboard(m_receivedKData + 0, 0b10);
	m_buttons[dsButton::KID_F3].SetKeyboard(m_receivedKData + 0, 0b100);
	m_buttons[dsButton::KID_F4].SetKeyboard(m_receivedKData + 0, 0b1000);
	m_buttons[dsButton::KID_F5].SetKeyboard(m_receivedKData + 0, 0b10000);
	m_buttons[dsButton::KID_F6].SetKeyboard(m_receivedKData + 0, 0b100000);
	m_buttons[dsButton::KID_F7].SetKeyboard(m_receivedKData + 0, 0b1000000);
	m_buttons[dsButton::KID_F8].SetKeyboard(m_receivedKData + 0, 0b10000000);
	m_buttons[dsButton::KID_F9].SetKeyboard(m_receivedKData + 1, 0b1);
	m_buttons[dsButton::KID_F10].SetKeyboard(m_receivedKData + 1, 0b10);
	m_buttons[dsButton::KID_F11].SetKeyboard(m_receivedKData + 1, 0b100);
	m_buttons[dsButton::KID_F12].SetKeyboard(m_receivedKData + 1, 0b1000);
	m_buttons[dsButton::KID_0].SetKeyboard(m_receivedKData + 1, 0b10000);
	m_buttons[dsButton::KID_1].SetKeyboard(m_receivedKData + 1, 0b100000);
	m_buttons[dsButton::KID_2].SetKeyboard(m_receivedKData + 1, 0b1000000);
	m_buttons[dsButton::KID_3].SetKeyboard(m_receivedKData + 1, 0b10000000);
	m_buttons[dsButton::KID_4].SetKeyboard(m_receivedKData + 2, 0b1);
	m_buttons[dsButton::KID_5].SetKeyboard(m_receivedKData + 2, 0b10);
	m_buttons[dsButton::KID_6].SetKeyboard(m_receivedKData + 2, 0b100);
	m_buttons[dsButton::KID_7].SetKeyboard(m_receivedKData + 2, 0b1000);
	m_buttons[dsButton::KID_8].SetKeyboard(m_receivedKData + 2, 0b10000);
	m_buttons[dsButton::KID_9].SetKeyboard(m_receivedKData + 2, 0b100000);
	m_buttons[dsButton::KID_OEM_MINUS].SetKeyboard(m_receivedKData + 2, 0b1000000);
	m_buttons[dsButton::KID_OEM_PLUS].SetKeyboard(m_receivedKData + 2, 0b10000000);
	m_buttons[dsButton::KID_OEM_1].SetKeyboard(m_receivedKData + 3, 0b1);
	m_buttons[dsButton::KID_OEM_2].SetKeyboard(m_receivedKData + 3, 0b10);
	m_buttons[dsButton::KID_OEM_3].SetKeyboard(m_receivedKData + 3, 0b100);
	m_buttons[dsButton::KID_OEM_4].SetKeyboard(m_receivedKData + 3, 0b1000);
	m_buttons[dsButton::KID_OEM_5].SetKeyboard(m_receivedKData + 3, 0b10000);
	m_buttons[dsButton::KID_OEM_6].SetKeyboard(m_receivedKData + 3, 0b100000);
	m_buttons[dsButton::KID_OEM_7].SetKeyboard(m_receivedKData + 3, 0b1000000);
	m_buttons[dsButton::KID_OEM_8].SetKeyboard(m_receivedKData + 3, 0b10000000);
	m_buttons[dsButton::KID_OEM_102].SetKeyboard(m_receivedKData + 4, 0b1);
	m_buttons[dsButton::KID_OEM_COMMA].SetKeyboard(m_receivedKData + 4, 0b10);
	m_buttons[dsButton::KID_OEM_PERIOD].SetKeyboard(m_receivedKData + 4, 0b100);
	m_buttons[dsButton::KID_A].SetKeyboard(m_receivedKData + 4, 0b1000);
	m_buttons[dsButton::KID_B].SetKeyboard(m_receivedKData + 4, 0b10000);
	m_buttons[dsButton::KID_C].SetKeyboard(m_receivedKData + 5, 0b1);
	m_buttons[dsButton::KID_D].SetKeyboard(m_receivedKData + 5, 0b10);
	m_buttons[dsButton::KID_E].SetKeyboard(m_receivedKData + 5, 0b100);
	m_buttons[dsButton::KID_F].SetKeyboard(m_receivedKData + 5, 0b1000);
	m_buttons[dsButton::KID_G].SetKeyboard(m_receivedKData + 5, 0b10000);
	m_buttons[dsButton::KID_H].SetKeyboard(m_receivedKData + 5, 0b100000);
	m_buttons[dsButton::KID_I].SetKeyboard(m_receivedKData + 5, 0b1000000);
	m_buttons[dsButton::KID_J].SetKeyboard(m_receivedKData + 5, 0b10000000);
	m_buttons[dsButton::KID_K].SetKeyboard(m_receivedKData + 6, 0b1);
	m_buttons[dsButton::KID_L].SetKeyboard(m_receivedKData + 6, 0b10);
	m_buttons[dsButton::KID_M].SetKeyboard(m_receivedKData + 6, 0b100);
	m_buttons[dsButton::KID_N].SetKeyboard(m_receivedKData + 6, 0b1000);
	m_buttons[dsButton::KID_O].SetKeyboard(m_receivedKData + 6, 0b10000);
	m_buttons[dsButton::KID_P].SetKeyboard(m_receivedKData + 6, 0b100000);
	m_buttons[dsButton::KID_Q].SetKeyboard(m_receivedKData + 6, 0b1000000);
	m_buttons[dsButton::KID_R].SetKeyboard(m_receivedKData + 6, 0b10000000);
	m_buttons[dsButton::KID_S].SetKeyboard(m_receivedKData + 7, 0b1);
	m_buttons[dsButton::KID_T].SetKeyboard(m_receivedKData + 7, 0b10);
	m_buttons[dsButton::KID_U].SetKeyboard(m_receivedKData + 7, 0b100);
	m_buttons[dsButton::KID_V].SetKeyboard(m_receivedKData + 7, 0b1000);
	m_buttons[dsButton::KID_W].SetKeyboard(m_receivedKData + 7, 0b10000);
	m_buttons[dsButton::KID_X].SetKeyboard(m_receivedKData + 7, 0b100000);
	m_buttons[dsButton::KID_Y].SetKeyboard(m_receivedKData + 7, 0b1000000);
	m_buttons[dsButton::KID_Z].SetKeyboard(m_receivedKData + 7, 0b10000000);
	m_buttons[dsButton::KID_ESCAPE].SetKeyboard(m_receivedKData + 8, 0b1);
	m_buttons[dsButton::KID_TAB].SetKeyboard(m_receivedKData + 8, 0b10);
	m_buttons[dsButton::KID_RETURN].SetKeyboard(m_receivedKData + 8, 0b100);
	m_buttons[dsButton::KID_SPACE].SetKeyboard(m_receivedKData + 8, 0b1000);
	m_buttons[dsButton::KID_BACK].SetKeyboard(m_receivedKData + 8, 0b10000);
	m_buttons[dsButton::KID_DELETE].SetKeyboard(m_receivedKData + 8, 0b100000);
	m_buttons[dsButton::KID_INSERT].SetKeyboard(m_receivedKData + 8, 0b1000000);
	m_buttons[dsButton::KID_NUMLOCK].SetKeyboard(m_receivedKData + 8, 0b10000000);
	m_buttons[dsButton::KID_LSHIFT].SetKeyboard(m_receivedKData + 9, 0b1);
	m_buttons[dsButton::KID_RSHIFT].SetKeyboard(m_receivedKData + 9, 0b10);
	m_buttons[dsButton::KID_LCONTROL].SetKeyboard(m_receivedKData + 9, 0b100);
	m_buttons[dsButton::KID_RCONTROL].SetKeyboard(m_receivedKData + 9, 0b1000);
	m_buttons[dsButton::KID_LWIN].SetKeyboard(m_receivedKData + 9, 0b10000);
	m_buttons[dsButton::KID_RWIN].SetKeyboard(m_receivedKData + 9, 0b100000);
	m_buttons[dsButton::KID_LMENU].SetKeyboard(m_receivedKData + 9, 0b1000000);
	m_buttons[dsButton::KID_RMENU].SetKeyboard(m_receivedKData + 9, 0b10000000);
	m_buttons[dsButton::KID_LEFT].SetKeyboard(m_receivedKData + 10, 0b1);
	m_buttons[dsButton::KID_UP].SetKeyboard(m_receivedKData + 10, 0b10);
	m_buttons[dsButton::KID_RIGHT].SetKeyboard(m_receivedKData + 10, 0b100);
	m_buttons[dsButton::KID_DOWN].SetKeyboard(m_receivedKData + 10, 0b1000);
	m_buttons[dsButton::KID_PRIOR].SetKeyboard(m_receivedKData + 10, 0b10000);
	m_buttons[dsButton::KID_NEXT].SetKeyboard(m_receivedKData + 10, 0b100000);
	m_buttons[dsButton::KID_END].SetKeyboard(m_receivedKData + 10, 0b1000000);
	m_buttons[dsButton::KID_HOME].SetKeyboard(m_receivedKData + 10, 0b10000000);
	m_buttons[dsButton::KID_NUMPAD0].SetKeyboard(m_receivedKData + 11, 0b1);
	m_buttons[dsButton::KID_NUMPAD1].SetKeyboard(m_receivedKData + 11, 0b10);
	m_buttons[dsButton::KID_NUMPAD2].SetKeyboard(m_receivedKData + 11, 0b100);
	m_buttons[dsButton::KID_NUMPAD3].SetKeyboard(m_receivedKData + 11, 0b1000);
	m_buttons[dsButton::KID_NUMPAD4].SetKeyboard(m_receivedKData + 11, 0b10000);
	m_buttons[dsButton::KID_NUMPAD5].SetKeyboard(m_receivedKData + 11, 0b100000);
	m_buttons[dsButton::KID_NUMPAD6].SetKeyboard(m_receivedKData + 11, 0b1000000);
	m_buttons[dsButton::KID_NUMPAD7].SetKeyboard(m_receivedKData + 11, 0b10000000);
	m_buttons[dsButton::KID_NUMPAD8].SetKeyboard(m_receivedKData + 12, 0b1);
	m_buttons[dsButton::KID_NUMPAD9].SetKeyboard(m_receivedKData + 12, 0b10);
	m_buttons[dsButton::KID_DIVIDE].SetKeyboard(m_receivedKData + 12, 0b100);
	m_buttons[dsButton::KID_MULTIPLY].SetKeyboard(m_receivedKData + 12, 0b1000);
	m_buttons[dsButton::KID_SUBTRACT].SetKeyboard(m_receivedKData + 12, 0b10000);
	m_buttons[dsButton::KID_ADD].SetKeyboard(m_receivedKData + 12, 0b100000);
	m_buttons[dsButton::KID_SEPARATOR].SetKeyboard(m_receivedKData + 12, 0b1000000);
	m_buttons[dsButton::KID_DECIMAL].SetKeyboard(m_receivedKData + 12, 0b10000000);
}

BOOL dsDevice::Open(HWND hWnd, bool verbose)
{
	if (verbose)
		firstflag = true;

	if (!tape.PreferredDS)
	{
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, inputloop, this, 0, &m_threadID);
		return TRUE;
	}

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

	if (tape.ActualDS == 2)
	{
		if (verbose)
			echo(I18N.ConnectController, L"DualSense", dsSerial);
		char buf[64] = { 0x20 };
		if (!HidD_GetFeature(dsHandle, buf, sizeof(buf)))
		{
			echo(I18N.FirmwareFail);

			DWORD errorcode = GetLastError();
			LPVOID lpMsgBuf;
			FormatMessage(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
			echo(L"%d = %s", errorcode, (LPTSTR)lpMsgBuf);
			LocalFree(lpMsgBuf);
			return FALSE;
		}

		WCHAR text[21];
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buf, 20, text, 21);
		text[20] = 0;
		if (verbose)
			echo(I18N.Firmware, buf[45], buf[44], text);
	}
	else if (verbose)
		echo(I18N.ConnectController, L"DualShock", dsSerial);

	//Secure send / receive buffer
	m_InputBuf = (byte*)malloc(m_inputLen);
	m_OutputBuf = (byte*)malloc(m_outputLen);
	if (m_OutputBuf)
		memset(m_OutputBuf, 0, m_outputLen);
	if (m_InputBuf)
		memset(m_InputBuf, 0, m_inputLen);

	if (tape.ActualDS == 2)
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
			m_OutputBuf[3] = 0xff;
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
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, inputloop, this, 0, &m_threadID);
	m_hThread2 = (HANDLE)_beginthreadex(NULL, 0, outputloop, this, 0, &m_threadID2);

	if (m_hThread == 0 || m_hThread2 == 0)
	{
		echo(I18N.FailedThread);
		return FALSE;
	}
	else
		SetThreadAffinityMask(m_hThread, 1);

	if (detail != 0)
		free(detail);

	SetupDiDestroyDeviceInfoList(hDevInfo);

	return TRUE;
}

BOOL dsDevice::Close()
{
	if (m_hThread)
	{
		m_threadShutdown = true;
		WaitForSingleObject(m_hThread, INFINITE);
		m_write_cv.notify_one();
		WaitForSingleObject(m_hThread2, INFINITE);
		m_threadShutdown = false;
		m_hThread = NULL;
		m_hThread2 = NULL;
		m_write_count = m_write_count2 = 0;
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

	return FALSE;
}

//Receive loop from DS4
void dsDevice::InputLoop()
{
	while (!m_threadShutdown)
	{
		bool updateflag = false;

		if (tape.PreferredDS)
		{
			if (!_read())
				break;

			if (m_receivedLength == 0)
			{
				if (tape.ActualDS == 2)
					echo(I18N.DisconnectController, L"DualSense");
				else
					echo(I18N.DisconnectController, L"DualShock");
				break;
			}

			if (!_parse(&updateflag))
			{
				if (tape.ActualDS == 2)
					echo(I18N.FailedParse, L"DualSense");
				else
					echo(I18N.FailedParse, L"DualShock");
				break;
			}

			if (firstflag)
			{
				if (tape.ActualDS == 2)
					echo(I18N.ConnectionStarted, L"DualSense");
				else
					echo(I18N.ConnectionStarted, L"DualShock");
				Write();
				firstflag = false;
			}
		}

		if (tape.MouseActive)
			_parseMouse(&updateflag);

		if (tape.KeyboardActive)
			_parseKeyboard(&updateflag);

		//Callback
		if (m_callback)
			m_callback(this, updateflag, m_callbackdata);
	}

	if (tape.PreferredDS)
	{
		m_threadShutdown = true;

		if (dsHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(dsHandle);
			dsHandle = INVALID_HANDLE_VALUE;
		}
	}
}

//Send loop to DS4
void dsDevice::OutputLoop()
{
	while (!m_threadShutdown)
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

EndOutputLoop:
	m_threadShutdown = true;

}

//Receive callback
void dsDevice::SetCallback(dsInputCallback cb, void* param)
{
	m_callback = cb;
	m_callbackdata = param;
}

WCHAR* dsDevice::GetSerial()
{
	return dsSerial;
}

//Specify the DS to connect
BOOL dsDevice::SetTargetSerial(const WCHAR* szTarget)
{
	if (lstrlenW(szTarget) + 1 > MAX_Serial_Length)
		return FALSE;
	lstrcpyW(m_TargetSerial, szTarget);

	return TRUE;
}

void dsDevice::SetLED(byte R, byte G, byte B)
{
	m_Red = R;
	m_Green = G;
	m_Blue = B;
}

void dsDevice::SetOrangeLED(byte val)
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
				if ((val == 0) && (battery < 5))
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

void dsDevice::SetWhiteLED(byte led)
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

void dsDevice::SetTriggers(int val)
{
	if ((val >= 0 && val < 4) && (m_Triggers != val))
		m_Triggers = val;
}

BOOL dsDevice::SetMoter(byte left, byte right)
{
	m_Left = left;
	m_Right = right;

	return TRUE;
}

//Send LED and Motor information
BOOL dsDevice::_prewrite()
{
	if (dsHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	if (tape.ActualDS == 2)
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
		case 1 :
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
		case 2:
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
		case 3:
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

BOOL dsDevice::_write()
{
	if (m_bBluetooth)
	{
		if (tape.ActualDS == 2)
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
				echo(I18N.FailedSendCmd, L"DS(BT)", GetLastError());
			return FALSE;
		}
	}
	ResetEvent(m_oWrite.hEvent);
	DWORD n;
	if (WriteFile(dsHandle, m_OutputBuf, m_bBluetooth ? 78 : m_outputLen, &n, &m_oWrite))
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
		echo(I18N.FailedSendCmd, m_bBluetooth ? L"DS(BT)" : L"DS(USB)", errorcode);

	echo(L"%d = %s", errorcode, (LPTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);

	return FALSE;
}

//Instruct the sending thread
BOOL dsDevice::Write()
{
	m_write_count++;
	m_write_cv.notify_one();

	return TRUE;
}

//Receive
BOOL dsDevice::_read()
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
		if (!m_threadShutdown && dsHandle != INVALID_HANDLE_VALUE)
		{
			firstflag = true;
			echo(I18N.Log_Wait_ds);
		}
		break;
	default:
		if (!m_threadShutdown && dsHandle != INVALID_HANDLE_VALUE)
			echo(I18N.FailedRecv, L"DS", errorcode);
		break;
	}

	return FALSE;
}

//CRC check of received data
BOOL dsDevice::_btcrc()
{
	unsigned int crc = crc32_16bytes(m_InputBuf, 74, 0x73D37CF3);
	unsigned int src = *(unsigned int*)&m_InputBuf[74];

	return crc == src;
}

//Analysis of received data
BOOL dsDevice::_parse(bool* updateflag)
{
	byte* buffer = m_InputBuf,
		* bufferEnd = m_InputBuf + m_receivedLength;

	if (m_bBluetooth)
	{
		if (tape.ActualDS == 2)
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
//		echo(I18N.BT_Size);
		return FALSE;
	}

	if (tape.ActualDS == 2)
	{
		//Button state
		memcpy(m_receivedData, buffer, 10);

//		m_receivedData[0] = buffer[0];
		m_receivedData[6] = 0;

		//Battery level & Touchpad
		memcpy(m_receivedData + 31, buffer + 31, 9);
		m_receivedData[52] = buffer[52];
		m_receivedData[53] = buffer[53];
		m_receivedData[54] = buffer[54];
		m_receivedData[55] = buffer[55];

		//Determine if the state is changing
		if (memcmp(m_receivedData, m_receivedLastData, MAX_Input_Length) != 0)
		{
			if (m_bBluetooth)
			{
				if (_btcrc())
				{
					*updateflag = true;
					if (m_crcerrorcount > 0)
						echo(I18N.BT_CRC, m_crcerrorcount);
					m_crcerrorcount = 0;
				}
				else
				{
					m_crcerrorcount++;
					if (m_crcerrorcount % 500 == 0)
						echo(I18N.BT_CRC, m_crcerrorcount);
				}
			}
			else
				*updateflag = true;
			if (updateflag)
				memcpy(m_receivedLastData, m_receivedData, MAX_Input_Length);
		}
	}
	else
	{
		//Button state
		m_receivedData[0] = buffer[0];
		m_receivedData[1] = buffer[1];
		m_receivedData[2] = buffer[2];
		m_receivedData[3] = buffer[3];
		m_receivedData[4] = buffer[4];
		m_receivedData[5] = buffer[5];
		m_receivedData[6] = buffer[6] & 0b11;
		m_receivedData[7] = buffer[7];
		m_receivedData[8] = buffer[8];

		//Battery level
		m_receivedData[OffsetBatteryLevel] = buffer[OffsetBatteryLevelData];

		//Gather Touch information
		int n = buffer[OffsetTouchs];
		if (n > 4)
		{
			n = 1;
		}
		byte* dst, * src;
		src = buffer + OffsetTouchs + 1;
		dst = m_receivedData + OffsetTouch;
		for (int i = 1; i <= 4; i++)
		{
			if (i == n && src + 8 < bufferEnd)
			{
				dst[0] = src[1];
				dst[1] = src[2];
				dst[2] = src[3];
				dst[3] = src[4];
				dst[4] = src[5];
				dst[5] = src[6];
				dst[6] = src[7];
				dst[7] = src[8];
			}
			src += 9;
		}

		//Determine if the state is changing
		if (memcmp(m_receivedData, m_receivedLastData, MAX_Input_Length) != 0)
		{
			*updateflag = true;
			memcpy(m_receivedLastData, m_receivedData, MAX_Input_Length);
		}
	}

	return TRUE;
}

//Analysis of Mouse received data
BOOL dsDevice::_parseMouse(bool* updateflag)
{
	GetCursorPos(&tape.mousepoint);
	if (tape.W > tape.H)
	{
		m_receivedMData[0] = (byte)min(255, ((((tape.mousepoint.x - tape.w) * tape.proportianality) + tape.w) * 255) / tape.W);
		m_receivedMData[1] = (byte)min(255, (tape.mousepoint.y * 255) / tape.H);
		m_receivedMData[2] = (byte)((tape.mousepoint.x < tape.w) ? (((tape.w - tape.mousepoint.x) * 255 * tape.proportianality) / tape.w) : 0);
		m_receivedMData[3] = (byte)((tape.mousepoint.x > tape.w) ? (((tape.mousepoint.x - tape.w) * 255 * tape.proportianality) / tape.w) : 0);
		m_receivedMData[4] = (byte)((tape.mousepoint.y < tape.h) ? (((tape.h - tape.mousepoint.y) * 255) / tape.h) : 0);
		m_receivedMData[5] = (byte)((tape.mousepoint.y > tape.h) ? (((tape.mousepoint.y - tape.h) * 255) / tape.h) : 0);
	}
	else
	{
		m_receivedMData[0] = (byte)min(255, (tape.mousepoint.x * 255) / tape.W);
		m_receivedMData[1] = (byte)min(255, ((((tape.mousepoint.y - tape.h) * tape.proportianality) + tape.h) * 255) / tape.H);
		m_receivedMData[2] = (byte)((tape.mousepoint.x < tape.w) ? (((tape.w - tape.mousepoint.x) * 255) / tape.w) : 0);
		m_receivedMData[3] = (byte)((tape.mousepoint.x > tape.w) ? (((tape.mousepoint.x - tape.w) * 255) / tape.w) : 0);
		m_receivedMData[4] = (byte)((tape.mousepoint.y < tape.h) ? (((tape.h - tape.mousepoint.y) * 255 * tape.proportianality) / tape.h) : 0);
		m_receivedMData[5] = (byte)((tape.mousepoint.y > tape.h) ? (((tape.mousepoint.y - tape.h) * 255 * tape.proportianality) / tape.h) : 0);
	}

	m_receivedMData[6] = ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1 : 0);
	m_receivedMData[6] |= (((GetAsyncKeyState(VK_MBUTTON) & 0x8000) ? 1 : 0) << 1);
	m_receivedMData[6] |= (((GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 1 : 0) << 2);
	m_receivedMData[6] |= (((GetAsyncKeyState(VK_XBUTTON1) & 0x8000) ? 1 : 0) << 3);
	m_receivedMData[6] |= (((GetAsyncKeyState(VK_XBUTTON2) & 0x8000) ? 1 : 0) << 4);

	if (memcmp(m_receivedMData, m_receivedMLastData, 7) != 0)
	{
		*updateflag = true;
		memcpy(m_receivedMLastData, m_receivedMData, 7);
	}

	return TRUE;
}

//Analysis of Keyboard received data
BOOL dsDevice::_parseKeyboard(bool* updateflag)
{
	m_receivedKData[0] = ((GetAsyncKeyState(VK_F1) & 0x8000) ? 1 : 0);
	m_receivedKData[0] |= (((GetAsyncKeyState(VK_F2) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[0] |= (((GetAsyncKeyState(VK_F3) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[0] |= (((GetAsyncKeyState(VK_F4) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[0] |= (((GetAsyncKeyState(VK_F5) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[0] |= (((GetAsyncKeyState(VK_F6) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[0] |= (((GetAsyncKeyState(VK_F7) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[0] |= (((GetAsyncKeyState(VK_F8) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[1] = ((GetAsyncKeyState(VK_F9) & 0x8000) ? 1 : 0);
	m_receivedKData[1] |= (((GetAsyncKeyState(VK_F10) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[1] |= (((GetAsyncKeyState(VK_F11) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[1] |= (((GetAsyncKeyState(VK_F12) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[1] |= (((GetAsyncKeyState(VK_0) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[1] |= (((GetAsyncKeyState(VK_1) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[1] |= (((GetAsyncKeyState(VK_2) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[1] |= (((GetAsyncKeyState(VK_3) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[2] = ((GetAsyncKeyState(VK_4) & 0x8000) ? 1 : 0);
	m_receivedKData[2] |= (((GetAsyncKeyState(VK_5) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[2] |= (((GetAsyncKeyState(VK_6) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[2] |= (((GetAsyncKeyState(VK_7) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[2] |= (((GetAsyncKeyState(VK_8) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[2] |= (((GetAsyncKeyState(VK_9) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[2] |= (((GetAsyncKeyState(VK_OEM_MINUS) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[2] |= (((GetAsyncKeyState(VK_OEM_PLUS) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[3] = ((GetAsyncKeyState(VK_OEM_1) & 0x8000) ? 1 : 0);
	m_receivedKData[3] |= (((GetAsyncKeyState(VK_OEM_2) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[3] |= (((GetAsyncKeyState(VK_OEM_3) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[3] |= (((GetAsyncKeyState(VK_OEM_4) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[3] |= (((GetAsyncKeyState(VK_OEM_5) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[3] |= (((GetAsyncKeyState(VK_OEM_6) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[3] |= (((GetAsyncKeyState(VK_OEM_7) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[3] |= (((GetAsyncKeyState(VK_OEM_8) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[4] = ((GetAsyncKeyState(VK_OEM_102) & 0x8000) ? 1 : 0);
	m_receivedKData[4] |= (((GetAsyncKeyState(VK_OEM_COMMA) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[4] |= (((GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[4] |= (((GetAsyncKeyState(VK_A) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[4] |= (((GetAsyncKeyState(VK_B) & 0x8000) ? 1 : 0) << 4);

	m_receivedKData[5] = ((GetAsyncKeyState(VK_C) & 0x8000) ? 1 : 0);
	m_receivedKData[5] |= (((GetAsyncKeyState(VK_D) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[5] |= (((GetAsyncKeyState(VK_E) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[5] |= (((GetAsyncKeyState(VK_F) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[5] |= (((GetAsyncKeyState(VK_G) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[5] |= (((GetAsyncKeyState(VK_H) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[5] |= (((GetAsyncKeyState(VK_I) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[5] |= (((GetAsyncKeyState(VK_J) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[6] = ((GetAsyncKeyState(VK_K) & 0x8000) ? 1 : 0);
	m_receivedKData[6] |= (((GetAsyncKeyState(VK_L) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[6] |= (((GetAsyncKeyState(VK_M) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[6] |= (((GetAsyncKeyState(VK_N) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[6] |= (((GetAsyncKeyState(VK_O) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[6] |= (((GetAsyncKeyState(VK_P) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[6] |= (((GetAsyncKeyState(VK_Q) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[6] |= (((GetAsyncKeyState(VK_R) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[7] = ((GetAsyncKeyState(VK_S) & 0x8000) ? 1 : 0);
	m_receivedKData[7] |= (((GetAsyncKeyState(VK_T) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[7] |= (((GetAsyncKeyState(VK_U) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[7] |= (((GetAsyncKeyState(VK_V) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[7] |= (((GetAsyncKeyState(VK_W) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[7] |= (((GetAsyncKeyState(VK_X) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[7] |= (((GetAsyncKeyState(VK_Y) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[7] |= (((GetAsyncKeyState(VK_Z) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[8] = ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) ? 1 : 0);
	m_receivedKData[8] |= (((GetAsyncKeyState(VK_TAB) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[8] |= (((GetAsyncKeyState(VK_RETURN) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[8] |= (((GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[8] |= (((GetAsyncKeyState(VK_BACK) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[8] |= (((GetAsyncKeyState(VK_DELETE) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[8] |= (((GetAsyncKeyState(VK_INSERT) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[8] |= (((GetAsyncKeyState(VK_NUMLOCK) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[9] = ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) ? 1 : 0);
	m_receivedKData[9] |= (((GetAsyncKeyState(VK_RSHIFT) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[9] |= (((GetAsyncKeyState(VK_LCONTROL) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[9] |= (((GetAsyncKeyState(VK_RCONTROL) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[9] |= (((GetAsyncKeyState(VK_LWIN) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[9] |= (((GetAsyncKeyState(VK_RWIN) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[9] |= (((GetAsyncKeyState(VK_LMENU) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[9] |= (((GetAsyncKeyState(VK_RMENU) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[10] = ((GetAsyncKeyState(VK_LEFT) & 0x8000) ? 1 : 0);
	m_receivedKData[10] |= (((GetAsyncKeyState(VK_UP) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[10] |= (((GetAsyncKeyState(VK_RIGHT) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[10] |= (((GetAsyncKeyState(VK_DOWN) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[10] |= (((GetAsyncKeyState(VK_PRIOR) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[10] |= (((GetAsyncKeyState(VK_NEXT) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[10] |= (((GetAsyncKeyState(VK_END) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[10] |= (((GetAsyncKeyState(VK_HOME) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[11] = ((GetAsyncKeyState(VK_NUMPAD0) & 0x8000) ? 1 : 0);
	m_receivedKData[11] |= (((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[11] |= (((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[11] |= (((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[11] |= (((GetAsyncKeyState(VK_NUMPAD4) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[11] |= (((GetAsyncKeyState(VK_NUMPAD5) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[11] |= (((GetAsyncKeyState(VK_NUMPAD6) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[11] |= (((GetAsyncKeyState(VK_NUMPAD7) & 0x8000) ? 1 : 0) << 7);

	m_receivedKData[12] = ((GetAsyncKeyState(VK_NUMPAD8) & 0x8000) ? 1 : 0);
	m_receivedKData[12] |= (((GetAsyncKeyState(VK_NUMPAD9) & 0x8000) ? 1 : 0) << 1);
	m_receivedKData[12] |= (((GetAsyncKeyState(VK_DIVIDE) & 0x8000) ? 1 : 0) << 2);
	m_receivedKData[12] |= (((GetAsyncKeyState(VK_MULTIPLY) & 0x8000) ? 1 : 0) << 3);
	m_receivedKData[12] |= (((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) ? 1 : 0) << 4);
	m_receivedKData[12] |= (((GetAsyncKeyState(VK_ADD) & 0x8000) ? 1 : 0) << 5);
	m_receivedKData[12] |= (((GetAsyncKeyState(VK_SEPARATOR) & 0x8000) ? 1 : 0) << 6);
	m_receivedKData[12] |= (((GetAsyncKeyState(VK_DECIMAL) & 0x8000) ? 1 : 0) << 7);

	if (memcmp(m_receivedKData, m_receivedKLastData, 13) != 0)
	{
		*updateflag = true;
		memcpy(m_receivedKLastData, m_receivedKData, 13);
	}

	return TRUE;
}

#pragma region get state

BOOL dsDevice::isBT()
{
	return m_bBluetooth;
}

int dsDevice::Battery()
{
	battery = (m_receivedData[OffsetBatteryLevel] & 0x0F) * 10;
	return battery;
}

BOOL dsDevice::BatteryCharge()
{
	return m_receivedData[OffsetBatteryLevel] & 0x10 ? true : false;
}

BOOL dsDevice::BatteryFull()
{
	return m_receivedData[OffsetBatteryLevel] & 0x20 ? true : false;
}

void dsDevice::DisconnectBT()
{
	if (!Active() || !isBT())
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

dsButton* dsDevice::GetButton(dsButtonID id)
{
	if (id >= dsButtonID::none && id < dsButtonID::button_Count)
		return &m_buttons[id];

	return &m_buttons[0];
}

BOOL dsDevice::TouchActive(int i)
{
	if (i != 0)i = 4;

	return (m_receivedData[OffsetTouch + i] & 0b10000000) == 0;
}

BYTE dsDevice::TouchId(int i)
{
	if (i != 0)i = 4;

	return m_receivedData[OffsetTouch + i] & 0b1111111;
}

int dsDevice::TouchX(int i)
{
	if (i != 0)i = 4;

	return ((m_receivedData[OffsetTouch + 2 + i] & 0x0F) << 8) | m_receivedData[OffsetTouch + 1 + i];
}

int dsDevice::TouchY(int i)
{
	if (i != 0)i = 4;

	return (m_receivedData[OffsetTouch + 2 + i] >> 4) | (m_receivedData[OffsetTouch + 3 + i] << 4);
}

void dsDevice::String()
{
	wchar_t buf[MAX_PATH];
	wchar_t* offset = buf;

	if (tape.ActualDS == 2)
		offset += wsprintfW(offset, L"%3d:  %d (%d,%d)    %3d:  %d (%d,%d)"
			, TouchId(0), TouchActive(0), TouchX(0), TouchY(0)
			, TouchId(1), TouchActive(1), TouchX(1), TouchY(1));
	else
		offset += wsprintfW(offset, L"%d (%d,%d)    %d (%d,%d)"
			, TouchActive(0), TouchX(0), TouchY(0)
			, TouchActive(1), TouchX(1), TouchY(1));

	if (buf != offset)
		echo(buf);
}

#pragma endregion
