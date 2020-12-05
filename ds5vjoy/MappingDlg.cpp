#include "stdafx.h"
#include "ds5vjoy.h"
#include "Settings.h"
#include "MappingDlg.h"
#include "MappingDataDlg.h"
#include "Language.h"

MappingDlg::MappingDlg()
	:m_dragflag(false)
{
}


MappingDlg::~MappingDlg()
{
}



void MappingDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_MAPPING), hWnd, (DLGPROC)MappingDlg::Proc, (LPARAM)this);

	m_hList = GetDlgItem(m_hDlg, IDC_MAPPING_LIST);

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.cx = 200;
	col.pszText = I18N.DS5Button;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = I18N.vJoyButton;
	col.cx = 200;
	ListView_InsertColumn(m_hList, 1, &col);
	m_hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_MAPPING));

}
INT_PTR CALLBACK MappingDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MappingDlg *dlg;
	if (uMsg == WM_INITDIALOG) {
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (MappingDlg *)lParam;
	}
	else {
		dlg = (MappingDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (dlg) {
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	}
	else {
		return NULL;
	}
}

INT_PTR MappingDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		case IDC_MAPPING_LIST:
			switch (((LPNMLISTVIEW)lParam)->hdr.code) {
			case LVN_BEGINDRAG:
				BeginDrag(((LPNMLISTVIEW)lParam)->iItem);
				SetFocus(m_hList);
				break;
			case NM_RCLICK: {
				POINT pt;
				GetCursorPos(&pt);
				TrackPopupMenu((HMENU)GetSubMenu(m_hMenu, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, m_hDlg, NULL);
				break;
			}
			case NM_DBLCLK:
				editMappingDataDlg();
				break;
			case LVN_ITEMCHANGED:
				if (m_active) {
					DWORD newstate = (((LPNMLISTVIEW)lParam)->uNewState & LVIS_STATEIMAGEMASK);
					if (newstate != (((LPNMLISTVIEW)lParam)->uOldState & LVIS_STATEIMAGEMASK)) {
						Mapping * btn = (Mapping *) ((LPNMLISTVIEW)lParam)->lParam;
						if (btn != 0) {
							btn->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
							m_change =true;
						}
					}
					break;
				}
			}
			break;
		default:
			return FALSE;
		}
		break;
	}
	case WM_MOUSEMOVE:
		if ( m_dragflag && GetCapture() == hWnd) {
			DragMove(LOWORD(lParam), HIWORD(lParam));
		}
		break;

	case WM_LBUTTONUP:
		if ( m_dragflag && GetCapture() == hWnd){
			EndDrag(LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_MENU_MAPPING_ADD:
			addMappingDataDlg();
			break;
		case ID_MENU_MAPPING_DEL:
			deleteMappingData();
			break;
		case ID_MENU_MAPPING_EDIT:
			editMappingDataDlg();
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}



int MappingDlg::insertMappingData(int idx, Mapping *btn)
{
	if (idx < 0)
		return false;
	LVITEM item = { 0 };
	bool enable = btn->Enable;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	item.lParam = (LPARAM)btn;
	item.pszText = (WCHAR*)btn->StrDS5();
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = (WCHAR*)btn->StrvJoy();
	ListView_SetItem(m_hList, &item);
	ListView_SetCheckState(m_hList, idx, enable);

	return ret;
}

void MappingDlg::load()
{
	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1) {
		LVITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL)
			delete (Mapping*)item.lParam;
		if (!ListView_DeleteItem(m_hList, 0))
			break;
	}
	ListView_DeleteAllItems(m_hList);
	SetFocus(m_hList);
	size_t len = g_settings.Mappingdata.size();
	for (int i = 0; i < len; i++) {
		Mapping * btn = new Mapping(g_settings.Mappingdata[i]);
		insertMappingData(i, btn);
	}
	m_change = false;
	m_active = true;

}

