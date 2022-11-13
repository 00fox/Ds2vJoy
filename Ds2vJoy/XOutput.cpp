#include "stdafx.h"
#include "XOutput.h"

XOutput::XOutput()
{
}

XOutput::~XOutput()
{
}

const WCHAR* XOutput::XOutputButtons()
{
	return XOutputButtonsString;
}

void XOutput::Init()
{
	if (tape.vJoyActive)
		vJoyEnable();
		//Enable(GetvJoyVersion());
	else
		vJoyDisable();
		//Disable(GetvJoyVersion());
}

void XOutput::InitClient(bool verbose)
{
	if (xoutput_connected)
		return;

	client = vigem_alloc();
	if (client == nullptr)
	{
		echo(I18N.XOutput_memory_allocating_error);
		return;
	}

	err = vigem_connect(client);
	if (!VIGEM_SUCCESS(err))
	{
		echo(I18N.XOutput_bus_connection_failed, XOutputError(err));
		return;
	}
	else
		xoutput_connected = true;

	if (verbose)
		echo(I18N.XOutput_client_connected);

	InitPad(verbose);
}

void XOutput::InitPad(bool verbose)
{
	if (tape.XOutputPaused)
		return;

	switch (tape.DesiredVirtualPad)
	{
	case 1: //DS4
	{
		pad = vigem_target_ds4_alloc();
		err = vigem_target_add(client, pad);
		if (!VIGEM_SUCCESS(err))
		{
			vigem_free(client);
			echo(I18N.XOutput_target_plugin_failed, XOutputError(err));
			return;
		}

		DS4_REPORT_INIT(&report_DS4);
		break;
	}
	case 2: //Xbox360
	{
		pad = vigem_target_x360_alloc();
		err = vigem_target_add(client, pad);
		if (!VIGEM_SUCCESS(err))
		{
			vigem_free(client);
			echo(I18N.XOutput_target_plugin_failed, XOutputError(err));
			return;
		}

		XUSB_REPORT_INIT(&report_X360);
		break;
	}
	}
	if (verbose)
		echo(I18N.XOutput_pad_added);
}

void XOutput::CloseClient(bool verbose)
{
	if (xoutput_connected)
	{
		xoutput_connected = false;
		ClosePad();
		vigem_disconnect(client);
		vigem_free(client);
	}
	if (verbose)
		echo(I18N.XOutput_client_removed);
}

void XOutput::ClosePad(bool verbose)
{
	vigem_target_remove(client, pad);
	vigem_target_free(pad);
	if (verbose)
		echo(I18N.XOutput_pad_removed);
}

void XOutput::LoadDevice(Destination* vjoy)
{
	for (int i = 0; i < 24; i++) { m_src[i] = { 0 }; }

	switch (tape.DesiredVirtualPad)
	{
	case 1:
	{
		for (int i = 0; i < 24; i++)
			m_src[i] = (tape.target_DS4[i]) ? vjoy->GetButton((DestButtonID)tape.target_DS4[i]) : 0;
		break;
	}
	case 2:
	{
		for (int i = 0; i < 24; i++)
			m_src[i] = (tape.target_X360[i]) ? vjoy->GetButton((DestButtonID)tape.target_X360[i]) : 0;
		break;
	}
	}
}

