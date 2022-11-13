#include "stdafx.h"
#include "SettingDlg.h"

SettingDlg::SettingDlg()
{
}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::Init()
{
	m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_SETTINGS), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));
	Hide();
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_SOURCES, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS4_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS4, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS5_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS5, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DI_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DI, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_XI_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_XI, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_KBD_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_KBD, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_MSE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_MSE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_COUNTRY, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_COUNTRY_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_COUNTRY, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_VJ_DEVICE, WM_SETFONT, WPARAM(tape.hStatic3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_VJ_DEVICE_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_VJ_DEVICE, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_XI_DEVICE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_XI_DEVICE_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_XI_DEVICE, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_STARTUP_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_STARTUP, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_START_MINIMIZED_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_START_MINIMIZED, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_CLOSE_MINIMIZE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_CLOSE_MINIMIZE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DISCONNECT_BT_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DISCONNECT_BT, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_MOUSE_CAN_BYPASS_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_MOUSE_CAN_BYPASS, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_ALERT_ON_LOWBATTS_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_ALERT_ON_LOWBATTS, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TRIGGERS_MODE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TRIGGERS_NONE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TRIGGERS_NONE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TRIGGERS_SHOOT_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TRIGGERS_SHOOT, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TRIGGERS_RESIST_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TRIGGERS_RESIST, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TRIGGERS_PROACTIVE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TRIGGERS_PROACTIVE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_DS_SERIAL, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS_SERIAL, WM_SETFONT, WPARAM(tape.hCombo2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DI_DEVICE_1, WM_SETFONT, WPARAM(tape.hStatic2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DI_DEVICE_2, WM_SETFONT, WPARAM(tape.hStatic2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_DI_DEVICE, WM_SETFONT, WPARAM(tape.hStatic3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DI_DEVICE_RELOAD, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DI_DEVICE_STATIC, WM_SETFONT, WPARAM(tape.hCombo2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DI_DEVICE, WM_SETFONT, WPARAM(tape.hSerial), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DI_DEVICE_CLEAR, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DARK_THEME_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DARK_THEME, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_THRESHOLD, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_SIMULTANEOUS, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_LONG, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_VERY_LONG, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_WEBREFRESH, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_OPACITY, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_UNIT_THRESHOLD, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_UNIT_SIMULTANEOUS, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_UNIT_LONG, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_UNIT_VERY_LONG, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_UNIT_WEB_REFRESH, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_UNIT_OPACITY, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_THRESHOLD, WM_SETFONT, WPARAM(tape.hLegend), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_SIMULTANEOUS, WM_SETFONT, WPARAM(tape.hLegend), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_LONG, WM_SETFONT, WPARAM(tape.hLegend), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_VERY_LONG, WM_SETFONT, WPARAM(tape.hLegend), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_WEBREFRESH, WM_SETFONT, WPARAM(tape.hLegend), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_OPACITY, WM_SETFONT, WPARAM(tape.hLegend), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_MULTIPLE_TOUCHPAD, WM_SETFONT, WPARAM(tape.hLegend3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_FIRST_BUTTON, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_COLUMNS, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_ROWS, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_FIRST_BUTTON_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_FIRST_BUTTON, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_COLUMNS_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_COLUMNS, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_ROWS_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_ROWS, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_VJOY_SHUTDOWN_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_VJOY_SHUTDOWN, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_ON_EXIT, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_LED_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_LED, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_WHEN_EXITING2, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_SLIDER, WM_SETFONT, WPARAM(tape.hSlider), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_SOURCES), I18N.SETTINGS_SOURCES);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DS4), I18N.SETTINGS_DS4);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DS5), I18N.SETTINGS_DS5);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DI), I18N.SETTINGS_DI);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_XI), I18N.SETTINGS_XI);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_KBD), I18N.SETTINGS_KBD);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_MSE), I18N.SETTINGS_MSE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_COUNTRY), I18N.SETTINGS_COUNTRY);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_VJ_DEVICE), I18N.SETTINGS_TEXT_VJ_DEVICE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_XI_DEVICE), I18N.SETTINGS_TEXT_XI_DEVICE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_STARTUP), I18N.SETTINGS_STARTUP);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_START_MINIMIZED), I18N.SETTINGS_START_MINIMIZED);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_CLOSE_MINIMIZE), I18N.SETTINGS_CLOSE_MINIMIZE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DISCONNECT_BT), I18N.SETTINGS_DISCONNECT_BT);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_MOUSE_CAN_BYPASS), I18N.SETTINGS_MOUSE_CAN_BYPASS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_ALERT_ON_LOWBATTS), I18N.SETTINGS_ALERT_ON_LOWBATTS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TRIGGERS_MODE), I18N.SETTINGS_TRIGGERS_MODE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TRIGGERS_NONE), I18N.SETTINGS_TRIGGERS_NONE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TRIGGERS_SHOOT), I18N.SETTINGS_TRIGGERS_SHOOT);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TRIGGERS_RESIST), I18N.SETTINGS_TRIGGERS_RESIST);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TRIGGERS_PROACTIVE), I18N.SETTINGS_TRIGGERS_PROACTIVE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_DS_SERIAL), I18N.SETTINGS_TEXT_DS_SERIAL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DI_DEVICE_1), I18N.SETTINGS_DI_DEVICE_1);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DI_DEVICE_2), I18N.SETTINGS_DI_DEVICE_2);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DI_DEVICE_RELOAD), I18N.SETTINGS_DI_DEVICE_RELOAD);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_DI_DEVICE), I18N.SETTINGS_TEXT_DI_DEVICE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DI_DEVICE_CLEAR), I18N.SETTINGS_DI_DEVICE_CLEAR);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DARK_THEME), I18N.SETTINGS_DARK_THEME);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_THRESHOLD), I18N.SETTINGS_TEXT_THRESHOLD);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_SIMULTANEOUS), I18N.SETTINGS_TEXT_SIMULTANEOUS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_LONG), I18N.SETTINGS_TEXT_LONG);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_VERY_LONG), I18N.SETTINGS_TEXT_VERY_LONG);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_WEBREFRESH), I18N.SETTINGS_TEXT_WEBREFRESH);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_OPACITY), I18N.SETTINGS_TEXT_OPACITY);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_UNIT_THRESHOLD), I18N.SETTINGS_UNIT_THRESHOLD);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_UNIT_SIMULTANEOUS), I18N.SETTINGS_UNIT_SIMULTANEOUS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_UNIT_LONG), I18N.SETTINGS_UNIT_LONG);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_UNIT_VERY_LONG), I18N.SETTINGS_UNIT_VERY_LONG);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_UNIT_WEB_REFRESH), I18N.SETTINGS_UNIT_WEB_REFRESH);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_UNIT_OPACITY), I18N.SETTINGS_UNIT_OPACITY);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_MULTIPLE_TOUCHPAD), I18N.SETTINGS_MULTIPLE_TOUCHPAD);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_FIRST_BUTTON), I18N.SETTINGS_TEXT_FIRST_BUTTON);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_COLUMNS), I18N.SETTINGS_TEXT_COLUMNS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_ROWS), I18N.SETTINGS_TEXT_ROWS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_VJOY_SHUTDOWN), I18N.SETTINGS_VJOY_SHUTDOWN);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_ON_EXIT), I18N.SETTINGS_ON_EXIT);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_LED), I18N.SETTINGS_LED);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_WHEN_EXITING2), I18N.SETTINGS_WHEN_EXITING);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_COLOR), I18N.SETTINGS_COLOR);

	::SetWindowTheme(GetDlgItem(m_hDlg, IDC_SETTINGS_MULTIPLE_TOUCHPAD), L"", L"");

	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_SETTINGS_MSE_CHK), I18N.HELP_SETTINGS_MOUSE);
}

