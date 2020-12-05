#include "stdafx.h"
#include "ds5vjoy.h"
#include "Settings.h"
#include "KeymapDlg.h"
#include "KeymapDataDlg.h"
#include "Language.h"

KeymapDlg::KeymapDlg()
{
}


KeymapDlg::~KeymapDlg()
{
}
void KeymapDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_KEYMAP), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hList = GetDlgItem(m_hDlg, IDC_KEYMAP);
	m_hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_MAPPING));

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	col.pszText = L"vJoy Button";
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = L"Keyboard";
	col.cx = 400;
	ListView_InsertColumn(m_hList, 1, &col);

	
}


INT_PTR CALLBACK KeymapDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	KeymapDlg *dlg;
	if (uMsg == WM_INITDIALOG) {
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (KeymapDlg *)lParam;
	}
	else {
		dlg = (KeymapDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (dlg) {
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	}
	else {
		return NULL;
	}
}

INT_PTR KeymapDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg){
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE) {
			load();
		} else {
			save();
		}
		break;
	}
	case WM_SIZE:
		::MoveWindow(m_hList, 0, 0, LOWORD(lParam), HIWORD(lParam), FALSE);
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom) {
		case IDC_KEYMAP:
			switch (((LPNMLISTVIEW)lParam)->hdr.code) {
			case NM_DBLCLK:
				editKeymapDlg();
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
						Keymap *data= (Keymap *) ((LPNMLISTVIEW)lParam)->lParam;
						if (data != 0) {
							data->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
							m_change=true;
						}
					}
					break;
				}
			default:
				return FALSE;
			}
			break;
		default:
			return FALSE;
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_MENU_MAPPING_ADD:
			addKeymapDlg();
			break;
		case ID_MENU_MAPPING_DEL:
			deleteKeymap();
			break;
		case ID_MENU_MAPPING_EDIT:
			editKeymapDlg();
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void KeymapDlg::load()
{

	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1) {
		LVITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL) {
			delete (Keymap*)item.lParam;
		}
		if (!ListView_DeleteItem(m_hList, 0))
			break;
	}
	ListView_DeleteAllItems(m_hList);

	size_t max = g_settings.Keymapdata.size();
	for (int i = 0; i < max; ++i) {
		Keymap *data = new Keymap( g_settings.Keymapdata[i] );
		insertKeymapItem(i, data);
	}
	m_active = true;
	m_change = false;
}

void KeymapDlg::save()
{
	m_active = false;
	if (m_change) {
		if (MessageBox(m_hWnd, I18N.MBOX_Save , I18N.APP_TITLE , MB_YESNO) != IDYES) {
			m_change = false;
		}
	}

	Keymaps newKeymaps;
	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1) {
		LVITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL) {
			if (m_change)
				newKeymaps.push_back(*(Keymap*)item.lParam);
			delete (Keymap*)item.lParam;
		}
		if (!ListView_DeleteItem(m_hList, 0))
			break;
	}
	ListView_DeleteAllItems(m_hList);

	if (m_change) {
		g_settings.Keymapdata.swap(newKeymaps);
		g_settings.Save();
		PostMessage(m_hWnd, WM_CHANGE_SETTING, 0, 0);
	}
	m_change = false;
}

bool KeymapDlg::insertKeymapItem(int idx, Keymap *data)
{
	if (idx < 0)
		return false;
	LVITEM item = { 0 };
	bool enable = data->Enable;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	item.lParam = (LPARAM)data;
	item.pszText = (WCHAR*)data->StrKey();
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = (WCHAR*)data->StrVal();
	ListView_SetItem(m_hList, &item);
	ListView_SetCheckState(m_hList, idx, enable);
	return true;
}


bool KeymapDlg::addKeymapDlg()
{
	KeymapDataDlg dlg;
	if (dlg.Open(m_hDlg)) {
		int idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
		if (idx == -1) {
			idx = ListView_GetItemCount(m_hList);
		}
		Keymap * data = new Keymap(dlg.keymapData);
		insertKeymapItem(idx, data);
		m_change = true;
		return true;
	}
	return false;
}

bool KeymapDlg::editKeymapDlg()
{
	int idx = ListView_GetNextItem(m_hList, -1, LVNI_FOCUSED);
	if (idx == -1) {
		idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
		if (idx == -1) {
			return false;
		}
	}

	LV_ITEM item = { 0 };
	item.mask = LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	ListView_GetItem(m_hList, &item);
	if (item.lParam != NULL) {
		KeymapDataDlg dlg;
		Keymap* data = (Keymap*)item.lParam;
		dlg.keymapData = *data;
		if (dlg.Open(m_hDlg)) {
			*data = dlg.keymapData;
			ListView_DeleteItem(m_hList, idx);
			insertKeymapItem(idx, data);
			m_change = true;
		}
	}
	return false;
}

bool KeymapDlg::deleteKeymap()
{
	if (MessageBox(m_hDlg, I18N.MBOX_Delete, I18N.APP_TITLE, MB_YESNO) == IDYES) {
		int idx;
		while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1) {
			LV_ITEM item = { 0 };
			item.mask = LVIF_PARAM;
			item.iItem = idx;
			item.iSubItem = 0;
			ListView_GetItem(m_hList, &item);
			delete (Keymap*)item.lParam;
			ListView_DeleteItem(m_hList, idx);
		}
		m_change = true;
		return true;
	}
	return false;
}



void KeymapDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}


void KeymapDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);
}

BOOL KeymapDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
