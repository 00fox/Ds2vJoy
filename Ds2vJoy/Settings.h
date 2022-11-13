#pragma once
#include "Keymap.h"
#include "Mapping.h"
#include "RapidFire.h"

class Settings
{
public:
	const int			VersionDate = 202211131;
	const std::wstring	ProgramFilesDirName = L"Ds2vJoy";
	bool				BreakAndExit = false;
	bool				FirstPass = true;

	WCHAR				Settingstxt[20];
	WCHAR				Mappingtxt[20];
	WCHAR				RapidFiretxt[20];
	WCHAR				Keymaptxt[20];
	WCHAR				XOutputtxt[20];
	WCHAR				Guardiantxt[20];
	WCHAR				Webtxt[20];
	//////////////////////
	WCHAR				ViGEmtxt[20];

	enum SettingCategory : short
	{
		SettingCategory_Create = -2,
		SettingCategory_Update = -1,
		SettingCategory_All,
		SettingCategory_Profile,
		SettingCategory_Tray,
		SettingCategory_Settings,
		SettingCategory_Mapping,
		SettingCategory_RapidFire,
		SettingCategory_Keymap,
		SettingCategory_XOutput,
		SettingCategory_Guardian,
		SettingCategory_Web,
		SettingCategory_WebScript,
		SettingCategory_Links,
		SettingCategory_Notepad
	};

	enum SettingName : short
	{
		Setting_Update = -1,
		Setting_All,				//All
		Setting_Version,
		Setting_Country,
		Setting_Profile,			//Profile
		Setting_TopMost,
		Setting_Transparency,
		Setting_vJoyShutDown,
		Setting_Tasktray,
		Setting_CloseMinimize,
		Setting_DisconnectBT,
		Setting_LowBattAlert,
		Setting_Serial,
		Setting_Device1,
		Setting_Device2,
		Setting_Dispatch1,
		Setting_Dispatch2,
		Setting_Dispatch3,
		Setting_BlackLedOnExit,
		Setting_MappingViewMode,
		Setting_CloneViewMode,
		Setting_NotepadFont,
		Setting_MappingPaused,		//Tasktray
		Setting_RapidFirePaused,
		Setting_KeymapPaused,
		Setting_vJoyPaused,
		Setting_XOutputPaused,
		Setting_GuardianPaused,
		Setting_RemoveBlacklist,	//Guardian
		Setting_PurgeWhitelist,
		Setting_dsHID1,
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
		Setting_App0Name,			//Links
		Setting_App1Name,
		Setting_App2Name,
		Setting_App3Name,
		Setting_App4Name,
		Setting_App0Location,
		Setting_App1Location,
		Setting_App2Location,
		Setting_App3Location,
		Setting_App4Location,
		Setting_App5Location,
		Setting_App6Location,
		Setting_App7Location,
		Setting_App8Location,
		Setting_App9Location,
		Setting_Notepad,			//Notepad
		Setting_Opacity,			//Settings	//Start of Profile dependant
		Setting_PreferredSource,
		Setting_MouseActive,
		Setting_KeyboardActive,
		Setting_vJoyDevice,
		Setting_XInputDevice,
		Setting_Threshold,
		Setting_Simultaneous,
		Setting_LongPress,
		Setting_VeryLongPress,
		Setting_MouseCanBypass,
		Setting_TriggersMode,
		Setting_Dispatch,
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
		Setting_XOutputActive,		//XOutput
		Setting_vJoyActive,
		Setting_DesiredVirtualPad,
		Setting_target_DS4,
		Setting_target_X360,
		Setting_GuardianActive,		//Guardian
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

