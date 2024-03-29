﻿#include "stdafx.h"
#include "RapidFireDlg.h"
#include "RapidFireDataDlg.h"

RapidFireDlg::RapidFireDlg()
{
	m_TabsID[0] = IDM_MENU_ADD;
	m_TabsID[1] = IDM_MENU_EDIT;
	m_TabsID[2] = IDM_MENU_DEL;
	m_TabsID[3] = IDM_MENU_COPY;
	m_TabsID[4] = IDM_MENU_SEPARATOR;
}

RapidFireDlg::~RapidFireDlg()
{
	RemoveWindowSubclass(m_hList, (SUBCLASSPROC)ListSubclassProc, 1);
}

void RapidFireDlg::Init()
{
	m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_RAPIDFIRE), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));
	Hide();
	m_hList = GetDlgItem(m_hDlg, IDC_RAPIDFIRE_LIST);
	m_hMenu = LoadMenu(tape.Ds2hInst, MAKEINTRESOURCE(IDR_MENU_EDITING));
	redrawMenu(5);

	SendMessage(m_hList, WM_SETFONT, WPARAM(tape.hList), MAKELPARAM(TRUE, 0));

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);

	HWND header = ListView_GetHeader(m_hList);
	DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
	dwHeaderStyle = dwHeaderStyle & ~HDS_DRAGDROP | HDS_NOSIZING;
	::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

	LVCOLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH;
	col.cx = 115 + (GetSystemMetrics(SM_CXVSCROLL) + 2);
	col.pszText = I18N.srceButton;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = I18N.Setting;
	col.cx = 112;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = WCHARI(L"");
	col.cx = 112;
	ListView_InsertColumn(m_hList, 2, &col);
	col.pszText = WCHARI(L"");
	col.cx = 112;
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
	
	SetWindowSubclass(m_hList, (SUBCLASSPROC)ListSubclassProc, 1, (DWORD_PTR)this);
}

void RapidFireDlg::PageUp()
{
	ListView_Scroll(m_hList, 0, -14);
}

void RapidFireDlg::PageDown()
{
	ListView_Scroll(m_hList, 0, 14);
}

void RapidFireDlg::PageHome()
{
	ListView_Scroll(m_hList, 0, -32765);
}

void RapidFireDlg::PageEnd()
{
	ListView_Scroll(m_hList, 0, 32765);
}

void RapidFireDlg::redrawMenu(int ntabs)
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

