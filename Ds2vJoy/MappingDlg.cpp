#include "stdafx.h"
#include "MappingDlg.h"
#include "MappingDataDlg.h"

MappingDlg::MappingDlg()
{
}

MappingDlg::~MappingDlg()
{
}

void MappingDlg::Init(bool isClone)
{
	m_Tab = 0;
	m_hDlg2 = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_MIND), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));
	Hide();
	SendDlgItemMessage(m_hDlg2, IDC_MAPPING_MIND_TEXT, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg2, IDC_MIND_OK, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg2, IDC_MIND_CANCEL, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg2, IDC_MIND_OK), I18N.MIND_OK);
	SetWindowText(GetDlgItem(m_hDlg2, IDC_MIND_CANCEL), I18N.MIND_CANCEL);

	if (isClone)
	{
		m_isClonedList = true;
		m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_CLONE), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));

		for (int i = 0; i < 32; i++) { m_Randcolor[i] = rand() % 4; }

		int lStyle = GetWindowLong(m_hDlg, GWL_STYLE);
		lStyle = lStyle & ~WS_CAPTION;
		SetWindowLong(m_hDlg, GWL_STYLE, lStyle);

		SendDlgItemMessage(m_hDlg, IDC_CLONE_MENU, WM_SETFONT, WPARAM(tape.hMenu2), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_STATS, WM_SETFONT, WPARAM(tape.hStats), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_STAT1, WM_SETFONT, WPARAM(tape.hStats), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_STAT2, WM_SETFONT, WPARAM(tape.hStats), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_STAT3, WM_SETFONT, WPARAM(tape.hStats), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_STAT4, WM_SETFONT, WPARAM(tape.hStats), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_STAT5, WM_SETFONT, WPARAM(tape.hStats), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_STAT6, WM_SETFONT, WPARAM(tape.hStats), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_STAT7, WM_SETFONT, WPARAM(tape.hStats), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_STAT8, WM_SETFONT, WPARAM(tape.hStats), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_CANCEL, WM_SETFONT, WPARAM(tape.hCancel), MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(m_hDlg, IDC_CLONE_POSTIT, WM_SETFONT, WPARAM(tape.hPostIt), MAKELPARAM(TRUE, 0));
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_MENU), I18N.CLONE_MENU);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_STATS), I18N.CLONE_STATS);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_STAT1), I18N.CLONE_STAT1);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_STAT2), I18N.CLONE_STAT2);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_STAT3), I18N.CLONE_STAT3);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_STAT4), I18N.CLONE_STAT4);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_STAT5), I18N.CLONE_STAT5);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_STAT6), I18N.CLONE_STAT6);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_STAT7), I18N.CLONE_STAT7);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_STAT8), I18N.CLONE_STAT8);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_CANCEL), I18N.CLONE_CANCEL);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_CLEAR), I18N.CLONE_CLEAR);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_POSTIT), I18N.CLONE_POSTIT);

		m_ReminderId[0] = IDC_POST_ITS_1;
		m_ReminderId[1] = IDC_POST_ITS_2;
		m_ReminderId[2] = IDC_POST_ITS_3;
		m_ReminderId[3] = IDC_POST_ITS_4;
		m_ReminderId[4] = IDC_POST_ITS_5;
		m_ReminderId[5] = IDC_POST_ITS_6;
		m_ReminderId[6] = IDC_POST_ITS_7;
		m_ReminderId[7] = IDC_POST_ITS_8;
		m_ReminderId[8] = IDC_POST_ITS_9;
		m_ReminderId[9] = IDC_POST_ITS_10;
		m_ReminderId[10] = IDC_POST_ITS_11;
		m_ReminderId[11] = IDC_POST_ITS_12;
		m_ReminderId[12] = IDC_POST_ITS_13;
		m_ReminderId[13] = IDC_POST_ITS_14;
		m_ReminderId[14] = IDC_POST_ITS_15;
		m_ReminderId[15] = IDC_POST_ITS_16;
		m_ReminderId[16] = IDC_POST_ITS_17;
		m_ReminderId[17] = IDC_POST_ITS_18;
		m_ReminderId[18] = IDC_POST_ITS_19;
		m_ReminderId[19] = IDC_POST_ITS_20;
		m_ReminderId[20] = IDC_POST_ITS_21;
		m_ReminderId[21] = IDC_POST_ITS_22;
		m_ReminderId[22] = IDC_POST_ITS_23;
		m_ReminderId[23] = IDC_POST_ITS_24;
		m_ReminderId[24] = IDC_POST_ITS_25;
		m_ReminderId[25] = IDC_POST_ITS_26;
		m_ReminderId[26] = IDC_POST_ITS_27;
		m_ReminderId[27] = IDC_POST_ITS_28;
		m_ReminderId[28] = IDC_POST_ITS_29;
		m_ReminderId[29] = IDC_POST_ITS_30;
		m_ReminderId[30] = IDC_POST_ITS_31;
		m_ReminderId[31] = IDC_POST_ITS_32;

		SetTimer(m_hDlg, 1, 50, NULL);
	}
	else
		m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_MAPPING), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));

	{
		int m_TabsID[10];
		m_TabsID[0] = IDM_MENU_SEE_VIEW2;
		m_TabsID[1] = IDM_MENU_TO_MODE_0;
		m_TabsID[2] = IDM_MENU_TO_MODE_1;
		m_TabsID[3] = IDM_MENU_TO_MODE_2;
		m_TabsID[4] = IDM_MENU_TO_MODE_3;
		m_TabsID[5] = IDM_MENU_TO_MODE_4;
		m_TabsID[6] = IDM_MENU_TO_MODE_5;
		m_TabsID[7] = IDM_MENU_TO_MODE_6;
		m_TabsID[8] = IDM_MENU_TO_MODE_7;
		m_TabsID[9] = IDM_MENU_TO_MODE_8;
		hMenu_Tabs = LoadMenu(tape.Ds2hInst, MAKEINTRESOURCE(IDR_MENU_TABS));
		DeleteMenu(hMenu_Tabs, IDM_MENU_TO_MODE_0, FALSE);
		DeleteMenu(hMenu_Tabs, IDM_MENU_TO_MODE_1, FALSE);
		DeleteMenu(hMenu_Tabs, IDM_MENU_TO_MODE_2, FALSE);
		DeleteMenu(hMenu_Tabs, IDM_MENU_TO_MODE_3, FALSE);
		DeleteMenu(hMenu_Tabs, IDM_MENU_TO_MODE_4, FALSE);
		DeleteMenu(hMenu_Tabs, IDM_MENU_TO_MODE_5, FALSE);
		DeleteMenu(hMenu_Tabs, IDM_MENU_TO_MODE_6, FALSE);
		DeleteMenu(hMenu_Tabs, IDM_MENU_TO_MODE_7, FALSE);
		DeleteMenu(hMenu_Tabs, IDM_MENU_TO_MODE_8, FALSE);
		hMenu_Tabs_2 = LoadMenu(tape.Ds2hInst, MAKEINTRESOURCE(IDR_MENU_TABS));
		MENUITEMINFO info;
		for (int i = 0; i < 10; i++)
		{
			ZeroMemory(&info, sizeof(info));
			info.cbSize = sizeof(info);
			info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING;
			GetMenuItemInfo(hMenu_Tabs_2, m_TabsID[i], FALSE, &info);
			if (i == 0)
				GetMenuItemInfo(hMenu_Tabs, m_TabsID[i], FALSE, &info);
			info.fType = MFT_OWNERDRAW;
			info.fState = MFS_UNCHECKED;
			switch (i)
			{
			case 0: info.dwTypeData = I18N.MENU_SEE_VIEW2; break;
			case 1: info.dwTypeData = I18N.MENU_TO_MODE_0; break;
			case 2: info.dwTypeData = I18N.MENU_TO_MODE_1; break;
			case 3: info.dwTypeData = I18N.MENU_TO_MODE_2; break;
			case 4: info.dwTypeData = I18N.MENU_TO_MODE_3; break;
			case 5: info.dwTypeData = I18N.MENU_TO_MODE_4; break;
			case 6: info.dwTypeData = I18N.MENU_TO_MODE_5; break;
			case 7: info.dwTypeData = I18N.MENU_TO_MODE_6; break;
			case 8: info.dwTypeData = I18N.MENU_TO_MODE_7; break;
			case 9: info.dwTypeData = I18N.MENU_TO_MODE_8; break;
			}
			SetMenuItemInfo(hMenu_Tabs_2, m_TabsID[i], FALSE, &info);
			if (i == 0)
				SetMenuItemInfo(hMenu_Tabs, m_TabsID[i], FALSE, &info);
		}
	}

	{
		m_TabsID[0] = IDM_MENU_DISABLE;
		m_TabsID[1] = IDM_MENU_ADD;
		m_TabsID[2] = IDM_MENU_EDIT;
		m_TabsID[3] = IDM_MENU_DEL;
		m_TabsID[4] = IDM_MENU_COPY;
		m_TabsID[5] = IDM_MENU_SEPARATOR;
		m_TabsID[6] = IDM_MENU_MOVE_TO_0;
		m_TabsID[7] = IDM_MENU_MOVE_TO_1;
		m_TabsID[8] = IDM_MENU_MOVE_TO_2;
		m_TabsID[9] = IDM_MENU_MOVE_TO_3;
		m_TabsID[10] = IDM_MENU_MOVE_TO_4;
		m_TabsID[11] = IDM_MENU_MOVE_TO_5;
		m_TabsID[12] = IDM_MENU_MOVE_TO_6;
		m_TabsID[13] = IDM_MENU_MOVE_TO_7;
		m_TabsID[14] = IDM_MENU_MOVE_TO_8;
		m_TabsID[15] = IDM_MENU_SWAP_VIEW;
		m_TabsID[16] = IDM_MENU_ADD_NOTICE;
		m_hMenu = LoadMenu(tape.Ds2hInst, MAKEINTRESOURCE(IDR_MENU_MAPPING));
		redrawMenu(17);

		if (isClone)
		{
			m_TabsID[0] = IDM_CLONE_TO_MODE_0;
			m_TabsID[1] = IDM_CLONE_TO_MODE_1;
			m_TabsID[2] = IDM_CLONE_TO_MODE_2;
			m_TabsID[3] = IDM_CLONE_TO_MODE_3;
			m_TabsID[4] = IDM_CLONE_TO_MODE_4;
			m_TabsID[5] = IDM_CLONE_TO_MODE_5;
			m_TabsID[6] = IDM_CLONE_TO_MODE_6;
			m_TabsID[7] = IDM_CLONE_TO_MODE_7;
			m_TabsID[8] = IDM_CLONE_TO_MODE_8;
			m_hMenu2 = LoadMenu(tape.Ds2hInst, MAKEINTRESOURCE(IDR_MENU_CLONE));
			redrawMenu(9, true);
		}
	}

	{
		m_hList = GetDlgItem(m_hDlg, IDC_MAPPING_LIST);
		DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
		dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_NOCOLUMNHEADER;
		ListView_SetExtendedListViewStyle(m_hList, dwStyle);

		HWND header = ListView_GetHeader(m_hList);
		DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
		dwHeaderStyle = dwHeaderStyle & ~HDS_DRAGDROP | HDS_NOSIZING | HDS_HIDDEN;
		::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

		LVCOLUMN col;
		col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		col.fmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH | HDF_OWNERDRAW;
		col.pszText = I18N.srceButton;
		col.cx = 53;
		ListView_InsertColumn(m_hList, 0, &col);
		col.pszText = WCHARI(L"");
		col.cx = 58;
		ListView_InsertColumn(m_hList, 1, &col);
		col.pszText = WCHARI(L"");
		col.cx = 58;
		ListView_InsertColumn(m_hList, 2, &col);
		col.pszText = WCHARI(L"");
		col.cx = 58;
		ListView_InsertColumn(m_hList, 3, &col);
		col.pszText = WCHARI(L"");
		col.cx = 58;
		ListView_InsertColumn(m_hList, 4, &col);
		col.pszText = (tape.MappingViewMode) ? I18N.Notice : I18N.destButton;
		col.cx = 126 - ((isClone) ? GetSystemMetrics(SM_CXVSCROLL) + 2 : 0);
		ListView_InsertColumn(m_hList, 5, &col);
		col.pszText = I18N.TagsButton;
		col.cx = 57;
		ListView_InsertColumn(m_hList, 6, &col);

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

	if (!isClone)
	{
		m_hTab = GetDlgItem(m_hDlg, IDC_MAPPING_TAB);
		SendMessage(m_hTab, WM_SETFONT, WPARAM(tape.hTab2), TRUE);
		TabCtrl_SetItemSize(m_hTab, 43, 17);
		TabCtrl_SetPadding(m_hTab, 0, 1);
		redrawTabs(tape.TabMapping, false);
	}
	else
	{
		Show();
		Hide();
	}
}

