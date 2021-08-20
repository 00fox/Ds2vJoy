#include "stdafx.h"
#include "MappingDlg.h"
#include "MappingDataDlg.h"
#include "Ds2vJoy.h"

MappingDlg::MappingDlg()
	:m_flag_drag(false)
{
}

MappingDlg::~MappingDlg()
{
}

void MappingDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_Tab = 0;
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_MAPPING), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_MAPPING));

	m_hList = GetDlgItem(m_hDlg, IDC_MAPPING_LIST);
	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.pszText = I18N.dsButton;
	col.cx = 80;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = L"";
	col.cx = 85;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = L"";
	col.cx = 85;
	ListView_InsertColumn(m_hList, 2, &col);
	col.pszText = I18N.vJoyButton;
	col.cx = 127;
	ListView_InsertColumn(m_hList, 3, &col);
	col.pszText = I18N.TagsButton;
	col.cx = 72;
	ListView_InsertColumn(m_hList, 4, &col);
}

void MappingDlg::Init2(HINSTANCE hInst, HWND hWnd)
{
	m_Tab = 0;
	m_isClonedList = true;
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_MAPPING_2), hWnd, (DLGPROC)Proc, (LPARAM)this);
	LONG lStyle = GetWindowLong(m_hDlg, GWL_STYLE);
	//		lStyle |= WS_THICKFRAME;
	lStyle = lStyle & ~WS_CAPTION;
	SetWindowLong(m_hDlg, GWL_STYLE, lStyle);
	Hide();

	m_hList = GetDlgItem(m_hDlg, IDC_MAPPING_LIST);
	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	//	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_FLATSB;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	HWND header = ListView_GetHeader(m_hList);
	DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
//	dwHeaderStyle |= HDS_HIDDEN | HDS_NOSIZING | HDS_OVERFLOW;
	dwHeaderStyle |= HDS_NOSIZING;
	::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.pszText = I18N.dsButton;
	col.cx = 80;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = L"";
	col.cx = 85;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = L"";
	col.cx = 85;
	ListView_InsertColumn(m_hList, 2, &col);
	col.pszText = I18N.vJoyButton;
	col.cx = 127;
	ListView_InsertColumn(m_hList, 3, &col);
	col.pszText = I18N.TagsButton;
	col.cx = 72;
	ListView_InsertColumn(m_hList, 4, &col);
}

bool MappingDlg::isCloned()
{
	return m_isCloned;
}

void MappingDlg::setCloned(bool cloned)
{
	m_isCloned = cloned;
}

void MappingDlg::SetTab(int tab)
{
	if (m_Tab != tab)
	{
		if (mode >= 0 && mode < 9)
			m_Tab = tab;
		else
			m_Tab = 0;
	}
	SetWindowText(GetDlgItem(m_hDlg, IDC_STATIC), (L" Clone of Tab " + std::to_wstring(m_Tab)).c_str());
	load();
	if (m_isCloned)
	{
		RECT win;
		GetWindowRect(m_hDlg, &win);
		::MoveWindow(m_hList, 2, 35, win.right - win.left, win.bottom - win.top - 36, FALSE);
	}
}

INT_PTR MappingDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MappingDlg* dlg;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (MappingDlg*)lParam;
	}
	else
		dlg = (MappingDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	else
		return NULL;
}