void RapidFireDlg::_InitDialog(HWND hWnd)
{

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void RapidFireDlg::_ShowWindow(HWND hWnd)
{
	if (tape.DarkTheme)
	{
		ListView_SetBkColor(m_hList, tape.ink_LIST_BACK_DARK);
		ListView_SetTextColor(m_hList, tape.ink_LIST_DARK);
		ListView_SetTextBkColor(m_hList, tape.ink_LIST_BACKGROUND_DARK);
	}
	else
	{
		ListView_SetBkColor(m_hList, tape.ink_LIST_BACK);
		ListView_SetTextColor(m_hList, tape.ink_LIST);
		ListView_SetTextBkColor(m_hList, tape.ink_LIST_BACKGROUND);
	}
	load();
	m_active = true;
}

INT_PTR CALLBACK RapidFireDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RapidFireDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<RapidFireDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<RapidFireDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR RapidFireDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CTLCOLORSCROLLBAR:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_SCROLLBAR);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_SCROLLBAR);
		return (LRESULT)tape.hB_SCROLLBAR;
	}
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		if (tape.DarkTheme)
		{
			SetTextColor(hdcStatic, tape.ink_COMBO_DARK);
			return (LRESULT)tape.hB_LIST_DARK;
		}
		else
		{
			SetTextColor(hdcStatic, tape.ink_COMBO);
			return (LRESULT)tape.hB_LIST;
		}
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

			SelectObject(DrawMenuStructure->hDC, tape.hMenu);
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
			std::thread(&RapidFireDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&RapidFireDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_LBUTTONUP:
	{
		if (m_flag_drag && GetCapture() == hWnd)
		{
			EndDrag(LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hWnd, NULL, TRUE);
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
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_RAPIDFIRE_LIST:
		{
			switch (((LPNMHDR)lParam)->code)
			{
			case NM_DBLCLK:
			{
				editRapidFireDlg();
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
					unsigned int newstate = (((LPNMLISTVIEW)lParam)->uNewState & LVIS_STATEIMAGEMASK);
					if (newstate != (((LPNMLISTVIEW)lParam)->uOldState & LVIS_STATEIMAGEMASK))
					{
						RapidFire* rf = (RapidFire*)((LPNMLISTVIEW)lParam)->lParam;
						if (rf != 0)
							if (rf->Enable != 2)
							{
								rf->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
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
		case IDM_MENU_ADD: { addRapidFireDlg(); break; }
		case IDM_MENU_EDIT: { editRapidFireDlg(); break; }
		case IDM_MENU_DEL: { deleteRapidFireDlg(); break; }
		case IDM_MENU_COPY: { duplicateRapidFireDlg(); break; }
		case IDM_MENU_SEPARATOR: { addSeparator(); break; }
		}
		break;
	}
	default:
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK RapidFireDlg::ListSubclassProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIDSubClass, DWORD_PTR RefData)
{
	RapidFireDlg* dlg = reinterpret_cast<RapidFireDlg*>(RefData);
	if (dlg)
		return dlg->_listSubclassProc(hWnd, message, wParam, lParam);

	return DefSubclassProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK RapidFireDlg::_listSubclassProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_sorting)
		return 0;

	switch (message)
	{
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case HDN_ENDDRAG:
		{
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case NM_CUSTOMDRAW:
		{
			LPNMCUSTOMDRAW DrawListCustom = (LPNMCUSTOMDRAW)lParam;
			switch (DrawListCustom->dwDrawStage)
			{
			case CDDS_PREPAINT:
			{
				ListView_GetColumnOrderArray(m_hList, 4, &m_columnOrder);
				m_indexOfSettings = (m_columnOrder[0] == 0) ? m_columnOrder[1] : m_columnOrder[0];
				return CDRF_NOTIFYITEMDRAW | CDRF_NOTIFYPOSTPAINT;
			}
			case CDDS_ITEMPREPAINT:
			{
				if (DrawListCustom->uItemState == CDIS_SELECTED)
					m_actualColumn = DrawListCustom->dwItemSpec;

				if (tape.DarkTheme)
				{
					FillRect(DrawListCustom->hdc, &DrawListCustom->rc, (m_actualColumn == DrawListCustom->dwItemSpec) ? tape.hB_LIST_Header_DARK : tape.hB_LIST_Header2_DARK);
					SetBkColor(DrawListCustom->hdc, (m_actualColumn == DrawListCustom->dwItemSpec) ? tape.Bk_LIST_header1_DARK : tape.Bk_LIST_header2_DARK);
					if (DrawListCustom->dwItemSpec == 0)
					{
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header1_DARK);
						DrawText(DrawListCustom->hdc, I18N.srceButton, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
					else
					{
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header2_DARK);
						if (DrawListCustom->dwItemSpec == m_indexOfSettings)
							DrawText(DrawListCustom->hdc, I18N.Setting, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
				else
				{
					FillRect(DrawListCustom->hdc, &DrawListCustom->rc, (m_actualColumn == DrawListCustom->dwItemSpec) ? tape.hB_LIST_Header : tape.hB_LIST_Header2);
					SetBkColor(DrawListCustom->hdc, (m_actualColumn == DrawListCustom->dwItemSpec) ? tape.ink_LIST_Header : tape.ink_LIST_scndHeader);
					if (DrawListCustom->dwItemSpec == 0)
					{
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header1);
						DrawText(DrawListCustom->hdc, I18N.srceButton, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
					else
					{
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header2);
						if (DrawListCustom->dwItemSpec == m_indexOfSettings)
							DrawText(DrawListCustom->hdc, I18N.Setting, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
				return CDRF_SKIPDEFAULT;
			}
			case CDDS_POSTPAINT:
			{
				if (m_actualColumn != m_lastColumn)
					Sort(m_actualColumn);
				break;
			}
			default:
				return CDRF_DODEFAULT;
				break;
			}
			break;
		}
		}
		break;
	}
	default:
		return DefSubclassProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void RapidFireDlg::load()
{
	m_active = false;

	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1)
	{
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

	size_t length = tape.RapidFiredata.size();
	for (int i = 0; i < length; i++)
	{
		RapidFire* rf = new RapidFire(tape.RapidFiredata[i]);
		insertRapidFire(i, rf);
	}

	m_active = true;
}

void RapidFireDlg::save()
{
	m_active = false;
	rDDlg.Hide();

	RapidFires newmap;
	int lastitemindex = ListView_GetItemCount(m_hList);
	for (int i = 0; i < lastitemindex; i++)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		item.iItem = i;
		if (!ListView_GetItem(m_hList, &item))
		{
			SendMessage(tape.Ds2hWnd, WM_ADDRAPIDFIRE, 0, -1);
			RECT win;
			GetWindowRect(tape.Ds2hWnd, &win);
			MessageBoxPos(tape.Ds2hWnd, I18N.MBOX_ErrorWhileSaving, I18N.MBOX_ErrTitle, MB_ICONERROR, win.left + 275, win.top + 30);
			return;
		}
		if (item.lParam != NULL)
			newmap.push_back(*(RapidFire*)item.lParam);
	}

	tape.RapidFiredata.swap(newmap);
	tape.Save(tape.Setting_RapidFiredata);
	SendMessage(tape.Ds2hWnd, WM_ADDRAPIDFIRE, 0, -1);

	m_active = true;
}

void RapidFireDlg::addRapidFireDlg()
{
	m_active = false;
	rDDlg.Hide();

	if (ListView_GetSelectedCount(m_hList) == 1)
		lastidx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
	else
		lastidx = ListView_GetItemCount(m_hList);

	RapidFire rf;
	rDDlg.rapidFireData = rf;
	rDDlg.Open(m_hDlg, 1);

	m_active = true;
}

void RapidFireDlg::addRapidFireDlgBack()
{
	m_active = false;

	RapidFire* data = new RapidFire(rDDlg.rapidFireData);
	insertRapidFire(lastidx, data);
	save();

	m_active = true;
}

void RapidFireDlg::addSeparator()
{
	m_active = false;
	rDDlg.Hide();

	int idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
	if (idx == -1)
		idx = ListView_GetItemCount(m_hList);

	RapidFire rf;
	rDDlg.rapidFireData = rf;
	RapidFire* data = new RapidFire(rDDlg.rapidFireData);
	data->Enable = 2;

	insertRapidFire(idx, data);
	save();

	m_active = true;
}

void RapidFireDlg::editRapidFireDlg()
{
	m_active = false;
	rDDlg.Hide();

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
			RapidFire* data = (RapidFire*)item.lParam;
			if (data->Enable != 2)
			{
				rDDlg.rapidFireData = *data;
				rDDlg.Open(m_hDlg, 2);
			}
		}
	}
	else if (nselected > 1)
	{
		lastidxs.clear();
		for (int i = 0; i < RapidFireDataDlg::ModifiedRapidFire_Count; i++)
			rDDlg.Modified[i] = false;
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
				RapidFire* data = (RapidFire*)item.lParam;
				if (data->Enable != 2)
					lastidxs.push_back(idx);
			}
		}

		for (int i = 0; i < lastidxs.size(); i++)
			ListView_SetItemState(m_hList, lastidxs[i], LVIS_SELECTED, LVIS_SELECTED);

		RapidFire rf;
		rDDlg.rapidFireData = rf;
		rDDlg.Open(m_hDlg, 3);
	}

	m_active = true;
}

void RapidFireDlg::editRapidFireDlgBack()
{
	m_active = false;

	LV_ITEM item = { 0 };
	item.mask = LVIF_PARAM;
	item.iItem = lastidx;
	item.iSubItem = 0;
	ListView_GetItem(m_hList, &item);
	if (item.lParam != NULL)
	{
		RapidFire* data = (RapidFire*)item.lParam;
		*data = rDDlg.rapidFireData;
		ListView_DeleteItem(m_hList, lastidx);
		insertRapidFire(lastidx, data);
		save();
	}

	m_active = true;
}

void RapidFireDlg::editRapidFireDlgBackMulti()
{
	m_active = false;

	RapidFire* data1 = new RapidFire(rDDlg.rapidFireData);

	for (int i = 0; i < lastidxs.size(); i++)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		item.iItem = lastidxs[i];
		item.iSubItem = 0;
		ListView_GetItem(m_hList, &item);
		if (item.lParam != NULL)
		{
			RapidFire rf;
			RapidFire* data2 = (RapidFire*)item.lParam;
			rf = *data2;
			data2 = new RapidFire(rf);
			for (int i = 0; i < RapidFireDataDlg::ModifiedRapidFire_Count; i++)
				if (rDDlg.Modified[i])
					switch (i)
					{
					default:
					case RapidFireDataDlg::ModifiedRapidFire_ButtonID:data2->ButtonID = data1->ButtonID; break;
					case RapidFireDataDlg::ModifiedRapidFire_ButtonID2:data2->ButtonID2 = data1->ButtonID2; break;
					case RapidFireDataDlg::ModifiedRapidFire_Firsttime:data2->Firsttime = data1->Firsttime; break;
					case RapidFireDataDlg::ModifiedRapidFire_Releasetime:data2->Releasetime = data1->Releasetime; break;
					case RapidFireDataDlg::ModifiedRapidFire_Presstime:data2->Presstime = data1->Presstime; break;
					}
			ListView_DeleteItem(m_hList, lastidxs[i]);
			insertRapidFire(lastidxs[i], data2);
		}
	}
	save();

	m_active = true;
}

void RapidFireDlg::deleteRapidFireDlg()
{
	m_active = false;
	rDDlg.Hide();

	if (ListView_GetSelectedCount(m_hList) == 0)
		{ m_active = true; return; }

	RECT win;
	GetWindowRect(tape.Ds2hWnd, &win);
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
			delete (RapidFire*)item.lParam;
			ListView_DeleteItem(m_hList, idx);
		}
		save();
	}

	m_active = true;
}

void RapidFireDlg::duplicateRapidFireDlg()
{
	m_active = false;
	rDDlg.Hide();

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
			RapidFire* data = (RapidFire*)item.lParam;
			rDDlg.rapidFireData = *data;
			data = new RapidFire(rDDlg.rapidFireData);
			insertRapidFire(idx + 1, data);
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
				RapidFire* data1 = (RapidFire*)item.lParam;
				RapidFire* data2 = (RapidFire*)item.lParam;
				rDDlg.rapidFireData = *data1;
				data1 = new RapidFire(rDDlg.rapidFireData);
				rDDlg.rapidFireData = *data2;
				data2 = new RapidFire(rDDlg.rapidFireData);
				ListView_DeleteItem(m_hList, idx);
				insertRapidFire(idx, data1);
				insertRapidFire(lastitemindex + 1, data2);
				lastitemindex++;
			}
		}
		save();
	}

	m_active = true;
}