void MappingDlg::SetTab(int tab, bool activate)
{
	if (m_Tab != tab)
	{
		if (mode >= 0 && mode < 9 && tab != -1)
			m_Tab = tab;
		else
			m_Tab = 0;
		tape.TabMapping = m_Tab;
		tape.Save(tape.Setting_TabMapping);
	}
	if (m_isClonedList)
		ShowWindow(GetDlgItem(m_hDlg, IDC_CLONE_MENU), SW_HIDE);
	else
	{
		if (tape.DarkTheme)
			TabCtrl_DeselectAll(m_hTab, FALSE);
		else
			TabCtrl_SetCurSel(m_hTab, tab);
	}
	load();
	if (m_isClonedList)
	{
		redrawMenu(9, true);
		SetWindowText(GetDlgItem(m_hDlg, IDC_CLONE_MENU), (I18N.Clone_of_Tab + std::to_wstring(m_Tab)).c_str());
		ShowWindow(GetDlgItem(m_hDlg, IDC_CLONE_MENU), SW_SHOW);
		redrawListReminder();
	}
	Hide();
	if (activate)
		Show();
}

void MappingDlg::redrawTabs(int tab, bool actualize)
{
	TCITEM tc_item;
	tc_item.mask = TCIF_TEXT;
	WCHAR buff[MAX_PATH];
	TabCtrl_DeleteAllItems(m_hTab);
	for (int i = 0; i < 9; i++)
	{
		TabCtrl_SetItem(m_hTab, i, L"");
		if (tape.Mode[i])
		{
			_snwprintf_s(buff, sizeof(buff), L"%d: m%d", i, tape.Mode[i]);
			tc_item.pszText = buff;
		}
		else
		{
			if (i)
				_snwprintf_s(buff, sizeof(buff), L"%d", i);
			else
				_snwprintf_s(buff, sizeof(buff), L"%s", I18N.MAPPING_ALWAYS);
			tc_item.pszText = buff;
		}
		TabCtrl_InsertItem(m_hTab, i, &tc_item);
	}
	if (actualize)
	{
		ShowWindow(m_hTab, SW_HIDE);
		ShowWindow(m_hTab, SW_SHOW);
	}
	SetTab(tab, actualize);
}

void MappingDlg::redrawMenu(int ntabs, bool isclonemenu)
{
	MENUITEMINFO info;
	if (isclonemenu)
		for (int i = 0; i < ntabs; i++)
		{
			ZeroMemory(&info, sizeof(info));
			info.cbSize = sizeof(info);
			info.fMask = MIIM_FTYPE | MIIM_STATE | MIIM_STRING;
			GetMenuItemInfo(m_hMenu2, m_TabsID[i], FALSE, &info);
			info.fType = MFT_RADIOCHECK | MFT_OWNERDRAW;
			if (i == m_Tab && m_isClonedList)
				info.fState = MFS_DISABLED | MFS_DEFAULT | MFS_HILITE;
			else
				info.fState = MFS_UNCHECKED;
			switch (i)
			{
			case 0: info.dwTypeData = I18N.CLONE_TO_MODE_0; break;
			case 1: info.dwTypeData = I18N.CLONE_TO_MODE_1; break;
			case 2: info.dwTypeData = I18N.CLONE_TO_MODE_2; break;
			case 3: info.dwTypeData = I18N.CLONE_TO_MODE_3; break;
			case 4: info.dwTypeData = I18N.CLONE_TO_MODE_4; break;
			case 5: info.dwTypeData = I18N.CLONE_TO_MODE_5; break;
			case 6: info.dwTypeData = I18N.CLONE_TO_MODE_6; break;
			case 7: info.dwTypeData = I18N.CLONE_TO_MODE_7; break;
			case 8: info.dwTypeData = I18N.CLONE_TO_MODE_8; break;
			}
			SetMenuItemInfo(m_hMenu2, m_TabsID[i], FALSE, &info);
		}
	else
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
			case 0 : info.dwTypeData = I18N.MENU_DISABLE; break;
			case 1 : info.dwTypeData = I18N.MENU_ADD; break;
			case 2 : info.dwTypeData = I18N.MENU_EDIT; break;
			case 3 : info.dwTypeData = I18N.MENU_DEL; break;
			case 4 : info.dwTypeData = I18N.MENU_COPY; break;
			case 5 : info.dwTypeData = I18N.MENU_SEPARATOR; break;
			case 6 : info.dwTypeData = I18N.MENU_MOVE_TO_0; break;
			case 7 : info.dwTypeData = I18N.MENU_MOVE_TO_1; break;
			case 8 : info.dwTypeData = I18N.MENU_MOVE_TO_2; break;
			case 9 : info.dwTypeData = I18N.MENU_MOVE_TO_3; break;
			case 10: info.dwTypeData = I18N.MENU_MOVE_TO_4; break;
			case 11: info.dwTypeData = I18N.MENU_MOVE_TO_5; break;
			case 12: info.dwTypeData = I18N.MENU_MOVE_TO_6; break;
			case 13: info.dwTypeData = I18N.MENU_MOVE_TO_7; break;
			case 14: info.dwTypeData = I18N.MENU_MOVE_TO_8; break;
			case 15: info.dwTypeData = I18N.MENU_SWAP_VIEW; break;
			case 16: info.dwTypeData = I18N.MENU_ADD_NOTICE; break;
			}
			SetMenuItemInfo(m_hMenu, m_TabsID[i], FALSE, &info);
		}
}

void MappingDlg::redrawListReminder()
{
	RECT win;
	GetWindowRect(m_hDlg, &win);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_MAPPING_CLEAR), 7, win.bottom - win.top - 18, 70, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_CLONE_POSTIT), 7, win.bottom - win.top - 18, 70, 12, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_1), 85, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_2), 94, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_3), 107, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_4), 116, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_5), 129, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_6), 138, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_7), 151, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_8), 160, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_9), 173, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_10), 182, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_11), 206, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_12), 215, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_13), 228, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_14), 237, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_15), 250, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_16), 259, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_17), 272, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_18), 281, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_19), 294, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_20), 303, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_21), 327, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_22), 336, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_23), 349, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_24), 358, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_25), 371, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_26), 380, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_27), 393, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_28), 402, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_29), 415, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_30), 424, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_31), 448, win.bottom - win.top - 17, 11, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_POST_ITS_32), 458, win.bottom - win.top - 17, 11, 11, FALSE);
}

void MappingDlg::PageUp()
{
	ListView_Scroll(m_hList, 0, -14);
}

void MappingDlg::PageDown()
{
	ListView_Scroll(m_hList, 0, 14);
}

void MappingDlg::PageHome()
{
	ListView_Scroll(m_hList, 0, -32765);
}

void MappingDlg::PageEnd()
{
	ListView_Scroll(m_hList, 0, 32765);
}

void MappingDlg::_InitDialog(HWND hWnd)
{
	if (m_isClonedList)
	{
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_1), WCHARI(L"1"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_2), WCHARI(L"2"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_3), WCHARI(L"3"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_4), WCHARI(L"4"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_5), WCHARI(L"5"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_6), WCHARI(L"6"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_7), WCHARI(L"7"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_8), WCHARI(L"8"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_9), WCHARI(L"9"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_10), WCHARI(L"10"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_11), WCHARI(L"11"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_12), WCHARI(L"12"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_13), WCHARI(L"13"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_14), WCHARI(L"14"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_15), WCHARI(L"15"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_16), WCHARI(L"16"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_17), WCHARI(L"17"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_18), WCHARI(L"18"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_19), WCHARI(L"19"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_20), WCHARI(L"20"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_21), WCHARI(L"21"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_22), WCHARI(L"22"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_23), WCHARI(L"23"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_24), WCHARI(L"24"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_25), WCHARI(L"25"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_26), WCHARI(L"26"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_27), WCHARI(L"27"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_28), WCHARI(L"28"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_29), WCHARI(L"29"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_30), WCHARI(L"30"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_31), WCHARI(L"31"));
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_32), WCHARI(L"32"));
	}

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void MappingDlg::_ShowWindow(HWND hWnd)
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

	if (m_isClonedList)
	{
		CheckDlgButton(hWnd, IDC_POST_ITS_1, tape.Reminder[0]);
		CheckDlgButton(hWnd, IDC_POST_ITS_2, tape.Reminder[1]);
		CheckDlgButton(hWnd, IDC_POST_ITS_3, tape.Reminder[2]);
		CheckDlgButton(hWnd, IDC_POST_ITS_4, tape.Reminder[3]);
		CheckDlgButton(hWnd, IDC_POST_ITS_5, tape.Reminder[4]);
		CheckDlgButton(hWnd, IDC_POST_ITS_6, tape.Reminder[5]);
		CheckDlgButton(hWnd, IDC_POST_ITS_7, tape.Reminder[6]);
		CheckDlgButton(hWnd, IDC_POST_ITS_8, tape.Reminder[7]);
		CheckDlgButton(hWnd, IDC_POST_ITS_9, tape.Reminder[8]);
		CheckDlgButton(hWnd, IDC_POST_ITS_10, tape.Reminder[9]);
		CheckDlgButton(hWnd, IDC_POST_ITS_11, tape.Reminder[10]);
		CheckDlgButton(hWnd, IDC_POST_ITS_12, tape.Reminder[11]);
		CheckDlgButton(hWnd, IDC_POST_ITS_13, tape.Reminder[12]);
		CheckDlgButton(hWnd, IDC_POST_ITS_14, tape.Reminder[13]);
		CheckDlgButton(hWnd, IDC_POST_ITS_15, tape.Reminder[14]);
		CheckDlgButton(hWnd, IDC_POST_ITS_16, tape.Reminder[15]);
		CheckDlgButton(hWnd, IDC_POST_ITS_17, tape.Reminder[16]);
		CheckDlgButton(hWnd, IDC_POST_ITS_18, tape.Reminder[17]);
		CheckDlgButton(hWnd, IDC_POST_ITS_19, tape.Reminder[18]);
		CheckDlgButton(hWnd, IDC_POST_ITS_20, tape.Reminder[19]);
		CheckDlgButton(hWnd, IDC_POST_ITS_21, tape.Reminder[20]);
		CheckDlgButton(hWnd, IDC_POST_ITS_22, tape.Reminder[21]);
		CheckDlgButton(hWnd, IDC_POST_ITS_23, tape.Reminder[22]);
		CheckDlgButton(hWnd, IDC_POST_ITS_24, tape.Reminder[23]);
		CheckDlgButton(hWnd, IDC_POST_ITS_25, tape.Reminder[24]);
		CheckDlgButton(hWnd, IDC_POST_ITS_26, tape.Reminder[25]);
		CheckDlgButton(hWnd, IDC_POST_ITS_27, tape.Reminder[26]);
		CheckDlgButton(hWnd, IDC_POST_ITS_28, tape.Reminder[27]);
		CheckDlgButton(hWnd, IDC_POST_ITS_29, tape.Reminder[28]);
		CheckDlgButton(hWnd, IDC_POST_ITS_30, tape.Reminder[29]);
		CheckDlgButton(hWnd, IDC_POST_ITS_31, tape.Reminder[30]);
		CheckDlgButton(hWnd, IDC_POST_ITS_32, tape.Reminder[31]);
	}
	::SetFocus(NULL);
}