void MappingDlg::save()
{
	m_active = false;
	if (m_change) {
		if (MessageBox(m_hDlg,I18N.MBOX_Save, I18N.APP_TITLE, MB_YESNO) != IDYES) {
			m_change = false;
		}
	}
	Mappings newmap;
	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1) {
		LVITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL) {
			if (m_change)
				newmap.push_back(*(Mapping*)item.lParam);
			delete (Mapping*)item.lParam;
		}
		if (!ListView_DeleteItem(m_hList, 0))
			break;
	}
	ListView_DeleteAllItems(m_hList);

	if (m_change) {
		g_settings.Mappingdata.swap(newmap);
		g_settings.Save();
		PostMessage(m_hWnd, WM_CHANGE_SETTING, 0, 0);
	}
}

void MappingDlg::BeginDrag(int idx)
{
	if (ListView_GetNextItem(m_hList, -1, LVNI_SELECTED) == -1)
		return;
	m_dragflag = true;
	SetCapture(m_hDlg);
}

void MappingDlg::DragMove(int x, int y)
{
	LV_HITTESTINFO  ht;
	ht.pt.x = x;
	ht.pt.y = y;
	ListView_HitTest(m_hList, &ht);
	if ((ht.flags & LVHT_ONITEM) != 0) {
		setInsertMark(ht.iItem);
		//ListView_Scroll(m_hList, 0 , 2);
	}
	else {
		setInsertMark(-1);
	}
}

void MappingDlg::EndDrag(int x, int y)
{
	setInsertMark(-1);
	m_dragflag = false;
	ReleaseCapture();

	LV_HITTESTINFO  ht;
	ht.pt.x = x;
	ht.pt.y = y;

	ListView_HitTest(m_hList, &ht);

	if ((ht.flags & LVHT_ONITEM) != 0)
	{
		LV_ITEM item = { 0 };
		item.mask = TVIF_HANDLE;
		item.iItem = ht.iItem;
		item.iSubItem = 0;
		ListView_GetItem(m_hList, &item);

		item.iItem = ht.iItem;
		item.iSubItem = 0;
		item.mask = LVIF_STATE;
		item.stateMask = LVIS_SELECTED;
		ListView_GetItem(m_hList, &item);
		if (item.state & LVIS_SELECTED)
			return;
		int idx;
		while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1) {
			LV_ITEM item = { 0 };
			item.mask = LVIF_PARAM;
			item.iItem = idx;
			item.iSubItem = 0;
			ListView_GetItem(m_hList, &item);
			int ret = insertMappingData(ht.iItem, (Mapping*)item.lParam);
			if (ht.iItem < idx)
				ht.iItem++;
			if (ret <= idx)
				idx++;
			ListView_DeleteItem(m_hList, idx);
			m_change = true;
		}
	}

}


void MappingDlg::setInsertMark(int idx)
{
	if (m_insrtpos != idx) {
		LVINSERTMARK mark = { 0 };
		mark.cbSize = sizeof(LVINSERTMARK);
		mark.dwFlags = 0;
		mark.iItem = idx;
		SendMessage(m_hList, LVM_SETINSERTMARK, 0, (LPARAM)&mark);
		m_insrtpos = idx;
	}
}

void MappingDlg::addMappingDataDlg()
{
	MappingDataDlg dlg;
	if (dlg.Open(m_hDlg)) {

		int idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
		if (idx == -1) {
			idx = ListView_GetItemCount(m_hList);
		}
		Mapping * btn = new Mapping(dlg.mappingData);
		insertMappingData(idx, btn);
		m_change = true;
	}
}

void MappingDlg::editMappingDataDlg()
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
		MappingDataDlg dlg;
		Mapping* btn = (Mapping*)item.lParam;
		dlg.mappingData = *btn;
		if (dlg.Open(m_hDlg)) {
			*btn = dlg.mappingData;
			ListView_DeleteItem(m_hList, idx);
			insertMappingData(idx, btn);
			m_change = true;
		}
	}
}


void MappingDlg::deleteMappingData()
{
	if (MessageBox(m_hDlg,I18N.MBOX_Delete, I18N.APP_TITLE , MB_YESNO) == IDYES) {
		int idx;
		while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1) {
			LV_ITEM item = { 0 };
			item.mask = LVIF_PARAM;
			item.iItem = idx;
			item.iSubItem = 0;
			ListView_GetItem(m_hList, &item);
			delete (Mapping*)item.lParam;
			ListView_DeleteItem(m_hList, idx);
			m_change = true;
		}
	}
}


void MappingDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}

void MappingDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);
}

BOOL MappingDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