void SettingDlg::_InitDialog(HWND hWnd)
{
	for (int i = 0; i < CountryID::Country_Count; i++)
	{
		if (tape.InstalledLanguage[i])
			SendDlgItemMessage(hWnd, IDC_SETTINGS_COUNTRY, CB_ADDSTRING, 0, LPARAM(Settings::CountryString((CountryID)i)));
		else
			SendDlgItemMessage(hWnd, IDC_SETTINGS_COUNTRY, CB_ADDSTRING, 0, LPARAM(L"--"));
	}

	SendDlgItemMessage(hWnd, IDC_SETTINGS_VJ_DEVICE, CB_ADDSTRING, 0, LPARAM(I18N.NONE));
	for (int i = 1; i < 16; i++)
	{
		WCHAR buf[10];
		swprintf_s(buf, 10, L"%d", i);
		SendDlgItemMessage(hWnd, IDC_SETTINGS_VJ_DEVICE, CB_ADDSTRING, 0, LPARAM(buf));
	}

	for (int i = 1; i < 5; i++)
	{
		WCHAR buf[10];
		swprintf_s(buf, 10, L"%d", i);
		SendDlgItemMessage(hWnd, IDC_SETTINGS_XI_DEVICE, CB_ADDSTRING, 0, LPARAM(buf));
	}

	SendDlgItemMessage(hWnd, IDC_SETTINGS_FIRST_BUTTON, CB_ADDSTRING, 0, LPARAM(L""));
	for (int i = 1; i <= 128; i++)
	{
		WCHAR buf[10];
		swprintf_s(buf, 10, L"%d", i);
		SendDlgItemMessage(hWnd, IDC_SETTINGS_FIRST_BUTTON, CB_ADDSTRING, 0, LPARAM(buf));
	}

	for (int i = 1; i < 10; i++)
	{
		WCHAR buf[10];
		swprintf_s(buf, 10, L"%d", i);
		SendDlgItemMessage(hWnd, IDC_SETTINGS_COLUMNS, CB_ADDSTRING, 0, LPARAM(buf));
		SendDlgItemMessage(hWnd, IDC_SETTINGS_ROWS, CB_ADDSTRING, 0, LPARAM(buf));
	}

	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd;
	cc.lpCustColors = CustColors;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	SendDlgItemMessage(hWnd, IDC_SETTINGS_SLIDER, TBM_SETRANGE, FALSE, MAKELONG(0, 166));
	SendDlgItemMessage(hWnd, IDC_SETTINGS_SLIDER, TBM_SETPOS, TRUE, tape.WaveSpeed);

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void SettingDlg::_ShowWindow(HWND hWnd)
{
	CheckDlgButton(hWnd, IDC_SETTINGS_DS4_CHK, tape.PreferredSource == 1);
	CheckDlgButton(hWnd, IDC_SETTINGS_DS5_CHK, tape.PreferredSource == 2);
	CheckDlgButton(hWnd, IDC_SETTINGS_DI_CHK, tape.PreferredSource == 3);
	CheckDlgButton(hWnd, IDC_SETTINGS_XI_CHK, tape.PreferredSource == 4);
	CheckDlgButton(hWnd, IDC_SETTINGS_KBD_CHK, tape.KeyboardActive);
	CheckDlgButton(hWnd, IDC_SETTINGS_MSE_CHK, tape.MouseActive);
	CheckDlgButton(hWnd, IDC_SETTINGS_VJOY_SHUTDOWN_CHK, tape.vJoyShutDown);

	SendDlgItemMessage(hWnd, IDC_SETTINGS_COUNTRY, CB_SETCURSEL, LPARAM(tape.Country), 0);
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_COUNTRY_STATIC), Settings::CountryString((CountryID)tape.Country));

	SendDlgItemMessage(hWnd, IDC_SETTINGS_VJ_DEVICE, CB_SETCURSEL, LPARAM(tape.vJoyDevice), 0);
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_VJ_DEVICE_STATIC), (tape.vJoyDevice) ? std::to_wstring(tape.vJoyDevice).c_str() : L"...");

	SendDlgItemMessage(hWnd, IDC_SETTINGS_XI_DEVICE, CB_SETCURSEL, LPARAM(tape.XInputDevice), 0);
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_XI_DEVICE_STATIC), std::to_wstring(tape.XInputDevice + 1).c_str());

	SendMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_LIST, 0, 0);
	SendDlgItemMessage(hWnd, IDC_SETTINGS_DI_DEVICE, CB_RESETCONTENT, 0, 0);
	for (int i = 0; i < tape.DevicesList.size(); i++)
	{
		WCHAR buf[MAX_PATH];
		swprintf_s(buf, MAX_PATH, L"  VID:%04hX  PID:%04hX  UID:%s -> %s", tape.DevicesList[i].vid, tape.DevicesList[i].pid, tape.DevicesList[i].uid.c_str(), tape.DevicesList[i].pname.c_str());
		SendDlgItemMessage(hWnd, IDC_SETTINGS_DI_DEVICE, CB_ADDSTRING, 0, LPARAM(buf));
	}
	if (m_device)
		SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), (wcslen(tape.Device2)) ? tape.Device2 : L". . .");
	else
		SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), (wcslen(tape.Device1)) ? tape.Device1 : L". . .");

	bool startupvalue = false;
	{
		HKEY hkey = NULL;
		BOOL bExist = FALSE;
		int openStatus = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &hkey);
		if (openStatus == ERROR_SUCCESS)
		{
			DWORD dwType;
			int status = RegQueryValueEx(hkey, L"Ds2vJoy", NULL, &dwType, NULL, NULL);
			if (status == ERROR_SUCCESS)
				startupvalue = true;
			RegCloseKey(hkey);
		}
	}
	CheckDlgButton(hWnd, IDC_SETTINGS_STARTUP_CHK, startupvalue);
	CheckDlgButton(hWnd, IDC_SETTINGS_START_MINIMIZED_CHK, tape.Tasktray);
	CheckDlgButton(hWnd, IDC_SETTINGS_CLOSE_MINIMIZE_CHK, tape.CloseMinimize);
	CheckDlgButton(hWnd, IDC_SETTINGS_DISCONNECT_BT_CHK, tape.DisconnectBT);
	CheckDlgButton(hWnd, IDC_SETTINGS_MOUSE_CAN_BYPASS_CHK, tape.MouseCanBypass);
	CheckDlgButton(hWnd, IDC_SETTINGS_ALERT_ON_LOWBATTS_CHK, tape.LowBattAlert);
	CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_NONE_CHK, tape.TriggersMode == 0);
	CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_SHOOT_CHK, tape.TriggersMode == 2);
	CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_RESIST_CHK, tape.TriggersMode == 1);
	CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_PROACTIVE_CHK, tape.TriggersMode == 3);
	CheckDlgButton(hWnd, IDC_SETTINGS_DARK_THEME_CHK, tape.DarkTheme);

	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_DS_SERIAL), tape.Serial);
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_THRESHOLD), WCHARI(20, L"%d", (tape.Threshold / 257)));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_SIMULTANEOUS), WCHARI(20, L"%d", tape.Simultaneous));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_LONG), WCHARI(20, L"%d", tape.LongPress));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_VERY_LONG), WCHARI(20, L"%d", tape.VeryLongPress));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_WEBREFRESH), WCHARI(20, L"%d", tape.WebRefreshTime));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_OPACITY), WCHARI(20, L"%d", tape.Opacity));

	SendDlgItemMessage(hWnd, IDC_SETTINGS_FIRST_BUTTON, CB_SETCURSEL, LPARAM(tape.TouchPadButton), 0);
	SendDlgItemMessage(hWnd, IDC_SETTINGS_COLUMNS, CB_SETCURSEL, LPARAM(tape.TouchRow - 1), 0);
	SendDlgItemMessage(hWnd, IDC_SETTINGS_ROWS, CB_SETCURSEL, LPARAM(tape.TouchCol - 1), 0);

	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_FIRST_BUTTON_STATIC), (tape.TouchPadButton) ? std::to_wstring(tape.TouchPadButton).c_str() : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_COLUMNS_STATIC), std::to_wstring(tape.TouchCol).c_str());
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_ROWS_STATIC), std::to_wstring(tape.TouchRow).c_str());

	cc.rgbResult = tape.LED_Color;
	CheckDlgButton(hWnd, IDC_SETTINGS_LED_CHK, tape.BlackLedOnExit);
}

