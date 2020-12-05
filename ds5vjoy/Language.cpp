#include "stdafx.h"
#include "Language.h"
#include "Resource.h"

struct LANGSTRS I18N = { 0 };

WCHAR * GetText(int _id, WCHAR* txt) {
	WCHAR buffer[1024];
	int len = LoadStringW(hInst, _id, buffer, 1024);
	WCHAR *ret;
	if (len == 0) {
		ret = new WCHAR[lstrlenW(txt) + 1];
		lstrcpyW(ret, txt);
	}
	else {
		ret = new WCHAR[lstrlenW(buffer) + 1];
		lstrcpyW(ret, buffer);
	}
	return ret;
}


void LoadLanguage() {
	I18N.APP_TITLE = GetText(IDS_APP_TITLE, L"ds5vjoy");
	I18N.SkipController = GetText(IDS_SKIPCONTROLLER, L"Skip %s Serial %s");
	I18N.ConnectController = GetText(IDS_CONNECTCONTROLLER, L"Connect %s Serial %s");
	I18N.FailedCreateThread = GetText(IDS_FAILEDTHREAD, L"Failed to create thread");
	I18N.DisconnectController = GetText(IDS_DISCONNECTCONTROLLER, L"Disconnect %s");
	I18N.FailedParse = GetText(IDS_FAILEDPARSE, L"Failed to parse %s");
	I18N.ConnectionStarted = GetText(IDS_CONNECTIONSTARTED, L"Connection started %s");
	I18N.FailedSendCmd = GetText(IDS_FAILEDSENDCMD, L"Failed to send command to %s : %d");
	I18N.DeviceNotConnected = GetText(IDS_ERROR_DEVICE_NOT_CONNECTED, L"%s device is not connected.");
	I18N.FailedRecv = GetText(IDS_FAILEDRECV, L"Failed to recv data from %s : %d");
	I18N.Button_SQUARE = GetText(IDS_BUTTON_SQUARE, L"Å†");
	I18N.Button_TRIANGLE = GetText(IDS_BUTTON_TRIANGLE, L"Å¢");
	I18N.Button_CROSS = GetText(IDS_BUTTON_CROSS, L"Å~");
	I18N.Button_CIRCLE = GetText(IDS_BUTTON_CIRCLE, L"Åõ");
	I18N.Button_L1 = GetText(IDS_BUTTON_L1, L"L1");
	I18N.Button_R1 = GetText(IDS_BUTTON_R1, L"R1");
	I18N.Button_L2 = GetText(IDS_BUTTON_L2, L"L2");
	I18N.Button_R2 = GetText(IDS_BUTTON_R2, L"R2");
	I18N.Button_L3 = GetText(IDS_BUTTON_L3, L"L3");
	I18N.Button_R3 = GetText(IDS_BUTTON_R3, L"R3");
	I18N.Button_SHARE = GetText(IDS_BUTTON_SHARE, L"SHARE");
	I18N.Button_CREATE = GetText(IDS_BUTTON_CREATE, L"CREATE");
	I18N.Button_MUTE = GetText(IDS_BUTTON_MUTE, L"MUTE");
	I18N.Button_OPTIONS = GetText(IDS_BUTTON_OPTIONS, L"OPTIONS");
	I18N.Button_PS = GetText(IDS_BUTTON_PS, L"PS");
	I18N.Button_TOUCH = GetText(IDS_BUTTON_TOUCH, L"TouchPad");
	I18N.Button_LX = GetText(IDS_BUTTON_LX, L"LX");
	I18N.Button_LY = GetText(IDS_BUTTON_LY, L"LY");
	I18N.Button_RX = GetText(IDS_BUTTON_RX, L"RX");
	I18N.Button_RY = GetText(IDS_BUTTON_RY, L"RY");
	I18N.Button_L2TRIGGER = GetText(IDS_BUTTON_L2TRIGGER, L"L2Trigger");
	I18N.Button_R2TRIGGER = GetText(IDS_BUTTON_R2TRIGGER, L"R2Trigger");
	I18N.Button_DPAD = GetText(IDS_BUTTON_DPAD, L"D-pad");
	I18N.Button_DPAD_UP = GetText(IDS_BUTTON_DPAD_UP, L"Å™");
	I18N.Button_DPAD_RIGHT = GetText(IDS_BUTTON_DPAD_RIGHT, L"Å®");
	I18N.Button_DPAD_DOWN = GetText(IDS_BUTTON_DPAD_DOWN, L"Å´");
	I18N.Button_DPAD_LEFT = GetText(IDS_BUTTON_DPAD_LEFT, L"Å©");
	I18N.MBOX_Save = GetText(IDS_MBOX_Save, L"Save?");
	I18N.MBOX_Delete = GetText(IDS_MBOX_Delete, L"Are you sure you want to delete the selected item?");
	I18N.MBOX_ErrTitle = GetText(IDS_MBOX_ErrTitle, L"Error");
	I18N.MBOX_NoButtonSelected = GetText(IDS_MBOX_NOBUTTONSELECTED, L"No button selected");
	I18N.DS5Button = GetText(IDS_DS5_BUTTON, L"DS5 Button");
	I18N.vJoyButton= GetText(IDS_VJOY_BUTTON, L"vJoy Button");
	I18N.Rapidfire_State = GetText(IDS_RAPIDFIRE_STATE, L"First:%dms UP:%dms DOWN:%dms");
	I18N.Rapidfire_if_down = GetText(IDS_RAPIDFIRE_IFDOWN, L" (if %s is down)");
	I18N.Setting = GetText(IDS_SETTING, L"Setting");
	I18N.vJoy_please_install = GetText(IDS_VJOY_PLZ_INST, L"Please install vJoy");
	I18N.vJoy_version = GetText(IDS_VJOY_VERSION, L"vJoy version %d.%d.%d");
	I18N.vJoy_version_notmatch = GetText(IDS_VJOY_NOMATCH, L"vJoy version not match. DLL(%d.%d.%d) Driver(%d.%d.%d)");
	I18N.vJoy_busy= GetText(IDS_VJOY_BUSY, L"vJoy(ID:%d) is busy");
	I18N.vJoy_cantuse = GetText(IDS_VJOY_CANT_USE, L"can not use vJoy(ID:%d) ");
	I18N.vJoy_failed_acquire = GetText(IDS_VJOY_FAILED_ACQUIRE, L"Failed to acquire vJoy(ID:%d)");
	I18N.vJoy_acquire = GetText(IDS_VJOY_ACQUIRE, L"Acquired vJoy(ID:%d)");
	I18N.vJoy_failed_update = GetText(IDS_VJOY_FAILED_UPDATE, L"Failed to update vJoy(ID:%d)");
	I18N.tabLog = GetText(IDS_TAB_LOG, L"Log");
	I18N.tabSettings = GetText(IDS_TAB_SETTINGS, L"Settings");
	I18N.tabMapping = GetText(IDS_TAB_MAPPING, L"Mapping");
	I18N.tabRapidfire = GetText(IDS_TAB_RAPIDFIRE, L"RapidFire");
	I18N.tabKeymap = GetText(IDS_TAB_KEYMAP, L"Keymap");
	I18N.status_wait = GetText(IDS_STATUS_WAIT, L"waiting");
	I18N.log_wait_vjoy = GetText(IDS_LOG_WAIT_VJOY, L"Waiting for a valid vJoy device.");
	I18N.log_wait_ds5 = GetText(IDS_LOG_WAIT_DS5, L"Waiting for a valid DS5 device.");
	I18N.log_change_settings = GetText(IDS_LOG_CHANGE_SETTINGS, L"Reconnecting for change settings.");
}


