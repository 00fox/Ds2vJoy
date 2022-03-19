#include "stdafx.h"
#include "SettingDlg.h"

SettingDlg::SettingDlg()
{
}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, (DLGPROC)Proc, LPARAM(this));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_PREFERRED_DS, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS4_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS4, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS5_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS5, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_KBD_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_KBD, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_MSE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_MSE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_VJOY_DEVICE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_VJOY_DEVICE, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
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
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_USE_THE_DS_SERIAL, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_DS_SERIAL, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
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
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_COLUMN, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_TEXT_ROW, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_FIRST_BUTTON, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_COLUMN, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_ROW, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_LED_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_LED, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_WHEN_EXITING, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_SETTINGS_SLIDER, WM_SETFONT, WPARAM(tape.hSlider), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_PREFERRED_DS), I18N.SETTINGS_PREFERRED_DS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DS4), I18N.SETTINGS_DS4);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_DS5), I18N.SETTINGS_DS5);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_KBD), I18N.SETTINGS_KBD);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_MSE), I18N.SETTINGS_MSE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_VJOY_DEVICE), I18N.SETTINGS_TEXT_VJOY_DEVICE);
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
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_USE_THE_DS_SERIAL), I18N.SETTINGS_USE_THE_DS_SERIAL);
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
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_COLUMN), I18N.SETTINGS_TEXT_COLUMN);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_TEXT_ROW), I18N.SETTINGS_TEXT_ROW);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_LED), I18N.SETTINGS_LED);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_WHEN_EXITING), I18N.SETTINGS_WHEN_EXITING);
	SetWindowText(GetDlgItem(m_hDlg, IDC_SETTINGS_COLOR), I18N.SETTINGS_COLOR);
	Hide();
}

