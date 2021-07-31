#include "stdafx.h"
#include "Settings.h"

Settings::Settings()
{
}

Settings::~Settings()
{
}

BOOL Settings::Open(WCHAR* file)
{
	lstrcpyW(m_file, file);
	return TRUE;
}

BOOL Settings::OpenIni(WCHAR* inifile)
{
	WCHAR path[MAX_PATH + 1];
	if (0 != GetModuleFileName(NULL, path, MAX_PATH))
	{
		WCHAR dir[MAX_PATH + 1];
		if (_wsplitpath_s(path, NULL, 0, dir, MAX_PATH + 1, NULL, 0, NULL, 0) == 0)
		{
			wsprintfW(m_file, L"%s%s", dir, inifile);
			return TRUE;
		}
	}
	return FALSE;
}

void Settings::Load()
{
	if (m_file[0] == 0)
		return;

	SetProfile(GetPrivateProfileInt(TEXT("Profile"), TEXT("Profile"), 1, m_file));

	WCHAR Settingstxt[20];
	WCHAR Mappingtxt[20];
	WCHAR ViGEmtxt[20];
	WCHAR Keymaptxt[20];
	WCHAR RapidFiretxt[20];
	WCHAR Guardiantxt[20];
	wsprintf(Settingstxt, L"%dSettings", Profile);
	wsprintf(Mappingtxt, L"%dMapping", Profile);
	wsprintf(ViGEmtxt, L"%dViGEm", Profile);
	wsprintf(Keymaptxt, L"%dKeymap", Profile);
	wsprintf(RapidFiretxt, L"%dRapidFire", Profile);
	wsprintf(Guardiantxt, L"%dGuardian", Profile);

	SetDesiredDS(GetPrivateProfileInt(TEXT("Profile"), TEXT("PreferredDS"), 2, m_file));
	Tasktray = GetPrivateProfileInt(TEXT("Profile"), TEXT("Tasktray"), 1, m_file) == 1 ? true : false;
	CloseMinimize = GetPrivateProfileInt(TEXT("Profile"), TEXT("CloseMinimize"), 0, m_file) == 1 ? true : false;
	DisconnectBT = GetPrivateProfileInt(TEXT("Profile"), TEXT("DisconnectBT"), 0, m_file) == 1 ? true : false;
	LowBattAlert = GetPrivateProfileInt(TEXT("Profile"), TEXT("LowBattAlert"), 1, m_file) == 1 ? true : false;
	GetPrivateProfileString(L"Profile", L"dsSerial", L"", dsSerial, sizeof(dsSerial) / sizeof(dsSerial[0]), m_file);
	BlackLedOnExit = GetPrivateProfileInt(TEXT("Profile"), TEXT("BlackLedOnExit"), 1, m_file) == 1 ? true : false;

	vJoyPaused = GetPrivateProfileInt(TEXT("Tray"), TEXT("vJoyPaused"), 0, m_file) == 1 ? true : false;
	ViGEmPaused = GetPrivateProfileInt(TEXT("Tray"), TEXT("ViGEmPaused"), 0, m_file) == 1 ? true : false;
	KeymapPaused = GetPrivateProfileInt(TEXT("Tray"), TEXT("KeymapPaused"), 0, m_file) == 1 ? true : false;
	RapidFirePaused = GetPrivateProfileInt(TEXT("Tray"), TEXT("RapidFirePaused"), 0, m_file) == 1 ? true : false;
	GuardianPaused = GetPrivateProfileInt(TEXT("Tray"), TEXT("GuardianPaused"), 0, m_file) == 1 ? true : false;

	GetPrivateProfileString(L"Guardian", L"dsHID1", LR"(HID\VID_054C&PID_0BA0&MI_03)", dsHID1, sizeof(dsHID1) / sizeof(dsHID1[0]), m_file);
	GetPrivateProfileString(L"Guardian", L"dsHID2", LR"(HID\VID_054C&PID_0CE6&MI_03)", dsHID2, sizeof(dsHID2) / sizeof(dsHID2[0]), m_file);
	GetPrivateProfileString(L"Guardian", L"dsHID3", L"", dsHID3, sizeof(dsHID3) / sizeof(dsHID3[0]), m_file);
	GetPrivateProfileString(L"Guardian", L"Exe1Name", L"RemotePlay.exe", Exe1Name, sizeof(Exe1Name) / sizeof(Exe1Name[0]), m_file);
	GetPrivateProfileString(L"Guardian", L"Exe2Name", L"", Exe2Name, sizeof(Exe2Name) / sizeof(Exe2Name[0]), m_file);
	GetPrivateProfileString(L"Guardian", L"Exe3Name", L"", Exe3Name, sizeof(Exe3Name) / sizeof(Exe3Name[0]), m_file);
	GetPrivateProfileString(L"Guardian", L"Exe4Name", L"", Exe4Name, sizeof(Exe4Name) / sizeof(Exe4Name[0]), m_file);
	GetPrivateProfileString(L"Guardian", L"Exe5Name", L"", Exe5Name, sizeof(Exe5Name) / sizeof(Exe5Name[0]), m_file);

	GetPrivateProfileString(L"Links", L"App1Name", L"Avoid", App1Name, sizeof(App1Name) / sizeof(App1Name[0]), m_file);
	GetPrivateProfileString(L"Links", L"App2Name", L"Prefer", App2Name, sizeof(App2Name) / sizeof(App2Name[0]), m_file);
	GetPrivateProfileString(L"Links", L"App3Name", L"", App3Name, sizeof(App3Name) / sizeof(App3Name[0]), m_file);
	GetPrivateProfileString(L"Links", L"App4Name", L"", App4Name, sizeof(App4Name) / sizeof(App4Name[0]), m_file);
	GetPrivateProfileString(L"Links", L"App5Name", L"", App5Name, sizeof(App5Name) / sizeof(App5Name[0]), m_file);
	GetPrivateProfileString(L"Links", L"App1Location", LR"(C:\Windows\System32\cmd.exe /C "joy.cpl")", App1Location, sizeof(App1Location) / sizeof(App1Location[0]), m_file);
	GetPrivateProfileString(L"Links", L"App2Location", LR"(rundll32.exe shell32.dll,Control_RunDLL joy.cpl)", App2Location, sizeof(App2Location) / sizeof(App2Location[0]), m_file);
	GetPrivateProfileString(L"Links", L"App3Location", L"", App3Location, sizeof(App3Location) / sizeof(App3Location[0]), m_file);
	GetPrivateProfileString(L"Links", L"App4Location", L"", App4Location, sizeof(App4Location) / sizeof(App4Location[0]), m_file);
	GetPrivateProfileString(L"Links", L"App5Location", L"", App5Location, sizeof(App5Location) / sizeof(App5Location[0]), m_file);

	SetThreshold(GetPrivateProfileInt(Settingstxt, TEXT("Threshold"), 7, m_file));
	SetSimultaneous(GetPrivateProfileInt(Settingstxt, TEXT("Simultaneous"), 40, m_file));
	SetLongPress(GetPrivateProfileInt(Settingstxt, TEXT("LongPress"), 255, m_file));
	SetVeryLongPress(GetPrivateProfileInt(Settingstxt, TEXT("VeryLongPress"), 3287, m_file));
	FFB = GetPrivateProfileInt(Settingstxt, TEXT("FFB"), 0, m_file) == 1 ? true : false;
	SetTriggersMode(GetPrivateProfileInt(Settingstxt, TEXT("TriggersMode"), 0, m_file));
	setvJoyDeviceID(GetPrivateProfileInt(Settingstxt, TEXT("vJoyDeviceID"), 1, m_file));
	SetTouchPadButton(GetPrivateProfileInt(Settingstxt, TEXT("TouchPadButton"), 0, m_file));
	SetSplitTouch();
	SetTouchCol(GetPrivateProfileInt(Settingstxt, TEXT("TouchCol"), 1, m_file));
	SetTouchRow(GetPrivateProfileInt(Settingstxt, TEXT("TouchRow"), 1, m_file));
	SetLED(GetPrivateProfileInt(Settingstxt, TEXT("LED_Color"), 0xFF0000, m_file));

	{
		const int n = sizeof(WCHAR) * 32 * 1024 *2;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			return;

		WCHAR* head = buf;
		int ret = GetPrivateProfileSectionW(Mappingtxt, buf, n, m_file);
		if (ret > 0 && ret - 2 != n)
		{
			WCHAR* key = head, * value;
			while (*key != 0)
			{
				head += lstrlenW(key) + 1;
				value = wcschr(key, L'=');
				if (value == 0)
					break;
				*value++ = 0;
				int j = _wtoi(key);
				if (j <= 0 || j >= 128)
				{
					key = head;
					continue;
				}

				int mapdata[MappingName::Mapping_Count] = { 0 };
				for (int i = 0; i < MappingName::Mapping_Count; i++)
				{
					key = value;
					value = wcschr(key, L',');
					if (value != 0)
						*value++ = 0;
					int j = _wtoi(key);
					if (j < 0 || j > 0x270F)
						j = 0;
					mapdata[i] = j;
					if (value == 0)
						break;
				}
				Mapping btn;
				btn.Enable = mapdata[MappingName::Mapping_Enable] == 1;
				btn.dsID[0] = (dsButtonID)mapdata[MappingName::Mapping_ds_1];
				btn.dsID[1] = (dsButtonID)mapdata[MappingName::Mapping_ds_2];
				btn.dsID[2] = (dsButtonID)mapdata[MappingName::Mapping_ds_3];
				btn.dsID[3] = (dsButtonID)mapdata[MappingName::Mapping_ds_4];
				btn.dsID[4] = (dsButtonID)mapdata[MappingName::Mapping_ds_5];
				btn.Target[0] = mapdata[MappingName::Mapping_Target_1] == 1;
				btn.Target[1] = mapdata[MappingName::Mapping_Target_2] == 1;
				btn.Target[2] = mapdata[MappingName::Mapping_Target_3] == 1;
				btn.Target[3] = mapdata[MappingName::Mapping_Target_4] == 1;
				btn.Target[4] = mapdata[MappingName::Mapping_Target_5] == 1;
				btn.vjID[0] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_source_1];
				btn.vjID[1] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_source_2];
				btn.vjID[2] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_source_3];
				btn.vjID[3] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_source_4];
				btn.vjID[4] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_source_5];
				btn.Disbale[0] = mapdata[MappingName::Mapping_ds_1_Disable];
				btn.Disbale[1] = mapdata[MappingName::Mapping_ds_2_Disable];
				btn.Disbale[2] = mapdata[MappingName::Mapping_ds_3_Disable];
				btn.Disbale[3] = mapdata[MappingName::Mapping_ds_4_Disable];
				btn.Disbale[4] = mapdata[MappingName::Mapping_ds_5_Disable];
				btn.OrXorNot[0] = mapdata[MappingName::Mapping_OrXorNot_1];
				btn.OrXorNot[1] = mapdata[MappingName::Mapping_OrXorNot_2];
				btn.OrXorNot[2] = mapdata[MappingName::Mapping_OrXorNot_3];
				btn.OrXorNot[3] = mapdata[MappingName::Mapping_OrXorNot_4];
				btn.Ifmouse = mapdata[MappingName::Mapping_If_mouse] == 1;
				btn.Force = mapdata[MappingName::Mapping_Force];
				btn.Led = mapdata[MappingName::Mapping_led];
				btn.Short = mapdata[MappingName::Mapping_Short] == 1;
				btn.Double = mapdata[MappingName::Mapping_Double] == 1;
				btn.Long = mapdata[MappingName::Mapping_Long] == 1;
				btn.Macro = mapdata[MappingName::Mapping_Macro];
				btn.Toggle = mapdata[MappingName::Mapping_Toggle];
				btn.vjID[5] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_1];
				btn.vjID[6] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_2];
				btn.vjID[7] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_3];
				btn.vjID[8] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_4];
				btn.vjID[9] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_5];
				btn.vjID[10] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_6];
				btn.vjID[11] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_7];
				btn.vjID[12] = (vJoyButtonID)mapdata[MappingName::Mapping_vJoy_8];
				btn.OnRelease[0] = mapdata[MappingName::Mapping_On_release_1];
				btn.OnRelease[1] = mapdata[MappingName::Mapping_On_release_2];
				btn.OnRelease[2] = mapdata[MappingName::Mapping_On_release_3];
				btn.OnRelease[3] = mapdata[MappingName::Mapping_On_release_4];
				btn.OnRelease[4] = mapdata[MappingName::Mapping_On_release_5];
				btn.OnRelease[5] = mapdata[MappingName::Mapping_On_release_6];
				btn.OnRelease[6] = mapdata[MappingName::Mapping_On_release_7];
				btn.OnRelease[7] = mapdata[MappingName::Mapping_On_release_8];
				btn.Disbale[5] = mapdata[MappingName::Mapping_vJoy_1_Disable];
				btn.Disbale[6] = mapdata[MappingName::Mapping_vJoy_2_Disable];
				btn.Disbale[7] = mapdata[MappingName::Mapping_vJoy_3_Disable];
				btn.Disbale[8] = mapdata[MappingName::Mapping_vJoy_4_Disable];
				btn.Disbale[9] = mapdata[MappingName::Mapping_vJoy_5_Disable];
				btn.Disbale[10] = mapdata[MappingName::Mapping_vJoy_6_Disable];
				btn.Disbale[11] = mapdata[MappingName::Mapping_vJoy_7_Disable];
				btn.Disbale[12] = mapdata[MappingName::Mapping_vJoy_8_Disable];
				btn.Start[0] = mapdata[MappingName::Mapping_Start_1];
				btn.Start[1] = mapdata[MappingName::Mapping_Start_2];
				btn.Start[2] = mapdata[MappingName::Mapping_Start_3];
				btn.Start[3] = mapdata[MappingName::Mapping_Start_4];
				btn.Start[4] = mapdata[MappingName::Mapping_Start_5];
				btn.Start[5] = mapdata[MappingName::Mapping_Start_6];
				btn.Start[6] = mapdata[MappingName::Mapping_Start_7];
				btn.Start[7] = mapdata[MappingName::Mapping_Start_8];
				btn.Stop[0] = mapdata[MappingName::Mapping_Stop_1];
				btn.Stop[1] = mapdata[MappingName::Mapping_Stop_2];
				btn.Stop[2] = mapdata[MappingName::Mapping_Stop_3];
				btn.Stop[3] = mapdata[MappingName::Mapping_Stop_4];
				btn.Stop[4] = mapdata[MappingName::Mapping_Stop_5];
				btn.Stop[5] = mapdata[MappingName::Mapping_Stop_6];
				btn.Stop[6] = mapdata[MappingName::Mapping_Stop_7];
				btn.Stop[7] = mapdata[MappingName::Mapping_Stop_8];
				btn.MouseAction[0] = mapdata[MappingName::Mapping_Mouse_action_1];
				btn.MouseAction[1] = mapdata[MappingName::Mapping_Mouse_action_2];
				btn.MouseAction[2] = mapdata[MappingName::Mapping_Mouse_action_3];
				btn.MouseAction[3] = mapdata[MappingName::Mapping_Mouse_action_4];
				btn.Mouse[0] = mapdata[MappingName::Mapping_Mouse_1];
				btn.Mouse[1] = mapdata[MappingName::Mapping_Mouse_2];
				btn.Mouse[2] = mapdata[MappingName::Mapping_Mouse_3];
				btn.Mouse[3] = mapdata[MappingName::Mapping_Mouse_4];
				btn.Mouse[4] = mapdata[MappingName::Mapping_Mouse_5];
				btn.Mouse[5] = mapdata[MappingName::Mapping_Mouse_6];
				btn.Mouse[6] = mapdata[MappingName::Mapping_Mouse_Grid];
				btn.Grid[0] = max(0, min(9999, mapdata[MappingName::Mapping_Grid_x]));
				btn.Grid[1] = max(0, min(9999, mapdata[MappingName::Mapping_Grid_y]));
				btn.Grid[2] = max(0, min(9999, mapdata[MappingName::Mapping_Grid_w]));
				btn.Grid[3] = max(0, min(9999, mapdata[MappingName::Mapping_Grid_h]));
				btn.Grid[4] = max(0, min(99, mapdata[MappingName::Mapping_Grid_nw]));
				btn.Grid[5] = max(0, min(99, mapdata[MappingName::Mapping_Grid_nh]));
				Mappingdata.push_back(std::move(btn));
				key = head;
			}
		}
	}

	ViGEmActive = GetPrivateProfileInt(ViGEmtxt, TEXT("ViGEmActive"), 0, m_file) == 1 ? true : false;
	SetDesiredVirtualPad(GetPrivateProfileInt(ViGEmtxt, TEXT("DesiredVirtualPad"), 1, m_file));

	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			return;

		int totalvalues_X360 = 0;
		int dstotalvalues_X360 = 0;
		int vjtotalvalues_X360 = 0;
		int totalvalues_DS4 = 0;
		int dstotalvalues_DS4 = 0;
		int vjtotalvalues_DS4 = 0;
		WCHAR* head = buf;
		int ret = GetPrivateProfileSectionW(ViGEmtxt, buf, n, m_file);
		if (ret > 0 && ret - 2 != n)
		{
			WCHAR* key = head, * value;
			while (*key != 0)
			{
				head += lstrlenW(key) + 1;
				value = wcschr(key, L'=');
				if (value == 0)
					break;
				*value++ = 0;
				int j = _wtoi(key);
				if (j < 1)
				{
					key = head;
					continue;
				}

				for (int i = 0; i < 24; i++)
				{
					key = value;
					value = wcschr(key, L',');
					if (value != 0)
						*value++ = 0;
					int k = _wtoi(key);
					if (k < 0 || k >= 0x100)
						continue;
					switch (j)
					{
					case 1:
						totalvalues_X360++;
						target_X360[i] = (int)k;
						break;
					case 2:
						dstotalvalues_X360++;
						dstarget_X360[i] = (dsButtonID)k;
						break;
					case 3:
						vjtotalvalues_X360++;
						vjtarget_X360[i] = (vJoyButtonID)k;
						break;
					case 4:
						totalvalues_DS4++;
						target_DS4[i] = (int)k;
						break;
					case 5:
						dstotalvalues_DS4++;
						dstarget_DS4[i] = (dsButtonID)k;
						break;
					case 6:
						vjtotalvalues_DS4++;
						vjtarget_DS4[i] = (vJoyButtonID)k;
						break;
					}
					if (value == 0)
						break;
				}
				key = head;
			}
		}
		if (totalvalues_X360 == 0)
			for (int i = 0; i < 24; i++) { target_X360[i] = false; };
		if (dstotalvalues_X360 == 0)
		{
			dstarget_X360[0] = dsButtonID::L3;
			dstarget_X360[1] = dsButtonID::DPAD_LEFT;
			dstarget_X360[2] = dsButtonID::DPAD_UP;
			dstarget_X360[3] = dsButtonID::DPAD_RIGHT;
			dstarget_X360[4] = dsButtonID::DPAD_DOWN;
			dstarget_X360[5] = dsButtonID::SHARE;
			dstarget_X360[6] = dsButtonID::OPTIONS;
			dstarget_X360[7] = dsButtonID::SQUARE;
			dstarget_X360[8] = dsButtonID::TRIANGLE;
			dstarget_X360[9] = dsButtonID::CIRCLE;
			dstarget_X360[10] = dsButtonID::CROSS;
			dstarget_X360[11] = dsButtonID::R3;
			dstarget_X360[12] = dsButtonID::PS;
			dstarget_X360[13] = dsButtonID::TOUCH;
			dstarget_X360[14] = dsButtonID::L1;
			dstarget_X360[15] = dsButtonID::R1;
			dstarget_X360[16] = dsButtonID::L2;
			dstarget_X360[17] = dsButtonID::R2;
			dstarget_X360[18] = dsButtonID::L2TRIGGER;
			dstarget_X360[19] = dsButtonID::R2TRIGGER;
			dstarget_X360[20] = dsButtonID::LX;
			dstarget_X360[21] = dsButtonID::LYINV;
			dstarget_X360[22] = dsButtonID::RX;
			dstarget_X360[23] = dsButtonID::RYINV;
		}
		if (vjtotalvalues_X360 == 0)
		{
			vjtarget_X360[0] = vJoyButtonID::Button1;
			vjtarget_X360[1] = vJoyButtonID::Button2;
			vjtarget_X360[2] = vJoyButtonID::Button3;
			vjtarget_X360[3] = vJoyButtonID::Button4;
			vjtarget_X360[4] = vJoyButtonID::Button5;
			vjtarget_X360[5] = vJoyButtonID::Button6;
			vjtarget_X360[6] = vJoyButtonID::Button7;
			vjtarget_X360[7] = vJoyButtonID::Button8;
			vjtarget_X360[8] = vJoyButtonID::Button9;
			vjtarget_X360[9] = vJoyButtonID::Button10;
			vjtarget_X360[10] = vJoyButtonID::Button11;
			vjtarget_X360[11] = vJoyButtonID::Button12;
			vjtarget_X360[12] = vJoyButtonID::Button13;
			vjtarget_X360[13] = vJoyButtonID::none;
			vjtarget_X360[14] = vJoyButtonID::Button16;
			vjtarget_X360[15] = vJoyButtonID::Button17;
			vjtarget_X360[16] = vJoyButtonID::none;
			vjtarget_X360[17] = vJoyButtonID::none;
			vjtarget_X360[18] = vJoyButtonID::RXTR;
			vjtarget_X360[19] = vJoyButtonID::RYTR;
			vjtarget_X360[20] = vJoyButtonID::X;
			vjtarget_X360[21] = vJoyButtonID::YINV;
			vjtarget_X360[22] = vJoyButtonID::Z;
			vjtarget_X360[23] = vJoyButtonID::RZINV;
		}
		if (totalvalues_DS4 == 0)
			for (int i = 0; i < 24; i++) { target_DS4[i] = false; };
		if (dstotalvalues_DS4 == 0)
		{
			dstarget_DS4[0] = dsButtonID::L3;
			dstarget_DS4[1] = dsButtonID::DPAD_LEFT;
			dstarget_DS4[2] = dsButtonID::DPAD_UP;
			dstarget_DS4[3] = dsButtonID::DPAD_RIGHT;
			dstarget_DS4[4] = dsButtonID::DPAD_DOWN;
			dstarget_DS4[5] = dsButtonID::SHARE;
			dstarget_DS4[6] = dsButtonID::OPTIONS;
			dstarget_DS4[7] = dsButtonID::SQUARE;
			dstarget_DS4[8] = dsButtonID::TRIANGLE;
			dstarget_DS4[9] = dsButtonID::CIRCLE;
			dstarget_DS4[10] = dsButtonID::CROSS;
			dstarget_DS4[11] = dsButtonID::R3;
			dstarget_DS4[12] = dsButtonID::PS;
			dstarget_DS4[13] = dsButtonID::TOUCH;
			dstarget_DS4[14] = dsButtonID::L1;
			dstarget_DS4[15] = dsButtonID::R1;
			dstarget_DS4[16] = dsButtonID::L2;
			dstarget_DS4[17] = dsButtonID::R2;
			dstarget_DS4[18] = dsButtonID::L2TRIGGER;
			dstarget_DS4[19] = dsButtonID::R2TRIGGER;
			dstarget_DS4[20] = dsButtonID::LX;
			dstarget_DS4[21] = dsButtonID::LY;
			dstarget_DS4[22] = dsButtonID::RX;
			dstarget_DS4[23] = dsButtonID::RY;
		}
		if (vjtotalvalues_DS4 == 0)
		{
			vjtarget_DS4[0] = vJoyButtonID::Button1;
			vjtarget_DS4[1] = vJoyButtonID::Button2;
			vjtarget_DS4[2] = vJoyButtonID::Button3;
			vjtarget_DS4[3] = vJoyButtonID::Button4;
			vjtarget_DS4[4] = vJoyButtonID::Button5;
			vjtarget_DS4[5] = vJoyButtonID::Button6;
			vjtarget_DS4[6] = vJoyButtonID::Button7;
			vjtarget_DS4[7] = vJoyButtonID::Button8;
			vjtarget_DS4[8] = vJoyButtonID::Button9;
			vjtarget_DS4[9] = vJoyButtonID::Button10;
			vjtarget_DS4[10] = vJoyButtonID::Button11;
			vjtarget_DS4[11] = vJoyButtonID::Button12;
			vjtarget_DS4[12] = vJoyButtonID::Button13;
			vjtarget_DS4[13] = vJoyButtonID::Button14;
			vjtarget_DS4[14] = vJoyButtonID::Button16;
			vjtarget_DS4[15] = vJoyButtonID::Button17;
			vjtarget_DS4[16] = vJoyButtonID::Button18;
			vjtarget_DS4[17] = vJoyButtonID::Button19;
			vjtarget_DS4[18] = vJoyButtonID::RXTR;
			vjtarget_DS4[19] = vJoyButtonID::RYTR;
			vjtarget_DS4[20] = vJoyButtonID::X;
			vjtarget_DS4[21] = vJoyButtonID::Y;
			vjtarget_DS4[22] = vJoyButtonID::Z;
			vjtarget_DS4[23] = vJoyButtonID::RZ;
		}
	}

	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			return;

		WCHAR* head = buf;
		int ret = GetPrivateProfileSectionW(Keymaptxt, buf, n, m_file);
		if (ret > 0 && ret - 2 != n)
		{
			WCHAR* key = head, * value;
			while (*key != 0)
			{
				head += lstrlenW(key) + 1;
				value = wcschr(key, L'=');
				if (value == 0)
					break;
				*value++ = 0;
				std::string header = SubString(key, "=", 0, 0);
				Keymap keymap;
				int btnid = _wtoi(key);
				if (btnid <= vJoyButtonID::none || btnid >= vJoyButtonID::button_Count)
				{
					key = head;
					continue;
				}
				keymap.ButtonID = (vJoyButtonID)btnid;

				key = value;
				value = wcschr(key, L',');
				if (value == 0)
					break;
				*value++ = 0;
				if (_wtoi(key) != 0)
					keymap.Enable = true;

				key = value;
				value = wcschr(key, L',');
				if (value != 0)
					*value++ = 0;
				if (_wtoi(key) != 0)
					keymap.usePostmessage = true;

				key = value;
				value = wcschr(key, L',');
				if (value != 0)
					*value++ = 0;
				if (_wtoi(key) != 0)
					keymap.useActivating = true;

				for (int i = 0; i < KEYMAP_MAX_KEYS; i++)
				{
					key = value;
					value = wcschr(key, L',');
					if (value != 0)
						*value++ = 0;
					if (_wcsnicmp(key, L"**", 2) == 0)
					{
						keymap.findWindow.Val(value);
						break;
					}
					int _vk = _wtoi(key);
					if (_vk <= 0 || _vk >= 0x100)
						break;
					keymap.vk.push_back((BYTE)_vk);
					if (value == 0)
						break;
				}
				Keymapdata.push_back(std::move(keymap));
				key = head;
			}
		}
	}

	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			return;

		WCHAR* head = buf;
		int ret = GetPrivateProfileSectionW(RapidFiretxt, buf, n, m_file);
		if (ret > 0 && ret - 2 != n)
		{
			WCHAR* key = head, * value;
			while (*key != 0)
			{
				head += lstrlenW(key) + 1;
				value = wcschr(key, L'=');
				if (value == 0)
					break;
				*value++ = 0;
				int j = _wtoi(key);
				if (j <= 0 || j >= 128)
				{
					key = head;
					continue;
				}

				int mapdata[RapidFireName::RapidFire_Count] = { 0 };
				for (int i = 0; i < RapidFireName::RapidFire_Count; i++)
				{
					key = value;
					value = wcschr(key, L',');
					if (value != 0)
						*value++ = 0;
					int j = _wtoi(key);
					if (j < 0 || j >= 0x10000)
						break;
					mapdata[i] = j;
					if (value == 0)
						break;
				}
				RapidFire rf;
				rf.Enable = mapdata[RapidFireName::RapidFire_Enable] == 1;
				rf.ButtonID = (vJoyButtonID)mapdata[RapidFireName::RapidFire_Button];
				rf.ButtonID2 = (vJoyButtonID)mapdata[RapidFireName::RapidFire_Button2];
				rf.Firsttime = mapdata[RapidFireName::RapidFire_FirstTime];
				rf.Releasetime = mapdata[RapidFireName::RapidFire_Release];
				rf.Presstime = mapdata[RapidFireName::RapidFire_PressTime];
				RapidFiredata.push_back(std::move(rf));

				key = head;
			}
		}
	}

	GuardianActive = GetPrivateProfileInt(Guardiantxt, TEXT("GuardianActive"), 0, m_file) == 1 ? true : false;
	RemoveBlacklist = GetPrivateProfileInt(Guardiantxt, TEXT("RemoveBlacklist"), 1, m_file) == 1 ? true : false;
	PurgeWhitelist = GetPrivateProfileInt(Guardiantxt, TEXT("PurgeWhitelist"), 1, m_file) == 1 ? true : false;
	dsHID1Enable = GetPrivateProfileInt(Guardiantxt, TEXT("dsHID1Enable"), 0, m_file) == 1 ? true : false;
	dsHID2Enable = GetPrivateProfileInt(Guardiantxt, TEXT("dsHID2Enable"), 0, m_file) == 1 ? true : false;
	dsHID3Enable = GetPrivateProfileInt(Guardiantxt, TEXT("dsHID3Enable"), 0, m_file) == 1 ? true : false;
	Exe1NameEnable = GetPrivateProfileInt(Guardiantxt, TEXT("Exe1NameEnable"), 0, m_file) == 1 ? true : false;
	Exe2NameEnable = GetPrivateProfileInt(Guardiantxt, TEXT("Exe2NameEnable"), 0, m_file) == 1 ? true : false;
	Exe3NameEnable = GetPrivateProfileInt(Guardiantxt, TEXT("Exe3NameEnable"), 0, m_file) == 1 ? true : false;
	Exe4NameEnable = GetPrivateProfileInt(Guardiantxt, TEXT("Exe4NameEnable"), 0, m_file) == 1 ? true : false;
	Exe5NameEnable = GetPrivateProfileInt(Guardiantxt, TEXT("Exe5NameEnable"), 0, m_file) == 1 ? true : false;

	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			return;

		WCHAR* head = buf;
		int ret = GetPrivateProfileSectionW(Settingstxt, buf, n, m_file);
		if (ret == 0)
		{
			Save();
			Save(1000);
			Load();
		}

		free(buf);
	}
}

