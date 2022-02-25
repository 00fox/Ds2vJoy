#pragma once
#include "Keymap.h"
#include "Mapping.h"
#include "RapidFire.h"

class Settings
{
public:
	const int			VersionDate = 202202241;
	const std::wstring	ProgramFilesDirName = L"Ds2vJoy";
	bool				BreakAndExit = false;

	WCHAR				Settingstxt[20];
	WCHAR				Mappingtxt[20];
	WCHAR				ViGEmtxt[20];
	WCHAR				Keymaptxt[20];
	WCHAR				RapidFiretxt[20];
	WCHAR				Guardiantxt[20];
	WCHAR				Webtxt[20];

	enum SettingCategory {
		Setting_Category_Create = -2,
		Setting_Category_Update = -1,
		Setting_Category_All,
		Setting_Category_Profile,
		Setting_Category_Tray,
		Setting_Category_Settings,
		Setting_Category_Mapping,
		Setting_Category_RapidFire,
		Setting_Category_Keymap,
		Setting_Category_ViGEm,
		Setting_Category_Guardian,
		Setting_Category_Web,
		Setting_Category_WebScript,
		Setting_Category_Links,
		Setting_Category_Notepad
	};

	enum SettingName {
		Setting_Update = -1,
		Setting_All,				//All
		Setting_Version,
		Setting_Profile,			//Profile
		Setting_Transparency,
		Setting_TopMost,
		Setting_Tasktray,
		Setting_CloseMinimize,
		Setting_DisconnectBT,
		Setting_LowBattAlert,
		Setting_dsSerial,
		Setting_BlackLedOnExit,
		Setting_MappingViewMode,
		Setting_CloneViewMode,
		Setting_NotepadFont,
		Setting_vJoyPaused,			//Tasktray
		Setting_RapidFirePaused,
		Setting_KeymapPaused,
		Setting_ViGEmPaused,
		Setting_GuardianPaused,
		Setting_dsHID1,				//Guardian
		Setting_dsHID2,
		Setting_dsHID3,
		Setting_Exe1Name,
		Setting_Exe2Name,
		Setting_Exe3Name,
		Setting_Exe4Name,
		Setting_Exe5Name,
		Setting_WebRefreshTime,		//Web
		Setting_DefaultZoomValue,
		Setting_DarkMode,
		Setting_RawBounds,
		Setting_WebLanguage,
		Setting_UserAgent,
		Setting_BlockedSites,
		Setting_WebURL0,
		Setting_WebURL1,
		Setting_WebURL2,
		Setting_WebURL3,
		Setting_WebURL4,
		Setting_WebURL5,
		Setting_WebURL6,
		Setting_WebURL7,
		Setting_WebURL8,
		Setting_WebURL9,
		Setting_InitialScript,		//WebScript
		Setting_App1Name,			//Links
		Setting_App2Name,
		Setting_App3Name,
		Setting_App4Name,
		Setting_App5Name,
		Setting_App1Location,
		Setting_App2Location,
		Setting_App3Location,
		Setting_App4Location,
		Setting_App5Location,
		Setting_Notepad,			//Notepad
		Setting_PreferredDS,		//Settings	//Start of Profile dependant
		Setting_MouseActive,
		Setting_KeyboardActive,
		Setting_vJoyDeviceID,
		Setting_Threshold,
		Setting_Simultaneous,
		Setting_LongPress,
		Setting_VeryLongPress,
		Setting_MouseCanBypass,
		Setting_TriggersMode,
		Setting_DarkTheme,
		Setting_TouchPadButton,
		Setting_TouchCol,
		Setting_TouchRow,
		Setting_LED_Color,
		Setting_Wave_Speed,
		Setting_TabMapping,
		Setting_TabToMode,
		Setting_Reminder,
		Setting_Stats,
		Setting_Mappingdata,		//Mapping
		Setting_RapidFiredata,		//RapidFire
		Setting_Keymapdata,			//Keymap
		Setting_ViGEmActive,		//ViGEm
		Setting_DesiredVirtualPad,
		Setting_target_X360,
		Setting_dstarget_X360,
		Setting_vjtarget_X360,
		Setting_target_DS4,
		Setting_dstarget_DS4,
		Setting_vjtarget_DS4,
		Setting_GuardianActive,		//Guardian
		Setting_RemoveBlacklist,
		Setting_PurgeWhitelist,
		Setting_dsHID1Enable,
		Setting_dsHID2Enable,
		Setting_dsHID3Enable,
		Setting_Exe1NameEnable,
		Setting_Exe2NameEnable,
		Setting_Exe3NameEnable,
		Setting_Exe4NameEnable,
		Setting_Exe5NameEnable,
		Setting_GiveMapping			//First time
	};