	enum CountryID : byte
	{
		Country_UNITED_STATES,				//US	01033
		Country_ALBANIA,					//AL	01052
		Country_ARMENIA,					//AM	01067
		Country_AZERBAIJAN,					//AZ	01068
		Country_BOSNIA,						//BA	05146
		Country_BULGARIA,					//BG	01026
		Country_BRAZIL,						//BR	01046
		Country_BELARUSIAN,					//BY	01059
		Country_CANADA,						//CA	03084
		Country_CHEROKEE,					//CH	01116
		Country_CHINA_SIMPLIFIED,			//CN	02052
		Country_SERBIA_LATIN,				//CS	02074
		Country_CZECH_REPUBLIC,				//CZ	01029
		Country_GERMANY,					//DE	01031
		Country_DENMARK,					//DK	01030
		Country_ESTONIA,					//EE	01061
		Country_SPAIN,						//ES	03082
		Country_ETHIOPIA,					//ET	01118
		Country_FINLAND,					//FI	01035
		Country_FRANCE,						//FR	01036
		Country_GREAT_BRITAIN,				//GB	01106
		Country_GEORGIA,					//GE	01079
		Country_GREECE,						//GR	01032
		Country_HONG_KONG,					//HK	03076
		Country_CROATIA,					//HR	01050
		Country_HUNGARY,					//HU	01038
		Country_INDONESIA,					//ID	01057
		Country_IRELAND,					//IE	02108
		Country_ISRAEL,						//IL	01037
		Country_INDIA,						//IN	01081
		Country_PERSIAN,					//IR	01065
		Country_ICELAND,					//IS	01039
		Country_ITALY,						//IT	01040
		Country_JAPAN,						//JP	01041
		Country_CAMBODIA,					//KH	01107
		Country_KOREA,						//KR	01042
		Country_KAZAKHSTAN,					//KZ	01087
		Country_LAOS,						//LA	01108
		Country_LITHUANIA,					//LT	01063
		Country_LUXEMBOURG,					//LU	01134
		Country_LATVIA,						//LV	01062
		Country_MACEDONIA,					//MK	01071
		Country_MALTA,						//MT	01082
		Country_MEXICO,						//MX	02058
		Country_MALAYSIA_BRUNEI_SINGAPORE,	//MY	01086
		Country_NETHERLANDS,				//NL	01043
		Country_NORWAY,						//NO	01044
		Country_NEPAL,						//NP	01121
		Country_NEW_ZEALAND,				//NZ	01153
		Country_PERU,						//PE	03179
		Country_FILIPINO,					//PH	01124
		Country_URDU,						//PK	01056
		Country_POLAND,						//PL	01045
		Country_PORTUGAL,					//PT	02070
		Country_ROMANIA,					//RO	01048
		Country_SERBIAN_CYRILLIC,			//RS	09242
		Country_RUSSIA,						//RU	01049
		Country_SAUDI_ARABIA,				//SA	01025
		Country_SWEDEN,						//SE	01053
		Country_SLOVENIA,					//SI	01060
		Country_SLOVAKIA,					//SK	01051
		Country_THAILAND,					//TH	01054
		Country_TURKEY,						//TR	01055
		Country_TAIWAN,						//TW	01028
		Country_UKRAINE,					//UA	01058
		Country_UZBEKISTAN,					//UZ	01091
		Country_VIETNAMESE,					//VN	01066
		Country_SOUTH_AFRICA,				//ZA	01078
		Country_Count
	};
	BOOL				InstalledLanguage[68] = { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };

	Settings();
	~Settings();

	BOOL				Init(WCHAR* inifile);
	void				LoadLanguage();
	void				Load(int category = SettingCategory_All);
	void				Save(int item = Setting_All);

	void				setCountry(int land);
	void				setvJoyDevice(int id);
	void				setXInputDevice(int id);
	void				setSerial(const WCHAR*);
	void				setDevice(const WCHAR*, unsigned char device);
	void				setTouchPadButton(byte);
	void				setTouchRow(int);
	void				setTouchCol(int i);
	void				setLED(unsigned int i);
	void				setPID(const WCHAR* buf, int ds);
	void				setExeName(const WCHAR* buf, int exe);
	void				setWebURL(const WCHAR* url, int lnk);
	void				setAppName(const WCHAR*, int app);
	void				setAppLocation(const WCHAR*, int app);

	static const WCHAR*	CountryString(CountryID land);

	HWND				Ds2hWnd;
	HINSTANCE			Ds2hInst;
	WCHAR				szTitle[100];
	WCHAR				szWindowClass[100];
	int					Ds2vJoyPID;