void Settings::Save(int category)
{
	WCHAR buffer[20];

	WCHAR Settingstxt[20];
	WCHAR Mappingtxt[20];
	WCHAR ViGEmtxt[20];
	WCHAR Keymaptxt[20];
	WCHAR RapidFiretxt[20];
	WCHAR Guardiantxt[20];
	wsprintf(Settingstxt, L"%dSettings", Profile);
	wsprintf(Mappingtxt, L"%dMapping", Profile);
	wsprintf(ViGEmtxt, L"%dViGEm", Profile);
	wsprintf(Keymaptxt, L"%dKeymap", Profile);
	wsprintf(RapidFiretxt, L"%dRapidFire", Profile);
	wsprintf(Guardiantxt, L"%dGuardian", Profile);

	switch (category)
	{
	case 0:
	case 1:
		wsprintf(buffer, L"%d", Profile);
		WritePrivateProfileString(TEXT("Profile"), TEXT("Profile"), buffer, m_file);
		if (category)
			break;
	case 100:
		wsprintf(buffer, L"%d", DesiredDS);
		WritePrivateProfileString(TEXT("Profile"), TEXT("PreferredDS"), buffer, m_file);
		if (category)
			break;
	case 101:
		WritePrivateProfileString(TEXT("Profile"), TEXT("Tasktray"), Tasktray ? L"1" : L"0", m_file);
		if (category)
			break;
	case 102:
		WritePrivateProfileString(TEXT("Profile"), TEXT("CloseMinimize"), CloseMinimize ? L"1" : L"0", m_file);
		if (category)
			break;
	case 103:
		WritePrivateProfileString(TEXT("Profile"), TEXT("DisconnectBT"), DisconnectBT ? L"1" : L"0", m_file);
		if (category)
			break;
	case 104:
		WritePrivateProfileString(TEXT("Profile"), TEXT("LowBattAlert"), LowBattAlert ? L"1" : L"0", m_file);
		if (category)
			break;
	case 105:
		WritePrivateProfileString(TEXT("Profile"), TEXT("dsSerial"), dsSerial, m_file);
		if (category)
			break;
	case 106:
		WritePrivateProfileString(TEXT("Profile"), TEXT("BlackLedOnExit"), BlackLedOnExit ? L"1" : L"0", m_file);
		if (category)
			break;
	case 2:
		WritePrivateProfileString(TEXT("Tray"), TEXT("vJoyPaused"), vJoyPaused ? L"1" : L"0", m_file);
		if (category)
			break;
	case 3:
		WritePrivateProfileString(TEXT("Tray"), TEXT("ViGEmPaused"), ViGEmPaused ? L"1" : L"0", m_file);
		if (category)
			break;
	case 4:
		WritePrivateProfileString(TEXT("Tray"), TEXT("KeymapPaused"), KeymapPaused ? L"1" : L"0", m_file);
		if (category)
			break;
	case 5:
		WritePrivateProfileString(TEXT("Tray"), TEXT("RapidFirePaused"), RapidFirePaused ? L"1" : L"0", m_file);
		if (category)
			break;
	case 6:
		WritePrivateProfileString(TEXT("Tray"), TEXT("GuardianPaused"), GuardianPaused ? L"1" : L"0", m_file);
		if (category)
			break;
	case 605:
		WritePrivateProfileString(TEXT("Guardian"), TEXT("dsHID1"), dsHID1, m_file);
		if (category)
			break;
	case 606:
		WritePrivateProfileString(TEXT("Guardian"), TEXT("dsHID2"), dsHID2, m_file);
		if (category)
			break;
	case 607:
		WritePrivateProfileString(TEXT("Guardian"), TEXT("dsHID3"), dsHID3, m_file);
		if (category)
			break;
	case 614:
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe1Name"), Exe1Name, m_file);
		if (category)
			break;
	case 615:
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe2Name"), Exe2Name, m_file);
		if (category)
			break;
	case 616:
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe3Name"), Exe3Name, m_file);
		if (category)
			break;
	case 617:
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe4Name"), Exe4Name, m_file);
		if (category)
			break;
	case 618:
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe5Name"), Exe5Name, m_file);
		if (category)
			break;
	case 701:
		WritePrivateProfileString(TEXT("Links"), TEXT("App1Name"), App1Name, m_file);
		if (category)
			break;
	case 702:
		WritePrivateProfileString(TEXT("Links"), TEXT("App2Name"), App2Name, m_file);
		if (category)
			break;
	case 703:
		WritePrivateProfileString(TEXT("Links"), TEXT("App3Name"), App3Name, m_file);
		if (category)
			break;
	case 704:
		WritePrivateProfileString(TEXT("Links"), TEXT("App4Name"), App4Name, m_file);
		if (category)
			break;
	case 705:
		WritePrivateProfileString(TEXT("Links"), TEXT("App5Name"), App5Name, m_file);
		if (category)
			break;
	case 706:
		WritePrivateProfileString(TEXT("Links"), TEXT("App1Location"), App1Location, m_file);
		if (category)
			break;
	case 707:
		WritePrivateProfileString(TEXT("Links"), TEXT("App2Location"), App2Location, m_file);
		if (category)
			break;
	case 708:
		WritePrivateProfileString(TEXT("Links"), TEXT("App3Location"), App3Location, m_file);
		if (category)
			break;
	case 709:
		WritePrivateProfileString(TEXT("Links"), TEXT("App4Location"), App4Location, m_file);
		if (category)
			break;
	case 710:
		WritePrivateProfileString(TEXT("Links"), TEXT("App5Location"), App5Location, m_file);
		if (category)
			break;
	case 107:
		wsprintf(buffer, L"%d", Threshold);
		WritePrivateProfileString(Settingstxt, TEXT("Threshold"), buffer, m_file);
		if (category)
			break;
	case 108:
		wsprintf(buffer, L"%d", Simultaneous);
		WritePrivateProfileString(Settingstxt, TEXT("Simultaneous"), buffer, m_file);
		if (category)
			break;
	case 109:
		wsprintf(buffer, L"%d", LongPress);
		WritePrivateProfileString(Settingstxt, TEXT("LongPress"), buffer, m_file);
		if (category)
			break;
	case 110:
		wsprintf(buffer, L"%d", VeryLongPress);
		WritePrivateProfileString(Settingstxt, TEXT("VeryLongPress"), buffer, m_file);
		if (category)
			break;
	case 111:
		WritePrivateProfileString(Settingstxt, TEXT("FFB"), FFB ? L"1" : L"0", m_file);
		if (category)
			break;
	case 112:
		wsprintf(buffer, L"%d", TriggersMode);
		WritePrivateProfileString(Settingstxt, TEXT("TriggersMode"), buffer, m_file);
		if (category)
			break;
	case 113:
		wsprintf(buffer, L"%d", vJoyDeviceID);
		WritePrivateProfileString(Settingstxt, TEXT("vJoyDeviceID"), buffer, m_file);
		if (category)
			break;
	case 114:
		wsprintf(buffer, L"%d", TouchPadButton);
		WritePrivateProfileString(Settingstxt, TEXT("TouchPadButton"), buffer, m_file);
		SetSplitTouch();
		if (category)
			break;
	case 115:
		wsprintf(buffer, L"%d", TouchCol);
		WritePrivateProfileString(Settingstxt, TEXT("TouchCol"), buffer, m_file);
		if (category)
			break;
	case 116:
		wsprintf(buffer, L"%d", TouchRow);
		WritePrivateProfileString(Settingstxt, TEXT("TouchRow"), buffer, m_file);
		if (category)
			break;
	case 117:
		wsprintf(buffer, L"%d", LED_Color);
		WritePrivateProfileString(Settingstxt, TEXT("LED_Color"), buffer, m_file);
		if (category)
			break;
	case 200:
	{
		const int n = sizeof(WCHAR) * 32 * 1024 *2;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;

		memset(buf, 0, n);
		WCHAR* head = buf;
		size_t length = Mappingdata.size();
		for (int i = 0; i < length; i++)
		{
			int mapdata[MappingName::Mapping_Count] = { 0 };
			Mapping* btn = &Mappingdata[i];
			mapdata[MappingName::Mapping_Enable] = btn->Enable;
			mapdata[MappingName::Mapping_ds_1] = btn->dsID[0];
			mapdata[MappingName::Mapping_ds_2] = btn->dsID[1];
			mapdata[MappingName::Mapping_ds_3] = btn->dsID[2];
			mapdata[MappingName::Mapping_ds_4] = btn->dsID[3];
			mapdata[MappingName::Mapping_ds_5] = btn->dsID[4];
			mapdata[MappingName::Mapping_Target_1] = btn->Target[0];
			mapdata[MappingName::Mapping_Target_2] = btn->Target[1];
			mapdata[MappingName::Mapping_Target_3] = btn->Target[2];
			mapdata[MappingName::Mapping_Target_4] = btn->Target[3];
			mapdata[MappingName::Mapping_Target_5] = btn->Target[4];
			mapdata[MappingName::Mapping_vJoy_source_1] = btn->vjID[0];
			mapdata[MappingName::Mapping_vJoy_source_2] = btn->vjID[1];
			mapdata[MappingName::Mapping_vJoy_source_3] = btn->vjID[2];
			mapdata[MappingName::Mapping_vJoy_source_4] = btn->vjID[3];
			mapdata[MappingName::Mapping_vJoy_source_5] = btn->vjID[4];
			mapdata[MappingName::Mapping_ds_1_Disable] = btn->Disbale[0];
			mapdata[MappingName::Mapping_ds_2_Disable] = btn->Disbale[1];
			mapdata[MappingName::Mapping_ds_3_Disable] = btn->Disbale[2];
			mapdata[MappingName::Mapping_ds_4_Disable] = btn->Disbale[3];
			mapdata[MappingName::Mapping_ds_5_Disable] = btn->Disbale[4];
			mapdata[MappingName::Mapping_OrXorNot_1] = btn->OrXorNot[0];
			mapdata[MappingName::Mapping_OrXorNot_2] = btn->OrXorNot[1];
			mapdata[MappingName::Mapping_OrXorNot_3] = btn->OrXorNot[2];
			mapdata[MappingName::Mapping_OrXorNot_4] = btn->OrXorNot[3];
			mapdata[MappingName::Mapping_If_mouse] = btn->Ifmouse;
			mapdata[MappingName::Mapping_Force] = btn->Force;
			mapdata[MappingName::Mapping_led] = btn->Led;
			mapdata[MappingName::Mapping_Short] = btn->Short;
			mapdata[MappingName::Mapping_Double] = btn->Double;
			mapdata[MappingName::Mapping_Long] = btn->Long;
			mapdata[MappingName::Mapping_Macro] = btn->Macro;
			mapdata[MappingName::Mapping_Toggle] = btn->Toggle;
			mapdata[MappingName::Mapping_vJoy_1] = btn->vjID[5];
			mapdata[MappingName::Mapping_vJoy_2] = btn->vjID[6];
			mapdata[MappingName::Mapping_vJoy_3] = btn->vjID[7];
			mapdata[MappingName::Mapping_vJoy_4] = btn->vjID[8];
			mapdata[MappingName::Mapping_vJoy_5] = btn->vjID[9];
			mapdata[MappingName::Mapping_vJoy_6] = btn->vjID[10];
			mapdata[MappingName::Mapping_vJoy_7] = btn->vjID[11];
			mapdata[MappingName::Mapping_vJoy_8] = btn->vjID[12];
			mapdata[MappingName::Mapping_On_release_1] = btn->OnRelease[0];
			mapdata[MappingName::Mapping_On_release_2] = btn->OnRelease[1];
			mapdata[MappingName::Mapping_On_release_3] = btn->OnRelease[2];
			mapdata[MappingName::Mapping_On_release_4] = btn->OnRelease[3];
			mapdata[MappingName::Mapping_On_release_5] = btn->OnRelease[4];
			mapdata[MappingName::Mapping_On_release_6] = btn->OnRelease[5];
			mapdata[MappingName::Mapping_On_release_7] = btn->OnRelease[6];
			mapdata[MappingName::Mapping_On_release_8] = btn->OnRelease[7];
			mapdata[MappingName::Mapping_vJoy_1_Disable] = btn->Disbale[5];
			mapdata[MappingName::Mapping_vJoy_2_Disable] = btn->Disbale[6];
			mapdata[MappingName::Mapping_vJoy_3_Disable] = btn->Disbale[7];
			mapdata[MappingName::Mapping_vJoy_4_Disable] = btn->Disbale[8];
			mapdata[MappingName::Mapping_vJoy_5_Disable] = btn->Disbale[9];
			mapdata[MappingName::Mapping_vJoy_6_Disable] = btn->Disbale[10];
			mapdata[MappingName::Mapping_vJoy_7_Disable] = btn->Disbale[11];
			mapdata[MappingName::Mapping_vJoy_8_Disable] = btn->Disbale[12];
			mapdata[MappingName::Mapping_Start_1] = btn->Start[0];
			mapdata[MappingName::Mapping_Start_2] = btn->Start[1];
			mapdata[MappingName::Mapping_Start_3] = btn->Start[2];
			mapdata[MappingName::Mapping_Start_4] = btn->Start[3];
			mapdata[MappingName::Mapping_Start_5] = btn->Start[4];
			mapdata[MappingName::Mapping_Start_6] = btn->Start[5];
			mapdata[MappingName::Mapping_Start_7] = btn->Start[6];
			mapdata[MappingName::Mapping_Start_8] = btn->Start[7];
			mapdata[MappingName::Mapping_Stop_1] = btn->Stop[0];
			mapdata[MappingName::Mapping_Stop_2] = btn->Stop[1];
			mapdata[MappingName::Mapping_Stop_3] = btn->Stop[2];
			mapdata[MappingName::Mapping_Stop_4] = btn->Stop[3];
			mapdata[MappingName::Mapping_Stop_5] = btn->Stop[4];
			mapdata[MappingName::Mapping_Stop_6] = btn->Stop[5];
			mapdata[MappingName::Mapping_Stop_7] = btn->Stop[6];
			mapdata[MappingName::Mapping_Stop_8] = btn->Stop[7];
			mapdata[MappingName::Mapping_Mouse_action_1] = btn->MouseAction[0];
			mapdata[MappingName::Mapping_Mouse_action_2] = btn->MouseAction[1];
			mapdata[MappingName::Mapping_Mouse_action_3] = btn->MouseAction[2];
			mapdata[MappingName::Mapping_Mouse_action_4] = btn->MouseAction[3];
			mapdata[MappingName::Mapping_Mouse_1] = btn->Mouse[0];
			mapdata[MappingName::Mapping_Mouse_2] = btn->Mouse[1];
			mapdata[MappingName::Mapping_Mouse_3] = btn->Mouse[2];
			mapdata[MappingName::Mapping_Mouse_4] = btn->Mouse[3];
			mapdata[MappingName::Mapping_Mouse_5] = btn->Mouse[4];
			mapdata[MappingName::Mapping_Mouse_6] = btn->Mouse[5];
			mapdata[MappingName::Mapping_Mouse_Grid] = btn->Mouse[6];
			mapdata[MappingName::Mapping_Grid_x] = btn->Grid[0];
			mapdata[MappingName::Mapping_Grid_y] = btn->Grid[1];
			mapdata[MappingName::Mapping_Grid_w] = btn->Grid[2];
			mapdata[MappingName::Mapping_Grid_h] = btn->Grid[3];
			mapdata[MappingName::Mapping_Grid_nw] = btn->Grid[4];
			mapdata[MappingName::Mapping_Grid_nh] = btn->Grid[5];

			head += wsprintf(head, L"%d=", i + 1);
			for (int j = 0; j < MappingName::Mapping_Count; j++)
				head += wsprintf(head, L"%d,", mapdata[j]);
			head++;
		}
		WritePrivateProfileSection(Mappingtxt, buf, m_file);
		if (category)
			break;
	}
	case 306:
		WritePrivateProfileString(ViGEmtxt, TEXT("ViGEmActive"), ViGEmActive ? L"1" : L"0", m_file);
		if (category)
			break;
	case 307:
		wsprintf(buffer, L"%d", DesiredVirtualPad);
		WritePrivateProfileString(ViGEmtxt, TEXT("DesiredVirtualPad"), buffer, m_file);
		if (category)
			break;
	case 300:
	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;

		memset(buf, 0, n);
		WCHAR* head = buf;
		for (int i = 0; i < 24; i++)
			head += wsprintf(head, L"%d,", target_X360[i]);
		WritePrivateProfileString(ViGEmtxt, TEXT("1"), buf, m_file);
		if (category)
			break;
	}
	case 301:
	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;
		memset(buf, 0, n);
		WCHAR* head = buf;
		for (int i = 0; i < 24; i++)
			head += wsprintf(head, L"%d,", dstarget_X360[i]);
		WritePrivateProfileString(ViGEmtxt, TEXT("2"), buf, m_file);
		if (category)
			break;
	}
	case 302:
	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;

		memset(buf, 0, n);
		WCHAR* head = buf;
		for (int i = 0; i < 24; i++)
			head += wsprintf(head, L"%d,", vjtarget_X360[i]);
		WritePrivateProfileString(ViGEmtxt, TEXT("3"), buf, m_file);
		if (category)
			break;
	}
	case 303:
	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;

		memset(buf, 0, n);
		WCHAR* head = buf;
		for (int i = 0; i < 24; i++)
			head += wsprintf(head, L"%d,", target_DS4[i]);
		WritePrivateProfileString(ViGEmtxt, TEXT("4"), buf, m_file);
		if (category)
			break;
	}
	case 304:
	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;

		memset(buf, 0, n);
		WCHAR* head = buf;
		for (int i = 0; i < 24; i++)
			head += wsprintf(head, L"%d,", dstarget_DS4[i]);
		WritePrivateProfileString(ViGEmtxt, TEXT("5"), buf, m_file);
		if (category)
			break;
	}
	case 305:
	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;

		memset(buf, 0, n);
		WCHAR* head = buf;
		for (int i = 0; i < 24; i++)
			head += wsprintf(head, L"%d,", vjtarget_DS4[i]);
		WritePrivateProfileString(ViGEmtxt, TEXT("6"), buf, m_file);
		if (category)
			break;
	}
	case 400:
	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;

		memset(buf, 0, n);
		WCHAR* head = buf;
		size_t length = Keymapdata.size();
		for (int i = 0; i < length; ++i)
		{
			Keymap* keymap = &Keymapdata[i];
			if (keymap->vk.empty())
				continue;
			head += wsprintf(head, L"%d=%d,%d,%d,", keymap->ButtonID, keymap->Enable ? 1 : 0, keymap->usePostmessage ? 1 : 0, keymap->useActivating ? 1 : 0);
			for (auto itr = keymap->vk.begin(); itr != keymap->vk.end(); ++itr)
			{
				if (*itr == 0)
					break;
				head += wsprintf(head, L"%d,", *itr);
			}
			head += wsprintf(head, L"**,%s", keymap->findWindow.Val().c_str());
			head++;
		}
		WritePrivateProfileSection(Keymaptxt, buf, m_file);
		if (category)
			break;
	}
	case 500:
	{
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;

		memset(buf, 0, n);
		WCHAR* head = buf;
		size_t length = RapidFiredata.size();
		for (int i = 0; i < length; i++)
		{
			int mapdata[RapidFireName::RapidFire_Count] = { 0 };
			RapidFire* rf = &RapidFiredata[i];
			mapdata[RapidFireName::RapidFire_Enable] = rf->Enable;
			mapdata[RapidFireName::RapidFire_Button] = rf->ButtonID;
			mapdata[RapidFireName::RapidFire_Button2] = rf->ButtonID2;
			mapdata[RapidFireName::RapidFire_FirstTime] = rf->Firsttime;
			mapdata[RapidFireName::RapidFire_Release] = rf->Releasetime;
			mapdata[RapidFireName::RapidFire_PressTime] = rf->Presstime;

			head += wsprintf(head, L"%d=", i + 1);
			for (int j = 0; j < RapidFireName::RapidFire_Count; j++)
				head += wsprintf(head, L"%d,", mapdata[j]);
			head++;
		}
		WritePrivateProfileSection(RapidFiretxt, buf, m_file);
		free(buf);
		if (category)
			break;
	}
	case 601:
		WritePrivateProfileString(Guardiantxt, TEXT("GuardianActive"), GuardianActive ? L"1" : L"0", m_file);
		if (category)
			break;
	case 608:
		WritePrivateProfileString(Guardiantxt, TEXT("RemoveBlacklist"), RemoveBlacklist ? L"1" : L"0", m_file);
		if (category)
			break;
	case 619:
		WritePrivateProfileString(Guardiantxt, TEXT("PurgeWhitelist"), PurgeWhitelist ? L"1" : L"0", m_file);
		if (category)
			break;
	case 602:
		WritePrivateProfileString(Guardiantxt, TEXT("dsHID1Enable"), dsHID1Enable ? L"1" : L"0", m_file);
		if (category)
			break;
	case 603:
		WritePrivateProfileString(Guardiantxt, TEXT("dsHID2Enable"), dsHID2Enable ? L"1" : L"0", m_file);
		if (category)
			break;
	case 604:
		WritePrivateProfileString(Guardiantxt, TEXT("dsHID3Enable"), dsHID3Enable ? L"1" : L"0", m_file);
		if (category)
			break;
	case 609:
		WritePrivateProfileString(Guardiantxt, TEXT("Exe1NameEnable"), Exe1NameEnable ? L"1" : L"0", m_file);
		if (category)
			break;
	case 610:
		WritePrivateProfileString(Guardiantxt, TEXT("Exe2NameEnable"), Exe2NameEnable ? L"1" : L"0", m_file);
		if (category)
			break;
	case 611:
		WritePrivateProfileString(Guardiantxt, TEXT("Exe3NameEnable"), Exe3NameEnable ? L"1" : L"0", m_file);
		if (category)
			break;
	case 612:
		WritePrivateProfileString(Guardiantxt, TEXT("Exe4NameEnable"), Exe4NameEnable ? L"1" : L"0", m_file);
		if (category)
			break;
	case 613:
		WritePrivateProfileString(Guardiantxt, TEXT("Exe5NameEnable"), Exe5NameEnable ? L"1" : L"0", m_file);
		if (category)
			break;
		break;
	case 1000:
		const int n = sizeof(WCHAR) * 32 * 1024;
		WCHAR* buf = (WCHAR*)malloc(n);
		if (buf == 0)
			break;

		memset(buf, 0, n);
		WCHAR* head = buf;

		head += wsprintf(head, L"1=1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"2=1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"3=1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"4=1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"5=1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,57,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"6=1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,58,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"7=1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,59,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"8=1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"9=1,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,61,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"10=1,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"11=1,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"12=1,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"13=1,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"14=1,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"15=1,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,67,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"16=1,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"17=1,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,69,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"18=1,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"19=1,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,71,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"20=1,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"21=1,21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"22=1,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,74,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"23=1,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,75,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"24=1,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		head += wsprintf(head, L"25=1,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"); head++;
		
		WritePrivateProfileSection(Mappingtxt, buf, m_file);
		break;
	}
}

