#include "stdafx.h"
#include "resource.h"
#include "DS5Button.h"
#include "vJoyButton.h"
#include "MappingDataDlg.h"
#include "Language.h"

MappingDataDlg::MappingDataDlg()
{
}


MappingDataDlg::~MappingDataDlg()
{
}

BOOL MappingDataDlg::Open(HWND hWnd)
{
	HINSTANCE h = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	m_hWnd = hWnd;
	switch (DialogBoxParam(h, L"IDD_ADD_MAPPING", hWnd, (DLGPROC)Proc,(LPARAM)this))
	{
	case IDOK: {
		return TRUE;
		break;
	}
	}
	return FALSE;
}

INT_PTR MappingDataDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MappingDataDlg *dlg;
	if (uMsg == WM_INITDIALOG) {
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (MappingDataDlg *)lParam;
	}
	else {
		dlg = (MappingDataDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (dlg) {
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	}
	else {
		return NULL;
	}
}


INT_PTR MappingDataDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			if (mappingData.DS5ID[0] == 0 || mappingData.vJoyID == 0) {
				MessageBox(hWnd, I18N.MBOX_NoButtonSelected, I18N.MBOX_ErrTitle , MB_ICONERROR);
				return TRUE;
			}
			int offset = 1;
			for (int i = 1; i < 4; i++) {
				if (mappingData.DS5ID[offset]) {
					offset++;
				}else if (mappingData.DS5ID[i]) {
					mappingData.Disbale[offset] = mappingData.Disbale[i];
					mappingData.DS5ID[offset++] = mappingData.DS5ID[i];
					mappingData.DS5ID[i] = DS5ButtonID::none;
					mappingData.Disbale[i] = 0;
				}
			}
			mappingData.Enable = true;
			return EndDialog(hWnd, IDOK);
		}
		case IDCANCEL:
			return EndDialog(hWnd, IDCANCEL);
		case IDC_MAPPING_DS5_1_DISABLE:
			mappingData.Disbale[0] = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0)== BST_CHECKED;
			break;
		case IDC_MAPPING_DS5_2_DISABLE:
			mappingData.Disbale[1] = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
			break;
		case IDC_MAPPING_DS5_3_DISABLE:
			mappingData.Disbale[2] = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
			break;
		case IDC_MAPPING_DS5_4_DISABLE:
			mappingData.Disbale[3] = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
			break;
		case IDC_MAPPING_FORCE:
			mappingData.Force = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
			break;
		case IDC_MAPPING_TOGGLE:
			mappingData.Toggle = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
			break;
		case IDC_MAPPING_DS5_1:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				mappingData.DS5ID[0] = (DS5ButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_MAPPING_DS5_2:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				mappingData.DS5ID[1] = (DS5ButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_MAPPING_DS5_3:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				mappingData.DS5ID[2] = (DS5ButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_MAPPING_DS5_4:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				mappingData.DS5ID[3] = (DS5ButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_MAPPING_VJOY:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				mappingData.vJoyID = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void MappingDataDlg::initdialog()
{
	HWND ds5_1 = GetDlgItem(m_hDlg, IDC_MAPPING_DS5_1);
	HWND ds5_2 = GetDlgItem(m_hDlg, IDC_MAPPING_DS5_2);
	HWND ds5_3 = GetDlgItem(m_hDlg, IDC_MAPPING_DS5_3);
	HWND ds5_4 = GetDlgItem(m_hDlg, IDC_MAPPING_DS5_4);
	HWND vjoy = GetDlgItem(m_hDlg, IDC_MAPPING_VJOY);

	for (int i = 0; i < DS5ButtonID::button_Count; i++) {
		WCHAR *str = DS5Button::String((DS5ButtonID)i);
		SendMessage(ds5_1, CB_ADDSTRING, 0, (LPARAM)str);
		SendMessage(ds5_2, CB_ADDSTRING, 0, (LPARAM)str);
		SendMessage(ds5_3, CB_ADDSTRING, 0, (LPARAM)str);
		SendMessage(ds5_4, CB_ADDSTRING, 0, (LPARAM)str);
	}
	for (int i = 0; i < vJoyButtonID::button_Count; i++) {
		WCHAR *str = vJoyButton::String((vJoyButtonID)i);
		SendMessage(vjoy, CB_ADDSTRING, 0, (LPARAM)str);
	}

	SendMessage(ds5_1, CB_SETCURSEL, (WPARAM)mappingData.DS5ID[0], 0);
	SendMessage(ds5_2, CB_SETCURSEL, (WPARAM)mappingData.DS5ID[1], 0);
	SendMessage(ds5_3, CB_SETCURSEL, (WPARAM)mappingData.DS5ID[2], 0);
	SendMessage(ds5_4, CB_SETCURSEL, (WPARAM)mappingData.DS5ID[3], 0);
	if (mappingData.Disbale[0])
		SendMessage(GetDlgItem(m_hDlg, IDC_MAPPING_DS5_1_DISABLE), BM_SETCHECK, BST_CHECKED, 0);
	if (mappingData.Disbale[1])
		SendMessage(GetDlgItem(m_hDlg, IDC_MAPPING_DS5_2_DISABLE), BM_SETCHECK, BST_CHECKED, 0);
	if (mappingData.Disbale[2])
		SendMessage(GetDlgItem(m_hDlg, IDC_MAPPING_DS5_3_DISABLE), BM_SETCHECK, BST_CHECKED, 0);
	if (mappingData.Disbale[3])
		SendMessage(GetDlgItem(m_hDlg, IDC_MAPPING_DS5_4_DISABLE), BM_SETCHECK, BST_CHECKED, 0);
	SendMessage(vjoy, CB_SETCURSEL, (WPARAM)mappingData.vJoyID, 0);
	if (mappingData.Force)
		SendMessage(GetDlgItem(m_hDlg, IDC_MAPPING_FORCE), BM_SETCHECK, BST_CHECKED, 0);
	if (mappingData.Toggle)
		SendMessage(GetDlgItem(m_hDlg, IDC_MAPPING_TOGGLE), BM_SETCHECK, BST_CHECKED, 0);

}
