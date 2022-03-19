#include "stdafx.h"
#include "Settings.h"

Settings::Settings()
{
}

Settings::~Settings()
{
	DeleteObject(hB_BackGround);
	DeleteObject(hB_CLONE_BackGround);
	DeleteObject(hB_DLG);
	DeleteObject(hB_MSGBOX);
	DeleteObject(hB_SCROLLBAR);
	DeleteObject(hB_BTN);
	DeleteObject(hB_BTN_Border);
	DeleteObject(hB_Not_Installed);
	DeleteObject(hB_Running);
	DeleteObject(hB_Stopped);
	DeleteObject(hB_Paused);
	DeleteObject(hB_STATIC);
	DeleteObject(hB_STATIC_Mouse1);
	DeleteObject(hB_STATIC_Mouse2);
	DeleteObject(hB_POSTIT);
	DeleteObject(hB_POSTIT_Rand0);
	DeleteObject(hB_POSTIT_Rand1);
	DeleteObject(hB_POSTIT_Rand2);
	DeleteObject(hB_POSTIT_Rand3);
	DeleteObject(hB_EDIT);
	DeleteObject(hB_LIST);
	DeleteObject(hB_LIST_HIGHLIGHT);
	DeleteObject(hB_LIST_Disable1);
	DeleteObject(hB_LIST_Disable2);
	DeleteObject(hB_LIST_Disabled);
	DeleteObject(hB_MENU);
	DeleteObject(hB_MENU_CLONE);
	DeleteObject(hB_MENU_SELECTED);
	DeleteObject(hB_MENU_HIGHLIGHT);
	DeleteObject(hB_CHECKBOX_UNCHECKED);
	DeleteObject(hB_CHECKBOX_CHECKED);
	DeleteObject(hB_CHECKBOX_INDETERMINATE);
	DeleteObject(hB_WEB_BackGround);
	DeleteObject(hB_neutral);
	DeleteObject(hB_black);
	DeleteObject(hB_white);
	DeleteObject(hB_grey);
	DeleteObject(hB_red);
	DeleteObject(hB_orange);
	DeleteObject(hB_yellow);
	DeleteObject(hB_emerald);
	DeleteObject(hB_green);
	DeleteObject(hB_blue);
	DeleteObject(hB_purple);
	DeleteObject(hB_bright_grey);
	DeleteObject(hB_bright_red);
	DeleteObject(hB_bright_orange);
	DeleteObject(hB_bright_yellow);
	DeleteObject(hB_bright_emerald);
	DeleteObject(hB_bright_green);
	DeleteObject(hB_bright_blue);
	DeleteObject(hB_bright_purple);
	DeleteObject(hB_WEB_BackGround);
	
	DeleteObject(hLog);
	DeleteObject(hNotepad);
	DeleteObject(hStatus);
	DeleteObject(hTab1);
	DeleteObject(hPostIt);
	DeleteObject(hLegend);
	DeleteObject(hLegend2);
	DeleteObject(hLegend3);
	DeleteObject(hLegend4);
	DeleteObject(hEdit);
	DeleteObject(hCheck2);
	DeleteObject(hCheck3);
	DeleteObject(hCombo);
	DeleteObject(hCombo2);
	DeleteObject(hEdit2);
	DeleteObject(hEdit3);
	DeleteObject(hButton);
	DeleteObject(hButton2);
	DeleteObject(hStatic);
	DeleteObject(hMenus);
	DeleteObject(hLinks);
	DeleteObject(hList);
	DeleteObject(hStats);
	DeleteObject(hTopMost);
	DeleteObject(hAbout);
	DeleteObject(hTooltip);
	DeleteObject(hDelete);
}

void Settings::Init(HINSTANCE hInst, HWND hWnd)
{
	Ds2hWnd = hWnd;
	Ds2hInst = hInst;
}

BOOL Settings::Open(WCHAR* file)
{
	wcscpy_s(m_file, wcslen(file) + 1, file);
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
			swprintf_s(m_file, MAX_PATH + 1, L"%s%s", dir, inifile);
			return TRUE;
		}
	}
	return FALSE;
}