void Settings::SetProfile(int i)
{
	if (i > 0 && i < 4)
		Profile = i;
	else
		Profile = 1;
}

void Settings::SetDesiredDS(int i)
{
	if (i > 0 && i < 3)
		DesiredDS = i;
	else
		DesiredDS = 2;
}

void Settings::SetThreshold(int i)
{
	if (i >= 0 && i <= 100)
		Threshold = i;
	else
		Threshold = 7;
}

void Settings::SetSimultaneous(int i)
{
	if (i > 0 && i < 10000)
		Simultaneous = i;
	else
		Simultaneous = 40;
}

void Settings::SetLongPress(int i)
{
	if (i > 0 && i < 10000)
		LongPress = i;
	else
		LongPress = 255;
}

void Settings::SetVeryLongPress(int i)
{
	if (i > 0 && i < 10000)
		VeryLongPress = i;
	else
		VeryLongPress = 3287;
}

void Settings::SetDesiredVirtualPad(int i)
{
	if (i > 0 && i < 3)
		DesiredVirtualPad = i;
	else
		DesiredVirtualPad = 2;
}

void Settings::setvJoyDeviceID(int id)
{
	if (id > 0 && id < 17)
		vJoyDeviceID = id;
	else
		vJoyDeviceID = 1;
}