int RapidFireDlg::insertRapidFire(int idx, RapidFire* rf)
{
	m_active = false;

	if (idx < 0)
		{ m_active = false; return FALSE; }

	LVITEM item = { 0 };
	bool enable = rf->Enable == 1;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	item.lParam = LPARAM(rf);
	item.pszText = (WCHAR*)(rf->KeyString());
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = (WCHAR*)(rf->ValueString(1));
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 2;
	item.lParam = 0;
	item.pszText = (WCHAR*)(rf->ValueString(2));
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 3;
	item.lParam = 0;
	item.pszText = (WCHAR*)(rf->ValueString(3));
	ListView_SetItem(m_hList, &item);
	ListView_SetCheckState(m_hList, idx, enable);

	m_active = true;
	return ret;
}

void RapidFireDlg::BeginDrag(int idx)
{
	if (ListView_GetNextItem(m_hList, -1, LVNI_SELECTED) == -1)
		return;
	rDDlg.Hide();
	m_flag_drag = true;
	SetCapture(m_hDlg);
}

void RapidFireDlg::DragMove(int x, int y)
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

void RapidFireDlg::EndDrag(int x, int y)
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
			int ret = insertRapidFire(ht.iItem, (RapidFire*)item.lParam);
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

void RapidFireDlg::setInsertMark(int idx)
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

