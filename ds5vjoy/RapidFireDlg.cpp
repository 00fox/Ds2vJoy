#include "stdafx.h"
#include "ds5vjoy.h"
#include "resource.h"
#include "Settings.h"
#include "RapidFireDlg.h"
#include "RapidFireDataDlg.h"
#include "Language.h"

RapidFireDlg::RapidFireDlg()
{
}


RapidFireDlg::~RapidFireDlg()
{
}

void RapidFireDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_RAPIDFIRE), hWnd, (DLGPROC)Proc, (LPARAM)this);

	m_hList = GetDlgItem(m_hDlg, IDC_RAPIDFIRE_LIST);

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	col.pszText = I18N.vJoyButton;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = I18N.Setting;
	col.cx = 400;
	ListView_InsertColumn(m_hList, 1, &col);


	m_hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_MAPPING));

}

INT_PTR RapidFireDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RapidFireDlg *dlg;
	if (uMsg == WM_INITDIALOG) {
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (RapidFireDlg *)lParam;
	}
	else {
		dlg = (RapidFireDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (dlg) {
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	}
	else {
		return NULL;
	}
}
INT_PTR RapidFireDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE) {
			load();
		}
		else {
			save();
		}
		break;
	}
	case WM_SIZE: {
		::MoveWindow(m_hList, 0, 0, LOWORD(lParam), HIWORD(lParam), FALSE);
		break;
	}
	case WM_NOTIFY: {
		switch (((LPNMHDR)lParam)->idFrom) {
		case IDC_RAPIDFIRE_LIST:
			switch (((LPNMLISTVIEW)lParam)->hdr.code) {
			case NM_DBLCLK:
				editRapidFireDlg();
				break;
			case NM_RCLICK: {
				POINT pt;
				GetCursorPos(&pt);
				TrackPopupMenu((HMENU)GetSubMenu(m_hMenu, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, m_hDlg, NULL);
				break;
			}
			case LVN_ITEMCHANGED:
				if (m_active) {
					DWORD newstate = (((LPNMLISTVIEW)lParam)->uNewState & LVIS_STATEIMAGEMASK);
					if (newstate != (((LPNMLISTVIEW)lParam)->uOldState & LVIS_STATEIMAGEMASK)) {
						RapidFire *data = (RapidFire *)((LPNMLISTVIEW)lParam)->lParam;
						if (data != 0) {
							data->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
							m_change = true;
						}
					}
					break;
				}			default:
				return FALSE;
			}
		default:
			return FALSE;
		}
		break;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_MENU_MAPPING_ADD:
			addRapidFireDlg();
			break;
		case ID_MENU_MAPPING_DEL:
			deleteRapidFire();
			break;
		case ID_MENU_MAPPING_EDIT:
			editRapidFireDlg();
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void RapidFireDlg::load()
{
	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1) {
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL)
			delete (RapidFire*)item.lParam;
		if (!ListView_DeleteItem(m_hList, 0))
			break;

	}
	ListView_DeleteAllItems(m_hList);

	int idx = 0;
	for (auto itr = g_settings.RapidFiredata.begin(); itr != g_settings.RapidFiredata.end(); ++itr) {
		RapidFire * _rf = new RapidFire(itr->second);
		insertRapidFireData(idx++, _rf);
	}
	m_active = true;
	m_change = false;

}

void RapidFireDlg::save()
{
	m_active = false;
	RapidFires newmap;
	if (m_change) {
		if (MessageBox(m_hDlg, I18N.MBOX_Save, I18N.APP_TITLE , MB_YESNO) != IDYES) {
			m_change = false;
		}
	}

	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1) {
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL) {
			RapidFire *data = (RapidFire*)item.lParam;
			if (m_change)
				newmap[data->ButtonID] = *data;
			delete data;
		}
		if (!ListView_DeleteItem(m_hList, 0))
			break;

	}
	ListView_DeleteAllItems(m_hList);

	if (m_change) {
		g_settings.RapidFiredata.swap(newmap);
		g_settings.Save();
		PostMessage(m_hWnd, WM_CHANGE_SETTING, 0, 0);
	}
	m_change = false;
}

void RapidFireDlg::addRapidFireDlg()
{
	RapidFireDataDlg dlg;
	if (dlg.Open(m_hDlg)) {
		int idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
		if (idx == -1) {
			idx = ListView_GetItemCount(m_hList);
		}
		RapidFire * data = new RapidFire(dlg.rapidFireData);
		insertRapidFireData(idx, data);
		m_change = true;
	}
}

void RapidFireDlg::editRapidFireDlg()
{
	int idx = ListView_GetNextItem(m_hList, -1, LVNI_FOCUSED);
	if (idx == -1) {
		idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
		if (idx == -1) {
			return;
		}
	}
	LV_ITEM item = { 0 };
	item.mask = LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	ListView_GetItem(m_hList, &item);
	if (item.lParam != NULL) {
		RapidFireDataDlg dlg;
		RapidFire* data = (RapidFire*)item.lParam;
		dlg.rapidFireData = *data;
		if (dlg.Open(m_hDlg)) {
			*data = dlg.rapidFireData;
			ListView_DeleteItem(m_hList, idx);
			insertRapidFireData(idx, data);
			m_change = true;
		}
	}
}

void RapidFireDlg::deleteRapidFire()
{
	if (MessageBox(m_hDlg, I18N.MBOX_Delete, I18N.APP_TITLE, MB_YESNO) == IDYES) {
		int idx;
		while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1) {
			LV_ITEM item = { 0 };
			item.mask = LVIF_PARAM;
			item.iItem = idx;
			item.iSubItem = 0;
			ListView_GetItem(m_hList, &item);
			delete (RapidFire*)item.lParam;
			ListView_DeleteItem(m_hList, idx);
			m_change = true;
		}
	}
}

void RapidFireDlg::insertRapidFireData(int idx, RapidFire * _rf)
{
	if (idx < 0)
		return;
	LVITEM item = { 0 };
	bool enable = _rf->Enable;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	item.lParam = (LPARAM)_rf;
	item.pszText = (WCHAR*)_rf->strKey();
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = (WCHAR*)_rf->strVal();
	ListView_SetItem(m_hList, &item);
	ListView_SetCheckState(m_hList, idx, enable);

}

void RapidFireDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);

}

void RapidFireDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);

}

BOOL RapidFireDlg::MoveWindow(int x, int y , int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
