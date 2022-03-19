#include "stdafx.h"
#include "ViGEm.h"

ViGEm::ViGEm()
{
}

ViGEm::~ViGEm()
{
}

const WCHAR* ViGEm::ViGEmButtons()
{
	return ViGEmButtonsString;
}

void ViGEm::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}

void ViGEm::InitClient(bool verbose)
{
	if (vigem_connected)
		return;

	client = vigem_alloc();
	if (client == nullptr)
	{
		echo(I18N.ViGEm_Memory_allocating_error);
		return;
	}

	err = vigem_connect(client);
	if (!VIGEM_SUCCESS(err))
	{
		echo(I18N.ViGEm_Bus_connection_failed, ViGEmError(err));
		return;
	}
	else
		vigem_connected = true;

	if (verbose)
		echo(L"ViGEm: client connected");

	InitPad(verbose);
}

void ViGEm::InitPad(bool verbose)
{
	if (tape.ViGEmPaused)
		return;

	switch (tape.DesiredVirtualPad)
	{
	case 1: //Xbox360
	{
		pad = vigem_target_x360_alloc();
		err = vigem_target_add(client, pad);
		if (!VIGEM_SUCCESS(err))
		{
			vigem_free(client);
			echo(I18N.ViGEm_Target_plugin_failed, ViGEmError(err));
			return;
		}

		XUSB_REPORT_INIT(&report_X360);
		break;
	}
	case 2: //DS4
	{
		pad = vigem_target_ds4_alloc();
		err = vigem_target_add(client, pad);
		if (!VIGEM_SUCCESS(err))
		{
			vigem_free(client);
			echo(I18N.ViGEm_Target_plugin_failed, ViGEmError(err));
			return;
		}

		DS4_REPORT_INIT(&report_DS4);
		break;
	}
	}
	if (verbose)
		echo(L"ViGEm: Pad added");
}

void ViGEm::CloseClient(bool verbose)
{
	if (vigem_connected)
	{
		vigem_connected = false;
		tape.ViGEmActive = false;
		ClosePad();
		vigem_disconnect(client);
		vigem_free(client);
	}
	if (verbose)
		echo(L"ViGEm: client removed");
}

void ViGEm::ClosePad(bool verbose)
{
	vigem_target_remove(client, pad);
	vigem_target_free(pad);
	if (verbose)
		echo(L"ViGEm: Pad removed");
}

void ViGEm::LoadDevice(dsDevice* ds, vJoyDevice* vjoy)
{
	for (int i = 0; i < 24; i++) { m_vj[i] = { 0 }; }

	switch (tape.DesiredVirtualPad)
	{
	case 1:
	{
		for (int i = 0; i < 24; i++)
		{
			m_ds[i] = (tape.dstarget_X360[i]) ? ds->GetButton((dsButtonID)tape.dstarget_X360[i]) : 0;
			m_vj[i] = (tape.vjtarget_X360[i]) ? vjoy->GetButton((vJoyButtonID)tape.vjtarget_X360[i]) : 0;
		}
		break;
	}
	case 2:
	{
		for (int i = 0; i < 24; i++)
		{
			m_ds[i] = (tape.dstarget_DS4[i]) ? ds->GetButton((dsButtonID)tape.dstarget_DS4[i]) : 0;
			m_vj[i] = (tape.vjtarget_DS4[i]) ? vjoy->GetButton((vJoyButtonID)tape.vjtarget_DS4[i]) : 0;
		}
		break;
	}
	}
}

