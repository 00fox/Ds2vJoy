#include "stdafx.h"
#include "resource.h"
#include "RapidFireDataDlg.h"
#include "Language.h"

RapidFireDataDlg::RapidFireDataDlg()
{
}


RapidFireDataDlg::~RapidFireDataDlg()
{
}

BOOL RapidFireDataDlg::Open(HWND hWnd)
{
	HINSTANCE h = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	m_hWnd = hWnd;
	switch (DialogBoxParam(h, L"IDD_ADD_RAPIDFIRE", hWnd, (DLGPROC)Proc, (LPARAM)this))
	{
	case IDOK: {
		return TRUE;
		break;
	}
	}
	return FALSE;
}

INT_PTR RapidFireDataDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RapidFireDataDlg *dlg;
	if (uMsg == WM_INITDIALOG) {
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (RapidFireDataDlg *)lParam;
	}
	else {
		dlg = (RapidFireDataDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (dlg) {
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	}
	else {
		return NULL;
	}
}

INT_PTR RapidFireDataDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		m_hDlg = hWnd;
		initdialog();
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: {
			if (rapidFireData.ButtonID == 0 ) {
				MessageBox(hWnd, I18N.MBOX_NoButtonSelected, I18N.MBOX_ErrTitle, MB_ICONERROR);
				return TRUE;
			}
			rapidFireData.Enable = true;
			return EndDialog(hWnd, IDOK);
		}
		case IDCANCEL:
			return EndDialog(hWnd, IDCANCEL);
		case IDC_RAPIDFIRE_BTN:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				rapidFireData.ButtonID = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_RAPIDFIRE_BTN2:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				rapidFireData.ButtonID2 = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_RAPIDFIRE_FIRST:
			switch (HIWORD(wParam)) {
			case EN_UPDATE: {
				WCHAR buf[256];
				if (GetWindowText((HWND)lParam, buf, 256) != 0) {
					rapidFireData.Firsttime = _wtoi(buf);
				}
				break;
			}
			default:
				return FALSE;
			}
			break;
		case IDC_RAPIDFIRE_RELEASE:
			switch (HIWORD(wParam)) {
			case EN_UPDATE: {
				WCHAR buf[256];
				if (GetWindowText((HWND)lParam, buf, 256) != 0) {
					rapidFireData.Releasetime = _wtoi(buf);
				}
				break;
			}
			default:
				return FALSE;
			}
			break;
		case IDC_RAPIDFIRE_DOWN:
			switch (HIWORD(wParam)) {
			case EN_UPDATE: {
				WCHAR buf[256];
				if (GetWindowText((HWND)lParam, buf, 256) != 0) {
					rapidFireData.Presstime = _wtoi(buf);
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

void RapidFireDataDlg::initdialog()
{
	HWND btn1 = GetDlgItem(m_hDlg, IDC_RAPIDFIRE_BTN);
	HWND btn2 = GetDlgItem(m_hDlg, IDC_RAPIDFIRE_BTN2);
	for (int i = 0; i < vJoyButtonID::button_Count; i++) {
		WCHAR *str = vJoyButton::String((vJoyButtonID)i);
		SendMessage(btn1, CB_ADDSTRING, 0, (LPARAM)str);
		SendMessage(btn2, CB_ADDSTRING, 0, (LPARAM)str);
	}

	SendMessage(btn1, CB_SETCURSEL, (WPARAM)rapidFireData.ButtonID, 0);
	SendMessage(btn2, CB_SETCURSEL, (WPARAM)rapidFireData.ButtonID2, 0);
	WCHAR buf[256];
	wsprintf(buf, L"%d", rapidFireData.Firsttime);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_FIRST), buf);
	wsprintf(buf, L"%d", rapidFireData.Releasetime);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_RELEASE), buf);
	wsprintf(buf, L"%d", rapidFireData.Presstime);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_DOWN), buf);
}