void XOutput::Run()
{
	if (tape.XOutputPaused)
		return;

	XOutputButtonsString[0] = 0;
	WCHAR* head = XOutputButtonsString;
	head += swprintf_s(head, MAX_PATH, L"%s", I18N.XOutputButtonsString);

	switch (tape.DesiredVirtualPad)
	{
	case 1: //DS4
	{
		unsigned short wButtons = 0x0;
		unsigned int dButtons = 0x0;
		byte sButtons = 0x0;

		if ((m_src[0]) ? (m_src[0]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_THUMB_LEFT;			head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_THUMB_LEFT)); }			//11
		if ((m_src[1]) ? (m_src[1]->isPushed()) : false) { dButtons = dButtons | 0x01;							head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_WEST)); }					//<
		if ((m_src[2]) ? (m_src[2]->isPushed()) : false) { dButtons = dButtons | 0x02;							head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_NORTH)); }					//^
		if ((m_src[3]) ? (m_src[3]->isPushed()) : false) { dButtons = dButtons | 0x04;							head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_EAST)); }					//>
		if ((m_src[4]) ? (m_src[4]->isPushed()) : false) { dButtons = dButtons | 0x08;							head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_SOUTH)); }					//v
		if ((m_src[5]) ? (m_src[5]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_SHARE;				head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_SHARE)); }					//9
		if ((m_src[6]) ? (m_src[6]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_OPTIONS;			head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_OPTIONS)); }				//10
		if ((m_src[7]) ? (m_src[7]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_SQUARE;				head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_SQUARE)); }				//1
		if ((m_src[8]) ? (m_src[8]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_TRIANGLE;			head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_TRIANGLE)); }				//4
		if ((m_src[9]) ? (m_src[9]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_CIRCLE;				head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_CIRCLE)); }				//3
		if ((m_src[10]) ? (m_src[10]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_CROSS;			head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_CROSS)); }					//2
		if ((m_src[11]) ? (m_src[11]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_THUMB_RIGHT;		head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_THUMB_RIGHT)); }			//12
		if ((m_src[12]) ? (m_src[12]->isPushed()) : false) { sButtons = sButtons | DS4_SPECIAL_BUTTON_PS;		head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_SPECIAL_BUTTON_PS)); }			//13
		if ((m_src[13]) ? (m_src[13]->isPushed()) : false) { sButtons = sButtons | DS4_SPECIAL_BUTTON_TOUCHPAD;	head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_SPECIAL_BUTTON_TOUCHPAD)); }		//14
		if ((m_src[14]) ? (m_src[14]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_SHOULDER_LEFT;	head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_SHOULDER_LEFT)); }			//5
		if ((m_src[15]) ? (m_src[15]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_SHOULDER_RIGHT;	head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_SHOULDER_RIGHT)); }		//6
		if ((m_src[16]) ? (m_src[16]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_TRIGGER_LEFT;		head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_TRIGGER_LEFT)); }			//7
		if ((m_src[17]) ? (m_src[17]->isPushed()) : false) { wButtons = wButtons | DS4_BUTTON_TRIGGER_RIGHT;	head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_TRIGGER_RIGHT)); }			//8

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

		if (m_src[18]) { report_DS4.bTriggerL = (m_src[18]->isPushed()) ? m_src[18]->GetValByte() : 0; }	//RX
		if (m_src[19]) { report_DS4.bTriggerR = (m_src[19]->isPushed()) ? m_src[19]->GetValByte() : 0; }	//RY
		if (m_src[20]) { report_DS4.bThumbLX = (m_src[20]->isPushed()) ? m_src[20]->GetValByte() : 127; }	//X
		if (m_src[21]) { report_DS4.bThumbLY = (m_src[21]->isPushed()) ? m_src[21]->GetValByte() : 127; }	//Y
		if (m_src[22]) { report_DS4.bThumbRX = (m_src[22]->isPushed()) ? m_src[22]->GetValByte() : 127; }	//Z
		if (m_src[23]) { report_DS4.bThumbRY = (m_src[23]->isPushed()) ? m_src[23]->GetValByte() : 127; }	//RZ

		if (report_DS4.bTriggerL) { head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_LEFT_TR)); }
		if (report_DS4.bTriggerR) { head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_BUTTON_RIGHT_TR)); }
		if (report_DS4.bThumbLX != 127) { head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_THUMB_LEFT_X)); }
		if (report_DS4.bThumbLY != 127) { head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_THUMB_LEFT_Y)); }
		if (report_DS4.bThumbRX != 127) { head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_THUMB_RIGHT_X)); }
		if (report_DS4.bThumbRY != 127) { head += swprintf_s(head, MAX_PATH, L" %s", DS4_String(DS4_THUMB_RIGHT_Y)); }

		vigem_target_ds4_update(client, pad, report_DS4);
		break;
	}
	case 2: //Xbox360
	{
	    unsigned short wButtons = 0x0;

		if ((m_src[0])  ? (m_src[0]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_LEFT_THUMB;		head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_LEFT_THUMB)); }		//9
		if ((m_src[1])  ? (m_src[1]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_DPAD_LEFT;		head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_DPAD_LEFT)); }		//<
		if ((m_src[2])  ? (m_src[2]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_DPAD_UP;		head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_DPAD_UP)); }		//^
		if ((m_src[3])  ? (m_src[3]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_DPAD_RIGHT;		head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_DPAD_RIGHT)); }		//>
		if ((m_src[4])  ? (m_src[4]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_DPAD_DOWN;		head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_DPAD_DOWN)); }		//v
		if ((m_src[5])  ? (m_src[5]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_BACK;			head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_BACK)); }			//7
		if ((m_src[6])  ? (m_src[6]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_START;			head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_START)); }			//8
		if ((m_src[7])  ? (m_src[7]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_X;				head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_X)); }				//3
		if ((m_src[8])  ? (m_src[8]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_Y;				head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_Y)); }				//4
		if ((m_src[9])  ? (m_src[9]->isPushed())  : false) { wButtons = wButtons | XUSB_GAMEPAD_B;				head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_B)); }				//2
		if ((m_src[10]) ? (m_src[10]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_A;				head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_A)); }				//1
		if ((m_src[11]) ? (m_src[11]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_RIGHT_THUMB;	head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_RIGHT_THUMB)); }	//10
		if ((m_src[12]) ? (m_src[12]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_GUIDE;			head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_GUIDE)); }			//No
		if ((m_src[14]) ? (m_src[14]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_LEFT_SHOULDER;	head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_LEFT_SHOULDER)); }	//5
		if ((m_src[15]) ? (m_src[15]->isPushed()) : false) { wButtons = wButtons | XUSB_GAMEPAD_RIGHT_SHOULDER;	head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_RIGHT_SHOULDER)); }	//6

		report_X360.wButtons = wButtons;

		if (m_src[18]) { report_X360.bLeftTrigger	= (m_src[18]->isPushed()) ? m_src[18]->GetValByte() : 0; }			//-Z
		if (m_src[19]) { report_X360.bRightTrigger	= (m_src[19]->isPushed()) ? m_src[19]->GetValByte() : 0; }			//+Z
		if (m_src[20]) { report_X360.sThumbLX		= (m_src[20]->isPushed()) ? (m_src[20]->GetVal() - 32768) : 0; }	//X
		if (m_src[21]) { report_X360.sThumbLY		= (m_src[21]->isPushed()) ? (m_src[21]->GetVal() - 32768) : 0; }	//Y
		if (m_src[22]) { report_X360.sThumbRX		= (m_src[22]->isPushed()) ? (m_src[22]->GetVal() - 32768) : 0; }	//RX
		if (m_src[23]) { report_X360.sThumbRY		= (m_src[23]->isPushed()) ? (m_src[23]->GetVal() - 32768) : 0; }	//RY

		if (report_X360.bLeftTrigger)	{ head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_LEFT_TRIGGER)); }
		if (report_X360.bRightTrigger)	{ head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_RIGHT_TRIGGER)); }
		if (report_X360.sThumbLX)		{ head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_LEFT_X)); }
		if (report_X360.sThumbLY)		{ head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_LEFT_Y)); }
		if (report_X360.sThumbRX)		{ head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_RIGHT_X)); }
		if (report_X360.sThumbRY)		{ head += swprintf_s(head, MAX_PATH, L" %s", X360_String(XUSB_GAMEPAD_RIGHT_Y)); }

		vigem_target_x360_update(client, pad, report_X360);
		break;
	}
	}

	return;
}

