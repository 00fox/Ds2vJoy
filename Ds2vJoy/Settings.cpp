#include "stdafx.h"
#include "Settings.h"

Settings::Settings()
{
	hIconTray[0] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_110));
	hIconTray[1] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_111));
	hIconTray[2] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_112));
	hIconTray[3] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_113));
	hIconTray[4] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_114));
	hIconTray[5] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_120));
	hIconTray[6] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_121));
	hIconTray[7] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_122));
	hIconTray[8] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_123));
	hIconTray[9] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_124));
	hIconTray[10] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_130));
	hIconTray[11] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_131));
	hIconTray[12] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_132));
	hIconTray[13] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_133));
	hIconTray[14] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_134));
	hIconTray[15] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_140));
	hIconTray[16] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_141));
	hIconTray[17] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_142));
	hIconTray[18] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_143));
	hIconTray[19] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_144));
	hIconTray[20] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_150));
	hIconTray[21] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_151));
	hIconTray[22] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_152));
	hIconTray[23] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_153));
	hIconTray[24] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_154));
	hIconTray[25] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_160));
	hIconTray[26] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_161));
	hIconTray[27] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_162));
	hIconTray[28] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_163));
	hIconTray[29] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_164));
	hIconTray[30] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_170));
	hIconTray[31] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_171));
	hIconTray[32] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_172));
	hIconTray[33] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_173));
	hIconTray[34] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_174));
	hIconTray[35] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_180));
	hIconTray[36] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_181));
	hIconTray[37] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_182));
	hIconTray[38] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_183));
	hIconTray[39] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_184));

	hIconTray[40] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_210));
	hIconTray[41] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_211));
	hIconTray[42] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_212));
	hIconTray[43] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_213));
	hIconTray[44] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_214));
	hIconTray[45] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_220));
	hIconTray[46] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_221));
	hIconTray[47] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_222));
	hIconTray[48] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_223));
	hIconTray[49] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_224));
	hIconTray[50] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_230));
	hIconTray[51] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_231));
	hIconTray[52] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_232));
	hIconTray[53] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_233));
	hIconTray[54] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_234));
	hIconTray[55] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_240));
	hIconTray[56] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_241));
	hIconTray[57] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_242));
	hIconTray[58] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_243));
	hIconTray[59] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_244));
	hIconTray[60] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_250));
	hIconTray[61] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_251));
	hIconTray[62] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_252));
	hIconTray[63] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_253));
	hIconTray[64] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_254));
	hIconTray[65] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_260));
	hIconTray[66] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_261));
	hIconTray[67] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_262));
	hIconTray[68] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_263));
	hIconTray[69] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_264));
	hIconTray[70] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_270));
	hIconTray[71] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_271));
	hIconTray[72] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_272));
	hIconTray[73] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_273));
	hIconTray[74] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_274));
	hIconTray[75] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_280));
	hIconTray[76] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_281));
	hIconTray[77] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_282));
	hIconTray[78] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_283));
	hIconTray[79] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_284));

	hIconTray[80] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_310));
	hIconTray[81] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_311));
	hIconTray[82] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_312));
	hIconTray[83] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_313));
	hIconTray[84] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_314));
	hIconTray[85] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_320));
	hIconTray[86] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_321));
	hIconTray[87] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_322));
	hIconTray[88] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_323));
	hIconTray[89] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_324));
	hIconTray[90] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_330));
	hIconTray[91] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_331));
	hIconTray[92] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_332));
	hIconTray[93] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_333));
	hIconTray[94] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_334));
	hIconTray[95] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_340));
	hIconTray[96] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_341));
	hIconTray[97] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_342));
	hIconTray[98] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_343));
	hIconTray[99] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_344));
	hIconTray[100] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_350));
	hIconTray[101] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_351));
	hIconTray[102] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_352));
	hIconTray[103] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_353));
	hIconTray[104] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_354));
	hIconTray[105] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_360));
	hIconTray[106] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_361));
	hIconTray[107] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_362));
	hIconTray[108] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_363));
	hIconTray[109] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_364));
	hIconTray[110] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_370));
	hIconTray[111] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_371));
	hIconTray[112] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_372));
	hIconTray[113] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_373));
	hIconTray[114] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_374));
	hIconTray[115] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_380));
	hIconTray[116] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_381));
	hIconTray[117] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_382));
	hIconTray[118] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_383));
	hIconTray[119] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DS2VJOY_384));

	hMagnification = LoadLibrary(L"Magnification.dll");
	if (hMagnification != nullptr)
		MagnificationSmoothing = (hMagSetSmoothing)GetProcAddress(tape.hMagnification, "MagSetFullscreenUseBitmapSmoothing");
}

Settings::~Settings()
{
	DeleteObject(hB_neutral);
	DeleteObject(hB_deepGrey);
	DeleteObject(hB_black);	
	DeleteObject(hB_blue_black);
	DeleteObject(hB_grey);	
	DeleteObject(hB_red);	
	DeleteObject(hB_orange);	
	DeleteObject(hB_yellow);	
	DeleteObject(hB_emerald);
	DeleteObject(hB_green);	
	DeleteObject(hB_blue);	
	DeleteObject(hB_purple);	
	DeleteObject(hB_white);	
	DeleteObject(hB_blue_white);
	DeleteObject(hB_bright_grey);
	DeleteObject(hB_bright_red);
	DeleteObject(hB_bright_orange);
	DeleteObject(hB_bright_yellow);
	DeleteObject(hB_bright_emerald);
	DeleteObject(hB_bright_green);
	DeleteObject(hB_bright_blue);
	DeleteObject(hB_bright_purple);
	DeleteObject(hB_DLG);	
	DeleteObject(hB_DLG_DARK);
	DeleteObject(hB_BTN_Border);
	DeleteObject(hB_BTN_Border_DARK);
	DeleteObject(hB_Not_Installed);
	DeleteObject(hB_Running);
	DeleteObject(hB_Stopped);
	DeleteObject(hB_Paused);	
	DeleteObject(hB_STATIC_Mouse1);
	DeleteObject(hB_STATIC_Mouse2);
	DeleteObject(hB_POSTIT);	
	DeleteObject(hB_POSTIT_Rand0);
	DeleteObject(hB_POSTIT_Rand1);
	DeleteObject(hB_POSTIT_Rand3);
	DeleteObject(hB_EDIT);
	DeleteObject(hB_EDIT_BORDER);
	DeleteObject(hB_EDIT_DARK3);
	DeleteObject(hB_LIST_HIGHLIGHT);
	DeleteObject(hB_LIST_Disabled);
	DeleteObject(hB_LIST_Disabled_DARK);
	DeleteObject(hB_LIST_Disable1);
	DeleteObject(hB_LIST_Disable1_DARK);
	DeleteObject(hB_LIST_Disable2);
	DeleteObject(hB_LIST_Header);
	DeleteObject(hB_MENU_CLONE);
	DeleteObject(hB_MENU_SELECTED);
	DeleteObject(hB_CHECKBOX_UNCHECKED);
	DeleteObject(hB_CHECKBOX_DARK);
		
	DeleteObject(hLog);
	DeleteObject(hSerial);
	DeleteObject(hNotepad);
	DeleteObject(hStatus);
	DeleteObject(hTab);
	DeleteObject(hTab2);
	DeleteObject(hPostIt);
	DeleteObject(hLegend);
	DeleteObject(hLegend2);
	DeleteObject(hLegend3);
	DeleteObject(hLegend4);
	DeleteObject(hEdit);
	DeleteObject(hEdit2);
	DeleteObject(hEdit3);
	DeleteObject(hStatic);
	DeleteObject(hStatic2);
	DeleteObject(hStatic3);
	DeleteObject(hCheck2);
	DeleteObject(hCheck3);
	DeleteObject(hCombo);
	DeleteObject(hCombo2);
	DeleteObject(hButton);
	DeleteObject(hButton2);
	DeleteObject(hMenu);
	DeleteObject(hMenu2);
	DeleteObject(hList);
	DeleteObject(hTopMost);
	DeleteObject(hAbout);
	DeleteObject(hTooltip);
	DeleteObject(hDelete);

	if (hMagnification != nullptr)
		FreeLibrary(hMagnification);
}

BOOL Settings::Init(WCHAR* inifile)
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

void Settings::LoadLanguage()
{
	setCountry(GetPrivateProfileInt(TEXT("Profile"), TEXT("Country"), 0, m_file));
	::LoadLanguage();
}

