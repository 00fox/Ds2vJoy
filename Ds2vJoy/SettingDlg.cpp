#include "stdafx.h"
#include "SettingDlg.h"
#include "Ds2vJoy.h"

SettingDlg::SettingDlg()
{
}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::Init(HINSTANCE hInst, HWND hWnd)
{
//	HINSTANCE h = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hWnd = hWnd;
	Hide();
}

INT_PTR CALLBACK SettingDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	SettingDlg* dlg;

	if (uMsg == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<SettingDlg*>(lparam);
		SetWindowLongPtrW(hWnd, DWLP_USER, lparam);
	}
	else
		dlg = reinterpret_cast<SettingDlg*>(GetWindowLongPtrW(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, uMsg, wparam, lparam);
		return result;
	}
	return DefWindowProcW(hWnd, uMsg, wparam, lparam);
}

INT_PTR SettingDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CTLCOLORDLG:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_DLG);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_DLG);
		return (LRESULT)tape.hB_DLG;
	}
	case WM_CTLCOLORMSGBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_MSGBOX);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_MSGBOX);
		return (LRESULT)tape.hB_MSGBOX;
	}
	case WM_CTLCOLORSCROLLBAR:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_SCROLLBAR);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_SCROLLBAR);
		return (LRESULT)tape.hB_SCROLLBAR;
	}
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_BTN);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_BTN);
		return (LRESULT)tape.hB_BTN;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		DWORD CtrlID = GetDlgCtrlID((HWND)lParam);
		if (CtrlID == IDC_STATIC_EXITING)
			SetTextColor(hdcStatic, tape.Tx_STATIC_EXITING);
		else
			SetTextColor(hdcStatic, tape.Tx_STATIC);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_STATIC);
		return (LRESULT)tape.hB_STATIC;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_EDIT);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LRESULT)tape.hB_EDIT;
	}
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_LISTBOX);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LRESULT)tape.hB_LISTBOX;
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
//			Rectangle(hDC, 122, 199, 261, 225);
//			RoundRect(hDC, 118, 142, 256, 186, 20, 20);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);

			HWND ledbutton = GetDlgItem(hWnd, IDC_COLOR);
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
				SetTextColor(hDC, tape.Tx_BTN_Heavy);
			else
				SetTextColor(hDC, tape.Tx_BTN_Light);

			DrawText(hDC, L"LED", 3, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			::ReleaseDC(hWnd, hDC);
			EndPaint(ledbutton, &ps);
		}
		return FALSE;
	}
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case TB_ENDTRACK:
			tape.WaveSpeed = (byte)SendMessage(GetDlgItem(hWnd, IDC_SLIDER), TBM_GETPOS, 0, 0);
			//SetDlgItemInt(hWnd, ID_SLIDERTXT, SendMessage(GetDlgItem(hWnd, IDC_SLIDER), TBM_GETPOS, 0, 0), FALSE);
			PostMessage(m_hWnd, WM_TIMER, 2, 0);
			break;
		}
		return TRUE;
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
		{
			if (!firsttime)
			{
				HFONT hFont = CreateFont(12, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
				SendDlgItemMessage(hWnd, IDC_STATIC_TIMES, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
				SendDlgItemMessage(hWnd, IDC_STATIC_UNIT, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
				SendDlgItemMessage(hWnd, IDC_STATIC_GROUP_PAD, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

				hFont = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
				SendDlgItemMessage(hWnd, IDC_THRESHOLD, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
				SendDlgItemMessage(hWnd, IDC_SIMULTANEOUS, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
				SendDlgItemMessage(hWnd, IDC_LONGPRESS, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
				SendDlgItemMessage(hWnd, IDC_VERYLONGPRESS, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
				firsttime = true;
			}

			CheckDlgButton(hWnd, IDC_DS4, tape.PreferredDS == 1);
			CheckDlgButton(hWnd, IDC_DS5, tape.PreferredDS == 2);
			CheckDlgButton(hWnd, IDC_MSE, tape.MouseActive);
			CheckDlgButton(hWnd, IDC_KBD, tape.KeyboardActive);
			SendDlgItemMessage(hWnd, IDC_VJOY_DEV, CB_SETCURSEL, (LPARAM)tape.vJoyDeviceID - 1, 0);

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
			CheckDlgButton(hWnd, IDC_STARTUP, startupvalue);

			CheckDlgButton(hWnd, IDC_TASKTRAY, tape.Tasktray);
			CheckDlgButton(hWnd, IDC_CLOSE_MINIMIZE, tape.CloseMinimize);
			CheckDlgButton(hWnd, IDC_DISCONNECT_BT, tape.DisconnectBT);
			CheckDlgButton(hWnd, IDC_LOWBATT, tape.LowBattAlert);
			CheckDlgButton(hWnd, IDC_FFB, tape.FFB);
			CheckDlgButton(hWnd, IDC_MOUSE_CAN_BYPASS, tape.MouseCanBypass);
			CheckDlgButton(hWnd, IDC_TRIGGERS_NONE, tape.TriggersMode == 0);
			CheckDlgButton(hWnd, IDC_TRIGGERS_RESIST, tape.TriggersMode == 1);
			CheckDlgButton(hWnd, IDC_TRIGGERS_SHOOT, tape.TriggersMode == 2);
			CheckDlgButton(hWnd, IDC_TRIGGERS_PROACTIVE, tape.TriggersMode == 3);
			
			SendDlgItemMessage(hWnd, IDC_TOUCHPAD, CB_SETCURSEL, (LPARAM)tape.TouchPadButton, 0);
			SendDlgItemMessage(hWnd, IDC_ROW, CB_SETCURSEL, (LPARAM)tape.TouchRow - 1, 0);
			SendDlgItemMessage(hWnd, IDC_COL, CB_SETCURSEL, (LPARAM)tape.TouchCol - 1, 0);

			SetWindowText(GetDlgItem(hWnd, IDC_DS_SERIAL), tape.getSerial());
			TCHAR buf[20];
			swprintf_s(buf, TEXT("%d"), tape.Threshold);
			SetWindowText(GetDlgItem(hWnd, IDC_THRESHOLD), buf);
			swprintf_s(buf, TEXT("%d"), tape.Simultaneous);
			SetWindowText(GetDlgItem(hWnd, IDC_SIMULTANEOUS), buf);
			swprintf_s(buf, TEXT("%d"), tape.LongPress);
			SetWindowText(GetDlgItem(hWnd, IDC_LONGPRESS), buf);
			swprintf_s(buf, TEXT("%d"), tape.VeryLongPress);
			SetWindowText(GetDlgItem(hWnd, IDC_VERYLONGPRESS), buf);

			cc.rgbResult = tape.LED_Color;
			CheckDlgButton(hWnd, IDC_LED, tape.BlackLedOnExit);
		}
		break;
	}
	case WM_INITDIALOG:
	{
//		SetWindowTheme(GetDlgItem(hWnd, IDC_DS5), NULL, L"Remove");
		HWND h_cb = GetDlgItem(hWnd, IDC_TOUCHPAD);
		SendMessage(h_cb, CB_ADDSTRING, 0, (LPARAM)L"");
		for (int i = 1; i <= 128; i++)
		{
			WCHAR buf[10];
			wsprintf(buf, L"%d", i);
			SendMessage(h_cb, CB_ADDSTRING, 0, (LPARAM)buf);
		}

		for (int i = 1; i < 10; i++)
		{
			WCHAR buf[10];
			wsprintf(buf, L"%d", i);
			SendDlgItemMessage(hWnd, IDC_ROW, CB_ADDSTRING, 0, (LPARAM)buf);
			SendDlgItemMessage(hWnd, IDC_COL, CB_ADDSTRING, 0, (LPARAM)buf);
		}
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hWnd;
		cc.lpCustColors = CustColors;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;

		for (int i = 1; i < 16; i++)
		{
			WCHAR buf[10];
			wsprintf(buf, L"%d", i);
			SendDlgItemMessage(hWnd, IDC_VJOY_DEV, CB_ADDSTRING, 0, (LPARAM)buf);
		}

		SendMessage(GetDlgItem(hWnd, IDC_SLIDER), TBM_SETRANGE, FALSE, MAKELONG(0, 166));
		SendMessage(GetDlgItem(hWnd, IDC_SLIDER), TBM_SETPOS, TRUE, tape.WaveSpeed);
		//SetDlgItemInt(hWnd, ID_SLIDERTXT, tape.WaveSpeed, FALSE);

		return TRUE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_STARTUP:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					std::wstring progPath = ExePathW() + L"\\Ds2vJoy.exe";
					HKEY hkey = NULL;
//					long createStatus = RegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\Example"), &hkey);
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
//							RegDeleteKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\Example"));
							echo(I18N.Registry_Removed);
						}
						RegCloseKey(hkey);
					}
				}
			}
			break;
		}
		case IDC_DS4:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_DS5, BST_UNCHECKED);
					tape.PreferredDS = 1;
				}
				else
					tape.PreferredDS = 0;
				tape.Save(tape.Setting_PreferredDS);
				PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 0);
				break;
			}
			break;
		case IDC_DS5:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_DS4, BST_UNCHECKED);
					tape.PreferredDS = 2;
				}
				else
					tape.PreferredDS = 0;
				tape.Save(tape.Setting_PreferredDS);
				PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 0);
				break;
			}
			break;
		case IDC_MSE:
			tape.MouseActive = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_MouseActive);
			break;
		case IDC_KBD:
			tape.KeyboardActive = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_KeyboardActive);
			break;
		case IDC_TASKTRAY:
			tape.Tasktray = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_Tasktray);
			PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 1);
			break;
		case IDC_CLOSE_MINIMIZE:
			tape.CloseMinimize = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_CloseMinimize);
			PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 1);
			break;
		case IDC_DISCONNECT_BT:
			tape.DisconnectBT = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_DisconnectBT);
			break;
		case IDC_LOWBATT:
			tape.LowBattAlert = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_LowBattAlert);
			break;
		case IDC_DS_SERIAL:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
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
			break;
		case IDC_LED:
			tape.BlackLedOnExit = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_BlackLedOnExit);
			break;
		case IDC_VJOY_DEV:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				tape.setvJoyDeviceID((int)SendMessage(GetDlgItem(hWnd, IDC_VJOY_DEV), CB_GETCURSEL, 0, 0) + 1);
				tape.Save(tape.Setting_vJoyDeviceID);
				PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 0);
				break;
			}
			break;
		case IDC_THRESHOLD:
			WCHAR bufThreshold[MAX_PATH];
			GetWindowText((HWND)lParam, bufThreshold, MAX_PATH);
			tape.Threshold = max(0, min(128, _wtoi(bufThreshold)));
			tape.Save(tape.Setting_Threshold);
			break;
		case IDC_SIMULTANEOUS:
			WCHAR bufSimultaneous[MAX_PATH];
			GetWindowText((HWND)lParam, bufSimultaneous, MAX_PATH);
			tape.Simultaneous = max(1, min(9999, _wtoi(bufSimultaneous)));
			tape.Save(tape.Setting_Simultaneous);
			break;
		case IDC_LONGPRESS:
			WCHAR bufLongPress[MAX_PATH];
			GetWindowText((HWND)lParam, bufLongPress, MAX_PATH);
			tape.LongPress = max(1, min(9999, _wtoi(bufLongPress)));
			tape.Save(tape.Setting_LongPress);
			break;
		case IDC_VERYLONGPRESS:
			WCHAR bufVeryLongPress[MAX_PATH];
			GetWindowText((HWND)lParam, bufVeryLongPress, MAX_PATH);
			tape.VeryLongPress = max(1, min(9999, _wtoi(bufVeryLongPress)));
			tape.Save(tape.Setting_VeryLongPress);
			break;
		case IDC_MOUSE_CAN_BYPASS:
			tape.MouseCanBypass = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_MouseCanBypass);
			break;
		case IDC_FFB:
			tape.FFB = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_FFB);
			PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 1);
			PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
			break;
		case IDC_TRIGGERS_NONE:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_TRIGGERS_RESIST, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_TRIGGERS_SHOOT, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_TRIGGERS_PROACTIVE, BST_UNCHECKED);
				}
				CheckDlgButton(hWnd, IDC_TRIGGERS_NONE, BST_CHECKED);
				tape.TriggersMode = 0;
				tape.Save(tape.Setting_TriggersMode);
				PostMessage(m_hWnd, WM_SETTRIGGERS, 0, 0);
				break;
			}
			break;
		case IDC_TRIGGERS_RESIST:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_TRIGGERS_NONE, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_TRIGGERS_SHOOT, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_TRIGGERS_PROACTIVE, BST_UNCHECKED);
				}
				CheckDlgButton(hWnd, IDC_TRIGGERS_RESIST, BST_CHECKED);
				tape.TriggersMode = 1;
				tape.Save(tape.Setting_TriggersMode);
				PostMessage(m_hWnd, WM_SETTRIGGERS, 1, 0);
				break;
			}
			break;
		case IDC_TRIGGERS_SHOOT:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_TRIGGERS_NONE, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_TRIGGERS_RESIST, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_TRIGGERS_PROACTIVE, BST_UNCHECKED);
				}
				CheckDlgButton(hWnd, IDC_TRIGGERS_SHOOT, BST_CHECKED);
				tape.TriggersMode = 2;
				tape.Save(tape.Setting_TriggersMode);
				PostMessage(m_hWnd, WM_SETTRIGGERS, 2, 0);
				break;
			}
			break;
		case IDC_TRIGGERS_PROACTIVE:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				{
					CheckDlgButton(hWnd, IDC_TRIGGERS_NONE, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_TRIGGERS_RESIST, BST_UNCHECKED);
					CheckDlgButton(hWnd, IDC_TRIGGERS_SHOOT, BST_UNCHECKED);
				}
				CheckDlgButton(hWnd, IDC_TRIGGERS_PROACTIVE, BST_CHECKED);
				tape.TriggersMode = 3;
				tape.Save(tape.Setting_TriggersMode);
				PostMessage(m_hWnd, WM_SETTRIGGERS, 3, 0);
				break;
			}
			break;
		case IDC_TOUCHPAD:
			tape.setTouchPadButton((int)SendMessage(GetDlgItem(hWnd, IDC_TOUCHPAD), CB_GETCURSEL, 0, 0));
			tape.Save(tape.Setting_TouchPadButton);
			PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
			break;
		case IDC_COL:
			tape.setTouchCol((int)SendMessage(GetDlgItem(hWnd, IDC_COL), CB_GETCURSEL, 0, 0) + 1);
			tape.Save(tape.Setting_TouchCol);
			PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
			break;
		case IDC_ROW:
			tape.setTouchRow((int)SendMessage(GetDlgItem(hWnd, IDC_ROW), CB_GETCURSEL, 0, 0) + 1);
			tape.Save(tape.Setting_TouchRow);
			PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
			break;
		case IDC_COLOR:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (ChooseColor(&cc))
				{
					tape.setLED(cc.rgbResult);
					tape.Save(tape.Setting_LED_Color);
					PostMessage(hWnd, WM_DEVICE_DS_START, 0, 1);
					RedrawWindow(m_hDlg, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW);
				}
				break;
			}
			break;
		}
		default:
			return FALSE;
		}
		break;
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

BOOL SettingDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
