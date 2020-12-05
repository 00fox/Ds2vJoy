#pragma once
#include "Keymap.h"
#include "Mapping.h"
#include "RapidFire.h"
class Settings
{
	WCHAR m_file[MAX_PATH + 1] = { 0 };
	WCHAR m_serial[13] = { 0 };
	enum MapName {
		Mapping_Enable=0,
		Mapping_ButtonID,
		Mapping_DS5_1,
		Mapping_DS5_1_Disable,
		Mapping_DS5_2,
		Mapping_DS5_2_Disable,
		Mapping_DS5_3,
		Mapping_DS5_3_Disable,
		Mapping_DS5_4,
		Mapping_DS5_4_Disable,
		Mapping_ForceOption,
		Mapping_Toggle,
		Mapping_Count,
	};

	enum RapidFireName {
		RapidFire_Enable=0,
		RapidFire_First,
		RapidFire_Release,
		RapidFire_Press,
		RapidFire_Button2,
		RapidFire_Count,
	};
public:
	Settings();
	bool Open(WCHAR*file);
	bool OpenIni(WCHAR *inifile);
	void Load();
	void Save();
	bool DisconnectBT;
	bool Tasktray;
	bool FFB;
	bool SplitTouchPad;
	int TouchPadButton;
	DWORD LED_Color;
	Keymaps Keymapdata;
	Mappings Mappingdata;
	RapidFires RapidFiredata;
	int TouchCol;
	int TouchRow;
	int vJoyDeviceID;
	void SetTouchRow(int);
	void SetTouchCol(int i);
	void SetTouchPadButton(DWORD);

	void SetLED_Color(DWORD i);
	const WCHAR * getSerial();
	void setSerial(const WCHAR*);
	void setvJoyDeviceID(int id);
	~Settings();
};
extern Settings g_settings;
