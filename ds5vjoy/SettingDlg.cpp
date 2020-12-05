#include "stdafx.h"
#include "ds5vjoy.h"
#include "resource.h"
#include "Startup.h"
#include "Settings.h"
#include "SettingDlg.h"
#include "Language.h"

SettingDlg::SettingDlg()
{
}

INT_PTR CALLBACK SettingDlg::Proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam) {
	SettingDlg *sDlg;
	if (uMsg == WM_INITDIALOG) {
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		sDlg = (SettingDlg *)lParam;
	}else {
		sDlg = (SettingDlg *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (sDlg) {
		return sDlg->_proc(hWnd, uMsg, wParam, lParam);
	}
	else {
		return NULL;
	}
}

void SettingDlg::Init(HINSTANCE hInst ,HWND hWnd)
{
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, (DLGPROC)Proc,(LPARAM)this);
	m_hWnd = hWnd;
}

INT_PTR SettingDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	static CHOOSECOLOR cc = { 0 };
	static COLORREF color = 0, CustColors[16];

	switch (uMsg) {
	case WM_SHOWWINDOW:
		if (wParam == TRUE) {
			m_changeflag = false;
			SendMessage(GetDlgItem(hWnd, IDC_DISCONNECT_BT), BM_SETCHECK, g_settings.DisconnectBT ? BST_CHECKED : BST_UNCHECKED, 0);
			SendMessage(GetDlgItem(hWnd, IDC_TOUCHPAD), BM_SETCHECK, g_settings.SplitTouchPad ? BST_CHECKED : BST_UNCHECKED, 0);
			SendMessage(GetDlgItem(hWnd, IDC_FFB), BM_SETCHECK, g_settings.FFB ? BST_CHECKED : BST_UNCHECKED, 0);
			SendMessage(GetDlgItem(hWnd, IDC_TASKTRAY), BM_SETCHECK, g_settings.Tasktray ? BST_CHECKED : BST_UNCHECKED, 0);

			SendMessage(GetDlgItem(hWnd, IDC_ROW), CB_SETCURSEL, (LPARAM)g_settings.TouchRow - 1, 0);
			SendMessage(GetDlgItem(hWnd, IDC_COL), CB_SETCURSEL, (LPARAM)g_settings.TouchCol - 1, 0);
			SendMessage(GetDlgItem(hWnd, IDC_VJOY_DEV), CB_SETCURSEL, (LPARAM)g_settings.vJoyDeviceID - 1, 0);
			SendMessage(GetDlgItem(hWnd, IDC_TOUCH_BUTTON), CB_SETCURSEL, (LPARAM)g_settings.TouchPadButton , 0);

			cc.rgbResult = g_settings.LED_Color;

			SetWindowText(GetDlgItem(hWnd, IDC_DS5_SERIAL), g_settings.getSerial());
			SendMessage(GetDlgItem(hWnd, IDC_STARTUP), BM_SETCHECK, CheckStartUp() ? BST_CHECKED : BST_UNCHECKED, 0);

		}
		else if(m_changeflag){
			if (MessageBox(hWnd, I18N.MBOX_Save , I18N.APP_TITLE , MB_YESNO) == IDYES) {
				g_settings.DisconnectBT = BST_CHECKED == SendMessage(GetDlgItem(hWnd, IDC_DISCONNECT_BT), BM_GETCHECK, 0, 0);
				g_settings.SplitTouchPad = BST_CHECKED == SendMessage(GetDlgItem(hWnd, IDC_TOUCHPAD), BM_GETCHECK, 0, 0);
				g_settings.FFB = BST_CHECKED == SendMessage(GetDlgItem(hWnd, IDC_FFB), BM_GETCHECK, 0, 0);
				g_settings.Tasktray = BST_CHECKED == SendMessage(GetDlgItem(hWnd, IDC_TASKTRAY), BM_GETCHECK, 0, 0);
				g_settings.SetTouchRow((int)SendMessage(GetDlgItem(hWnd, IDC_ROW), CB_GETCURSEL, 0, 0) + 1);
				g_settings.SetTouchCol((int)SendMessage(GetDlgItem(hWnd, IDC_COL), CB_GETCURSEL, 0, 0) + 1);
				g_settings.SetTouchPadButton((int)SendMessage(GetDlgItem(hWnd, IDC_TOUCH_BUTTON), CB_GETCURSEL, 0, 0));
				g_settings.setvJoyDeviceID((int)SendMessage(GetDlgItem(hWnd, IDC_VJOY_DEV), CB_GETCURSEL, 0, 0) + 1);

				g_settings.SetLED_Color(cc.rgbResult);

				WCHAR buf[13];
				GetWindowText(GetDlgItem(hWnd, IDC_DS5_SERIAL), buf, 13);
				g_settings.setSerial(buf);
				g_settings.Save();
				PostMessage(m_hWnd, WM_CHANGE_SETTING, 0, 0);
				bool startup = BST_CHECKED == SendMessage(GetDlgItem(hWnd, IDC_STARTUP), BM_GETCHECK, 0, 0);
				if (startup) {
					if (!CheckStartUp()) {
						CreateStartUp();
					}
				}
				else if (CheckStartUp()) {
					DeleteStartUp();
				}
			}
			else {
				g_settings.Load();
			}
		}
		break;
	case WM_INITDIALOG: {
		HWND h_cb = GetDlgItem(hWnd, IDC_TOUCH_BUTTON);
		SendMessage(h_cb, CB_ADDSTRING, 0, (LPARAM)L"");
		for (int i = 1; i <= 128; i++) {
			WCHAR buf[10];
			wsprintf(buf, L"%d", i);
			SendMessage(h_cb, CB_ADDSTRING, 0, (LPARAM)buf);
		}

		for (int i = 1; i < 10; i++) {
			WCHAR buf[10];
			wsprintf(buf, L"%d", i);
			SendMessage(GetDlgItem(hWnd, IDC_ROW), CB_ADDSTRING, 0, (LPARAM)buf);
			SendMessage(GetDlgItem(hWnd, IDC_COL), CB_ADDSTRING, 0, (LPARAM)buf);
		}
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hWnd;
		cc.lpCustColors = CustColors;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;

		for (int i = 1; i < 16; i++) {
			WCHAR buf[10];
			wsprintf(buf, L"%d", i);
			SendMessage(GetDlgItem(hWnd, IDC_VJOY_DEV), CB_ADDSTRING, 0, (LPARAM)buf);
		}

		return TRUE;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_FFB:
		case IDC_DISCONNECT_BT:
		case IDC_TOUCHPAD:
		case IDC_TASKTRAY:
		case IDC_STARTUP:
			m_changeflag = true;
			break;
		case IDC_TOUCH_BUTTON:
		case IDC_ROW:
		case IDC_COL:
		case IDC_VJOY_DEV:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				m_changeflag = true;
				break;
			}
			break;
		case IDC_COLOR:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (ChooseColor(&cc)) {
					m_changeflag = true;
				}
				break;
			}
			break;
		case IDC_DS5_SERIAL:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[13];
				GetWindowText(GetDlgItem(hWnd, IDC_DS5_SERIAL), buf, 13);
				if (lstrcmpW(g_settings.getSerial(), buf) != 0) {
					m_changeflag = true;
				}
				break;
			}
			break;
		default:
			return FALSE;
		}

	}
	default:
		return FALSE;
	}
	return TRUE;
}

void SettingDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}


void SettingDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);

}

BOOL SettingDlg::MoveWindow(int x, int y , int w, int h, BOOL r)
{
	return  ::MoveWindow(m_hDlg, x, y, w, h, r);
}

SettingDlg::~SettingDlg()
{
}