INT_PTR CALLBACK MappingDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MappingDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<MappingDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<MappingDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR MappingDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CTLCOLORDLG:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_DLG);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_DLG);
		return (LRESULT)tape.hB_DLG;
	}
	case WM_CTLCOLORMSGBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_MSGBOX);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_MSGBOX);
		return (LRESULT)tape.hB_MSGBOX;
	}
	case WM_CTLCOLORSCROLLBAR:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_SCROLLBAR);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_SCROLLBAR);
		return (LRESULT)tape.hB_SCROLLBAR;
	}
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_BTN);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_BTN);
		if (tape.DarkTheme)
			return (LRESULT)tape.hB_BTN_DARK;
		else
			return (LRESULT)tape.hB_BTN;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		DWORD CtrlID = GetDlgCtrlID((HWND)lParam);
		if (CtrlID == IDC_CLONE_POSTIT)
		{
			SetTextColor(hdcStatic, tape.ink_POSTIT);
			SetBkColor(hdcStatic, tape.Bk_POSTIT);
			return (LRESULT)GetStockObject(NULL_BRUSH);
		}
		else if (CtrlID == IDC_CLONE_MENU)
		{
			SetBkMode(hdcStatic, TRANSPARENT);
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_DARK);
				return (LRESULT)tape.hB_BackGround_DARK;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_BTN_CLONE);
				return (LRESULT)tape.hB_BackGround;
			}
		}
		else
		{
			SetBkMode(hdcStatic, TRANSPARENT);
			SetBkColor(hdcStatic, tape.Bk_STATS);
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_POSTIT);
				return (LRESULT)tape.hB_BackGround_DARK;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_STATIC);
				return (LRESULT)tape.hB_CLONE_BackGround;
			}
		}
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode((HDC)wParam, TRANSPARENT);
		if (tape.DarkTheme)
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TERMINAL);
			return (LRESULT)tape.hB_EDIT_DARK;
		}
		else
		{
			SetTextColor(hdcStatic, tape.ink_EDIT);
			return (LRESULT)tape.hB_EDIT;
		}
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
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			if (tape.DarkTheme)
				FillRect(hDC, &rect, tape.hB_BackGround_DARK);
			else
				FillRect(hDC, &rect, tape.hB_CLONE_BackGround);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);

			for (int i = 0; i < 32; i++)
			{
				if (!tape.Reminder[i])
				{
					hDC = BeginPaint(GetDlgItem(hWnd, m_ReminderId[i]), &ps);
					GetClientRect(GetDlgItem(hWnd, m_ReminderId[i]), &rect);
					rect.right -= 1;
					rect.bottom -= 1;
					if (tape.DarkTheme)
						FillRect(hDC, &rect, tape.hB_POSTIT_DARK);
					else
						FillRect(hDC, &rect, tape.hB_POSTIT);
					if (tape.destUsed[i])
					{
						rect.bottom -= 1;
						rect.right -= 1;
						POINT Pt;
						SelectObject(hDC, GetStockObject(DC_PEN));
						SetDCPenColor(hDC, RGB(90, 90, 90));
						if (i & 1)
						{
							MoveToEx(hDC, rect.right - 4, rect.bottom, &Pt);
							LineTo(hDC, rect.right, rect.bottom);
							LineTo(hDC, rect.right, rect.bottom - 4);
							LineTo(hDC, rect.right - 4, rect.bottom);
							MoveToEx(hDC, rect.right - 3, rect.bottom - 1, &Pt);
							LineTo(hDC, rect.right - 1, rect.bottom - 1);
							LineTo(hDC, rect.right - 1, rect.bottom - 3);
							LineTo(hDC, rect.right - 3, rect.bottom - 1);
						}
						else
						{
							MoveToEx(hDC, rect.left + 4, rect.bottom, &Pt);
							LineTo(hDC, rect.left, rect.bottom);
							LineTo(hDC, rect.left, rect.bottom - 4);
							LineTo(hDC, rect.left + 4, rect.bottom);
							MoveToEx(hDC, rect.left + 3, rect.bottom - 1, &Pt);
							LineTo(hDC, rect.left + 1, rect.bottom - 1);
							LineTo(hDC, rect.left + 1, rect.bottom - 3);
							LineTo(hDC, rect.left + 3, rect.bottom - 1);
						}
					}

					::ReleaseDC(hWnd, hDC);
					EndPaint(GetDlgItem(hWnd, m_ReminderId[i]), &ps);
				}
			}

			for (int i = 0; i < 32; i++)
			{
				if (tape.Reminder[i])
				{
					hDC = BeginPaint(GetDlgItem(hWnd, m_ReminderId[i]), &ps);
					GetClientRect(GetDlgItem(hWnd, m_ReminderId[i]), &rect);
					rect.right -= 1;
					rect.bottom -= 1;
					if (!moving || m_Randcolor[i] == 0)
						FillRect(hDC, &rect, tape.hB_POSTIT_Rand0);
					else if (m_Randcolor[i] == 1)
						FillRect(hDC, &rect, tape.hB_POSTIT_Rand1);
					else if (m_Randcolor[i] == 2)
						FillRect(hDC, &rect, tape.hB_POSTIT_Rand2);
					else
						FillRect(hDC, &rect, tape.hB_POSTIT_Rand3);
					if (tape.destUsed[i])
					{
						rect.bottom -= 1;
						rect.right -= 1;
						POINT Pt;
						SelectObject(hDC, GetStockObject(DC_PEN));
						SetDCPenColor(hDC, RGB(95, 95, 95));
						if (i & 1)
						{
							MoveToEx(hDC, rect.right - 4, rect.bottom, &Pt);
							LineTo(hDC, rect.right, rect.bottom);
							LineTo(hDC, rect.right, rect.bottom - 4);
							LineTo(hDC, rect.right - 4, rect.bottom);
							MoveToEx(hDC, rect.right - 3, rect.bottom - 1, &Pt);
							LineTo(hDC, rect.right - 1, rect.bottom - 1);
							LineTo(hDC, rect.right - 1, rect.bottom - 3);
							LineTo(hDC, rect.right - 3, rect.bottom - 1);
						}
						else
						{
							MoveToEx(hDC, rect.left + 4, rect.bottom, &Pt);
							LineTo(hDC, rect.left, rect.bottom);
							LineTo(hDC, rect.left, rect.bottom - 4);
							LineTo(hDC, rect.left + 4, rect.bottom);
							MoveToEx(hDC, rect.left + 3, rect.bottom - 1, &Pt);
							LineTo(hDC, rect.left + 1, rect.bottom - 1);
							LineTo(hDC, rect.left + 1, rect.bottom - 3);
							LineTo(hDC, rect.left + 3, rect.bottom - 1);
						}
					}

					::ReleaseDC(hWnd, hDC);
					EndPaint(GetDlgItem(hWnd, m_ReminderId[i]), &ps);
				}
			}
		}
		return FALSE;
	}
	case WM_MEASUREITEM:
	{
		LPMEASUREITEMSTRUCT DrawMenuSize = (LPMEASUREITEMSTRUCT)lParam;

		if (DrawMenuSize->CtlType == ODT_LISTVIEW)
			DrawMenuSize->itemHeight = 14;
		else if (DrawMenuSize->CtlType == ODT_MENU)
		{
			DrawMenuSize->itemHeight = 14;
			DrawMenuSize->itemWidth = 75;
		}
		break;
	}
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* DrawMenuStructure = (DRAWITEMSTRUCT*)lParam;

		if (DrawMenuStructure->CtlType == ODT_LISTVIEW)
		{
			bool selected = DrawMenuStructure->itemState & ODS_SELECTED;
			bool checked = ListView_GetCheckState((HWND)DrawMenuStructure->hwndItem, DrawMenuStructure->itemID);

			SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
			SelectObject(DrawMenuStructure->hDC, tape.hList);

			WCHAR wszBuffer[2048];
			ListView_GetItemText((HWND)DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, 0, wszBuffer, 2048);
			std::wstring GetItemText = wszBuffer;
			if (GetItemText.size())
			{
				for (int i = 0; i < (((m_isClonedList && tape.CloneViewMode) || (!m_isClonedList && tape.MappingViewMode)) ? 6 : 7); i++)
				{
					WCHAR wszBuffer[2048];
					ListView_GetItemText((HWND)DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, i, wszBuffer, 2048);
					std::wstring GetItemText = wszBuffer;

					switch (i)
					{
					case 0:
					{
						DrawMenuStructure->rcItem.left = 0;
						DrawMenuStructure->rcItem.right = 53;
						break;
					}
					case 1:
					{
						DrawMenuStructure->rcItem.left = 53;
						DrawMenuStructure->rcItem.right = 111;
						break;
					}
					case 2:
					{
						DrawMenuStructure->rcItem.left = 111;
						DrawMenuStructure->rcItem.right = 169;
						break;
					}
					case 3:
					{
						DrawMenuStructure->rcItem.left = 169;
						DrawMenuStructure->rcItem.right = 227;
						break;
					}
					case 4:
					{
						DrawMenuStructure->rcItem.left = 227;
						DrawMenuStructure->rcItem.right = 285;
						break;
					}
					case 5:
					{
						DrawMenuStructure->rcItem.left = 285;
						DrawMenuStructure->rcItem.right = ((tape.MappingViewMode) ? 468 : 411) - ((m_isClonedList) ? GetSystemMetrics(SM_CXVSCROLL) + 2 : 0);
						break;
					}
					case 6:
					{
						DrawMenuStructure->rcItem.left = 411 - ((m_isClonedList) ? GetSystemMetrics(SM_CXVSCROLL) + 2 : 0);
						DrawMenuStructure->rcItem.right = 468 - ((m_isClonedList) ? GetSystemMetrics(SM_CXVSCROLL) + 2 : 0);
						break;
					}
					}

					std::size_t found = 0;
					bool disable1 = (i < 5) ? (found = GetItemText.find_first_of(L"#")) != std::string::npos : false;
					if (disable1) GetItemText.erase(found, 1);
					bool disable2 = (i < 5) ? (found = GetItemText.find_first_of(L"✱")) != std::string::npos : false;
					if (disable2) GetItemText.erase(found, 1);
					bool not1 = (i < 5) ? GetItemText.find_first_of(L"‒") != std::string::npos : false;
					bool not2 = (i < 5) ? GetItemText.find_first_of(L"=") != std::string::npos : false;

					if (checked)
					{
						if (disable1 || disable2)
						{
							if (tape.DarkTheme)
							{
								if (disable1)
									FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_LIST_Disable1_DARK);
								else
									FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_LIST_Disable2_DARK);
							}
							else
							{
								if (disable1)
									FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_LIST_Disable1);
								else
									FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_LIST_Disable2);
							}
							if (selected)
							{
								SelectObject(DrawMenuStructure->hDC, GetStockObject(DC_PEN));
								SetDCPenColor(DrawMenuStructure->hDC, tape.ink_LIST_Selected);
								MoveToEx(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.left - 4, DrawMenuStructure->rcItem.top, nullptr);
								LineTo(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.right, DrawMenuStructure->rcItem.top);
								MoveToEx(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.left - 4, DrawMenuStructure->rcItem.bottom, nullptr);
								LineTo(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.right, DrawMenuStructure->rcItem.bottom);
								//FrameRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_HIGHLIGHT);
							}
						}
						else if (selected)
							FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_LIST_HIGHLIGHT);
						else
						{
							if (tape.DarkTheme)
								FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_BackGround_DARK);
							else
								FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_BackGround);
						}
						if (not1 || not2)
						{
							if (selected && !(disable1 || disable2))
							{
								if (tape.DarkTheme)
									SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST_not_HIGHLIGHT_DARK);
								else
									SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST_not_HIGHLIGHT);
							}
							else
								SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST_not);
						}
						else if (selected)
						{
							if (tape.DarkTheme)
								SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST_not_HIGHLIGHT_DARK);
							else if (disable1 || disable2)
								SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST);
							else
								SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST_HIGHLIGHT);
						}
						else
						{
							if (tape.DarkTheme && !(disable1 || disable2))
								SetTextColor(DrawMenuStructure->hDC, tape.ink_STATIC_CHK_DARK);
							else
								SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST);
						}
					}
					else
					{
						if (selected)
						{
							FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_LIST_HIGHLIGHT);
							SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST_Disabled);
						}
						else
						{
							if (tape.DarkTheme)
							{
								FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_LIST_Disabled_DARK);
								SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST);
							}
							else
							{
								FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_LIST_Disabled);
								SetTextColor(DrawMenuStructure->hDC, tape.ink_LIST);
							}
						}
					}

					int nCharCount = GetItemText.size();
					if (nCharCount)
					{
						int nCharacters;
						for (nCharacters = 0;
							nCharacters < nCharCount; nCharacters++)
							if (wszBuffer[nCharacters] == L'\t' ||
								wszBuffer[nCharacters] == L'\b')
								break;
						DrawMenuStructure->rcItem.left += 2;
						DrawTextW(DrawMenuStructure->hDC, GetItemText.c_str(), GetItemText.size(), &(DrawMenuStructure->rcItem), DT_VCENTER | DT_SINGLELINE);
					}
				}
			}
			else
			{
				SelectObject(DrawMenuStructure->hDC, GetStockObject(DC_PEN));
				if (selected)
					SetDCPenColor(DrawMenuStructure->hDC, tape.ink_LIST_separator_HIGH);
				else
					SetDCPenColor(DrawMenuStructure->hDC, tape.ink_LIST_separator);
				if (tape.DarkTheme)
					FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_BackGround_DARK);
				else
					FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_BackGround);
				MoveToEx(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.left - 4, DrawMenuStructure->rcItem.top + 7, nullptr);
				LineTo(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.right, DrawMenuStructure->rcItem.top + 7);
			}
		}
		else if (DrawMenuStructure->CtlType == ODT_MENU)
		{
			bool selected = DrawMenuStructure->itemState & ODS_SELECTED;

			int itemnumber = -1;
			switch (DrawMenuStructure->itemID)
			{
			case IDM_CLONE_TO_MODE_0: { itemnumber = 0; break; }
			case IDM_CLONE_TO_MODE_1: { itemnumber = 1; break; }
			case IDM_CLONE_TO_MODE_2: { itemnumber = 2; break; }
			case IDM_CLONE_TO_MODE_3: { itemnumber = 3; break; }
			case IDM_CLONE_TO_MODE_4: { itemnumber = 4; break; }
			case IDM_CLONE_TO_MODE_5: { itemnumber = 5; break; }
			case IDM_CLONE_TO_MODE_6: { itemnumber = 6; break; }
			case IDM_CLONE_TO_MODE_7: { itemnumber = 7; break; }
			case IDM_CLONE_TO_MODE_8: { itemnumber = 8; break; }
			case IDM_MENU_DEL: { itemnumber = 9; break; }
			case IDM_MENU_SEE_VIEW2: { itemnumber = 10; break; }
			}

			if ((m_isClonedList && itemnumber == m_Tab) || (itemnumber == 10 && !selected))
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_SELECTED);
			else if (itemnumber == 10)
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_white);
			else if (selected)
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_HIGHLIGHT);
			else if (itemnumber == 9)
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_red);
			else if (m_isClonedList || tape.DarkTheme)
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_CLONE);
			else
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU);

			SelectObject(DrawMenuStructure->hDC, tape.hMenu);
			WCHAR wszBuffer[MAX_PATH];
			int nCharCount = ::GetMenuString((HMENU)DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
			if (nCharCount > 0)
			{
				COLORREF crCurrText = 0;
				crCurrText = (m_isClonedList && itemnumber == m_Tab) ? tape.ink_MENU_SELECTED : ((selected) ? ((itemnumber == 9) ? tape.ink_MENU_Delete : ((itemnumber == 10) ? tape.ink_MENU_SeeView2_HIGH : tape.ink_MENU_HIGHLIGHT)) : ((itemnumber == 10) ? tape.ink_MENU_SeeView2 : tape.ink_MENU));
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
		else if (DrawMenuStructure->CtlType == ODT_TAB)
		{
			BOOL selected = DrawMenuStructure->itemState & ODS_SELECTED;

			if (tape.DarkTheme)
			{
				if (std::chrono::system_clock::now() - m_timeOfLastDarkMenuCall > std::chrono::milliseconds{ 1 })
				{
					m_timeOfLastDarkMenuCall = std::chrono::system_clock::now();
					SetTimer(hWnd, 2, USER_TIMER_MINIMUM, NULL);
				}
				else
					m_timeOfLastDarkMenuCall = std::chrono::system_clock::now();
			}
			else
			{
				RECT rect = DrawMenuStructure->rcItem;
				TC_ITEM tc_item;
				tc_item.mask = TCIF_TEXT;
				WCHAR buff[MAX_PATH - 1];
				tc_item.pszText = buff;
				tc_item.cchTextMax = MAX_PATH - 1;
				if (!TabCtrl_GetItem(m_hTab, DrawMenuStructure->itemID, &tc_item))
					return FALSE;

				rect.top += ::GetSystemMetrics(SM_CYEDGE);

				SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
				SetTextColor(DrawMenuStructure->hDC, tape.ink_TAB);

				WCHAR wszBuffer[MAX_PATH];
				int nCharCount = _snwprintf_s(wszBuffer, sizeof(wszBuffer), L"%s", buff);
				if (nCharCount > 0)
				{
					int nCharacters;
					for (nCharacters = 0;
						nCharacters < nCharCount; nCharacters++)
						if (wszBuffer[nCharacters] == L'\t' ||
							wszBuffer[nCharacters] == L'\b')
							break;
					DrawTextW(DrawMenuStructure->hDC, wszBuffer, nCharacters, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
		}
		break;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
			std::thread(&MappingDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&MappingDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_TIMER:
	{
		if (IsIconic(hWnd) || !IsWindowVisible(m_hDlg))
			break;

		if (wParam == 1)
		{
			SetWindowText(GetDlgItem(hWnd, IDC_CLONE_STAT1), WCHARI(6, L"%05d", tape.Stat[0]));
			SetWindowText(GetDlgItem(hWnd, IDC_CLONE_STAT2), WCHARI(6, L"%05d", tape.Stat[1]));
			SetWindowText(GetDlgItem(hWnd, IDC_CLONE_STAT3), WCHARI(6, L"%05d", tape.Stat[2]));
			SetWindowText(GetDlgItem(hWnd, IDC_CLONE_STAT4), WCHARI(6, L"%05d", tape.Stat[3]));
			SetWindowText(GetDlgItem(hWnd, IDC_CLONE_STAT5), WCHARI(6, L"%05d", tape.Stat[4]));
			SetWindowText(GetDlgItem(hWnd, IDC_CLONE_STAT6), WCHARI(6, L"%05d", tape.Stat[5]));
			SetWindowText(GetDlgItem(hWnd, IDC_CLONE_STAT7), WCHARI(6, L"%05d", tape.Stat[6]));
			SetWindowText(GetDlgItem(hWnd, IDC_CLONE_STAT8), WCHARI(6, L"%05d", tape.Stat[7]));
		}
		else if (wParam == 2)
		{
			HDC hDC = GetDC(m_hTab);
			RECT rect;
			GetClientRect(m_hTab, &rect);
			FillRect(hDC, &rect, tape.hB_black);

			if (std::chrono::system_clock::now() - m_timeOfLastDarkMenuCall > std::chrono::milliseconds{ 1 })
			{
				KillTimer(hWnd, 2);
				for (int i = 0; i < 9; i++)
				{
					rect.left = (53 * i) - 3;
					if (i == 0)
						rect.left += 2;
					rect.right = (53 * (i + 1)) - 3;

					TC_ITEM tc_item;
					tc_item.mask = TCIF_TEXT;
					WCHAR buff[MAX_PATH - 1];
					tc_item.pszText = buff;
					tc_item.cchTextMax = MAX_PATH - 1;
					if (!TabCtrl_GetItem(m_hTab, i, &tc_item))
						return FALSE;

					SetBkMode(hDC, TRANSPARENT);
					if (m_Tab == i)
						SetTextColor(hDC, tape.ink_LIST_header1_DARK);
					else
						SetTextColor(hDC, tape.ink_LIST_header2_DARK);

					WCHAR wszBuffer[MAX_PATH];
					int nCharCount = 0;
					if (m_Tab == i)
						nCharCount = _snwprintf_s(wszBuffer, sizeof(wszBuffer), L"> %s <", buff);
					else
						nCharCount = _snwprintf_s(wszBuffer, sizeof(wszBuffer), L"%s", buff);
					if (nCharCount > 0)
					{
						int nCharacters;
						for (nCharacters = 0;
							nCharacters < nCharCount; nCharacters++)
							if (wszBuffer[nCharacters] == L'\t' ||
								wszBuffer[nCharacters] == L'\b')
								break;
						SelectObject(hDC, tape.hTab2);
						DrawTextW(hDC, wszBuffer, nCharacters, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}

				::ReleaseDC(m_hTab, hDC);
			}
		}
		return FALSE;
	}
	case WM_RBUTTONDOWN:
	{
		if (m_isClonedList)
			PostMessage(tape.Ds2hWnd, WM_TRANSPARENCY, 0, 1);
		break;
	}
	case WM_LBUTTONUP:
	{
		if (m_flag_drag && GetCapture() == hWnd)
		{
			if (m_isClonedList)
				EndDrag(LOWORD(lParam), HIWORD(lParam) - 35);
			else
				EndDrag(LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (m_flag_drag && GetCapture() == hWnd)
		{
			if (m_isClonedList)
				DragMove(LOWORD(lParam), HIWORD(lParam) - 35);
			else
				DragMove(LOWORD(lParam), HIWORD(lParam));
		}
		break;
	}
	case WM_SIZE:
	{
		if (m_isClonedList)
			redrawListReminder();
		break;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_MAPPING_TAB:
		{
			switch (((NMHDR*)lParam)->code)
			{
			case NM_RCLICK:
			{
				TCHITTESTINFO tabinfo;
				POINT pt;
				GetCursorPos(&pt);
				POINT ptt = pt;
				ScreenToClient(m_hTab, &ptt);
				tabinfo.pt = ptt;
				int tab = TabCtrl_HitTest(m_hTab, &tabinfo);
				if (tab == -1)
					break;
				else
					tabrightclick = tab;
				if (tabrightclick)
					TrackPopupMenu((HMENU)GetSubMenu(hMenu_Tabs_2, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
				else
					TrackPopupMenu((HMENU)GetSubMenu(hMenu_Tabs, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
				break;
			}
			case TCN_SELCHANGE:
			{
				if (TabCtrl_GetCurSel(m_hTab) != -1)
					SetTab(TabCtrl_GetCurSel(m_hTab));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_LIST:
		{
			switch (((LPNMHDR)lParam)->code)
			{
			case LVN_COLUMNCLICK:
			{
				m_active = false;
				mDDlg.Hide();

				LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
				unsigned char column = pnmv->iSubItem;

				Mappings newmaptmp;
				Mappings newmapbis;
				size_t length = tape.Mappingdata.size();
				for (size_t i = 0; i < length; i++)
					if (tape.Mappingdata[i].Tab == m_Tab)
						newmapbis.push_back((Mapping)tape.Mappingdata[i]);
					else
						newmaptmp.push_back((Mapping)tape.Mappingdata[i]);

				length = newmapbis.size();
				for (size_t i = 0; i < length; i++)
				{
					if (newmapbis[i].Enable == 2)
					{
						newmaptmp.push_back((Mapping)newmapbis[i]);
						newmapbis.erase(newmapbis.begin() + i);
					}
				}

				while (newmapbis.size())
				{
					int pos = -1;

					unsigned long long valuefirst = 0;
					unsigned long long valuesecond = 0;
					std::bitset<128> first = 0xFFFFFFFFFFFFFFFF;
					std::bitset<128> second = 0xFFFFFFFFFFFFFFFF;
					first <<= 64;

					length = newmapbis.size();
					for (size_t i = 0; i < length; i++)
					{
						std::bitset<128> sortresult = 0;

						std::vector<unsigned short> vjdata;
						for (int j = 0; j < 8; j++)
						{
							if (newmapbis[i].destID[j])
							{
								short vjvalue = newmapbis[i].destID[j];
								vjvalue |= (newmapbis[i].ActionType[j] << 8);
								vjdata.push_back(vjvalue);
							}
						}
						length = 8 - vjdata.size();
						for (int j = 0; j < length; j++)
							vjdata.push_back(0);

						switch (column)
						{
						case 0:
						{
							sortresult |= ((std::bitset<128>)newmapbis[i].srceID[0] << 0);
							sortresult |= ((std::bitset<128>)newmapbis[i].Target[0] << 16);
							sortresult |= ((std::bitset<128>)(newmapbis[i].Enable == 1) << 18);
						}
						break;
						case 1:
						{
							sortresult |= ((std::bitset<128>)newmapbis[i].srceID[1] << 0);
							sortresult |= ((std::bitset<128>)newmapbis[i].Target[1] << 16);
							sortresult |= ((std::bitset<128>)newmapbis[i].OrXorNot[0] << 18);
							sortresult |= ((std::bitset<128>)(newmapbis[i].Enable == 1) << 20);
						}
						break;
						case 2:
						{
							sortresult |= ((std::bitset<128>)newmapbis[i].srceID[2] << 0);
							sortresult |= ((std::bitset<128>)newmapbis[i].Target[2] << 16);
							sortresult |= ((std::bitset<128>)newmapbis[i].OrXorNot[1] << 18);
							sortresult |= ((std::bitset<128>)(newmapbis[i].Enable == 1) << 20);
						}
						break;
						case 3:
						{
							sortresult |= ((std::bitset<128>)newmapbis[i].OrXorNot[2] << 0);
							sortresult |= ((std::bitset<128>)newmapbis[i].srceID[3] << 2);
							sortresult |= ((std::bitset<128>)newmapbis[i].Target[3] << 18);
							sortresult |= ((std::bitset<128>)(newmapbis[i].OrXorNot[2] >= 1) << 20);
							sortresult |= ((std::bitset<128>)(newmapbis[i].Enable == 1) << 21);
						}
						break;
						case 4:
						{
							sortresult |= ((std::bitset<128>)newmapbis[i].OrXorNot[3] << 0);
							sortresult |= ((std::bitset<128>)newmapbis[i].srceID[4] << 2);
							sortresult |= ((std::bitset<128>)newmapbis[i].Target[4] << 18);
							sortresult |= ((std::bitset<128>)(newmapbis[i].OrXorNot[3] >= 1) << 20);
							sortresult |= ((std::bitset<128>)(newmapbis[i].Enable == 1) << 21);
						}
						break;
						case 5:
						{
							sortresult |= ((std::bitset<128>)vjdata[7] << 0);
							sortresult |= ((std::bitset<128>)vjdata[6] << 9);
							sortresult |= ((std::bitset<128>)vjdata[5] << 18);
							sortresult |= ((std::bitset<128>)vjdata[4] << 27);
							sortresult |= ((std::bitset<128>)vjdata[3] << 36);
							sortresult |= ((std::bitset<128>)vjdata[2] << 45);
							sortresult |= ((std::bitset<128>)vjdata[1] << 54);
							sortresult |= ((std::bitset<128>)vjdata[0] << 63);
							sortresult |= ((std::bitset<128>)(newmapbis[i].Enable == 1) << 72);
						}
						break;
						case 6:
						{
							sortresult |= ((std::bitset<128>)newmapbis[i].Toggle << 0);
							sortresult |= ((std::bitset<128>)newmapbis[i].Transitivity << 2);
							sortresult |= ((std::bitset<128>)newmapbis[i].Pause << 4);
							sortresult |= ((std::bitset<128>)newmapbis[i].Macro << 6);
							sortresult |= ((std::bitset<128>)newmapbis[i].Long << 8);
							sortresult |= ((std::bitset<128>)newmapbis[i].Double << 9);
							sortresult |= ((std::bitset<128>)newmapbis[i].Short << 10);
							sortresult |= ((std::bitset<128>)newmapbis[i].Force << 11);
							sortresult |= ((std::bitset<128>)newmapbis[i].Ifmouse << 13);
							sortresult |= ((std::bitset<128>)(newmapbis[i].Enable == 1) << 15);
						}
						break;
						}

						unsigned long long sortresultfirst = ((sortresult & first) >> 64).to_ullong();
						unsigned long long sortresultsecond = (sortresult & second).to_ullong();
						if (pos == -1 || (pos >= 0 && ((sortresultfirst < valuefirst) || ((sortresultfirst == valuefirst) && (sortresultsecond < valuesecond)))))
						{
							pos = (int)i;
							valuefirst = sortresultfirst;
							valuesecond = sortresultsecond;
						}
					}
					newmaptmp.push_back((Mapping)newmapbis[pos]);
					newmapbis.erase(newmapbis.begin() + pos);
				}

				Mappings newmap;
				length = newmaptmp.size();
				for (int j = 0; j < 9; j++)
					for (int i = 0; i < length; i++)
						if (newmaptmp[i].Tab == j)
							newmap.push_back((Mapping)newmaptmp[i]);

				tape.Mappingdata.swap(newmap);
				tape.Save(tape.Setting_Mappingdata);

				PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM(0, m_Tab));

				m_active = true;
				break;
			}
			case NM_DBLCLK:
			{
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(m_hList, &pt);
				//if (pt.x < 45)
				//	stateMappingDlg();
				//else
					editMappingDlg();
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
						Mapping* m = (Mapping*)((LPNMLISTVIEW)lParam)->lParam;
						if (m != 0)
							if (m->Enable != 2)
							{
								m->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
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
		if (m_isClonedList)
		{
			switch (LOWORD(wParam))
			{
			case IDC_CLONE_MENU:
			{
				switch (HIWORD(wParam))
				{
				case STN_CLICKED:
				{
					GetCursorPos(&tape.mousepoint);
					TrackPopupMenu((HMENU)GetSubMenu(m_hMenu2, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, tape.mousepoint.x, tape.mousepoint.y, NULL, m_hDlg, NULL);
					return FALSE;
				}
				}
				break;
			}
			case IDC_CLONE_STAT1:
			{
				switch (HIWORD(wParam))
				{
				case STN_CLICKED:
				{
					tape.Stat[0] = 0;
					return FALSE;
				}
				}
				break;
			}
			case IDC_CLONE_STAT2:
			{
				switch (HIWORD(wParam))
				{
				case STN_CLICKED:
				{
					tape.Stat[1] = 0;
					return FALSE;
				}
				}
				break;
			}
			case IDC_CLONE_STAT3:
			{
				switch (HIWORD(wParam))
				{
				case STN_CLICKED:
				{
					tape.Stat[2] = 0;
					return FALSE;
				}
				}
				break;
			}
			case IDC_CLONE_STAT4:
			{
				switch (HIWORD(wParam))
				{
				case STN_CLICKED:
				{
					tape.Stat[3] = 0;
					return FALSE;
				}
				}
				break;
			}
			case IDC_CLONE_STAT5:
			{
				switch (HIWORD(wParam))
				{
				case STN_CLICKED:
				{
					tape.Stat[4] = 0;
					return FALSE;
				}
				}
				break;
			}
			case IDC_CLONE_STAT6:
			{
				switch (HIWORD(wParam))
				{
				case STN_CLICKED:
				{
					tape.Stat[5] = 0;
					return FALSE;
				}
				}
				break;
			}
			case IDC_CLONE_STAT7:
			{
				switch (HIWORD(wParam))
				{
				case STN_CLICKED:
				{
					tape.Stat[6] = 0;
					return FALSE;
				}
				}
				break;
			}
			case IDC_CLONE_STAT8:
			{
				switch (HIWORD(wParam))
				{
				case STN_CLICKED:
				{
					tape.Stat[7] = 0;
					return FALSE;
				}
				}
				break;
			}
			case IDC_CLONE_CANCEL:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					m_isCloned = false;
					Hide();
				}
				}
				break;
			}
			case IDM_CLONE_TO_MODE_0: { SetTab(0); return FALSE; }
			case IDM_CLONE_TO_MODE_1: { SetTab(1); return FALSE; }
			case IDM_CLONE_TO_MODE_2: { SetTab(2); return FALSE; }
			case IDM_CLONE_TO_MODE_3: { SetTab(3); return FALSE; }
			case IDM_CLONE_TO_MODE_4: { SetTab(4); return FALSE; }
			case IDM_CLONE_TO_MODE_5: { SetTab(5); return FALSE; }
			case IDM_CLONE_TO_MODE_6: { SetTab(6); return FALSE; }
			case IDM_CLONE_TO_MODE_7: { SetTab(7); return FALSE; }
			case IDM_CLONE_TO_MODE_8: { SetTab(8); return FALSE; }
			case IDC_CLONE_CLEAR:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					for (int i = 0; i < 32; i++)
					{
						tape.Reminder[i] = 0;
						m_Randcolor[i] = rand() % 4;
					}
					tape.Save(tape.Setting_Reminder);
					InvalidateRect(hWnd, NULL, TRUE);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_1:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[0] = !tape.Reminder[0];
					CheckDlgButton(hWnd, IDC_POST_ITS_1, WPARAM(tape.Reminder[0]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_2:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[1] = !tape.Reminder[1];
					CheckDlgButton(hWnd, IDC_POST_ITS_2, WPARAM(tape.Reminder[1]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_3:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[2] = !tape.Reminder[2];
					CheckDlgButton(hWnd, IDC_POST_ITS_3, WPARAM(tape.Reminder[2]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_4:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[3] = !tape.Reminder[3];
					CheckDlgButton(hWnd, IDC_POST_ITS_4, WPARAM(tape.Reminder[3]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_5:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[4] = !tape.Reminder[4];
					CheckDlgButton(hWnd, IDC_POST_ITS_5, WPARAM(tape.Reminder[4]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_6:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[5] = !tape.Reminder[5];
					CheckDlgButton(hWnd, IDC_POST_ITS_6, WPARAM(tape.Reminder[5]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_7:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[6] = !tape.Reminder[6];
					CheckDlgButton(hWnd, IDC_POST_ITS_7, WPARAM(tape.Reminder[6]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_8:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[7] = !tape.Reminder[7];
					CheckDlgButton(hWnd, IDC_POST_ITS_8, WPARAM(tape.Reminder[7]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_9:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[8] = !tape.Reminder[8];
					CheckDlgButton(hWnd, IDC_POST_ITS_9, WPARAM(tape.Reminder[8]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_10:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[9] = !tape.Reminder[9];
					CheckDlgButton(hWnd, IDC_POST_ITS_10, WPARAM(tape.Reminder[9]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_11:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[10] = !tape.Reminder[10];
					CheckDlgButton(hWnd, IDC_POST_ITS_11, WPARAM(tape.Reminder[10]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_12:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[11] = !tape.Reminder[11];
					CheckDlgButton(hWnd, IDC_POST_ITS_12, WPARAM(tape.Reminder[11]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_13:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[12] = !tape.Reminder[12];
					CheckDlgButton(hWnd, IDC_POST_ITS_13, WPARAM(tape.Reminder[12]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_14:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[13] = !tape.Reminder[13];
					CheckDlgButton(hWnd, IDC_POST_ITS_14, WPARAM(tape.Reminder[13]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_15:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[14] = !tape.Reminder[14];
					CheckDlgButton(hWnd, IDC_POST_ITS_15, WPARAM(tape.Reminder[14]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_16:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[15] = !tape.Reminder[15];
					CheckDlgButton(hWnd, IDC_POST_ITS_16, WPARAM(tape.Reminder[15]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_17:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[16] = !tape.Reminder[16];
					CheckDlgButton(hWnd, IDC_POST_ITS_17, WPARAM(tape.Reminder[16]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_18:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[17] = !tape.Reminder[17];
					CheckDlgButton(hWnd, IDC_POST_ITS_18, WPARAM(tape.Reminder[17]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_19:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[18] = !tape.Reminder[18];
					CheckDlgButton(hWnd, IDC_POST_ITS_19, WPARAM(tape.Reminder[18]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_20:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[19] = !tape.Reminder[19];
					CheckDlgButton(hWnd, IDC_POST_ITS_20, WPARAM(tape.Reminder[19]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_21:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[20] = !tape.Reminder[20];
					CheckDlgButton(hWnd, IDC_POST_ITS_21, WPARAM(tape.Reminder[20]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_22:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[21] = !tape.Reminder[21];
					CheckDlgButton(hWnd, IDC_POST_ITS_22, WPARAM(tape.Reminder[21]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_23:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[22] = !tape.Reminder[22];
					CheckDlgButton(hWnd, IDC_POST_ITS_23, WPARAM(tape.Reminder[22]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_24:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[23] = !tape.Reminder[23];
					CheckDlgButton(hWnd, IDC_POST_ITS_24, WPARAM(tape.Reminder[23]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_25:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[24] = !tape.Reminder[24];
					CheckDlgButton(hWnd, IDC_POST_ITS_25, WPARAM(tape.Reminder[24]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_26:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[25] = !tape.Reminder[25];
					CheckDlgButton(hWnd, IDC_POST_ITS_26, WPARAM(tape.Reminder[25]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_27:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[26] = !tape.Reminder[26];
					CheckDlgButton(hWnd, IDC_POST_ITS_27, WPARAM(tape.Reminder[26]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_28:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[27] = !tape.Reminder[27];
					CheckDlgButton(hWnd, IDC_POST_ITS_28, WPARAM(tape.Reminder[27]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_29:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[28] = !tape.Reminder[28];
					CheckDlgButton(hWnd, IDC_POST_ITS_29, WPARAM(tape.Reminder[28]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_30:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[29] = !tape.Reminder[29];
					CheckDlgButton(hWnd, IDC_POST_ITS_30, WPARAM(tape.Reminder[29]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_31:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[30] = !tape.Reminder[30];
					CheckDlgButton(hWnd, IDC_POST_ITS_31, WPARAM(tape.Reminder[30]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			case IDC_POST_ITS_32:
			{
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
				{
					tape.Reminder[31] = !tape.Reminder[31];
					CheckDlgButton(hWnd, IDC_POST_ITS_32, WPARAM(tape.Reminder[31]));
					tape.Save(tape.Setting_Reminder);
					RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW);
					break;
				}
				}
				break;
			}
			}
		}
		else
		{
			switch (LOWORD(wParam))
			{
			case IDM_MENU_TO_MODE_0: { tape.Mode[tabrightclick] = 0; tape.Save(tape.Setting_TabToMode); redrawTabs(tabrightclick); tape.Save(tape.Setting_TabToMode); break; }
			case IDM_MENU_TO_MODE_1: { tape.Mode[tabrightclick] = 1; tape.Save(tape.Setting_TabToMode); redrawTabs(tabrightclick); tape.Save(tape.Setting_TabToMode); break; }
			case IDM_MENU_TO_MODE_2: { tape.Mode[tabrightclick] = 2; tape.Save(tape.Setting_TabToMode); redrawTabs(tabrightclick); tape.Save(tape.Setting_TabToMode); break; }
			case IDM_MENU_TO_MODE_3: { tape.Mode[tabrightclick] = 3; tape.Save(tape.Setting_TabToMode); redrawTabs(tabrightclick); tape.Save(tape.Setting_TabToMode); break; }
			case IDM_MENU_TO_MODE_4: { tape.Mode[tabrightclick] = 4; tape.Save(tape.Setting_TabToMode); redrawTabs(tabrightclick); tape.Save(tape.Setting_TabToMode); break; }
			case IDM_MENU_TO_MODE_5: { tape.Mode[tabrightclick] = 5; tape.Save(tape.Setting_TabToMode); redrawTabs(tabrightclick); tape.Save(tape.Setting_TabToMode); break; }
			case IDM_MENU_TO_MODE_6: { tape.Mode[tabrightclick] = 6; tape.Save(tape.Setting_TabToMode); redrawTabs(tabrightclick); tape.Save(tape.Setting_TabToMode); break; }
			case IDM_MENU_TO_MODE_7: { tape.Mode[tabrightclick] = 7; tape.Save(tape.Setting_TabToMode); redrawTabs(tabrightclick); tape.Save(tape.Setting_TabToMode); break; }
			case IDM_MENU_TO_MODE_8: { tape.Mode[tabrightclick] = 8; tape.Save(tape.Setting_TabToMode); redrawTabs(tabrightclick); tape.Save(tape.Setting_TabToMode); break; }
			case IDM_MENU_SEE_VIEW2: { PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 4, MAKELPARAM(1, tabrightclick)); break; }
			}
		}
		switch (LOWORD(wParam))
		{
		case IDC_MIND_OK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText(GetDlgItem(m_hDlg2, IDC_MAPPING_MIND_TEXT), buf, MAX_PATH);
				if (lstrcmpW(NoticeDlg, buf) != 0)
				{
					wcscpy_s(NoticeDlg, wcslen(buf) + 1, buf);
					addNoticeDlgBack();
				}
				Hide2();
				break;
			}
			}
			break;
		}
		case IDC_MIND_CANCEL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				Hide2();
				break;
			}
			}
			break;
		}
		case IDM_MENU_DISABLE: { stateMappingDlg(); break; }
		case IDM_MENU_ADD: { addMappingDlg(); break; }
		case IDM_MENU_EDIT: { editMappingDlg(); break; }
		case IDM_MENU_DEL: { deleteMappingDlg(); break; }
		case IDM_MENU_COPY: { duplicateMappingDlg(); break; }
		case IDM_MENU_SEPARATOR: { addSeparator(); break; }
		case IDM_MENU_MOVE_TO_0: { moveMappingDlg(0); break; }
		case IDM_MENU_MOVE_TO_1: { moveMappingDlg(1); break; }
		case IDM_MENU_MOVE_TO_2: { moveMappingDlg(2); break; }
		case IDM_MENU_MOVE_TO_3: { moveMappingDlg(3); break; }
		case IDM_MENU_MOVE_TO_4: { moveMappingDlg(4); break; }
		case IDM_MENU_MOVE_TO_5: { moveMappingDlg(5); break; }
		case IDM_MENU_MOVE_TO_6: { moveMappingDlg(6); break; }
		case IDM_MENU_MOVE_TO_7: { moveMappingDlg(7); break; }
		case IDM_MENU_MOVE_TO_8: { moveMappingDlg(8); break; }
		case IDM_MENU_SWAP_VIEW:
		{
			if (m_isClonedList)
			{
				tape.CloneViewMode = !tape.CloneViewMode;
				tape.Save(tape.Setting_CloneViewMode);
			}
			else
			{
				tape.MappingViewMode = !tape.MappingViewMode;
				tape.Save(tape.Setting_MappingViewMode);
			}
			load();
			break;
		}
		case IDM_MENU_ADD_NOTICE: { addNoticeDlg(); break; }
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

void MappingDlg::save()
{
	m_active = false;
	mDDlg.Hide();
	Hide2();

	Mappings newtmp;
	size_t length = tape.Mappingdata.size();
	for (int i = 0; i < length; i++)
		if (tape.Mappingdata[i].Tab != m_Tab)
			newtmp.push_back((Mapping)tape.Mappingdata[i]);

	int lastitemindex = ListView_GetItemCount(m_hList);
	for (int i = 0; i < lastitemindex; i++)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		item.iItem = i;
		if (!ListView_GetItem(m_hList, &item))
		{
			PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, mDDlg.m_mode, MAKELPARAM(0, m_Tab));
			RECT win;
			GetWindowRect(tape.Ds2hWnd, &win);
			MessageBoxPos(tape.Ds2hWnd, I18N.MBOX_ErrorWhileSaving, I18N.MBOX_ErrTitle, MB_ICONERROR, win.left + 275, win.top + 30);
			return;
		}
		if (item.lParam != NULL)
			newtmp.push_back(*(Mapping*)item.lParam);
	}

	Mappings newmap;
	length = newtmp.size();
	for (int j = 0; j < 9; j++)
		for (int i = 0; i < length; i++)
			if (newtmp[i].Tab == j)
				newmap.push_back((Mapping)newtmp[i]);

	tape.Mappingdata.swap(newmap);
	tape.Save(tape.Setting_Mappingdata);

	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, NULL, MAKELPARAM(0, NULL));
	m_active = true;
}

void MappingDlg::addMappingDlg()
{
	m_active = false;
	mDDlg.Hide();
	Hide2();

	if (ListView_GetSelectedCount(m_hList) == 1)
		lastidx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
	else
		lastidx = ListView_GetItemCount(m_hList);

	Mapping m;
	mDDlg.mappingData = m;
	mDDlg.m_isClonedList = m_isClonedList;
	mDDlg.Open(m_hDlg, 1, m_Tab);

	m_active = true;
}

void MappingDlg::addMappingDlgBack()
{
	m_active = false;
	Hide2();

	Mapping* data = new Mapping(mDDlg.mappingData);
	data->Tab = m_Tab;
	insertMapping(lastidx, data);
	lastidx++;
	save();

	m_active = true;
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
}

void MappingDlg::addSeparator()
{
	m_active = false;
	mDDlg.Hide();
	Hide2();

	int idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
	if (idx == -1)
		idx = ListView_GetItemCount(m_hList);

	Mapping m;
	mDDlg.mappingData = m;
	Mapping* data = new Mapping(mDDlg.mappingData);
	data->Tab = m_Tab;
	data->Enable = 2;

	insertMapping(idx, data);
	save();

	m_active = true;
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
}

void MappingDlg::editMappingDlg()
{
	m_active = false;
	mDDlg.Hide();
	Hide2();
	
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
			Mapping* data = (Mapping*)item.lParam;
			if (data->Enable != 2)
			{
				mDDlg.mappingData = *data;
				mDDlg.m_isClonedList = m_isClonedList;
				mDDlg.Open(m_hDlg, 2, m_Tab);
			}
		}
	}
	else if (nselected > 1)
	{
		lastidxs.clear();
		for (int i = 0; i < MappingDataDlg::ModifiedMapping_Count; i++)
			mDDlg.Modified[i] = false;
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
				Mapping* data = (Mapping*)item.lParam;
				if (data->Enable != 2)
					lastidxs.push_back(idx);
			}
		}

		for (int i = 0; i < lastidxs.size(); i++)
			ListView_SetItemState(m_hList, lastidxs[i], LVIS_SELECTED, LVIS_SELECTED);

		Mapping m;
		mDDlg.mappingData = m;
		mDDlg.m_isClonedList = m_isClonedList;
		mDDlg.Open(m_hDlg, 3, m_Tab);
	}

	m_active = true;
}

void MappingDlg::editMappingDlgBack()
{
	m_active = false;
	Hide2();

	LV_ITEM item = { 0 };
	item.mask = LVIF_PARAM;
	item.iItem = lastidx;
	item.iSubItem = 0;
	ListView_GetItem(m_hList, &item);
	if (item.lParam != NULL)
	{
		Mapping* data = (Mapping*)item.lParam;
		*data = mDDlg.mappingData;
		ListView_DeleteItem(m_hList, lastidx);
		insertMapping(lastidx, data);
		save();
	}

	m_active = true;
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
}

void MappingDlg::editMappingDlgBackMulti()
{
	m_active = false;
	Hide2();

	Mapping* data1 = new Mapping(mDDlg.mappingData);

	for (int i = 0; i < lastidxs.size(); i++)
	{
		LV_ITEM item = { 0 };
		item.mask = LVIF_PARAM;
		item.iItem = lastidxs[i];
		item.iSubItem = 0;
		ListView_GetItem(m_hList, &item);
		if (item.lParam != NULL)
		{
			Mapping m;
			Mapping* data2 = (Mapping*)item.lParam;
			m = *data2;
			data2 = new Mapping(m);
			for (int i = 0; i < MappingDataDlg::ModifiedMapping_Count; i++)
				if (mDDlg.Modified[i])
					switch (i)
					{
					case MappingDataDlg::Mofified_Ifmouse: { data2->Ifmouse = data1->Ifmouse; break; }
					case MappingDataDlg::Mofified_Force: { data2->Force = data1->Force; break; }
					case MappingDataDlg::Mofified_Short: { data2->Short = data1->Short; break; }
					case MappingDataDlg::Mofified_Double: { data2->Double = data1->Double; break; }
					case MappingDataDlg::Mofified_Long: { data2->Long = data1->Long; break; }
					case MappingDataDlg::Mofified_Led: { data2->Led = data1->Led; break; }
					case MappingDataDlg::Mofified_Macro: { data2->Macro = data1->Macro; break; }
					case MappingDataDlg::Mofified_Pause: { data2->Pause = data1->Pause; break; }
					case MappingDataDlg::Mofified_Transitivity: { data2->Transitivity = data1->Transitivity; break; }
					case MappingDataDlg::Mofified_Target1: { data2->Target[0] = data1->Target[0]; break; }
					case MappingDataDlg::Mofified_Target2: { data2->Target[1] = data1->Target[1]; break; }
					case MappingDataDlg::Mofified_Target3: { data2->Target[2] = data1->Target[2]; break; }
					case MappingDataDlg::Mofified_Target4: { data2->Target[3] = data1->Target[3]; break; }
					case MappingDataDlg::Mofified_Target5: { data2->Target[4] = data1->Target[4]; break; }
					case MappingDataDlg::Mofified_Toggle: { data2->Toggle = data1->Toggle; break; }
					case MappingDataDlg::Mofified_dsID1: { data2->srceID[0] = data1->srceID[0]; break; }
					case MappingDataDlg::Mofified_dsID2: { data2->srceID[1] = data1->srceID[1]; break; }
					case MappingDataDlg::Mofified_dsID3: { data2->srceID[2] = data1->srceID[2]; break; }
					case MappingDataDlg::Mofified_dsID4: { data2->srceID[3] = data1->srceID[3]; break; }
					case MappingDataDlg::Mofified_dsID5: { data2->srceID[4] = data1->srceID[4]; break; }
					case MappingDataDlg::Mofified_OrXorNot1: { data2->OrXorNot[0] = data1->OrXorNot[0]; break; }
					case MappingDataDlg::Mofified_OrXorNot2: { data2->OrXorNot[1] = data1->OrXorNot[1]; break; }
					case MappingDataDlg::Mofified_OrXorNot3: { data2->OrXorNot[2] = data1->OrXorNot[2]; break; }
					case MappingDataDlg::Mofified_OrXorNot4: { data2->OrXorNot[3] = data1->OrXorNot[3]; break; }
					case MappingDataDlg::Mofified_dsDisable1: { data2->srceDisable[0] = data1->srceDisable[0]; break; }
					case MappingDataDlg::Mofified_dsDisable2: { data2->srceDisable[1] = data1->srceDisable[1]; break; }
					case MappingDataDlg::Mofified_dsDisable3: { data2->srceDisable[2] = data1->srceDisable[2]; break; }
					case MappingDataDlg::Mofified_dsDisable4: { data2->srceDisable[3] = data1->srceDisable[3]; break; }
					case MappingDataDlg::Mofified_dsDisable5: { data2->srceDisable[4] = data1->srceDisable[4]; break; }
					case MappingDataDlg::Mofified_ActionType1: { data2->ActionType[0] = data1->ActionType[0]; break; }
					case MappingDataDlg::Mofified_ActionType2: { data2->ActionType[1] = data1->ActionType[1]; break; }
					case MappingDataDlg::Mofified_ActionType3: { data2->ActionType[2] = data1->ActionType[2]; break; }
					case MappingDataDlg::Mofified_ActionType4: { data2->ActionType[3] = data1->ActionType[3]; break; }
					case MappingDataDlg::Mofified_ActionType5: { data2->ActionType[4] = data1->ActionType[4]; break; }
					case MappingDataDlg::Mofified_ActionType6: { data2->ActionType[5] = data1->ActionType[5]; break; }
					case MappingDataDlg::Mofified_ActionType7: { data2->ActionType[6] = data1->ActionType[6]; break; }
					case MappingDataDlg::Mofified_ActionType8: { data2->ActionType[7] = data1->ActionType[7]; break; }
					case MappingDataDlg::Mofified_vjID1: { data2->destID[0] = data1->destID[0]; break; }
					case MappingDataDlg::Mofified_vjID2: { data2->destID[1] = data1->destID[1]; break; }
					case MappingDataDlg::Mofified_vjID3: { data2->destID[2] = data1->destID[2]; break; }
					case MappingDataDlg::Mofified_vjID4: { data2->destID[3] = data1->destID[3]; break; }
					case MappingDataDlg::Mofified_vjID5: { data2->destID[4] = data1->destID[4]; break; }
					case MappingDataDlg::Mofified_vjID6: { data2->destID[5] = data1->destID[5]; break; }
					case MappingDataDlg::Mofified_vjID7: { data2->destID[6] = data1->destID[6]; break; }
					case MappingDataDlg::Mofified_vjID8: { data2->destID[7] = data1->destID[7]; break; }
					case MappingDataDlg::Mofified_Overcontrol1: { data2->Overcontrol[0] = data1->Overcontrol[0]; break; }
					case MappingDataDlg::Mofified_Overcontrol2: { data2->Overcontrol[1] = data1->Overcontrol[1]; break; }
					case MappingDataDlg::Mofified_Overcontrol3: { data2->Overcontrol[2] = data1->Overcontrol[2]; break; }
					case MappingDataDlg::Mofified_Overcontrol4: { data2->Overcontrol[3] = data1->Overcontrol[3]; break; }
					case MappingDataDlg::Mofified_Overcontrol5: { data2->Overcontrol[4] = data1->Overcontrol[4]; break; }
					case MappingDataDlg::Mofified_Overcontrol6: { data2->Overcontrol[5] = data1->Overcontrol[5]; break; }
					case MappingDataDlg::Mofified_Overcontrol7: { data2->Overcontrol[6] = data1->Overcontrol[6]; break; }
					case MappingDataDlg::Mofified_Overcontrol8: { data2->Overcontrol[7] = data1->Overcontrol[7]; break; }
					case MappingDataDlg::Mofified_Switch1: { data2->Switch[0] = data1->Switch[0]; break; }
					case MappingDataDlg::Mofified_Switch2: { data2->Switch[1] = data1->Switch[1]; break; }
					case MappingDataDlg::Mofified_Switch3: { data2->Switch[2] = data1->Switch[2]; break; }
					case MappingDataDlg::Mofified_Switch4: { data2->Switch[3] = data1->Switch[3]; break; }
					case MappingDataDlg::Mofified_Switch5: { data2->Switch[4] = data1->Switch[4]; break; }
					case MappingDataDlg::Mofified_Switch6: { data2->Switch[5] = data1->Switch[5]; break; }
					case MappingDataDlg::Mofified_Switch7: { data2->Switch[6] = data1->Switch[6]; break; }
					case MappingDataDlg::Mofified_Switch8: { data2->Switch[7] = data1->Switch[7]; break; }
					case MappingDataDlg::Mofified_OnRelease1: { data2->OnRelease[0] = data1->OnRelease[0]; break; }
					case MappingDataDlg::Mofified_OnRelease2: { data2->OnRelease[1] = data1->OnRelease[1]; break; }
					case MappingDataDlg::Mofified_OnRelease3: { data2->OnRelease[2] = data1->OnRelease[2]; break; }
					case MappingDataDlg::Mofified_OnRelease4: { data2->OnRelease[3] = data1->OnRelease[3]; break; }
					case MappingDataDlg::Mofified_OnRelease5: { data2->OnRelease[4] = data1->OnRelease[4]; break; }
					case MappingDataDlg::Mofified_OnRelease6: { data2->OnRelease[5] = data1->OnRelease[5]; break; }
					case MappingDataDlg::Mofified_OnRelease7: { data2->OnRelease[6] = data1->OnRelease[6]; break; }
					case MappingDataDlg::Mofified_OnRelease8: { data2->OnRelease[7] = data1->OnRelease[7]; break; }
					case MappingDataDlg::Mofified_NoRelease1: { data2->NoRelease[0] = data1->NoRelease[0]; break; }
					case MappingDataDlg::Mofified_NoRelease2: { data2->NoRelease[1] = data1->NoRelease[1]; break; }
					case MappingDataDlg::Mofified_NoRelease3: { data2->NoRelease[2] = data1->NoRelease[2]; break; }
					case MappingDataDlg::Mofified_NoRelease4: { data2->NoRelease[3] = data1->NoRelease[3]; break; }
					case MappingDataDlg::Mofified_NoRelease5: { data2->NoRelease[4] = data1->NoRelease[4]; break; }
					case MappingDataDlg::Mofified_NoRelease6: { data2->NoRelease[5] = data1->NoRelease[5]; break; }
					case MappingDataDlg::Mofified_NoRelease7: { data2->NoRelease[6] = data1->NoRelease[6]; break; }
					case MappingDataDlg::Mofified_NoRelease8: { data2->NoRelease[7] = data1->NoRelease[7]; break; }
					case MappingDataDlg::Mofified_NlRelease1: { data2->NlRelease[0] = data1->NlRelease[0]; break; }
					case MappingDataDlg::Mofified_NlRelease2: { data2->NlRelease[1] = data1->NlRelease[1]; break; }
					case MappingDataDlg::Mofified_NlRelease3: { data2->NlRelease[2] = data1->NlRelease[2]; break; }
					case MappingDataDlg::Mofified_NlRelease4: { data2->NlRelease[3] = data1->NlRelease[3]; break; }
					case MappingDataDlg::Mofified_NlRelease5: { data2->NlRelease[4] = data1->NlRelease[4]; break; }
					case MappingDataDlg::Mofified_NlRelease6: { data2->NlRelease[5] = data1->NlRelease[5]; break; }
					case MappingDataDlg::Mofified_NlRelease7: { data2->NlRelease[6] = data1->NlRelease[6]; break; }
					case MappingDataDlg::Mofified_NlRelease8: { data2->NlRelease[7] = data1->NlRelease[7]; break; }
					case MappingDataDlg::Mofified_vjDisable1: { data2->destDisable[0] = data1->destDisable[0]; break; }
					case MappingDataDlg::Mofified_vjDisable2: { data2->destDisable[1] = data1->destDisable[1]; break; }
					case MappingDataDlg::Mofified_vjDisable3: { data2->destDisable[2] = data1->destDisable[2]; break; }
					case MappingDataDlg::Mofified_vjDisable4: { data2->destDisable[3] = data1->destDisable[3]; break; }
					case MappingDataDlg::Mofified_vjDisable5: { data2->destDisable[4] = data1->destDisable[4]; break; }
					case MappingDataDlg::Mofified_vjDisable6: { data2->destDisable[5] = data1->destDisable[5]; break; }
					case MappingDataDlg::Mofified_vjDisable7: { data2->destDisable[6] = data1->destDisable[6]; break; }
					case MappingDataDlg::Mofified_vjDisable8: { data2->destDisable[7] = data1->destDisable[7]; break; }
					case MappingDataDlg::Mofified_Mouse1: { data2->Mouse[0] = data1->Mouse[0]; break; }
					case MappingDataDlg::Mofified_Mouse2: { data2->Mouse[1] = data1->Mouse[1]; break; }
					case MappingDataDlg::Mofified_Mouse3: { data2->Mouse[2] = data1->Mouse[2]; break; }
					case MappingDataDlg::Mofified_Mouse4: { data2->Mouse[3] = data1->Mouse[3]; break; }
					case MappingDataDlg::Mofified_Mouse5: { data2->Mouse[4] = data1->Mouse[4]; break; }
					case MappingDataDlg::Mofified_Mouse6: { data2->Mouse[5] = data1->Mouse[5]; break; }
					case MappingDataDlg::Mofified_Mouse7: { data2->Mouse[6] = data1->Mouse[6]; break; }
					case MappingDataDlg::Mofified_Grid1: { data2->Grid[0] = data1->Grid[0]; break; }
					case MappingDataDlg::Mofified_Grid2: { data2->Grid[1] = data1->Grid[1]; break; }
					case MappingDataDlg::Mofified_Grid3: { data2->Grid[2] = data1->Grid[2]; break; }
					case MappingDataDlg::Mofified_Grid4: { data2->Grid[3] = data1->Grid[3]; break; }
					case MappingDataDlg::Mofified_Grid5: { data2->Grid[4] = data1->Grid[4]; break; }
					case MappingDataDlg::Mofified_Grid6: { data2->Grid[5] = data1->Grid[5]; break; }
					case MappingDataDlg::Mofified_Start1: { data2->Start[0] = data1->Start[0]; break; }
					case MappingDataDlg::Mofified_Start2: { data2->Start[1] = data1->Start[1]; break; }
					case MappingDataDlg::Mofified_Start3: { data2->Start[2] = data1->Start[2]; break; }
					case MappingDataDlg::Mofified_Start4: { data2->Start[3] = data1->Start[3]; break; }
					case MappingDataDlg::Mofified_Start5: { data2->Start[4] = data1->Start[4]; break; }
					case MappingDataDlg::Mofified_Start6: { data2->Start[5] = data1->Start[5]; break; }
					case MappingDataDlg::Mofified_Start7: { data2->Start[6] = data1->Start[6]; break; }
					case MappingDataDlg::Mofified_Start8: { data2->Start[7] = data1->Start[7]; break; }
					case MappingDataDlg::Mofified_Stop1: { data2->Stop[0] = data1->Stop[0]; break; }
					case MappingDataDlg::Mofified_Stop2: { data2->Stop[1] = data1->Stop[1]; break; }
					case MappingDataDlg::Mofified_Stop3: { data2->Stop[2] = data1->Stop[2]; break; }
					case MappingDataDlg::Mofified_Stop4: { data2->Stop[3] = data1->Stop[3]; break; }
					case MappingDataDlg::Mofified_Stop5: { data2->Stop[4] = data1->Stop[4]; break; }
					case MappingDataDlg::Mofified_Stop6: { data2->Stop[5] = data1->Stop[5]; break; }
					case MappingDataDlg::Mofified_Stop7: { data2->Stop[6] = data1->Stop[6]; break; }
					case MappingDataDlg::Mofified_Stop8: { data2->Stop[7] = data1->Stop[7]; break; }
					}
			ListView_DeleteItem(m_hList, lastidxs[i]);
			insertMapping(lastidxs[i], data2);
		}
	}
	save();

	m_active = true;
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
}

void MappingDlg::stateMappingDlg()
{
	m_active = false;

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
			Mapping* data = (Mapping*)item.lParam;
			if (data->Enable != 2)
				switch (data->Enable)
				{
				case 0:
				{
					data->Enable = 1;
					save();
					break;
				}
				case 1:
				{
					data->Enable = 0;
					save();
					break;
				}
				}
		}
	}
	else if (nselected > 1)
	{
		lastidxs.clear();
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
				Mapping* data = (Mapping*)item.lParam;
				if (data->Enable != 2)
					lastidxs.push_back(idx);
			}
		}
		{
			Mappings newtmp;
			size_t length = tape.Mappingdata.size();
			for (int i = 0; i < length; i++)
				if (tape.Mappingdata[i].Tab != m_Tab)
					newtmp.push_back((Mapping)tape.Mappingdata[i]);

			int lastitemindex = ListView_GetItemCount(m_hList);
			for (int i = 0; i < lastitemindex; i++)
			{
				LV_ITEM item = { 0 };
				item.mask = LVIF_PARAM;
				item.iItem = i;
				if (!ListView_GetItem(m_hList, &item))
				{
					PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, mDDlg.m_mode, MAKELPARAM(0, m_Tab));
					RECT win;
					GetWindowRect(tape.Ds2hWnd, &win);
					MessageBoxPos(tape.Ds2hWnd, I18N.MBOX_ErrorWhileSaving, I18N.MBOX_ErrTitle, MB_ICONERROR, win.left + 275, win.top + 30);
					return;
				}
				if (item.lParam != NULL)
				{
					Mapping* data = (Mapping*)item.lParam;
					if (std::find(lastidxs.begin(), lastidxs.end(), i) != lastidxs.end())
					{
						if (data->Enable != 2)
							switch (data->Enable)
							{
							case 0:
							{
								data->Enable = 1;
								save();
								break;
							}
							case 1:
							{
								data->Enable = 0;
								save();
								break;
							}
							}
					}
					newtmp.push_back(*data);
				}
			}

			Mappings newmap;
			length = newtmp.size();
			for (int j = 0; j < 9; j++)
				for (int i = 0; i < length; i++)
					if (newtmp[i].Tab == j)
						newmap.push_back((Mapping)newtmp[i]);

			tape.Mappingdata.swap(newmap);
			tape.Save(tape.Setting_Mappingdata);

			PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, NULL, MAKELPARAM(0, NULL));
		}
	}

	load();
	m_active = true;
}

void MappingDlg::deleteMappingDlg()
{
	m_active = false;
	mDDlg.Hide();
	Hide2();

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
			delete (Mapping*)item.lParam;
			ListView_DeleteItem(m_hList, idx);
		}
		save();
	}

	m_active = true;
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
}

void MappingDlg::duplicateMappingDlg()
{
	m_active = false;
	mDDlg.Hide();
	Hide2();

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
			Mapping* data = (Mapping*)item.lParam;
			mDDlg.mappingData = *data;
			data = new Mapping(mDDlg.mappingData);
			insertMapping(idx + 1, data);
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
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
}

void MappingDlg::moveMappingDlg(int tab)
{
	m_active = false;
	mDDlg.Hide();
	Hide2();

	if (tab == m_Tab)
		{ m_active = true; return; }

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
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, tab));
}

void MappingDlg::addNoticeDlg()
{
	m_active = false;
	mDDlg.Hide();
	Hide2();

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
			Mapping* data = (Mapping*)item.lParam;
			if (data->Enable != 2)
			{
				mDDlg.mappingData = *data;
				mDDlg.m_isClonedList = m_isClonedList;
				Show2();
				RECT win;
				RECT win2;
				GetWindowRect(tape.Ds2hWnd, &win);
				GetWindowRect(m_hDlg2, &win2);
				MoveWindow2(win.left + 275, win.top + 30, win2.right - win2.left, win2.bottom - win2.top, false);
				wcscpy_s(NoticeDlg, wcslen(mDDlg.mappingData.Notice) + 1, mDDlg.mappingData.Notice);
				SetWindowText(GetDlgItem(m_hDlg2, IDC_MAPPING_MIND_TEXT), mDDlg.mappingData.Notice);
				SetFocus(m_hDlg2);
			}
		}
	}

	m_active = true;
}

void MappingDlg::addNoticeDlgBack()
{
	m_active = false;

	LV_ITEM item = { 0 };
	item.mask = LVIF_PARAM;
	item.iItem = lastidx;
	item.iSubItem = 0;
	ListView_GetItem(m_hList, &item);
	if (item.lParam != NULL)
	{
		Mapping* data = (Mapping*)item.lParam;
		*data = mDDlg.mappingData;
		auto ret = wcscpy_s(data->Notice, wcslen(NoticeDlg) + 1, NoticeDlg);
		if (ret == 0)
		{
			ListView_DeleteItem(m_hList, lastidx);
			insertMapping(lastidx, data);
			save();
		}
		else
			load();
	}

	m_active = true;
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
}

int MappingDlg::insertMapping(int idx, Mapping* m)
{
	m_active = false;

	if (idx < 0)
		{ m_active = true; return FALSE; }

	LVITEM item = { 0 };
	bool enable = m->Enable == 1;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = idx;
	item.iSubItem = 0;
	item.lParam = LPARAM(m);
	item.pszText = m->SrceString(0);
	int ret = ListView_InsertItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 1;
	item.lParam = 0;
	item.pszText = m->SrceString(1);
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 2;
	item.lParam = 0;
	item.pszText = m->SrceString(2);
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 3;
	item.lParam = 0;
	item.pszText = m->SrceString(3);
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 4;
	item.lParam = 0;
	item.pszText = m->SrceString(4);
	ListView_SetItem(m_hList, &item);
	item.mask = LVIF_TEXT;
	item.iSubItem = 5;
	item.lParam = 0;
	if ((m_isClonedList && tape.CloneViewMode) || (!m_isClonedList && tape.MappingViewMode))
	{
		item.pszText = (WCHAR*)(m->NoticeString());
		ListView_SetItem(m_hList, &item);
	}
	else
	{
		item.pszText = (WCHAR*)(m->DestString());
		ListView_SetItem(m_hList, &item);
		item.mask = LVIF_TEXT;
		item.iSubItem = 6;
		item.lParam = 0;
		item.pszText = (WCHAR*)(m->TagsString());
		ListView_SetItem(m_hList, &item);
	}
	
	ListView_SetCheckState(m_hList, idx, enable);

	m_active = true;
	return ret;
}

void MappingDlg::BeginDrag(int idx)
{
	if (ListView_GetNextItem(m_hList, -1, LVNI_SELECTED) == -1)
		return;
	mDDlg.Hide();
	Hide2();
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
		setInsertMark(ht.iItem);
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
	PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 0, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
}

void MappingDlg::setInsertMark(int idx)
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

void MappingDlg::Show()
{
	if (m_isClonedList)
		m_isCloned = true;
	::ShowWindow(m_hDlg, SW_SHOW);
}

void MappingDlg::Show2()
{
	::ShowWindow(m_hDlg2, SW_SHOW);
}

void MappingDlg::Hide()
{
	m_isCloned = false;
	::ShowWindow(m_hDlg2, SW_HIDE);
	::ShowWindow(m_hDlg, SW_HIDE);
}

void MappingDlg::Hide2()
{
	::ShowWindow(m_hDlg2, SW_HIDE);
}

BOOL MappingDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	BOOL ret = ::MoveWindow(m_hDlg, x, y, w, h, r);
	RECT win;
	GetWindowRect(m_hDlg, &win);
	if (m_isClonedList)
		::MoveWindow(m_hList, 2, 36, win.right - win.left - 4, win.bottom - win.top - 60, FALSE);
	else
	{
		::MoveWindow(m_hTab, 0, -1, win.right - win.left + 8, 17, FALSE);
		::MoveWindow(m_hList, 0, 16, win.right - win.left + (GetSystemMetrics(SM_CXVSCROLL) + 2), win.bottom - win.top - 16, FALSE);
	}

	return ret;
}

BOOL MappingDlg::MoveWindow2(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg2, x, y, w, h, r);
}

void MappingDlg::SetTransparency(bool transparencyon)
{
	if (transparencyon)
		SetWindowTransparent(m_hDlg, true, tape.Opacity);
	else
		SetWindowTransparent(m_hDlg, false, NULL);
}