void SettingDlg::_InitDialog(HWND hWnd)
{
	for (int i = 1; i < 16; i++)
	{
		WCHAR buf[10];
		swprintf_s(buf, 10, L"%d", i);
		SendDlgItemMessage(hWnd, IDC_SETTINGS_VJOY_DEVICE, CB_ADDSTRING, 0, LPARAM(buf));
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
		SendDlgItemMessage(hWnd, IDC_SETTINGS_COLUMN, CB_ADDSTRING, 0, LPARAM(buf));
		SendDlgItemMessage(hWnd, IDC_SETTINGS_ROW, CB_ADDSTRING, 0, LPARAM(buf));
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
	CheckDlgButton(hWnd, IDC_SETTINGS_DS4_CHK, tape.PreferredDS == 1);
	CheckDlgButton(hWnd, IDC_SETTINGS_DS5_CHK, tape.PreferredDS == 2);
	CheckDlgButton(hWnd, IDC_SETTINGS_KBD_CHK, tape.KeyboardActive);
	CheckDlgButton(hWnd, IDC_SETTINGS_MSE_CHK, tape.MouseActive);

	SendDlgItemMessage(hWnd, IDC_SETTINGS_VJOY_DEVICE, CB_SETCURSEL, LPARAM(tape.vJoyDeviceID - 1), 0);

	bool startupvalue = false;
	{
		HKEY hkey = NULL;
		BOOL bExist = FALSE;
		long openStatus = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &hkey);
		if (openStatus == ERROR_SUCCESS)
		{
			DWORD dwType;
			long status = RegQueryValueEx(hkey, L"Ds2vJoy", NULL, &dwType, NULL, NULL);
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

	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_DS_SERIAL), tape.getSerial());
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_THRESHOLD), WCHARI(20, L"%d", tape.Threshold));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_SIMULTANEOUS), WCHARI(20, L"%d", tape.Simultaneous));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_LONG), WCHARI(20, L"%d", tape.LongPress));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_VERY_LONG), WCHARI(20, L"%d", tape.VeryLongPress));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_WEBREFRESH), WCHARI(20, L"%d", tape.WebRefreshTime));
	SetWindowText(GetDlgItem(hWnd, IDC_SETTINGS_OPACITY), WCHARI(20, L"%d", tape.Opacity));

	SendDlgItemMessage(hWnd, IDC_SETTINGS_FIRST_BUTTON, CB_SETCURSEL, LPARAM(tape.TouchPadButton), 0);
	SendDlgItemMessage(hWnd, IDC_SETTINGS_COLUMN, CB_SETCURSEL, LPARAM(tape.TouchRow - 1), 0);
	SendDlgItemMessage(hWnd, IDC_SETTINGS_ROW, CB_SETCURSEL, LPARAM(tape.TouchCol - 1), 0);

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
		SetTextColor(hdcStatic, tape.ink_DLG);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_DLG);
		return (LRESULT)tape.hB_DLG;
	}
	case WM_CTLCOLORMSGBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_MSGBOX);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_MSGBOX);
		return (LRESULT)tape.hB_MSGBOX;
	}
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_BTN);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_BTN);
		return (LRESULT)tape.hB_BTN;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		switch (GetDlgCtrlID((HWND)lParam))
		{
		case IDC_SETTINGS_DS4:
		case IDC_SETTINGS_DS5:
		case IDC_SETTINGS_KBD:
		case IDC_SETTINGS_MSE:
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
		case IDC_SETTINGS_WHEN_EXITING:
		{
			SetTextColor(hdcStatic, tape.ink_STATIC_Checkbox);
			break;
		}
		default:
		{
			SetTextColor(hdcStatic, tape.ink_STATIC);
			break;
		}
		}
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_STATIC);
		return (LRESULT)tape.hB_STATIC;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_EDIT);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LRESULT)tape.hB_EDIT;
	}
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_LIST);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LRESULT)tape.hB_LIST;
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			FillRect(hDC, &rect, tape.hB_BackGround);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);

			HWND ledbutton = GetDlgItem(hWnd, IDC_SETTINGS_COLOR);
			hDC = BeginPaint(ledbutton, &ps);
			GetClientRect(ledbutton, &rect);

			DrawEdge(hDC, &rect, EDGE_RAISED, BF_RECT);

			rect.top -= 1;
			rect.left -= 1;
			rect.right += 1;
			rect.bottom += 1;
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
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_CUSTOMDRAW:
		{
			LPNMCUSTOMDRAW DrawMenuCustom = (LPNMCUSTOMDRAW)lParam;
			DrawMenuCustom->rc.right = DrawMenuCustom->rc.left + 12;
			DrawMenuCustom->rc.bottom = DrawMenuCustom->rc.top + 12;

			RECT rect;
			rect.left = DrawMenuCustom->rc.left + 1;
			rect.right = rect.left + 11;
			rect.top = DrawMenuCustom->rc.top + 1;
			rect.bottom = rect.top + 11;

			switch (((LPNMHDR)lParam)->idFrom)
			{
			case IDC_SETTINGS_DS4_CHK:
			case IDC_SETTINGS_DS5_CHK:
			case IDC_SETTINGS_KBD_CHK:
			case IDC_SETTINGS_MSE_CHK:
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
				if (DrawMenuCustom->dwDrawStage == CDDS_PREPAINT)
				{
					switch (IsDlgButtonChecked(m_hDlg, ((LPNMHDR)lParam)->idFrom))
					{
					case BST_UNCHECKED:
					{
						FillRect(DrawMenuCustom->hdc, &rect, tape.hB_CHECKBOX_UNCHECKED);
						break;
					}
					case BST_CHECKED:
					{
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
				{
					CheckDlgButton(hWnd, IDC_SETTINGS_DS5_CHK, BST_UNCHECKED);
					tape.PreferredDS = 1;
				}
				else
					tape.PreferredDS = 0;
				tape.Save(tape.Setting_PreferredDS);
				PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 0);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS4_CHK, (tape.PreferredDS == 1) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS5_CHK, (tape.PreferredDS == 2) ? BST_CHECKED : BST_UNCHECKED);
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
				{
					CheckDlgButton(hWnd, IDC_SETTINGS_DS4_CHK, BST_UNCHECKED);
					tape.PreferredDS = 2;
				}
				else
					tape.PreferredDS = 0;
				tape.Save(tape.Setting_PreferredDS);
				PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 0);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS4_CHK, (tape.PreferredDS == 1) ? BST_CHECKED : BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_SETTINGS_DS5_CHK, (tape.PreferredDS == 2) ? BST_CHECKED : BST_UNCHECKED);
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
		case IDC_SETTINGS_VJOY_DEVICE:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.setvJoyDeviceID((int)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_VJOY_DEVICE), CB_GETCURSEL, 0, 0) + 1);
				tape.Save(tape.Setting_vJoyDeviceID);
				PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 0);
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
					long openStatus = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &hkey);
					if (openStatus == ERROR_SUCCESS)
					{
						long status = RegSetValueEx(hkey, L"Ds2vJoy", 0, REG_SZ, (byte*)progPath.c_str(), (unsigned long)((progPath.size() + 1) * sizeof(wchar_t)));
						if (status == ERROR_SUCCESS) {
							echo(I18N.Registry_Added);
						}
						RegCloseKey(hkey);
					}
				}
				else
				{
					HKEY hkey = NULL;
					long openStatus = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &hkey);
					if (openStatus == ERROR_SUCCESS)
					{
						long status = RegDeleteValue(hkey, L"Ds2vJoy");
						if (status == ERROR_SUCCESS) {
							echo(I18N.Registry_Removed);
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
				PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 1);
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
				PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 1);
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
				PostMessage(m_hWnd, WM_SETTRIGGERS, 0, 0);
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
				PostMessage(m_hWnd, WM_SETTRIGGERS, 2, 0);
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
				PostMessage(m_hWnd, WM_SETTRIGGERS, 1, 0);
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
				PostMessage(m_hWnd, WM_SETTRIGGERS, 3, 0);
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
				if (lstrcmpW(tape.getSerial(), buf) != 0)
				{
					tape.setSerial(buf);
					tape.Save(tape.Setting_dsSerial);
					PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 0);
				}
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
				tape.DarkTheme = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_DarkTheme);
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
				tape.Threshold = max(0, min(128, _wtoi(buf)));
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
					PostMessage(m_hWnd, WM_TRANSPARENCY, 0, 0);
				}
				break;
			}
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
				PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_COLUMN:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.setTouchCol((int)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_COLUMN), CB_GETCURSEL, 0, 0) + 1);
				tape.Save(tape.Setting_TouchCol);
				PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
				break;
			}
			}
			break;
		}
		case IDC_SETTINGS_ROW:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.setTouchRow((int)SendMessage(GetDlgItem(hWnd, IDC_SETTINGS_ROW), CB_GETCURSEL, 0, 0) + 1);
				tape.Save(tape.Setting_TouchRow);
				PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
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
					PostMessage(hWnd, WM_DEVICE_DS_START, 0, 1);
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
			PostMessage(m_hWnd, WM_TIMER, 2, 0);
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
