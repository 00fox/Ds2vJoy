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

	m_TabsID[0] = ID_MENU_ADD;
	m_TabsID[1] = ID_MENU_EDIT;
	m_TabsID[2] = ID_MENU_DEL;
	m_TabsID[3] = ID_MENU_COPY;
	m_TabsID[4] = ID_MENU_SEPARATOR;
	m_hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_EDITING));
	DeleteMenu(m_hMenu, ID_MENU_MOVE_TO_0, FALSE);
	DeleteMenu(m_hMenu, ID_MENU_MOVE_TO_1, FALSE);
	DeleteMenu(m_hMenu, ID_MENU_MOVE_TO_2, FALSE);
	DeleteMenu(m_hMenu, ID_MENU_MOVE_TO_3, FALSE);
	DeleteMenu(m_hMenu, ID_MENU_MOVE_TO_4, FALSE);
	DeleteMenu(m_hMenu, ID_MENU_MOVE_TO_5, FALSE);
	DeleteMenu(m_hMenu, ID_MENU_MOVE_TO_6, FALSE);
	DeleteMenu(m_hMenu, ID_MENU_MOVE_TO_7, FALSE);
	DeleteMenu(m_hMenu, ID_MENU_MOVE_TO_8, FALSE);
	redrawMenu(5);

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_NOCOLUMNHEADER;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH;
	col.cx = 114;
	col.pszText = I18N.vJoyButton;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = I18N.Setting;
	col.cx = 201;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = L"";
	col.cx = 93;
	ListView_InsertColumn(m_hList, 2, &col);
	col.pszText = I18N.TagsButton;
	col.cx = 41;
	ListView_InsertColumn(m_hList, 3, &col);

	HWND hTip = ListView_GetToolTips(m_hList);
	SetWindowPos(hTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void KeymapDlg::redrawMenu(int ntabs)
{
	MENUITEMINFO info;
	for (int i = 0; i < ntabs; i++)
	{
		ZeroMemory(&info, sizeof(info));
		info.cbSize = sizeof(info);
		info.fMask = MIIM_FTYPE | MIIM_STATE;
		GetMenuItemInfo(m_hMenu, m_TabsID[i], FALSE, &info);
		info.fType = MFT_OWNERDRAW;
		info.fState = 0;
		SetMenuItemInfo(m_hMenu, m_TabsID[i], FALSE, &info);
	}
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
	case WM_MEASUREITEM:
	{
		LPMEASUREITEMSTRUCT DrawMenuSize = (LPMEASUREITEMSTRUCT)lParam;
		if (DrawMenuSize->CtlType == ODT_MENU)
		{
			int nEdgeWidth = ::GetSystemMetrics(SM_CYEDGE);
			DrawMenuSize->itemWidth = ::GetSystemMetrics(SM_CXMENUCHECK) + nEdgeWidth + nEdgeWidth;
			DrawMenuSize->itemHeight = 12 + nEdgeWidth + nEdgeWidth;

			WCHAR wszBuffer[MAX_PATH];
			int nCharCount = ::GetMenuString(m_hMenu, DrawMenuSize->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
			if (nCharCount > 0)
			{
				int nAcceleratorDelimiter;
				for (nAcceleratorDelimiter = 0;
					nAcceleratorDelimiter < nCharCount; nAcceleratorDelimiter++)
					if (wszBuffer[nAcceleratorDelimiter] == L'\t' || wszBuffer[nAcceleratorDelimiter] == L'\b')
						break;

				RECT rTextMetric = { 0, 0, 0, 0 };
				HDC hDC = ::GetDC(m_hDlg);

				if (hDC != NULL)
				{
					NONCLIENTMETRICSW nm;
					nm.cbSize = sizeof(NONCLIENTMETRICS);
					::SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, nm.cbSize, &nm, 0);
					HFONT font = ::CreateFontIndirect(&(nm.lfMenuFont));

					HFONT hOldFont = NULL;
					if (font != NULL)
						hOldFont = (HFONT)::SelectObject(hDC, font);

					::DrawTextW(hDC, wszBuffer, nAcceleratorDelimiter, &rTextMetric, DT_CALCRECT);
					long _CaptionWidth = rTextMetric.right - rTextMetric.left;

					long _AcceleratorWidth = 0;
					if (nAcceleratorDelimiter < nCharCount - 1)
					{
						::DrawTextW(hDC, &(wszBuffer[nAcceleratorDelimiter + 1]), nCharCount - nAcceleratorDelimiter - 1, &rTextMetric, DT_CALCRECT);
						_AcceleratorWidth = rTextMetric.right - rTextMetric.left;
					}
					if (hOldFont == NULL)
						::SelectObject(hDC, hOldFont);

					::ReleaseDC(m_hDlg, hDC);

					DrawMenuSize->itemWidth = _CaptionWidth + _AcceleratorWidth + (_AcceleratorWidth > 0 ? 1 : 0) + 12;
				}
			}
		}
		break;
	}
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* DrawMenuStructure = (DRAWITEMSTRUCT*)lParam;
		if (DrawMenuStructure->CtlType == ODT_MENU)
		{
			BOOL bSelected = DrawMenuStructure->itemState & ODS_SELECTED;

			// Background
			HBRUSH hBrushColor = ::CreateSolidBrush(RGB(205, 205, 210));
			::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), hBrushColor);

			// Highlight
			if (DrawMenuStructure->itemState & ODS_SELECTED)
			{
				hBrushColor = ::CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), hBrushColor);
			}

			// Caption
			WCHAR wszBuffer[MAX_PATH];
			int   nCharCount = ::GetMenuString((HMENU)DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
			if (nCharCount > 0)
			{
				COLORREF crPrevText = 0;
				COLORREF crCurrText = 0;
				crCurrText = ::GetSysColor((bSelected) ? COLOR_HIGHLIGHTTEXT : RGB(176, 144, 180));
				crPrevText = ::SetTextColor(DrawMenuStructure->hDC, crCurrText);

				int nAcceleratorDelimiter;
				for (nAcceleratorDelimiter = 0;
					nAcceleratorDelimiter < nCharCount; nAcceleratorDelimiter++)
					if (wszBuffer[nAcceleratorDelimiter] == L'\t' ||
						wszBuffer[nAcceleratorDelimiter] == L'\b')
						break;

				NONCLIENTMETRICSW nm;
				nm.cbSize = sizeof(NONCLIENTMETRICS);
				::SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, nm.cbSize, &nm, 0);
				HFONT _hMenuFontNormal = ::CreateFontIndirect(&(nm.lfMenuFont));
				HFONT hOldFont = (HFONT)::SelectObject(DrawMenuStructure->hDC, _hMenuFontNormal);

				int nOldBkMode = ::SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
				int nEdgeWidth = ::GetSystemMetrics(SM_CYEDGE);
				int nImageOffsetX = nEdgeWidth + nEdgeWidth + 12;
				DrawMenuStructure->rcItem.left += nImageOffsetX;
				DrawMenuStructure->rcItem.top += 0;
				::DrawTextW(DrawMenuStructure->hDC, wszBuffer, nAcceleratorDelimiter, &(DrawMenuStructure->rcItem), 0);

				if (nAcceleratorDelimiter < nCharCount - 1)
				{
					DrawMenuStructure->rcItem.left += 21;
					if (wszBuffer[nAcceleratorDelimiter] == L'\t')
						::DrawTextW(DrawMenuStructure->hDC, &(wszBuffer[nAcceleratorDelimiter + 1]),
							nCharCount - nAcceleratorDelimiter - 1, &(DrawMenuStructure->rcItem),
							DT_LEFT | DT_SINGLELINE);
					else
						::DrawTextW(DrawMenuStructure->hDC, &(wszBuffer[nAcceleratorDelimiter + 1]),
							nCharCount - nAcceleratorDelimiter - 1, &(DrawMenuStructure->rcItem),
							DT_RIGHT | DT_SINGLELINE);
					DrawMenuStructure->rcItem.left -= +21;
				}
				DrawMenuStructure->rcItem.left -= nImageOffsetX;
				DrawMenuStructure->rcItem.top -= 0;

				::SetBkMode(DrawMenuStructure->hDC, nOldBkMode);
				::SetTextColor(DrawMenuStructure->hDC, crPrevText);

				if (hOldFont == NULL)
					::SelectObject(DrawMenuStructure->hDC, hOldFont);
			}
		}
		break;
	}
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
		switch (((LPNMHDR)lParam)->code)
		{
		case HDN_BEGINTRACK:
			SetWindowLong(m_hDlg, 0, TRUE);  // prevent resizing
			return TRUE;
		}
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
				TrackPopupMenu((HMENU)GetSubMenu(m_hMenu, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y - 25, 0, m_hDlg, NULL);
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
								if (km->Enable != 2)
								{
									km->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
									save();
								}
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
		case ID_MENU_ADD:addKeymapDlg(); break;
		case ID_MENU_EDIT:editKeymapDlg(); break;
		case ID_MENU_DEL:deleteKeymapDlg(); break;
		case ID_MENU_COPY:duplicateKeymapDlg(); break;
		case ID_MENU_SEPARATOR:addSeparator(); break;
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
	kDDlg.Hide();

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
	tape.Save(tape.Setting_Keymapdata);
	PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
	load();
	RedrawWindow(m_hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW);

	m_active = true;
}

