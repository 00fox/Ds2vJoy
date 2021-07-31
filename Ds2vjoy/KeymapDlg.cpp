#include "stdafx.h"
#include "KeymapDlg.h"
#include "KeymapDataDlg.h"
#include "Findwindow.h"
#include "Ds2vJoy.h"

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
	m_hList = GetDlgItem(m_hDlg, IDC_KEYMAP_LIST);
	m_hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_MAPPING));

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.cx = 76;
	col.pszText = L"vJoy Button";
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = L"Keyboard";
	col.cx = 379;
	ListView_InsertColumn(m_hList, 1, &col);
}

INT_PTR CALLBACK KeymapDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KeymapDlg* dlg;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (KeymapDlg*)lParam;
	}
	else
		dlg = (KeymapDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	else
		return NULL;
}

INT_PTR KeymapDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SHOWWINDOW:
	{
		SendMessage(m_hList, LVM_SETBKCOLOR, 0, (LPARAM)RGB(210, 210, 215));
		SendMessage(m_hList, LVM_SETTEXTCOLOR, 0, (LPARAM)RGB(10, 10, 10));
		SendMessage(m_hList, LVM_SETTEXTBKCOLOR, 0, (LPARAM)RGB(225, 225, 230));
		if (wParam == TRUE)
			load();
		m_active = true;
		break;
	}
	case WM_SIZE:
		::MoveWindow(m_hList, 0, 0, LOWORD(lParam), HIWORD(lParam), FALSE);
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_KEYMAP_LIST:
			switch (((LPNMLISTVIEW)lParam)->hdr.code)
			{
			case NM_DBLCLK:
				editKeymapDlg();
				break;
			case NM_RCLICK:
				POINT pt;
				GetCursorPos(&pt);
				TrackPopupMenu((HMENU)GetSubMenu(m_hMenu, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, m_hDlg, NULL);
				break;
			case LVN_BEGINDRAG:
				BeginDrag(((LPNMLISTVIEW)lParam)->iItem);
				SetFocus(m_hList);
				break;
			case LVN_ITEMCHANGED:
			{
				if (m_active && !m_flag_drag)
				{
					DWORD newstate = (((LPNMLISTVIEW)lParam)->uNewState & LVIS_STATEIMAGEMASK);
					if (newstate != (((LPNMLISTVIEW)lParam)->uOldState & LVIS_STATEIMAGEMASK))
					{
						Keymap* km = (Keymap*)((LPNMLISTVIEW)lParam)->lParam;
						if (km != 0)
						{
							int idx = ListView_GetNextItem(m_hList, -1, LVNI_FOCUSED);
							if (idx == -1)
							{
								idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
								km->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
								save();
							}
						}
					}
				}
				break;
			}
			default:
				return FALSE;
			}
		default:
			return FALSE;
		}
		break;
	case WM_MOUSEMOVE:
		if (m_flag_drag && GetCapture() == hWnd)
			DragMove(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONUP:
		if (m_flag_drag && GetCapture() == hWnd)
		{
			EndDrag(LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MENU_MAPPING_ADD:
			addKeymapDlg();
			break;
		case ID_MENU_MAPPING_EDIT:
			editKeymapDlg();
			break;
		case ID_MENU_MAPPING_DEL:
			deleteKeymap();
			break;
		case ID_MENU_MAPPING_COPY:
			duplicateKeymap();
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
	m_active = false;
	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1)
		{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL)
			delete (Keymap*)item.lParam;
		if (!ListView_DeleteItem(m_hList, 0))
			break;
	}
	ListView_DeleteAllItems(m_hList);

	size_t length = tape.Keymapdata.size();
	for (int i = 0; i < length; i++)
	{
		Keymap* km = new Keymap(tape.Keymapdata[i]);
		insertKeymap(i, km);
	}
	m_active = true;
}

void KeymapDlg::save()
{
	m_active = false;
	Keymaps newmap;

	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL)
		{
			newmap.push_back(*(Keymap*)item.lParam);
			delete (Keymap*)item.lParam;
		}
		if (!ListView_DeleteItem(m_hList, 0))
			break;
	}
	ListView_DeleteAllItems(m_hList);

	tape.Keymapdata.swap(newmap);
	tape.Save(400);
	PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);

	load();
	RedrawWindow(m_hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW);
	m_active = true;
}

void KeymapDlg::addKeymapDlg()
{
	m_active = false;
	kDDlg.Hide();
	Keymap km;
	kDDlg.keymapData = km;
	kDDlg.alreadydone = false;
	kDDlg.Open(m_hDlg, -1);
	m_active = true;
}

void KeymapDlg::addKeymapDlgBack()
{
	m_active = false;
	int idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
	if (idx == -1)
		idx = ListView_GetItemCount(m_hList);
	Keymap* data = new Keymap(kDDlg.keymapData);
	insertKeymap(idx, data);
	save();
	m_active = true;
}

