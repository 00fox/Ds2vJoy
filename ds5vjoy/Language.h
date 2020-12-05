#pragma once

struct LANGSTRS {
	WCHAR *APP_TITLE;
	WCHAR *SkipController;
	WCHAR *ConnectController;
	WCHAR *FailedCreateThread;
	WCHAR *DisconnectController;
	WCHAR *FailedParse;
	WCHAR *ConnectionStarted;
	WCHAR *FailedSendCmd;
	WCHAR *DeviceNotConnected;
	WCHAR *FailedRecv;
	WCHAR *Button_SQUARE;
	WCHAR *Button_TRIANGLE;
	WCHAR *Button_CROSS;
	WCHAR *Button_CIRCLE;
	WCHAR *Button_L1;
	WCHAR *Button_R1;
	WCHAR *Button_L2;
	WCHAR *Button_R2;
	WCHAR *Button_L3;
	WCHAR *Button_R3;
	WCHAR *Button_SHARE;
	WCHAR *Button_OPTIONS;
	WCHAR *Button_PS;
	WCHAR *Button_TOUCH;
	WCHAR *Button_LX;
	WCHAR *Button_LY;
	WCHAR *Button_RX;
	WCHAR *Button_RY;
	WCHAR *Button_L2TRIGGER;
	WCHAR *Button_R2TRIGGER;
	WCHAR *Button_DPAD;
	WCHAR *Button_DPAD_UP;
	WCHAR *Button_DPAD_RIGHT;
	WCHAR *Button_DPAD_DOWN;
	WCHAR *Button_DPAD_LEFT;
	WCHAR *Button_CREATE;
	WCHAR *Button_MUTE;
	WCHAR *MBOX_Save;
	WCHAR *MBOX_Delete;
	WCHAR *MBOX_ErrTitle;
	WCHAR *MBOX_NoButtonSelected;
	WCHAR *DS5Button;
	WCHAR *vJoyButton;
	WCHAR *Rapidfire_State;
	WCHAR *Rapidfire_if_down;
	WCHAR *Setting;
	WCHAR *vJoy_please_install;
	WCHAR *vJoy_version;
	WCHAR *vJoy_version_notmatch;
	WCHAR *vJoy_busy;
	WCHAR *vJoy_cantuse;
	WCHAR *vJoy_failed_acquire;
	WCHAR *vJoy_acquire;
	WCHAR *vJoy_failed_update;
	WCHAR *tabLog;
	WCHAR *tabSettings;
	WCHAR *tabMapping;
	WCHAR *tabRapidfire;
	WCHAR *tabKeymap;
	WCHAR *status_wait;
	WCHAR *log_wait_vjoy;
	WCHAR *log_wait_ds5;
	WCHAR *log_change_settings;
};

void LoadLanguage();
void FreeLanguage();

extern HINSTANCE hInst;
extern struct LANGSTRS I18N;


