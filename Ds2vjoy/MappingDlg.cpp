#include "stdafx.h"
#include "MappingDlg.h"
#include "MappingDataDlg.h"
#include "Ds2vJoy.h"
#include "uxtheme.h"
#pragma comment(lib, "UxTheme.lib")

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

	m_TabsID[0] = ID_MENU_ADD;
	m_TabsID[1] = ID_MENU_EDIT;
	m_TabsID[2] = ID_MENU_DEL;
	m_TabsID[3] = ID_MENU_COPY;
	m_TabsID[4] = ID_MENU_SEPARATOR;
	m_TabsID[5] = ID_MENU_MOVE_TO_0;
	m_TabsID[6] = ID_MENU_MOVE_TO_1;
	m_TabsID[7] = ID_MENU_MOVE_TO_2;
	m_TabsID[8] = ID_MENU_MOVE_TO_3;
	m_TabsID[9] = ID_MENU_MOVE_TO_4;
	m_TabsID[10] = ID_MENU_MOVE_TO_5;
	m_TabsID[11] = ID_MENU_MOVE_TO_6;
	m_TabsID[12] = ID_MENU_MOVE_TO_7;
	m_TabsID[13] = ID_MENU_MOVE_TO_8;
	m_hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_EDITING));
	redrawMenu(14);

	m_hList = GetDlgItem(m_hDlg, IDC_MAPPING_LIST);
	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_NOCOLUMNHEADER;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH;
	col.pszText = I18N.dsButton;
	col.cx = 83;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = L"";
	col.cx = 84;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = L"";
	col.cx = 84;
	ListView_InsertColumn(m_hList, 2, &col);
	col.pszText = I18N.vJoyButton;
	col.cx = 120;
	ListView_InsertColumn(m_hList, 3, &col);
	col.pszText = I18N.TagsButton;
	col.cx = 78;
	ListView_InsertColumn(m_hList, 4, &col);

	HWND hTip = ListView_GetToolTips(m_hList);
	SetWindowPos(hTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void MappingDlg::Init2(HINSTANCE hInst, HWND hWnd)
{
	for (int i = 0; i < 32; i++) m_Randcolor[i] = rand() % 4;
	m_Tab = 0;
	m_isClonedList = true;
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_CLONE), hWnd, (DLGPROC)Proc, (LPARAM)this);
	LONG lStyle = GetWindowLong(m_hDlg, GWL_STYLE);
//		lStyle |= WS_THICKFRAME;
	lStyle = lStyle & ~WS_CAPTION;
	SetWindowLong(m_hDlg, GWL_STYLE, lStyle);
	HFONT hFont = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe Print");
	SendDlgItemMessage(m_hDlg, IDC_STATIC, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
	Hide();
	
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

	m_TabsID[0] = ID_MENU_ADD;
	m_TabsID[1] = ID_MENU_EDIT;
	m_TabsID[2] = ID_MENU_DEL;
	m_TabsID[3] = ID_MENU_COPY;
	m_TabsID[4] = ID_MENU_SEPARATOR;
	m_TabsID[5] = ID_MENU_MOVE_TO_0;
	m_TabsID[6] = ID_MENU_MOVE_TO_1;
	m_TabsID[7] = ID_MENU_MOVE_TO_2;
	m_TabsID[8] = ID_MENU_MOVE_TO_3;
	m_TabsID[9] = ID_MENU_MOVE_TO_4;
	m_TabsID[10] = ID_MENU_MOVE_TO_5;
	m_TabsID[11] = ID_MENU_MOVE_TO_6;
	m_TabsID[12] = ID_MENU_MOVE_TO_7;
	m_TabsID[13] = ID_MENU_MOVE_TO_8;
	m_hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_EDITING));
	redrawMenu(14);

	m_TabsID[0] = ID_MENU_TO_MODE_0;
	m_TabsID[1] = ID_MENU_TO_MODE_1;
	m_TabsID[2] = ID_MENU_TO_MODE_2;
	m_TabsID[3] = ID_MENU_TO_MODE_3;
	m_TabsID[4] = ID_MENU_TO_MODE_4;
	m_TabsID[5] = ID_MENU_TO_MODE_5;
	m_TabsID[6] = ID_MENU_TO_MODE_6;
	m_TabsID[7] = ID_MENU_TO_MODE_7;
	m_TabsID[8] = ID_MENU_TO_MODE_8;
	m_hMenu2 = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_CLONE));
	redrawMenu(9, true);

	m_hList = GetDlgItem(m_hDlg, IDC_MAPPING_LIST);
	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_FLATSB;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	HWND header = ListView_GetHeader(m_hList);
	DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
