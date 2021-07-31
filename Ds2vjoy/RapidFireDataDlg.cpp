#include "stdafx.h"
#include "RapidFireDataDlg.h"
#include "Ds2vJoy.h"

RapidFireDataDlg::RapidFireDataDlg()
{
}

RapidFireDataDlg::~RapidFireDataDlg()
{
}

void RapidFireDataDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_idx = -2;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_RAPIDFIRE_ADD), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hWnd = hWnd;
	Hide();
}

void RapidFireDataDlg::Open(HWND parent, int idx)
{
	m_idx = idx;
	ShowWindow(parent, SW_HIDE);
	ShowWindow(m_hDlg, SW_SHOW);
	PostMessage(m_hWnd, WM_SIZE, 0, -1);
}

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

INT_PTR RapidFireDataDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor;
		if (!hBrushColor)
			hBrushColor = CreateSolidBrush(RGB(210, 210, 215));
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
			DeleteObject(brush);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
		if (wParam == TRUE)
		{
			SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN, CB_SETCURSEL, (WPARAM)autoFireData.ButtonID, 0);
			SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN2, CB_SETCURSEL, (WPARAM)autoFireData.ButtonID2, 0);
			WCHAR buf[256];
			wsprintf(buf, L"%d", autoFireData.Firsttime);
			SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_FIRST), buf);
			wsprintf(buf, L"%d", autoFireData.Releasetime);
			SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_RELEASE), buf);
			wsprintf(buf, L"%d", autoFireData.Presstime);
			SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_DOWN), buf);
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
			if (autoFireData.ButtonID == 0 && autoFireData.ButtonID2 == 0)
			{
				RECT rect;
				GetWindowRect(m_hWnd, &rect);
				MessageBoxPos(hWnd, I18N.MBOX_NoButtonSelected, I18N.MBOX_ErrTitle, MB_ICONERROR, rect.left + 275, rect.top + 30);
				return TRUE;
			}
			autoFireData.Enable = true;
			PostMessage(m_hWnd, WM_ADDRAPIDFIRE, m_idx, 1);
			m_idx = -2;
			break;
		}
		case IDCANCEL:
		{
			PostMessage(m_hWnd, WM_ADDRAPIDFIRE, 0, 0);
			m_idx = -2;
			break;
		}
		case IDC_RAPIDFIRE_BTN:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				autoFireData.ButtonID = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_RAPIDFIRE_BTN2:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				autoFireData.ButtonID2 = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_RAPIDFIRE_FIRST:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[256];
				if (GetWindowText((HWND)lParam, buf, 256) != 0)
					autoFireData.Firsttime = _wtoi(buf);
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
				WCHAR buf[256];
				if (GetWindowText((HWND)lParam, buf, 256) != 0)
					autoFireData.Releasetime = _wtoi(buf);
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
				WCHAR buf[256];
				if (GetWindowText((HWND)lParam, buf, 256) != 0)
					autoFireData.Presstime = _wtoi(buf);
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
