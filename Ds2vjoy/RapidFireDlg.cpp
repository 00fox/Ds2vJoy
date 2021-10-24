#include "stdafx.h"
#include "RapidFireDlg.h"
#include "RapidFireDataDlg.h"
#include "Ds2vJoy.h"

RapidFireDlg::RapidFireDlg()
	:m_hWnd()
	, m_hDlg()
	, m_hList()
	, m_hMenu()
	, m_TabsID()
	, m_active(false)
	, m_flag_drag(false)
	, m_insrtpos(0)
	, lastidx(0)
	, lastidxs()
	, lasttab(15)
	, tabSortingMethod(false)
{
	m_TabsID[0] = ID_MENU_ADD;
	m_TabsID[1] = ID_MENU_EDIT;
	m_TabsID[2] = ID_MENU_DEL;
	m_TabsID[3] = ID_MENU_COPY;
	m_TabsID[4] = ID_MENU_SEPARATOR;
}

RapidFireDlg::~RapidFireDlg()
{
}

void RapidFireDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_RAPIDFIRE), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hList = GetDlgItem(m_hDlg, IDC_RAPIDFIRE_LIST);

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
	DeleteMenu(m_hMenu, ID_MENU_ADD_NOTICE, FALSE);
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
	col.cx = 112;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = L"";
	col.cx = 112;
	ListView_InsertColumn(m_hList, 2, &col);
	col.pszText = L"";
	col.cx = 111;
	ListView_InsertColumn(m_hList, 3, &col);

	HWND hTip = ListView_GetToolTips(m_hList);
	SetWindowPos(hTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void RapidFireDlg::redrawMenu(int ntabs)
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

/*
INT_PTR RapidFireDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RapidFireDlg* dlg;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (RapidFireDlg*)lParam;
	}
	else
		dlg = (RapidFireDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	else
		return NULL;
}
*/

INT_PTR CALLBACK RapidFireDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	RapidFireDlg* dlg;

	if (uMsg == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<RapidFireDlg*>(lparam);
		SetWindowLongPtrW(hWnd, DWLP_USER, lparam);
	}
	else
		dlg = reinterpret_cast<RapidFireDlg*>(GetWindowLongPtrW(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, uMsg, wparam, lparam);
		return result;
	}
	return DefWindowProcW(hWnd, uMsg, wparam, lparam);
}