//	dwHeaderStyle |= HDS_HIDDEN | HDS_NOSIZING | HDS_OVERFLOW;
	dwHeaderStyle |= HDS_NOSIZING;
	::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH;
	col.pszText = I18N.dsButton;
	col.cx = 83;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = L"";
	col.cx = 84;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = L"";
	col.cx = 84;
	ListView_InsertColumn(m_hList, 2, &col);
	col.pszText = I18N.vJoyButton;
	col.cx = 120;
	ListView_InsertColumn(m_hList, 3, &col);
	col.pszText = I18N.TagsButton;
	col.cx = 78;
	ListView_InsertColumn(m_hList, 4, &col);

	HWND hTip = ListView_GetToolTips(m_hList);
	SetWindowPos(hTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
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
	ShowWindow(GetDlgItem(m_hDlg, IDC_STATIC_CLONE), SW_HIDE);
	if (m_Tab != tab)
	{
		if (mode >= 0 && mode < 9)
			m_Tab = tab;
		else
			m_Tab = 0;
	}
	load();
	redrawMenu(9, true);
	SetWindowText(GetDlgItem(m_hDlg, IDC_STATIC_CLONE), (I18N.Clone_of_Tab + std::to_wstring(m_Tab)).c_str());
	if (m_isCloned)
		redrawListReminder();
	ShowWindow(GetDlgItem(m_hDlg, IDC_STATIC_CLONE), SW_SHOW);
}

int MappingDlg::GetTab()
{
	return m_Tab;
}