	Settings();
	~Settings();

	void				Init(HINSTANCE hInst, HWND hWnd);
	BOOL				OpenIni(WCHAR* inifile);
	void				Load(int category = Setting_Category_All);
	void				Save(int item = Setting_All);

	const WCHAR*		getSerial();
	const std::wstring	getHID(int ds);
	void				setvJoyDeviceID(int id);
	void				setTouchPadButton(byte);
	void				setTouchRow(int);
	void				setTouchCol(int i);
	void				setSerial(const WCHAR*);
	void				setLED(unsigned long i);
	void				setPID(const WCHAR* buf, int ds);
	void				setExeName(const WCHAR* buf, int exe);
	void				setWebURL(const WCHAR* url, int lnk);
	void				setAppName(const WCHAR*, int app);
	void				setAppLocation(const WCHAR*, int app);

	HWND				Ds2hWnd;
	HINSTANCE			Ds2hInst;

	POINT				mousepoint;
	short				W;
	short				H;
	short				w;
	short				h;
	long				proportianality;
	bool				Transparency;
	bool				TopMost;

	HBRUSH				hB_BackGround =				CreateSolidBrush(RGB(210, 210, 215));
	HBRUSH				hB_CLONE_BackGround =		CreateSolidBrush(RGB(240, 240, 240));
	HBRUSH				hB_DLG =					CreateSolidBrush(RGB(191, 200, 196));
	HBRUSH				hB_MSGBOX =					CreateSolidBrush(RGB(191, 200, 196));
	HBRUSH				hB_SCROLLBAR =				CreateSolidBrush(RGB(191, 200, 196));
	HBRUSH				hB_BTN =					CreateSolidBrush(RGB(210, 210, 215));
	HBRUSH				hB_BTN_Border =				CreateSolidBrush(RGB(195, 195, 200));
	HBRUSH				hB_Not_Installed =			CreateSolidBrush(RGB(160, 160, 160));
	HBRUSH				hB_Running =				CreateSolidBrush(RGB(240, 240, 0));
	HBRUSH				hB_Stopped =				CreateSolidBrush(RGB(255, 140, 0));
	HBRUSH				hB_Paused =					CreateSolidBrush(RGB(96, 192, 96));
	HBRUSH				hB_STATIC =					CreateSolidBrush(RGB(210, 210, 215));
	HBRUSH				hB_STATIC_Mouse1 =			CreateSolidBrush(RGB(180, 180, 0));
	HBRUSH				hB_STATIC_Mouse2 =			CreateSolidBrush(RGB(180, 0, 180));
	HBRUSH				hB_POSTIT =					CreateSolidBrush(RGB(175, 175, 175));
	HBRUSH				hB_POSTIT_Rand0 =			CreateSolidBrush(RGB(210, 210, 255));
	HBRUSH				hB_POSTIT_Rand1 =			CreateSolidBrush(RGB(210, 225, 0));
	HBRUSH				hB_POSTIT_Rand2 =			CreateSolidBrush(RGB(240, 240, 0));
	HBRUSH				hB_POSTIT_Rand3 =			CreateSolidBrush(RGB(225, 115, 210));
	HBRUSH				hB_EDIT =					CreateSolidBrush(RGB(228, 228, 232));
	HBRUSH				hB_LIST =					CreateSolidBrush(RGB(210, 210, 215));
	HBRUSH				hB_LIST_HIGHLIGHT =			CreateSolidBrush(RGB(0, 120, 215));
	HBRUSH				hB_LIST_Disable1 =			CreateSolidBrush(RGB(169, 186, 225));
	HBRUSH				hB_LIST_Disable2 =			CreateSolidBrush(RGB(211, 178, 221));
	HBRUSH				hB_LIST_Disabled =			CreateSolidBrush(RGB(190, 190, 195));
	HBRUSH				hB_MENU =					CreateSolidBrush(RGB(205, 205, 210));
	HBRUSH				hB_MENU_CLONE =				CreateSolidBrush(RGB(200, 200, 205));
	HBRUSH				hB_MENU_SELECTED =			CreateSolidBrush(RGB(153, 160, 157));
	HBRUSH				hB_MENU_HIGHLIGHT =			CreateSolidBrush(RGB(0, 120, 215));