	POINT				mousepoint;
	short				W;							//Logical (scaling)
	short				H;
	short				Wp;							//Physical
	short				Hp;
	short				w;							//Logical / 2
	short				h;
	double				Hscale;						//Scaling
	double				Vscale;
	float				proportianality;			//(W > H) ? (W / H) : (H / W);
	bool				Transparency = false;
	byte				Opacity = 60;
	bool				TopMost = true;

	COLORREF			ink_neutral =				RGB(128, 128, 128);
	COLORREF			ink_deepGrey =				RGB(60, 64, 78);
	COLORREF			ink_near_dark =				RGB(10, 10, 10);
	COLORREF			ink_near_silver =			RGB(214, 167, 230);

	COLORREF			ink_black =					RGB(0, 0, 0);
	COLORREF			ink_blue_black =			RGB(10, 12, 13);
	COLORREF			ink_grey =					RGB(205, 205, 210);
	COLORREF			ink_red =					RGB(238, 172, 176);
	COLORREF			ink_orange =				RGB(255, 188, 152);
	COLORREF			ink_yellow =				RGB(229, 191, 142);
	COLORREF			ink_emerald =				RGB(198, 195, 186);
	COLORREF			ink_green =					RGB(162, 193, 186);
	COLORREF			ink_blue =					RGB(161, 198, 247);
	COLORREF			ink_purple =				RGB(211, 178, 221);

	COLORREF			ink_white =					RGB(240, 240, 240);
	COLORREF			ink_blue_white =			RGB(210, 210, 215);
	COLORREF			ink_bright_grey =			RGB(234, 234, 240);
	COLORREF			ink_bright_red =			RGB(252, 228, 230);
	COLORREF			ink_bright_orange =			RGB(250, 237, 209);
	COLORREF			ink_bright_yellow =			RGB(251, 241, 214);
	COLORREF			ink_bright_emerald =		RGB(227, 255, 171);
	COLORREF			ink_bright_green =			RGB(222, 238, 235);
	COLORREF			ink_bright_blue =			RGB(226, 235, 249);
	COLORREF			ink_bright_purple =			RGB(245, 231, 248);