void KeymapDlg::editKeymapDlg()
{
	kDDlg.Hide();
	int idx = ListView_GetNextItem(m_hList, -1, LVNI_FOCUSED);
	if (idx == -1)
	{
		idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
		if (idx == -1)
			return;
	}
	m_active = false;
	LV_ITEM item = { 0 };
	item.mask = LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	ListView_GetItem(m_hList, &item);
	if (item.lParam != NULL)
	{
		Keymap* data = (Keymap*)item.lParam;
		kDDlg.keymapData = *data;
		kDDlg.alreadydone = false;
		kDDlg.Open(m_hDlg, idx);
	}
	m_active = true;
}

void KeymapDlg::editKeymapDlgBack(int idx)
{
	if (idx == -1)
	{
		idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
		if (idx == -1)
			return;
	}
	m_active = false;
	LV_ITEM item = { 0 };
	item.mask = LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	ListView_GetItem(m_hList, &item);
	if (item.lParam != NULL)
	{
		Keymap* data = (Keymap*)item.lParam;
		*data = kDDlg.keymapData;
		ListView_DeleteItem(m_hList, idx);
		insertKeymap(idx, data);
		save();
	}
	m_active = true;
}

void KeymapDlg::duplicateKeymap()
{
	kDDlg.Hide();
	int idx = ListView_GetNextItem(m_hList, -1, LVNI_FOCUSED);
	if (idx == -1)
	{
		idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
		if (idx == -1)
			return;
	}
	m_active = false;
	LV_ITEM item = { 0 };
	item.mask = LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	ListView_GetItem(m_hList, &item);
	if (item.lParam != NULL)
	{
		Keymap* data = (Keymap*)item.lParam;
		kDDlg.keymapData = *data;
		data = new Keymap(kDDlg.keymapData);
		insertKeymap(idx + 1, data);
		save();
	}
	m_active = true;
}

void KeymapDlg::deleteKeymap()
{
	m_active = false;
	kDDlg.Hide();
	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	if (MessageBoxPos(m_hDlg, I18N.MBOX_Delete, I18N.APP_TITLE, MB_YESNO, rect.left + 160, rect.top + 60) == IDYES)
	{
		int idx;
		while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1)
		{
			LV_ITEM item = { 0 };
			item.mask = LVIF_PARAM;
			item.iItem = idx;
			item.iSubItem = 0;
			ListView_GetItem(m_hList, &item);
			delete (Keymap*)item.lParam;
			ListView_DeleteItem(m_hList, idx);
		}
		save();
	}
	m_active = true;
}

int KeymapDlg::insertKeymap(int idx, Keymap* km)
{
	if (idx < 0)
		return FALSE;
	m_active = false;
	LVITEM item = { 0 };
	bool enable = km->Enable;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	item.lParam = (LPARAM)km;
	item.pszText = (WCHAR*)km->KeyString();
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = (WCHAR*)km->ValueString();
	ListView_SetItem(m_hList, &item);
	ListView_SetCheckState(m_hList, idx, enable);

	m_active = true;
	return ret;
}

void KeymapDlg::BeginDrag(int idx)
{
	if (ListView_GetNextItem(m_hList, -1, LVNI_SELECTED) == -1)
		return;
	m_flag_drag = true;
	SetCapture(m_hDlg);
}

void KeymapDlg::DragMove(int x, int y)
{
	LV_HITTESTINFO ht;
	ht.pt.x = x;
	ht.pt.y = y;
	ListView_HitTest(m_hList, &ht);
	if ((ht.flags & LVHT_ONITEM) != 0)
	{
		setInsertMark(ht.iItem);
		//ListView_Scroll(m_hList, 0 , 2);
	}
	else
		setInsertMark(-1);
}

void KeymapDlg::EndDrag(int x, int y)
{
	setInsertMark(-1);
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
		while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1)
		{
			LV_ITEM item = { 0 };
			item.mask = LVIF_PARAM;
			item.iItem = idx;
			item.iSubItem = 0;
			ListView_GetItem(m_hList, &item);
			int ret = insertKeymap(ht.iItem, (Keymap*)item.lParam);
			if (ht.iItem < idx)
				ht.iItem++;
			if (ret <= idx)
				idx++;
			ListView_DeleteItem(m_hList, idx);
		}
		save();
	}
	m_flag_drag = false;
}

void KeymapDlg::setInsertMark(int idx)
{
	if (m_insrtpos != idx)
	{
		LVINSERTMARK mark = { 0 };
		mark.cbSize = sizeof(LVINSERTMARK);
		mark.dwFlags = 0;
		mark.iItem = idx;
		SendMessage(m_hList, LVM_SETINSERTMARK, 0, (LPARAM)&mark);
		m_insrtpos = idx;
	}
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