INT_PTR RapidFireDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
				int nCharacters;
				for (nCharacters = 0;
					nCharacters < nCharCount; nCharacters++)
					if (wszBuffer[nCharacters] == L'\t' || wszBuffer[nCharacters] == L'\b')
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

					::DrawTextW(hDC, wszBuffer, nCharacters, &rTextMetric, DT_CALCRECT);
					long _CaptionWidth = rTextMetric.right - rTextMetric.left;

					long _AcceleratorWidth = 0;
					if (nCharacters < nCharCount - 1)
					{
						::DrawTextW(hDC, &(wszBuffer[nCharacters + 1]), nCharCount - nCharacters - 1, &rTextMetric, DT_CALCRECT);
						_AcceleratorWidth = rTextMetric.right - rTextMetric.left;
					}
					if (hOldFont == NULL && hOldFont != 0)
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

				int nCharacters;
				for (nCharacters = 0;
					nCharacters < nCharCount; nCharacters++)
					if (wszBuffer[nCharacters] == L'\t' ||
						wszBuffer[nCharacters] == L'\b')
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
				::DrawTextW(DrawMenuStructure->hDC, wszBuffer, nCharacters, &(DrawMenuStructure->rcItem), 0);

				if (nCharacters < nCharCount - 1)
				{
					DrawMenuStructure->rcItem.left += 21;
					if (wszBuffer[nCharacters] == L'\t')
						::DrawTextW(DrawMenuStructure->hDC, &(wszBuffer[nCharacters + 1]),
							nCharCount - nCharacters - 1, &(DrawMenuStructure->rcItem),
							DT_LEFT | DT_SINGLELINE);
					else
						::DrawTextW(DrawMenuStructure->hDC, &(wszBuffer[nCharacters + 1]),
							nCharCount - nCharacters - 1, &(DrawMenuStructure->rcItem),
							DT_RIGHT | DT_SINGLELINE);
					DrawMenuStructure->rcItem.left -= +21;
				}
				DrawMenuStructure->rcItem.left -= nImageOffsetX;
				DrawMenuStructure->rcItem.top -= 0;

				::SetBkMode(DrawMenuStructure->hDC, nOldBkMode);
				::SetTextColor(DrawMenuStructure->hDC, crPrevText);

				if (hOldFont == NULL && hOldFont != 0)
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
		case IDC_RAPIDFIRE_LIST:
			switch (((LPNMLISTVIEW)lParam)->hdr.code)
			{
			case LVN_COLUMNCLICK:
			{
				m_active = false;
				rDDlg.Hide();

				LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
				unsigned char column = pnmv->iSubItem;
				if (lasttab == column)
					tabSortingMethod = !tabSortingMethod;
				else
					tabSortingMethod = false;
				lasttab = column;

				RapidFires newmap;
				RapidFires newmaptmp;
				size_t length = tape.RapidFiredata.size();
				for (int i = 0; i < length; i++)
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

					long value = 0;

					length = newmaptmp.size();
					for (size_t i = 0; i < length; i++)
					{
						long sortresult = 0;

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
							sortresult |= ((long)vjdata[1] << 0);
							sortresult |= ((long)vjdata[0] << 8);
							break;
						}
						case 1:
						{
							sortresult |= ((long)newmaptmp[i].Firsttime << 0);
							break;
						}
						case 2:
						{
							sortresult |= ((long)newmaptmp[i].Releasetime << 0);
							break;
						}
						case 3:
						{
							sortresult |= ((long)newmaptmp[i].Presstime << 0);
							break;
						}
						}

						if (pos == -1 || (pos >= 0 && ((tabSortingMethod) ? sortresult > value : sortresult < value)))
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

				PostMessage(m_hWnd, WM_ADDRAPIDFIRE, 0, -1);

				m_active = true;
				break;
			}
			case NM_DBLCLK:
				editRapidFireDlg();
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
					unsigned long newstate = (((LPNMLISTVIEW)lParam)->uNewState & LVIS_STATEIMAGEMASK);
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
		case ID_MENU_ADD:addRapidFireDlg(); break;
		case ID_MENU_EDIT:editRapidFireDlg(); break;
		case ID_MENU_DEL:deleteRapidFireDlg(); break;
		case ID_MENU_COPY:duplicateRapidFireDlg(); break;
		case ID_MENU_SEPARATOR:addSeparator(); break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
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
			SendMessage(m_hWnd, WM_ADDRAPIDFIRE, 0, -1);
			RECT rect;
			GetWindowRect(m_hWnd, &rect);
			MessageBoxPos(m_hWnd, I18N.MBOX_ErrorWhileSaving, I18N.MBOX_ErrTitle, MB_ICONERROR, rect.left + 275, rect.top + 30);
			return;
		}
		if (item.lParam != NULL)
			newmap.push_back(*(RapidFire*)item.lParam);
	}

	tape.RapidFiredata.swap(newmap);
	tape.Save(tape.Setting_RapidFiredata);
	SendMessage(m_hWnd, WM_ADDRAPIDFIRE, 0, -1);

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
	else if (nselected >= 1)
	{
		lastidxs.clear();
		for (int i = 0; i < RapidFireDataDlg::Mofified_count; i++)
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
			for (int i = 0; i < RapidFireDataDlg::Mofified_count; i++)
				if (rDDlg.Modified[i])
					switch (i)
					{
					default:
					case RapidFireDataDlg::Mofified_ButtonID:data2->ButtonID = data1->ButtonID; break;
					case RapidFireDataDlg::Mofified_ButtonID2:data2->ButtonID2 = data1->ButtonID2; break;
					case RapidFireDataDlg::Mofified_Firsttime:data2->Firsttime = data1->Firsttime; break;
					case RapidFireDataDlg::Mofified_Releasetime:data2->Releasetime = data1->Releasetime; break;
					case RapidFireDataDlg::Mofified_Presstime:data2->Presstime = data1->Presstime; break;
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
	item.lParam = (LPARAM)rf;
	item.pszText = (WCHAR*)rf->KeyString();
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = (WCHAR*)rf->ValueString(1);
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 2;
	item.lParam = 0;
	item.pszText = (WCHAR*)rf->ValueString(2);
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 3;
	item.lParam = 0;
	item.pszText = (WCHAR*)rf->ValueString(3);
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
		SendMessage(m_hList, LVM_SETINSERTMARK, 0, (LPARAM)&mark);
		m_insrtpos = idx;
	}
}

void RapidFireDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}

void RapidFireDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);
}

BOOL RapidFireDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