void ViGEm::Run()
{
	if (tape.ViGEmPaused)
		return;

	ViGEmButtonsString[0] = 0;
	WCHAR* head = ViGEmButtonsString;

	switch (tape.DesiredVirtualPad)
	{
	case 1: //Xbox360
	{
	    unsigned short wButtons = 0x0;

		if ((tape.target_X360[0]) ? ((m_vj[0]) ? (m_vj[0]->isPushed()) : false) : (m_ds[0]) ? (m_ds[0]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_LEFT_THUMB; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_LEFT_THUMB)); }				//9
		if ((tape.target_X360[1]) ? ((m_vj[1]) ? (m_vj[1]->isPushed()) : false) : (m_ds[1]) ? (m_ds[1]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_DPAD_LEFT; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_DPAD_LEFT)); }					//<
		if ((tape.target_X360[2]) ? ((m_vj[2]) ? (m_vj[2]->isPushed()) : false) : (m_ds[2]) ? (m_ds[2]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_DPAD_UP; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_DPAD_UP)); }						//^
		if ((tape.target_X360[3]) ? ((m_vj[3]) ? (m_vj[3]->isPushed()) : false) : (m_ds[3]) ? (m_ds[3]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_DPAD_RIGHT; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_DPAD_RIGHT)); }				//>
		if ((tape.target_X360[4]) ? ((m_vj[4]) ? (m_vj[4]->isPushed()) : false) : (m_ds[4]) ? (m_ds[4]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_DPAD_DOWN; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_DPAD_DOWN)); }					//v
		if ((tape.target_X360[5]) ? ((m_vj[5]) ? (m_vj[5]->isPushed()) : false) : (m_ds[5]) ? (m_ds[5]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_BACK; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_BACK)); }							//7
		if ((tape.target_X360[6]) ? ((m_vj[6]) ? (m_vj[6]->isPushed()) : false) : (m_ds[6]) ? (m_ds[6]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_START; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_START)); }							//8
		if ((tape.target_X360[7]) ? ((m_vj[7]) ? (m_vj[7]->isPushed()) : false) : (m_ds[7]) ? (m_ds[7]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_X; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_X)); }									//3
		if ((tape.target_X360[8]) ? ((m_vj[8]) ? (m_vj[8]->isPushed()) : false) : (m_ds[8]) ? (m_ds[8]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_Y; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_Y)); }									//4
		if ((tape.target_X360[9]) ? ((m_vj[9]) ? (m_vj[9]->isPushed()) : false) : (m_ds[9]) ? (m_ds[9]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_B; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_B)); }									//2
		if ((tape.target_X360[10]) ? ((m_vj[10]) ? (m_vj[10]->isPushed()) : false) : (m_ds[10]) ? (m_ds[10]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_A; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_A)); }							//1
		if ((tape.target_X360[11]) ? ((m_vj[11]) ? (m_vj[11]->isPushed()) : false) : (m_ds[11]) ? (m_ds[11]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_RIGHT_THUMB; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_RIGHT_THUMB)); }		//10
		if ((tape.target_X360[12]) ? ((m_vj[12]) ? (m_vj[12]->isPushed()) : false) : (m_ds[12]) ? (m_ds[12]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_GUIDE; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_GUIDE)); }					//No
		if ((tape.target_X360[14]) ? ((m_vj[14]) ? (m_vj[14]->isPushed()) : false) : (m_ds[14]) ? (m_ds[14]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_LEFT_SHOULDER; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_LEFT_SHOULDER)); }	//5
		if ((tape.target_X360[15]) ? ((m_vj[15]) ? (m_vj[15]->isPushed()) : false) : (m_ds[15]) ? (m_ds[15]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_RIGHT_SHOULDER; head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_RIGHT_SHOULDER)); }	//6

		report_X360.wButtons = wButtons;

		if (tape.target_X360[18]) { if (m_vj[18]) { report_X360.bLeftTrigger = (m_vj[18]->isPushed()) ? m_vj[18]->GetValByte() : 0; } }	//-Z
		else { if (m_ds[18]) { report_X360.bLeftTrigger = (m_ds[18]->isPushed()) ? m_ds[18]->GetVal() : 0; } }
		if (tape.target_X360[19]) { if (m_vj[19]) { report_X360.bRightTrigger = (m_vj[19]->isPushed()) ? m_vj[19]->GetValByte() : 0; } }	//+Z
		else { if (m_ds[19]) { report_X360.bRightTrigger = (m_ds[19]->isPushed()) ? m_ds[19]->GetVal() : 0; } }
		if (tape.target_X360[20]) { if (m_vj[20]) { report_X360.sThumbLX = (m_vj[20]->isPushed()) ? (((m_vj[20]->GetValByte() + 1) * 256) - 32769) : 0; } }	//X
		else { if (m_ds[20]) { report_X360.sThumbLX = (m_ds[20]->isPushed()) ? (((m_ds[20]->GetVal() + 1) * 256) - 32769) : 0; } }
		if (tape.target_X360[21]) { if (m_vj[21]) { report_X360.sThumbLY = (m_vj[21]->isPushed()) ? (((m_vj[21]->GetValByte() + 1) * 256) - 32769) : 0; } }	//Y
		else { if (m_ds[21]) { report_X360.sThumbLY = (m_ds[21]->isPushed()) ? (((m_ds[21]->GetVal() + 1) * 256) - 32769) : 0; } }
		if (tape.target_X360[22]) { if (m_vj[22]) { report_X360.sThumbRX = (m_vj[22]->isPushed()) ? (((m_vj[22]->GetValByte() + 1) * 256) - 32769) : 0; } }	//RX
		else { if (m_ds[22]) { report_X360.sThumbRX = (m_ds[22]->isPushed()) ? (((m_ds[22]->GetVal() + 1) * 256) - 32769) : 0; } }
		if (tape.target_X360[23]) { if (m_vj[23]) { report_X360.sThumbRY = (m_vj[23]->isPushed()) ? (((m_vj[23]->GetValByte() + 1) * 256) - 32769) : 0; } }	//RY
		else { if (m_ds[23]) { report_X360.sThumbRY = (m_ds[23]->isPushed()) ? (((m_ds[23]->GetVal() + 1) * 256) - 32769) : 0; } }

		if (report_X360.bLeftTrigger) { head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_LEFT_TRIGGER)); }
		if (report_X360.bRightTrigger) { head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_RIGHT_TRIGGER)); }
		if (report_X360.sThumbLX) { head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_LEFT_X)); }
		if (report_X360.sThumbLY) { head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_LEFT_Y)); }
		if (report_X360.sThumbRX) { head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_RIGHT_X)); }
		if (report_X360.sThumbRY) { head += swprintf_s(head, MAX_PATH, L"%s ", X360_String(XUSB_GAMEPAD_RIGHT_Y)); }

		vigem_target_x360_update(client, pad, report_X360);
		break;
	}
	case 2: //DS4
	{
		unsigned short wButtons = 0x0;
		unsigned long dButtons = 0x0;
		byte sButtons = 0x0;

		if ((tape.target_DS4[0]) ? ((m_vj[0]) ? (m_vj[0]->isPushed()) : false) : (m_ds[0]) ? (m_ds[0]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_THUMB_LEFT; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_THUMB_LEFT)); }						//11
		if ((tape.target_DS4[1]) ? ((m_vj[1]) ? (m_vj[1]->isPushed()) : false) : (m_ds[1]) ? (m_ds[1]->isPushed()) : false) { dButtons = dButtons | 0x01; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_WEST)); }											//<
		if ((tape.target_DS4[2]) ? ((m_vj[2]) ? (m_vj[2]->isPushed()) : false) : (m_ds[2]) ? (m_ds[2]->isPushed()) : false) { dButtons = dButtons | 0x02; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_NORTH)); }											//^
		if ((tape.target_DS4[3]) ? ((m_vj[3]) ? (m_vj[3]->isPushed()) : false) : (m_ds[3]) ? (m_ds[3]->isPushed()) : false) { dButtons = dButtons | 0x04; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_EAST)); }											//>
		if ((tape.target_DS4[4]) ? ((m_vj[4]) ? (m_vj[4]->isPushed()) : false) : (m_ds[4]) ? (m_ds[4]->isPushed()) : false) { dButtons = dButtons | 0x08; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_SOUTH)); }											//v
		if ((tape.target_DS4[5]) ? ((m_vj[5]) ? (m_vj[5]->isPushed()) : false) : (m_ds[5]) ? (m_ds[5]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_SHARE; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_SHARE)); }								//9
		if ((tape.target_DS4[6]) ? ((m_vj[6]) ? (m_vj[6]->isPushed()) : false) : (m_ds[6]) ? (m_ds[6]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_OPTIONS; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_OPTIONS)); }							//10
		if ((tape.target_DS4[7]) ? ((m_vj[7]) ? (m_vj[7]->isPushed()) : false) : (m_ds[7]) ? (m_ds[7]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_SQUARE; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_SQUARE)); }								//1
		if ((tape.target_DS4[8]) ? ((m_vj[8]) ? (m_vj[8]->isPushed()) : false) : (m_ds[8]) ? (m_ds[8]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_TRIANGLE; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_TRIANGLE)); }							//4
		if ((tape.target_DS4[9]) ? ((m_vj[9]) ? (m_vj[9]->isPushed()) : false) : (m_ds[9]) ? (m_ds[9]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_CIRCLE; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_CIRCLE)); }								//3
		if ((tape.target_DS4[10]) ? ((m_vj[10]) ? (m_vj[10]->isPushed()) : false) : (m_ds[10]) ? (m_ds[10]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_CROSS; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_CROSS)); }							//2
		if ((tape.target_DS4[11]) ? ((m_vj[11]) ? (m_vj[11]->isPushed()) : false) : (m_ds[11]) ? (m_ds[11]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_THUMB_RIGHT; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_THUMB_RIGHT)); }				//12
		if ((tape.target_DS4[12]) ? ((m_vj[12]) ? (m_vj[12]->isPushed()) : false) : (m_ds[12]) ? (m_ds[12]->isPushed()) : false) { sButtons = sButtons | DS4_SPECIAL_BUTTON_PS; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_SPECIAL_BUTTON_PS)); }				//13
		if ((tape.target_DS4[13]) ? ((m_vj[13]) ? (m_vj[13]->isPushed()) : false) : (m_ds[13]) ? (m_ds[13]->isPushed()) : false) { sButtons = sButtons | DS4_SPECIAL_BUTTON_TOUCHPAD; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_SPECIAL_BUTTON_TOUCHPAD)); }	//14
		if ((tape.target_DS4[14]) ? ((m_vj[14]) ? (m_vj[14]->isPushed()) : false) : (m_ds[14]) ? (m_ds[14]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_SHOULDER_LEFT; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_SHOULDER_LEFT)); }			//5
		if ((tape.target_DS4[15]) ? ((m_vj[15]) ? (m_vj[15]->isPushed()) : false) : (m_ds[15]) ? (m_ds[15]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_SHOULDER_RIGHT; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_SHOULDER_RIGHT)); }		//6
		if ((tape.target_DS4[16]) ? ((m_vj[16]) ? (m_vj[16]->isPushed()) : false) : (m_ds[16]) ? (m_ds[16]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_TRIGGER_LEFT; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_TRIGGER_LEFT)); }			//7
		if ((tape.target_DS4[17]) ? ((m_vj[17]) ? (m_vj[17]->isPushed()) : false) : (m_ds[17]) ? (m_ds[17]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_TRIGGER_RIGHT; head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_TRIGGER_RIGHT)); }			//8

		report_DS4.wButtons = wButtons;
		report_DS4.bSpecial = sButtons;

		switch (dButtons)
		{
		case 0x01: { Dpad = DS4_BUTTON_DPAD_WEST;break; }
		case 0x03: { Dpad = DS4_BUTTON_DPAD_NORTHWEST;break; }
		case 0x02: { Dpad = DS4_BUTTON_DPAD_NORTH;break; }
		case 0x06: { Dpad = DS4_BUTTON_DPAD_NORTHEAST;break; }
		case 0x04: { Dpad = DS4_BUTTON_DPAD_EAST;break; }
		case 0x0C: { Dpad = DS4_BUTTON_DPAD_SOUTHEAST;break; }
		case 0x08: { Dpad = DS4_BUTTON_DPAD_SOUTH;break; }
		case 0x09: { Dpad = DS4_BUTTON_DPAD_SOUTHWEST;break; }
		default: { Dpad = DS4_BUTTON_DPAD_NONE; }
		}

		DS4_SET_DPAD(&report_DS4, Dpad);

		if (tape.target_DS4[18]) { if (m_vj[18]) { report_DS4.bTriggerL = (m_vj[18]->isPushed()) ? m_vj[18]->GetValByte() : 0; } }	//RX
		else { if (m_ds[18]) { report_DS4.bTriggerL = (m_ds[18]->isPushed()) ? m_ds[18]->GetVal() : 0; } }
		if (tape.target_DS4[19]) { if (m_vj[19]) { report_DS4.bTriggerR = (m_vj[19]->isPushed()) ? m_vj[19]->GetValByte() : 0; } }	//RY
		else { if (m_ds[19]) { report_DS4.bTriggerR = (m_ds[19]->isPushed()) ? m_ds[19]->GetVal() : 0; } }
		if (tape.target_DS4[20]) { if (m_vj[20]) { report_DS4.bThumbLX = (m_vj[20]->isPushed()) ? m_vj[20]->GetValByte() : 127; } }	//X
		else { if (m_ds[20]) { report_DS4.bThumbLX = (m_ds[20]->isPushed()) ? m_ds[20]->GetVal() : 127; } }
		if (tape.target_DS4[21]) { if (m_vj[21]) { report_DS4.bThumbLY = (m_vj[21]->isPushed()) ? m_vj[21]->GetValByte() : 127; } }	//Y
		else { if (m_ds[21]) { report_DS4.bThumbLY = (m_ds[21]->isPushed()) ? m_ds[21]->GetVal() : 127; } }
		if (tape.target_DS4[22]) { if (m_vj[22]) { report_DS4.bThumbRX = (m_vj[22]->isPushed()) ? m_vj[22]->GetValByte() : 127; } }	//Z
		else { if (m_ds[22]) { report_DS4.bThumbRX = (m_ds[22]->isPushed()) ? m_ds[22]->GetVal() : 127; } }
		if (tape.target_DS4[23]) { if (m_vj[23]) { report_DS4.bThumbRY = (m_vj[23]->isPushed()) ? m_vj[23]->GetValByte() : 127; } }	//RZ
		else { if (m_ds[23]) { report_DS4.bThumbRY = (m_ds[23]->isPushed()) ? m_ds[23]->GetVal() : 127; } }

		if (report_DS4.bTriggerL) { head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_LEFT_TR)); }
		if (report_DS4.bTriggerR) { head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_BUTTON_RIGHT_TR)); }
		if (report_DS4.bThumbLX != 127) { head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_THUMB_LEFT_X)); }
		if (report_DS4.bThumbLY != 127) { head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_THUMB_LEFT_Y)); }
		if (report_DS4.bThumbRX != 127) { head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_THUMB_RIGHT_X)); }
		if (report_DS4.bThumbRY != 127) { head += swprintf_s(head, MAX_PATH, L"%s ", DS4_String(DS4_THUMB_RIGHT_Y)); }

		vigem_target_ds4_update(client, pad, report_DS4);
		break;
	}
	}

	return;
}

