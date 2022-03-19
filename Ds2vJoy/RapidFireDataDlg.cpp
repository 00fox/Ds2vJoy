#include "stdafx.h"
#include "RapidFireDataDlg.h"

RapidFireDataDlg::RapidFireDataDlg()
{
}

RapidFireDataDlg::~RapidFireDataDlg()
{
}

void RapidFireDataDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_RAPIDFIRE_ADD), hWnd, (DLGPROC)Proc, LPARAM(this));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_RAPIDFIRE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_BTN, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_MULTIPLE_PRESS, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_BTN2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_TEXT_FIRST, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_TEXT_RELEASE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_TEXT_DOWN, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_UNIT_FIRST, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_UNIT_RELEASE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_UNIT_DOWN, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_FIRST, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_RELEASE, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_DOWN, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_OK, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_CANCEL, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_NOTICE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_RAPIDFIRE), I18N.RAPIDFIRE_RAPIDFIRE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_MULTIPLE_PRESS), I18N.RAPIDFIRE_MULTIPLE_PRESS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_TEXT_FIRST), I18N.RAPIDFIRE_TEXT_FIRST);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_TEXT_RELEASE), I18N.RAPIDFIRE_TEXT_RELEASE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_TEXT_DOWN), I18N.RAPIDFIRE_TEXT_DOWN);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_UNIT_FIRST), I18N.RAPIDFIRE_UNIT_FIRST);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_UNIT_RELEASE), I18N.RAPIDFIRE_UNIT_RELEASE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_UNIT_DOWN), I18N.RAPIDFIRE_UNIT_DOWN);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_NOTICE), I18N.RAPIDFIRE_NOTICE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_OK), I18N.RAPIDFIRE_OK);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_CANCEL), I18N.RAPIDFIRE_CANCEL);
	Hide();
}

void RapidFireDataDlg::Open(HWND parent, int mode)
{
	m_mode = mode;
	canprint = false;
	ShowWindow(parent, SW_HIDE);
	Show();
	PostMessage(m_hWnd, WM_SIZE, 0, -1);
}

void RapidFireDataDlg::_InitDialog(HWND hWnd)
{
	for (int i = 0; i < vJoyButtonID::button_Count; i++)
	{
		WCHAR* str = vJoyButton::String((vJoyButtonID)i);
		SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN2, CB_ADDSTRING, 0, LPARAM(str));
	}

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void RapidFireDataDlg::_ShowWindow(HWND hWnd)
{
	SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN, CB_SETCURSEL, rapidFireData.ButtonID, 0);
	SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN2, CB_SETCURSEL, rapidFireData.ButtonID2, 0);

	canprint = false;
	WCHAR buf[MAX_PATH];
	swprintf_s(buf, MAX_PATH, L"%d", rapidFireData.Firsttime);
	SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_FIRST), buf);
	swprintf_s(buf, MAX_PATH, L"%d", rapidFireData.Releasetime);
	SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_RELEASE), buf);
	swprintf_s(buf, MAX_PATH, L"%d", rapidFireData.Presstime);
	SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_DOWN), buf);
	canprint = true;
}

INT_PTR CALLBACK RapidFireDataDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RapidFireDataDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<RapidFireDataDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<RapidFireDataDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR RapidFireDataDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		SetTextColor(hdcStatic, tape.ink_STATIC);
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
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
			std::thread(&RapidFireDataDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&RapidFireDataDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_RAPIDFIRE_OK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (rapidFireData.ButtonID == 0 && rapidFireData.ButtonID2 == 0 && m_mode != 3)
				{
					RECT win;
					GetWindowRect(m_hWnd, &win);
					MessageBoxPos(hWnd, I18N.MBOX_NoButtonSelected, I18N.MBOX_ErrTitle, MB_ICONERROR, win.left + 275, win.top + 30);
					return TRUE;
				}
				rapidFireData.Enable = true;
				PostMessage(m_hWnd, WM_ADDRAPIDFIRE, m_mode, 1);
				m_mode = 0;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_CANCEL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				PostMessage(m_hWnd, WM_ADDRAPIDFIRE, 0, 0);
				m_mode = 0;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_BTN:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				rapidFireData.ButtonID = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_ButtonID] = true;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_BTN2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				rapidFireData.ButtonID2 = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_ButtonID2] = true;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_FIRST:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf1[MAX_PATH];
				GetWindowText((HWND)lParam, buf1, MAX_PATH);
				rapidFireData.Firsttime = max(0, _wtoi(buf1));
				if (canprint) Modified[Mofified_Firsttime] = true;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_RELEASE:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf2[MAX_PATH];
				GetWindowText((HWND)lParam, buf2, MAX_PATH);
				rapidFireData.Releasetime = max(0, _wtoi(buf2));
				if (canprint) Modified[Mofified_Releasetime] = true;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_DOWN:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf3[MAX_PATH];
				GetWindowText((HWND)lParam, buf3, MAX_PATH);
				rapidFireData.Presstime = max(0, _wtoi(buf3));
				if (canprint) Modified[Mofified_Presstime] = true;
				break;
			}
			}
			break;
		}
		}
		break;
	}
	default:
		return FALSE;
	}
	return TRUE;
}

void RapidFireDataDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void RapidFireDataDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL RapidFireDataDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
