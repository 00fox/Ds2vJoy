#include "stdafx.h"
#include "SettingDlg.h"
#include "Startup.h"
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

INT_PTR CALLBACK SettingDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SettingDlg* sDlg;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		sDlg = (SettingDlg*)lParam;
	}
	else
		sDlg = (SettingDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (sDlg)
		return sDlg->_proc(hWnd, uMsg, wParam, lParam);
	else
		return NULL;
}

INT_PTR SettingDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CTLCOLORDLG:
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLORSCROLLBAR:
	{
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor;
		if (!hBrushColor)
			hBrushColor = CreateSolidBrush(RGB(191, 200, 196));
		SetTextColor(hdcStatic, RGB(10, 10, 10));
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, RGB(191, 200, 196));
		return (LRESULT)hBrushColor;
	}
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor;
		if (!hBrushColor)
			hBrushColor = CreateSolidBrush(RGB(210, 210, 215));
		DWORD CtrlID = GetDlgCtrlID((HWND)lParam);
		if (CtrlID == IDC_STATIC_EXITING)
			SetTextColor(hdcStatic, RGB(10, 10, 10));
		else
			SetTextColor(hdcStatic, RGB(100, 93, 79));
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, RGB(36, 163, 163));
		return (LRESULT)hBrushColor;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor;
		if (!hBrushColor)
			hBrushColor = CreateSolidBrush(RGB(228, 228, 232));
		SetTextColor(hdcStatic, RGB(10, 10, 10));
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, RGB(255, 255, 0));
		return (LRESULT)hBrushColor;
	}
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor;
		if (!hBrushColor)
			hBrushColor = CreateSolidBrush(RGB(216, 215, 220));
		SetTextColor(hdcStatic, RGB(10, 10, 10));
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, RGB(255, 255, 0));
		return (LRESULT)hBrushColor;
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			HBRUSH brush = CreateSolidBrush(RGB(210, 210, 215));
			FillRect(hDC, &rect, brush);
//			Rectangle(hDC, 122, 199, 261, 225);
//			RoundRect(hDC, 118, 142, 256, 186, 20, 20);

			EndPaint(hWnd, &ps);

			HWND ledbutton = GetDlgItem(hWnd, IDC_COLOR);
			hDC = BeginPaint(ledbutton, &ps);
			GetClientRect(ledbutton, &rect);

			brush = CreateSolidBrush(RGB(128, 128, 128));