void ViGEm::ViGEmStates()
{
	vgState = ViGEmState();
}

int ViGEm::GetViGEmState()
{
	return vgState;
}

int ViGEm::ViGEmState(bool verbose)
{
	char ViGEmState = -1;
	
	std::wstring devconpath = L"Devcon.exe status Nefarius\\ViGEmBus\\Gen1";
	std::wstring devconcmd = LaunchCmd(devconpath.c_str());

	if (FindInString(devconcmd, L"No matching devices found"))
		ViGEmState = 0;
	if (FindInString(devconcmd, L"Driver is running"))
		ViGEmState = 1;
	if (FindInString(devconcmd, L"Device is disabled"))
		ViGEmState = 2;

	if (verbose)
		switch (ViGEmState)
		{
		case 0: { echo(L"ViGEm driver is uninstalled"); break; }
		case 1: { echo(L"ViGEm driver is runing"); break; }
		case 2: { echo(L"ViGEm driver is disabled"); break; }
		default: { echo(L"ViGEm state unknown"); }
		}

	return ViGEmState;
}

BOOL ViGEm::ViGEmInstall(bool verbose)
{
	if (ViGEmState() > 0)
	{
		if (verbose)
			echo(L"ViGEm driver is already installed");
		return TRUE;
	}

	std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName;

	if (ExtractEmbededResource(installpath, IDR_VIGEMBUS_ZIP, true))
	{
		std::wstring devconpath = L"Devcon.exe install \"" + PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\ViGEmBus\\ViGEmBus.inf\" Nefarius\\ViGEmBus\\Gen1";
		LaunchCmd(devconpath.c_str());

		if (ViGEmState() == 1)
		{
			echo(I18N.ViGEm_driver_installed);
			return TRUE;
		}
	}
	echo(I18N.ViGEm_driver_instalation_failed);

	return FALSE;
}