void Settings::SetSplitTouch()
{
	if (TouchPadButton && TouchPadButton <= 128)
		SplitTouch = true;
	else
		SplitTouch = false;
}

void Settings::SetTouchPadButton(DWORD n)
{
	if (n <= 128)
		TouchPadButton = n;
	else
		TouchPadButton = 0;
}

void Settings::SetTouchRow(int i)
{
	if (i > 0 && i < 10)
		TouchRow = i;
	else
		TouchRow = 1;
}

void Settings::SetTouchCol(int i)
{
	if (i > 0 && i < 10)
		TouchCol = i;
	else
		TouchCol = 1;
}

void Settings::SetLED(DWORD i)
{
	if (i >= 0 && i <= 0xFFFFFF)
		LED_Color = i;
}

void Settings::SetTriggersMode(int i)
{
	if (i >= 0 && i < 4)
		TriggersMode = i;
	else
		TriggersMode = 0;
}

const WCHAR* Settings::getSerial()
{
	return dsSerial;
}

void Settings::setSerial(const WCHAR* buf)
{
	lstrcpynW(dsSerial, buf, sizeof(dsSerial) / sizeof(dsSerial[0]));
}

const std::string Settings::getHID(int ds)
{
	switch (ds)
	{
	case 1:
		return rws2s(dsHID1);
	case 2:
		return rws2s(dsHID2);
	case 3:
		return rws2s(dsHID3);
	default:
		return "";
	}
}