INT_PTR MappingDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SHOWWINDOW:
	{
		SendMessage(m_hList, LVM_SETBKCOLOR, 0, (LPARAM)RGB(210, 210, 215));
		SendMessage(m_hList, LVM_SETTEXTCOLOR, 0, (LPARAM)RGB(10, 10, 10));
		SendMessage(m_hList, LVM_SETTEXTBKCOLOR, 0, (LPARAM)RGB(225, 225, 230));

		if (m_isClonedList)
		{
			HFONT hFont = CreateFont(16, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"MS Shell Dlg");
			SendDlgItemMessage(hWnd, IDCANCEL, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		}

		if (wParam == TRUE)
			load();
		m_active = true;
		break;
	}
	case WM_SIZE:
		if (m_isClonedList)
			::MoveWindow(m_hList, 2, 35, LOWORD(lParam), HIWORD(lParam) - 36, FALSE);
		else
			::MoveWindow(m_hList, 2, 0, LOWORD(lParam), HIWORD(lParam), FALSE);
		break;
	case WM_NCCALCSIZE:
		if (wParam)
		{
			//			NCCALCSIZE_PARAMS FAR* lpncsp = (NCCALCSIZE_PARAMS FAR*)lParam;
			//			lpncsp->rgrc[0].top -= 6;
			//			return FALSE;
			return TRUE;
		}
	case WM_CTLCOLORSCROLLBAR:
	{
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor;
		if (!hBrushColor)
			hBrushColor = CreateSolidBrush(RGB(191, 200, 196));
		SetTextColor(hdcStatic, RGB(10, 10, 10));
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, RGB(191, 200, 196));
		return (LRESULT)hBrushColor;
	}
	case WM_CTLCOLORDLG:
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor;
		if (!hBrushColor)
			hBrushColor = CreateSolidBrush(RGB(210, 210, 215));
		SetTextColor(hdcStatic, RGB(100, 93, 79));
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, RGB(36, 163, 163));
		return (LRESULT)hBrushColor;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor;
		if (!hBrushColor)
			hBrushColor = CreateSolidBrush(RGB(228, 228, 232));
		SetTextColor(hdcStatic, RGB(62, 20, 102));
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, RGB(255, 255, 0));
		return (LRESULT)hBrushColor;
	}
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor;
		if (!hBrushColor)
			hBrushColor = CreateSolidBrush(RGB(216, 215, 220));
		SetTextColor(hdcStatic, RGB(10, 10, 10));
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, RGB(255, 255, 0));
		return (LRESULT)hBrushColor;
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;

			GetClientRect(hWnd, &rect);

			HBRUSH brush = CreateSolidBrush(RGB(240, 240, 240));
			FillRect(hDC, &rect, brush);
			DeleteObject(brush);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_NOTIFY:
		if (m_isClonedList)
			break;
		else
		{
			switch (((LPNMHDR)lParam)->idFrom)
			{
			case IDC_MAPPING_LIST:
				/*			if (((LPNMHEADER)lParam)->iItem)
							{
								switch (((LPNMHDR)lParam)->code)
								{
								case HDN_OVERFLOWCLICK:
								case -166:
									m_isCloned = false;
									Hide();
									break;
								}
							}*/
				switch (((LPNMLISTVIEW)lParam)->hdr.code)
				{
				case NM_DBLCLK:
					editMappingDlg();
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
							Mapping* m = (Mapping*)((LPNMLISTVIEW)lParam)->lParam;
							if (m != 0)
							{
								int idx = ListView_GetNextItem(m_hList, -1, LVNI_FOCUSED);
								if (idx == -1)
								{
									idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
									m->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
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
				break;
			default:
				return FALSE;
			}
			break;
		}
	case WM_MOUSEMOVE:
		if (m_isClonedList)
			break;
		else
		{
			if (m_flag_drag && GetCapture() == hWnd)
				DragMove(LOWORD(lParam), HIWORD(lParam));
			break;
		}
	case WM_LBUTTONUP:
		if (m_isClonedList)
			break;
		else
		{
			if (m_flag_drag && GetCapture() == hWnd)
			{
				EndDrag(LOWORD(lParam), HIWORD(lParam));
				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;
		}
	case WM_COMMAND:
		if (m_isClonedList)
		{
			switch (LOWORD(wParam))
			{
			case IDCANCEL:
				m_isCloned = false;
				Hide();
				break;
			}
			break;
		}
		else
		{
			switch (LOWORD(wParam))
			{
			case IDCANCEL:
				m_isCloned = false;
				Hide();
				break;
			case ID_MENU_MAPPING_ADD:
				addMappingDlg();
				break;
			case ID_MENU_MAPPING_EDIT:
				editMappingDlg();
				break;
			case ID_MENU_MAPPING_DEL:
				deleteMappingDlg();
				break;
			case ID_MENU_MAPPING_COPY:
				duplicateMappingDlg();
				break;
			case ID_MENU_MOVE_TO_0:
				moveMappingDlg(0);
				break;
			case ID_MENU_MOVE_TO_1:
				moveMappingDlg(1);
				break;
			case ID_MENU_MOVE_TO_2:
				moveMappingDlg(2);
				break;
			case ID_MENU_MOVE_TO_3:
				moveMappingDlg(3);
				break;
			case ID_MENU_MOVE_TO_4:
				moveMappingDlg(4);
				break;
			case ID_MENU_MOVE_TO_5:
				moveMappingDlg(5);
				break;
			case ID_MENU_MOVE_TO_6:
				moveMappingDlg(6);
				break;
			case ID_MENU_MOVE_TO_7:
				moveMappingDlg(7);
				break;
			case ID_MENU_MOVE_TO_8:
				moveMappingDlg(8);
				break;
			}
			break;
		}
	default:
		return FALSE;
	}
	return TRUE;
}

void MappingDlg::load()
{
	m_active = false;
	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL)
			delete (Mapping*)item.lParam;
		if (!ListView_DeleteItem(m_hList, 0))
			break;
	}
	ListView_DeleteAllItems(m_hList);
//	SetFocus(m_hList);
	size_t length = tape.Mappingdata.size();
	int j = 0;
	for (int i = 0; i < length; i++)
	{
		Mapping* m = new Mapping(tape.Mappingdata[i]);
		if (m->Tab == m_Tab)
		{
			insertMapping(j, m);
			j++;
		}
	}
	m_active = true;
}