BOOL ViGEm::ViGEmUninstall(bool verbose)
{
	BOOL ViGEmUninstall = FALSE;

	if (ViGEmState() > 0)
	{
		{
			std::wstring devconpath = L"Devcon.exe remove Nefarius\\ViGEmBus\\Gen1";
			LaunchCmd(devconpath.c_str());
		}

		if (ViGEmState() < 1)
		{
			echo(I18N.ViGEm_driver_uninstalled);
			ViGEmUninstall = TRUE;
		}
		else
			echo(I18N.ViGEm_driver_uninstalation_failed);
	}
	else
	{
		if (verbose)
			echo(L"ViGEm driver is already uninstalled");
		ViGEmUninstall = TRUE;
	}

	std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\ViGEmBus\0\0";
	std::filesystem::remove_all(installpath);

	std::wstring prfdirpath = PrfPath() + L"/" + tape.ProgramFilesDirName;
	prfdirpath = ReplaceInString(prfdirpath, L"\\", '/');
	RemoveDirectoryW(prfdirpath.c_str());

	return ViGEmUninstall;
}

BOOL ViGEm::ViGEmEnable(bool verbose)
{
	int hdState = ViGEmState();

	if (hdState == 0)
	{
		if (verbose)
			echo(L"ViGEm driver is not installed");
		return FALSE;
	}
	else if (hdState == 1)
	{
		if (verbose)
			echo(L"ViGEm driver is already running");
		return TRUE;
	}

	std::wstring devconpath = L"Devcon.exe enable Nefarius\\ViGEmBus\\Gen1";
	LaunchCmd(devconpath.c_str());

	if (ViGEmState() == 1)
	{
		if (verbose)
			echo(L"ViGEm driver enabled");
		return TRUE;
	}

	if (verbose)
		echo(L"ViGEm driver enabling failed");

	return FALSE;
}