	HBRUSH				hB_CHECKBOX_UNCHECKED =		CreateSolidBrush(RGB(225, 225, 230));
	HBRUSH				hB_CHECKBOX_CHECKED =		CreateSolidBrush(RGB(251, 241, 214));
	HBRUSH				hB_CHECKBOX_INDETERMINATE =	CreateSolidBrush(RGB(226, 235, 249));

	HBRUSH				hB_neutral =				CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH				hB_black =					CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH				hB_white =					CreateSolidBrush(RGB(240, 240, 240));

	HBRUSH				hB_grey =					CreateSolidBrush(RGB(205, 205, 210));
	HBRUSH				hB_red =					CreateSolidBrush(RGB(238, 172, 176));
	HBRUSH				hB_orange =					CreateSolidBrush(RGB(255, 188, 152));
	HBRUSH				hB_yellow =					CreateSolidBrush(RGB(229, 191, 142));
	HBRUSH				hB_emerald =				CreateSolidBrush(RGB(198, 195, 186));
	HBRUSH				hB_green =					CreateSolidBrush(RGB(162, 193, 186));
	HBRUSH				hB_blue =					CreateSolidBrush(RGB(161, 198, 247));
	HBRUSH				hB_purple =					CreateSolidBrush(RGB(211, 178, 221));
	
	HBRUSH				hB_bright_grey =			CreateSolidBrush(RGB(234, 234, 240));
	HBRUSH				hB_bright_red =				CreateSolidBrush(RGB(252, 228, 230));
	HBRUSH				hB_bright_orange =			CreateSolidBrush(RGB(250, 237, 209));
	HBRUSH				hB_bright_yellow =			CreateSolidBrush(RGB(251, 241, 214));
	HBRUSH				hB_bright_emerald =			CreateSolidBrush(RGB(227, 255, 171));
	HBRUSH				hB_bright_green =			CreateSolidBrush(RGB(222, 238, 235));
	HBRUSH				hB_bright_blue =			CreateSolidBrush(RGB(226, 235, 249));
	HBRUSH				hB_bright_purple =			CreateSolidBrush(RGB(245, 231, 248));

	HBRUSH				hB_WEB_BackGround =			CreateSolidBrush(RGB(10, 12, 13));

	COLORREF			ink_DLG =					RGB(10, 10, 10);
	COLORREF			ink_MSGBOX =				RGB(10, 10, 10);
	COLORREF			ink_SCROLLBAR =				RGB(10, 10, 10);
	COLORREF			ink_BTN =					RGB(100, 93, 79);
	COLORREF			ink_BTN_Heavy =				RGB(45, 45, 45);
	COLORREF			ink_BTN_Light =				RGB(210, 210, 215);
	COLORREF			ink_BTN_Install =			RGB(10, 10, 10);
	COLORREF			ink_BTN_CLONE =				RGB(100, 93, 79);
	COLORREF			ink_BTN_MAPPING =			RGB(87, 24, 55);
	COLORREF			ink_BTN_MAPPING_OK =		RGB(51, 239, 96);
	COLORREF			ink_BTN_MAPPING_CLEAR =		RGB(0, 227, 248);
	COLORREF			ink_BTN_MAPPING_HELP =		RGB(0, 219, 78);
	COLORREF			ink_STATIC =				RGB(100, 93, 79);
	COLORREF			ink_STATIC_Mouse1 =			RGB(24, 24, 92);
	COLORREF			ink_STATIC_Mouse2 =			RGB(224, 224, 255);
	COLORREF			ink_STATIC_Checkbox =		RGB(10, 10, 10);
	COLORREF			ink_STATIC_Checkbox2 =		RGB(136, 128, 104);
	COLORREF			ink_POSTIT =				RGB(0, 0, 255);
	COLORREF			ink_EDIT =					RGB(10, 10, 10);
	COLORREF			ink_EDIT_TERMINAL =			RGB(172, 196, 226);
	COLORREF			ink_EDIT_TIMELINE =			RGB(87, 24, 55);
	COLORREF			ink_EDIT_NOTEPAD =			RGB(10, 10, 10);
	COLORREF			ink_LIST =					RGB(10, 10, 10);
	COLORREF			ink_LIST_BACK =				RGB(210, 210, 215);
	COLORREF			ink_LIST_BACKGROUND =		RGB(225, 225, 230);
	COLORREF			ink_LIST_Selected =			RGB(0, 120, 215);
	COLORREF			ink_LIST_HIGHLIGHT =		RGB(234, 234, 255);
	COLORREF			ink_LIST_Disabled =			RGB(195, 195, 195);
	COLORREF			ink_LIST_not =				RGB(195, 10, 5);
	COLORREF			ink_LIST_not_HIGHLIGHT =	RGB(255, 160, 165);
	COLORREF			ink_LIST_separator =		RGB(232, 228, 9);
	COLORREF			ink_LIST_separator_HIGH =	RGB(0, 120, 215);
	COLORREF			ink_MENU =					RGB(63, 37, 67);
	COLORREF			ink_MENU_SELECTED =			RGB(255, 255, 225);
	COLORREF			ink_MENU_HIGHLIGHT =		RGB(234, 234, 255);
	COLORREF			ink_MENU_SEPARATOR =		RGB(166, 166, 166);
	COLORREF			ink_MENU_Delete =			RGB(255, 160, 165);
	COLORREF			ink_MENU_SeeView2 =			RGB(254, 254, 255);
	COLORREF			ink_MENU_SeeView2_HIGH =	RGB(163, 154, 21);
	COLORREF			Bk_DLG =					RGB(191, 200, 196);
	COLORREF			Bk_MSGBOX =					RGB(191, 200, 196);
	COLORREF			Bk_SCROLLBAR =				RGB(191, 200, 196);
	COLORREF			Bk_BTN =					RGB(36, 163, 163);
	COLORREF			Bk_STATIC =					RGB(36, 163, 163);
	COLORREF			Bk_STATS =					RGB(240, 240, 240);
	COLORREF			Bk_POSTIT =					RGB(240, 240, 0);
	COLORREF			Bk_NOTEPAD =				RGB(240, 240, 240);
	COLORREF			Bk_TOOLTIP =				RGB(22, 8, 84);
	COLORREF			ink_TOOLTIP =				RGB(240, 228, 241);