void KeymapDlg::addKeymapDlg()
{
	m_active = false;
	kDDlg.Hide();

	if (ListView_GetSelectedCount(m_hList) == 1)
		lastidx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
	else
		lastidx = ListView_GetItemCount(m_hList);

	Keymap km;
	kDDlg.keymapData = km;
	kDDlg.alreadydone = false;
	kDDlg.Open(m_hDlg, 1);

	m_active = true;
}

void KeymapDlg::addKeymapDlgBack()
{
	m_active = false;

	Keymap* data = new Keymap(kDDlg.keymapData);
	insertKeymap(lastidx, data);
	save();

	m_active = true;
}

void KeymapDlg::addSeparator()
{
	m_active = false;
	kDDlg.Hide();

	int idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
	if (idx == -1)
		idx = ListView_GetItemCount(m_hList);

	Keymap km;
	kDDlg.keymapData = km;
	Keymap* data = new Keymap(kDDlg.keymapData);
	data->ButtonID = vJoyButtonID::none;
	data->Enable = 2;

	insertKeymap(idx, data);
	save();

	m_active = true;
}

void KeymapDlg::editKeymapDlg()
{
	m_active = false;
	kDDlg.Hide();

	int nselected = ListView_GetSelectedCount(m_hList);
	if (nselected == 1)
	{
		lastidx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);

		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		item.iItem = lastidx;
		item.iSubItem = 0;
		ListView_GetItem(m_hList, &item);
		if (item.lParam != NULL)
		{
			Keymap* data = (Keymap*)item.lParam;
			if (data->Enable != 2)
			{
				kDDlg.keymapData = *data;
				kDDlg.alreadydone = false;
				kDDlg.Open(m_hDlg, 2);
			}
		}
	}
	else if (nselected >= 1)
	{
		lastidxs.clear();
		for (int i = 0; i < KeymapDataDlg::Mofified_count; i++)
			kDDlg.Modified[i] = false;
		int idx;
		while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1)
		{
			ListView_SetItemState(m_hList, idx, LVIF_STATE, LVIS_SELECTED);
			LV_ITEM item = { 0 };
			item.mask = LVIF_PARAM;
			item.iItem = idx;
			item.iSubItem = 0;
			ListView_GetItem(m_hList, &item);
			if (item.lParam != NULL)
			{
				Keymap* data = (Keymap*)item.lParam;
				if (data->Enable != 2)
					lastidxs.push_back(idx);
			}
		}

		for (int i = 0; i < lastidxs.size(); i++)
			ListView_SetItemState(m_hList, lastidxs[i], LVIS_SELECTED, LVIS_SELECTED);

		Keymap m;
		kDDlg.keymapData = m;
		kDDlg.alreadydone = false;
		kDDlg.Open(m_hDlg, 3);
	}

	m_active = true;
}