BOOL ViGEm::ViGEmDisable(bool verbose)
{
	int hdState = ViGEmState();

	if (hdState == 0)
	{
		if (verbose)
			echo(L"ViGEm driver is not installed");
		return FALSE;
	}
	else if (hdState == 2)
	{
		if (verbose)
			echo(L"ViGEm driver is already disabled");
		return TRUE;
	}

	std::wstring devconpath = L"Devcon.exe disable Nefarius\\ViGEmBus\\Gen1";
	LaunchCmd(devconpath.c_str());

	if (ViGEmState() == 2)
	{
		if (verbose)
			echo(L"ViGEm driver disabled");
		return TRUE;
	}

	if (verbose)
		echo(L"ViGEm driver disabling failed");

	return FALSE;
}

std::wstring ViGEm::ViGEmError(VIGEM_ERROR err)
{
	switch (err)
	{
	case VIGEM_ERROR_NONE: return L"none";
	case VIGEM_ERROR_ALREADY_CONNECTED: return L"already connected";
	case VIGEM_ERROR_BUS_ACCESS_FAILED: return L"bus access failed";
	case VIGEM_ERROR_BUS_ALREADY_CONNECTED: return L"bus already connected";
	case VIGEM_ERROR_BUS_INVALID_HANDLE: return L"bus invalid handle";
	case VIGEM_ERROR_BUS_NOT_FOUND: return L"bus not found";
	case VIGEM_ERROR_BUS_VERSION_MISMATCH: return L"bus version mismatch";
	case VIGEM_ERROR_CALLBACK_ALREADY_REGISTERED: return L"callback already registered";
	case VIGEM_ERROR_CALLBACK_NOT_FOUND: return L"callback not found";
	case VIGEM_ERROR_INVALID_TARGET: return L"invalid target";
	case VIGEM_ERROR_NO_FREE_SLOT: return L"no free slot";
	case VIGEM_ERROR_REMOVAL_FAILED: return L"removal failed";
	case VIGEM_ERROR_TARGET_NOT_PLUGGED_IN: return L"target not plugged in";
	case VIGEM_ERROR_TARGET_UNINITIALIZED: return L"target uninitialized";
	case VIGEM_ERROR_XUSB_USERINDEX_OUT_OF_RANGE: return L"xusb userindex out of range";
	default: return L"invalid code returned by ViGEm";
	}
}