void Settings::Load(int category, bool isExport)
{
	int VersionDateCheck = 0;
	if (isExport)
	{
		if (m_file2[0] == 0)
			return;

		VersionDateCheck = max(0, GetPrivateProfileInt(TEXT("Profile"), TEXT("VersionDate"), 0, m_file2));

		swprintf_s(Mappingtxt, 20, L"Mapping");
		swprintf_s(RapidFiretxt, 20, L"RapidFire");
		swprintf_s(Keymaptxt, 20, L"Keymap");
		swprintf_s(XOutputtxt, 20, L"XOutput");
	}
	else
	{
		if (m_file[0] == 0)
			return;

		if (category != Setting_Create && category != Setting_Update)
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
					Load(Setting_Create);
					Save(Setting_All);
					SendMessage(Ds2hWnd, WM_RESET, 0, 0);
				}
				Profile = 1;
				Save(Setting_Profile);
				Save(Setting_GiveMapping);
				Load(Setting_Mappingdata);
				return;
			}
		}
		setProfile(Profile);

		VersionDateCheck = max(0, GetPrivateProfileInt(TEXT("Profile"), TEXT("VersionDate"), 0, m_file));

		if (VersionDateCheck && VersionDateCheck < 202112101)
		{
			RECT win;
			GetWindowRect(Ds2hWnd, &win);
			MessageBoxPos(Ds2hWnd, L"Your .ini file is too old\nto be updated with this version,\nupgrade with 20211210-1 then 20220328-1 before this one", I18N.MBOX_ErrTitle, MB_ICONERROR, win.left, win.top + 30);
			BreakAndExit = true;
			return;
		}
		if (VersionDateCheck && VersionDateCheck < 202203281)
		{
			RECT win;
			GetWindowRect(Ds2hWnd, &win);
			MessageBoxPos(Ds2hWnd, L"Your .ini file is too old\nto be updated with this version,\nupgrade with 20220328-1 before this one", I18N.MBOX_ErrTitle, MB_ICONERROR, win.left, win.top + 30);
			BreakAndExit = true;
			return;
		}
		if (VersionDateCheck && VersionDateCheck < 202211131)
		{
			RECT win;
			GetWindowRect(Ds2hWnd, &win);
			MessageBoxPos(Ds2hWnd, L"Your .ini file is too old\nto be updated with this version,\nupgrade with 20221113-1 before this one", I18N.MBOX_ErrTitle, MB_ICONERROR, win.left, win.top + 30);
			BreakAndExit = true;
			return;
		}

		swprintf_s(Settingstxt, 20, L"%dSettings", Profile);
		swprintf_s(Mappingtxt, 20, L"%dMapping", Profile);
		swprintf_s(RapidFiretxt, 20, L"%dRapidFire", Profile);
		swprintf_s(Keymaptxt, 20, L"%dKeymap", Profile);
		swprintf_s(XOutputtxt, 20, L"%dXOutput", Profile);
		swprintf_s(Guardiantxt, 20, L"%dGuardian", Profile);
		swprintf_s(Webtxt, 20, L"%dWeb", Profile);
		swprintf_s(ViGEmtxt, 20, L"%dViGEm", Profile);

		if (category == Setting_All && category != Setting_Create && category != Setting_Update)
		{
			if (VersionDateCheck < VersionDate)
			{
				unsigned char ProfileNumberSaved = Profile;
				for (int i = 1; i < 4; i++)
				{
					if (i == 2) { FirstPass = false; }
					SendMessage(Ds2hWnd, WM_RESET, 0, 0);
					Profile = i;
					Load(Setting_Update);
					Save(Setting_Update);
				}
				Profile = ProfileNumberSaved;
				Save(Setting_Profile);
				Save(Setting_Version);
				SendMessage(Ds2hWnd, WM_RESET, 0, 0);
				FirstPass = true;
				Load(Setting_All);
				return;
			}
		}
	}

	bool Create = false;
	bool Update = false;
	switch (category)
	{
	case Setting_Create:
	{
		Create = true;
		[[fallthrough]];
	}
	case Setting_Update:
	{
		if (!Create)
			Update = true;
		category = Setting_All;
		[[fallthrough]];
	}
	case Setting_All:
	{
		[[fallthrough]];
	}
	case Setting_Country:
	{
		if (category != Setting_All)			//////////////////////////
			break;
		[[fallthrough]];
	}
	case Setting_Profile:
	{
		if (category != Setting_All)			//////////////////////////
			break;
		[[fallthrough]];
	}
	case Setting_TopMost:
	{
		TopMost = (GetPrivateProfileInt(TEXT("Profile"), TEXT("TopMost"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Transparency:
	{
		Transparency = (GetPrivateProfileInt(TEXT("Profile"), TEXT("Transparency"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyShutDown:
	{
		vJoyShutDown = (GetPrivateProfileInt(L"Profile", TEXT("vJoyShutDown"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Tasktray:
	{
		Tasktray = (GetPrivateProfileInt(TEXT("Profile"), TEXT("Tasktray"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_CloseMinimize:
	{
		CloseMinimize = (GetPrivateProfileInt(TEXT("Profile"), TEXT("CloseMinimize"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DisconnectBT:
	{
		DisconnectBT = (GetPrivateProfileInt(TEXT("Profile"), TEXT("DisconnectBT"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_LowBattAlert:
	{
		LowBattAlert = (GetPrivateProfileInt(TEXT("Profile"), TEXT("LowBattAlert"), 1, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Serial:
	{
		GetPrivateProfileString(L"Profile", L"Serial", L"", Serial, sizeof(Serial) / sizeof(Serial[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Device1:
	{
		GetPrivateProfileString(L"Profile", L"Device1", L"", Device1, sizeof(Device1) / sizeof(Device1[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Device2:
	{
		GetPrivateProfileString(L"Profile", L"Device2", L"", Device2, sizeof(Device2) / sizeof(Device2[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Dispatch1:
	{
		{
			WCHAR buf[MAX_PATH] = { 0 };
			byte dispatchInit[SrceDispatchID::Dispatch_Count] = { 0 };					//XBOX
			dispatchInit[SrceDispatchID::Dispatch_LX] = SrceDIAxisID::DIAxisID_1_X;
			dispatchInit[SrceDispatchID::Dispatch_LY] = SrceDIAxisID::DIAxisID_1_Y;
			dispatchInit[SrceDispatchID::Dispatch_RX] = SrceDIAxisID::DIAxisID_1_RX;
			dispatchInit[SrceDispatchID::Dispatch_RY] = SrceDIAxisID::DIAxisID_1_RY;
			dispatchInit[SrceDispatchID::Dispatch_L2TR] = SrceDIAxisID::DIAxisID_1_Z;
			dispatchInit[SrceDispatchID::Dispatch_R2TR] = SrceDIAxisID::DIAxisID_1_RZ;
			dispatchInit[SrceDispatchID::Dispatch_DPAD] = SrceDIPOVID::DIPOVID_1_1;
			dispatchInit[SrceDispatchID::Dispatch_SQUARE] = SrceDIButtonID::DIButtonID_1_3;
			dispatchInit[SrceDispatchID::Dispatch_CROSS] = SrceDIButtonID::DIButtonID_1_1;
			dispatchInit[SrceDispatchID::Dispatch_CIRCLE] = SrceDIButtonID::DIButtonID_1_2;
			dispatchInit[SrceDispatchID::Dispatch_TRIANGLE] = SrceDIButtonID::DIButtonID_1_4;
			dispatchInit[SrceDispatchID::Dispatch_L1] = SrceDIButtonID::DIButtonID_1_5;
			dispatchInit[SrceDispatchID::Dispatch_R1] = SrceDIButtonID::DIButtonID_1_6;
			dispatchInit[SrceDispatchID::Dispatch_SHARE] = SrceDIButtonID::DIButtonID_1_7;
			dispatchInit[SrceDispatchID::Dispatch_OPTIONS] = SrceDIButtonID::DIButtonID_1_8;
			dispatchInit[SrceDispatchID::Dispatch_L3] = SrceDIButtonID::DIButtonID_1_10;
			dispatchInit[SrceDispatchID::Dispatch_R3] = SrceDIButtonID::DIButtonID_1_11;
			dispatchInit[SrceDispatchID::Dispatch_PS] = SrceDIButtonID::DIButtonID_1_9;
			std::wstring dispatchInitStr = L"";
			for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
				dispatchInitStr += std::to_wstring(dispatchInit[i]) + L",";

			GetPrivateProfileString(L"Profile", L"diDispatch1", dispatchInitStr.c_str(), buf, sizeof(buf) / sizeof(buf[0]), m_file);
			std::wstringstream ss(buf);
			for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
			{
				std::wstring substr;
				getline(ss, substr, L',');
				setDispatch(i, _wtoi(substr.c_str()), 1);
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Dispatch2:
	{
		{
			WCHAR buf[MAX_PATH] = { 0 };
			byte dispatchInit[SrceDispatchID::Dispatch_Count] = { 0 };					//PS3
			dispatchInit[SrceDispatchID::Dispatch_LX] = SrceDIAxisID::DIAxisID_1_X;
			dispatchInit[SrceDispatchID::Dispatch_LY] = SrceDIAxisID::DIAxisID_1_Y;
			dispatchInit[SrceDispatchID::Dispatch_RX] = SrceDIAxisID::DIAxisID_1_Z;
			dispatchInit[SrceDispatchID::Dispatch_RY] = SrceDIAxisID::DIAxisID_1_RX;
			dispatchInit[SrceDispatchID::Dispatch_DPAD] = SrceDIPOVID::DIPOVID_1_1;
			dispatchInit[SrceDispatchID::Dispatch_SQUARE] = SrceDIButtonID::DIButtonID_1_1;
			dispatchInit[SrceDispatchID::Dispatch_CROSS] = SrceDIButtonID::DIButtonID_1_2;
			dispatchInit[SrceDispatchID::Dispatch_CIRCLE] = SrceDIButtonID::DIButtonID_1_3;
			dispatchInit[SrceDispatchID::Dispatch_TRIANGLE] = SrceDIButtonID::DIButtonID_1_4;
			dispatchInit[SrceDispatchID::Dispatch_L1] = SrceDIButtonID::DIButtonID_1_5;
			dispatchInit[SrceDispatchID::Dispatch_R1] = SrceDIButtonID::DIButtonID_1_6;
			dispatchInit[SrceDispatchID::Dispatch_L2] = SrceDIButtonID::DIButtonID_1_7;
			dispatchInit[SrceDispatchID::Dispatch_R2] = SrceDIButtonID::DIButtonID_1_8;
			dispatchInit[SrceDispatchID::Dispatch_SHARE] = SrceDIButtonID::DIButtonID_1_9;
			dispatchInit[SrceDispatchID::Dispatch_OPTIONS] = SrceDIButtonID::DIButtonID_1_10;
			dispatchInit[SrceDispatchID::Dispatch_L3] = SrceDIButtonID::DIButtonID_1_11;
			dispatchInit[SrceDispatchID::Dispatch_R3] = SrceDIButtonID::DIButtonID_1_12;
			dispatchInit[SrceDispatchID::Dispatch_PS] = SrceDIButtonID::DIButtonID_1_13;
			std::wstring dispatchInitStr = L"";
			for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
				dispatchInitStr += std::to_wstring(dispatchInit[i]) + L",";

			GetPrivateProfileString(L"Profile", L"diDispatch2", dispatchInitStr.c_str(), buf, sizeof(buf) / sizeof(buf[0]), m_file);
			std::wstringstream ss(buf);
			for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
			{
				std::wstring substr;
				getline(ss, substr, L',');
				setDispatch(i, _wtoi(substr.c_str()), 2);
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Dispatch3:
	{
		{
			WCHAR buf[MAX_PATH] = { 0 };
			byte dispatchInit[SrceDispatchID::Dispatch_Count] = { 0 };					//PS5
			dispatchInit[SrceDispatchID::Dispatch_LX] = SrceDIAxisID::DIAxisID_1_X;
			dispatchInit[SrceDispatchID::Dispatch_LY] = SrceDIAxisID::DIAxisID_1_Y;
			dispatchInit[SrceDispatchID::Dispatch_RX] = SrceDIAxisID::DIAxisID_1_Z;
			dispatchInit[SrceDispatchID::Dispatch_RY] = SrceDIAxisID::DIAxisID_1_RZ;
			dispatchInit[SrceDispatchID::Dispatch_L2TR] = SrceDIAxisID::DIAxisID_1_RX;
			dispatchInit[SrceDispatchID::Dispatch_R2TR] = SrceDIAxisID::DIAxisID_1_RY;
			dispatchInit[SrceDispatchID::Dispatch_DPAD] = SrceDIPOVID::DIPOVID_1_1;
			dispatchInit[SrceDispatchID::Dispatch_SQUARE] = SrceDIButtonID::DIButtonID_1_1;
			dispatchInit[SrceDispatchID::Dispatch_CROSS] = SrceDIButtonID::DIButtonID_1_2;
			dispatchInit[SrceDispatchID::Dispatch_CIRCLE] = SrceDIButtonID::DIButtonID_1_3;
			dispatchInit[SrceDispatchID::Dispatch_TRIANGLE] = SrceDIButtonID::DIButtonID_1_4;
			dispatchInit[SrceDispatchID::Dispatch_L1] = SrceDIButtonID::DIButtonID_1_5;
			dispatchInit[SrceDispatchID::Dispatch_R1] = SrceDIButtonID::DIButtonID_1_6;
			dispatchInit[SrceDispatchID::Dispatch_L2] = SrceDIButtonID::DIButtonID_1_7;
			dispatchInit[SrceDispatchID::Dispatch_R2] = SrceDIButtonID::DIButtonID_1_8;
			dispatchInit[SrceDispatchID::Dispatch_SHARE] = SrceDIButtonID::DIButtonID_1_9;
			dispatchInit[SrceDispatchID::Dispatch_OPTIONS] = SrceDIButtonID::DIButtonID_1_10;
			dispatchInit[SrceDispatchID::Dispatch_L3] = SrceDIButtonID::DIButtonID_1_11;
			dispatchInit[SrceDispatchID::Dispatch_R3] = SrceDIButtonID::DIButtonID_1_12;
			dispatchInit[SrceDispatchID::Dispatch_PS] = SrceDIButtonID::DIButtonID_1_13;
			dispatchInit[SrceDispatchID::Dispatch_TOUCH] = SrceDIButtonID::DIButtonID_1_14;
			dispatchInit[SrceDispatchID::Dispatch_MUTE] = SrceDIButtonID::DIButtonID_1_15;
			std::wstring dispatchInitStr = L"";
			for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
				dispatchInitStr += std::to_wstring(dispatchInit[i]) + L",";

			GetPrivateProfileString(L"Profile", L"diDispatch3", dispatchInitStr.c_str(), buf, sizeof(buf) / sizeof(buf[0]), m_file);
			std::wstringstream ss(buf);
			for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
			{
				std::wstring substr;
				getline(ss, substr, L',');
				setDispatch(i, _wtoi(substr.c_str()), 3);
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_BlackLedOnExit:
	{
		BlackLedOnExit = (GetPrivateProfileInt(TEXT("Profile"), TEXT("BlackLedOnExit"), 1, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MappingViewMode:
	{
		MappingViewMode = (GetPrivateProfileInt(TEXT("Profile"), TEXT("MappingViewMode"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_CloneViewMode:
	{
		CloneViewMode = (GetPrivateProfileInt(TEXT("Profile"), TEXT("CloneViewMode"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_NotepadFont:
	{
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
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MappingPaused:
	{
		MappingPaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("MappingPaused"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RapidFirePaused:
	{
		RapidFirePaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("RapidFirePaused"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_KeymapPaused:
	{
		KeymapPaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("KeymapPaused"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyPaused:
	{
		vJoyPaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("vJoyPaused"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_XOutputPaused:
	{
		XOutputPaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("XOutputPaused"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_GuardianPaused:
	{
		GuardianPaused = (GetPrivateProfileInt(TEXT("Tray"), TEXT("GuardianPaused"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RemoveBlacklist:
	{
		RemoveBlacklist = (GetPrivateProfileInt(L"Guardian", TEXT("RemoveBlacklist"), 1, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_PurgeWhitelist:
	{
		PurgeWhitelist = (GetPrivateProfileInt(L"Guardian", TEXT("PurgeWhitelist"), 1, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID1:
	{
		GetPrivateProfileString(L"Guardian", L"dsHID1", LR"(HID\VID_054C&PID_0BA0&MI_03)", dsHID[0], sizeof(dsHID[0]) / sizeof(dsHID[0][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID2:
	{
		GetPrivateProfileString(L"Guardian", L"dsHID2", LR"(HID\VID_054C&PID_0CE6&MI_03)", dsHID[1], sizeof(dsHID[1]) / sizeof(dsHID[1][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID3:
	{
		GetPrivateProfileString(L"Guardian", L"dsHID3", L"", dsHID[2], sizeof(dsHID[2]) / sizeof(dsHID[2][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe1Name:
	{
		GetPrivateProfileString(L"Guardian", L"Exe1Name", L"RemotePlay.exe", Exe1Name, sizeof(Exe1Name) / sizeof(Exe1Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe2Name:
	{
		GetPrivateProfileString(L"Guardian", L"Exe2Name", L"", Exe2Name, sizeof(Exe2Name) / sizeof(Exe2Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe3Name:
	{
		GetPrivateProfileString(L"Guardian", L"Exe3Name", L"", Exe3Name, sizeof(Exe3Name) / sizeof(Exe3Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe4Name:
	{
		GetPrivateProfileString(L"Guardian", L"Exe4Name", L"", Exe4Name, sizeof(Exe4Name) / sizeof(Exe4Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe5Name:
	{
		GetPrivateProfileString(L"Guardian", L"Exe5Name", L"", Exe5Name, sizeof(Exe5Name) / sizeof(Exe5Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebRefreshTime:
	{
		setWebRefreshTime(GetPrivateProfileInt(L"Web", TEXT("WebRefreshTime"), 20, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DefaultZoomValue:
	{
		setDefaultZoomValue(GetPrivateProfileInt(L"Web", TEXT("DefaultZoomValue"), 470, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DarkMode:
	{
		setDarkMode(GetPrivateProfileInt(L"Web", TEXT("DarkMode"), 1, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RawBounds:
	{
		RawBounds = (GetPrivateProfileInt(L"Web", TEXT("RawBounds"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebLanguage:
	{
		{
			WCHAR buf[MAX_PATH] = { 0 };
			GetPrivateProfileString(L"Web", L"WebLanguage", L"", buf, sizeof(buf) / sizeof(buf[0]), m_file);
			WebLanguage = buf;
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_UserAgent:
	{
		{
			WCHAR buf[1024] = { 0 };
			GetPrivateProfileString(L"Web", L"UserAgent", L"", buf, sizeof(buf) / sizeof(buf[0]), m_file);
			UserAgent = buf;
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_BlockedSites:
	{
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
				delete[] buf;
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL0:
	{
		GetPrivateProfileString(L"Web", L"WebURL1", LR"(https://www.google.com)", WebURL[0], sizeof(WebURL[0]) / sizeof(WebURL[0][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL1:
	{
		GetPrivateProfileString(L"Web", L"WebURL2", L"", WebURL[1], sizeof(WebURL[1]) / sizeof(WebURL[1][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL2:
	{
		GetPrivateProfileString(L"Web", L"WebURL3", L"", WebURL[2], sizeof(WebURL[2]) / sizeof(WebURL[2][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL3:
	{
		GetPrivateProfileString(L"Web", L"WebURL4", L"", WebURL[3], sizeof(WebURL[3]) / sizeof(WebURL[3][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL4:
	{
		GetPrivateProfileString(L"Web", L"WebURL5", L"", WebURL[4], sizeof(WebURL[4]) / sizeof(WebURL[4][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL5:
	{
		GetPrivateProfileString(L"Web", L"WebURL6", LR"(file:///C:/Windows/Web/Wallpaper/Windows/img0.jpg)", WebURL[5], sizeof(WebURL[5]) / sizeof(WebURL[5][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL6:
	{
		GetPrivateProfileString(L"Web", L"WebURL7", L"", WebURL[6], sizeof(WebURL[6]) / sizeof(WebURL[6][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL7:
	{
		GetPrivateProfileString(L"Web", L"WebURL8", L"", WebURL[7], sizeof(WebURL[7]) / sizeof(WebURL[7][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL8:
	{
		GetPrivateProfileString(L"Web", L"WebURL9", L"", WebURL[8], sizeof(WebURL[8]) / sizeof(WebURL[8][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL9:
	{
		GetPrivateProfileString(L"Web", L"WebURL10", L"", WebURL[9], sizeof(WebURL[9]) / sizeof(WebURL[9][0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_InitialScript:
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
				delete[] buf;
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App0Name:
	{
		GetPrivateProfileString(L"Links", L"App0Name", L"Avoid", App0Name, sizeof(App0Name) / sizeof(App0Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App1Name:
	{
		GetPrivateProfileString(L"Links", L"App1Name", L"Prefer", App1Name, sizeof(App1Name) / sizeof(App1Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App2Name:
	{
		GetPrivateProfileString(L"Links", L"App2Name", L"", App2Name, sizeof(App2Name) / sizeof(App2Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App3Name:
	{
		GetPrivateProfileString(L"Links", L"App3Name", L"", App3Name, sizeof(App3Name) / sizeof(App3Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App4Name:
	{
		GetPrivateProfileString(L"Links", L"App4Name", L"", App4Name, sizeof(App4Name) / sizeof(App4Name[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App0Location:
	{
		GetPrivateProfileString(L"Links", L"App0Location", LR"(C:\Windows\System32\cmd.exe /C "joy.cpl")", App0Location, sizeof(App0Location) / sizeof(App0Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App1Location:
	{
		GetPrivateProfileString(L"Links", L"App1Location", LR"(rundll32.exe shell32.dll,Control_RunDLL joy.cpl)", App1Location, sizeof(App1Location) / sizeof(App1Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App2Location:
	{
		GetPrivateProfileString(L"Links", L"App2Location", L"", App2Location, sizeof(App2Location) / sizeof(App2Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App3Location:
	{
		GetPrivateProfileString(L"Links", L"App3Location", L"", App3Location, sizeof(App3Location) / sizeof(App3Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App4Location:
	{
		GetPrivateProfileString(L"Links", L"App4Location", L"", App4Location, sizeof(App4Location) / sizeof(App4Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App5Location:
	{
		GetPrivateProfileString(L"Links", L"App5Location", L"", App5Location, sizeof(App5Location) / sizeof(App5Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App6Location:
	{
		GetPrivateProfileString(L"Links", L"App6Location", L"", App6Location, sizeof(App6Location) / sizeof(App6Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App7Location:
	{
		GetPrivateProfileString(L"Links", L"App7Location", L"", App7Location, sizeof(App7Location) / sizeof(App7Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App8Location:
	{
		GetPrivateProfileString(L"Links", L"App8Location", L"", App8Location, sizeof(App8Location) / sizeof(App8Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App9Location:
	{
		GetPrivateProfileString(L"Links", L"App9Location", L"", App9Location, sizeof(App9Location) / sizeof(App9Location[0]), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Notepad:
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
				delete[] buf;
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Opacity:
	{
		setOpacity(GetPrivateProfileInt(Settingstxt, TEXT("Opacity"), 60, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_PreferredSource:
	{
		setPreferredSource(GetPrivateProfileInt(Settingstxt, TEXT("PreferredSource"), 0, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MouseActive:
	{
		setMouseActive(GetPrivateProfileInt(Settingstxt, TEXT("MouseActive"), 0, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_KeyboardActive:
	{
		KeyboardActive = (GetPrivateProfileInt(Settingstxt, TEXT("KeyboardActive"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyDevice:
	{
		setvJoyDevice(GetPrivateProfileInt(Settingstxt, TEXT("vJoyDevice"), 0, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_XInputDevice:
	{
		setXInputDevice(GetPrivateProfileInt(Settingstxt, TEXT("XInputDevice"), 0, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Threshold:
	{
		setThreshold(GetPrivateProfileInt(Settingstxt, TEXT("Threshold"), 2056, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Simultaneous:
	{
		setSimultaneous(GetPrivateProfileInt(Settingstxt, TEXT("Simultaneous"), 40, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_LongPress:
	{
		setLongPress(GetPrivateProfileInt(Settingstxt, TEXT("LongPress"), 255, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_VeryLongPress:
	{
		setVeryLongPress(GetPrivateProfileInt(Settingstxt, TEXT("VeryLongPress"), 3287, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MouseCanBypass:
	{
		MouseCanBypass = (GetPrivateProfileInt(Settingstxt, TEXT("MouseCanBypass"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TriggersMode:
	{
		setTriggersMode(GetPrivateProfileInt(Settingstxt, TEXT("TriggersMode"), 0, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Dispatch:
	{
		{
			WCHAR buf[MAX_PATH] = { 0 };
			byte dispatchInit[SrceDispatchID::Dispatch_Count] = { 0 };
			dispatchInit[SrceDispatchID::Dispatch_LX] = SrceDIAxisID::DIAxisID_1_X;
			dispatchInit[SrceDispatchID::Dispatch_LY] = SrceDIAxisID::DIAxisID_1_Y;
			dispatchInit[SrceDispatchID::Dispatch_RX] = SrceDIAxisID::DIAxisID_1_Z;
			dispatchInit[SrceDispatchID::Dispatch_RY] = SrceDIAxisID::DIAxisID_1_RZ;
			dispatchInit[SrceDispatchID::Dispatch_L2TR] = SrceDIAxisID::DIAxisID_1_RX;
			dispatchInit[SrceDispatchID::Dispatch_R2TR] = SrceDIAxisID::DIAxisID_1_RY;
			dispatchInit[SrceDispatchID::Dispatch_DPAD] = SrceDIPOVID::DIPOVID_1_1;
			dispatchInit[SrceDispatchID::Dispatch_SQUARE] = SrceDIButtonID::DIButtonID_1_1;
			dispatchInit[SrceDispatchID::Dispatch_CROSS] = SrceDIButtonID::DIButtonID_1_2;
			dispatchInit[SrceDispatchID::Dispatch_CIRCLE] = SrceDIButtonID::DIButtonID_1_3;
			dispatchInit[SrceDispatchID::Dispatch_TRIANGLE] = SrceDIButtonID::DIButtonID_1_4;
			dispatchInit[SrceDispatchID::Dispatch_L1] = SrceDIButtonID::DIButtonID_1_5;
			dispatchInit[SrceDispatchID::Dispatch_R1] = SrceDIButtonID::DIButtonID_1_6;
			dispatchInit[SrceDispatchID::Dispatch_L2] = SrceDIButtonID::DIButtonID_1_7;
			dispatchInit[SrceDispatchID::Dispatch_R2] = SrceDIButtonID::DIButtonID_1_8;
			dispatchInit[SrceDispatchID::Dispatch_SHARE] = SrceDIButtonID::DIButtonID_1_9;
			dispatchInit[SrceDispatchID::Dispatch_OPTIONS] = SrceDIButtonID::DIButtonID_1_10;
			dispatchInit[SrceDispatchID::Dispatch_L3] = SrceDIButtonID::DIButtonID_1_11;
			dispatchInit[SrceDispatchID::Dispatch_R3] = SrceDIButtonID::DIButtonID_1_12;
			dispatchInit[SrceDispatchID::Dispatch_PS] = SrceDIButtonID::DIButtonID_1_13;
			dispatchInit[SrceDispatchID::Dispatch_TOUCH] = SrceDIButtonID::DIButtonID_1_14;
			dispatchInit[SrceDispatchID::Dispatch_MUTE] = SrceDIButtonID::DIButtonID_1_15;
			std::wstring dispatchInitStr = L"";
			for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
				dispatchInitStr += std::to_wstring(dispatchInit[i]) + L",";

			GetPrivateProfileString(Settingstxt, L"diDispatch", dispatchInitStr.c_str(), buf, sizeof(buf) / sizeof(buf[0]), m_file);
			std::wstringstream ss(buf);
			for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
			{
				std::wstring substr;
				getline(ss, substr, L',');
				setDispatch(i, _wtoi(substr.c_str()));
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DarkTheme:
	{
		DarkTheme = (GetPrivateProfileInt(Settingstxt, TEXT("DarkTheme"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TouchPadButton:
	{
		setTouchPadButton(GetPrivateProfileInt(Settingstxt, TEXT("TouchPadButton"), 0, m_file));
		setSplitTouch();
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TouchCol:
	{
		setTouchCol(GetPrivateProfileInt(Settingstxt, TEXT("TouchCol"), 1, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TouchRow:
	{
		setTouchRow(GetPrivateProfileInt(Settingstxt, TEXT("TouchRow"), 1, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_LED_Color:
	{
		setLED(GetPrivateProfileInt(Settingstxt, TEXT("LED_Color"), 0xFF0000, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Wave_Speed:
	{
		setWaveSpeed(GetPrivateProfileInt(Settingstxt, TEXT("WaveSpeed"), 130, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TabMapping:
	{
		setTabMapping(GetPrivateProfileInt(Settingstxt, TEXT("TabMapping"), 0, m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TabToMode:
	{
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
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Reminder:
	{
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
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Stats:
	{
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
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Mappingdata:
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
				int ret = GetPrivateProfileSectionW(Mappingtxt, buf, n, (isExport) ? m_file2 : m_file);
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
						for (int i = 0; i < MappingName::MappingName_Count; i++)
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
							case Mapping_Pause: { btn.Pause = max(0, min(3, _wtoi(key))); break; }
							case Mapping_Transitivity: { btn.Transitivity = max(0, min(2, _wtoi(key))); break; }
							case Mapping_Toggle: { btn.Toggle = max(0, min(2, _wtoi(key))); break; }
							case Mapping_Target: { for (int i = 0; i < 5; i++) { btn.Target[i] = max(0, min(3, CheckboxString(key, i))); } break; }
							case Mapping_dsID:
							{
								for (int i = 0; i < 5; i++)
								{
									switch (btn.Target[i])
									{
									case 0: { btn.srceID[i] = max(SrceButtonID::Button_None, min(SrceButtonID::Button_Count, dsIDString(key, i))); break; }
									case 1: { btn.srceID[i] = max(SrceButtonID::Sisaxis_None, min(SrceButtonID::Sisaxis_Count, dsIDString(key, i) + SourceButton::Sisaxis_None)); break; }
									case 2: { btn.srceID[i] = max(SrceButtonID::Keyboard_None, min(SrceButtonID::Keyboard_Count, dsIDString(key, i) + SourceButton::Keyboard_None)); break; }
									case 3: { btn.srceID[i] = max(DestButtonID::Destination_None, min(DestButtonID::Destination_Count, dsIDString(key, i))); break; }
									}
								}
								break;
							}
							case Mapping_OrXorNot: { for (int i = 0; i < 4; i++) { btn.OrXorNot[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_dsDisable: { for (int i = 0; i < 5; i++) { btn.srceDisable[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_ActionType: { for (int i = 0; i < 8; i++) { btn.ActionType[i] = max(0, min(5, CheckboxString(key, i, true))); } break; }
							case Mapping_vjID: {
								for (int i = 0; i < 8; i++)
								{
									btn.destID[i] = max(0, min((btn.ActionType[i]) ? ((btn.ActionType[i] == 1) ? Mapping::MouseAction_Count : ((btn.ActionType[i] == 2) ? Mapping::SpecialAction_Count : ((btn.ActionType[i] == 3) ? DestAxisMoveID::AxisMove_Count : ((btn.ActionType[i] == 4) ? DestAfterEffectID::AfterEffect_Count : Mapping::ModulesAction_Count)))) : DestButtonID::Destination_Count, vjIDString(key, i)));
								}
								break;
							}
							case Mapping_Overcontrol: { for (int i = 0; i < 8; i++) { btn.Overcontrol[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_Switch: { for (int i = 0; i < 8; i++) { btn.Switch[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_OnRelease: { for (int i = 0; i < 8; i++) { btn.OnRelease[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_NoRelease: { for (int i = 0; i < 8; i++) { btn.NoRelease[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_NlRelease: { for (int i = 0; i < 8; i++) { btn.NlRelease[i] = max(0, min(2, CheckboxString(key, i))); } break; }
							case Mapping_vjDisable: { for (int i = 0; i < 8; i++) { btn.destDisable[i] = max(0, min(2, CheckboxString(key, i))); } break; }
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
				delete[] buf;
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RapidFiredata:
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
				int ret = GetPrivateProfileSectionW(RapidFiretxt, buf, n, (isExport) ? m_file2 : m_file);
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

						int mapdata[RapidFireName::RapidFireName_Count] = { 0 };
						for (int i = 0; i < RapidFireName::RapidFireName_Count; i++)
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
				delete[] buf;
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Keymapdata:
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
				int ret = GetPrivateProfileSectionW(Keymaptxt, buf, n, (isExport) ? m_file2 : m_file);
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
						if (btnid < DestButtonID::Destination_None || btnid >= DestButtonID::Destination_Count)
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
				delete[] buf;
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_XOutputActive:
	{
		XOutputActive = (GetPrivateProfileInt(XOutputtxt, TEXT("XOutputActive"), 0, (isExport) ? m_file2 : m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyActive:
	{
		vJoyActive = (GetPrivateProfileInt(XOutputtxt, TEXT("vJoyActive"), 0, (isExport) ? m_file2 : m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DesiredVirtualPad:
	{
		setDesiredVirtualPad(GetPrivateProfileInt(XOutputtxt, TEXT("DesiredVirtualPad"), 1, (isExport) ? m_file2 : m_file));
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_target_DS4:
	{
		{
			const int n = 128 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0)
			{
				MessageBoxPos(Ds2hWnd, L"Not enough memory\nto load vigem,\nany modification\nwill be lost on exit.", L"Careful", MB_OK, 0, 0, 180);
				cansavexoutput = false;
			}
			else
			{
				int vjtotalvalues_DS4 = 0;
				WCHAR* head = buf;
				int ret = GetPrivateProfileSectionW(XOutputtxt, buf, n, (isExport) ? m_file2 : m_file);
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
						if (wcscmp(key, L"DS4"))
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
							vjtotalvalues_DS4++; target_DS4[i] = (byte)k;
							if (value == 0)
								break;
						}
						key = head;
					}
				}
				if (vjtotalvalues_DS4 == 0)
				{
					target_DS4[0] = DestButtonID::Button1;
					target_DS4[1] = DestButtonID::Button2;
					target_DS4[2] = DestButtonID::Button3;
					target_DS4[3] = DestButtonID::Button4;
					target_DS4[4] = DestButtonID::Button5;
					target_DS4[5] = DestButtonID::Button6;
					target_DS4[6] = DestButtonID::Button7;
					target_DS4[7] = DestButtonID::Button8;
					target_DS4[8] = DestButtonID::Button9;
					target_DS4[9] = DestButtonID::Button10;
					target_DS4[10] = DestButtonID::Button11;
					target_DS4[11] = DestButtonID::Button12;
					target_DS4[12] = DestButtonID::Button13;
					target_DS4[13] = DestButtonID::Button14;
					target_DS4[14] = DestButtonID::Button16;
					target_DS4[15] = DestButtonID::Button17;
					target_DS4[16] = DestButtonID::Button18;
					target_DS4[17] = DestButtonID::Button19;
					target_DS4[18] = DestButtonID::RXTR;
					target_DS4[19] = DestButtonID::RYTR;
					target_DS4[20] = DestButtonID::X;
					target_DS4[21] = DestButtonID::Y;
					target_DS4[22] = DestButtonID::Z;
					target_DS4[23] = DestButtonID::RZ;
				}
				delete[] buf;
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_target_X360:
	{
		{
			const int n = 128 * 1024;
			WCHAR* buf = new WCHAR[n];
			if (buf == 0)
			{
				MessageBoxPos(Ds2hWnd, L"Not enough memory\nto load vigem,\nany modification\nwill be lost on exit.", L"Careful", MB_OK, 0, 0, 180);
				cansavexoutput = false;
			}
			else
			{
				int vjtotalvalues_X360 = 0;
				WCHAR* head = buf;
				int ret = GetPrivateProfileSectionW(XOutputtxt, buf, n, (isExport) ? m_file2 : m_file);
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
						if (wcscmp(key, L"X360"))
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
							vjtotalvalues_X360++; target_X360[i] = (byte)k;
							if (value == 0)
								break;
						}
						key = head;
					}
				}
				if (vjtotalvalues_X360 == 0)
				{
					target_X360[0] = DestButtonID::Button1;
					target_X360[1] = DestButtonID::Button2;
					target_X360[2] = DestButtonID::Button3;
					target_X360[3] = DestButtonID::Button4;
					target_X360[4] = DestButtonID::Button5;
					target_X360[5] = DestButtonID::Button6;
					target_X360[6] = DestButtonID::Button7;
					target_X360[7] = DestButtonID::Button8;
					target_X360[8] = DestButtonID::Button9;
					target_X360[9] = DestButtonID::Button10;
					target_X360[10] = DestButtonID::Button11;
					target_X360[11] = DestButtonID::Button12;
					target_X360[12] = DestButtonID::Button13;
					target_X360[13] = DestButtonID::Destination_None;
					target_X360[14] = DestButtonID::Button16;
					target_X360[15] = DestButtonID::Button17;
					target_X360[16] = DestButtonID::Destination_None;
					target_X360[17] = DestButtonID::Destination_None;
					target_X360[18] = DestButtonID::RXTR;
					target_X360[19] = DestButtonID::RYTR;
					target_X360[20] = DestButtonID::X;
					target_X360[21] = DestButtonID::Y;
					target_X360[22] = DestButtonID::Z;
					target_X360[23] = DestButtonID::RZ;
				}
				delete[] buf;
			}
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_GuardianActive:
	{
		GuardianActive = (GetPrivateProfileInt(Guardiantxt, TEXT("GuardianActive"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID1Enable:
	{
		dsHID1Enable = (GetPrivateProfileInt(Guardiantxt, TEXT("dsHID1Enable"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID2Enable:
	{
		dsHID2Enable = (GetPrivateProfileInt(Guardiantxt, TEXT("dsHID2Enable"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID3Enable:
	{
		dsHID3Enable = (GetPrivateProfileInt(Guardiantxt, TEXT("dsHID3Enable"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe1NameEnable:
	{
		Exe1NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe1NameEnable"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe2NameEnable:
	{
		Exe2NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe2NameEnable"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe3NameEnable:
	{
		Exe3NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe3NameEnable"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe4NameEnable:
	{
		Exe4NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe4NameEnable"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe5NameEnable:
	{
		Exe5NameEnable = (GetPrivateProfileInt(Guardiantxt, TEXT("Exe5NameEnable"), 0, m_file) == 1) ? true : false;
		if (category != Setting_All)
			break;
		break;
	}
	}
}

void Settings::Save(int category, bool isExport)
{
	if (isExport)
	{
		if (m_file2[0] == 0)
			return;

		swprintf_s(Mappingtxt, 20, L"Mapping");
		swprintf_s(RapidFiretxt, 20, L"RapidFire");
		swprintf_s(Keymaptxt, 20, L"Keymap");
		swprintf_s(XOutputtxt, 20, L"XOutput");
	}
	else
	{
		if (m_file[0] == 0)
			return;

		swprintf_s(Settingstxt, 20, L"%dSettings", Profile);
		swprintf_s(Mappingtxt, 20, L"%dMapping", Profile);
		swprintf_s(RapidFiretxt, 20, L"%dRapidFire", Profile);
		swprintf_s(Keymaptxt, 20, L"%dKeymap", Profile);
		swprintf_s(XOutputtxt, 20, L"%dXOutput", Profile);
		swprintf_s(Guardiantxt, 20, L"%dGuardian", Profile);
		swprintf_s(Webtxt, 20, L"%dWeb", Profile);
	}

	WCHAR buffer[MAX_PATH * 2];
	bool Create = false;
	bool Update = false;
	switch (category)
	{
	case Setting_Create:
	{
		Create = true;
		[[fallthrough]];
	}
	case Setting_Update:
	{
		if (!Create)
			Update = true;
		category = Setting_All;
		[[fallthrough]];
	}
	case Setting_All:
		[[fallthrough]];
	case Setting_Version:
	{
		if (!Update)
		{
			swprintf_s(buffer, MAX_PATH, L"%d", VersionDate);
			WritePrivateProfileString(TEXT("Profile"), TEXT("VersionDate"), buffer, (isExport) ? m_file2 : m_file);
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Country:
	{
		if (!Update)
		{
			swprintf_s(buffer, MAX_PATH, L"%d", Country);
			WritePrivateProfileString(TEXT("Profile"), TEXT("Country"), buffer, m_file);
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Profile:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", Profile);
		WritePrivateProfileString(TEXT("Profile"), TEXT("Profile"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TopMost:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("TopMost"), (TopMost) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Transparency:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("Transparency"), (Transparency) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyShutDown:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("vJoyShutDown"), (vJoyShutDown) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Tasktray:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("Tasktray"), (Tasktray) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_CloseMinimize:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("CloseMinimize"), (CloseMinimize) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DisconnectBT:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("DisconnectBT"), (DisconnectBT) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_LowBattAlert:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("LowBattAlert"), (LowBattAlert) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Serial:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("Serial"), Serial, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Device1:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("Device1"), Device1, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Device2:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("Device2"), Device2, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Dispatch1:
	{
		std::wstring dispatchInitStr = L"";
		for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
			dispatchInitStr += std::to_wstring(diDispatch1[i]) + L",";
		WritePrivateProfileString(TEXT("Profile"), TEXT("diDispatch1"), dispatchInitStr.c_str(), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Dispatch2:
	{
		std::wstring dispatchInitStr = L"";
		for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
			dispatchInitStr += std::to_wstring(diDispatch2[i]) + L",";
		WritePrivateProfileString(TEXT("Profile"), TEXT("diDispatch2"), dispatchInitStr.c_str(), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Dispatch3:
	{
		std::wstring dispatchInitStr = L"";
		for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
			dispatchInitStr += std::to_wstring(diDispatch3[i]) + L",";
		WritePrivateProfileString(TEXT("Profile"), TEXT("diDispatch3"), dispatchInitStr.c_str(), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_BlackLedOnExit:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("BlackLedOnExit"), (BlackLedOnExit) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MappingViewMode:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("MappingViewMode"), (MappingViewMode) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_CloneViewMode:
	{
		WritePrivateProfileString(TEXT("Profile"), TEXT("CloneViewMode"), (CloneViewMode) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_NotepadFont:
	{
		swprintf_s(buffer, MAX_PATH, L"%s,%d,%d", NotepadFont.c_str(), NotepadFontH, NotepadFontW);
		WritePrivateProfileString(TEXT("Profile"), TEXT("NotepadFont"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MappingPaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("MappingPaused"), (MappingPaused) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RapidFirePaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("RapidFirePaused"), (RapidFirePaused) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_KeymapPaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("KeymapPaused"), (KeymapPaused) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyPaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("vJoyPaused"), (vJoyPaused) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_XOutputPaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("XOutputPaused"), (XOutputPaused) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_GuardianPaused:
	{
		WritePrivateProfileString(TEXT("Tray"), TEXT("GuardianPaused"), (GuardianPaused) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RemoveBlacklist:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("RemoveBlacklist"), (RemoveBlacklist) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_PurgeWhitelist:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("PurgeWhitelist"), (PurgeWhitelist) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID1:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("dsHID1"), dsHID[0], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID2:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("dsHID2"), dsHID[1], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID3:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("dsHID3"), dsHID[2], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe1Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe1Name"), Exe1Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe2Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe2Name"), Exe2Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe3Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe3Name"), Exe3Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe4Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe4Name"), Exe4Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe5Name:
	{
		WritePrivateProfileString(TEXT("Guardian"), TEXT("Exe5Name"), Exe5Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebRefreshTime:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", WebRefreshTime);
		WritePrivateProfileString(TEXT("Web"), TEXT("WebRefreshTime"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DefaultZoomValue:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", int(DefaultZoomValue * 1000));
		WritePrivateProfileString(TEXT("Web"), TEXT("DefaultZoomValue"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DarkMode:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", DarkMode);
		WritePrivateProfileString(TEXT("Web"), TEXT("DarkMode "), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_RawBounds:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", RawBounds);
		WritePrivateProfileString(TEXT("Web"), TEXT("RawBounds "), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebLanguage:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebLanguage"), WebLanguage.c_str(), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_UserAgent:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("UserAgent"), UserAgent.c_str(), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_BlockedSites:
	{
		if (!cansaveblockedsites)
			MessageBoxPos(Ds2hWnd, L"Blocked sites\nwere not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
			WritePrivateProfileString(TEXT("Web"), TEXT("BlockedSites"), BlockedSites.c_str(), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL0:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL1"), WebURL[0], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL1:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL2"), WebURL[1], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL2:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL3"), WebURL[2], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL3:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL4"), WebURL[3], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL4:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL5"), WebURL[4], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL5:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL6"), WebURL[5], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL6:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL7"), WebURL[6], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL7:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL8"), WebURL[7], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL8:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL9"), WebURL[8], m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_WebURL9:
	{
		WritePrivateProfileString(TEXT("Web"), TEXT("WebURL10"), WebURL[9], m_file);
		if (category != Setting_All)
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
			delete[] buf;
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App0Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App0Name"), App0Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App1Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App1Name"), App1Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App2Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App2Name"), App2Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App3Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App3Name"), App3Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App4Name:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App4Name"), App4Name, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App0Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App0Location"), App0Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App1Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App1Location"), App1Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App2Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App2Location"), App2Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App3Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App3Location"), App3Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App4Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App4Location"), App4Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App5Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App5Location"), App5Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App6Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App6Location"), App6Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App7Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App7Location"), App6Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App8Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App8Location"), App8Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_App9Location:
	{
		WritePrivateProfileString(TEXT("Links"), TEXT("App9Location"), App9Location, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Notepad:
	{
		if (category != Setting_All)
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
				delete[] buf;
			}
			NotepadUnsaved = false;
			break;
		}
		[[fallthrough]];
	}
	case Setting_Opacity:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", Opacity);
		WritePrivateProfileString(Settingstxt, TEXT("Opacity"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_PreferredSource:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", PreferredSource);
		WritePrivateProfileString(Settingstxt, TEXT("PreferredSource"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MouseActive:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", MouseActive);
		WritePrivateProfileString(Settingstxt, TEXT("MouseActive"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_KeyboardActive:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", KeyboardActive);
		WritePrivateProfileString(Settingstxt, TEXT("KeyboardActive"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyDevice:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", vJoyDevice);
		WritePrivateProfileString(Settingstxt, TEXT("vJoyDevice"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_XInputDevice:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", XInputDevice);
		WritePrivateProfileString(Settingstxt, TEXT("XInputDevice"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Threshold:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", Threshold);
		WritePrivateProfileString(Settingstxt, TEXT("Threshold"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Simultaneous:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", Simultaneous);
		WritePrivateProfileString(Settingstxt, TEXT("Simultaneous"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_LongPress:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", LongPress);
		WritePrivateProfileString(Settingstxt, TEXT("LongPress"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_VeryLongPress:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", VeryLongPress);
		WritePrivateProfileString(Settingstxt, TEXT("VeryLongPress"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_MouseCanBypass:
	{
		WritePrivateProfileString(Settingstxt, TEXT("MouseCanBypass"), (MouseCanBypass) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TriggersMode:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TriggersMode);
		WritePrivateProfileString(Settingstxt, TEXT("TriggersMode"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Dispatch:
	{
		std::wstring dispatchInitStr = L"";
		for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
			dispatchInitStr += std::to_wstring(diDispatch[i]) + L",";
		WritePrivateProfileString(Settingstxt, TEXT("diDispatch"), dispatchInitStr.c_str(), m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DarkTheme:
	{
		WritePrivateProfileString(Settingstxt, TEXT("DarkTheme"), (DarkTheme) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TouchPadButton:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TouchPadButton);
		WritePrivateProfileString(Settingstxt, TEXT("TouchPadButton"), buffer, m_file);
		setSplitTouch();
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TouchCol:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TouchCol);
		WritePrivateProfileString(Settingstxt, TEXT("TouchCol"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TouchRow:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TouchRow);
		WritePrivateProfileString(Settingstxt, TEXT("TouchRow"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_LED_Color:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", LED_Color);
		WritePrivateProfileString(Settingstxt, TEXT("LED_Color"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Wave_Speed:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", WaveSpeed);
		WritePrivateProfileString(Settingstxt, TEXT("WaveSpeed"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TabMapping:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", TabMapping);
		WritePrivateProfileString(Settingstxt, TEXT("TabMapping"), buffer, m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_TabToMode:
	{
		swprintf_s(buffer, MAX_PATH, L"%d,%d,%d,%d,%d,%d,%d,%d,%d", Mode[0], Mode[1], Mode[2], Mode[3], Mode[4], Mode[5], Mode[6], Mode[7], Mode[8]);
		WritePrivateProfileString(Settingstxt, TEXT("TabToMode"), buffer, m_file);
		if (category != Setting_All)
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
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Stats:
	{
		swprintf_s(buffer, MAX_PATH, L"%d,%d,%d,%d,%d,%d,%d,%d", Stat[0], Stat[1], Stat[2], Stat[3], Stat[4], Stat[5], Stat[6], Stat[7]);
		WritePrivateProfileString(Settingstxt, TEXT("Stats"), buffer, m_file);
		if (category != Setting_All)
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
				for (int j = 0; j < MappingName::MappingName_Count; j++)
					switch (j)
					{
					case Mapping_Enable: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Enable); break; }
					case Mapping_Tab: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Tab); break; }
					case Mapping_Ifmouse: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Ifmouse); break; }
					case Mapping_Force: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Force); break; }
					case Mapping_Short: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Short); break; }
					case Mapping_Double: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Double); break; }
					case Mapping_Long: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Long); break; }
					case Mapping_Led: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Led); break; }
					case Mapping_Macro: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Macro); break; }
					case Mapping_Pause: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Pause); break; }
					case Mapping_Transitivity: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Transitivity); break; }
					case Mapping_Toggle: { head += swprintf_s(head, MAX_PATH, L"%d,", btn->Toggle); break; }
					case Mapping_Target: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->Target[0], btn->Target[1], btn->Target[2], btn->Target[3], btn->Target[4], 0, 0, 0)); break; }
					case Mapping_dsID:
					{
						if (btn->Target[0] == 1)
							head += swprintf_s(head, MAX_PATH, L"%s,", dsIDToString(max(0, btn->srceID[0] - SourceButton::Sisaxis_None), max(0, btn->srceID[1] - SourceButton::Sisaxis_None), max(0, btn->srceID[2] - SourceButton::Sisaxis_None), max(0, btn->srceID[3] - SourceButton::Sisaxis_None), max(0, btn->srceID[4] - SourceButton::Sisaxis_None)));
						else if (btn->Target[0] == 2)
							head += swprintf_s(head, MAX_PATH, L"%s,", dsIDToString(max(0, btn->srceID[0] - SourceButton::Keyboard_None), max(0, btn->srceID[1] - SourceButton::Keyboard_None), max(0, btn->srceID[2] - SourceButton::Keyboard_None), max(0, btn->srceID[3] - SourceButton::Keyboard_None), max(0, btn->srceID[4] - SourceButton::Keyboard_None)));
						else
							head += swprintf_s(head, MAX_PATH, L"%s,", dsIDToString(btn->srceID[0], btn->srceID[1], btn->srceID[2], btn->srceID[3], btn->srceID[4]));
						break;
					}
					case Mapping_OrXorNot: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->OrXorNot[0], btn->OrXorNot[1], btn->OrXorNot[2], btn->OrXorNot[3], 0, 0, 0, 0)); break; }
					case Mapping_dsDisable: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->srceDisable[0], btn->srceDisable[1], btn->srceDisable[2], btn->srceDisable[3], btn->srceDisable[4], 0, 0, 0)); break; }
					case Mapping_ActionType: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->ActionType[0], btn->ActionType[1], btn->ActionType[2], btn->ActionType[3], btn->ActionType[4], btn->ActionType[5], btn->ActionType[6], btn->ActionType[7], true)); break; }
					case Mapping_Overcontrol: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->Overcontrol[0], btn->Overcontrol[1], btn->Overcontrol[2], btn->Overcontrol[3], btn->Overcontrol[4], btn->Overcontrol[5], btn->Overcontrol[6], btn->Overcontrol[7])); break; }
					case Mapping_Switch: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->Switch[0], btn->Switch[1], btn->Switch[2], btn->Switch[3], btn->Switch[4], btn->Switch[5], btn->Switch[6], btn->Switch[7])); break; }
					case Mapping_vjID: { head += swprintf_s(head, MAX_PATH, L"%s,", vjIDToString(btn->destID[0], btn->destID[1], btn->destID[2], btn->destID[3], btn->destID[4], btn->destID[5], btn->destID[6], btn->destID[7])); break; }
					case Mapping_OnRelease: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->OnRelease[0], btn->OnRelease[1], btn->OnRelease[2], btn->OnRelease[3], btn->OnRelease[4], btn->OnRelease[5], btn->OnRelease[6], btn->OnRelease[7])); break; }
					case Mapping_NoRelease: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->NoRelease[0], btn->NoRelease[1], btn->NoRelease[2], btn->NoRelease[3], btn->NoRelease[4], btn->NoRelease[5], btn->NoRelease[6], btn->NoRelease[7])); break; }
					case Mapping_NlRelease: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->NlRelease[0], btn->NlRelease[1], btn->NlRelease[2], btn->NlRelease[3], btn->NlRelease[4], btn->NlRelease[5], btn->NlRelease[6], btn->NlRelease[7])); break; }
					case Mapping_vjDisable: { head += swprintf_s(head, MAX_PATH, L"%s,", CheckboxToString(btn->destDisable[0], btn->destDisable[1], btn->destDisable[2], btn->destDisable[3], btn->destDisable[4], btn->destDisable[5], btn->destDisable[6], btn->destDisable[7])); break; }
					case Mapping_Mouse: { head += swprintf_s(head, MAX_PATH, L"%s,", MouseToString(btn->Mouse[0], btn->Mouse[1], btn->Mouse[2], btn->Mouse[3], btn->Mouse[4], btn->Mouse[5], btn->Mouse[6])); break; }
					case Mapping_Grid: { head += swprintf_s(head, MAX_PATH, L"%s,", GridToString(btn->Grid[0], btn->Grid[1], btn->Grid[2], btn->Grid[3], btn->Grid[4], btn->Grid[5])); break; }
					case Mapping_Start1: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Start[0]); break; }
					case Mapping_Start2: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Start[1]); break; }
					case Mapping_Start3: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Start[2]); break; }
					case Mapping_Start4: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Start[3]); break; }
					case Mapping_Start5: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Start[4]); break; }
					case Mapping_Start6: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Start[5]); break; }
					case Mapping_Start7: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Start[6]); break; }
					case Mapping_Start8: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Start[7]); break; }
					case Mapping_Stop1: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Stop[0]); break; }
					case Mapping_Stop2: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Stop[1]); break; }
					case Mapping_Stop3: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Stop[2]); break; }
					case Mapping_Stop4: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Stop[3]); break; }
					case Mapping_Stop5: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Stop[4]); break; }
					case Mapping_Stop6: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Stop[5]); break; }
					case Mapping_Stop7: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Stop[6]); break; }
					case Mapping_Stop8: { head += swprintf_s(head, MAX_PATH, L"%lld,", btn->Stop[7]); break; }
					case Mapping_Notice: { head += swprintf_s(head, MAX_PATH, L"%s,", btn->Notice); break; }
					}
				head++;
			}
			WritePrivateProfileSection(Mappingtxt, buf, (isExport) ? m_file2 : m_file);
			delete[] buf;
		}
		if (category != Setting_All)
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
				int mapdata[RapidFireName::RapidFireName_Count] = { 0 };
				RapidFire* rf = &RapidFiredata[i];
				mapdata[RapidFireName::RapidFire_Enable] = rf->Enable;
				mapdata[RapidFireName::RapidFire_Button] = rf->ButtonID;
				mapdata[RapidFireName::RapidFire_Button2] = rf->ButtonID2;
				mapdata[RapidFireName::RapidFire_FirstTime] = rf->Firsttime;
				mapdata[RapidFireName::RapidFire_Release] = rf->Releasetime;
				mapdata[RapidFireName::RapidFire_PressTime] = rf->Presstime;

				head += swprintf_s(head, 1024, L"%d=", i + 1);
				for (int j = 0; j < RapidFireName::RapidFireName_Count; j++)
					head += swprintf_s(head, 1024, L"%d,", mapdata[j]);
				head++;
			}
			WritePrivateProfileSection(RapidFiretxt, buf, (isExport) ? m_file2 : m_file);
			delete[] buf;
		}
		if (category != Setting_All)
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
			WritePrivateProfileSection(Keymaptxt, buf, (isExport) ? m_file2 : m_file);
			delete[] buf;
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_XOutputActive:
	{
		WritePrivateProfileString(XOutputtxt, TEXT("XOutputActive"), (XOutputActive) ? L"1" : L"0", (isExport) ? m_file2 : m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_vJoyActive:
	{
		WritePrivateProfileString(XOutputtxt, TEXT("vJoyActive"), (vJoyActive) ? L"1" : L"0", (isExport) ? m_file2 : m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_DesiredVirtualPad:
	{
		swprintf_s(buffer, MAX_PATH, L"%d", DesiredVirtualPad);
		WritePrivateProfileString(XOutputtxt, TEXT("DesiredVirtualPad"), buffer, (isExport) ? m_file2 : m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_target_DS4:
	{
		const int n = 128* 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavexoutput)
			MessageBoxPos(Ds2hWnd, L"XOutput DS4\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			for (int i = 0; i < 24; i++)
				head += swprintf_s(head, 1024, L"%d,", target_DS4[i]);
			WritePrivateProfileString(XOutputtxt, TEXT("DS4"), buf, (isExport) ? m_file2 : m_file);
			delete[] buf;
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_target_X360:
	{
		const int n = 128 * 1024;
		WCHAR* buf = new WCHAR[n];
		if (buf == 0 || !cansavexoutput)
			MessageBoxPos(Ds2hWnd, L"XOutput X360\nwas not saved.", L"Warning", MB_OK, 0, 0, 180);
		else
		{
			memset(buf, 0, n * sizeof(WCHAR));
			WCHAR* head = buf;
			for (int i = 0; i < 24; i++)
				head += swprintf_s(head, 1024, L"%d,", target_X360[i]);
			WritePrivateProfileString(XOutputtxt, TEXT("X360"), buf, (isExport) ? m_file2 : m_file);
			delete[] buf;
		}
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_GuardianActive:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("GuardianActive"), (GuardianActive) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID1Enable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("dsHID1Enable"), (dsHID1Enable) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID2Enable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("dsHID2Enable"), (dsHID2Enable) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_dsHID3Enable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("dsHID3Enable"), (dsHID3Enable) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe1NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe1NameEnable"), (Exe1NameEnable) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe2NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe2NameEnable"), (Exe2NameEnable) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe3NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe3NameEnable"), (Exe3NameEnable) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe4NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe4NameEnable"), (Exe4NameEnable) ? L"1" : L"0", m_file);
		if (category != Setting_All)
			break;
		[[fallthrough]];
	}
	case Setting_Exe5NameEnable:
	{
		WritePrivateProfileString(Guardiantxt, TEXT("Exe5NameEnable"), (Exe5NameEnable) ? L"1" : L"0", m_file);
		if (category != Setting_All)
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
		
		head += swprintf_s(head, MAX_PATH, L"1=1,0,0,0,0,0,0,0,0,0,0,0,0000,0100000000,0000,0000,000000,0100000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"2=1,0,0,0,0,0,0,0,0,0,0,0,0000,0200000000,0000,0000,000000,0200000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"3=0,0,0,0,0,0,0,0,0,0,0,0,0000,1B00000000,0000,0000,000000,0200000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"4=1,0,0,0,0,0,0,0,0,0,0,0,0000,0300000000,0000,0000,000000,0300000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"5=1,0,0,0,0,0,0,0,0,0,0,0,0000,0400000000,0000,0000,000000,0600000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"6=0,0,0,0,0,0,0,0,0,0,0,0,0000,1D00000000,0000,0000,000000,0600000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"7=1,1,0,0,0,0,0,0,0,0,0,0,0000,0500000000,0000,0000,000000,5100000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"8=1,1,0,0,0,0,0,0,0,0,0,0,0000,0600000000,0000,0000,000000,5200000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"9=1,1,0,0,0,0,0,0,0,0,0,0,0000,0700000000,0000,0000,000000,5300000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"10=1,1,0,0,0,0,0,0,0,0,0,0,0000,0800000000,0000,0000,000000,5400000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"11=1,1,0,0,0,0,0,0,0,0,0,0,0000,0900000000,0000,0000,000000,5500000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"12=1,1,0,0,0,0,0,0,0,0,0,0,0000,0C00000000,0000,0000,000000,5800000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"13=1,1,0,0,0,0,0,0,0,0,0,0,0000,0D00000000,0000,0000,000000,5900000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"14=1,1,0,0,0,0,0,0,0,0,0,0,0000,0E00000000,0000,0000,000000,5A00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"15=1,1,0,0,0,0,0,0,0,0,0,0,0000,0F00000000,0000,0000,000000,5B00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"16=1,1,0,0,0,0,0,0,0,0,0,0,0000,1000000000,0000,0000,000000,5C00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"17=1,2,0,0,0,0,0,0,0,0,0,0,0000,0A00000000,0000,0000,000000,5600000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"18=1,2,0,0,0,0,0,0,0,0,0,0,0000,0B00000000,0000,0000,000000,5700000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"19=1,2,0,0,0,0,0,0,0,0,0,0,0000,1100000000,0000,0000,000000,5D00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"20=1,2,0,0,0,0,0,0,0,0,0,0,0000,1200000000,0000,0000,000000,5E00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"21=1,2,0,0,0,0,0,0,0,0,0,0,0000,1300000000,0000,0000,000000,5F00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"22=1,3,0,0,0,0,0,0,0,0,0,0,0000,1400000000,0000,0000,000000,6000000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"23=1,3,0,0,0,0,0,0,0,0,0,0,0000,1500000000,0000,0000,000000,6100000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"24=1,3,0,0,0,0,0,0,0,0,0,0,0000,1600000000,0000,0000,000000,6200000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"25=1,3,0,0,0,0,0,0,0,0,0,0,0000,1700000000,0000,0000,000000,6300000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"26=1,3,0,0,0,0,0,0,0,0,0,0,0000,1800000000,0000,0000,000000,0C00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;
		head += swprintf_s(head, MAX_PATH, L"27=1,3,0,0,0,0,0,0,0,0,0,0,0000,1900000000,0000,0000,000000,0D00000000000000,0000,0000,0000,0000,0000,0000,0000,000000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,,"); head++;

		WritePrivateProfileSection(Mappingtxt, buf, m_file);
		delete[] buf;
		break;
	}
	}
}

bool Settings::Import()
{
	OPENFILENAME ofn;
	WCHAR fileTitle[MAX_PATH + 1] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Ds2hWnd;
	ofn.hInstance = Ds2hInst;
	ofn.lpstrFilter = L"Ds2vJoy(.ds2)\0*.ds2\0";
	//ofn.lpstrCustomFilter = NULL;
	//ofn.nMaxCustFilter = NULL;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = m_file2;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(m_file2);
	ofn.lpstrFileTitle = fileTitle;
	ofn.lpstrFileTitle[0] = '\0';
	ofn.nMaxFileTitle = sizeof(fileTitle);
	ofn.lpstrInitialDir = WCHARI(ExePath());
	//ofn.lpstrTitle = NULL;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = L"ds2";
	//ofn.FlagsEx = OFN_EX_NOPLACESBAR;

	if (GetOpenFileNameW(&ofn))
	{
		int VersionDateCheck = max(0, GetPrivateProfileInt(TEXT("Profile"), TEXT("VersionDate"), 0, m_file2));
		if (VersionDateCheck < 2022)
			return false;

		Mappingdata.clear();
		Keymapdata.clear();
		RapidFiredata.clear();

		Load(Setting_Mappingdata, true);
		Load(Setting_RapidFiredata, true);
		Load(Setting_Keymapdata, true);
		Load(Setting_XOutputActive, true);
		Load(Setting_vJoyActive, true);
		Load(Setting_DesiredVirtualPad, true);
		Load(Setting_target_DS4, true);
		Load(Setting_target_X360, true);

		Save(Setting_Mappingdata);
		Save(Setting_RapidFiredata);
		Save(Setting_Keymapdata);
		Save(Setting_XOutputActive);
		Save(Setting_vJoyActive);
		Save(Setting_DesiredVirtualPad);
		Save(Setting_target_DS4);
		Save(Setting_target_X360);

		echo(I18N.TaskTray_Imported, tape.Profile, fileTitle);
		return true;
	}
	else
		return false;
}

bool Settings::Export()
{
	OPENFILENAME ofn;
	WCHAR fileTitle[MAX_PATH + 1] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Ds2hWnd;
	ofn.hInstance = Ds2hInst;
	ofn.lpstrFilter = L"Ds2vJoy(.ds2)\0*.ds2\0";
	//ofn.lpstrCustomFilter = NULL;
	//ofn.nMaxCustFilter = NULL;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = m_file2;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(m_file2);
	ofn.lpstrFileTitle = fileTitle;
	ofn.lpstrFileTitle[0] = '\0';
	ofn.nMaxFileTitle = sizeof(fileTitle);
	ofn.lpstrInitialDir = WCHARI(ExePath());
	//ofn.lpstrTitle = NULL;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_PATHMUSTEXIST;
	ofn.lpstrDefExt = L"ds2";
	//ofn.FlagsEx = OFN_EX_NOPLACESBAR;

	if (GetSaveFileNameW(&ofn))
	{
		Save(Setting_Version, true);
		Save(Setting_Mappingdata, true);
		Save(Setting_RapidFiredata, true);
		Save(Setting_Keymapdata, true);
		Save(Setting_XOutputActive, true);
		Save(Setting_vJoyActive, true);
		Save(Setting_DesiredVirtualPad, true);
		Save(Setting_target_DS4, true);
		Save(Setting_target_X360, true);

		echo(I18N.TaskTray_Exported, tape.Profile, fileTitle);
		return true;
	}
	else
		return false;
}


void Settings::setCountry(int land)
{
	if (land >= 0 && land < Country_Count)
		Country = land;
	else
		Country = 0;
}

void Settings::setvJoyDevice(int id)
{
	if (id >= 0 && id < 16)
		vJoyDevice = id;
	else
		vJoyDevice = 0;
}

void Settings::setXInputDevice(int id)
{
	if (id >= 0 && id < 4)
		XInputDevice = id;
	else
		XInputDevice = 0;
}

void Settings::setSerial(const WCHAR* buf)
{
	wcscpy_s(Serial, wcslen(buf) + 1, buf);
}

void Settings::setDevice(const WCHAR* buf, unsigned char device)
{
	if (device)
		wcscpy_s(Device2, wcslen(buf) + 1, buf);
	else
		wcscpy_s(Device1, wcslen(buf) + 1, buf);
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

void Settings::setLED(unsigned int i)
{
	if (i >= 0 && i <= 0xFFFFFF)
		LED_Color = i;
}

void Settings::setPID(const WCHAR* buf, int ds)
{
	switch (ds)
	{
	case 1: { wcscpy_s(dsHID[0], wcslen(buf) + 1, buf);break; }
	case 2: { wcscpy_s(dsHID[1], wcslen(buf) + 1, buf);break; }
	case 3: { wcscpy_s(dsHID[2], wcslen(buf) + 1, buf);break; }
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
	case 0: { wcscpy_s(App0Name, wcslen(buf) + 1, buf);break; }
	case 1: { wcscpy_s(App1Name, wcslen(buf) + 1, buf);break; }
	case 2: { wcscpy_s(App2Name, wcslen(buf) + 1, buf);break; }
	case 3: { wcscpy_s(App3Name, wcslen(buf) + 1, buf);break; }
	case 4: { wcscpy_s(App4Name, wcslen(buf) + 1, buf);break; }
	}
}

void Settings::setAppLocation(const WCHAR* buf, int app)
{
	switch (app)
	{
	case 0: { wcscpy_s(App0Location, wcslen(buf) + 1, buf);break; }
	case 1: { wcscpy_s(App1Location, wcslen(buf) + 1, buf);break; }
	case 2: { wcscpy_s(App2Location, wcslen(buf) + 1, buf);break; }
	case 3: { wcscpy_s(App3Location, wcslen(buf) + 1, buf);break; }
	case 4: { wcscpy_s(App4Location, wcslen(buf) + 1, buf);break; }
	case 5: { wcscpy_s(App5Location, wcslen(buf) + 1, buf);break; }
	case 6: { wcscpy_s(App6Location, wcslen(buf) + 1, buf);break; }
	case 7: { wcscpy_s(App7Location, wcslen(buf) + 1, buf);break; }
	case 8: { wcscpy_s(App8Location, wcslen(buf) + 1, buf);break; }
	case 9: { wcscpy_s(App9Location, wcslen(buf) + 1, buf);break; }
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

void Settings::setPreferredSource(int i)
{
	if (i >= 0 && i < 5)
		PreferredSource = (unsigned char)i;
	else
		PreferredSource = 0;
}

void Settings::setMouseActive(int i)
{
	if (i >= 0 && i < 3)
		MouseActive = (unsigned char)i;
	else
		MouseActive = 0;
}

void Settings::setTriggersMode(int i)
{
	if (i >= 0 && i < 4)
		TriggersMode = i;
	else
		TriggersMode = 0;
}

void Settings::setThreshold(int i)
{
	if (i >= 0 && i <= 32767)
		Threshold = i;
	else
		Threshold = 2056;
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

void Settings::setWebRefreshTime(int i)
{
	if (i > 0 && i < 10000)
		WebRefreshTime = i;
	else
		WebRefreshTime = 20;
}

void Settings::setSplitTouch()
{
	if (TouchPadButton && TouchPadButton <= 128)
		SplitTouch = true;
	else
		SplitTouch = false;
}

void Settings::setWaveSpeed(int i)
{
	if (i >= 0 && i < 167)
		WaveSpeed = i;
	else
		WaveSpeed = 130;
}

void Settings::setDispatch(int i, int value, unsigned char layout)
{
	if (i >= SrceDispatchID::Dispatch_LX && i <= SrceDispatchID::Dispatch_SL1)
	{
		if (value >= SrceDIAxisID::DIAxisID_none && value < SrceDIAxisID::DIAxisID_Count)
		{
			switch (layout)
			{
			case 0: { diDispatch[i] = value; break; }
			case 1: { diDispatch1[i] = value; break; }
			case 2: { diDispatch2[i] = value; break; }
			case 3: { diDispatch3[i] = value; break; }
			}
		}
		else
		{
			switch (layout)
			{
			case 0: { diDispatch[i] = SrceDIAxisID::DIAxisID_none; break; }
			case 1: { diDispatch1[i] = SrceDIAxisID::DIAxisID_none; break; }
			case 2: { diDispatch2[i] = SrceDIAxisID::DIAxisID_none; break; }
			case 3: { diDispatch3[i] = SrceDIAxisID::DIAxisID_none; break; }
			}
		}
	}
	else if (i >= SrceDispatchID::Dispatch_DPAD && i <= SrceDispatchID::Dispatch_DPAD4)
	{
		if (value >= SrceDIPOVID::DIPOVID_none && value < SrceDIPOVID::DIPOVID_Count)
		{
			switch (layout)
			{
			case 0: { diDispatch[i] = value; break; }
			case 1: { diDispatch1[i] = value; break; }
			case 2: { diDispatch2[i] = value; break; }
			case 3: { diDispatch3[i] = value; break; }
			}
		}
		else
		{
			switch (layout)
			{
			case 0: { diDispatch[i] = SrceDIPOVID::DIPOVID_none; break; }
			case 1: { diDispatch1[i] = SrceDIPOVID::DIPOVID_none; break; }
			case 2: { diDispatch2[i] = SrceDIPOVID::DIPOVID_none; break; }
			case 3: { diDispatch3[i] = SrceDIPOVID::DIPOVID_none; break; }
			}
		}
	}
	else if (i >= SrceDispatchID::Dispatch_SQUARE && i <= SrceDispatchID::Dispatch_BUTTON32)
	{
		if (value >= SrceDIButtonID::DIButtonID_none && value < SrceDIButtonID::DIButtonID_Count)
		{
			switch (layout)
			{
			case 0: { diDispatch[i] = value; break; }
			case 1: { diDispatch1[i] = value; break; }
			case 2: { diDispatch2[i] = value; break; }
			case 3: { diDispatch3[i] = value; break; }
			}
		}
		else
		{
			switch (layout)
			{
			case 0: { diDispatch[i] = SrceDIButtonID::DIButtonID_none; break; }
			case 1: { diDispatch1[i] = SrceDIButtonID::DIButtonID_none; break; }
			case 2: { diDispatch2[i] = SrceDIButtonID::DIButtonID_none; break; }
			case 3: { diDispatch3[i] = SrceDIButtonID::DIButtonID_none; break; }
			}
		}
	}
}

void Settings::setTabMapping(int i)
{
	if (i >= 0 && i < 9)
		TabMapping = i;
	else
		TabMapping = 0;
}

void Settings::setTabMode(int i, int mode)
{
	if (mode >= 0 && mode < 9)
		Mode[i] = (unsigned char)mode;
	else
		Mode[i] = 0;
}

void Settings::setStats(int i, int stat)
{
	if (stat >= 0 && stat < 65536)
		Stat[i] = stat;
	else
		Stat[i] = 0;
}

void Settings::setReminder(int i, int reminder)
{
	if (reminder >= 0 && reminder < 2)
		Reminder[i] = reminder;
	else
		Reminder[i] = 0;
}

void Settings::setDesiredVirtualPad(int i)
{
	if (i > 0 && i < 3)
		DesiredVirtualPad = i;
	else
		DesiredVirtualPad = 1;
}

void Settings::setDefaultZoomValue(int i)
{
	DefaultZoomValue = float(max(250, min(5000, i))) / 1000;
}

void Settings::setDarkMode(int i)
{
	DarkMode = max(0, min(3, i));
}

WCHAR* Settings::CheckboxToString(byte v1, byte v2, byte v3, byte v4, byte v5, byte v6, byte v7, byte v8, bool eightOverFour)
{
	int packit = 0;
	int packit2 = 0;

	if (eightOverFour)
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

	if (eightOverFour)
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
		return I18N.EMPTY;

	static WCHAR buf[1024];
	buf[0] = 0;
	WCHAR* head = buf;

	for (auto itr = vk.begin(); itr != vk.end(); ++itr)
	{
		head += swprintf_s(head, 1024, L"%02hX", *itr);
	}

	return buf;
}

unsigned short Settings::CheckboxString(std::wstring checkboxesstring, unsigned char idx, bool eightOverFour)
{
	if (checkboxesstring == L"")
		return 0;
	if (checkboxesstring.length() < 4 || (eightOverFour && checkboxesstring.length() < 6))
		return 0;

	int pakitstoi = std::stoi(checkboxesstring, nullptr, 16);

	if (eightOverFour)
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


const WCHAR* Settings::CountryString(CountryID land)
{
	switch (land)
	{
	case Country_UNITED_STATES: return L"US";
	case Country_ALBANIA: return L"AL";
	case Country_ARMENIA: return L"AM";
	case Country_AZERBAIJAN: return L"AZ";
	case Country_BOSNIA: return L"BA";
	case Country_BULGARIA: return L"BG";
	case Country_BRAZIL: return L"BR";
	case Country_BELARUSIAN: return L"BY";
	case Country_CANADA: return L"CA";
	case Country_CHEROKEE: return L"CH";
	case Country_CHINA_SIMPLIFIED: return L"CN";
	case Country_SERBIA_LATIN: return L"CS";
	case Country_CZECH_REPUBLIC: return L"CZ";
	case Country_GERMANY: return L"DE";
	case Country_DENMARK: return L"DK";
	case Country_ESTONIA: return L"EE";
	case Country_SPAIN: return L"ES";
	case Country_ETHIOPIA: return L"ET";
	case Country_FINLAND: return L"FI";
	case Country_FRANCE: return L"FR";
	case Country_GREAT_BRITAIN: return L"GB";
	case Country_GEORGIA: return L"GE";
	case Country_GREECE: return L"GR";
	case Country_HONG_KONG: return L"HK";
	case Country_CROATIA: return L"HR";
	case Country_HUNGARY: return L"HU";
	case Country_INDONESIA: return L"ID";
	case Country_IRELAND: return L"IE";
	case Country_ISRAEL: return L"IL";
	case Country_INDIA: return L"IN";
	case Country_PERSIAN: return L"IR";
	case Country_ICELAND: return L"IS";
	case Country_ITALY: return L"IT";
	case Country_JAPAN: return L"JP";
	case Country_CAMBODIA: return L"KH";
	case Country_KOREA: return L"KR";
	case Country_KAZAKHSTAN: return L"KZ";
	case Country_LAOS: return L"LA";
	case Country_LITHUANIA: return L"LT";
	case Country_LUXEMBOURG: return L"LU";
	case Country_LATVIA: return L"LV";
	case Country_MACEDONIA: return L"MK";
	case Country_MALTA: return L"MT";
	case Country_MEXICO: return L"MX";
	case Country_MALAYSIA_BRUNEI_SINGAPORE: return L"MY";
	case Country_NETHERLANDS: return L"NL";
	case Country_NORWAY: return L"NO";
	case Country_NEPAL: return L"NP";
	case Country_NEW_ZEALAND: return L"NZ";
	case Country_PERU: return L"PE";
	case Country_FILIPINO: return L"PH";
	case Country_URDU: return L"PK";
	case Country_POLAND: return L"PL";
	case Country_PORTUGAL: return L"PT";
	case Country_ROMANIA: return L"RO";
	case Country_SERBIAN_CYRILLIC: return L"RS";
	case Country_RUSSIA: return L"RU";
	case Country_SAUDI_ARABIA: return L"SA";
	case Country_SWEDEN: return L"SE";
	case Country_SLOVENIA: return L"SI";
	case Country_SLOVAKIA: return L"SK";
	case Country_THAILAND: return L"TH";
	case Country_TURKEY: return L"TR";
	case Country_TAIWAN: return L"TW";
	case Country_UKRAINE: return L"UA";
	case Country_UZBEKISTAN: return L"UZ";
	case Country_VIETNAMESE: return L"VN";
	case Country_SOUTH_AFRICA: return L"ZA";
	default: return I18N.WHICH;
	}
}