	COLORREF			ink_black =					RGB(0, 0, 0);
	COLORREF			ink_neutral =				RGB(128, 128, 128);
	COLORREF			ink_white =					RGB(240, 240, 240);

	COLORREF			ink_grey =					RGB(205, 205, 210);
	COLORREF			ink_red =					RGB(238, 172, 176);
	COLORREF			ink_orange =				RGB(255, 188, 152);
	COLORREF			ink_yellow =				RGB(229, 191, 142);
	COLORREF			ink_emerald =				RGB(198, 195, 186);
	COLORREF			ink_green =					RGB(162, 193, 186);
	COLORREF			ink_blue =					RGB(161, 198, 247);
	COLORREF			ink_purple =				RGB(211, 178, 221);

	COLORREF			ink_bright_grey =			RGB(234, 234, 240);
	COLORREF			ink_bright_red =			RGB(252, 228, 230);
	COLORREF			ink_bright_orange =			RGB(250, 237, 209);
	COLORREF			ink_bright_yellow =			RGB(251, 241, 214);
	COLORREF			ink_bright_emerald =		RGB(227, 255, 171);
	COLORREF			ink_bright_green =			RGB(222, 238, 235);
	COLORREF			ink_bright_blue =			RGB(226, 235, 249);
	COLORREF			ink_bright_purple =			RGB(245, 231, 248);