void XOutput::XOutputStates()
{
	xiState = XOutputState();
}

char XOutput::GetXOutputState()
{
	return xiState;
}

char XOutput::XOutputState(bool verbose)
{
	return GetDeviceState(L"ROOT\\SYSTEM", L"Nefarius\\ViGEmBus\\Gen1", verbose);
}

BOOL XOutput::XOutputInstall(bool verbose)
{
	if (XOutputState() > 0)
	{
		if (verbose)
			echo(L"XOutput driver is already installed");
		return TRUE;
	}

	std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName;

	if (ExtractEmbededResource(installpath, IDR_VIGEMBUS_ZIP, true))
	{
		if (SendMessage(tape.Ds2hWnd, WM_PAUSE, 0, 0))
		{
			std::wstring infpath = PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\ViGEmBus\\ViGEmBus.inf";
			InstallDriverByHwId(infpath, L"Nefarius\\ViGEmBus\\Gen1");
			PostMessage(tape.Ds2hWnd, WM_RESTART, 0, 0);
		}

		switch (XOutputState())
		{
		case DRIVER_STATE_ACTIVE:
		{
			echo(I18N.XOutput_driver_installed);
			PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 1, 0);
			return TRUE;
		}
		case DRIVER_STATE_DISABLED:
		{
			echo(I18N.XOutput_driver_installed);
			PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 0, 0);
			return TRUE;
		}
		}
	}
	echo(I18N.XOutput_driver_instalation_failed);

	return FALSE;
}