INT_PTR CALLBACK SettingDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SettingDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<SettingDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<SettingDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR SettingDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CTLCOLORDLG:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_DLG);
		SetTextColor(hdcStatic, tape.ink_DLG);
		return (LRESULT)tape.hB_DLG;
	}
	case WM_CTLCOLORMSGBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_MSGBOX);
		SetTextColor(hdcStatic, tape.ink_MSGBOX);
		return (LRESULT)tape.hB_MSGBOX;
	}
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_BTN);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_BTN);
		if (tape.DarkTheme)
			return (LRESULT)tape.hB_BTN_DARK;
		else
			return (LRESULT)tape.hB_BTN;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		switch (GetDlgCtrlID((HWND)lParam))
		{
		case IDC_SETTINGS_DS4:
		case IDC_SETTINGS_DS5:
		case IDC_SETTINGS_DI:
		case IDC_SETTINGS_XI:
		case IDC_SETTINGS_KBD:
		case IDC_SETTINGS_MSE:
		case IDC_SETTINGS_COUNTRY_STATIC:
		case IDC_SETTINGS_VJ_DEVICE_STATIC:
		case IDC_SETTINGS_XI_DEVICE_STATIC:
		case IDC_SETTINGS_STARTUP:
		case IDC_SETTINGS_START_MINIMIZED:
		case IDC_SETTINGS_CLOSE_MINIMIZE:
		case IDC_SETTINGS_DISCONNECT_BT:
		case IDC_SETTINGS_MOUSE_CAN_BYPASS:
		case IDC_SETTINGS_ALERT_ON_LOWBATTS:
		case IDC_SETTINGS_TRIGGERS_NONE:
		case IDC_SETTINGS_TRIGGERS_SHOOT:
		case IDC_SETTINGS_TRIGGERS_RESIST:
		case IDC_SETTINGS_TRIGGERS_PROACTIVE:
		case IDC_SETTINGS_DARK_THEME:
		case IDC_SETTINGS_LED:
		case IDC_SETTINGS_WHEN_EXITING2:
		case IDC_SETTINGS_TEXT_FIRST_BUTTON:
		case IDC_SETTINGS_TEXT_COLUMNS:
		case IDC_SETTINGS_TEXT_ROWS:
		case IDC_SETTINGS_FIRST_BUTTON_STATIC:
		case IDC_SETTINGS_COLUMNS_STATIC:
		case IDC_SETTINGS_ROWS_STATIC:
		case IDC_SETTINGS_VJOY_SHUTDOWN:
		case IDC_SETTINGS_ON_EXIT:
		{
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_CHK_DARK);
				return (LRESULT)tape.hB_BackGround_DARK;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_CHK);
				return (LRESULT)tape.hB_BackGround;
			}
			break;
		}
		case IDC_SETTINGS_DI_DEVICE_STATIC:
		{
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_CHK_DARK);
				return (LRESULT)tape.hB_EDIT_DARK2;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_CHK);
				return (LRESULT)tape.hB_EDIT;
			}
			break;
		}
		case IDC_SETTINGS_DS4_CHK:
		case IDC_SETTINGS_DS5_CHK:
		case IDC_SETTINGS_DI_CHK:
		case IDC_SETTINGS_XI_CHK:
		case IDC_SETTINGS_KBD_CHK:
		case IDC_SETTINGS_MSE_CHK:
		case IDC_SETTINGS_VJOY_SHUTDOWN_CHK:
		case IDC_SETTINGS_STARTUP_CHK:
		case IDC_SETTINGS_START_MINIMIZED_CHK:
		case IDC_SETTINGS_CLOSE_MINIMIZE_CHK:
		case IDC_SETTINGS_DISCONNECT_BT_CHK:
		case IDC_SETTINGS_MOUSE_CAN_BYPASS_CHK:
		case IDC_SETTINGS_ALERT_ON_LOWBATTS_CHK:
		case IDC_SETTINGS_TRIGGERS_NONE_CHK:
		case IDC_SETTINGS_TRIGGERS_SHOOT_CHK:
		case IDC_SETTINGS_TRIGGERS_RESIST_CHK:
		case IDC_SETTINGS_TRIGGERS_PROACTIVE_CHK:
		case IDC_SETTINGS_DARK_THEME_CHK:
		case IDC_SETTINGS_LED_CHK:
		{
			SetTextColor(hdcStatic, tape.ink_STATIC);
			if (tape.DarkTheme)
				return (LRESULT)tape.hB_BackGround_DARK;
			else
				return (LRESULT)tape.hB_BackGround;
		}
		default:
		{
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_DARK);
				return (LRESULT)tape.hB_BackGround_DARK;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_STATIC);
				return (LRESULT)tape.hB_BackGround;
			}
			break;
		}
		}
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode((HDC)wParam, TRANSPARENT);
		if (tape.DarkTheme)
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TERMINAL);
			return (LRESULT)tape.hB_EDIT_DARK;
		}
		else
		{
			SetTextColor(hdcStatic, tape.ink_EDIT);
			return (LRESULT)tape.hB_EDIT;
		}
	}
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		if (tape.DarkTheme)
		{
			SetTextColor(hdcStatic, tape.ink_COMBO_DARK);
			return (LRESULT)tape.hB_LIST_DARK;
		}
		else
		{
			SetTextColor(hdcStatic, tape.ink_COMBO);
			return (LRESULT)tape.hB_LIST;
		}
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			if (tape.DarkTheme)
				FillRect(hDC, &rect, tape.hB_BackGround_DARK);
			else
				FillRect(hDC, &rect, tape.hB_BackGround);

			if (tape.DarkTheme)
			{
				SetRect(&rect, 110, 194, 233, 213);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK3);
				SetRect(&rect, 110, 195, 233, 212);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK);
				SetRect(&rect, 70, 217, 276, 236);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 250, 200, 276, 215);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK2);
			}
			else
			{
				SetRect(&rect, 111, 194, 232, 213);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 110, 195, 233, 212);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 70, 217, 276, 236);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 250, 200, 276, 215);
				FrameRect(hDC, &rect, tape.hB_EDIT);
			}

			if (m_device)
			{
				SetRect(&rect, 263, 197, 276, 199);
				FrameRect(hDC, &rect, tape.hB_bright_yellow);
			}
			else
			{
				SetRect(&rect, 250, 197, 263, 199);
				FrameRect(hDC, &rect, tape.hB_bright_yellow);
			}

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);

			HWND ledbutton = GetDlgItem(hWnd, IDC_SETTINGS_COLOR);
			hDC = BeginPaint(ledbutton, &ps);
			GetClientRect(ledbutton, &rect);

			if (tape.DarkTheme)
				DrawEdge(hDC, &rect, BDR_RAISEDOUTER, BF_RECT | BF_MONO | BF_FLAT | BF_SOFT);
			else
				DrawEdge(hDC, &rect, EDGE_RAISED, BF_RECT);

			rect.top -= 1;
			rect.left -= 1;
			rect.right += 1;
			rect.bottom += 1;
			if (!tape.DarkTheme)
				DrawFocusRect(hDC, &rect);

			rect.top += 4;
			rect.left += 4;
			rect.right -= 4;
			rect.bottom -= 4;
			DWORD ledcolor = tape.LED_Color;
			HBRUSH brush = CreateSolidBrush(RGB(GetRValue(ledcolor), GetGValue(ledcolor), GetBValue(ledcolor)));
			FillRect(hDC, &rect, brush);
			DeleteObject(brush);

			if (GetRValue(ledcolor) + GetGValue(ledcolor) + GetBValue(ledcolor) > 381)
				SetTextColor(hDC, tape.ink_BTN_Heavy);
			else
				SetTextColor(hDC, tape.ink_BTN_Light);

			SelectObject(hDC, tape.hButton);
			DrawText(hDC, I18N.SETTINGS_LED_BUTTON, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			::ReleaseDC(hWnd, hDC);
			EndPaint(ledbutton, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
			std::thread(&SettingDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&SettingDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_SETTINGS_DS4_CHK:
		case IDC_SETTINGS_DS5_CHK:
		case IDC_SETTINGS_DI_CHK:
		case IDC_SETTINGS_XI_CHK:
		case IDC_SETTINGS_KBD_CHK:
		case IDC_SETTINGS_MSE_CHK:
		case IDC_SETTINGS_VJOY_SHUTDOWN_CHK:
		case IDC_SETTINGS_STARTUP_CHK:
		case IDC_SETTINGS_START_MINIMIZED_CHK:
		case IDC_SETTINGS_CLOSE_MINIMIZE_CHK:
		case IDC_SETTINGS_DISCONNECT_BT_CHK:
		case IDC_SETTINGS_MOUSE_CAN_BYPASS_CHK:
		case IDC_SETTINGS_ALERT_ON_LOWBATTS_CHK:
		case IDC_SETTINGS_TRIGGERS_NONE_CHK:
		case IDC_SETTINGS_TRIGGERS_SHOOT_CHK:
		case IDC_SETTINGS_TRIGGERS_RESIST_CHK:
		case IDC_SETTINGS_TRIGGERS_PROACTIVE_CHK:
		case IDC_SETTINGS_DARK_THEME_CHK:
		case IDC_SETTINGS_LED_CHK:
		{
			if (((LPNMHDR)lParam)->code == NM_CUSTOMDRAW)
			{
				LPNMCUSTOMDRAW DrawMenuCustom = (LPNMCUSTOMDRAW)lParam;
				DrawMenuCustom->rc.right = DrawMenuCustom->rc.left + 12;
				DrawMenuCustom->rc.bottom = DrawMenuCustom->rc.top + 12;

				RECT rect;
				rect.left = DrawMenuCustom->rc.left + 1;
				rect.right = rect.left + 11;
				rect.top = DrawMenuCustom->rc.top + 1;
				rect.bottom = rect.top + 11;

				if (DrawMenuCustom->dwDrawStage == CDDS_PREPAINT)
				{
					switch (IsDlgButtonChecked(m_hDlg, ((LPNMHDR)lParam)->idFrom))
					{
					case BST_UNCHECKED:
					{
						if (tape.DarkTheme)
							FillRect(DrawMenuCustom->hdc, &rect, tape.hB_green);
						else
							FillRect(DrawMenuCustom->hdc, &rect, tape.hB_CHECKBOX_UNCHECKED);
						break;
					}
					case BST_CHECKED:
					{

						if (tape.DarkTheme)
							FillRect(DrawMenuCustom->hdc, &rect, tape.hB_CHECKBOX_DARK);
						else
							FillRect(DrawMenuCustom->hdc, &rect, tape.hB_CHECKBOX_CHECKED);
						DrawText(DrawMenuCustom->hdc, L"■", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					case BST_INDETERMINATE:
					{
						FillRect(DrawMenuCustom->hdc, &rect, tape.hB_CHECKBOX_INDETERMINATE);
						DrawText(DrawMenuCustom->hdc, L"■", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					}
					return TRUE;
				}
			}
			break;
		}
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_SETTINGS_DS4_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					tape.PreferredSource = 1;
				else
				{
					echo(I18N.ds_notforuse);
					tape.PreferredSource = 0;
				}
				tape.Save(tape.Setting_PreferredSource);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS4_CHK, (tape.PreferredSource == 1) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS5_CHK, (tape.PreferredSource == 2) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DI_CHK, (tape.PreferredSource == 3) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_XI_CHK, (tape.PreferredSource == 4) ? BST_CHECKED : BST_UNCHECKED);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DS5_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					tape.PreferredSource = 2;
				else
				{
					echo(I18N.ds_notforuse);
					tape.PreferredSource = 0;
				}
				tape.Save(tape.Setting_PreferredSource);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS4_CHK, (tape.PreferredSource == 1) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS5_CHK, (tape.PreferredSource == 2) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DI_CHK, (tape.PreferredSource == 3) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_XI_CHK, (tape.PreferredSource == 4) ? BST_CHECKED : BST_UNCHECKED);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DI_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					tape.PreferredSource = 3;
				else
				{
					echo(I18N.di_notforuse);
					tape.PreferredSource = 0;
				}
				tape.Save(tape.Setting_PreferredSource);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS4_CHK, (tape.PreferredSource == 1) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS5_CHK, (tape.PreferredSource == 2) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DI_CHK, (tape.PreferredSource == 3) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_XI_CHK, (tape.PreferredSource == 4) ? BST_CHECKED : BST_UNCHECKED);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_XI_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					tape.PreferredSource = 4;
				else
				{
					echo(I18N.xi_notforuse);
					tape.PreferredSource = 0;
				}
				tape.Save(tape.Setting_PreferredSource);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS4_CHK, (tape.PreferredSource == 1) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS5_CHK, (tape.PreferredSource == 2) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DI_CHK, (tape.PreferredSource == 3) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_XI_CHK, (tape.PreferredSource == 4) ? BST_CHECKED : BST_UNCHECKED);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_KBD_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.KeyboardActive = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_KeyboardActive);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_MSE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.MouseActive = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_MouseActive);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_COUNTRY_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_SETTINGS_COUNTRY), TRUE);
				break;
			}
			break;
		}
		case IDC_SETTINGS_COUNTRY:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				int result = (int)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				if (tape.InstalledLanguage[result])
				{
					tape.setCountry(result);
					tape.Save(tape.Setting_Country);
					SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_COUNTRY_STATIC), Settings::CountryString((CountryID)tape.Country));
					LoadLanguage();
					SendMessage(tape.Ds2hWnd, WM_CHANGE_LANGUAGE, 0, 0);
				}
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_TEXT_VJ_DEVICE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (vJoyEnabled())
					PostMessage(tape.Ds2hWnd, WM_SETVJOY, 0, 0);
				else
				{
					RECT win;
					GetWindowRect(tape.Ds2hWnd, &win);
					MessageBoxPos(tape.Ds2hWnd, I18N.VJOY_NOT_INSTALLED, I18N.APP_TITLE, MB_ICONERROR, win.left + 174, win.top + 30);
				}
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_VJ_DEVICE_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_SETTINGS_VJ_DEVICE), TRUE);
				break;
			}
			break;
		}
		case IDC_SETTINGS_VJ_DEVICE:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.setvJoyDevice((int)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_VJ_DEVICE), CB_GETCURSEL, 0, 0));
				tape.Save(tape.Setting_vJoyDevice);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_DEST_START, 0, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_VJ_DEVICE_STATIC), (result) ? std::to_wstring(result).c_str() : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_VJ_DEVICE_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_VJ_DEVICE_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_XI_DEVICE_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_SETTINGS_XI_DEVICE), TRUE);
				break;
			}
			break;
		}
		case IDC_SETTINGS_XI_DEVICE:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.setXInputDevice((int)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_XI_DEVICE), CB_GETCURSEL, 0, 0));
				tape.Save(tape.Setting_XInputDevice);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_DEST_START, 0, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_XI_DEVICE_STATIC), std::to_wstring(result + 1).c_str());
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_XI_DEVICE_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_XI_DEVICE_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_STARTUP_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					std::wstring progPath = ExePath() + L"\\Ds2vJoy.exe";
					HKEY hkey = NULL;
					int openStatus = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &hkey);
					if (openStatus == ERROR_SUCCESS)
					{
						int status = RegSetValueEx(hkey, L"Ds2vJoy", 0, REG_SZ, (byte*)progPath.c_str(), (unsigned int)((progPath.size() + 1) * sizeof(wchar_t)));
						if (status == ERROR_SUCCESS) {
							echo(I18N.Settings_Registry_Added);
						}
						RegCloseKey(hkey);
					}
				}
				else
				{
					HKEY hkey = NULL;
					int openStatus = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &hkey);
					if (openStatus == ERROR_SUCCESS)
					{
						int status = RegDeleteValue(hkey, L"Ds2vJoy");
						if (status == ERROR_SUCCESS) {
							echo(I18N.Settings_Registry_Removed);
						}
						RegCloseKey(hkey);
					}
				}
			}
			}
			break;
		}
		case IDC_SETTINGS_START_MINIMIZED_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.Tasktray = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_Tasktray);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_DEST_START, 0, 1);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_CLOSE_MINIMIZE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.CloseMinimize = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_CloseMinimize);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_DEST_START, 0, 1);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DISCONNECT_BT_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.DisconnectBT = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_DisconnectBT);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_MOUSE_CAN_BYPASS_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.MouseCanBypass = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_MouseCanBypass);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_ALERT_ON_LOWBATTS_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.LowBattAlert = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_LowBattAlert);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_TRIGGERS_NONE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_SHOOT_CHK, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_RESIST_CHK, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_PROACTIVE_CHK, BST_UNCHECKED);
				}
				CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_MODE, BST_CHECKED);
				tape.TriggersMode = 0;
				tape.Save(tape.Setting_TriggersMode);
				PostMessage(tape.Ds2hWnd, WM_SETTRIGGERS, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_TRIGGERS_SHOOT_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_NONE_CHK, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_RESIST_CHK, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_PROACTIVE_CHK, BST_UNCHECKED);
				}
				CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_SHOOT_CHK, BST_CHECKED);
				tape.TriggersMode = 2;
				tape.Save(tape.Setting_TriggersMode);
				PostMessage(tape.Ds2hWnd, WM_SETTRIGGERS, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_TRIGGERS_RESIST_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_NONE_CHK, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_SHOOT_CHK, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_PROACTIVE_CHK, BST_UNCHECKED);
				}
				CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_RESIST_CHK, BST_CHECKED);
				tape.TriggersMode = 1;
				tape.Save(tape.Setting_TriggersMode);
				PostMessage(tape.Ds2hWnd, WM_SETTRIGGERS, 1, 0);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_TRIGGERS_PROACTIVE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_NONE_CHK, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_SHOOT_CHK, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_RESIST_CHK, BST_UNCHECKED);
				}
				CheckDlgButton(hWnd, IDC_SETTINGS_TRIGGERS_PROACTIVE_CHK, BST_CHECKED);
				tape.TriggersMode = 3;
				tape.Save(tape.Setting_TriggersMode);
				PostMessage(tape.Ds2hWnd, WM_SETTRIGGERS, 3, 0);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DS_SERIAL:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[13];
				GetWindowText((HWND)lParam, buf, 13);
				if (lstrcmpW(tape.Serial, buf) != 0)
				{
					tape.setSerial(buf);
					tape.Save(tape.Setting_Serial);
					PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);
				}
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_TEXT_DI_DEVICE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				PostMessage(tape.Ds2hWnd, WM_SETDINPUT, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DI_DEVICE_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 0;
				SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), (wcslen(tape.Device1)) ? tape.Device1 : L". . .");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DI_DEVICE_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 1;
				SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), (wcslen(tape.Device2)) ? tape.Device2 : L". . .");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DI_DEVICE_RELOAD:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				SendMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_LIST, 0, 0);
				SendDlgItemMessage(hWnd, IDC_SETTINGS_DI_DEVICE, CB_RESETCONTENT, 0, 0);
				for (int i = 0; i < tape.DevicesList.size(); i++)
				{
					WCHAR buf[MAX_PATH];
					swprintf_s(buf, MAX_PATH, L"  VID:%04hX  PID:%04hX  UID:%s -> %s", tape.DevicesList[i].vid, tape.DevicesList[i].pid, tape.DevicesList[i].uid.c_str(), tape.DevicesList[i].pname.c_str());
					SendDlgItemMessage(hWnd, IDC_SETTINGS_DI_DEVICE, CB_ADDSTRING, 0, LPARAM(buf));
				}
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DI_DEVICE_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE), TRUE);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DI_DEVICE:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.setDevice((tape.DevicesList[(int)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE), CB_GETCURSEL, 0, 0)].uid).c_str(), m_device);
				if (m_device)
					tape.Save(tape.Setting_Device2);
				else
					tape.Save(tape.Setting_Device1);
				if (tape.PreferredSource)
					PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				if (m_device)
					SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), (wcslen(tape.Device2)) ? tape.Device2 : L". . .");
				else
					SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), (wcslen(tape.Device1)) ? tape.Device1 : L". . .");
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DI_DEVICE_CLEAR:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.setDevice(L"", m_device);
				if (m_device)
					tape.Save(tape.Setting_Device2);
				else
					tape.Save(tape.Setting_Device1);
				if (tape.PreferredSource)
					PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), L". . .");
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_DI_DEVICE_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_DARK_THEME_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{	
				::EnableWindow(GetDlgItem(m_hDlg, IDC_SETTINGS_SLIDER), FALSE);
				tape.DarkTheme = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_DarkTheme);
				::ShowWindow(tape.Ds2hWnd, SW_HIDE);
				::ShowWindow(tape.Ds2hWnd, SW_SHOW);
				::EnableWindow(GetDlgItem(m_hDlg, IDC_SETTINGS_SLIDER), TRUE);
				
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_THRESHOLD:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[8];
				GetWindowText((HWND)lParam, buf, 8);
				tape.Threshold = max(0, min(128, _wtoi(buf))) * 257;
				tape.Save(tape.Setting_Threshold);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_SIMULTANEOUS:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[8];
				GetWindowText((HWND)lParam, buf, 8);
				tape.Simultaneous = max(1, min(9999, _wtoi(buf)));
				tape.Save(tape.Setting_Simultaneous);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_LONG:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[8];
				GetWindowText((HWND)lParam, buf, 8);
				tape.LongPress = max(1, min(9999, _wtoi(buf)));
				tape.Save(tape.Setting_LongPress);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_VERY_LONG:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[8];
				GetWindowText((HWND)lParam, buf, 8);
				tape.VeryLongPress = max(1, min(9999, _wtoi(buf)));
				tape.Save(tape.Setting_VeryLongPress);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_WEBREFRESH:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[8];
				GetWindowText((HWND)lParam, buf, 8);
				tape.WebRefreshTime = max(1, min(9999, _wtoi(buf)));
				tape.Save(tape.Setting_WebRefreshTime);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_OPACITY:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[8];
				GetWindowText((HWND)lParam, buf, 8);
				byte Opacitytmp = min(100, _wtoi(buf));
				if (Opacitytmp > 19)
				{
					tape.Opacity = Opacitytmp;
					tape.Save(tape.Setting_Opacity);
					PostMessage(tape.Ds2hWnd, WM_TRANSPARENCY, 0, 0);
				}
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_FIRST_BUTTON_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_SETTINGS_FIRST_BUTTON), TRUE);
				break;
			}
			break;
		}
		case IDC_SETTINGS_FIRST_BUTTON:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.setTouchPadButton((int)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_FIRST_BUTTON), CB_GETCURSEL, 0, 0));
				tape.Save(tape.Setting_TouchPadButton);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 1);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_FIRST_BUTTON_STATIC), (result) ? std::to_wstring(result).c_str() : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_FIRST_BUTTON_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_FIRST_BUTTON_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_COLUMNS_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_SETTINGS_COLUMNS), TRUE);
				break;
			}
			break;
		}
		case IDC_SETTINGS_COLUMNS:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.setTouchCol((int)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_COLUMNS), CB_GETCURSEL, 0, 0) + 1);
				tape.Save(tape.Setting_TouchCol);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 1);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_COLUMNS_STATIC), std::to_wstring(result + 1).c_str());
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_COLUMNS_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_COLUMNS_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_ROWS_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_SETTINGS_ROWS), TRUE);
				break;
			}
			break;
		}
		case IDC_SETTINGS_ROWS:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.setTouchRow((int)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_ROWS), CB_GETCURSEL, 0, 0) + 1);
				tape.Save(tape.Setting_TouchRow);
				PostMessage(tape.Ds2hWnd, WM_DEVICE_SRCE_START, 0, 1);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_ROWS_STATIC), std::to_wstring(result + 1).c_str());
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_ROWS_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_SETTINGS_ROWS_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_VJOY_SHUTDOWN_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.vJoyShutDown = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_vJoyShutDown);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_LED_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.BlackLedOnExit = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_BlackLedOnExit);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_COLOR:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (ChooseColor(&cc))
				{
					tape.setLED(cc.rgbResult);
					tape.Save(tape.Setting_LED_Color);
					PostMessage(hWnd, WM_DEVICE_SRCE_START, 0, 1);
					RedrawWindow(m_hDlg, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW);
				}
				break;
			}
			}
			break;
		}
		default:
			return FALSE;
		}
		break;
	}
	case WM_HSCROLL:
	{
		switch (LOWORD(wParam))
		{
		case TB_ENDTRACK:
		{
			tape.WaveSpeed = (byte)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_SLIDER), TBM_GETPOS, 0, 0);
			//SetDlgItemInt(hWnd, ID_SLIDERTXT, SendMessage(GetDlgItem(hWnd, IDC_SLIDER), TBM_GETPOS, 0, 0), FALSE);
			PostMessage(tape.Ds2hWnd, WM_TIMER, 2, 0);
			break;
		}
		}
		return TRUE;
	}
	default:
		return FALSE;
	}
	return TRUE;
}

void SettingDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void SettingDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL SettingDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
