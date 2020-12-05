#include "stdafx.h"
#include "Settings.h"


Settings::Settings()
{
}

bool Settings::Open(WCHAR * file)
{
	lstrcpyW(m_file,file);
	return true;
}

bool Settings::OpenIni(WCHAR * inifile)
{
	WCHAR path[MAX_PATH + 1];
	if (0 != GetModuleFileName(NULL, path, MAX_PATH)) {
		WCHAR dir[MAX_PATH + 1];
		if (_wsplitpath_s(path, NULL, 0, dir, MAX_PATH + 1, NULL, 0, NULL, 0) == 0) {
			wsprintfW(m_file, L"%s%s", dir, inifile);
			return true;
		}
	}
	return false;
}

void Settings::Load()
{
	if (m_file[0] == 0)
		return;
	DisconnectBT = GetPrivateProfileInt(TEXT("settings"), TEXT("DisconnectBT"), 0, m_file) == 1 ? true : false;
	FFB = GetPrivateProfileInt(TEXT("settings"), TEXT("FFB"), 0, m_file) == 1 ? true : false;
	Tasktray = GetPrivateProfileInt(TEXT("settings"), TEXT("Tasktray"), 0, m_file) == 1 ? true : false;
	SplitTouchPad = GetPrivateProfileInt(TEXT("settings"), TEXT("SplitTouchPad"), 0, m_file) == 1 ? true : false;

	SetTouchPadButton(GetPrivateProfileInt(TEXT("settings"), TEXT("TouchPadButton"), 0, m_file));
	SetTouchCol(GetPrivateProfileInt(TEXT("settings"), TEXT("TouchCol"), 2, m_file));
	SetTouchRow(GetPrivateProfileInt(TEXT("settings"), TEXT("TouchRow"), 1, m_file));
	setvJoyDeviceID(GetPrivateProfileInt(TEXT("settings"), TEXT("vJoyDeviceID"), 1, m_file));
	SetLED_Color(GetPrivateProfileInt(TEXT("settings"), TEXT("LED_Color"), 0xFF0000, m_file));
	GetPrivateProfileString(L"settings", L"DS5Serial", L"", m_serial, sizeof(m_serial)/ sizeof(m_serial[0]), m_file);
	int n = sizeof(WCHAR) * 32 * 1024;
	WCHAR *buf = (WCHAR*)malloc(n);
	if (buf == 0)
		return;

	WCHAR *head = buf;
	int ret = GetPrivateProfileSectionW(L"Keymap",buf,n,m_file);
	if (ret > 0 && ret - 2 != n) {
		WCHAR *key = head,*value;
		while (*key != 0) {
			head += lstrlenW(key) + 1;
			value = wcschr(key, L'=');
			if (value == 0)
				break;
			*value++ = 0;
			if (_wcsnicmp(key, L"usepm", 5) == 0) {
				int btnid = _wtoi(key + 5);
				if (btnid <= vJoyButtonID::none || btnid >= vJoyButtonID::button_Count) {
					key = head;
					continue;
				}
				if (_wcsnicmp(value, L"1", 1) == 0) {
					for (Keymap& km : Keymapdata) {
						if (km.ButtonID == btnid) {
							km.usePostmessage = true;
							break;
						}
					}
				}
			}
			else if (_wcsnicmp(key, L"fw", 2) == 0) {
				int btnid = _wtoi(key + 2);
				if (btnid <= vJoyButtonID::none || btnid >= vJoyButtonID::button_Count) {
					key = head;
					continue;
				}
				if (wcslen(value) > 0) {
					for (Keymap& km : Keymapdata) {
						if (km.ButtonID == btnid) {
							km.findWindow.Val( value );
							break;
						}
					}
				}
			}
			else
			{
				Keymap _keymap;
				int btnid = _wtoi(key);
				if (btnid <= vJoyButtonID::none || btnid >= vJoyButtonID::button_Count) {
					key = head;
					continue;
				}
				_keymap.ButtonID = (vJoyButtonID)btnid;

				key = value;
				value = wcschr(key, L',');
				if (value == 0)
					break;
				*value++ = 0;
				if (_wtoi(key) != 0) {
					_keymap.Enable = true;
				}
				for (int i = 0; i < KEYMAP_MAX_KEYS; i++) {
					key = value;
					value = wcschr(key, L',');
					if (value != 0)
						*value++ = 0;
					int _vk = _wtoi(key);
					if (_vk <= 0 || _vk >= 0x100)
						break;
					_keymap.vk.push_back((BYTE)_vk);
					if (value == 0)
						break;
				}
				Keymapdata.push_back(std::move(_keymap));
			}
			key = head;
		}
	}

	head = buf;
	ret = GetPrivateProfileSectionW(L"Mapping", buf, n, m_file);
	if (ret > 0 && ret - 2 != n) {
		WCHAR *key = head, *value;
		while (*key != 0) {
			head += lstrlenW(key) + 1;
			value = wcschr(key, L'=');
			if (value == 0)
				break;
			*value++ = 0;
			int j = _wtoi(key);
			if (j <= 0 || j >= 128)
				break;

			int mapdata[MapName::Mapping_Count] = { 0 };
			for (int i = 0; i < MapName::Mapping_Count; i++) {
				key = value;
				value = wcschr(key, L',');
				if (value != 0)
					*value++ = 0;
				int j = _wtoi(key);
				if (j < 0 || j >= 0x100)
					break;
				mapdata[i] = j;
				if (value == 0)
					break;
			}
			if (mapdata[MapName::Mapping_DS5_1] && mapdata[MapName::Mapping_ButtonID]) {
				Mapping btn;
				btn.Enable = mapdata[MapName::Mapping_Enable] == 1;
				btn.vJoyID = (vJoyButtonID)mapdata[MapName::Mapping_ButtonID];
				btn.Force = mapdata[MapName::Mapping_ForceOption] == 1;
				btn.Toggle = mapdata[MapName::Mapping_Toggle] == 1;
				btn.DS5ID[0] = (DS5ButtonID) mapdata[MapName::Mapping_DS5_1];
				btn.DS5ID[1] = (DS5ButtonID) mapdata[MapName::Mapping_DS5_2];
				btn.DS5ID[2] = (DS5ButtonID) mapdata[MapName::Mapping_DS5_3];
				btn.DS5ID[3] = (DS5ButtonID) mapdata[MapName::Mapping_DS5_4];
				btn.Disbale[0] = mapdata[MapName::Mapping_DS5_1_Disable] == 1;
				btn.Disbale[1] = mapdata[MapName::Mapping_DS5_2_Disable] == 1;
				btn.Disbale[2] = mapdata[MapName::Mapping_DS5_3_Disable] == 1;
				btn.Disbale[3] = mapdata[MapName::Mapping_DS5_4_Disable] == 1;
				Mappingdata.push_back(std::move(btn));
			}
			key = head;
		}
	}

	head = buf;
	ret = GetPrivateProfileSectionW(L"RapidFire", buf, n, m_file);
	if (ret > 0 && ret - 2 != n) {
		WCHAR *key = head, *value;
		while (*key != 0) {
			head += lstrlenW(key) + 1;
			value = wcschr(key, L'=');
			if (value == 0)
				break;
			*value++ = 0;
			int btnid = _wtoi(key);
			if (btnid <= vJoyButtonID::none || btnid >= vJoyButtonID::button_Count)
				break;

			int data[RapidFireName::RapidFire_Count] = { 0 };
			for (int i = 0; i < RapidFireName::RapidFire_Count; i++) {
				key = value;
				value = wcschr(key, L',');
				if (value != 0)
					*value++ = 0;
				int j = _wtoi(key);
				if (j < 0 || j >= 0x100)
					break;
				data[i] = j;
				if (value == 0)
					break;
			}
			RapidFire _rf;
			_rf.Enable = data[RapidFireName::RapidFire_Enable] == 1;
			_rf.ButtonID = (vJoyButtonID)btnid;
			_rf.Firsttime = data[RapidFireName::RapidFire_First];
			_rf.Releasetime = data[RapidFireName::RapidFire_Release];
			_rf.Presstime = data[RapidFireName::RapidFire_Press];
			_rf.ButtonID2 = (vJoyButtonID)data[RapidFireName::RapidFire_Button2];
			RapidFiredata[_rf.ButtonID] = std::move(_rf);
			
			key = head;
		}
	}

	free(buf);
}