void FreeLanguage() {
	if (I18N.SkipController == 0)
		return;
	delete[] I18N.APP_TITLE;
	delete[] I18N.SkipController;
	delete[] I18N.ConnectController;
	delete[] I18N.FailedCreateThread;
	delete[] I18N.DisconnectController;
	delete[] I18N.FailedParse;
	delete[] I18N.ConnectionStarted;
	delete[] I18N.FailedSendCmd;
	delete[] I18N.DeviceNotConnected;
	delete[] I18N.FailedRecv;
	delete[] I18N.Button_SQUARE;
	delete[] I18N.Button_TRIANGLE;
	delete[] I18N.Button_CROSS;
	delete[] I18N.Button_CIRCLE;
	delete[] I18N.Button_L1;
	delete[] I18N.Button_R1;
	delete[] I18N.Button_L2;
	delete[] I18N.Button_R2;
	delete[] I18N.Button_L3;
	delete[] I18N.Button_R3;
	delete[] I18N.Button_SHARE;
	delete[] I18N.Button_OPTIONS;
	delete[] I18N.Button_PS;
	delete[] I18N.Button_TOUCH;
	delete[] I18N.Button_LX;
	delete[] I18N.Button_LY;
	delete[] I18N.Button_RX;
	delete[] I18N.Button_RY;
	delete[] I18N.Button_L2TRIGGER;
	delete[] I18N.Button_R2TRIGGER;
	delete[] I18N.Button_DPAD;
	delete[] I18N.Button_DPAD_UP;
	delete[] I18N.Button_DPAD_RIGHT;
	delete[] I18N.Button_DPAD_DOWN;
	delete[] I18N.Button_DPAD_LEFT;
	delete[] I18N.MBOX_Save;
	delete[] I18N.MBOX_Delete;
	delete[] I18N.MBOX_ErrTitle;
	delete[] I18N.MBOX_NoButtonSelected;
	delete[] I18N.DS5Button;
	delete[] I18N.vJoyButton;
	delete[] I18N.Rapidfire_State;
	delete[] I18N.Rapidfire_if_down;
	delete[] I18N.Setting;
	delete[] I18N.vJoy_please_install;
	delete[] I18N.vJoy_version;
	delete[] I18N.vJoy_version_notmatch;
	delete[] I18N.vJoy_busy;
	delete[] I18N.vJoy_cantuse;
	delete[] I18N.vJoy_failed_acquire;
	delete[] I18N.vJoy_acquire;
	delete[] I18N.vJoy_failed_update;
	delete[] I18N.tabLog;
	delete[] I18N.tabSettings;
	delete[] I18N.tabMapping;
	delete[] I18N.tabRapidfire;
	delete[] I18N.tabKeymap;
	delete[] I18N.status_wait;
	delete[] I18N.log_wait_vjoy;
	delete[] I18N.log_wait_ds5;
	delete[] I18N.log_change_settings;

}