void MappingDlg::redrawMenu(int ntabs, bool menu)
{
	MENUITEMINFO info;
	if (menu)
		for (int i = 0; i < ntabs; i++)
		{
			ZeroMemory(&info, sizeof(info));
			info.cbSize = sizeof(info);
			info.fMask = MIIM_FTYPE | MIIM_STATE;
			GetMenuItemInfo(m_hMenu2, m_TabsID[i], FALSE, &info);
			info.fType = MFT_RADIOCHECK | MFT_OWNERDRAW;
			if (i == m_Tab && m_isClonedList)
				info.fState = MFS_DISABLED | MFS_DEFAULT | MFS_HILITE;
			else
				info.fState = 0;
			SetMenuItemInfo(m_hMenu2, m_TabsID[i], FALSE, &info);
		}
	else
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

void MappingDlg::redrawListReminder()
{
	RECT win;
	GetWindowRect(m_hDlg, &win);
	::MoveWindow(m_hList, 0, 35, win.right - win.left, win.bottom - win.top - 59, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_CLEAR), 6, win.bottom - win.top - 19, 46, 11, FALSE);
	::MoveWindow(GetDlgItem(m_hDlg, IDC_STATIC), 6, win.bottom - win.top - 19, 74, 11, FALSE);
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
	case WM_INITDIALOG:
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_1), L"1");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_2), L"2");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_3), L"3");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_4), L"4");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_5), L"5");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_6), L"6");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_7), L"7");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_8), L"8");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_9), L"9");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_10), L"10");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_11), L"11");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_12), L"12");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_13), L"13");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_14), L"14");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_15), L"15");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_16), L"16");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_17), L"17");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_18), L"18");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_19), L"19");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_20), L"20");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_21), L"21");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_22), L"22");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_23), L"23");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_24), L"24");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_25), L"25");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_26), L"26");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_27), L"27");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_28), L"28");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_29), L"29");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_30), L"30");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_31), L"31");
		CreateToolTip(hWnd, GetDlgItem(hWnd, IDC_POST_ITS_32), L"32");
		break;
	case WM_SHOWWINDOW:
	{
		SendMessage(m_hList, LVM_SETBKCOLOR, 0, (LPARAM)RGB(210, 210, 215));
		SendMessage(m_hList, LVM_SETTEXTCOLOR, 0, (LPARAM)RGB(10, 10, 10));
		SendMessage(m_hList, LVM_SETTEXTBKCOLOR, 0, (LPARAM)RGB(225, 225, 230));

		if (m_isClonedList)
		{
			HFONT hFont = CreateFont(16, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"MS Shell Dlg");
			SendDlgItemMessage(hWnd, IDCANCEL, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

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

		if (wParam == TRUE)
			load();
		m_active = true;
		break;
	}
	case WM_SIZE:
		if (m_isClonedList)
			redrawListReminder();
		else
			::MoveWindow(m_hList, 0, 0, LOWORD(lParam), HIWORD(lParam), FALSE);
		break;
	case WM_MEASUREITEM:
	{
		LPMEASUREITEMSTRUCT DrawMenuSize = (LPMEASUREITEMSTRUCT)lParam;
		if (DrawMenuSize->CtlType == ODT_MENU)
		{
			int nEdgeWidth = ::GetSystemMetrics(SM_CYEDGE);
			DrawMenuSize->itemWidth = ::GetSystemMetrics(SM_CXMENUCHECK) + nEdgeWidth + nEdgeWidth;
//			DrawMenuSize->itemHeight = 13 + nEdgeWidth + nEdgeWidth;
			if (m_isClonedList)
				DrawMenuSize->itemHeight = 10 + nEdgeWidth + nEdgeWidth;
			else
				DrawMenuSize->itemHeight = 12 + nEdgeWidth + nEdgeWidth;

			bool menunumber = false;
			switch (DrawMenuSize->itemID)
			{
			case ID_MENU_TO_MODE_0:
			case ID_MENU_TO_MODE_1:
			case ID_MENU_TO_MODE_2:
			case ID_MENU_TO_MODE_3:
			case ID_MENU_TO_MODE_4:
			case ID_MENU_TO_MODE_5:
			case ID_MENU_TO_MODE_6:
			case ID_MENU_TO_MODE_7:
			case ID_MENU_TO_MODE_8:
				menunumber = true;
				break;
			}

			WCHAR wszBuffer[MAX_PATH];
			int nCharCount = 0;
			if (menunumber)
				nCharCount = ::GetMenuString(m_hMenu2, DrawMenuSize->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
			else
				nCharCount = ::GetMenuString(m_hMenu, DrawMenuSize->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
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

		if (DrawMenuStructure->CtlType == ODT_BUTTON)
		{
		}
		else if (DrawMenuStructure->CtlType == ODT_MENU)
		{
//			BOOL bDisabled = DrawMenuStructure->itemState & ODS_GRAYED;
			BOOL bSelected = DrawMenuStructure->itemState & ODS_SELECTED;
//			BOOL bChecked = DrawMenuStructure->itemState & ODS_CHECKED;

			// Background
			HBRUSH hBrushColor;
			if (m_isClonedList)
				hBrushColor = ::CreateSolidBrush(RGB(200, 200, 205));
			else
				hBrushColor = ::CreateSolidBrush(RGB(205, 205, 210));
			::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), hBrushColor);
/*
			// Delimiter
			COLORREF crCurrPen = 0;
			crCurrPen = ::GetSysColor(COLOR_3DLIGHT);
			int nEdgeWidth = ::GetSystemMetrics(SM_CYEDGE);
			int nImageOffsetX = ::GetSystemMetrics(SM_CXMENUCHECK) + nEdgeWidth + nEdgeWidth;
			HPEN hNewPen = ::CreatePen(PS_SOLID, 1, crCurrPen);
			HGDIOBJ hOldPen = ::SelectObject(DrawMenuStructure->hDC, hNewPen);
			::MoveToEx(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.left + nImageOffsetX + 1, DrawMenuStructure->rcItem.top, NULL);
			::LineTo(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.left + nImageOffsetX + 1, DrawMenuStructure->rcItem.bottom);
			::SelectObject(DrawMenuStructure->hDC, ::GetStockObject(WHITE_PEN));
			::MoveToEx(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.left + nImageOffsetX + 2, DrawMenuStructure->rcItem.top, NULL);
			::LineTo(DrawMenuStructure->hDC, DrawMenuStructure->rcItem.left + nImageOffsetX + 2, DrawMenuStructure->rcItem.bottom);
			::SelectObject(DrawMenuStructure->hDC, hOldPen);
*/
			int itemnumber = -1;
			switch (DrawMenuStructure->itemID)
			{
			case ID_MENU_TO_MODE_0:itemnumber = 0; break;
			case ID_MENU_TO_MODE_1:itemnumber = 1; break;
			case ID_MENU_TO_MODE_2:itemnumber = 2; break;
			case ID_MENU_TO_MODE_3:itemnumber = 3; break;
			case ID_MENU_TO_MODE_4:itemnumber = 4; break;
			case ID_MENU_TO_MODE_5:itemnumber = 5; break;
			case ID_MENU_TO_MODE_6:itemnumber = 6; break;
			case ID_MENU_TO_MODE_7:itemnumber = 7; break;
			case ID_MENU_TO_MODE_8:itemnumber = 8; break;
			}

			// Highlight
			if (m_isClonedList && itemnumber == m_Tab)
			{
				HBRUSH hBrushColor = ::CreateSolidBrush(RGB(153, 160, 157));
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), hBrushColor);
			}
			else if (bSelected)
			{
				HBRUSH hBrushColor = ::CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
				::FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), hBrushColor);
			}

			// Caption
			WCHAR wszBuffer[MAX_PATH];
			int   nCharCount = ::GetMenuString((HMENU)DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, wszBuffer, MAX_PATH, MF_BYCOMMAND);
			if (nCharCount > 0)
			{
				COLORREF crPrevText = 0;
				COLORREF crCurrText = 0;
				crCurrText = ::GetSysColor((itemnumber == m_Tab && m_isClonedList) ? COLOR_INFOBK : (bSelected ? COLOR_HIGHLIGHTTEXT : ((m_isClonedList) ? RGB(166, 134, 170) : RGB(176, 144, 180))));
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
//				int nImageOffsetX = ::GetSystemMetrics(SM_CXMENUCHECK) + nEdgeWidth + nEdgeWidth;
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
					DrawMenuStructure->rcItem.left -=  + 21;
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
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		if (::GetDlgCtrlID((HWND)lParam) == IDC_STATIC)
		{
			SetTextColor(hdcStatic, RGB(0, 0, 255));
			SetBkColor(hdcStatic, RGB(240, 240, 0));
		}
		else if (::GetDlgCtrlID((HWND)lParam) == IDC_STATIC_CLONE)
		{
			static HBRUSH hBrushColor;
			if (!hBrushColor)
				hBrushColor = CreateSolidBrush(RGB(210, 210, 215));
			SetTextColor(hdcStatic, RGB(100, 93, 79));
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LRESULT)hBrushColor;
		}
		else
		{
			SetTextColor(hdcStatic, RGB(62, 20, 102));
			SetBkMode(hdcStatic, TRANSPARENT);
		}
		return (LRESULT)GetStockObject(NULL_BRUSH);
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
			EndPaint(hWnd, &ps);

			for (int i = 0; i < 32; i++)
			{
				if (!tape.Reminder[i])
				{
					hDC = BeginPaint(GetDlgItem(hWnd, m_ReminderId[i]), &ps);
					GetClientRect(GetDlgItem(hWnd, m_ReminderId[i]), &rect);
					rect.right -= 1;
					rect.bottom -= 1;
					brush = CreateSolidBrush(RGB(175, 175, 175));
					FillRect(hDC, &rect, brush);
					if (tape.vJoyUsed[i])
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
						brush = CreateSolidBrush(RGB(210, 210, 255));
					else if (m_Randcolor[i] == 1)
						brush = CreateSolidBrush(RGB(210, 225, 0));
					else if (m_Randcolor[i] == 2)
						brush = CreateSolidBrush(RGB(240, 240, 0));
					else
						brush = CreateSolidBrush(RGB(225, 115, 210));
					FillRect(hDC, &rect, brush);
					if (tape.vJoyUsed[i])
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
					EndPaint(GetDlgItem(hWnd, m_ReminderId[i]), &ps);
				}
			}

			DeleteObject(brush);
		}
		return FALSE;
	}
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code)
		{
		case HDN_BEGINTRACK:
			SetWindowLong(m_hDlg, 0, TRUE);  // prevent resizing
			return TRUE;
		}
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
						Mapping* m = (Mapping*)((LPNMLISTVIEW)lParam)->lParam;
						if (m != 0)
						{
							int idx = ListView_GetNextItem(m_hList, -1, LVNI_FOCUSED);
							if (idx == -1)
							{
								idx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
								if(m->Enable != 2)
								{
									m->Enable = newstate == INDEXTOSTATEIMAGEMASK(2);
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
			break;
		default:
			return FALSE;
		}
		break;
	case WM_MOUSEMOVE:
		if (m_flag_drag && GetCapture() == hWnd)
		{
			if (m_isClonedList)
				DragMove(LOWORD(lParam), HIWORD(lParam) - 35);
			else
				DragMove(LOWORD(lParam), HIWORD(lParam));
		}
		break;
	case WM_LBUTTONUP:
		if (m_flag_drag && GetCapture() == hWnd)
		{
			if (m_isClonedList)
				EndDrag(LOWORD(lParam), HIWORD(lParam) - 35);
			else
				EndDrag(LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_COMMAND:
		if (m_isClonedList)
		{
			switch (LOWORD(wParam))
			{
			case IDC_STATIC_CLONE:
				switch (HIWORD(wParam))
				{
				case BN_CLICKED:
					POINT pt;
					GetCursorPos(&pt);
					TrackPopupMenu((HMENU)GetSubMenu(m_hMenu2, 0), TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, m_hDlg, NULL);
					break;
				}
				break;
			case IDCANCEL:m_isCloned = false; Hide(); break;
			case ID_MENU_TO_MODE_0:SetTab(0); break;
			case ID_MENU_TO_MODE_1:SetTab(1); break;
			case ID_MENU_TO_MODE_2:SetTab(2); break;
			case ID_MENU_TO_MODE_3:SetTab(3); break;
			case ID_MENU_TO_MODE_4:SetTab(4); break;
			case ID_MENU_TO_MODE_5:SetTab(5); break;
			case ID_MENU_TO_MODE_6:SetTab(6); break;
			case ID_MENU_TO_MODE_7:SetTab(7); break;
			case ID_MENU_TO_MODE_8:SetTab(8); break;
			}
		}
		switch (LOWORD(wParam))
		{
		case ID_MENU_ADD:addMappingDlg(); break;
		case ID_MENU_EDIT:editMappingDlg(); break;
		case ID_MENU_DEL:deleteMappingDlg(); break;
		case ID_MENU_COPY:duplicateMappingDlg(); break;
		case ID_MENU_SEPARATOR:addSeparator(); break;
		case ID_MENU_MOVE_TO_0:moveMappingDlg(0); break;
		case ID_MENU_MOVE_TO_1:moveMappingDlg(1); break;
		case ID_MENU_MOVE_TO_2:moveMappingDlg(2); break;
		case ID_MENU_MOVE_TO_3:moveMappingDlg(3); break;
		case ID_MENU_MOVE_TO_4:moveMappingDlg(4); break;
		case ID_MENU_MOVE_TO_5:moveMappingDlg(5); break;
		case ID_MENU_MOVE_TO_6:moveMappingDlg(6); break;
		case ID_MENU_MOVE_TO_7:moveMappingDlg(7); break;
		case ID_MENU_MOVE_TO_8:moveMappingDlg(8); break;
		case IDC_CLEAR:for (int i = 0; i < 32; i++) { tape.Reminder[i] = 0; m_Randcolor[i] = rand() % 4; }tape.Save(tape.Setting_Reminder); Hide(); Show(); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_1:tape.Reminder[0] = !tape.Reminder[0]; CheckDlgButton(hWnd, IDC_POST_ITS_1, (WPARAM)tape.Reminder[0]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_2:tape.Reminder[1] = !tape.Reminder[1]; CheckDlgButton(hWnd, IDC_POST_ITS_2, (WPARAM)tape.Reminder[1]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_3:tape.Reminder[2] = !tape.Reminder[2]; CheckDlgButton(hWnd, IDC_POST_ITS_3, (WPARAM)tape.Reminder[2]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_4:tape.Reminder[3] = !tape.Reminder[3]; CheckDlgButton(hWnd, IDC_POST_ITS_4, (WPARAM)tape.Reminder[3]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_5:tape.Reminder[4] = !tape.Reminder[4]; CheckDlgButton(hWnd, IDC_POST_ITS_5, (WPARAM)tape.Reminder[4]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_6:tape.Reminder[5] = !tape.Reminder[5]; CheckDlgButton(hWnd, IDC_POST_ITS_6, (WPARAM)tape.Reminder[5]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_7:tape.Reminder[6] = !tape.Reminder[6]; CheckDlgButton(hWnd, IDC_POST_ITS_7, (WPARAM)tape.Reminder[6]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_8:tape.Reminder[7] = !tape.Reminder[7]; CheckDlgButton(hWnd, IDC_POST_ITS_8, (WPARAM)tape.Reminder[7]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_9:tape.Reminder[8] = !tape.Reminder[8]; CheckDlgButton(hWnd, IDC_POST_ITS_9, (WPARAM)tape.Reminder[8]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_10:tape.Reminder[9] = !tape.Reminder[9]; CheckDlgButton(hWnd, IDC_POST_ITS_10, (WPARAM)tape.Reminder[9]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_11:tape.Reminder[10] = !tape.Reminder[10]; CheckDlgButton(hWnd, IDC_POST_ITS_11, (WPARAM)tape.Reminder[10]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_12:tape.Reminder[11] = !tape.Reminder[11]; CheckDlgButton(hWnd, IDC_POST_ITS_12, (WPARAM)tape.Reminder[11]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_13:tape.Reminder[12] = !tape.Reminder[12]; CheckDlgButton(hWnd, IDC_POST_ITS_13, (WPARAM)tape.Reminder[12]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_14:tape.Reminder[13] = !tape.Reminder[13]; CheckDlgButton(hWnd, IDC_POST_ITS_14, (WPARAM)tape.Reminder[13]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_15:tape.Reminder[14] = !tape.Reminder[14]; CheckDlgButton(hWnd, IDC_POST_ITS_15, (WPARAM)tape.Reminder[14]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_16:tape.Reminder[15] = !tape.Reminder[15]; CheckDlgButton(hWnd, IDC_POST_ITS_16, (WPARAM)tape.Reminder[15]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_17:tape.Reminder[16] = !tape.Reminder[16]; CheckDlgButton(hWnd, IDC_POST_ITS_17, (WPARAM)tape.Reminder[16]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_18:tape.Reminder[17] = !tape.Reminder[17]; CheckDlgButton(hWnd, IDC_POST_ITS_18, (WPARAM)tape.Reminder[17]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_19:tape.Reminder[18] = !tape.Reminder[18]; CheckDlgButton(hWnd, IDC_POST_ITS_19, (WPARAM)tape.Reminder[18]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_20:tape.Reminder[19] = !tape.Reminder[19]; CheckDlgButton(hWnd, IDC_POST_ITS_20, (WPARAM)tape.Reminder[19]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_21:tape.Reminder[20] = !tape.Reminder[20]; CheckDlgButton(hWnd, IDC_POST_ITS_21, (WPARAM)tape.Reminder[20]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_22:tape.Reminder[21] = !tape.Reminder[21]; CheckDlgButton(hWnd, IDC_POST_ITS_22, (WPARAM)tape.Reminder[21]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_23:tape.Reminder[22] = !tape.Reminder[22]; CheckDlgButton(hWnd, IDC_POST_ITS_23, (WPARAM)tape.Reminder[22]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_24:tape.Reminder[23] = !tape.Reminder[23]; CheckDlgButton(hWnd, IDC_POST_ITS_24, (WPARAM)tape.Reminder[23]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_25:tape.Reminder[24] = !tape.Reminder[24]; CheckDlgButton(hWnd, IDC_POST_ITS_25, (WPARAM)tape.Reminder[24]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_26:tape.Reminder[25] = !tape.Reminder[25]; CheckDlgButton(hWnd, IDC_POST_ITS_26, (WPARAM)tape.Reminder[25]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_27:tape.Reminder[26] = !tape.Reminder[26]; CheckDlgButton(hWnd, IDC_POST_ITS_27, (WPARAM)tape.Reminder[26]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_28:tape.Reminder[27] = !tape.Reminder[27]; CheckDlgButton(hWnd, IDC_POST_ITS_28, (WPARAM)tape.Reminder[27]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_29:tape.Reminder[28] = !tape.Reminder[28]; CheckDlgButton(hWnd, IDC_POST_ITS_29, (WPARAM)tape.Reminder[28]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_30:tape.Reminder[29] = !tape.Reminder[29]; CheckDlgButton(hWnd, IDC_POST_ITS_30, (WPARAM)tape.Reminder[29]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_31:tape.Reminder[30] = !tape.Reminder[30]; CheckDlgButton(hWnd, IDC_POST_ITS_31, (WPARAM)tape.Reminder[30]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		case IDC_POST_ITS_32:tape.Reminder[31] = !tape.Reminder[31]; CheckDlgButton(hWnd, IDC_POST_ITS_32, (WPARAM)tape.Reminder[31]);tape.Save(tape.Setting_Reminder); RedrawWindow(hWnd, NULL, NULL, RDW_INTERNALPAINT | RDW_UPDATENOW); break;
		}
		break;
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
	tape.Save(tape.Setting_Mappingdata);

	PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
	PostMessage(m_hWnd, WM_ADDMAPPING, mDDlg.m_mode, 0);

	m_active = true;
}

void MappingDlg::addMappingDlg()
{
	m_active = false;
	mDDlg.Hide();

	if (ListView_GetSelectedCount(m_hList) == 1)
		lastidx = ListView_GetNextItem(m_hList, -1, LVNI_SELECTED);
	else
		lastidx = ListView_GetItemCount(m_hList);

	Mapping m;
	mDDlg.mappingData = m;
	mDDlg.m_isClonedList = m_isClonedList;
	mDDlg.Open(m_hDlg, 1);

	m_active = true;
}

void MappingDlg::addMappingDlgBack()
{
	m_active = false;

	Mapping* data = new Mapping(mDDlg.mappingData);
	data->Tab = m_Tab;
	insertMapping(lastidx, data);
	lastidx++;
	save();

	m_active = true;
}

void MappingDlg::addSeparator()
{
	m_active = false;
	mDDlg.Hide();

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
}

void MappingDlg::editMappingDlg()
{
	m_active = false;
	mDDlg.Hide();
	
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
				mDDlg.Open(m_hDlg, 2);
			}
		}
	}
	else if (nselected >= 1)
	{
		lastidxs.clear();
		for (int i = 0; i < MappingDataDlg::Mofified_count; i++)
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
		mDDlg.Open(m_hDlg, 3);
	}

	m_active = true;
}

void MappingDlg::editMappingDlgBack()
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
		ListView_DeleteItem(m_hList, lastidx);
		insertMapping(lastidx, data);
		save();
	}

	m_active = true;
}

void MappingDlg::editMappingDlgBackMulti()
{
	m_active = false;

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
			for (int i = 0; i < MappingDataDlg::Mofified_count; i++)
				if (mDDlg.Modified[i])
					switch (i)
					{
					case MappingDataDlg::Mofified_dsID1:data2->dsID[0] = data1->dsID[0]; break;
					case MappingDataDlg::Mofified_dsID2:data2->dsID[1] = data1->dsID[1]; break;
					case MappingDataDlg::Mofified_dsID3:data2->dsID[2] = data1->dsID[2]; break;
					case MappingDataDlg::Mofified_dsID4:data2->dsID[3] = data1->dsID[3]; break;
					case MappingDataDlg::Mofified_dsID5:data2->dsID[4] = data1->dsID[4]; break;
					case MappingDataDlg::Mofified_vjID1:data2->vjID[5] = data1->vjID[5]; break;
					case MappingDataDlg::Mofified_vjID2:data2->vjID[1] = data1->vjID[1]; break;
					case MappingDataDlg::Mofified_vjID3:data2->vjID[2] = data1->vjID[2]; break;
					case MappingDataDlg::Mofified_vjID4:data2->vjID[3] = data1->vjID[3]; break;
					case MappingDataDlg::Mofified_vjID5:data2->vjID[4] = data1->vjID[4]; break;
					case MappingDataDlg::Mofified_vjID6:data2->vjID[5] = data1->vjID[5]; break;
					case MappingDataDlg::Mofified_vjID7:data2->vjID[6] = data1->vjID[6]; break;
					case MappingDataDlg::Mofified_vjID8:data2->vjID[7] = data1->vjID[7]; break;
					case MappingDataDlg::Mofified_vjID9:data2->vjID[8] = data1->vjID[8]; break;
					case MappingDataDlg::Mofified_vjID10:data2->vjID[9] = data1->vjID[9]; break;
					case MappingDataDlg::Mofified_vjID11:data2->vjID[10] = data1->vjID[10]; break;
					case MappingDataDlg::Mofified_vjID12:data2->vjID[11] = data1->vjID[11]; break;
					case MappingDataDlg::Mofified_vjID13:data2->vjID[12] = data1->vjID[12]; break;
					case MappingDataDlg::Mofified_Target1:data2->Target[0] = data1->Target[0]; break;
					case MappingDataDlg::Mofified_Target2:data2->Target[1] = data1->Target[1]; break;
					case MappingDataDlg::Mofified_Target3:data2->Target[2] = data1->Target[2]; break;
					case MappingDataDlg::Mofified_Target4:data2->Target[3] = data1->Target[3]; break;
					case MappingDataDlg::Mofified_Target5:data2->Target[4] = data1->Target[4]; break;
					case MappingDataDlg::Mofified_Disable1:data2->Disable[0] = data1->Disable[0]; break;
					case MappingDataDlg::Mofified_Disable2:data2->Disable[1] = data1->Disable[1]; break;
					case MappingDataDlg::Mofified_Disable3:data2->Disable[2] = data1->Disable[2]; break;
					case MappingDataDlg::Mofified_Disable4:data2->Disable[3] = data1->Disable[3]; break;
					case MappingDataDlg::Mofified_Disable5:data2->Disable[4] = data1->Disable[4]; break;
					case MappingDataDlg::Mofified_Disable6:data2->Disable[5] = data1->Disable[5]; break;
					case MappingDataDlg::Mofified_Disable7:data2->Disable[6] = data1->Disable[6]; break;
					case MappingDataDlg::Mofified_Disable8:data2->Disable[7] = data1->Disable[7]; break;
					case MappingDataDlg::Mofified_Disable9:data2->Disable[8] = data1->Disable[8]; break;
					case MappingDataDlg::Mofified_Disable10:data2->Disable[9] = data1->Disable[9]; break;
					case MappingDataDlg::Mofified_Disable11:data2->Disable[10] = data1->Disable[10]; break;
					case MappingDataDlg::Mofified_Disable12:data2->Disable[11] = data1->Disable[11]; break;
					case MappingDataDlg::Mofified_Disable13:data2->Disable[12] = data1->Disable[12]; break;
					case MappingDataDlg::Mofified_OrXorNot1:data2->OrXorNot[0] = data1->OrXorNot[0]; break;
					case MappingDataDlg::Mofified_OrXorNot2:data2->OrXorNot[1] = data1->OrXorNot[1]; break;
					case MappingDataDlg::Mofified_OrXorNot3:data2->OrXorNot[2] = data1->OrXorNot[2]; break;
					case MappingDataDlg::Mofified_OrXorNot4:data2->OrXorNot[3] = data1->OrXorNot[3]; break;
					case MappingDataDlg::Mofified_Ifmouse:data2->Ifmouse = data1->Ifmouse; break;
					case MappingDataDlg::Mofified_Force:data2->Force = data1->Force; break;
					case MappingDataDlg::Mofified_Led:data2->Led = data1->Led; break;
					case MappingDataDlg::Mofified_Short:data2->Short = data1->Short; break;
					case MappingDataDlg::Mofified_Double:data2->Double = data1->Double; break;
					case MappingDataDlg::Mofified_Long:data2->Long = data1->Long; break;
					case MappingDataDlg::Mofified_Macro:data2->Macro = data1->Macro; break;
					case MappingDataDlg::Mofified_Pause:data2->Pause = data1->Pause; break;
					case MappingDataDlg::Mofified_Toggle:data2->Toggle = data1->Toggle; break;
					case MappingDataDlg::Mofified_OnRelease1:data2->OnRelease[0] = data1->OnRelease[0]; break;
					case MappingDataDlg::Mofified_OnRelease2:data2->OnRelease[1] = data1->OnRelease[1]; break;
					case MappingDataDlg::Mofified_OnRelease3:data2->OnRelease[2] = data1->OnRelease[2]; break;
					case MappingDataDlg::Mofified_OnRelease4:data2->OnRelease[3] = data1->OnRelease[3]; break;
					case MappingDataDlg::Mofified_OnRelease5:data2->OnRelease[4] = data1->OnRelease[4]; break;
					case MappingDataDlg::Mofified_OnRelease6:data2->OnRelease[5] = data1->OnRelease[5]; break;
					case MappingDataDlg::Mofified_OnRelease7:data2->OnRelease[6] = data1->OnRelease[6]; break;
					case MappingDataDlg::Mofified_OnRelease8:data2->OnRelease[7] = data1->OnRelease[7]; break;
					case MappingDataDlg::Mofified_Start1:data2->Start[0] = data1->Start[0]; break;
					case MappingDataDlg::Mofified_Start2:data2->Start[1] = data1->Start[1]; break;
					case MappingDataDlg::Mofified_Start3:data2->Start[2] = data1->Start[2]; break;
					case MappingDataDlg::Mofified_Start4:data2->Start[3] = data1->Start[3]; break;
					case MappingDataDlg::Mofified_Start5:data2->Start[4] = data1->Start[4]; break;
					case MappingDataDlg::Mofified_Start6:data2->Start[5] = data1->Start[5]; break;
					case MappingDataDlg::Mofified_Start7:data2->Start[6] = data1->Start[6]; break;
					case MappingDataDlg::Mofified_Start8:data2->Start[7] = data1->Start[7]; break;
					case MappingDataDlg::Mofified_Stop1:data2->Stop[0] = data1->Stop[0]; break;
					case MappingDataDlg::Mofified_Stop2:data2->Stop[1] = data1->Stop[1]; break;
					case MappingDataDlg::Mofified_Stop3:data2->Stop[2] = data1->Stop[2]; break;
					case MappingDataDlg::Mofified_Stop4:data2->Stop[3] = data1->Stop[3]; break;
					case MappingDataDlg::Mofified_Stop5:data2->Stop[4] = data1->Stop[4]; break;
					case MappingDataDlg::Mofified_Stop6:data2->Stop[5] = data1->Stop[5]; break;
					case MappingDataDlg::Mofified_Stop7:data2->Stop[6] = data1->Stop[6]; break;
					case MappingDataDlg::Mofified_Stop8:data2->Stop[7] = data1->Stop[7]; break;
					case MappingDataDlg::Mofified_MouseAction1:data2->MouseAction[0] = data1->MouseAction[0]; break;
					case MappingDataDlg::Mofified_MouseAction2:data2->MouseAction[1] = data1->MouseAction[1]; break;
					case MappingDataDlg::Mofified_MouseAction3:data2->MouseAction[2] = data1->MouseAction[2]; break;
					case MappingDataDlg::Mofified_MouseAction4:data2->MouseAction[3] = data1->MouseAction[3]; break;
					case MappingDataDlg::Mofified_Mouse1:data2->Mouse[0] = data1->Mouse[0]; break;
					case MappingDataDlg::Mofified_Mouse2:data2->Mouse[1] = data1->Mouse[1]; break;
					case MappingDataDlg::Mofified_Mouse3:data2->Mouse[2] = data1->Mouse[2]; break;
					case MappingDataDlg::Mofified_Mouse4:data2->Mouse[3] = data1->Mouse[3]; break;
					case MappingDataDlg::Mofified_Mouse5:data2->Mouse[4] = data1->Mouse[4]; break;
					case MappingDataDlg::Mofified_Mouse6:data2->Mouse[5] = data1->Mouse[5]; break;
					case MappingDataDlg::Mofified_Mouse7:data2->Mouse[6] = data1->Mouse[6]; break;
					case MappingDataDlg::Mofified_Grid1:data2->Grid[0] = data1->Grid[0]; break;
					case MappingDataDlg::Mofified_Grid2:data2->Grid[1] = data1->Grid[1]; break;
					case MappingDataDlg::Mofified_Grid3:data2->Grid[2] = data1->Grid[2]; break;
					case MappingDataDlg::Mofified_Grid4:data2->Grid[3] = data1->Grid[3]; break;
					case MappingDataDlg::Mofified_Grid5:data2->Grid[4] = data1->Grid[4]; break;
					case MappingDataDlg::Mofified_Grid6:data2->Grid[5] = data1->Grid[5]; break;
					}
			ListView_DeleteItem(m_hList, lastidxs[i]);
			insertMapping(lastidxs[i], data2);
		}
	}
	save();

	m_active = true;
}

void MappingDlg::deleteMappingDlg()
{
	m_active = false;
	mDDlg.Hide();

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
			delete (Mapping*)item.lParam;
			ListView_DeleteItem(m_hList, idx);
		}
		save();
	}

	m_active = true;
}

void MappingDlg::duplicateMappingDlg()
{
	m_active = false;
	mDDlg.Hide();

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
	m_active = false;
	mDDlg.Hide();

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
	mDDlg.Hide();
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