WCHAR* ViGEm::X360_String(int id)
{
	switch (id)
	{
	case XUSB_GAMEPAD_LEFT_X: return I18N.vJoy_X;
	case XUSB_GAMEPAD_LEFT_Y: return I18N.vJoy_Y;
	case XUSB_GAMEPAD_RIGHT_X: return I18N.vJoy_RX;
	case XUSB_GAMEPAD_RIGHT_Y: return I18N.vJoy_RY;
	case XUSB_GAMEPAD_LEFT_THUMB: return I18N.Gamepad_LEFT_STICK;
	case XUSB_GAMEPAD_DPAD_LEFT: return I18N.Button_DPAD_LEFT;
	case XUSB_GAMEPAD_DPAD_UP: return I18N.Button_DPAD_UP;
	case XUSB_GAMEPAD_DPAD_RIGHT: return I18N.Button_DPAD_RIGHT;
	case XUSB_GAMEPAD_DPAD_DOWN: return I18N.Button_DPAD_DOWN;
	case XUSB_GAMEPAD_BACK: return I18N.Gamepad_BACK;
	case XUSB_GAMEPAD_START: return I18N.Gamepad_START;
	case XUSB_GAMEPAD_X: return I18N.Gamepad_X;
	case XUSB_GAMEPAD_Y: return I18N.Gamepad_Y;
	case XUSB_GAMEPAD_B: return I18N.Gamepad_B;
	case XUSB_GAMEPAD_A: return I18N.Gamepad_A;
	case XUSB_GAMEPAD_RIGHT_THUMB: return I18N.Gamepad_RIGHT_STICK;
	case XUSB_GAMEPAD_GUIDE: return I18N.Gamepad_GUIDE;
	case XUSB_GAMEPAD_LEFT_SHOULDER: return I18N.Gamepad_LEFT_BUMPER;
	case XUSB_GAMEPAD_RIGHT_SHOULDER: return I18N.Gamepad_RIGHT_BUMPER;
	case XUSB_GAMEPAD_LEFT_TRIGGER: return I18N.Gamepad_LEFT_TRIGGER;
	case XUSB_GAMEPAD_RIGHT_TRIGGER: return I18N.Gamepad_RIGHT_TRIGGER;
	default: return WCHARI(L"???");
	}
}