void RapidFireDlg::Sort(int column)
{
	m_sorting = true;
	m_active = false;
	rDDlg.Hide();

	RapidFires newmap;
	RapidFires newmaptmp;
	size_t length = tape.RapidFiredata.size();
	for (size_t i = 0; i < length; i++)
		newmaptmp.push_back((RapidFire)tape.RapidFiredata[i]);

	length = newmaptmp.size();
	for (size_t i = 0; i < length; i++)
	{
		if (newmaptmp[i].Enable == 2)
		{
			newmap.push_back((RapidFire)newmaptmp[i]);
			newmaptmp.erase(newmaptmp.begin() + i);
		}
	}

	while (newmaptmp.size())
	{
		int pos = -1;

		long long value = 0;

		length = newmaptmp.size();
		for (size_t i = 0; i < length; i++)
		{
			int sortresult = 0;

			std::vector<byte> vjdata;
			if (newmaptmp[i].ButtonID)
				vjdata.push_back(newmaptmp[i].ButtonID);
			if (newmaptmp[i].ButtonID2)
				vjdata.push_back(newmaptmp[i].ButtonID2);
			std::sort(vjdata.begin(), vjdata.end());
			size_t length = 2 - vjdata.size();
			for (int j = 0; j < length; j++)
				vjdata.push_back(0);

			switch (column)
			{
			case 0:
			{
				sortresult |= ((long long)vjdata[1] << 0);
				sortresult |= ((long long)vjdata[0] << 8);
				break;
			}
			case 1:
			{
				sortresult |= ((long long)newmaptmp[i].Firsttime << 0);
				break;
			}
			case 2:
			{
				sortresult |= ((long long)newmaptmp[i].Releasetime << 0);
				break;
			}
			case 3:
			{
				sortresult |= ((long long)newmaptmp[i].Presstime << 0);
				break;
			}
			}

			if (pos == -1 || (pos >= 0 && (sortresult < value)))
			{
				pos = (int)i;
				value = sortresult;
			}
		}
		newmap.push_back((RapidFire)newmaptmp[pos]);
		newmaptmp.erase(newmaptmp.begin() + pos);
	}

	tape.RapidFiredata.swap(newmap);

	tape.Save(tape.Setting_RapidFiredata);

	PostMessage(tape.Ds2hWnd, WM_ADDRAPIDFIRE, 0, -1);

	m_lastColumn = m_actualColumn;
	m_active = true;
	m_sorting = false;
}

void RapidFireDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void RapidFireDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL RapidFireDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	BOOL ret = ::MoveWindow(m_hDlg, x, y, w, h, r);
	RECT win;
	GetWindowRect(m_hDlg, &win);
	::MoveWindow(m_hList, 0, 0, win.right - win.left + (GetSystemMetrics(SM_CXVSCROLL) + 2), win.bottom - win.top, FALSE);

	return ret;
}