void MappingDlg::save(bool closeeditor)
{
	m_active = false;

	Mappings newmap;
	size_t length = tape.Mappingdata.size();
	for (int i = 0; i < length; i++)
		if (tape.Mappingdata[i].Tab != m_Tab)
			newmap.push_back((Mapping)tape.Mappingdata[i]);

	while (ListView_GetNextItem(m_hList, -1, LVNI_ALL) != -1)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		if (!ListView_GetItem(m_hList, &item))
			break;
		if (item.lParam != NULL)
		{
			newmap.push_back(*(Mapping*)item.lParam);
			delete (Mapping*)item.lParam;
		}
		if (!ListView_DeleteItem(m_hList, 0))
			break;
	}
	ListView_DeleteAllItems(m_hList);

	Mappings newmap2;
	length = newmap.size();
	for (int j = 0; j < 9; j++)
		for (int i = 0; i < length; i++)
			if (newmap[i].Tab == j)
				newmap2.push_back((Mapping)newmap[i]);

	tape.Mappingdata.swap(newmap2);
	tape.Save(200);

	PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
	if (closeeditor)
		PostMessage(m_hWnd, WM_ADDMAPPING, 0, -1);
	else
		PostMessage(m_hWnd, WM_ADDMAPPING, -1, -1);

	m_active = true;
}

void MappingDlg::addMappingDlg()
{
	m_active = false;
	mDDlg.Hide();
	Mapping m;
	mDDlg.mappingData = m;
	mDDlg.Open(m_hDlg, -1);
	m_active = true;
}

void MappingDlg::addMappingDlgBack()
{
	m_active = false;
	int idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
	if (idx == -1)
		idx = ListView_GetItemCount(m_hList);
	Mapping* data = new Mapping(mDDlg.mappingData);
	data->Tab = m_Tab;
	insertMapping(idx, data);
	save(false);
	m_active = true;
}

void MappingDlg::editMappingDlg()
{
	mDDlg.Hide();
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
		Mapping* data = (Mapping*)item.lParam;
		mDDlg.mappingData = *data;
		mDDlg.Open(m_hDlg, idx);
	}
	m_active = true;
}

void MappingDlg::editMappingDlgBack(int idx)
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
		Mapping* data = (Mapping*)item.lParam;
		*data = mDDlg.mappingData;
		ListView_DeleteItem(m_hList, idx);
		insertMapping(idx, data);
		save();
	}
	m_active = true;
}

