#include "stdafx.h"
#include "KeymapDlg.h"
#include "KeymapDataDlg.h"
#include "Findwindow.h"

KeymapDlg::KeymapDlg()
{
	m_TabsID[0] = IDM_MENU_ADD;
	m_TabsID[1] = IDM_MENU_EDIT;
	m_TabsID[2] = IDM_MENU_DEL;
	m_TabsID[3] = IDM_MENU_COPY;
	m_TabsID[4] = IDM_MENU_SEPARATOR;
}

KeymapDlg::~KeymapDlg()
{
}

void KeymapDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_KEYMAP), hWnd, (DLGPROC)Proc, LPARAM(this));
	m_hList = GetDlgItem(m_hDlg, IDC_KEYMAP_LIST);
	m_hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_EDITING));
	redrawMenu(5);

	SendMessage(m_hList, WM_SETFONT, WPARAM(tape.hList), MAKELPARAM(TRUE, 0));

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_NOCOLUMNHEADER;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);

	HWND header = ListView_GetHeader(m_hList);
	DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
	dwHeaderStyle |= HDS_NOSIZING;
	::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

	LVCOLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH;
	col.cx = 76;
	col.pszText = I18N.vJoyButton;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = I18N.Setting;
	col.cx = 213;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = I18N.Process;
	col.cx = 90;
	ListView_InsertColumn(m_hList, 2, &col);
	col.pszText = I18N.TagsButton;
	col.cx = 70;
	ListView_InsertColumn(m_hList, 3, &col);

	HWND hTip = ListView_GetToolTips(m_hList);
	SetWindowPos(hTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	SetWindowTheme(hTip, L"", L"");
	SendMessage(hTip, TTM_SETMAXTIPWIDTH, 0, 8192);
	SendMessage(hTip, TTM_SETDELAYTIME, TTDT_AUTOPOP, MAKELPARAM((32767), (0)));
	SendMessage(hTip, TTM_SETTIPBKCOLOR, tape.Bk_TOOLTIP, 0);
	SendMessage(hTip, TTM_SETTIPTEXTCOLOR, tape.ink_TOOLTIP, 0);
	RECT TipRect = { 5, 1, 2, 2 };
	SendMessage(hTip, TTM_SETMARGIN, 0, LPARAM(&TipRect));
	SendMessage(hTip, WM_SETFONT, WPARAM(tape.hTooltip), MAKELPARAM(TRUE, 0));
}

void KeymapDlg::redrawMenu(int ntabs)
{
	MENUITEMINFO info;
	for (int i = 0; i < ntabs; i++)
	{
		ZeroMemory(&info, sizeof(info));
		info.cbSize = sizeof(info);
		info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING;
		GetMenuItemInfo(m_hMenu, m_TabsID[i], FALSE, &info);
		info.fType = MFT_OWNERDRAW;
		info.fState = MFS_UNCHECKED;
		switch (i)
		{
		case 0: info.dwTypeData = I18N.MENU_ADD; break;
		case 1: info.dwTypeData = I18N.MENU_EDIT; break;
		case 2: info.dwTypeData = I18N.MENU_DEL; break;
		case 3: info.dwTypeData = I18N.MENU_COPY; break;
		case 4: info.dwTypeData = I18N.MENU_SEPARATOR; break;
		}
		SetMenuItemInfo(m_hMenu, m_TabsID[i], FALSE, &info);
	}
}