void Settings::Load(int category)
{
	if (m_file[0] == 0)
		return;

	if (category != Setting_Category_Create && category != Setting_Category_Update)
	{
		Profile = GetPrivateProfileInt(TEXT("Profile"), TEXT("Profile"), 0, m_file);
		if (Profile == 0)
		{
			HANDLE hf;
			hf = CreateFile(m_file, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
			DWORD writtenBytes = 0;
			WORD bom = 0xFEFF;
			WriteFile(hf, &bom, sizeof(bom), &writtenBytes, NULL);
			CloseHandle(hf);

			SendMessage(Ds2hWnd, WM_RESET, 0, 0);
			for (int i = 1; i < 4; i++)
			{
				Profile = i;
				Load(Setting_Category_Create);
				Save(Setting_All);
				SendMessage(Ds2hWnd, WM_RESET, 0, 0);
			}
			Profile = 1;
			Save(Setting_Profile);
			Save(Setting_GiveMapping);
			Load(Setting_Category_Mapping);
			return;
		}
	}
	setProfile(Profile);

	swprintf_s(Settingstxt, 20, L"%dSettings", Profile);
	swprintf_s(Mappingtxt, 20, L"%dMapping", Profile);
	swprintf_s(ViGEmtxt, 20, L"%dViGEm", Profile);
	swprintf_s(Keymaptxt, 20, L"%dKeymap", Profile);
	swprintf_s(RapidFiretxt, 20, L"%dRapidFire", Profile);
	swprintf_s(Guardiantxt, 20, L"%dGuardian", Profile);
	swprintf_s(Webtxt, 20, L"%dWeb", Profile);

	int VersionDateCheck = max(0, GetPrivateProfileInt(TEXT("Profile"), TEXT("VersionDate"), 0, m_file));
	if (VersionDateCheck && VersionDateCheck < 202112101)
	{
		RECT win;
		GetWindowRect(Ds2hWnd, &win);
		MessageBoxPos(Ds2hWnd, L"Your .ini file is too old\nto be updated with this version,\nuse 20211210-1 before this one", I18N.MBOX_ErrTitle, MB_ICONERROR, win.left, win.top + 30);
		BreakAndExit = true;
		return;
	}

	if (category == Setting_Category_All && category != Setting_Category_Create && category != Setting_Category_Update)
	{
		if (VersionDateCheck < VersionDate)
		{
			unsigned char ProfileNumberSaved = Profile;
			for (int i = 1; i < 4; i++)
			{
				SendMessage(Ds2hWnd, WM_RESET, 0, 0);
				Profile = i;
				Load(Setting_Category_Update);
				Save(Setting_Update);
			}
			Profile = ProfileNumberSaved;
			Save(Setting_Profile);
			Save(Setting_Version);
			SendMessage(Ds2hWnd, WM_RESET, 0, 0);
			Load(Setting_Category_All);
			return;
		}
	}

	bool Create = false;
	bool Update = false;
	switch (category)
	{
	case Setting_Category_Create:
	{
		Create = true;
		[[fallthrough]];
	}
	case Setting_Category_Update:
	{
		if (!Create)
			Update = true;
		category = Setting_Category_All;
		[[fallthrough]];
	}
	case Setting_Category_All:
		[[fallthrough]];
	case Setting_Category_Profile:
	{
		TopMost = (GetPrivateProfileInt(TEXT("Profile"), TEXT("TopMost"), 0, m_file) == 1) ? true : false;
		Transparency = (GetPrivateProfileInt(TEXT("Profile"), TEXT("Transparency"), 0, m_file) == 1) ? true : false;
		Tasktray = (GetPrivateProfileInt(TEXT("Profile"), TEXT("Tasktray"), 0, m_file) == 1) ? true : false;
		CloseMinimize = (GetPrivateProfileInt(TEXT("Profile"), TEXT("CloseMinimize"), 0, m_file) == 1) ? true : false;
		DisconnectBT = (GetPrivateProfileInt(TEXT("Profile"), TEXT("DisconnectBT"), 0, m_file) == 1) ? true : false;
		LowBattAlert = (GetPrivateProfileInt(TEXT("Profile"), TEXT("LowBattAlert"), 1, m_file) == 1) ? true : false;
		GetPrivateProfileString(L"Profile", L"dsSerial", L"", dsSerial, sizeof(dsSerial) / sizeof(dsSerial[0]), m_file);
		BlackLedOnExit = (GetPrivateProfileInt(TEXT("Profile"), TEXT("BlackLedOnExit"), 1, m_file) == 1) ? true : false;
		MappingViewMode = (GetPrivateProfileInt(TEXT("Profile"), TEXT("MappingViewMode"), 0, m_file) == 1) ? true : false;
		CloneViewMode = (GetPrivateProfileInt(TEXT("Profile"), TEXT("CloneViewMode"), 0, m_file) == 1) ? true : false;
		{
			WCHAR buf[MAX_PATH] = { 0 };
			GetPrivateProfileString(L"Profile", L"NotepadFont", L"NotepadFont,16,0", buf, MAX_PATH, m_file);
			std::wstringstream ss(buf);
			std::wstring substr;
			getline(ss, substr, L',');
			NotepadFont = substr;
			getline(ss, substr, L',');
			NotepadFontH = _wtoi(substr.c_str());
			getline(ss, substr, L',');
			NotepadFontW = _wtoi(substr.c_str());
		}
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_Tray:
	{
		vJoyPaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("vJoyPaused"), 0, m_file) == 1) ? true : false;
		RapidFirePaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("RapidFirePaused"), 0, m_file) == 1) ? true : false;
		KeymapPaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("KeymapPaused"), 0, m_file) == 1) ? true : false;
		ViGEmPaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("ViGEmPaused"), 0, m_file) == 1) ? true : false;
		GuardianPaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("GuardianPaused"), 0, m_file) == 1) ? true : false;
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_Settings:
	{
		setOpacity(GetPrivateProfileInt(Settingstxt, TEXT("Opacity"), 60, m_file));
		setPreferredDS(GetPrivateProfileInt(Settingstxt, TEXT("PreferredDS"), 0, m_file));
		MouseActive = (GetPrivateProfileInt(Settingstxt, TEXT("MouseActive"), 0, m_file) == 1) ? true : false;
		KeyboardActive = (GetPrivateProfileInt(Settingstxt, TEXT("KeyboardActive"), 0, m_file) == 1) ? true : false;
		setvJoyDeviceID(GetPrivateProfileInt(Settingstxt, TEXT("vJoyDeviceID"), 1, m_file));
		setThreshold(GetPrivateProfileInt(Settingstxt, TEXT("Threshold"), 8, m_file));
		setSimultaneous(GetPrivateProfileInt(Settingstxt, TEXT("Simultaneous"), 40, m_file));
		setLongPress(GetPrivateProfileInt(Settingstxt, TEXT("LongPress"), 255, m_file));
		setVeryLongPress(GetPrivateProfileInt(Settingstxt, TEXT("VeryLongPress"), 3287, m_file));
		MouseCanBypass = (GetPrivateProfileInt(Settingstxt, TEXT("MouseCanBypass"), 0, m_file) == 1) ? true : false;
		setTriggersMode(GetPrivateProfileInt(Settingstxt, TEXT("TriggersMode"), 0, m_file));
		DarkTheme = (GetPrivateProfileInt(Settingstxt, TEXT("DarkTheme"), 0, m_file) == 1) ? true : false;
		setTouchPadButton(GetPrivateProfileInt(Settingstxt, TEXT("TouchPadButton"), 0, m_file));
		setSplitTouch();
		setTouchCol(GetPrivateProfileInt(Settingstxt, TEXT("TouchCol"), 1, m_file));
		setTouchRow(GetPrivateProfileInt(Settingstxt, TEXT("TouchRow"), 1, m_file));
		setLED(GetPrivateProfileInt(Settingstxt, TEXT("LED_Color"), 0xFF0000, m_file));
		setWaveSpeed(GetPrivateProfileInt(Settingstxt, TEXT("WaveSpeed"), 130, m_file));
		setTabMapping(GetPrivateProfileInt(Settingstxt, TEXT("TabMapping"), 0, m_file));

		{
			WCHAR buf[MAX_PATH] = { 0 };
			GetPrivateProfileString(Settingstxt, L"TabToMode", L"0,0,0,0,0,0,0,0,0", buf, sizeof(buf) / sizeof(buf[0]), m_file);
			std::wstringstream ss(buf);
			for (int i = 0; i < 9; i++)
			{
				std::wstring substr;
				getline(ss, substr, L',');
				setTabMode(i, _wtoi(substr.c_str()));
			}
		}

		{
			WCHAR buf[MAX_PATH] = { 0 };
			GetPrivateProfileString(Settingstxt, L"Reminder", L"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0", buf, sizeof(buf) / sizeof(buf[0]), m_file);
			std::wstringstream ss(buf);
			for (int i = 0; i < 32; i++)
			{
				std::wstring substr;
				getline(ss, substr, L',');
				setReminder(i, _wtoi(substr.c_str()));
			}
		}

		{
			WCHAR buf[MAX_PATH] = { 0 };
			GetPrivateProfileString(Settingstxt, L"Stats", L"0,0,0,0,0,0,0,0", buf, sizeof(buf) / sizeof(buf[0]), m_file);
			std::wstringstream ss(buf);
			for (int i = 0; i < 8; i++)
			{
				std::wstring substr;
				getline(ss, substr, L',');
				setStats(i, _wtoi(substr.c_str()));
			}
		}

		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_Mapping:
	{
		if (!Create)
		{
			const int n = 512 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0)
			{
				MessageBoxPos(Ds2hWnd, L"Not enough memory\nto load mappings,\nany modification\nwill be lost on exit.", L"Careful", MB_OK, 0, 0, 180);
				cansavemappings = false;
			}
			else
			{
				WCHAR* head = buf;
				int ret = GetPrivateProfileSectionW(Mappingtxt, buf, n, m_file);
				if (ret > 0 && ret - 2 != n)
				{
					WCHAR* key = head, * value;
					while (*key != 0)
					{
						head += wcslen(key) + 1;
						value = wcschr(key, L'=');
						if (value == 0)
							break;
						*value++ = 0;
						int j = _wtoi(key);
						if (j < 1 || j > 512)
						{
							key = head;
							continue;
						}

						Mapping btn;
						for (int i = 0; i < MappingName::Mapping_Count; i++)
						{
							key = value;
							value = wcschr(key, L',');
							if (value != 0)
								*value++ = 0;
							switch (i)
							{
							case Mapping_Enable: { btn.Enable = max(0, min(2, _wtoi(key))); break; }
							case Mapping_Tab: { btn.Tab = max(0, min(8, _wtoi(key))); break; }
							case Mapping_Ifmouse: { btn.Ifmouse = max(0, min(2, _wtoi(key))); break; }
							case Mapping_Force: { btn.Force = max(0, min(2, _wtoi(key))); break; }
							case Mapping_Short: { btn.Short = _wtoi(key) == 1; break; }
							case Mapping_Double: { btn.Double = _wtoi(key) == 1; break; }
							case Mapping_Long: { btn.Long = _wtoi(key) == 1; break; }
							case Mapping_Led: { btn.Led = max(0, min(6, _wtoi(key))); break; }
							case Mapping_Macro: { btn.Macro = max(0, min(2, _wtoi(key))); break; }
							case Mapping_Pause: { btn.Pause = max(0, min(2, _wtoi(key))); break; }
							case Mapping_Transitivity: { btn.Transitivity = max(0, min(2, _wtoi(key))); break; }
							case Mapping_Toggle: { btn.Toggle = max(0, min(2, _wtoi(key))); break; }
							case Mapping_Target: { for (int i = 0; i < 5; i++) { btn.Target[i] = CheckboxString(key, i) == 1; } break; }
							case Mapping_dsID: { for (int i = 0; i < 5; i++) { btn.dsID[i] = max(0, min((btn.Target[i]) ? vJoyButtonID::button_Count : dsButtonID::button_Count, dsIDString(key, i))); } break; }
							case Mapping_OrXorNot: { for (int i = 0; i < 4; i++) { btn.OrXorNot[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_dsDisable: { for (int i = 0; i < 5; i++) { btn.dsDisable[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_ActionType:
							{
								for (int i = 0; i < 8; i++)
								{
									if (VersionDateCheck >= 202203131)
										btn.ActionType[i] = max(0, min(4, CheckboxString(key, i, true)));
									else if (VersionDateCheck >= 202112201)
										btn.ActionType[i] = max(0, min(3, CheckboxString(key, i)));
									else
										btn.ActionType[i] = (CheckboxString(key, i) == 2) ? 3 : max(0, min(1, CheckboxString(key, i)));
								}
								break;
							}
							case Mapping_vjID:
							{
								for (int i = 0; i < 8; i++)
								{
									if (VersionDateCheck < 202112201 && btn.ActionType[i] == 1 && vjIDString(key, i) > Mapping::SCROLL_DOWN_VARIABLE)
									{
										btn.ActionType[i] = 2;
										btn.vjID[i] = max(0, min(Mapping::special_Count, (vjIDString(key, i) - 34)));
									}
									else
									{
										btn.vjID[i] = max(0, min((btn.ActionType[i]) ? ((btn.ActionType[i] == 1) ? Mapping::mouse_Count : ((btn.ActionType[i] == 2) ? Mapping::special_Count : ((btn.ActionType[i] == 3) ? vJoyAxisMoveID::axismove_Count : Mapping::modules_Count))) : vJoyButtonID::button_Count, vjIDString(key, i)));
										if (VersionDateCheck < 202203131 && btn.ActionType[i] == 2 && vjIDString(key, i) > Mapping::ADDSTAT8)
											btn.vjID[i] += 5;
									}
								}
								break;
							}
							case Mapping_Overcontrol: { for (int i = 0; i < 8; i++) { btn.Overcontrol[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_Switch: { for (int i = 0; i < 8; i++) { btn.Switch[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_OnRelease: { for (int i = 0; i < 8; i++) { btn.OnRelease[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_NoRelease: { for (int i = 0; i < 8; i++) { btn.NoRelease[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_NlRelease: { for (int i = 0; i < 8; i++) { btn.NlRelease[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_vjDisable: { for (int i = 0; i < 8; i++) { btn.vjDisable[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_Mouse:
							{
								btn.Mouse[0] = max(0, min(5, MouseString(key, 0)));
								btn.Mouse[1] = max(0, min(5, MouseString(key, 1)));
								btn.Mouse[2] = max(0, min(5, MouseString(key, 2)));
								btn.Mouse[3] = max(0, min(1, MouseString(key, 3)));
								btn.Mouse[4] = max(0, min(1, MouseString(key, 4)));
								btn.Mouse[5] = max(0, min(1, MouseString(key, 5)));
								btn.Mouse[6] = max(0, min(2, MouseString(key, 6)));
								break;
							}
							case Mapping_Grid:
							{
								btn.Grid[0] = max(-32768, min(32767, GridString(key, 0)));
								btn.Grid[1] = max(-32768, min(32767, GridString(key, 1)));
								btn.Grid[2] = max(-32768, min(32767, GridString(key, 2)));
								btn.Grid[3] = max(-32768, min(32767, GridString(key, 3)));
								btn.Grid[4] = max(-32768, min(32767, GridString(key, 4)));
								btn.Grid[5] = max(-32768, min(32767, GridString(key, 5)));
								break;
							}
							case Mapping_Start1: { btn.Start[0] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Start2: { btn.Start[1] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Start3: { btn.Start[2] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Start4: { btn.Start[3] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Start5: { btn.Start[4] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Start6: { btn.Start[5] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Start7: { btn.Start[6] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Start8: { btn.Start[7] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Stop1: { btn.Stop[0] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Stop2: { btn.Stop[1] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Stop3: { btn.Stop[2] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Stop4: { btn.Stop[3] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Stop5: { btn.Stop[4] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Stop6: { btn.Stop[5] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Stop7: { btn.Stop[6] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Stop8: { btn.Stop[7] = max(0, min(99999999, _wtoi(key))); break; }
							case Mapping_Notice: { wcscpy_s(btn.Notice, wcslen(key) + 1, key); break; }
							}
							if (value == 0)
								break;
						}
						Mappingdata.push_back(std::move(btn));
						key = head;
					}
				}
			}
			delete[] buf;
		}
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_RapidFire:
	{
		if (!Create)
		{
			const int n = 128 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0)
			{
				MessageBoxPos(Ds2hWnd, L"Not enough memory\nto load rapidfires,\nany modification\nwill be lost on exit.", L"Careful", MB_OK, 0, 0, 180);
				cansaverapidfires = false;
			}
			else
			{
				WCHAR* head = buf;
				int ret = GetPrivateProfileSectionW(RapidFiretxt, buf, n, m_file);
				if (ret > 0 && ret - 2 != n)
				{
					WCHAR* key = head, * value;
					while (*key != 0)
					{
						head += wcslen(key) + 1;
						value = wcschr(key, L'=');
						if (value == 0)
							break;
						*value++ = 0;
						int j = _wtoi(key);
						if (j < 1 || j > 128)
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
						rf.Enable = mapdata[RapidFireName::RapidFire_Enable];
						rf.ButtonID = mapdata[RapidFireName::RapidFire_Button];
						rf.ButtonID2 = mapdata[RapidFireName::RapidFire_Button2];
						rf.Firsttime = mapdata[RapidFireName::RapidFire_FirstTime];
						rf.Releasetime = mapdata[RapidFireName::RapidFire_Release];
						rf.Presstime = mapdata[RapidFireName::RapidFire_PressTime];
						RapidFiredata.push_back(std::move(rf));

						key = head;
					}
				}
			}
			delete[] buf;
		}
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_Keymap:
	{
		if (!Create)
		{
			const int n = 128 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0)
			{
				MessageBoxPos(Ds2hWnd, L"Not enough memory\nto load keymaps,\nany modification\nwill be lost on exit.", L"Careful", MB_OK, 0, 0, 180);
				cansavekeymaps = false;
			}
			else
			{
				WCHAR* head = buf;
				int ret = GetPrivateProfileSectionW(Keymaptxt, buf, n, m_file);
				if (ret > 0 && ret - 2 != n)
				{
					WCHAR* key = head, * value;
					while (*key != 0)
					{
						head += wcslen(key) + 1;
						value = wcschr(key, L'=');
						if (value == 0)
							break;
						*value++ = 0;
						Keymap keymap;
						int btnid = _wtoi(key);
						if (btnid < vJoyButtonID::none || btnid >= vJoyButtonID::button_Count)
						{
							key = head;
							continue;
						}
						keymap.ButtonID = btnid;

						key = value;
						value = wcschr(key, L',');
						if (value == 0)
							break;
						*value++ = 0;
						keymap.Enable = _wtoi(key);

						key = value;
						value = wcschr(key, L',');
						if (value != 0)
							*value++ = 0;
						keymap.WndRestore = _wtoi(key);

						key = value;
						value = wcschr(key, L',');
						if (value != 0)
							*value++ = 0;
						keymap.WndMaximize = _wtoi(key);

						key = value;
						value = wcschr(key, L',');
						if (value != 0)
							*value++ = 0;
						keymap.WndShow = _wtoi(key);

						key = value;
						value = wcschr(key, L',');
						if (value != 0)
							*value++ = 0;
						if (_wtoi(key) != 0)
							keymap.NaturalTyping = true;

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

						key = value;
						value = wcschr(key, L',');
						if (value != 0)
							*value++ = 0;
						if (_wtoi(key) != 0)
							keymap.ExtendedKey = true;

						key = value;
						value = wcschr(key, L',');
						if (value != 0)
							*value++ = 0;
						if (_wtoi(key) != 0)
							keymap.Scancode = true;

						key = value;
						value = wcschr(key, L',');
						if (value != 0)
							*value++ = 0;
						keymap.vk = KeymapString(key);
						keymap.findWindow.Val(value);

						Keymapdata.push_back(std::move(keymap));
						key = head;
					}
				}
			}
			delete[] buf;
		}
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_ViGEm:
	{
		ViGEmActive = (GetPrivateProfileInt(ViGEmtxt, TEXT("ViGEmActive"), 0, m_file) == 1) ? true : false;
		setDesiredVirtualPad(GetPrivateProfileInt(ViGEmtxt, TEXT("DesiredVirtualPad"), 1, m_file));

		{
			const int n = 128 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0)
			{
				MessageBoxPos(Ds2hWnd, L"Not enough memory\nto load vigem,\nany modification\nwill be lost on exit.", L"Careful", MB_OK, 0, 0, 180);
				cansavevigem = false;
			}
			else
			{
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
						head += wcslen(key) + 1;
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
							case 1: { totalvalues_X360++; target_X360[i] = (bool)k; break; }
							case 2: { dstotalvalues_X360++; dstarget_X360[i] = (byte)k; break; }
							case 3: { vjtotalvalues_X360++; vjtarget_X360[i] = (byte)k; break; }
							case 4: { totalvalues_DS4++; target_DS4[i] = (bool)k; break; }
							case 5: { dstotalvalues_DS4++; dstarget_DS4[i] = (byte)k; break; }
							case 6: { vjtotalvalues_DS4++; vjtarget_DS4[i] = (byte)k; break; }
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
			delete[] buf;
		}
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_Guardian:
	{
		GetPrivateProfileString(L"Guardian", L"dsHID1", LR"(HID\VID_054C&PID_0BA0&MI_03)", dsHID1, sizeof(dsHID1) / sizeof(dsHID1[0]), m_file);
		GetPrivateProfileString(L"Guardian", L"dsHID2", LR"(HID\VID_054C&PID_0CE6&MI_03)", dsHID2, sizeof(dsHID2) / sizeof(dsHID2[0]), m_file);
		GetPrivateProfileString(L"Guardian", L"dsHID3", L"", dsHID3, sizeof(dsHID3) / sizeof(dsHID3[0]), m_file);
		GetPrivateProfileString(L"Guardian", L"Exe1Name", L"RemotePlay.exe", Exe1Name, sizeof(Exe1Name) / sizeof(Exe1Name[0]), m_file);
		GetPrivateProfileString(L"Guardian", L"Exe2Name", L"", Exe2Name, sizeof(Exe2Name) / sizeof(Exe2Name[0]), m_file);
		GetPrivateProfileString(L"Guardian", L"Exe3Name", L"", Exe3Name, sizeof(Exe3Name) / sizeof(Exe3Name[0]), m_file);
		GetPrivateProfileString(L"Guardian", L"Exe4Name", L"", Exe4Name, sizeof(Exe4Name) / sizeof(Exe4Name[0]), m_file);
		GetPrivateProfileString(L"Guardian", L"Exe5Name", L"", Exe5Name, sizeof(Exe5Name) / sizeof(Exe5Name[0]), m_file);

		GuardianActive = (GetPrivateProfileInt(Guardiantxt, TEXT("GuardianActive"), 0, m_file) == 1) ? true : false;
		RemoveBlacklist = (GetPrivateProfileInt(Guardiantxt, TEXT("RemoveBlacklist"), 1, m_file) == 1) ? true : false;
		PurgeWhitelist = (GetPrivateProfileInt(Guardiantxt, TEXT("PurgeWhitelist"), 1, m_file) == 1) ? true : false;
		dsHID1Enable = (GetPrivateProfileInt(Guardiantxt, TEXT("dsHID1Enable"), 0, m_file) == 1) ? true : false;
		dsHID2Enable = (GetPrivateProfileInt(Guardiantxt, TEXT("dsHID2Enable"), 0, m_file) == 1) ? true : false;
		dsHID3Enable = (GetPrivateProfileInt(Guardiantxt, TEXT("dsHID3Enable"), 0, m_file) == 1) ? true : false;
		Exe1NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe1NameEnable"), 0, m_file) == 1) ? true : false;
		Exe2NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe2NameEnable"), 0, m_file) == 1) ? true : false;
		Exe3NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe3NameEnable"), 0, m_file) == 1) ? true : false;
		Exe4NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe4NameEnable"), 0, m_file) == 1) ? true : false;
		Exe5NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe5NameEnable"), 0, m_file) == 1) ? true : false;
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_Web:
	{
		setWebRefreshTime(GetPrivateProfileInt(L"Web", TEXT("WebRefreshTime"), 20, m_file));
		setDefaultZoomValue(GetPrivateProfileInt(L"Web", TEXT("DefaultZoomValue"), 47, m_file));
		RawBounds = (GetPrivateProfileInt(L"Web", TEXT("RawBounds"), 0, m_file) == 1) ? true : false;
		setDarkMode(GetPrivateProfileInt(L"Web", TEXT("DarkMode"), 1, m_file));
		{
			WCHAR buf[MAX_PATH] = { 0 };
			GetPrivateProfileString(L"Web", L"WebLanguage", L"", buf, sizeof(buf) / sizeof(buf[0]), m_file);
			WebLanguage = buf;
		}
		{
			WCHAR buf[1024] = { 0 };
			GetPrivateProfileString(L"Web", L"UserAgent", L"", buf, sizeof(buf) / sizeof(buf[0]), m_file);
			UserAgent = buf;
		}
		{
			const int n = 128 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0)
			{
				MessageBoxPos(Ds2hWnd, L"Not enough memory\nto load blocked sites,\nany modification\nwill be lost on exit.", L"Careful", MB_OK, 0, 0, 180);
				cansaveblockedsites = false;
			}
			else
			{
				GetPrivateProfileString(L"Web", L"BlockedSites", L"", buf, n, m_file);
				BlockedSites = buf;
			}
			delete[] buf;
		}
		GetPrivateProfileString(L"Web", L"WebURL1", LR"(https://www.google.com)", WebURL[0], sizeof(WebURL[0]) / sizeof(WebURL[0][0]), m_file);
		GetPrivateProfileString(L"Web", L"WebURL2", L"", WebURL[1], sizeof(WebURL[1]) / sizeof(WebURL[1][0]), m_file);
		GetPrivateProfileString(L"Web", L"WebURL3", L"", WebURL[2], sizeof(WebURL[2]) / sizeof(WebURL[2][0]), m_file);
		GetPrivateProfileString(L"Web", L"WebURL4", L"", WebURL[3], sizeof(WebURL[3]) / sizeof(WebURL[3][0]), m_file);
		GetPrivateProfileString(L"Web", L"WebURL5", L"", WebURL[4], sizeof(WebURL[4]) / sizeof(WebURL[4][0]), m_file);
		GetPrivateProfileString(L"Web", L"WebURL6", LR"(file:///C:/Windows/Web/Wallpaper/Windows/img0.jpg)", WebURL[5], sizeof(WebURL[5]) / sizeof(WebURL[5][0]), m_file);
		GetPrivateProfileString(L"Web", L"WebURL7", L"", WebURL[6], sizeof(WebURL[6]) / sizeof(WebURL[6][0]), m_file);
		GetPrivateProfileString(L"Web", L"WebURL8", L"", WebURL[7], sizeof(WebURL[7]) / sizeof(WebURL[7][0]), m_file);
		GetPrivateProfileString(L"Web", L"WebURL9", L"", WebURL[8], sizeof(WebURL[8]) / sizeof(WebURL[8][0]), m_file);
		GetPrivateProfileString(L"Web", L"WebURL10", L"", WebURL[9], sizeof(WebURL[9]) / sizeof(WebURL[9][0]), m_file);
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_WebScript:
	{
		if (!Create)
		{
			const int n = 512 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0)
			{
				MessageBoxPos(Ds2hWnd, L"Not enough memory\nto load web script,\nany modification\nwill be lost on exit.", L"Careful", MB_OK, 0, 0, 180);
				cansavewebscript = false;
			}
			else
			{
				WCHAR* head = buf;
				int ret = GetPrivateProfileSectionW(L"WebScript", buf, n, m_file);
				if (ret > 0 && ret - 2 != n)
				{
					WCHAR* key = head, * value;
					while (*key != 0)
					{
						head += wcslen(key) + 1;
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

						if (j > 1)
							WebScript += L"\r\n";
						WebScript += value;

						key = head;
					}
				}
			}
			delete[] buf;
		}
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_Links:
	{
		GetPrivateProfileString(L"Links", L"App1Name", L"Avoid", App1Name, sizeof(App1Name) / sizeof(App1Name[0]), m_file);
		GetPrivateProfileString(L"Links", L"App2Name", L"Prefer", App2Name, sizeof(App2Name) / sizeof(App2Name[0]), m_file);
		GetPrivateProfileString(L"Links", L"App1Location", LR"(C:\Windows\System32\cmd.exe /C "joy.cpl")", App1Location, sizeof(App1Location) / sizeof(App1Location[0]), m_file);
		GetPrivateProfileString(L"Links", L"App2Location", LR"(rundll32.exe shell32.dll,Control_RunDLL joy.cpl)", App2Location, sizeof(App2Location) / sizeof(App2Location[0]), m_file);
		GetPrivateProfileString(L"Links", L"App3Name", L"", App3Name, sizeof(App3Name) / sizeof(App3Name[0]), m_file);
		GetPrivateProfileString(L"Links", L"App4Name", L"", App4Name, sizeof(App4Name) / sizeof(App4Name[0]), m_file);
		GetPrivateProfileString(L"Links", L"App5Name", L"", App5Name, sizeof(App5Name) / sizeof(App5Name[0]), m_file);
		GetPrivateProfileString(L"Links", L"App3Location", L"", App3Location, sizeof(App3Location) / sizeof(App3Location[0]), m_file);
		GetPrivateProfileString(L"Links", L"App4Location", L"", App4Location, sizeof(App4Location) / sizeof(App4Location[0]), m_file);
		GetPrivateProfileString(L"Links", L"App5Location", L"", App5Location, sizeof(App5Location) / sizeof(App5Location[0]), m_file);
		if (category != Setting_Category_All)
			break;
		[[fallthrough]];
	}
	case Setting_Category_Notepad:
	{
		if (!Create)
		{
			Notepad = L"";
			const int n = 512 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0)
			{
				MessageBoxPos(Ds2hWnd, L"Not enough memory\nto load notepad,\nany modification\nwill be lost on exit.", L"Careful", MB_OK, 0, 0, 180);
				cansavenotepad = false;
			}
			else
			{
				WCHAR* head = buf;
				int ret = GetPrivateProfileSectionW(L"Notepad", buf, n, m_file);
				if (ret > 0 && ret - 2 != n)
				{
					WCHAR* key = head, * value;
					while (*key != 0)
					{
						head += wcslen(key) + 1;
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

						if (j > 1)
							Notepad += L"\r\n";

						Notepad += value;

						key = head;
					}
				}
			}
			delete[] buf;
		}
		if (category != Setting_Category_All)
			break;
	}
	}
}

void Settings::Save(int item)
{
	swprintf_s(Settingstxt, 20, L"%dSettings", Profile);
	swprintf_s(Mappingtxt, 20, L"%dMapping", Profile);
	swprintf_s(ViGEmtxt, 20, L"%dViGEm", Profile);
	swprintf_s(Keymaptxt, 20, L"%dKeymap", Profile);
	swprintf_s(RapidFiretxt, 20, L"%dRapidFire", Profile);
	swprintf_s(Guardiantxt, 20, L"%dGuardian", Profile);
	swprintf_s(Webtxt, 20, L"%dWeb", Profile);

	WCHAR buffer[MAX_PATH * 2];
	bool Update = false;
	switch (item)
	{
	case Setting_Update:
	{
		Update = true;
		item = Setting_All;
		[[fallthrough]];
	}
	case Setting_All:
		[[fallthrough]];
	case Setting_Version:
	{
		if (!Update)
		{
			swprintf_s(buffer, MAX_PATH, L"%d", VersionDate);
			WritePrivateProfileString(TEXT("Profile"), TEXT("VersionDate"), buffer, m_file);
		}
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Profile:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", Profile);
		WritePrivateProfileString(TEXT("Profile"), TEXT("Profile"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TopMost:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("TopMost"), (TopMost) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Transparency:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("Transparency"), (Transparency) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Tasktray:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("Tasktray"), (Tasktray) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_CloseMinimize:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("CloseMinimize"), (CloseMinimize) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DisconnectBT:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("DisconnectBT"), (DisconnectBT) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_LowBattAlert:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("LowBattAlert"), (LowBattAlert) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsSerial:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("dsSerial"), dsSerial, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_BlackLedOnExit:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("BlackLedOnExit"), (BlackLedOnExit) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MappingViewMode:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("MappingViewMode"), (MappingViewMode) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_CloneViewMode:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("CloneViewMode"), (CloneViewMode) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_NotepadFont:
	{
		swprintf_s(buffer, MAX_PATH, L"%s,%d,%d", NotepadFont.c_str(), NotepadFontH, NotepadFontW);
		WritePrivateProfileString(TEXT("Profile"), TEXT("NotepadFont"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyPaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("vJoyPaused"), (vJoyPaused) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RapidFirePaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("RapidFirePaused"), (RapidFirePaused) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_KeymapPaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("KeymapPaused"), (KeymapPaused) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_ViGEmPaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("ViGEmPaused"), (ViGEmPaused) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_GuardianPaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("GuardianPaused"), (GuardianPaused) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID1:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("dsHID1"), dsHID1, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID2:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("dsHID2"), dsHID2, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID3:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("dsHID3"), dsHID3, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe1Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe1Name"), Exe1Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe2Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe2Name"), Exe2Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe3Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe3Name"), Exe3Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe4Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe4Name"), Exe4Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe5Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe5Name"), Exe5Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebRefreshTime:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", WebRefreshTime);
		WritePrivateProfileString(TEXT("Web"), TEXT("WebRefreshTime"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DefaultZoomValue:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", int(DefaultZoomValue * 100));
		WritePrivateProfileString(TEXT("Web"), TEXT("DefaultZoomValue"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DarkMode:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", DarkMode);
		WritePrivateProfileString(TEXT("Web"), TEXT("DarkMode "), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RawBounds:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", RawBounds);
		WritePrivateProfileString(TEXT("Web"), TEXT("RawBounds "), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebLanguage:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebLanguage"), WebLanguage.c_str(), m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_UserAgent:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("UserAgent"), UserAgent.c_str(), m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_BlockedSites:
	{
		if (!cansaveblockedsites)
			MessageBoxPos(Ds2hWnd, L"Blocked sites\nwere not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
			WritePrivateProfileString(TEXT("Web"), TEXT("BlockedSites"), BlockedSites.c_str(), m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL0:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL1"), WebURL[0], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL1:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL2"), WebURL[1], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL2:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL3"), WebURL[2], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL3:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL4"), WebURL[3], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL4:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL5"), WebURL[4], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL5:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL6"), WebURL[5], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL6:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL7"), WebURL[6], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL7:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL8"), WebURL[7], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL8:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL9"), WebURL[8], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL9:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL10"), WebURL[9], m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_InitialScript:
	{
		const int n = 512 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavewebscript)
			MessageBoxPos(Ds2hWnd, L"Web script\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;

			if (WebScript.size())
			{
				WebScript.erase(std::remove_if(WebScript.begin(), WebScript.end(),
					[](WCHAR wc) { return iswcntrl(wc) && !iswspace(wc); }), WebScript.end());

				std::vector<std::wstring> toswap = { L"\r\n", L"\r", L"\f", L"\v" };
				for (int i = 0; i < toswap.size(); i++)
				{
					std::wstring::size_type pos = 0;
					while ((pos = WebScript.find(toswap[i])) != std::wstring::npos)
					{
						WebScript.replace(pos, toswap[i].length(), L"\n");
						pos += 1;
					}
				}
			}

			std::wstringstream ss(WebScript);
			std::wstring to;
			int i = 0;
			if (WebScript.size())
			{
				while (std::getline(ss, to, L'\n'))
				{
					head += swprintf_s(head, 2048, L"%d=", ++i);
					head += swprintf_s(head, 2048, L"%s", to.c_str());
					head++;
				}
			}
			WritePrivateProfileSection(TEXT("WebScript"), buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App1Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App1Name"), App1Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App2Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App2Name"), App2Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App3Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App3Name"), App3Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App4Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App4Name"), App4Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App5Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App5Name"), App5Name, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App1Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App1Location"), App1Location, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App2Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App2Location"), App2Location, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App3Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App3Location"), App3Location, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App4Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App4Location"), App4Location, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App5Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App5Location"), App5Location, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Notepad:
	{
		if (item != Setting_All)
		{
			const int n = 512 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0 || !cansavenotepad)
				MessageBoxPos(Ds2hWnd, L"Notepad\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
			else
			{
				memset(buf, 0, n * sizeof(WCHAR));
				WCHAR* head = buf;

				if (Notepad.size())
				{
					Notepad.erase(std::remove_if(Notepad.begin(), Notepad.end(),
						[](WCHAR wc) { return iswcntrl(wc) && !iswspace(wc); }), Notepad.end());

					std::vector<std::wstring> toswap = { L"\r\n", L"\r", L"\f", L"\v" };
					for (int i = 0; i < toswap.size(); i++)
					{
						std::wstring::size_type pos = 0;
						while ((pos = Notepad.find(toswap[i])) != std::wstring::npos)
						{
							Notepad.replace(pos, toswap[i].length(), L"\n");
							pos += 1;
						}
					}
				}

				std::wstringstream ss(Notepad);
				std::wstring to;
				int i = 0;
				if (Notepad.size())
				{
					while (std::getline(ss, to, L'\n'))
					{
						head += swprintf_s(head, 2048, L"%d=", ++i);
						head += swprintf_s(head, 2048, L"%s", to.c_str());
						head++;
					}
				}
				WritePrivateProfileSection(TEXT("Notepad"), buf, m_file);
			}
			delete[] buf;
			NotepadUnsaved = false;
			break;
		}
		[[fallthrough]];
	}
	case Setting_Opacity:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", Opacity);
		WritePrivateProfileString(Settingstxt, TEXT("Opacity"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_PreferredDS:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", PreferredDS);
		WritePrivateProfileString(Settingstxt, TEXT("PreferredDS"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MouseActive:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", MouseActive);
		WritePrivateProfileString(Settingstxt, TEXT("MouseActive"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_KeyboardActive:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", KeyboardActive);
		WritePrivateProfileString(Settingstxt, TEXT("KeyboardActive"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyDeviceID:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", vJoyDeviceID);
		WritePrivateProfileString(Settingstxt, TEXT("vJoyDeviceID"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Threshold:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", Threshold);
		WritePrivateProfileString(Settingstxt, TEXT("Threshold"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Simultaneous:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", Simultaneous);
		WritePrivateProfileString(Settingstxt, TEXT("Simultaneous"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_LongPress:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", LongPress);
		WritePrivateProfileString(Settingstxt, TEXT("LongPress"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_VeryLongPress:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", VeryLongPress);
		WritePrivateProfileString(Settingstxt, TEXT("VeryLongPress"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MouseCanBypass:
	{
		WritePrivateProfileString(Settingstxt, TEXT("MouseCanBypass"), (MouseCanBypass) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TriggersMode:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TriggersMode);
		WritePrivateProfileString(Settingstxt, TEXT("TriggersMode"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DarkTheme:
	{
		WritePrivateProfileString(Settingstxt, TEXT("DarkTheme"), (DarkTheme) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TouchPadButton:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TouchPadButton);
		WritePrivateProfileString(Settingstxt, TEXT("TouchPadButton"), buffer, m_file);
		setSplitTouch();
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TouchCol:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TouchCol);
		WritePrivateProfileString(Settingstxt, TEXT("TouchCol"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TouchRow:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TouchRow);
		WritePrivateProfileString(Settingstxt, TEXT("TouchRow"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_LED_Color:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", LED_Color);
		WritePrivateProfileString(Settingstxt, TEXT("LED_Color"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Wave_Speed:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", WaveSpeed);
		WritePrivateProfileString(Settingstxt, TEXT("WaveSpeed"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TabMapping:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TabMapping);
		WritePrivateProfileString(Settingstxt, TEXT("TabMapping"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TabToMode:
	{
		swprintf_s(buffer, MAX_PATH, L"%d,%d,%d,%d,%d,%d,%d,%d,%d", Mode[0], Mode[1], Mode[2], Mode[3], Mode[4], Mode[5], Mode[6], Mode[7], Mode[8]);
		WritePrivateProfileString(Settingstxt, TEXT("TabToMode"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Reminder:
	{
		swprintf_s(buffer, MAX_PATH, L"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			Reminder[0], Reminder[1], Reminder[2], Reminder[3], Reminder[4], Reminder[5], Reminder[6], Reminder[7], Reminder[8], Reminder[9],
			Reminder[10], Reminder[11], Reminder[12], Reminder[13], Reminder[14], Reminder[15], Reminder[16], Reminder[17], Reminder[18], Reminder[19],
			Reminder[20], Reminder[21], Reminder[22], Reminder[23], Reminder[24], Reminder[25], Reminder[26], Reminder[7], Reminder[28], Reminder[29],
			Reminder[30], Reminder[31]);
		WritePrivateProfileString(Settingstxt, TEXT("Reminder"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Stats:
	{
		swprintf_s(buffer, MAX_PATH, L"%d,%d,%d,%d,%d,%d,%d,%d", Stat[0], Stat[1], Stat[2], Stat[3], Stat[4], Stat[5], Stat[6], Stat[7]);
		WritePrivateProfileString(Settingstxt, TEXT("Stats"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Mappingdata:
	{
		const int n = 512 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavemappings)
			MessageBoxPos(Ds2hWnd, L"Mapping data\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			size_t length = Mappingdata.size();
			for (int i = 0; i < length; i++)
			{
				head += swprintf_s(head, 1024, L"%d=", i + 1);
				Mapping* btn = &Mappingdata[i];
				for (int j = 0; j < MappingName::Mapping_Count; j++)
					switch (j)
					{
					case Mapping_Enable:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Enable); break;
					case Mapping_Tab:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Tab); break;
					case Mapping_Ifmouse:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Ifmouse); break;
					case Mapping_Force:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Force); break;
					case Mapping_Short:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Short); break;
					case Mapping_Double:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Double); break;
					case Mapping_Long:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Long); break;
					case Mapping_Led:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Led); break;
					case Mapping_Macro:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Macro); break;
					case Mapping_Pause:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Pause); break;
					case Mapping_Transitivity:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Transitivity); break;
					case Mapping_Toggle:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Toggle); break;
					case Mapping_Target:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->Target[0], btn->Target[1], btn->Target[2], btn->Target[3], btn->Target[4], 0, 0, 0)); break;
					case Mapping_dsID:head += swprintf_s(head, MAX_PATH, L"%s,", dsIDToString(btn->dsID[0], btn->dsID[1], btn->dsID[2], btn->dsID[3], btn->dsID[4])); break;
					case Mapping_OrXorNot:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->OrXorNot[0], btn->OrXorNot[1], btn->OrXorNot[2], btn->OrXorNot[3], 0, 0, 0, 0)); break;
					case Mapping_dsDisable:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->dsDisable[0], btn->dsDisable[1], btn->dsDisable[2], btn->dsDisable[3], btn->dsDisable[4], 0, 0, 0)); break;
					case Mapping_ActionType:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->ActionType[0], btn->ActionType[1], btn->ActionType[2], btn->ActionType[3], btn->ActionType[4], btn->ActionType[5], btn->ActionType[6], btn->ActionType[7], true)); break;
					case Mapping_Overcontrol:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->Overcontrol[0], btn->Overcontrol[1], btn->Overcontrol[2], btn->Overcontrol[3], btn->Overcontrol[4], btn->Overcontrol[5], btn->Overcontrol[6], btn->Overcontrol[7])); break;
					case Mapping_Switch:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->Switch[0], btn->Switch[1], btn->Switch[2], btn->Switch[3], btn->Switch[4], btn->Switch[5], btn->Switch[6], btn->Switch[7])); break;
					case Mapping_vjID:head += swprintf_s(head, MAX_PATH, L"%s,", vjIDToString(btn->vjID[0], btn->vjID[1], btn->vjID[2], btn->vjID[3], btn->vjID[4], btn->vjID[5], btn->vjID[6], btn->vjID[7])); break;
					case Mapping_OnRelease:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->OnRelease[0], btn->OnRelease[1], btn->OnRelease[2], btn->OnRelease[3], btn->OnRelease[4], btn->OnRelease[5], btn->OnRelease[6], btn->OnRelease[7])); break;
					case Mapping_NoRelease:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->NoRelease[0], btn->NoRelease[1], btn->NoRelease[2], btn->NoRelease[3], btn->NoRelease[4], btn->NoRelease[5], btn->NoRelease[6], btn->NoRelease[7])); break;
					case Mapping_NlRelease:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->NlRelease[0], btn->NlRelease[1], btn->NlRelease[2], btn->NlRelease[3], btn->NlRelease[4], btn->NlRelease[5], btn->NlRelease[6], btn->NlRelease[7])); break;
					case Mapping_vjDisable:head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->vjDisable[0], btn->vjDisable[1], btn->vjDisable[2], btn->vjDisable[3], btn->vjDisable[4], btn->vjDisable[5], btn->vjDisable[6], btn->vjDisable[7])); break;
					case Mapping_Mouse:head += swprintf_s(head, MAX_PATH, L"%s,", MouseToString(btn->Mouse[0], btn->Mouse[1], btn->Mouse[2], btn->Mouse[3], btn->Mouse[4], btn->Mouse[5], btn->Mouse[6])); break;
					case Mapping_Grid:head += swprintf_s(head, MAX_PATH, L"%s,", GridToString(btn->Grid[0], btn->Grid[1], btn->Grid[2], btn->Grid[3], btn->Grid[4], btn->Grid[5])); break;
					case Mapping_Start1:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Start[0]); break;
					case Mapping_Start2:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Start[1]); break;
					case Mapping_Start3:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Start[2]); break;
					case Mapping_Start4:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Start[3]); break;
					case Mapping_Start5:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Start[4]); break;
					case Mapping_Start6:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Start[5]); break;
					case Mapping_Start7:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Start[6]); break;
					case Mapping_Start8:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Start[7]); break;
					case Mapping_Stop1:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Stop[0]); break;
					case Mapping_Stop2:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Stop[1]); break;
					case Mapping_Stop3:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Stop[2]); break;
					case Mapping_Stop4:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Stop[3]); break;
					case Mapping_Stop5:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Stop[4]); break;
					case Mapping_Stop6:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Stop[5]); break;
					case Mapping_Stop7:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Stop[6]); break;
					case Mapping_Stop8:head += swprintf_s(head, MAX_PATH, L"%d,", btn->Stop[7]); break;
					case Mapping_Notice:head += swprintf_s(head, MAX_PATH, L"%s,", btn->Notice); break;
					}
				head++;
			}
			WritePrivateProfileSection(Mappingtxt, buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RapidFiredata:
	{
		const int n = 128 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansaverapidfires)
			MessageBoxPos(Ds2hWnd, L"RapidFire data\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
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

				head += swprintf_s(head, 1024, L"%d=", i + 1);
				for (int j = 0; j < RapidFireName::RapidFire_Count; j++)
					head += swprintf_s(head, 1024, L"%d,", mapdata[j]);
				head++;
			}
			WritePrivateProfileSection(RapidFiretxt, buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Keymapdata:
	{
		const int n = 128 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavekeymaps)
			MessageBoxPos(Ds2hWnd, L"Keymap data\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			size_t length = Keymapdata.size();
			for (int i = 0; i < length; ++i)
			{
				Keymap* keymap = &Keymapdata[i];
				//			if (keymap->vk.empty())
				//				continue;
				head += swprintf_s(head, MAX_PATH, L"%d=%d,", keymap->ButtonID, keymap->Enable);
				head += swprintf_s(head, MAX_PATH, L"%d,", keymap->WndRestore);
				head += swprintf_s(head, MAX_PATH, L"%d,", keymap->WndMaximize);
				head += swprintf_s(head, MAX_PATH, L"%d,", keymap->WndShow);
				head += swprintf_s(head, MAX_PATH, L"%d,", (keymap->NaturalTyping) ? 1 : 0);
				head += swprintf_s(head, MAX_PATH, L"%d,", (keymap->usePostmessage) ? 1 : 0);
				head += swprintf_s(head, MAX_PATH, L"%d,", (keymap->useActivating) ? 1 : 0);
				head += swprintf_s(head, MAX_PATH, L"%d,", (keymap->ExtendedKey) ? 1 : 0);
				head += swprintf_s(head, MAX_PATH, L"%d,", (keymap->Scancode) ? 1 : 0);
				head += swprintf_s(head, MAX_PATH, L"%s,", KeymapToString(keymap->vk));
				head += swprintf_s(head, MAX_PATH, L"%s", keymap->findWindow.Val().c_str());
				head++;
			}
			WritePrivateProfileSection(Keymaptxt, buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_ViGEmActive:
	{
		WritePrivateProfileString(ViGEmtxt, TEXT("ViGEmActive"), (ViGEmActive) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DesiredVirtualPad:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", DesiredVirtualPad);
		WritePrivateProfileString(ViGEmtxt, TEXT("DesiredVirtualPad"), buffer, m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_target_X360:
	{
		const int n = 128 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavevigem)
			MessageBoxPos(Ds2hWnd, L"ViGEm X360\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			for (int i = 0; i < 24; i++)
				head += swprintf_s(head, 1024, L"%d,", target_X360[i]);
			WritePrivateProfileString(ViGEmtxt, TEXT("1"), buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dstarget_X360:
	{
		const int n = 128 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavevigem)
			MessageBoxPos(Ds2hWnd, L"ViGEm X360\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			for (int i = 0; i < 24; i++)
				head += swprintf_s(head, 1024, L"%d,", dstarget_X360[i]);
			WritePrivateProfileString(ViGEmtxt, TEXT("2"), buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vjtarget_X360:
	{
		const int n = 128 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavevigem)
			MessageBoxPos(Ds2hWnd, L"ViGEm X360\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			for (int i = 0; i < 24; i++)
				head += swprintf_s(head, 1024, L"%d,", vjtarget_X360[i]);
			WritePrivateProfileString(ViGEmtxt, TEXT("3"), buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_target_DS4:
	{
		const int n = 128 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavevigem)
			MessageBoxPos(Ds2hWnd, L"ViGEm DS4\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			for (int i = 0; i < 24; i++)
				head += swprintf_s(head, 1024, L"%d,", target_DS4[i]);
			WritePrivateProfileString(ViGEmtxt, TEXT("4"), buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dstarget_DS4:
	{
		const int n = 128 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavevigem)
			MessageBoxPos(Ds2hWnd, L"ViGEm DS4\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			for (int i = 0; i < 24; i++)
				head += swprintf_s(head, 1024, L"%d,", dstarget_DS4[i]);
			WritePrivateProfileString(ViGEmtxt, TEXT("5"), buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vjtarget_DS4:
	{
		const int n = 128* 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavevigem)
			MessageBoxPos(Ds2hWnd, L"ViGEm DS4\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			for (int i = 0; i < 24; i++)
				head += swprintf_s(head, 1024, L"%d,", vjtarget_DS4[i]);
			WritePrivateProfileString(ViGEmtxt, TEXT("6"), buf, m_file);
		}
		delete[] buf;
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_GuardianActive:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("GuardianActive"), (GuardianActive) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RemoveBlacklist:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("RemoveBlacklist"), (RemoveBlacklist) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_PurgeWhitelist:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("PurgeWhitelist"), (PurgeWhitelist) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID1Enable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("dsHID1Enable"), (dsHID1Enable) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID2Enable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("dsHID2Enable"), (dsHID2Enable) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID3Enable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("dsHID3Enable"), (dsHID3Enable) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe1NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe1NameEnable"), (Exe1NameEnable) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe2NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe2NameEnable"), (Exe2NameEnable) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe3NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe3NameEnable"), (Exe3NameEnable) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe4NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe4NameEnable"), (Exe4NameEnable) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe5NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe5NameEnable"), (Exe5NameEnable) ? L"1" : L"0", m_file);
		if (item != Setting_All)
			break;
		break;
	}
	case Setting_GiveMapping:
	{
		const int n = 128 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0)
			break;

		memset(buf, 0, n * sizeof(WCHAR));
		WCHAR* head = buf;
		
		head += swprintf_s(head, MAX_PATH, L"1=1,0,0,0,0,0,0,0,0,0,0,0,0000,0100000000,0000,0000,0000,0100000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"2=1,0,0,0,0,0,0,0,0,0,0,0,0000,0200000000,0000,0000,0000,0200000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"3=0,0,0,0,0,0,0,0,0,0,0,0,0000,1E00000000,0000,0000,0000,0200000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"4=1,0,0,0,0,0,0,0,0,0,0,0,0000,0300000000,0000,0000,0000,0300000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"5=1,0,0,0,0,0,0,0,0,0,0,0,0000,0400000000,0000,0000,0000,0600000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"6=0,0,0,0,0,0,0,0,0,0,0,0,0000,2000000000,0000,0000,0000,0500000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"7=1,1,0,0,0,0,0,0,0,0,0,0,0000,0500000000,0000,0000,0000,3900000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"8=1,1,0,0,0,0,0,0,0,0,0,0,0000,0600000000,0000,0000,0000,3A00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"9=1,1,0,0,0,0,0,0,0,0,0,0,0000,0700000000,0000,0000,0000,3B00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"10=1,1,0,0,0,0,0,0,0,0,0,0,0000,0800000000,0000,0000,0000,3C00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"11=1,1,0,0,0,0,0,0,0,0,0,0,0000,0900000000,0000,0000,0000,3D00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"12=1,1,0,0,0,0,0,0,0,0,0,0,0000,0C00000000,0000,0000,0000,4000000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"13=1,1,0,0,0,0,0,0,0,0,0,0,0000,0D00000000,0000,0000,0000,4100000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"14=1,1,0,0,0,0,0,0,0,0,0,0,0000,0E00000000,0000,0000,0000,4200000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"15=1,1,0,0,0,0,0,0,0,0,0,0,0000,0F00000000,0000,0000,0000,4300000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"16=1,1,0,0,0,0,0,0,0,0,0,0,0000,1000000000,0000,0000,0000,4400000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"17=1,2,0,0,0,0,0,0,0,0,0,0,0000,0A00000000,0000,0000,0000,3E00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"18=1,2,0,0,0,0,0,0,0,0,0,0,0000,0B00000000,0000,0000,0000,3F00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"19=1,2,0,0,0,0,0,0,0,0,0,0,0000,1100000000,0000,0000,0000,4500000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"20=1,2,0,0,0,0,0,0,0,0,0,0,0000,1200000000,0000,0000,0000,4600000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"21=1,2,0,0,0,0,0,0,0,0,0,0,0000,1300000000,0000,0000,0000,4700000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"22=1,3,0,0,0,0,0,0,0,0,0,0,0000,1400000000,0000,0000,0000,4800000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"23=1,3,0,0,0,0,0,0,0,0,0,0,0000,1500000000,0000,0000,0000,4900000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"24=1,3,0,0,0,0,0,0,0,0,0,0,0000,1600000000,0000,0000,0000,4A00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"25=1,3,0,0,0,0,0,0,0,0,0,0,0000,1700000000,0000,0000,0000,4B00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"26=1,3,0,0,0,0,0,0,0,0,0,0,0000,1800000000,0000,0000,0000,0C00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"27=1,3,0,0,0,0,0,0,0,0,0,0,0000,1900000000,0000,0000,0000,0D00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		
		WritePrivateProfileSection(Mappingtxt, buf, m_file);
		delete[] buf;
		break;
	}
	}
}

void Settings::setProfile(int i)
{
	if (i > 0 && i < 4)
		Profile = i;
	else
		Profile = 1;
}

void Settings::setOpacity(int i)
{
	if (i > 19 && i < 101)
		Opacity = i;
	else
		Opacity = 60;
}

void Settings::setTabMapping(int i)
{
	if (i >= 0 && i < 9)
		TabMapping = i;
	else
		TabMapping = 0;
}

void Settings::setPreferredDS(int i)
{
	if (i >= 0 && i < 3)
		PreferredDS = (unsigned char)i;
	else
		PreferredDS = 0;
}

void Settings::setTabMode(int i, int mode)
{
	if (mode >= 0 && mode < 9)
		Mode[i] = (unsigned char)mode;
	else
		Mode[i] = 0;
}

void Settings::setReminder(int i, int reminder)
{
	if (reminder >= 0 && reminder < 2)
		Reminder[i] = reminder;
	else
		Reminder[i] = 0;
}

void Settings::setStats(int i, int stat)
{
	if (stat >= 0 && stat < 65536)
		Stat[i] = stat;
	else
		Stat[i] = 0;
}

void Settings::setThreshold(int i)
{
	if (i >= 0 && i <= 128)
		Threshold = i;
	else
		Threshold = 8;
}

void Settings::setSimultaneous(int i)
{
	if (i > 0 && i < 10000)
		Simultaneous = i;
	else
		Simultaneous = 40;
}

void Settings::setLongPress(int i)
{
	if (i > 0 && i < 10000)
		LongPress = i;
	else
		LongPress = 255;
}

void Settings::setVeryLongPress(int i)
{
	if (i > 0 && i < 10000)
		VeryLongPress = i;
	else
		VeryLongPress = 3287;
}

void Settings::setDefaultZoomValue(int i)
{
	DefaultZoomValue = max(25, min(500, i)) / 100;
}

void Settings::setDarkMode(int i)
{
	DarkMode = max(0, min(3, i)) ;
}

void Settings::setWebRefreshTime(int i)
{
	if (i > 0 && i < 10000)
		WebRefreshTime = i;
	else
		WebRefreshTime = 20;
}

void Settings::setDesiredVirtualPad(int i)
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

void Settings::setSplitTouch()
{
	if (TouchPadButton && TouchPadButton <= 128)
		SplitTouch = true;
	else
		SplitTouch = false;
}

void Settings::setTouchPadButton(byte n)
{
	if (n <= 128)
		TouchPadButton = n;
	else
		TouchPadButton = 0;
}

void Settings::setTouchRow(int i)
{
	if (i > 0 && i < 10)
		TouchRow = i;
	else
		TouchRow = 1;
}

void Settings::setTouchCol(int i)
{
	if (i > 0 && i < 10)
		TouchCol = i;
	else
		TouchCol = 1;
}

void Settings::setLED(unsigned long i)
{
	if (i >= 0 && i <= 0xFFFFFF)
		LED_Color = i;
}

void Settings::setTriggersMode(int i)
{
	if (i >= 0 && i < 4)
		TriggersMode = i;
	else
		TriggersMode = 0;
}

void Settings::setWaveSpeed(int i)
{
	if (i >= 0 && i < 167)
		WaveSpeed = i;
	else
		WaveSpeed = 130;
}

const WCHAR* Settings::getSerial()
{
	return dsSerial;
}

void Settings::setSerial(const WCHAR* buf)
{
	wcscpy_s(dsSerial, wcslen(buf) + 1, buf);
}

const std::wstring Settings::getHID(int ds)
{
	switch (ds)
	{
	case 1: return dsHID1;
	case 2: return dsHID2;
	case 3: return dsHID3;
	default: return L"";
	}
}

void Settings::setPID(const WCHAR* buf, int ds)
{
	switch (ds)
	{
	case 1: { wcscpy_s(dsHID1, wcslen(buf) + 1, buf);break; }
	case 2: { wcscpy_s(dsHID2, wcslen(buf) + 1, buf);break; }
	case 3: { wcscpy_s(dsHID3, wcslen(buf) + 1, buf);break; }
	}
}

void Settings::setExeName(const WCHAR* buf, int exe)
{
	switch (exe)
	{
	case 1: { wcscpy_s(Exe1Name, wcslen(buf) + 1, buf);break; }
	case 2: { wcscpy_s(Exe2Name, wcslen(buf) + 1, buf);break; }
	case 3: { wcscpy_s(Exe3Name, wcslen(buf) + 1, buf);break; }
	case 4: { wcscpy_s(Exe4Name, wcslen(buf) + 1, buf);break; }
	case 5: { wcscpy_s(Exe5Name, wcslen(buf) + 1, buf);break; }
	}
}

void Settings::setWebURL(const WCHAR* url, int lnk)
{
	switch (lnk)
	{
	case 0: { wcscpy_s(WebURL[0], wcslen(url) + 1, url);break; }
	case 1: { wcscpy_s(WebURL[1], wcslen(url) + 1, url);break; }
	case 2: { wcscpy_s(WebURL[2], wcslen(url) + 1, url);break; }
	case 3: { wcscpy_s(WebURL[2], wcslen(url) + 1, url);break; }
	case 4: { wcscpy_s(WebURL[4], wcslen(url) + 1, url);break; }
	case 5: { wcscpy_s(WebURL[5], wcslen(url) + 1, url);break; }
	case 6: { wcscpy_s(WebURL[6], wcslen(url) + 1, url);break; }
	case 7: { wcscpy_s(WebURL[7], wcslen(url) + 1, url);break; }
	case 8: { wcscpy_s(WebURL[8], wcslen(url) + 1, url);break; }
	case 9: { wcscpy_s(WebURL[9], wcslen(url) + 1, url);break; }
	}
}

void Settings::setAppName(const WCHAR* buf, int app)
{
	switch (app)
	{
	case 1: { wcscpy_s(App1Name, wcslen(buf) + 1, buf);break; }
	case 2: { wcscpy_s(App2Name, wcslen(buf) + 1, buf);break; }
	case 3: { wcscpy_s(App3Name, wcslen(buf) + 1, buf);break; }
	case 4: { wcscpy_s(App4Name, wcslen(buf) + 1, buf);break; }
	case 5: { wcscpy_s(App5Name, wcslen(buf) + 1, buf);break; }
	}
}

void Settings::setAppLocation(const WCHAR* buf, int app)
{
	switch (app)
	{
	case 1: { wcscpy_s(App1Location, wcslen(buf) + 1, buf);break; }
	case 2: { wcscpy_s(App2Location, wcslen(buf) + 1, buf);break; }
	case 3: { wcscpy_s(App3Location, wcslen(buf) + 1, buf);break; }
	case 4: { wcscpy_s(App4Location, wcslen(buf) + 1, buf);break; }
	case 5: { wcscpy_s(App5Location, wcslen(buf) + 1, buf);break; }
	}
}

WCHAR* Settings::CheckboxToString(byte v1, byte v2, byte v3, byte v4, byte v5, byte v6, byte v7, byte v8, bool eightCases)
{
	int packit = 0;
	int packit2 = 0;

	if (eightCases)
	{
		packit2 |= v8;
		packit2 |= (v7 << 3);
		packit2 |= (v6 << 6);
		packit2 |= (v5 << 9);
		packit |= v4;
		packit |= (v3 << 3);
		packit |= (v2 << 6);
		packit |= (v1 << 9);
	}
	else
	{
		packit |= v8;
		packit |= (v7 << 2);
		packit |= (v6 << 4);
		packit |= (v5 << 6);
		packit |= (v4 << 8);
		packit |= (v3 << 10);
		packit |= (v2 << 12);
		packit |= (v1 << 14);
	}

//	std::stringstream sstream;
//	sstream << std::hex << packit;
//	echo("%s", sstream.str());

	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	if (eightCases)
		head += swprintf_s(head, MAX_PATH, L"%03hX%03hX", packit, packit2);
	else
		head += swprintf_s(head, MAX_PATH, L"%04hX", packit);

	return buf;
}

WCHAR* Settings::dsIDToString(byte v1, byte v2, byte v3, byte v4, byte v5)
{
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	head += swprintf_s(head, MAX_PATH, L"%02hX%02hX%02hX%02hX%02hX", v1, v2, v3, v4, v5);

	return buf;
}

WCHAR* Settings::vjIDToString(byte v1, byte v2, byte v3, byte v4, byte v5, byte v6, byte v7, byte v8)
{
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	head += swprintf_s(head, MAX_PATH, L"%02hX%02hX%02hX%02hX%02hX%02hX%02hX%02hX", v1, v2, v3, v4, v5, v6, v7, v8);

	return buf;
}

WCHAR* Settings::MouseToString(byte v1, byte v2, byte v3, byte v4, byte v5, byte v6, byte v7)
{
	unsigned short packit = 0;
	packit |= (v7 << 2);
	packit |= (v6 << 4);
	packit |= (v5 << 5);
	packit |= (v4 << 6);
	packit |= (v3 << 7);
	packit |= (v2 << 10);
	packit |= (v1 << 13);

	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	head += swprintf_s(head, MAX_PATH, L"%04hX", packit);

	return buf;
}

WCHAR* Settings::GridToString(unsigned short v1,unsigned short v2, unsigned short v3, unsigned short v4, unsigned short v5, unsigned short v6)
{
	static WCHAR buf[MAX_PATH];
	buf[0] = 0;
	WCHAR* head = buf;

	head += swprintf_s(head, MAX_PATH, L"%04hX%04hX%04hX%04hX%04hX%04hX", v1, v2, v3, v4, v5, v6);

	return buf;
}

WCHAR* Settings::KeymapToString(std::vector<BYTE> vk)
{
	if (!vk.size())
		return WCHARI(L"");

	static WCHAR buf[1024];
	buf[0] = 0;
	WCHAR* head = buf;

	for (auto itr = vk.begin(); itr != vk.end(); ++itr)
	{
		head += swprintf_s(head, 1024, L"%02hX", *itr);
	}

	return buf;
}

unsigned short Settings::CheckboxString(std::wstring checkboxesstring, unsigned char idx, bool eightCases)
{
	if (checkboxesstring == L"")
		return 0;
	if (checkboxesstring.length() < 4 || (eightCases && checkboxesstring.length() < 6))
		return 0;

	int pakitstoi = std::stoi(checkboxesstring, nullptr, 16);

	if (eightCases)
	{
		switch (idx)
		{
		case 7: return (pakitstoi & 0x000007);
		case 6: return (pakitstoi & 0x000038) >> 3;
		case 5: return (pakitstoi & 0x0001C0) >> 6;
		case 4: return (pakitstoi & 0x000E00) >> 9;
		case 3: return (pakitstoi & 0x007000) >> 12;
		case 2: return (pakitstoi & 0x038000) >> 15;
		case 1: return (pakitstoi & 0x1C0000) >> 18;
		case 0: return (pakitstoi & 0xE00000) >> 21;
		default: return 0;
		}
	}
	else
	{
		switch (idx)
		{
		case 7: return (pakitstoi & 0x0003);
		case 6: return (pakitstoi & 0x000C) >> 2;
		case 5: return (pakitstoi & 0x0030) >> 4;
		case 4: return (pakitstoi & 0x00C0) >> 6;
		case 3: return (pakitstoi & 0x0300) >> 8;
		case 2: return (pakitstoi & 0x0C00) >> 10;
		case 1: return (pakitstoi & 0x3000) >> 12;
		case 0: return (pakitstoi & 0xC000) >> 14;
		default: return 0;
		}
	}
}

BYTE Settings::dsIDString(std::wstring dsidstring, unsigned char idx)
{
	if (dsidstring == L"")
		return 0;
	if (dsidstring.length() < 10)
		return 0;

	unsigned long long pakitstoi1 = std::stoll(dsidstring.std::wstring::substr(0, 8), nullptr, 16);
	unsigned long long pakitstoi2 = std::stoll(dsidstring.std::wstring::substr(8, 2), nullptr, 16);

	switch (idx)
	{
	case 4: return (BYTE)pakitstoi2;
	case 3: return (BYTE)(pakitstoi1 & 0x000000FF);
	case 2: return (BYTE)((pakitstoi1 & 0x0000FF00) >> 8);
	case 1: return (BYTE)((pakitstoi1 & 0x00FF0000) >> 16);
	case 0: return (BYTE)((pakitstoi1 & 0xFF000000) >> 24);
	default: return 0;
	}
}

BYTE Settings::vjIDString(std::wstring vjidstring, unsigned char idx)
{
	if (vjidstring == L"")
		return 0;
	if (vjidstring.length() < 16)
		return 0;

	unsigned long long pakitstoi1 = std::stoll(vjidstring.std::wstring::substr(0, 8), nullptr, 16);
	unsigned long long pakitstoi2 = std::stoll(vjidstring.std::wstring::substr(8, 8), nullptr, 16);

	switch (idx)
	{
	case 7: return (BYTE)(pakitstoi2 & 0x000000FF);
	case 6: return (BYTE)((pakitstoi2 & 0x0000FF00) >> 8);
	case 5: return (BYTE)((pakitstoi2 & 0x00FF0000) >> 16);
	case 4: return (BYTE)((pakitstoi2 & 0xFF000000) >> 24);
	case 3: return (BYTE)(pakitstoi1 & 0x000000FF);
	case 2: return (BYTE)((pakitstoi1 & 0x0000FF00) >> 8);
	case 1: return (BYTE)((pakitstoi1 & 0x00FF0000) >> 16);
	case 0: return (BYTE)((pakitstoi1 & 0xFF000000) >> 24);
	default: return 0;
	}
}

unsigned short Settings::MouseString(std::wstring mousestring, unsigned char idx)
{
	if (mousestring == L"")
		return 0;
	if (mousestring.length() < 4)
		return 0;

	unsigned short pakitstoi = std::stoi(mousestring, nullptr, 16);

	switch (idx)
	{
	case 6: return (pakitstoi & 0x000C) >> 2;
	case 5: return (pakitstoi & 0x0010) >> 4;
	case 4: return (pakitstoi & 0x0020) >> 5;
	case 3: return (pakitstoi & 0x0040) >> 6;
	case 2: return (pakitstoi & 0x0380) >> 7;
	case 1: return (pakitstoi & 0x1C00) >> 10;
	case 0: return (pakitstoi & 0xE000) >> 13;
	default: return 0;
	}
}

unsigned short Settings::GridString(std::wstring gridstring, unsigned char idx)
{
	if (gridstring == L"")
		return 0;
	if (gridstring.length() < 24)
		return 0;

	unsigned long long pakitstoi1 = std::stoll(gridstring.std::wstring::substr(0, 8), nullptr, 16);
	unsigned long long pakitstoi2 = std::stoll(gridstring.std::wstring::substr(8, 8), nullptr, 16);
	unsigned long long pakitstoi3 = std::stoll(gridstring.std::wstring::substr(16, 8), nullptr, 16);
	
	switch (idx)
	{
	case 5: return (unsigned short)(pakitstoi3 & 0x0000FFFF);
	case 4: return (unsigned short)((pakitstoi3 & 0xFFFF0000) >> 16);
	case 3: return (unsigned short)(pakitstoi2 & 0x0000FFFF);
	case 2: return (unsigned short)((pakitstoi2 & 0xFFFF0000) >> 16);
	case 1: return (unsigned short)(pakitstoi1 & 0x0000FFFF);
	case 0: return (unsigned short)((pakitstoi1 & 0xFFFF0000) >> 16);
	default: return 0;
	}
}

std::vector<BYTE> Settings::KeymapString(std::wstring keymapstring)
{
	std::vector<BYTE> vk;

	if (keymapstring == L"")
		return vk;
	if (keymapstring.length() %2)
		return vk;

	size_t length = min(KEYMAP_MAX_KEYS, (keymapstring.length() / 2));

	for (size_t i = 0; i < length; i++)
		vk.push_back((BYTE)std::stoll(keymapstring.std::wstring::substr(i * 2, 2), nullptr, 16));

	return vk;
}