BOOL XOutput::XOutputUninstall(bool verbose)
{
	switch (XOutputState())
	{
	case DRIVER_STATE_NOTPRESENT:
	{
		if (verbose)
			echo(L"XOutput driver is already uninstalled");
		return TRUE;
	}
	case DRIVER_STATE_ACTIVE:
	case DRIVER_STATE_DISABLED:
	{
		if (SendMessage(tape.Ds2hWnd, WM_PAUSE, 0, 0))
		{
			RemoveDriverByHwId(L"ROOT\\SYSTEM", L"Nefarius\\ViGEmBus\\Gen1", verbose);
			PostMessage(tape.Ds2hWnd, WM_RESTART, 0, 0);
		}

		if (XOutputState() == DRIVER_STATE_NOTPRESENT)
		{
			std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\ViGEmBus\0\0";
			std::filesystem::remove_all(installpath);

			std::wstring prfdirpath = PrfPath() + L"/" + tape.ProgramFilesDirName;
			prfdirpath = ReplaceInString(prfdirpath, L"\\", '/');
			RemoveDirectoryW(prfdirpath.c_str());

			SendMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 0, 0);
			echo(I18N.XOutput_driver_uninstalled);
			return TRUE;
		}
		else
		{
			if (verbose)
				echo(I18N.XOutput_driver_uninstalation_failed);
			return FALSE;
		}
	}
	default:
	{
		if (verbose)
		{
			echo(L"XOutput driver has a problem");
			GetDeviceError(L"ROOT\\SYSTEM", L"Nefarius\\ViGEmBus\\Gen1", true);
		}
		return FALSE;
	}
	}
}

BOOL XOutput::XOutputEnable(bool verbose)
{
	return SetDeviceState(L"ROOT\\SYSTEM", L"Nefarius\\ViGEmBus\\Gen1", DICS_ENABLE, verbose);
}

BOOL XOutput::XOutputDisable(bool verbose)
{
	return SetDeviceState(L"ROOT\\SYSTEM", L"Nefarius\\ViGEmBus\\Gen1", DICS_DISABLE, verbose);
}

void XOutput::vJoyStates()
{
	vjState = vJoyState();
}

char XOutput::GetvJoyState()
{
	return vjState;
}

char XOutput::vJoyState(bool verbose)
{
	return GetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", verbose);
}

