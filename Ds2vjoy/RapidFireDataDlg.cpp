#include "stdafx.h"
#include "RapidFireDataDlg.h"
#include "Ds2vJoy.h"

RapidFireDataDlg::RapidFireDataDlg()
	:m_hWnd()
	,m_parent()
	,m_hDlg()
	,m_mode(0)
	,canprint(false)
	,rapidFireData()
	,Modified()
{
	for (int i = 0; i < Mofified_count; i++)
		Modified[i] = false;
}

RapidFireDataDlg::~RapidFireDataDlg()
{
}

void RapidFireDataDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_RAPIDFIRE_ADD), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hWnd = hWnd;
	Hide();
}

void RapidFireDataDlg::Open(HWND parent, int mode)
{
	m_mode = mode;
	canprint = false;
	ShowWindow(parent, SW_HIDE);
	ShowWindow(m_hDlg, SW_SHOW);
	PostMessage(m_hWnd, WM_SIZE, 0, -1);
}

/*
INT_PTR RapidFireDataDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RapidFireDataDlg* dlg;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (RapidFireDataDlg*)lParam;
	}
	else
		dlg = (RapidFireDataDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	else
		return NULL;
}
*/

INT_PTR CALLBACK RapidFireDataDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	RapidFireDataDlg* dlg;

	if (uMsg == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<RapidFireDataDlg*>(lparam);
		SetWindowLongPtrW(hWnd, DWLP_USER, lparam);
	}
	else
		dlg = reinterpret_cast<RapidFireDataDlg*>(GetWindowLongPtrW(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, uMsg, wparam, lparam);
		return result;
	}
	return DefWindowProcW(hWnd, uMsg, wparam, lparam);
}

INT_PTR RapidFireDataDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
		if (wParam == TRUE)
		{
			SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN, CB_SETCURSEL, rapidFireData.ButtonID, 0);
			SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN2, CB_SETCURSEL, rapidFireData.ButtonID2, 0);

			canprint = false;
			WCHAR buf[MAX_PATH];
			wsprintf(buf, L"%d", rapidFireData.Firsttime);
			SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_FIRST), buf);
			wsprintf(buf, L"%d", rapidFireData.Releasetime);
			SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_RELEASE), buf);
			wsprintf(buf, L"%d", rapidFireData.Presstime);
			SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_DOWN), buf);
			canprint = true;
		}
		break;
	case WM_INITDIALOG:
	{
		for (int i = 0; i < vJoyButtonID::button_Count; i++)
		{
			WCHAR* str = vJoyButton::String((vJoyButtonID)i);
			SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN, CB_ADDSTRING, 0, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN2, CB_ADDSTRING, 0, (LPARAM)str);
		}
		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: {
			if (rapidFireData.ButtonID == 0 && rapidFireData.ButtonID2 == 0 && m_mode != 3)
			{
				RECT rect;
				GetWindowRect(m_hWnd, &rect);
				MessageBoxPos(hWnd, I18N.MBOX_NoButtonSelected, I18N.MBOX_ErrTitle, MB_ICONERROR, rect.left + 275, rect.top + 30);
				return TRUE;
			}
			rapidFireData.Enable = true;
			PostMessage(m_hWnd, WM_ADDRAPIDFIRE, m_mode, 1);
			m_mode = 0;
			break;
		}
		case IDCANCEL:
		{
			PostMessage(m_hWnd, WM_ADDRAPIDFIRE, 0, 0);
			m_mode = 0;
			break;
		}
		case IDC_RAPIDFIRE_BTN:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				rapidFireData.ButtonID = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_ButtonID] = true;
			}
			break;
		case IDC_RAPIDFIRE_BTN2:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				rapidFireData.ButtonID2 = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_ButtonID2] = true;
			}
			break;
		case IDC_RAPIDFIRE_FIRST:
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
			default:
				return FALSE;
			}
			break;
		case IDC_RAPIDFIRE_RELEASE:
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
			default:
				return FALSE;
			}
			break;
		case IDC_RAPIDFIRE_DOWN:
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
			default:
				return FALSE;
			}
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void RapidFireDataDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}

void RapidFireDataDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);
}

BOOL RapidFireDataDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