	#define				ink_ABOUT					ink_black
	#define				ink_DLG						ink_near_dark
	#define				ink_MSGBOX					ink_near_dark
	#define				ink_SCROLLBAR				ink_near_dark
	COLORREF			ink_BTN =					RGB(100, 93, 79);
	COLORREF			ink_BTN_Heavy =				RGB(45, 45, 45);
	#define				ink_BTN_Light				ink_blue_white
	#define				ink_BTN_Install				ink_near_dark
	#define				ink_BTN_CLONE				ink_BTN
	COLORREF			ink_BTN_MAPPING =			RGB(87, 24, 55);
	COLORREF			ink_BTN_MAPPING_OK =		RGB(51, 239, 96);
	COLORREF			ink_BTN_MAPPING_CLEAR =		RGB(0, 227, 248);
	COLORREF			ink_BTN_MAPPING_HELP =		RGB(0, 219, 78);
	#define				ink_COMBO					ink_near_dark
	#define				ink_COMBO_DARK				ink_blue_black
	#define				ink_STATIC					ink_BTN
	COLORREF			ink_STATIC_DARK =			RGB(182, 184, 138);
	COLORREF			ink_STATIC_Mouse1 =			RGB(24, 24, 92);
	COLORREF			ink_STATIC_Mouse2 =			RGB(224, 224, 255);
	#define				ink_STATIC_CHK				ink_near_dark
	#define				ink_STATIC_CHK_DARK			ink_near_silver
	COLORREF			ink_STATIC_CHK2 =			RGB(136, 128, 104);
	COLORREF			ink_POSTIT =				RGB(0, 0, 255);
	#define				ink_EDIT					ink_near_dark
	COLORREF			ink_EDIT_TERMINAL =			RGB(172, 196, 226);
	#define				ink_EDIT_TIMELINE			ink_BTN_MAPPING
	#define				ink_LIST					ink_near_dark
	#define				ink_LIST_DARK				ink_near_silver
	#define				ink_LIST_BACK				ink_blue_white
	#define				ink_LIST_BACK_DARK			ink_blue_black
	COLORREF			ink_LIST_BACKGROUND =		RGB(225, 225, 230);
	#define				ink_LIST_BACKGROUND_DARK	ink_near_dark
	COLORREF			ink_LIST_Selected =			RGB(0, 120, 215);
	#define				ink_LIST_HIGHLIGHT			ink_bright_grey
	COLORREF			ink_LIST_Disabled =			RGB(195, 195, 195);
	COLORREF			ink_LIST_not =				RGB(195, 10, 5);
	COLORREF			ink_LIST_not_HIGHLIGHT =	RGB(255, 160, 165);
	#define				ink_LIST_not_HIGHLIGHT_DARK ink_bright_emerald
	COLORREF			ink_LIST_separator =		RGB(232, 228, 9);
	#define				ink_LIST_separator_HIGH		ink_LIST_Selected
	COLORREF			ink_LIST_Header =			RGB(194, 195, 198);
	#define				ink_LIST_scndHeader			ink_grey
	COLORREF			ink_LIST_header1 =			RGB(124, 123, 0);
	COLORREF			ink_LIST_header2 =			RGB(0, 123, 124);
	COLORREF			ink_LIST_header1_DARK =		RGB(174, 173, 0);
	COLORREF			ink_LIST_header2_DARK =		RGB(0, 173, 174);
	COLORREF			ink_MENU =					RGB(63, 37, 67);
	COLORREF			ink_MENU_SELECTED =			RGB(255, 255, 225);
	#define				ink_MENU_HIGHLIGHT			ink_bright_grey
	COLORREF			ink_MENU_SEPARATOR =		RGB(166, 166, 166);
	#define				ink_MENU_Delete				ink_LIST_not_HIGHLIGHT
	COLORREF			ink_MENU_SeeView2 =			RGB(254, 254, 255);
	COLORREF			ink_MENU_SeeView2_HIGH =	RGB(163, 154, 21);
	#define				ink_NOTEPAD					ink_near_dark
	#define				ink_NOTEPAD_DARK			ink_EDIT_TERMINAL
	#define				ink_NOTEPAD_ALERT			ink_red
	#define				ink_TAB						ink_near_dark
	#define				ink_TAB_DARK				ink_emerald
	#define				ink_TAB2_DARK				ink_yellow
	COLORREF			ink_TOOLTIP =				RGB(240, 228, 241);
	
	#define				Bk_ABOUT					ink_bright_yellow
	COLORREF			Bk_DLG =					RGB(191, 200, 196);
	#define				Bk_MSGBOX					Bk_DLG
	#define				Bk_SCROLLBAR				Bk_DLG
	#define				Bk_LIST_header1_DARK		ink_black
	#define				Bk_LIST_header2_DARK		ink_deepGrey
	COLORREF			Bk_BTN =					RGB(36, 163, 163);
	#define				Bk_STATIC					Bk_BTN
	#define				Bk_STATS					ink_white
	COLORREF			Bk_POSTIT =					RGB(240, 240, 0);
	#define				Bk_NOTEPAD					ink_white
	#define				Bk_NOTEPAD_DARK				ink_near_dark
	COLORREF			Bk_TOOLTIP =				RGB(22, 8, 84);

	HBRUSH				hB_neutral =				CreateSolidBrush(ink_neutral);
	HBRUSH				hB_deepGrey =				CreateSolidBrush(ink_deepGrey);

	HBRUSH				hB_black =					CreateSolidBrush(ink_black);
	HBRUSH				hB_blue_black =				CreateSolidBrush(ink_blue_black);
	HBRUSH				hB_grey =					CreateSolidBrush(ink_grey);
	HBRUSH				hB_red =					CreateSolidBrush(ink_red);
	HBRUSH				hB_orange =					CreateSolidBrush(ink_orange);
	HBRUSH				hB_yellow =					CreateSolidBrush(ink_yellow);
	HBRUSH				hB_emerald =				CreateSolidBrush(ink_emerald);
	HBRUSH				hB_green =					CreateSolidBrush(ink_green);
	HBRUSH				hB_blue =					CreateSolidBrush(ink_blue);
	HBRUSH				hB_purple =					CreateSolidBrush(ink_purple);
	
