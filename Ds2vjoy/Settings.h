#pragma once
#include "Keymap.h"
#include "Mapping.h"
#include "RapidFire.h"

class Settings
{
public:
	const int VersionDate = 202110162;

	WCHAR Settingstxt[20];
	WCHAR Mappingtxt[20];
	WCHAR ViGEmtxt[20];
	WCHAR Keymaptxt[20];
	WCHAR RapidFiretxt[20];
	WCHAR Guardiantxt[20];

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
		Setting_Category_Links
	};

	enum SettingName {
		Setting_Update = -1,
		Setting_All,				//All
		Setting_Version,
		Setting_Profile,			//Profile
		Setting_PreferredDS,
		Setting_Tasktray,
		Setting_CloseMinimize,
		Setting_DisconnectBT,
		Setting_LowBattAlert,
		Setting_dsSerial,
		Setting_BlackLedOnExit,
		Setting_MappingViewMode,
		Setting_CloneViewMode,
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
		Setting_vJoyDeviceID,		//Settings
		Setting_Threshold,
		Setting_Simultaneous,
		Setting_LongPress,
		Setting_VeryLongPress,
		Setting_MouseCanBypass,
		Setting_FFB,
		Setting_TriggersMode,
		Setting_TouchPadButton,
		Setting_TouchCol,
		Setting_TouchRow,
		Setting_LED_Color,
		Setting_Wave_Speed,
		Setting_TabMapping,
		Setting_TabToMode,
		Setting_Reminder,
		Setting_Mappingdata,		//vJoy
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

	void Init(HINSTANCE hInst, HWND hWnd);
	BOOL OpenIni(WCHAR* inifile);
	void Load(int category = Setting_Category_All);
	void Save(int item = Setting_All);

	const WCHAR* getSerial();
	const std::string getHID(int ds);
	void setvJoyDeviceID(int id);
	void SetTouchPadButton(byte);
	void SetTouchRow(int);
	void SetTouchCol(int i);
	void setSerial(const WCHAR*);
	void SetLED(DWORD i);
	void setPID(const WCHAR* buf, int ds);
	void setExeName(const WCHAR*, int exe);
	void setAppName(const WCHAR*, int app);
	void setAppLocation(const WCHAR*, int app);

	HWND ActualhWnd;
	HWND LoghWnd;

	Mappings Mappingdata;
	Keymaps Keymapdata;
	RapidFires RapidFiredata;

	int VersionDatetmp;
	unsigned char Profile;
	unsigned char Mode[9];
	bool Reminder[32];
	bool vJoyUsed[32];
	bool MappingViewMode;
	unsigned char TabMapping;
	bool CloneViewMode;

	unsigned char ActualDS = 0;		//0 Unknown
	unsigned char PreferredDS;		//1 DS4, 2 DS5

	unsigned char vJoyDeviceID;
	bool Tasktray;
	bool CloseMinimize;
	bool DisconnectBT;
	bool LowBattAlert;
	bool MouseCanBypass;

	bool FFB;
	unsigned char TriggersMode;		//0 None, 1 Resist, 2 Shoot, 3 Proactive

	bool SplitTouch;
	byte TouchPadButton;
	unsigned char TouchCol;
	unsigned char TouchRow;

	WCHAR dsSerial[13] = { 0 };
	DWORD LED_Color;
	byte WaveSpeed;
	bool BlackLedOnExit;

	byte Threshold;					//8 (0-128)
	unsigned short Simultaneous;	//40 ms
	unsigned short LongPress;		//255 ms
	unsigned short VeryLongPress;	//3287 ms

	bool vJoyPaused;
	bool ViGEmPaused;
	bool KeymapPaused;
	bool RapidFirePaused;
	bool GuardianPaused;

	bool ViGEmActive;
	unsigned char DesiredVirtualPad;	//1 Xbox360, 2 DS4
	bool target_X360[24];
	byte dstarget_X360[24];
	byte vjtarget_X360[24];
	bool target_DS4[24];
	byte dstarget_DS4[24];
	byte vjtarget_DS4[24];
	LONG FFBvJoyLeft;
	LONG FFBvJoyRight;

	bool GuardianActive;
	bool RemoveBlacklist;
	bool PurgeWhitelist;
	WCHAR dsHID1[MAX_PATH] = { 0 };
	WCHAR dsHID2[MAX_PATH] = { 0 };
	WCHAR dsHID3[MAX_PATH] = { 0 };
	bool dsHID1Enable;
	bool dsHID2Enable;
	bool dsHID3Enable;
	WCHAR Exe1Name[MAX_PATH] = { 0 };
	WCHAR Exe2Name[MAX_PATH] = { 0 };
	WCHAR Exe3Name[MAX_PATH] = { 0 };
	WCHAR Exe4Name[MAX_PATH] = { 0 };
	WCHAR Exe5Name[MAX_PATH] = { 0 };
	bool Exe1NameEnable;
	bool Exe2NameEnable;
	bool Exe3NameEnable;
	bool Exe4NameEnable;
	bool Exe5NameEnable;

	WCHAR App1Name[MAX_PATH] = { 0 };
	WCHAR App2Name[MAX_PATH] = { 0 };
	WCHAR App3Name[MAX_PATH] = { 0 };
	WCHAR App4Name[MAX_PATH] = { 0 };
	WCHAR App5Name[MAX_PATH] = { 0 };
	WCHAR App1Location[MAX_PATH] = { 0 };
	WCHAR App2Location[MAX_PATH] = { 0 };
	WCHAR App3Location[MAX_PATH] = { 0 };
	WCHAR App4Location[MAX_PATH] = { 0 };
	WCHAR App5Location[MAX_PATH] = { 0 };

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

	BOOL Open(WCHAR* file);
	void SetProfile(int i);
	void SetTabMapping(int i);
	void SetPreferredDS(int i);
	void SetTabMode(int i, int mode);
	void SetReminder(int i, int reminder);
	void SetThreshold(int i);
	void SetSimultaneous(int i);
	void SetLongPress(int i);
	void SetVeryLongPress(int i);
	void SetDesiredVirtualPad(int i);
	void SetSplitTouch();
	void SetTriggersMode(int i);
	void SetWaveSpeed(int i);

	WCHAR* CheckboxToString(byte, byte, byte, byte, byte, byte, byte, byte);
	WCHAR* dsIDToString(byte, byte, byte, byte, byte);
	WCHAR* vjIDToString(byte, byte, byte, byte, byte, byte, byte, byte);
	WCHAR* MouseToString(byte, byte, byte, byte, byte, byte, byte);
	WCHAR* GridToString(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);
	WCHAR* KeymapToString(std::vector<BYTE>);
	unsigned short CheckboxString(std::wstring, unsigned char);
	byte dsIDString(std::wstring, unsigned char);
	byte vjIDString(std::wstring, unsigned char);
	unsigned short MouseString(std::wstring, unsigned char);
	short GridString(std::wstring, unsigned char);
	std::vector<BYTE> KeymapString(std::wstring);

	HWND m_hWnd;
	WCHAR m_file[MAX_PATH + 1] = { 0 };
};

extern HINSTANCE hInst;
extern Settings tape;
extern const std::wstring ProgramFilesDirName;