	HFONT hLog = CreateFont(11, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Lucida Console");
	HFONT hNotepad = CreateFont(15, 7, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Consolas");
	HFONT hStatus = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"MS Shell Dlg");
	HFONT hTab1 = CreateFont(13, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Bahnschrift SemiLight SemiConde");
	HFONT hPostIt = CreateFont(14, 4, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe Print");
	HFONT hLegend = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hLegend2 = CreateFont(12, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hLegend3 = CreateFont(11, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hLegend4 = CreateFont(9, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hEdit = CreateFont(14, 6, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hCheck2 = CreateFont(9, 5, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Lucida Console");
	HFONT hCheck3 = CreateFont(14, 5, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hCombo = CreateFont(14, 4, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hCombo2 = CreateFont(14, 4, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hEdit2 = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Bahnschrift SemiLight SemiConde");
	HFONT hEdit3 = CreateFont(13, 4, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hButton = CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hButton2 = CreateFont(15, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hStatic = CreateFont(14, 6, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hMenus = CreateFont(15, 5, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hLinks = CreateFont(14, 5, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hList = CreateFont(15, 4, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hStats = CreateFont(13, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hTopMost = CreateFont(16, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hAbout = CreateFont(18, 0, 0, 10, FW_REGULAR, TRUE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe Script");
	HFONT hTooltip = CreateFont(15, 7, 0, 30, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Bahnschrift SemiLight SemiConde");
	#define hCancel = hLegend2
	#define hCheck hStatic
	#define hSlider hButton
	#define hTab2 hLinks

	
	unsigned char		Profile;
	
	bool				cansavemappings = true;
	bool				cansaverapidfires = true;
	bool				cansavekeymaps = true;
	bool				cansavevigem = true;
	bool				cansaveblockedsites = true;
	bool				cansavewebscript = true;
	bool				cansavenotepad = true;

	unsigned char		ActualDS = 0;	//0 Unknown
	unsigned char		PreferredDS;	//0 None, 1 DS4, 2 DS5
	bool				MouseActive;
	bool				KeyboardActive;
	unsigned char		vJoyDeviceID;

	bool				Tasktray;
	bool				CloseMinimize;
	bool				DisconnectBT;
	bool				MouseCanBypass;
	bool				LowBattAlert;
	unsigned char		TriggersMode;	//0 None, 1 Resist, 2 Shoot, 3 Proactive
	bool				DarkTheme;

	bool				SplitTouch;
	byte				TouchPadButton;
	unsigned char		TouchCol;
	unsigned char		TouchRow;

	WCHAR				dsSerial[13] = { 0 };
	bool				BlackLedOnExit;
	DWORD				LED_Color;
	byte				WaveSpeed;

	byte				Threshold;		//8 (0-128)
	unsigned short		Simultaneous;	//40 ms
	unsigned short		LongPress;		//255 ms
	unsigned short		VeryLongPress;	//3287 ms
	unsigned short		WebRefreshTime;	//20 s

	bool				vJoyPaused;
	bool				ViGEmPaused;
	bool				KeymapPaused;
	bool				RapidFirePaused;
	bool				GuardianPaused;

	Mappings			Mappingdata;
	Keymaps				Keymapdata;
	RapidFires			RapidFiredata;

	unsigned char		TabMapping;
	bool				MappingViewMode;
	bool				CloneViewMode;
	unsigned char		Mode[9];
	short				Stat[8];
	bool				Reminder[32];
	bool				vJoyUsed[32];

	bool				ViGEmActive;
	unsigned char		DesiredVirtualPad;	//1 Xbox360, 2 DS4
	bool				target_X360[24];
	byte				dstarget_X360[24];
	byte				vjtarget_X360[24];
	bool				target_DS4[24];
	byte				dstarget_DS4[24];
	byte				vjtarget_DS4[24];

	bool				GuardianActive;
	bool				RemoveBlacklist;
	bool				PurgeWhitelist;
	WCHAR				dsHID1[MAX_PATH] = { 0 };
	WCHAR				dsHID2[MAX_PATH] = { 0 };
	WCHAR				dsHID3[MAX_PATH] = { 0 };
	bool				dsHID1Enable;
	bool				dsHID2Enable;
	bool				dsHID3Enable;
	WCHAR				Exe1Name[MAX_PATH] = { 0 };
	WCHAR				Exe2Name[MAX_PATH] = { 0 };
	WCHAR				Exe3Name[MAX_PATH] = { 0 };
	WCHAR				Exe4Name[MAX_PATH] = { 0 };
	WCHAR				Exe5Name[MAX_PATH] = { 0 };
	bool				Exe1NameEnable;
	bool				Exe2NameEnable;
	bool				Exe3NameEnable;
	bool				Exe4NameEnable;
	bool				Exe5NameEnable;

	double				DefaultZoomValue = 0.47;
	bool				RawBounds = false;
	unsigned char		DarkMode = 1;
	std::wstring		WebScript = LR"()";
	std::wstring		WebLanguage = L"";
	std::wstring		UserAgent = L"";
	std::wstring		BlockedSites = L"";
	WCHAR				WebURL[10][MAX_PATH] = { 0 };

	WCHAR				App1Name[MAX_PATH] = { 0 };
	WCHAR				App2Name[MAX_PATH] = { 0 };
	WCHAR				App3Name[MAX_PATH] = { 0 };
	WCHAR				App4Name[MAX_PATH] = { 0 };
	WCHAR				App5Name[MAX_PATH] = { 0 };
	WCHAR				App1Location[MAX_PATH] = { 0 };
	WCHAR				App2Location[MAX_PATH] = { 0 };
	WCHAR				App3Location[MAX_PATH] = { 0 };
	WCHAR				App4Location[MAX_PATH] = { 0 };
	WCHAR				App5Location[MAX_PATH] = { 0 };

	std::wstring		Notepad = L"";
	std::wstring		NotepadFont = L"";
	unsigned short		NotepadFontH = 14;
	unsigned short		NotepadFontW = 0;
	bool				NotepadUnsaved = false;

private:
	enum MappingName {
		Mapping_Enable,
		Mapping_Tab,
		Mapping_Ifmouse,
		Mapping_Force,
		Mapping_Short,
		Mapping_Double,
		Mapping_Long,
		Mapping_Led,
		Mapping_Macro,
		Mapping_Pause,
		Mapping_Transitivity,
		Mapping_Toggle,
		Mapping_Target,				//1-5(2,2,2,2,2,0,0,0)
		Mapping_dsID,
		Mapping_OrXorNot,			//1-4(2,2,2,2,0,0,0,0)
		Mapping_dsDisable,			//1-5(2,2,2,2,2,0,0,0)
		Mapping_MouseAction,		//1-8(2,2,2,2,2,2,2,2)
		Mapping_vjID,
		Mapping_Overcontrol,		//1-8(2,2,2,2,2,2,2,2)
		Mapping_Switch,				//1-8(2,2,2,2,2,2,2,2)
		Mapping_OnRelease,			//1-8(2,2,2,2,2,2,2,2)
		Mapping_NoRelease,			//1-8(2,2,2,2,2,2,2,2)
		Mapping_NlRelease,			//1-8(2,2,2,2,2,2,2,2)
		Mapping_vjDisable,			//1-8(2,2,2,2,2,2,2,2)
		Mapping_Mouse,				//1-7(3,3,3,1,1,1,2)
		Mapping_Grid,				//1-6(16,16,16,16,8,8)
		Mapping_Start1,
		Mapping_Start2,
		Mapping_Start3,
		Mapping_Start4,
		Mapping_Start5,
		Mapping_Start6,
		Mapping_Start7,
		Mapping_Start8,
		Mapping_Stop1,
		Mapping_Stop2,
		Mapping_Stop3,
		Mapping_Stop4,
		Mapping_Stop5,
		Mapping_Stop6,
		Mapping_Stop7,
		Mapping_Stop8,
		Mapping_Notice,
		Mapping_Count,
	};

	enum RapidFireName {
		RapidFire_Enable,
		RapidFire_Button,
		RapidFire_Button2,
		RapidFire_FirstTime,
		RapidFire_Release,
		RapidFire_PressTime,
		RapidFire_Count,
	};

	BOOL				Open(WCHAR* file);
	void				setProfile(int i);
	void				setTabMapping(int i);
	void				setPreferredDS(int i);
	void				setTabMode(int i, int mode);
	void				setReminder(int i, int reminder);
	void				setStats(int i, int stat);
	void				setThreshold(int i);
	void				setSimultaneous(int i);
	void				setLongPress(int i);
	void				setVeryLongPress(int i);
	void				setWebRefreshTime(int i);
	void				setDesiredVirtualPad(int i);
	void				setSplitTouch();
	void				setTriggersMode(int i);
	void				setWaveSpeed(int i);
	void				setDefaultZoomValue(int i);
	void				setDarkMode(int i);

	WCHAR*				CheckboxToString(byte, byte, byte, byte, byte, byte, byte, byte);
	WCHAR*				dsIDToString(byte, byte, byte, byte, byte);
	WCHAR*				vjIDToString(byte, byte, byte, byte, byte, byte, byte, byte);
	WCHAR*				MouseToString(byte, byte, byte, byte, byte, byte, byte);
	WCHAR*				GridToString(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);
	WCHAR*				KeymapToString(std::vector<BYTE>);
	unsigned short		CheckboxString(std::wstring, unsigned char);
	byte				dsIDString(std::wstring, unsigned char);
	byte				vjIDString(std::wstring, unsigned char);
	unsigned short		MouseString(std::wstring, unsigned char);
	short				GridString(std::wstring, unsigned char);
	std::vector<BYTE>	KeymapString(std::wstring);

	WCHAR				m_file[MAX_PATH + 1] = { 0 };
};

	extern Settings		tape;