	HBRUSH				hB_white =					CreateSolidBrush(ink_white);
	HBRUSH				hB_blue_white =				CreateSolidBrush(ink_blue_white);
	HBRUSH				hB_bright_grey =			CreateSolidBrush(ink_bright_grey);
	HBRUSH				hB_bright_red =				CreateSolidBrush(ink_bright_red);
	HBRUSH				hB_bright_orange =			CreateSolidBrush(ink_bright_orange);
	HBRUSH				hB_bright_yellow =			CreateSolidBrush(ink_bright_yellow);
	HBRUSH				hB_bright_emerald =			CreateSolidBrush(ink_bright_emerald);
	HBRUSH				hB_bright_green =			CreateSolidBrush(ink_bright_green);
	HBRUSH				hB_bright_blue =			CreateSolidBrush(ink_bright_blue);
	HBRUSH				hB_bright_purple =			CreateSolidBrush(ink_bright_purple);

	#define				hB_ABOUT					hB_bright_yellow
	#define				hB_BackGround				hB_blue_white
	#define				hB_BackGround_DARK			hB_blue_black
	#define				hB_CLONE_BackGround			hB_white
	#define				hB_NOTEPAD_BackGround		hB_white
	#define				hB_NOTEPAD_BackGround_DARK	hB_black
	HBRUSH				hB_DLG =					CreateSolidBrush(Bk_DLG);
	HBRUSH				hB_DLG_DARK =				CreateSolidBrush(RGB(255, 193, 185));
	#define				hB_MSGBOX					hB_DLG
	#define				hB_SCROLLBAR				hB_DLG
	#define				hB_BTN						hB_blue_white
	#define				hB_BTN_DARK					hB_black
	HBRUSH				hB_BTN_Border =				CreateSolidBrush(RGB(195, 195, 200));
	HBRUSH				hB_BTN_Border_DARK =		CreateSolidBrush(RGB(60, 64, 192));
	HBRUSH				hB_Not_Installed =			CreateSolidBrush(RGB(160, 160, 160));
	HBRUSH				hB_Running =				CreateSolidBrush(Bk_POSTIT);
	HBRUSH				hB_Stopped =				CreateSolidBrush(RGB(255, 140, 0));
	HBRUSH				hB_Paused =					CreateSolidBrush(RGB(96, 192, 96));
	HBRUSH				hB_STATIC_Mouse1 =			CreateSolidBrush(RGB(180, 180, 0));
	HBRUSH				hB_STATIC_Mouse2 =			CreateSolidBrush(RGB(180, 0, 180));
	HBRUSH				hB_POSTIT =					CreateSolidBrush(RGB(175, 175, 175));
	#define				hB_POSTIT_DARK				hB_Paused
	HBRUSH				hB_POSTIT_Rand0 =			CreateSolidBrush(RGB(185, 181, 245));
	HBRUSH				hB_POSTIT_Rand1 =			CreateSolidBrush(RGB(210, 225, 0));
	#define				hB_POSTIT_Rand2				hB_Running
	HBRUSH				hB_POSTIT_Rand3 =			CreateSolidBrush(RGB(225, 115, 210));
	HBRUSH				hB_EDIT =					CreateSolidBrush(RGB(228, 228, 232));
	HBRUSH				hB_EDIT_BORDER =			CreateSolidBrush(RGB(187, 151, 172));
	#define				hB_EDIT_DARK				hB_black
	#define				hB_EDIT_DARK2				hB_deepGrey
	HBRUSH				hB_EDIT_DARK3 =				CreateSolidBrush(RGB(165, 175, 200));
	#define				hB_LIST						hB_blue_white
	#define				hB_LIST_DARK				hB_yellow
	HBRUSH				hB_LIST_HIGHLIGHT =			CreateSolidBrush(ink_LIST_Selected);
	HBRUSH				hB_LIST_Disabled =			CreateSolidBrush(RGB(190, 190, 195));
	HBRUSH				hB_LIST_Disabled_DARK =		CreateSolidBrush(RGB(84, 92, 64));
	HBRUSH				hB_LIST_Disable1 =			CreateSolidBrush(RGB(169, 186, 225));
	HBRUSH				hB_LIST_Disable1_DARK =		CreateSolidBrush(RGB(90, 90, 180));
	HBRUSH				hB_LIST_Disable2 =			CreateSolidBrush(ink_purple);
	#define				hB_LIST_Disable2_DARK		hB_STATIC_Mouse2
	HBRUSH				hB_LIST_Header =			CreateSolidBrush(ink_LIST_Header);
	#define				hB_LIST_Header_DARK			hB_black
	#define				hB_LIST_Header2				hB_grey
	#define				hB_LIST_Header2_DARK		hB_deepGrey
	#define				hB_MENU						hB_grey
	HBRUSH				hB_MENU_CLONE =				CreateSolidBrush(RGB(200, 200, 205));
	HBRUSH				hB_MENU_SELECTED =			CreateSolidBrush(RGB(153, 160, 157));
	#define				hB_MENU_HIGHLIGHT			hB_LIST_HIGHLIGHT
	HBRUSH				hB_CHECKBOX_UNCHECKED =		CreateSolidBrush(ink_LIST_BACKGROUND);
	#define				hB_CHECKBOX_CHECKED			hB_bright_yellow
	HBRUSH				hB_CHECKBOX_DARK =			CreateSolidBrush(RGB(237, 215, 195));
	#define				hB_CHECKBOX_INDETERMINATE	hB_bright_blue

