#pragma once
#include "Keymap.h"
#include "Mapping.h"
#include "RapidFire.h"

class Settings
{
	enum MappingName {
		Mapping_Enable,
		Mapping_ds_1,
		Mapping_ds_2,
		Mapping_ds_3,
		Mapping_ds_4,
		Mapping_ds_5,
		Mapping_Target_1,
		Mapping_Target_2,
		Mapping_Target_3,
		Mapping_Target_4,
		Mapping_Target_5,
		Mapping_vJoy_source_1,
		Mapping_vJoy_source_2,
		Mapping_vJoy_source_3,
		Mapping_vJoy_source_4,
		Mapping_vJoy_source_5,
		Mapping_ds_1_Disable,
		Mapping_ds_2_Disable,
		Mapping_ds_3_Disable,
		Mapping_ds_4_Disable,
		Mapping_ds_5_Disable,
		Mapping_OrXorNot_1,
		Mapping_OrXorNot_2,
		Mapping_OrXorNot_3,
		Mapping_OrXorNot_4,
		Mapping_If_mouse,
		Mapping_Force,
		Mapping_led,
		Mapping_Short,
		Mapping_Double,
		Mapping_Long,
		Mapping_Macro,
		Mapping_Pause,
		Mapping_Toggle,
		Mapping_vJoy_1,
		Mapping_vJoy_2,
		Mapping_vJoy_3,
		Mapping_vJoy_4,
		Mapping_vJoy_5,
		Mapping_vJoy_6,
		Mapping_vJoy_7,
		Mapping_vJoy_8,
		Mapping_On_release_1,
		Mapping_On_release_2,
		Mapping_On_release_3,
		Mapping_On_release_4,
		Mapping_On_release_5,
		Mapping_On_release_6,
		Mapping_On_release_7,
		Mapping_On_release_8,
		Mapping_vJoy_1_Disable,
		Mapping_vJoy_2_Disable,
		Mapping_vJoy_3_Disable,
		Mapping_vJoy_4_Disable,
		Mapping_vJoy_5_Disable,
		Mapping_vJoy_6_Disable,
		Mapping_vJoy_7_Disable,
		Mapping_vJoy_8_Disable,
		Mapping_Start_1,
		Mapping_Start_2,
		Mapping_Start_3,
		Mapping_Start_4,
		Mapping_Start_5,
		Mapping_Start_6,
		Mapping_Start_7,
		Mapping_Start_8,
		Mapping_Stop_1,
		Mapping_Stop_2,
		Mapping_Stop_3,
		Mapping_Stop_4,
		Mapping_Stop_5,
		Mapping_Stop_6,
		Mapping_Stop_7,
		Mapping_Stop_8,
		Mapping_Mouse_action_1,
		Mapping_Mouse_action_2,
		Mapping_Mouse_action_3,
		Mapping_Mouse_action_4,
		Mapping_Mouse_1,
		Mapping_Mouse_2,
		Mapping_Mouse_3,
		Mapping_Mouse_4,
		Mapping_Mouse_5,
		Mapping_Mouse_6,
		Mapping_Mouse_Grid,
		Mapping_Grid_x,
		Mapping_Grid_y,
		Mapping_Grid_w,
		Mapping_Grid_h,
		Mapping_Grid_nw,
		Mapping_Grid_nh,
		Mapping_Tab,
		Mapping_Count,
	};

	enum RapidFireName {
		RapidFire_Enable = 0,
		RapidFire_Button,
		RapidFire_Button2,
		RapidFire_FirstTime,
		RapidFire_Release,
		RapidFire_PressTime,
		RapidFire_Count,
	};

public:
	Settings();
	~Settings();

	BOOL OpenIni(WCHAR* inifile);
	void Load();
	void Save(int category = 0);

	const WCHAR* getSerial();
	const std::string getHID(int ds);
	void setvJoyDeviceID(int id);
	void SetTouchPadButton(DWORD);
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

	int Profile;
	int Mode[9];
	bool Reminder[32];
	bool vJoyUsed[32];

	int ActualDS = 0;				//0 Unknown
	int DesiredDS;					//1 DS4, 2 DS5

	int vJoyDeviceID;
	bool Tasktray;
	bool CloseMinimize;
	bool DisconnectBT;
	bool LowBattAlert;

	bool FFB;
	int TriggersMode;				//0 None, 1 Resist, 2 Shoot, 3 Proactive

	bool SplitTouch;
	int TouchPadButton;
	int TouchCol;
	int TouchRow;

	WCHAR dsSerial[13] = { 0 };
	DWORD LED_Color;
	bool BlackLedOnExit;

	int Threshold;					//7%
	int Simultaneous;				//40 ms
	int LongPress;					//255 ms
	int VeryLongPress;				//3287 ms

	bool vJoyPaused;
	bool ViGEmPaused;
	bool KeymapPaused;
	bool RapidFirePaused;
	bool GuardianPaused;

	bool ViGEmActive;
	int DesiredVirtualPad;			//1 Xbox360, 2 DS4
	bool target_X360[24];
	dsButtonID dstarget_X360[24];
	vJoyButtonID vjtarget_X360[24];
	bool target_DS4[24];
	dsButtonID dstarget_DS4[24];
	vJoyButtonID vjtarget_DS4[24];
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
	BOOL Open(WCHAR* file);
	void SetProfile(int i);
	void SetDesiredDS(int i);
	void SetTabMode(int i, int mode);
	void SetReminder(int i, int reminder);
	void SetThreshold(int i);
	void SetSimultaneous(int i);
	void SetLongPress(int i);
	void SetVeryLongPress(int i);
	void SetDesiredVirtualPad(int i);
	void SetSplitTouch();
	void SetTriggersMode(int i);

	WCHAR m_file[MAX_PATH + 1] = { 0 };
};

extern HINSTANCE hInst;
extern Settings tape;
extern const std::wstring ProgramFilesDirName;