void Settings::setPID(const WCHAR* buf, int ds)
{
	switch (ds)
	{
	case 1:
		lstrcpynW(dsHID1, buf, sizeof(dsHID1) / sizeof(dsHID1[0]));
		break;
	case 2:
		lstrcpynW(dsHID2, buf, sizeof(dsHID2) / sizeof(dsHID2[0]));
		break;
	case 3:
		lstrcpynW(dsHID3, buf, sizeof(dsHID3) / sizeof(dsHID3[0]));
		break;
	}
}

void Settings::setExeName(const WCHAR* buf, int exe)
{
	switch (exe)
	{
	case 1:
		lstrcpynW(Exe1Name, buf, sizeof(Exe1Name) / sizeof(Exe1Name[0]));
		break;
	case 2:
		lstrcpynW(Exe2Name, buf, sizeof(Exe2Name) / sizeof(Exe2Name[0]));
		break;
	case 3:
		lstrcpynW(Exe3Name, buf, sizeof(Exe3Name) / sizeof(Exe3Name[0]));
		break;
	case 4:
		lstrcpynW(Exe4Name, buf, sizeof(Exe4Name) / sizeof(Exe4Name[0]));
		break;
	case 5:
		lstrcpynW(Exe5Name, buf, sizeof(Exe5Name) / sizeof(Exe5Name[0]));
		break;
	}
}