	HFONT hLog = CreateFont(11, 7, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Lucida Console");
	HFONT hSerial = CreateFont(14, 5, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Consolas");
	HFONT hNotepad = CreateFont(15, 7, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Consolas");
	HFONT hStatus = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"MS Shell Dlg");
	HFONT hTab = CreateFont(13, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Bahnschrift SemiLight SemiConde");
	HFONT hTab2 = CreateFont(14, 5, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hPostIt = CreateFont(14, 4, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe Print");
	HFONT hLegend = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hLegend2 = CreateFont(12, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hLegend3 = CreateFont(11, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hLegend4 = CreateFont(9, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hEdit = CreateFont(14, 6, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hEdit2 = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Bahnschrift SemiLight SemiConde");
	HFONT hEdit3 = CreateFont(13, 4, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hStatic = CreateFont(14, 6, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hStatic2 = CreateFont(13, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hStatic3 = CreateFont(14, 6, 0, 0, FW_MEDIUM, FALSE, TRUE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hCheck2 = CreateFont(9, 5, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Lucida Console");
	HFONT hCheck3 = CreateFont(14, 5, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hCombo = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hCombo2 = CreateFont(14, 4, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hButton = CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hButton2 = CreateFont(15, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hMenu = CreateFont(15, 5, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hMenu2 = CreateFont(14, 6, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hList = CreateFont(15, 4, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hTopMost = CreateFont(16, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	HFONT hAbout = CreateFont(18, 0, 0, 10, FW_REGULAR, TRUE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe Script");
	HFONT hTooltip = CreateFont(15, 7, 0, 30, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Bahnschrift SemiLight SemiConde");
	HFONT hDelete = CreateFont(22, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

	#define hCheck hStatic
	#define hCancel hButton2
	#define hStats hStatic2
	#define hSlider hButton
	#define hWeb hTopMost
	#define hLinks hTab2
	#define hButton3 hCombo

	HICON hIconTray[120];
	
	unsigned char		Profile;
	bool				DsvJoyAddedToGuardian = false;

	bool				cansavemappings = true;
	bool				cansaverapidfires = true;
	bool				cansavekeymaps = true;
	bool				cansavexoutput = true;
	bool				cansaveblockedsites = true;
	bool				cansavewebscript = true;
	bool				cansavenotepad = true;

	byte				Country = 0;
	unsigned char		ActualSource = 0;	//0 Unknown
	unsigned char		PreferredSource;	//0 None, 1 DS4, 2 DS5, 3 DirectInput, 4 XInput
	bool				KeyboardActive;
	bool				MouseActive;
	bool				KeyboardActivetmp = false;
	bool				MouseActivetmp = false;
	unsigned char		vJoyDevice;
	unsigned char		XInputDevice;

	bool				Tasktray;
	bool				CloseMinimize;
	bool				DisconnectBT;
	bool				MouseCanBypass;
	bool				MouseCanBypasstmp = false;
	bool				LowBattAlert;
	unsigned char		TriggersMode;		//0 None, 1 Resist, 2 Shoot, 3 Proactive
	bool				DarkTheme;

	WCHAR				Serial[13] = { 0 };
	bool				SplitTouch;
	byte				TouchPadButton;
	unsigned char		TouchCol;
	unsigned char		TouchRow;

	struct DevicesData
	{
		std::wstring pname;
		WORD pid;
		WORD vid;
		std::wstring uid;
	};
	std::vector<DevicesData> DevicesList;
	WCHAR				Device1[MAX_PATH] = { };
	WCHAR				Device2[MAX_PATH] = { };
	byte				diDispatch[SrceDispatchID::Dispatch_Count];
	byte				diDispatch1[SrceDispatchID::Dispatch_Count];
	byte				diDispatch2[SrceDispatchID::Dispatch_Count];
	byte				diDispatch3[SrceDispatchID::Dispatch_Count];

	bool				BlackLedOnExit;
	DWORD				LED_Color;
	byte				WaveSpeed;

	unsigned short		Threshold;			//2056 (0-32767)
	unsigned short		Simultaneous;		//40 ms
	unsigned short		LongPress;			//255 ms
	unsigned short		VeryLongPress;		//3287 ms
	unsigned short		WebRefreshTime;		//20 s

	std::chrono::system_clock::time_point lastButton = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point lastMove = std::chrono::system_clock::now();
	byte				BatteryLevel = 0;
	bool				BatteryCharge = false;
	bool				zoneChange = false;
	unsigned char		Stance = 2;		//0 back, 1 leaned, 2 leaned + sat, 3 sat, 4 leaning
	unsigned char		Zone = 2;

	bool				CallbackPaused = true;
	bool				MouseMovePaused = true;
	bool				MappingPaused;
	bool				RapidFirePaused;
	bool				KeymapPaused;
	bool				vJoyPaused;
	bool				XOutputPaused;
	bool				GuardianPaused;
	bool				isExplorerLoaded;
	bool				isWebView2Installing;

	Mappings			Mappingdata;
	Keymaps				Keymapdata;
	RapidFires			RapidFiredata;
	unsigned short		ReceivedData[SrceOffsetsID::Offset_Count] = { 0 };

	unsigned char		TabMapping;
	bool				MappingViewMode;
	bool				CloneViewMode;
	unsigned char		Mode[9];
	short				Stat[8];
	bool				Reminder[32];
	bool				destUsed[32];

	bool				XOutputActive;
	bool				vJoyActive;
	unsigned char		DesiredVirtualPad;	//1 DS4, 2 Xbox360
	byte				target_DS4[24];
	byte				target_X360[24];

	bool				GuardianActive;
	bool				vJoyShutDown;
	bool				RemoveBlacklist;
	bool				PurgeWhitelist;
	WCHAR				dsHID[3][MAX_PATH] = { };
	bool				dsHID1Enable;
	bool				dsHID2Enable;
	bool				dsHID3Enable;
	WCHAR				Exe1Name[MAX_PATH] = { };
	WCHAR				Exe2Name[MAX_PATH] = { };
	WCHAR				Exe3Name[MAX_PATH] = { };
	WCHAR				Exe4Name[MAX_PATH] = { };
	WCHAR				Exe5Name[MAX_PATH] = { };
	bool				Exe1NameEnable;
	bool				Exe2NameEnable;
	bool				Exe3NameEnable;
	bool				Exe4NameEnable;
	bool				Exe5NameEnable;

	float				DefaultZoomValue = 0.47;
	bool				RawBounds = false;
	unsigned char		DarkMode = 1;
	std::wstring		WebScript = LR"()";
	std::wstring		WebLanguage = L"";
	std::wstring		UserAgent = L"";
	std::wstring		BlockedSites = L"";
	WCHAR				WebURL[10][MAX_PATH] = { };

	WCHAR				App0Name[MAX_PATH] = { };
	WCHAR				App1Name[MAX_PATH] = { };
	WCHAR				App2Name[MAX_PATH] = { };
	WCHAR				App3Name[MAX_PATH] = { };
	WCHAR				App4Name[MAX_PATH] = { };
	WCHAR				App0Location[MAX_PATH] = { };
	WCHAR				App1Location[MAX_PATH] = { };
	WCHAR				App2Location[MAX_PATH] = { };
	WCHAR				App3Location[MAX_PATH] = { };
	WCHAR				App4Location[MAX_PATH] = { };
	WCHAR				App5Location[MAX_PATH] = { };
	WCHAR				App6Location[MAX_PATH] = { };
	WCHAR				App7Location[MAX_PATH] = { };
	WCHAR				App8Location[MAX_PATH] = { };
	WCHAR				App9Location[MAX_PATH] = { };

	std::wstring		Notepad = L"";
	std::wstring		NotepadFont = L"";
	unsigned short		NotepadFontH = 14;
	unsigned short		NotepadFontW = 0;
	bool				NotepadUnsaved = false;
	size_t				web_actualtab = 0;

	HMODULE				hMagnification = nullptr;
	typedef				bool(WINAPI* hMagSetSmoothing)(bool);
	hMagSetSmoothing	MagnificationSmoothing;
	bool				MagInitialized = false;
	bool				MagCanUninitialize = true;
	float				MagLevel = 1;
	bool				MagCursor = true;

private:
	enum MappingName : byte
	{
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
		Mapping_Target,				//1-5(3,3,3,3,3,0,0,0)
		Mapping_dsID,
		Mapping_OrXorNot,			//1-4(2,2,2,2,0,0,0,0)
		Mapping_dsDisable,			//1-5(2,2,2,2,2,0,0,0)
		Mapping_ActionType,			//1-8(2,2,2,2,2,2,2,2)
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
		MappingName_Count,
	};

	enum RapidFireName : unsigned char
	{
		RapidFire_Enable,
		RapidFire_Button,
		RapidFire_Button2,
		RapidFire_FirstTime,
		RapidFire_Release,
		RapidFire_PressTime,
		RapidFireName_Count,
	};

	void				setProfile(int i);
	void				setOpacity(int i);
	void				setPreferredSource(int i);
	void				setMouseActive(int i);
	void				setTriggersMode(int i);
	void				setThreshold(int i);
	void				setSimultaneous(int i);
	void				setLongPress(int i);
	void				setVeryLongPress(int i);
	void				setWebRefreshTime(int i);
	void				setSplitTouch();
	void				setWaveSpeed(int i);
	void				setDispatch(int i, int value, unsigned char layout = 0);
	void				setTabMapping(int i);
	void				setTabMode(int i, int mode);
	void				setStats(int i, int stat);
	void				setReminder(int i, int reminder);
	void				setDesiredVirtualPad(int i);
	void				setDefaultZoomValue(int i);
	void				setDarkMode(int i);

	WCHAR*				CheckboxToString(byte, byte, byte, byte, byte, byte, byte, byte, bool eightOverFour = false);
	WCHAR*				dsIDToString(byte, byte, byte, byte, byte);
	WCHAR*				vjIDToString(byte, byte, byte, byte, byte, byte, byte, byte);
	WCHAR*				MouseToString(byte, byte, byte, byte, byte, byte, byte);
	WCHAR*				GridToString(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);
	WCHAR*				KeymapToString(std::vector<BYTE>);
	unsigned short		CheckboxString(std::wstring, unsigned char, bool eightOverFour = false);
	byte				dsIDString(std::wstring, unsigned char);
	byte				vjIDString(std::wstring, unsigned char);
	unsigned short		MouseString(std::wstring, unsigned char);
	unsigned short		GridString(std::wstring, unsigned char);
	std::vector<BYTE>	KeymapString(std::wstring);

	WCHAR				m_file[MAX_PATH + 1] = { 0 };
};

	extern	Settings			tape;
	typedef	Settings::CountryID	CountryID;