void Settings::Save()
{
	WritePrivateProfileString(TEXT("settings"), TEXT("DisconnectBT"), DisconnectBT ? L"1" : L"0", m_file);
	WritePrivateProfileString(TEXT("settings"), TEXT("FFB"), FFB ? L"1" : L"0", m_file);
	WritePrivateProfileString(TEXT("settings"), TEXT("Tasktray"), Tasktray ? L"1" : L"0", m_file);
	WritePrivateProfileString(TEXT("settings"), TEXT("SplitTouchPad"), SplitTouchPad ? L"1" : L"0", m_file);

	WCHAR buffer[20];
	wsprintf(buffer, L"%d", TouchPadButton);
	WritePrivateProfileString(TEXT("settings"), TEXT("TouchPadButton"), buffer, m_file);

	wsprintf(buffer, L"%d", TouchCol);
	WritePrivateProfileString(TEXT("settings"), TEXT("TouchCol"), buffer, m_file);

	wsprintf(buffer, L"%d", TouchRow);
	WritePrivateProfileString(TEXT("settings"), TEXT("TouchRow"), buffer, m_file);

	wsprintf(buffer, L"%d", LED_Color);
	WritePrivateProfileString(TEXT("settings"), TEXT("LED_Color"), buffer, m_file);

	WritePrivateProfileString(TEXT("settings"), TEXT("DS5Serial"), m_serial, m_file);

	wsprintf(buffer, L"%d", vJoyDeviceID);
	WritePrivateProfileString(TEXT("settings"), TEXT("vJoyDeviceID"), buffer, m_file);



	const int n = sizeof(WCHAR) * 32 * 1024;
	WCHAR *buf = (WCHAR*)malloc(n);
	if (buf == 0)
		return;
	memset(buf, 0, n);
	WCHAR *head = buf;
	size_t max = Keymapdata.size();
	for (int i = 0; i < max; ++i ) {
		Keymap *_keymap = &Keymapdata[i];
		if (_keymap->vk.empty())
			continue;
		head += wsprintf(head, L"%d=%d,", _keymap->ButtonID, _keymap->Enable?1:0  );
		for (auto itr = _keymap->vk.begin(); itr != _keymap->vk.end(); ++itr) {
			if (*itr == 0)
				break;
			head += wsprintf(head, L"%d,", *itr);
		}
		head++;
		if (_keymap->usePostmessage) {
			head += wsprintf(head, L"usePM%d=1", _keymap->ButtonID);
			head++;
		}
		head += wsprintf(head, L"fw%d=%s", _keymap->ButtonID, _keymap->findWindow.Val().c_str());
		head++;
	}
	WritePrivateProfileSection(L"Keymap", buf, m_file);

	memset(buf, 0, n);
	head = buf;
	size_t length = Mappingdata.size();
	for (int i = 0; i < length; i++) {
		int mapdata[MapName::Mapping_Count] = { 0 };
		Mapping *btn = &Mappingdata[i];
		mapdata[MapName::Mapping_Enable] = btn->Enable;
		mapdata[MapName::Mapping_ButtonID] = btn->vJoyID;
		mapdata[MapName::Mapping_DS5_1] = btn->DS5ID[0];
		mapdata[MapName::Mapping_DS5_2] = btn->DS5ID[1];
		mapdata[MapName::Mapping_DS5_3] = btn->DS5ID[2];
		mapdata[MapName::Mapping_DS5_4] = btn->DS5ID[3];
		mapdata[MapName::Mapping_DS5_1_Disable] = btn->Disbale[0];
		mapdata[MapName::Mapping_DS5_2_Disable] = btn->Disbale[1];
		mapdata[MapName::Mapping_DS5_3_Disable] = btn->Disbale[2];
		mapdata[MapName::Mapping_DS5_4_Disable] = btn->Disbale[3];
		mapdata[MapName::Mapping_ForceOption] = btn->Force;
		mapdata[MapName::Mapping_Toggle] = btn->Toggle;
		head += wsprintf(head, L"%d=", i+1);
		for (int j=0; j<MapName::Mapping_Count; j++) {
			head += wsprintf(head, L"%d,",mapdata[j]);
		}
		head++;
	}
	WritePrivateProfileSection(L"Mapping", buf, m_file);


	memset(buf, 0, n);
	head = buf;
	for (auto itr = RapidFiredata.begin(); itr != RapidFiredata.end(); ++itr) {

		int data[RapidFireName::RapidFire_Count] = { 0 };
		RapidFire *_repeat = &itr->second;
		data[RapidFireName::RapidFire_Enable] = _repeat->Enable;
		data[RapidFireName::RapidFire_First] = _repeat->Firsttime;
		data[RapidFireName::RapidFire_Release] = _repeat->Releasetime;
		data[RapidFireName::RapidFire_Press] = _repeat->Presstime;
		data[RapidFireName::RapidFire_Button2] = _repeat->ButtonID2;

		head += wsprintf(head, L"%d=", _repeat->ButtonID);
		for (int j = 0; j<RapidFireName::RapidFire_Count; j++) {
			head += wsprintf(head, L"%d,", data[j]);
		}
		head++;
	}
	WritePrivateProfileSection(L"RapidFire", buf, m_file);

	free(buf);
}

void Settings::SetTouchRow( int i)
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

void Settings::SetTouchPadButton(DWORD n)
{
	if (n <= 128) {
		TouchPadButton = n;
	}
	else {
		TouchPadButton = 0;
	}
}

void Settings::SetLED_Color(DWORD i)
{
	if (i >= 0 && i <= 0xFFFFFF) {
		LED_Color = i;
	}
}

const WCHAR * Settings::getSerial()
{
	return m_serial;
}

void Settings::setSerial(const WCHAR *buf)
{
	lstrcpynW(m_serial, buf, sizeof(m_serial) / sizeof(m_serial[0]) );
}

void Settings::setvJoyDeviceID(int id)
{
	if (id > 0 && id < 17) {
		vJoyDeviceID = id;
	}
	else {
		vJoyDeviceID = 1;
	}
}

Settings::~Settings()
{
}