void Settings::setAppName(const WCHAR* buf, int app)
{
	switch (app)
	{
	case 1:
		lstrcpynW(App1Name, buf, sizeof(App1Name) / sizeof(App1Name[0]));
		break;
	case 2:
		lstrcpynW(App2Name, buf, sizeof(App2Name) / sizeof(App2Name[0]));
		break;
	case 3:
		lstrcpynW(App3Name, buf, sizeof(App3Name) / sizeof(App3Name[0]));
		break;
	case 4:
		lstrcpynW(App4Name, buf, sizeof(App4Name) / sizeof(App4Name[0]));
		break;
	case 5:
		lstrcpynW(App5Name, buf, sizeof(App5Name) / sizeof(App5Name[0]));
		break;
	}
}

void Settings::setAppLocation(const WCHAR* buf, int app)
{
	switch (app)
	{
	case 1:
		lstrcpynW(App1Location, buf, sizeof(App1Location) / sizeof(App1Location[0]));
		break;
	case 2:
		lstrcpynW(App2Location, buf, sizeof(App2Location) / sizeof(App2Location[0]));
		break;
	case 3:
		lstrcpynW(App3Location, buf, sizeof(App3Location) / sizeof(App3Location[0]));
		break;
	case 4:
		lstrcpynW(App4Location, buf, sizeof(App4Location) / sizeof(App4Location[0]));
		break;
	case 5:
		lstrcpynW(App5Location, buf, sizeof(App5Location) / sizeof(App5Location[0]));
		break;
	}
}