//			DrawEdge(hDC, &rect, EDGE_SUNKEN, BF_RECT);
			DrawEdge(hDC, &rect, EDGE_RAISED, BF_RECT);

			brush = CreateSolidBrush(RGB(210, 210, 215));
			rect.top -= 1;
			rect.left -= 1;
			rect.right += 1;
			rect.bottom += 1;
			DrawFocusRect(hDC, &rect);

			DWORD ledcolor = tape.LED_Color;

			brush = CreateSolidBrush(RGB(GetRValue(ledcolor), GetGValue(ledcolor), GetBValue(ledcolor)));
			rect.top += 4;
			rect.left += 4;
			rect.right -= 4;
			rect.bottom -= 4;
			FillRect(hDC, &rect, brush);

			if (GetRValue(ledcolor) + GetGValue(ledcolor) + GetBValue(ledcolor) > 381)
				SetTextColor(hDC, RGB(45, 45, 45));
			else
				SetTextColor(hDC, RGB(210, 210, 215));

			DrawText(hDC, L"LED", 3, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			DeleteObject(brush);
			EndPaint(ledbutton, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
		{
			CheckDlgButton(hWnd, IDC_DS4, tape.DesiredDS == 1);
			CheckDlgButton(hWnd, IDC_DS5, tape.DesiredDS == 2);
			SendDlgItemMessage(hWnd, IDC_VJOY_DEV, CB_SETCURSEL, (LPARAM)tape.vJoyDeviceID - 1, 0);

			CheckDlgButton(hWnd, IDC_STARTUP, CheckStartUp());
			CheckDlgButton(hWnd, IDC_TASKTRAY, tape.Tasktray);
			CheckDlgButton(hWnd, IDC_CLOSEMINIMIZE, tape.CloseMinimize);
			CheckDlgButton(hWnd, IDC_DISCONNECT_BT, tape.DisconnectBT);
			CheckDlgButton(hWnd, IDC_LOWBATT, tape.LowBattAlert);
			
			CheckDlgButton(hWnd, IDC_FFB, tape.FFB);
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

			HFONT hFont = CreateFont(12, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			SendDlgItemMessage(hWnd, IDC_STATIC_TIMES, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

			hFont = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			SendDlgItemMessage(hWnd, IDC_THRESHOLD, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_SIMULTANEOUS, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_LONGPRESS, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VERYLONGPRESS, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		}
		break;
	}
	case WM_INITDIALOG: {
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

		return TRUE;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDC_DS4:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					CheckDlgButton(hWnd, IDC_DS5, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_DS4, BST_CHECKED);
				tape.DesiredDS = 1;
				tape.Save(100);
				PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 0);
				break;
			}
			break;
		case IDC_DS5:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					CheckDlgButton(hWnd, IDC_DS4, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_DS5, BST_CHECKED);
				tape.DesiredDS = 2;
				tape.Save(100);
				PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 0);
				break;
			}
			break;
		case IDC_VJOY_DEV:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				tape.setvJoyDeviceID((int)SendMessage(GetDlgItem(hWnd, IDC_VJOY_DEV), CB_GETCURSEL, 0, 0) + 1);
				tape.Save(113);
				PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 0);
				break;
			}
			break;
		case IDC_THRESHOLD:
			WCHAR bufThreshold[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_THRESHOLD), bufThreshold, MAX_PATH);
			tape.Threshold = max(0, min(100, _wtoi(bufThreshold)));
			tape.Save(107);
			break;
		case IDC_SIMULTANEOUS:
			WCHAR bufSimultaneous[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_SIMULTANEOUS), bufSimultaneous, MAX_PATH);
			tape.Simultaneous = max(1, min(9999, _wtoi(bufSimultaneous)));
			tape.Save(108);
			break;
		case IDC_LONGPRESS:
			WCHAR bufLongPress[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_LONGPRESS), bufLongPress, MAX_PATH);
			tape.LongPress = max(1, min(9999, _wtoi(bufLongPress)));
			tape.Save(109);
			break;
		case IDC_VERYLONGPRESS:
			WCHAR bufVeryLongPress[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_VERYLONGPRESS), bufVeryLongPress, MAX_PATH);
			tape.VeryLongPress = max(1, min(9999, _wtoi(bufVeryLongPress)));
			tape.Save(110);
			break;
		case IDC_STARTUP:
		{
			bool startup = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			if (startup)
			{
				if (!CheckStartUp())
					CreateStartUp();
			}
			else if (CheckStartUp())
				DeleteStartUp();
			break;
		}
		case IDC_TASKTRAY:
			tape.Tasktray = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(101);
			PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 1);
			break;
		case IDC_CLOSEMINIMIZE:
			tape.CloseMinimize = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(102);
			PostMessage(m_hWnd, WM_DEVICE_VJOY_START, 0, 1);
			break;
		case IDC_DISCONNECT_BT:
			tape.DisconnectBT = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(103);
			break;
		case IDC_LOWBATT:
			tape.LowBattAlert = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(104);
			break;
		case IDC_FFB:
			tape.FFB = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(111);
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
				tape.Save(112);
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
				tape.Save(112);
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
				tape.Save(112);
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
				tape.Save(112);
				PostMessage(m_hWnd, WM_SETTRIGGERS, 3, 0);
				break;
			}
			break;
		case IDC_TOUCHPAD:
			tape.SetTouchPadButton((int)SendMessage(GetDlgItem(hWnd, IDC_TOUCHPAD), CB_GETCURSEL, 0, 0));
			tape.Save(114);
			PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
			break;
		case IDC_ROW:
			tape.SetTouchRow((int)SendMessage(GetDlgItem(hWnd, IDC_ROW), CB_GETCURSEL, 0, 0) + 1);
			tape.Save(115);
			PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
			break;
		case IDC_COL:
			tape.SetTouchCol((int)SendMessage(GetDlgItem(hWnd, IDC_COL), CB_GETCURSEL, 0, 0) + 1);
			tape.Save(116);
			PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
			break;
		case IDC_DS_SERIAL:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[13];
				GetWindowText(GetDlgItem(hWnd, IDC_DS_SERIAL), buf, 13);
				if (lstrcmpW(tape.getSerial(), buf) != 0)
				{
					tape.setSerial(buf);
					tape.Save(105);
					PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 0);
				}
				break;
			}
			break;
		case IDC_LED:
			tape.BlackLedOnExit = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(106);
			break;
		case IDC_COLOR:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (ChooseColor(&cc))
				{
					tape.SetLED(cc.rgbResult);
					tape.Save(117);
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