WCHAR* ViGEm::DS4_String(int id)
{
	switch (id)
	{
	case DS4_THUMB_LEFT_X: return I18N.vJoy_X;
	case DS4_THUMB_LEFT_Y: return I18N.vJoy_Y;
	case DS4_THUMB_RIGHT_X: return I18N.vJoy_Z;
	case DS4_THUMB_RIGHT_Y: return I18N.vJoy_RZ;
	case DS4_BUTTON_THUMB_LEFT: return I18N.Button_L3;
	case DS4_BUTTON_WEST: return I18N.Button_DPAD_LEFT;
	case DS4_BUTTON_NORTH: return I18N.Button_DPAD_UP;
	case DS4_BUTTON_EAST: return I18N.Button_DPAD_RIGHT;
	case DS4_BUTTON_SOUTH: return I18N.Button_DPAD_DOWN;
	case DS4_BUTTON_SHARE: return I18N.Button_SHARE;
	case DS4_BUTTON_OPTIONS: return I18N.Button_OPTIONS;
	case DS4_BUTTON_SQUARE: return I18N.Button_SQUARE;
	case DS4_BUTTON_TRIANGLE: return I18N.Button_TRIANGLE;
	case DS4_BUTTON_CIRCLE: return I18N.Button_CIRCLE;
	case DS4_BUTTON_CROSS: return I18N.Button_CROSS;
	case DS4_BUTTON_THUMB_RIGHT: return I18N.Button_R3;
	case DS4_SPECIAL_BUTTON_PS: return I18N.Button_PS;
	case DS4_SPECIAL_BUTTON_TOUCHPAD: return I18N.Button_TOUCH;
	case DS4_BUTTON_SHOULDER_LEFT: return I18N.Button_L1;
	case DS4_BUTTON_SHOULDER_RIGHT: return I18N.Button_R1;
	case DS4_BUTTON_TRIGGER_LEFT: return I18N.Button_L2;
	case DS4_BUTTON_TRIGGER_RIGHT: return I18N.Button_R2;
	case DS4_BUTTON_LEFT_TR: return I18N.Button_L2TRIGGER;
	case DS4_BUTTON_RIGHT_TR: return I18N.Button_R2TRIGGER;
	default: return WCHARI(L"???");
	}
}