void KeymapDlg::_InitDialog(HWND hWnd)
{

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void KeymapDlg::_ShowWindow(HWND hWnd)
{
	SendMessage(m_hList, LVM_SETBKCOLOR, 0, LPARAM(tape.ink_LIST_BACK));
	SendMessage(m_hList, LVM_SETTEXTCOLOR, 0, LPARAM(tape.ink_LIST));
	SendMessage(m_hList, LVM_SETTEXTBKCOLOR, 0, LPARAM(tape.ink_LIST_BACKGROUND));
	load();
	m_active = true;
}

INT_PTR CALLBACK KeymapDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	KeymapDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<KeymapDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<KeymapDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR KeymapDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_LIST);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LRESULT)tape.hB_LIST;
	}
	case WM_MEASUREITEM:
	{
		LPMEASUREITEMSTRUCT DrawMenuSize = (LPMEASUREITEMSTRUCT)lParam;
		if (DrawMenuSize->CtlType == ODT_MENU)
		{
			DrawMenuSize->itemHeight = 14;
			DrawMenuSize->itemWidth = 75;
		}
		break;
	}
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* DrawMenuStructure = (DRAWITEMSTRUCT*)lParam;
		if (DrawMenuStructure->CtlType == ODT_MENU)
		{
			BOOL selected = DrawMenuStructure->itemState & ODS_SELECTED;

			if (DrawMenuStructure->itemState & ODS_SELECTED)
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_HIGHLIGHT);
			else if (DrawMenuStructure->itemID == IDM_MENU_DEL)
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_red);
			else
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU);

			SelectObject(DrawMenuStructure->hDC, tape.hMenus);
			WCHAR wszBuffer[MAX_PATH];
			int nCharCount = ::GetMenuString((HMENU)DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
			if (nCharCount > 0)
			{
				COLORREF crCurrText = 0;
				crCurrText = (selected) ? ((DrawMenuStructure->itemID == IDM_MENU_DEL) ? tape.ink_MENU_Delete : tape.ink_MENU_HIGHLIGHT) : tape.ink_MENU;
				SetTextColor(DrawMenuStructure->hDC, crCurrText);

				int nCharacters;
				for (nCharacters = 0;
					nCharacters < nCharCount; nCharacters++)
					if (wszBuffer[nCharacters] == L'\t' ||
						wszBuffer[nCharacters] == L'\b')
						break;

				SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
				DrawMenuStructure->rcItem.left += 5;
				DrawTextW(DrawMenuStructure->hDC, wszBuffer, nCharacters, &(DrawMenuStructure->rcItem), DT_VCENTER | DT_SINGLELINE);
			}
		}
		break;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
			std::thread(&KeymapDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&KeymapDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_LBUTTONUP:
	{
		if (m_flag_drag && GetCapture() == hWnd)
		{
			EndDrag(LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (m_flag_drag && GetCapture() == hWnd)
			DragMove(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_SIZE:
	{
		::MoveWindow(m_hList, 0, 0, LOWORD(lParam), HIWORD(lParam), FALSE);
		break;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case HDN_BEGINTRACK:
		{
			SetWindowLong(m_hDlg, 0, TRUE);  // prevent resizing
			return TRUE;
		}
		}
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_KEYMAP_LIST:
		{
			switch (((LPNMHDR)lParam)->code)
			{
			case LVN_COLUMNCLICK:
			{
				m_active = false;
				kDDlg.Hide();

				LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
				unsigned char column = pnmv->iSubItem;
				if (lasttab == column)
					tabSortingMethod = !tabSortingMethod;
				else
					tabSortingMethod = false;
				lasttab = column;

				Keymaps newmap;
				Keymaps newmaptmp;
				size_t length = tape.Keymapdata.size();
				for (size_t i = 0; i < length; i++)
					newmaptmp.push_back((Keymap)tape.Keymapdata[i]);

				length = newmaptmp.size();
				for (size_t i = 0; i < length; i++)
				{
					if (newmaptmp[i].Enable == 2)
					{
						newmap.push_back((Keymap)newmaptmp[i]);
						newmaptmp.erase(newmaptmp.begin() + i);
					}
				}

				while (newmaptmp.size())
				{
					int pos = -1;

					unsigned long long value = 0;
					std::wstring valuestr = L"";

					length = newmaptmp.size();
					for (size_t i = 0; i < length; i++)
					{
						unsigned long long sortresult = 0;
						std::wstring sortstr = L"";

						switch (column)
						{
						case 0:
						{
							sortresult |= ((unsigned long long)newmaptmp[i].ButtonID << 0);
							break;
						}
						case 1:
						{
							if (newmaptmp[i].vk.size() > 7)
								sortresult |= ((unsigned long long)newmaptmp[i].vk[7] << 0);
							if (newmaptmp[i].vk.size() > 6)
								sortresult |= ((unsigned long long)newmaptmp[i].vk[6] << 8);
							if (newmaptmp[i].vk.size() > 5)
								sortresult |= ((unsigned long long)newmaptmp[i].vk[5] << 16);
							if (newmaptmp[i].vk.size() > 4)
								sortresult |= ((unsigned long long)newmaptmp[i].vk[4] << 24);
							if (newmaptmp[i].vk.size() > 3)
								sortresult |= ((unsigned long long)newmaptmp[i].vk[3] << 32);
							if (newmaptmp[i].vk.size() > 2)
								sortresult |= ((unsigned long long)newmaptmp[i].vk[2] << 40);
							if (newmaptmp[i].vk.size() > 1)
								sortresult |= ((unsigned long long)newmaptmp[i].vk[1] << 48);
							if (newmaptmp[i].vk.size() > 0)
								sortresult |= ((unsigned long long)newmaptmp[i].vk[0] << 56);
							break;
						}
						case 2:
						{
							sortstr = newmaptmp[i].findWindow.Val();
							break;
						}
						case 3:
						{
							sortresult |= ((unsigned long long)newmaptmp[i].useActivating << 0);
							sortresult |= ((unsigned long long)newmaptmp[i].usePostmessage << 1);
							break;
						}
						}

						if (column == 2)
						{
							if (pos == -1 || (pos >= 0 && ((tabSortingMethod) ? sortstr.compare(valuestr) > 0 : sortstr.compare(valuestr) < 0)))
							{
								pos = (int)i;
								valuestr = sortstr;
							}
						}
						else if (pos == -1 || (pos >= 0 && ((tabSortingMethod) ? sortresult > value : sortresult < value)))
						{
							pos = (int)i;
							value = sortresult;
						}
					}
					newmap.push_back((Keymap)newmaptmp[pos]);
					newmaptmp.erase(newmaptmp.begin() + pos);
				}

				tape.Keymapdata.swap(newmap);
				tape.Save(tape.Setting_Keymapdata);

				PostMessage(m_hWnd, WM_ADDKEYMAP, 0, -1);

				m_active = true;
				break;
			}
			case NM_DBLCLK:
			{
				editKeymapDlg();
				break;
			}
			case NM_RCLICK:
			{
				GetCursorPos(&tape.mousepoint);
				TrackPopupMenu((HMENU)GetSubMenu(m_hMenu, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, tape.mousepoint.x, tape.mousepoint.y - 25, 0, m_hDlg, NULL);
				break;
			}
			case LVN_BEGINDRAG:
			{
				BeginDrag(((LPNMLISTVIEW)lParam)->iItem);
				SetFocus(m_hList);
				break;
			}
			case LVN_ITEMCHANGED:
			{
				if (m_active && !m_flag_drag)
				{
					DWORD newstate = (((LPNMLISTVIEW)lParam)->uNewState & LVIS_STATEIMAGEMASK);
					if (newstate != (((LPNMLISTVIEW)lParam)->uOldState & LVIS_STATEIMAGEMASK))
					{
						Keymap* km = (Keymap*)((LPNMLISTVIEW)lParam)->lParam;
						if (km != 0)
							if (km->Enable != 2)
							{
								km->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
								save();
							}
					}
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
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_MENU_ADD: { addKeymapDlg(); break; }
		case IDM_MENU_EDIT: { editKeymapDlg(); break; }
		case IDM_MENU_DEL: { deleteKeymapDlg(); break; }
		case IDM_MENU_COPY: { duplicateKeymapDlg(); break; }
		case IDM_MENU_SEPARATOR: { addSeparator(); break; }
		}
		break;
	}
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
	int lastitemindex = ListView_GetItemCount(m_hList);
	for (int i = 0; i < lastitemindex; i++)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		item.iItem = i;
		if (!ListView_GetItem(m_hList, &item))
		{
			SendMessage(m_hWnd, WM_ADDKEYMAP, 0, -1);
			RECT win;
			GetWindowRect(m_hWnd, &win);
			MessageBoxPos(m_hWnd, I18N.MBOX_ErrorWhileSaving, I18N.MBOX_ErrTitle, MB_ICONERROR, win.left + 275, win.top + 30);
			return;
		}
		if (item.lParam != NULL)
			newmap.push_back(*(Keymap*)item.lParam);
	}

	tape.Keymapdata.swap(newmap);
	tape.Save(tape.Setting_Keymapdata);
	SendMessage(m_hWnd, WM_ADDKEYMAP, 0, -1);

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
	else if (nselected > 1)
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
					case KeymapDataDlg::Mofified_ButtonID: { data2->ButtonID = data1->ButtonID; break; }
					case KeymapDataDlg::Mofified_WndRestore: { data2->WndRestore = data1->WndRestore; break; }
					case KeymapDataDlg::Mofified_WndMaximize: { data2->WndMaximize = data1->WndMaximize; break; }
					case KeymapDataDlg::Mofified_WndShow: { data2->WndShow = data1->WndShow; break; }
					case KeymapDataDlg::Mofified_vk: { data2->vk = data1->vk; break; }
					case KeymapDataDlg::Mofified_NaturalTyping: { data2->NaturalTyping = data1->NaturalTyping; break; }
					case KeymapDataDlg::Mofified_usePostmessage: { data2->usePostmessage = data1->usePostmessage; break; }
					case KeymapDataDlg::Mofified_useActivating: { data2->useActivating = data1->useActivating; break; }
					case KeymapDataDlg::Mofified_ExtendedKey: { data2->ExtendedKey = data1->ExtendedKey; break; }
					case KeymapDataDlg::Mofified_Scancode: { data2->Scancode = data1->Scancode; break; }
					case KeymapDataDlg::Mofified_findWindow: { data2->findWindow = data1->findWindow; break; }
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

	RECT win;
	GetWindowRect(m_hWnd, &win);
	if (MessageBoxPos(m_hDlg, I18N.MBOX_Delete, I18N.APP_TITLE, MB_YESNO, win.left + 160, win.top + 60) == IDYES)
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
	else if (nselected > 1)
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
	item.lParam = LPARAM(km);
	item.pszText = (WCHAR*)(km->KeyString());
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = (WCHAR*)(km->ValueString(1));
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 2;
	item.lParam = 0;
	item.pszText = (WCHAR*)(km->ValueString(2));
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 3;
	item.lParam = 0;
	item.pszText = (WCHAR*)(km->ValueString(3));
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
		SendMessage(m_hList, LVM_SETINSERTMARK, 0, LPARAM(&mark));
		m_insrtpos = idx;
	}
}

void KeymapDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void KeymapDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL KeymapDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
