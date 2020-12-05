#include "stdafx.h"
#include "resource.h"
#include "KeymapDataDlg.h"
#include "FindwindowDlg.h"

KeymapDataDlg::KeymapDataDlg()
{
}


KeymapDataDlg::~KeymapDataDlg()
{
}

BOOL CALLBACK keymapdataEnumWindowsProc(HWND hWnd, LPARAM lParam) {
	TCHAR strWindowText[1024] = L"";
	TCHAR strClassText[1024] = L"";
	TCHAR str[1024];
	//if (!IsWindowVisible(hWnd)) return TRUE;
	GetWindowText(hWnd, strWindowText, 1024);
	GetClassName(hWnd, strClassText, 1024);

	HWND combo = (HWND)lParam;
	wsprintf(str, L"%s, %s", strClassText, strWindowText);
	LRESULT idx = SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)str);
	if (idx == CB_ERR || idx == CB_ERRSPACE) {
		return TRUE;
	}
	SendMessage(combo, CB_SETITEMDATA, idx, (LPARAM)hWnd);
	return TRUE;
}

BOOL KeymapDataDlg::Open(HWND hWnd)
{
	HINSTANCE h = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	m_hWnd = hWnd;
	switch (DialogBoxParam(h, L"IDD_INPUTKEY", hWnd, (DLGPROC)KeymapDataDlg::Proc, (LPARAM)this))
	{
	case IDOK: {
		return TRUE;
	}
	}
	return FALSE;
}

INT_PTR KeymapDataDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KeymapDataDlg *dlg;
	if (uMsg == WM_INITDIALOG) {
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (KeymapDataDlg *)lParam;
	}
	else {
		dlg = (KeymapDataDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (dlg) {
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	}
	else {
		return NULL;
	}
}
INT_PTR KeymapDataDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		m_hDlg = hWnd;
		initdialog();
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			keymapData.Enable = true;
			return EndDialog(hWnd, IDOK);
		case IDCANCEL:
			return EndDialog(hWnd, IDCANCEL);
		case IDC_KEYMAP_BTN:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				keymapData.ButtonID = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_INPUT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE: {
				keymapData.GetState();
				SetWindowText((HWND)lParam, keymapData.StrVal());
				break;
			}
			default:
				return FALSE;
			}
			break;
		case IDC_POSTMESSAGE:
		{
			BOOL flag = FALSE;
			if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0)) {
				flag = TRUE;
			}
			keymapData.usePostmessage = flag?true:false;
			EnableWindow(GetDlgItem(m_hDlg, IDC_FW_TEXT), flag);
			EnableWindow(GetDlgItem(m_hDlg, IDC_FINDWINDOW), flag);
			break;
		}
		case IDC_FINDWINDOW:
		{
			FindwindowDlg dlg;
			dlg.findwindow = keymapData.findWindow;
			if (dlg.Open(hWnd)) {
				//keymapData.findWindow.Val( dlg.findwindow.Val() );
				keymapData.findWindow = dlg.findwindow;
				SetWindowText(GetDlgItem(m_hDlg, IDC_FW_TEXT), keymapData.findWindow.Val().c_str() );
			}
		}
			break;
	

		}

	default:
		return FALSE;
	}
	return TRUE;
}
INT_PTR KeymapDataDlg::InputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KeymapDataDlg *dlg = (KeymapDataDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_inputProc(hWnd, uMsg, wParam, lParam);
	return 0;
}
INT_PTR KeymapDataDlg::_inputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_GETDLGCODE:
		return DLGC_WANTALLKEYS;
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		keymapData.GetState();
		SetWindowText(hWnd, keymapData.StrVal());
		return TRUE;
	}
	break;
	}
	return CallWindowProc(m_defaultInputProc, hWnd, uMsg, wParam, lParam);
}

void KeymapDataDlg::initdialog()
{
	HWND hInput = GetDlgItem(m_hDlg, IDC_INPUT);
	SetWindowLongPtr(hInput,GWLP_USERDATA, (LONG_PTR)this);
	m_defaultInputProc = (WNDPROC)SetWindowLongPtr(hInput, GWLP_WNDPROC, (LONG_PTR)InputProc);
	SetFocus(hInput);
	SetWindowText(hInput, keymapData.StrVal());

	HWND hBtn = GetDlgItem(m_hDlg, IDC_KEYMAP_BTN);
	for (int i = 0; i < vJoyButtonID::button_Count; i++) {
		WCHAR *str = vJoyButton::String((vJoyButtonID)i);
		SendMessage(hBtn, CB_ADDSTRING, 0, (LPARAM)str);
	}
	SendMessage(hBtn, CB_SETCURSEL, (WPARAM)keymapData.ButtonID, 0);
	if (keymapData.usePostmessage) {
		SendMessage(GetDlgItem(m_hDlg, IDC_POSTMESSAGE), BM_SETCHECK, BST_CHECKED, 0);
	}
	else {
		EnableWindow(GetDlgItem(m_hDlg, IDC_FW_TEXT), FALSE);
		EnableWindow(GetDlgItem(m_hDlg, IDC_FINDWINDOW), FALSE);
	}
	SetWindowText(GetDlgItem(m_hDlg, IDC_FW_TEXT), keymapData.findWindow.Val().c_str());

}