void KeymapDlg::editKeymapDlgBack()
{
	m_active = false;

	LV_ITEM item = { 0 };
	item.mask = LVIF_PARAM;
	item.iItem = lastidx;
	item.iSubItem = 0;
	ListView_GetItem(m_hList, &item);
	if (item.lParam != NULL)
	{
		Keymap* data = (Keymap*)item.lParam;
		*data = kDDlg.keymapData;
		ListView_DeleteItem(m_hList, lastidx);
		insertKeymap(lastidx, data);
		save();
	}

	m_active = true;
}

void KeymapDlg::editKeymapDlgBackMulti()
{
	m_active = false;

	Keymap* data1 = new Keymap(kDDlg.keymapData);

	for (int i = 0; i < lastidxs.size(); i++)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		item.iItem = lastidxs[i];
		item.iSubItem = 0;
		ListView_GetItem(m_hList, &item);
		if (item.lParam != NULL)
		{
			Keymap km;
			Keymap* data2 = (Keymap*)item.lParam;
			km = *data2;
			data2 = new Keymap(km);
			for (int i = 0; i < KeymapDataDlg::Mofified_count; i++)
				if (kDDlg.Modified[i])
					switch (i)
					{
					default:
					case KeymapDataDlg::Mofified_ButtonID:data2->ButtonID = data1->ButtonID; break;
					case KeymapDataDlg::Mofified_vk:data2->vk = data1->vk; break;
					case KeymapDataDlg::Mofified_usePostmessage:data2->usePostmessage = data1->usePostmessage; break;
					case KeymapDataDlg::Mofified_useActivating:data2->useActivating = data1->useActivating; break;
					case KeymapDataDlg::Mofified_findWindow:data2->findWindow = data1->findWindow; break;
					}
			ListView_DeleteItem(m_hList, lastidxs[i]);
			insertKeymap(lastidxs[i], data2);
		}
	}
	save();

	m_active = true;
}