BOOL XOutput::vJoyInstall(bool verbose)
{
	if (vJoyState() > 0)
	{
		if (verbose)
			echo(L"vJoy driver is already installed");
		return TRUE;
	}

	std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName;

	if (ExtractEmbededResource(installpath, IDR_VJOYDEVICE_ZIP, true))
	{
		//std::wstring regpath = L"regedit.exe /s \"" + PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\vJoyDevice\\vJoy.reg";
		//LaunchCmd(regpath.c_str());

		if (SendMessage(tape.Ds2hWnd, WM_PAUSE, 0, 0))
		{
			std::wstring infpath = PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\vJoyDevice\\vJoy.inf";
			InstallDriverByHwId(infpath, L"root\\VID_1234&PID_BEAD&REV_0219");
			PostMessage(tape.Ds2hWnd, WM_RESTART, 0, 0);
		}

		switch (vJoyState())
		{
		case DRIVER_STATE_ACTIVE:
		{
			echo(I18N.vJoy_driver_installed);
			if (!tape.vJoyActive)
				vJoyDisable();
			else
			return TRUE;
		}
		case DRIVER_STATE_DISABLED:
		{
			echo(I18N.vJoy_driver_installed);
			if (tape.vJoyActive)
				vJoyEnable();
			return TRUE;
		}
		}
	}
	echo(I18N.vJoy_driver_instalation_failed);

	return FALSE;
}

BOOL XOutput::vJoyUninstall(bool verbose)
{
	switch (vJoyState())
	{
	case DRIVER_STATE_NOTPRESENT:
	{
		if (verbose)
			echo(L"vJoy driver is already uninstalled");
		return TRUE;
	}
	case DRIVER_STATE_ACTIVE:
	case DRIVER_STATE_DISABLED:
	{
		if (SendMessage(tape.Ds2hWnd, WM_PAUSE, 0, 0))
		{
			RemoveDriverByHwId(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", verbose);
			PostMessage(tape.Ds2hWnd, WM_RESTART, 0, 0);
		}

		if (vJoyState() == DRIVER_STATE_NOTPRESENT)
		{
			std::wstring installpath = PrfPath() + L"\\" + tape.ProgramFilesDirName + L"\\vJoyDevice\0\0";
			std::filesystem::remove_all(installpath);

			std::wstring prfdirpath = PrfPath() + L"/" + tape.ProgramFilesDirName;
			prfdirpath = ReplaceInString(prfdirpath, L"\\", '/');
			RemoveDirectoryW(prfdirpath.c_str());

			echo(I18N.vJoy_driver_uninstalled);
			return TRUE;
		}
		else
		{
			if (verbose)
				echo(I18N.vJoy_driver_uninstalation_failed);
			return FALSE;
		}
	}
	default:
	{
		if (verbose)
		{
			echo(L"vJoy driver has a problem");
			GetDeviceError(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", true);
		}
		return FALSE;
	}
	}
}

BOOL XOutput::vJoyEnable(bool verbose)
{
	return SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_ENABLE, verbose);
}

BOOL XOutput::vJoyDisable(bool verbose)
{
	return SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_DISABLE, verbose);
}

std::wstring XOutput::XOutputError(VIGEM_ERROR err)
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

WCHAR* XOutput::X360_String(int id)
{
	switch (id)
	{
	case XUSB_GAMEPAD_LEFT_X: return I18N.Dest_X;
	case XUSB_GAMEPAD_LEFT_Y: return I18N.Dest_Y;
	case XUSB_GAMEPAD_RIGHT_X: return I18N.Dest_RX;
	case XUSB_GAMEPAD_RIGHT_Y: return I18N.Dest_RY;
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
	default: return I18N.WHICH;
	}
}

WCHAR* XOutput::DS4_String(int id)
{
	switch (id)
	{
	case DS4_THUMB_LEFT_X: return I18N.Dest_X;
	case DS4_THUMB_LEFT_Y: return I18N.Dest_Y;
	case DS4_THUMB_RIGHT_X: return I18N.Dest_Z;
	case DS4_THUMB_RIGHT_Y: return I18N.Dest_RZ;
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
	case DS4_BUTTON_LEFT_TR: return I18N.Button_L2_TRIGGER;
	case DS4_BUTTON_RIGHT_TR: return I18N.Button_R2_TRIGGER;
	default: return I18N.WHICH;
	}
}