void MappingDlg::deleteMappingDlg()
{
	m_active = false;
	mDDlg.Hide();
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
			delete (Mapping*)item.lParam;
			ListView_DeleteItem(m_hList, idx);
		}
		save();
	}
	m_active = true;
}

void MappingDlg::duplicateMappingDlg()
{
	mDDlg.Hide();
	m_active = false;
	int nselected = ListView_GetSelectedCount(m_hList);
	if (nselected == 1)
	{
		int idx = ListView_GetNextItem(m_hList, -1, LVNI_FOCUSED);
		if (idx == -1)
		{
			idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
			if (idx == -1)
				return;
		}
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		item.iItem = idx;
		item.iSubItem = 0;
		ListView_GetItem(m_hList, &item);
		if (item.lParam != NULL)
		{
			Mapping* data = (Mapping*)item.lParam;
			mDDlg.mappingData = *data;
			data = new Mapping(mDDlg.mappingData);
			insertMapping(idx + 1, data);
			save();
		}
	}
	else if (nselected >= 1)
	{
		int idx;
		int lastitemindex = ListView_GetItemCount(m_hList);
		ListView_GetNextItem(m_hList, 1, LVNI_ALL);
		while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1)
		{
			LV_ITEM item = { 0 };
			item.mask = LVIF_PARAM;
			item.iItem = idx;
			item.iSubItem = 0;
			ListView_GetItem(m_hList, &item);
			if (item.lParam != NULL)
			{
				Mapping* data1 = (Mapping*)item.lParam;
				Mapping* data2 = (Mapping*)item.lParam;
				mDDlg.mappingData = *data1;
				data1 = new Mapping(mDDlg.mappingData);
				mDDlg.mappingData = *data2;
				data2 = new Mapping(mDDlg.mappingData);
				ListView_DeleteItem(m_hList, idx);
				insertMapping(idx, data1);
				insertMapping(lastitemindex + 1, data2);
				lastitemindex++;
			}
		}
		save();
	}
	m_active = true;
}

void MappingDlg::moveMappingDlg(int tab)
{
	if (tab == m_Tab)
		return;
	mDDlg.Hide();
	m_active = false;
	int idx;
	while ((idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED)) != -1)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		item.iItem = idx;
		item.iSubItem = 0;
		ListView_GetItem(m_hList, &item);
		if (item.lParam != NULL)
		{
			Mapping* data = (Mapping*)item.lParam;
			data->Tab = tab;
			ListView_DeleteItem(m_hList, idx);
			insertMapping(idx, data);
		}
	}
	save();
	m_active = true;
}

int MappingDlg::insertMapping(int idx, Mapping* m)
{
	if (idx < 0)
		return FALSE;
	m_active = false;
	LVITEM item = { 0 };
	bool enable = m->Enable;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	item.lParam = (LPARAM)m;
	item.pszText = (WCHAR*)m->dsString();
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = (WCHAR*)m->dsLastString();
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 2;
	item.lParam = 0;
	item.pszText = (WCHAR*)m->dsNotString();
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 3;
	item.lParam = 0;
	item.pszText = (WCHAR*)m->vJoyString();
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 4;
	item.lParam = 0;
	item.pszText = (WCHAR*)m->TagsString();
	ListView_SetItem(m_hList, &item);
	ListView_SetCheckState(m_hList, idx, enable);

	m_active = true;
	return ret;
}

void MappingDlg::BeginDrag(int idx)
{
	if (ListView_GetNextItem(m_hList, -1, LVNI_SELECTED) == -1)
		return;
	m_flag_drag = true;
	SetCapture(m_hDlg);
}

void MappingDlg::DragMove(int x, int y)
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

void MappingDlg::EndDrag(int x, int y)
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
			int ret = insertMapping(ht.iItem, (Mapping*)item.lParam);
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

void MappingDlg::setInsertMark(int idx)
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