void KeymapDlg::deleteKeymapDlg()
{
	m_active = false;
	kDDlg.Hide();

	if (ListView_GetSelectedCount(m_hList) == 0)
		{ m_active = true; return; }

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

void KeymapDlg::duplicateKeymapDlg()
{
	m_active = false;
	kDDlg.Hide();

	int nselected = ListView_GetSelectedCount(m_hList);
	if (nselected == 1)
	{
		int idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);

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
	}
	else if (nselected >= 1)
	{
		int idx;
		int lastitemindex = ListView_GetItemCount(m_hList);
		while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1)
		{
			LV_ITEM item = { 0 };
			item.mask = LVIF_PARAM;
			item.iItem = idx;
			item.iSubItem = 0;
			ListView_GetItem(m_hList, &item);
			if (item.lParam != NULL)
			{
				Keymap* data1 = (Keymap*)item.lParam;
				Keymap* data2 = (Keymap*)item.lParam;
				kDDlg.keymapData = *data1;
				data1 = new Keymap(kDDlg.keymapData);
				kDDlg.keymapData = *data2;
				data2 = new Keymap(kDDlg.keymapData);
				ListView_DeleteItem(m_hList, idx);
				insertKeymap(idx, data1);
				insertKeymap(lastitemindex + 1, data2);
				lastitemindex++;
			}
		}
		save();
	}

	m_active = true;
}

int KeymapDlg::insertKeymap(int idx, Keymap* km)
{
	m_active = false;

	if (idx < 0)
		{ m_active = false; return FALSE; }

	LVITEM item = { 0 };
	bool enable = km->Enable == 1;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	item.lParam = (LPARAM)km;
	item.pszText = (WCHAR*)km->KeyString();
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = (WCHAR*)km->ValueString(1);
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 2;
	item.lParam = 0;
	item.pszText = (WCHAR*)km->ValueString(2);
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 3;
	item.lParam = 0;
	item.pszText = (WCHAR*)km->ValueString(3);
	ListView_SetItem(m_hList, &item);
	ListView_SetCheckState(m_hList, idx, enable);

	m_active = true;
	return ret;
}

void KeymapDlg::BeginDrag(int idx)
{
	if (ListView_GetNextItem(m_hList, -1, LVNI_SELECTED) == -1)
		return;
	kDDlg.Hide();
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
		setInsertMark(ht.iItem);
	else
		setInsertMark(-1);
}

void KeymapDlg::EndDrag(int x, int y)
{
	setInsertMark(-1);
	ReleaseCapture();

	LV_HITTESTINFO ht;
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
