#include "stdafx.h"
#include "KeymapDataDlg.h"

KeymapDataDlg::KeymapDataDlg()
{
}

KeymapDataDlg::~KeymapDataDlg()
{
}

void KeymapDataDlg::Init()
{
	m_mode = 0;
	m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_KEYMAP_ADD), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));
	Hide();
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_SOURCE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_BTN_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_BTN, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_RESTORE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_RESTORE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_MAXIMIZE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_MAXIMIZE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_SHOW_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_SHOW, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_ACTIVATING_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_ACTIVATING, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_SEND, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_INPUT1_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_INPUT2_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_INPUT3_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_INPUT1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_INPUT2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_INPUT3, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_ENTER, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_INPUT, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_CLEAR, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_NATURAL_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_NATURAL, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_POSTMESSAGE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_POSTMESSAGE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_FW_TEXT, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_FINDWINDOW, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_METHOD, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_EXTENDEDKEY_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_EXTENDEDKEY, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_SCANCODE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_SCANCODE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_OK, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_CANCEL, WM_SETFONT, WPARAM(tape.hCancel), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_WINDOW, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_FIND_LIST, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_WINDOW_LIST_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_WINDOW_LIST, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_IS_W_VISIBLE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_IS_W_VISIBLE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_CLEAR2, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_DELETE, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_OK2, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_KEYMAP_CANCEL2, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_SOURCE), I18N.KEYMAP_SOURCE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_RESTORE), I18N.KEYMAP_RESTORE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_MAXIMIZE), I18N.KEYMAP_MAXIMIZE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_SHOW), I18N.KEYMAP_SHOW);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_ACTIVATING), I18N.KEYMAP_ACTIVATING);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_SEND), I18N.KEYMAP_SEND);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_ENTER), I18N.KEYMAP_ENTER);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_CLEAR), I18N.KEYMAP_CLEAR);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_NATURAL), I18N.KEYMAP_NATURAL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_POSTMESSAGE), I18N.KEYMAP_POSTMESSAGE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_FINDWINDOW), I18N.KEYMAP_FINDWINDOW);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_METHOD), I18N.KEYMAP_METHOD);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_EXTENDEDKEY), I18N.KEYMAP_EXTENDEDKEY);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_SCANCODE), I18N.KEYMAP_SCANCODE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_OK), I18N.KEYMAP_OK);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_CANCEL), I18N.KEYMAP_CANCEL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_WINDOW), I18N.KEYMAP_WINDOW);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_IS_W_VISIBLE), I18N.KEYMAP_IS_W_VISIBLE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_CLEAR2), I18N.KEYMAP_CLEAR2);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_DELETE), I18N.KEYMAP_DELETE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_OK2), I18N.KEYMAP_OK2);
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_CANCEL2), I18N.KEYMAP_CANCEL2);

	m_hList = GetDlgItem(m_hDlg, IDC_KEYMAP_FIND_LIST);

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);

	HWND header = ListView_GetHeader(m_hList);
	DWORD dwHeaderStyle = ::GetWindowLong(header, GWL_STYLE);
	dwHeaderStyle = dwHeaderStyle & ~HDS_DRAGDROP | HDS_NOSIZING;
	::SetWindowLong(header, GWL_STYLE, dwHeaderStyle);

	LVCOLUMN col;
	firsttime = true;
	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.cx = 140;
	col.pszText = I18N.KEYMAP_CLASS;
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = I18N.KEYMAP_TITLE;
	col.cx = 270;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = I18N.KEYMAP_IDX;
	col.cx = 26;
	ListView_InsertColumn(m_hList, 2, &col);

	SetWindowSubclass(m_hList, (SUBCLASSPROC)ListSubclassProc, 1, (DWORD_PTR)this);
}

void KeymapDataDlg::Open(HWND parent, int mode)
{
	m_mode = mode;
	dlgPage = 0;
	firsttime = false;
	canprint = false;
	ShowWindow(parent, SW_HIDE);
	Show();
	PostMessage(tape.Ds2hWnd, WM_SIZE, 0, -1);
}

void KeymapDataDlg::_InitDialog(HWND hWnd)
{
	SetTimer(hWnd, 1, 10, NULL);
	for (int i = 0; i < DestButtonID::Destination_Count; i++)
	{
		WCHAR* str = DestinationButton::String((DestButtonID)i);
		SendDlgItemMessage(hWnd, IDC_KEYMAP_BTN, CB_ADDSTRING, 0, LPARAM(str));
	}
	for (int i = 0; i < keymapData.KeyboardID_Count; i++)
	{
		const WCHAR* str = keymapData.String((KeyboardID)i);
		SendDlgItemMessage(hWnd, IDC_KEYMAP_INPUT1, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_KEYMAP_INPUT2, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_KEYMAP_INPUT3, CB_ADDSTRING, 0, LPARAM(str));
	}

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void KeymapDataDlg::_ShowWindow(HWND hWnd)
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

	SendDlgItemMessage(hWnd, IDC_KEYMAP_BTN, CB_SETCURSEL, WPARAM(keymapData.ButtonID), 0);
	SendDlgItemMessage(hWnd, IDC_KEYMAP_INPUT1, CB_SETCURSEL, 0, 0);
	SendDlgItemMessage(hWnd, IDC_KEYMAP_INPUT2, CB_SETCURSEL, 0, 0);
	SendDlgItemMessage(hWnd, IDC_KEYMAP_INPUT3, CB_SETCURSEL, 0, 0);
	HWND hInput = GetDlgItem(hWnd, IDC_KEYMAP_INPUT);

	SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_BTN_STATIC), (keymapData.ButtonID) ? DestinationButton::String((DestButtonID)keymapData.ButtonID) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_INPUT1_STATIC), L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_INPUT2_STATIC), L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_INPUT3_STATIC), L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_WINDOW_LIST_STATIC), L"...");

	CheckDlgButton(hWnd, IDC_KEYMAP_NATURAL_CHK, keymapData.NaturalTyping);

	SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_METHOD), L"Method: PostMessage");
	if (keymapData.usePostmessage)
	{
		CheckDlgButton(hWnd, IDC_KEYMAP_POSTMESSAGE_CHK, BST_CHECKED);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_RESTORE_CHK), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_MAXIMIZE_CHK), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_SHOW_CHK), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_ACTIVATING_CHK), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_FW_TEXT), TRUE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_FINDWINDOW), TRUE);
		CheckDlgButton(hWnd, IDC_KEYMAP_RESTORE_CHK, keymapData.WndRestore);
		CheckDlgButton(hWnd, IDC_KEYMAP_MAXIMIZE_CHK, keymapData.WndMaximize);
		CheckDlgButton(hWnd, IDC_KEYMAP_SHOW_CHK, keymapData.WndShow);
		CheckDlgButton(hWnd, IDC_KEYMAP_ACTIVATING_CHK, keymapData.useActivating);
		if (keymapData.useActivating)
			SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_METHOD), L"Method: Activating");
	}
	else
	{
		CheckDlgButton(hWnd, IDC_KEYMAP_POSTMESSAGE_CHK, BST_UNCHECKED);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_RESTORE_CHK), FALSE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_MAXIMIZE_CHK), FALSE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_SHOW_CHK), FALSE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_ACTIVATING_CHK), FALSE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_FW_TEXT), FALSE);
		EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_FINDWINDOW), FALSE);
	}

	canprint = false;
	SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_INPUT), keymapData.ValueString(1));
	SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_FW_TEXT), keymapData.findWindow.Val().c_str());
	canprint = true;

	CheckDlgButton(hWnd, IDC_KEYMAP_EXTENDEDKEY_CHK, keymapData.ExtendedKey);
	CheckDlgButton(hWnd, IDC_KEYMAP_SCANCODE_CHK, keymapData.Scancode);

	SendMessage(hWnd, WM_RESET_FINDWINDOW, 0, 0);

	SetFocus(GetDlgItem(hWnd, IDC_KEYMAP_INPUT));
	EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_INPUT), true);
}

INT_PTR CALLBACK KeymapDataDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	KeymapDataDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<KeymapDataDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<KeymapDataDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR KeymapDataDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int KeymapDataDlgmoved;
	static RECT KeymapDataDlgrect;
	switch (message)
	{
	case WM_CTLCOLORDLG:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_DLG);
		SetTextColor(hdcStatic, tape.ink_DLG);
		return (LRESULT)tape.hB_DLG;
	}
	case WM_CTLCOLORMSGBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_MSGBOX);
		SetTextColor(hdcStatic, tape.ink_MSGBOX);
		return (LRESULT)tape.hB_MSGBOX;
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
		SetBkMode(hdcStatic, TRANSPARENT);
		switch (GetDlgCtrlID((HWND)lParam))
		{
		case IDC_KEYMAP_FW_TEXT:
		{
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_EDIT_TERMINAL);
				return (LRESULT)tape.hB_BackGround_DARK;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_EDIT);
				return (LRESULT)tape.hB_EDIT;
			}
		}
		case IDC_KEYMAP_RESTORE:
		case IDC_KEYMAP_MAXIMIZE:
		case IDC_KEYMAP_SHOW:
		case IDC_KEYMAP_ACTIVATING:
		case IDC_KEYMAP_NATURAL:
		case IDC_KEYMAP_POSTMESSAGE:
		case IDC_KEYMAP_EXTENDEDKEY:
		case IDC_KEYMAP_SCANCODE:
		case IDC_KEYMAP_IS_W_VISIBLE:
		case IDC_KEYMAP_BTN_STATIC:
		case IDC_KEYMAP_INPUT1_STATIC:
		case IDC_KEYMAP_INPUT2_STATIC:
		case IDC_KEYMAP_INPUT3_STATIC:
		case IDC_KEYMAP_WINDOW_LIST_STATIC:
		{
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_CHK_DARK);
				return (LRESULT)tape.hB_BackGround_DARK;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_CHK);
				return (LRESULT)tape.hB_BackGround;
			}
			break;
		}
		case IDC_KEYMAP_RESTORE_CHK:
		case IDC_KEYMAP_MAXIMIZE_CHK:
		case IDC_KEYMAP_SHOW_CHK:
		case IDC_KEYMAP_ACTIVATING_CHK:
		case IDC_KEYMAP_NATURAL_CHK:
		case IDC_KEYMAP_POSTMESSAGE_CHK:
		case IDC_KEYMAP_EXTENDEDKEY_CHK:
		case IDC_KEYMAP_SCANCODE_CHK:
		case IDC_KEYMAP_IS_W_VISIBLE_CHK:
		{
			SetTextColor(hdcStatic, tape.ink_STATIC);
			if (tape.DarkTheme)
				return (LRESULT)tape.hB_BackGround_DARK;
			else
				return (LRESULT)tape.hB_BackGround;
		}
		default:
		{
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_DARK);
				return (LRESULT)tape.hB_BackGround_DARK;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_STATIC);
				return (LRESULT)tape.hB_BackGround;
			}
			break;
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
				FillRect(hDC, &rect, tape.hB_BackGround);

			if (tape.DarkTheme)
			{
				SetRect(&rect, 8, 96, 423, 116);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK3);
				SetRect(&rect, 8, 150, 423, 170);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK3);

				SetRect(&rect, 8, 97, 423, 115);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK);
				SetRect(&rect, 8, 151, 423, 169);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK);
			}
			else
			{
				SetRect(&rect, 8, 96, 423, 116);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 8, 150, 423, 170);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);

				SetRect(&rect, 8, 97, 423, 115);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 8, 151, 423, 169);
				FillRect(hDC, &rect, tape.hB_EDIT);
			}

			POINT Pt;
			MoveToEx(hDC, 469, rect.top, &Pt);
			LineTo(hDC, 469, rect.bottom);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
			std::thread(&KeymapDataDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&KeymapDataDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_TIMER:
	{
		if (wParam == 1)
		{
			if (KeymapDataDlgmoved > 0)
			{
				if (KeymapDataDlgmoved < 22)
				{
					double tmp1 = (double)KeymapDataDlgmoved - 1;
					double tmp2 = ((y20minus470 * tmp1) / 21) + y470;
					double tmp3 = 1 / (tmp2 * tmp2);
					int tmp4 = 492 - (int)tmp3;
					::MoveWindow(m_hDlg, KeymapDataDlgrect.left - tmp4, KeymapDataDlgrect.top, KeymapDataDlgrect.right + tmp4, KeymapDataDlgrect.bottom, TRUE);
					KeymapDataDlgmoved++;
				}
				else
				{
					KeymapDataDlgmoved = 0;
				}
			}
			if (KeymapDataDlgmoved < 0)
			{
				if (KeymapDataDlgmoved > -22)
				{
					double tmp1 = -1 - (double)KeymapDataDlgmoved;
					double tmp2 = ((y20minus470 * tmp1) / 21) + y470;
					double tmp3 = 1 / (tmp2 * tmp2);
					int tmp4 = 492 - (int)tmp3;
					::MoveWindow(m_hDlg, KeymapDataDlgrect.left - 470 + tmp4, KeymapDataDlgrect.top, KeymapDataDlgrect.right + 470 - tmp4, KeymapDataDlgrect.bottom, TRUE);
					KeymapDataDlgmoved--;
				}
				else
				{
					KeymapDataDlgmoved = 0;
				}
			}
		}
		break;
	}
	case WM_RESET_FINDWINDOW:
	{
		if (!alreadydone)
		{
			alreadydone = true;
			SendDlgItemMessage(hWnd, IDC_KEYMAP_WINDOW_LIST, CB_RESETCONTENT, 0, 0);
			int idx = ListView_GetItemCount(m_hList);
			while (--idx >= 0) { ListView_DeleteItem(m_hList, idx); }
			SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_WINDOW_LIST_STATIC), L"...");
		}

		if (m_hEdit != NULL)
			DestroyWindow(m_hEdit);
		m_hEdit = NULL;

		SendMessage(GetDlgItem(m_hDlg, IDC_KEYMAP_IS_W_VISIBLE_CHK), BM_SETCHECK, BST_CHECKED, 0);
		m_filter_iwv = true;
		int length = keymapData.findWindow.Size();

		LVITEM item = { 0 };
		item.mask = LVIF_TEXT | LVIF_PARAM;
		item.iSubItem = 0;
		item.lParam = LPARAM(0);
		for (int i = 0; i < length; i++)
		{
			auto findClass = keymapData.findWindow.Get(i, 0);
			auto findTitle = keymapData.findWindow.Get(i, 1);
			auto findIdx = keymapData.findWindow.Get(i, 2);
			item.iItem = ListView_GetItemCount(m_hList);
			item.pszText = const_cast<WCHAR*>(findClass.c_str());
			ListView_InsertItem(m_hList, &item);
			ListView_SetItemText(m_hList, item.iItem, 1, const_cast<WCHAR*>(findTitle.c_str()));
			ListView_SetItemText(m_hList, item.iItem, 2, const_cast<WCHAR*>(findIdx.c_str()));
		}
		break;
	}
	case WM_GETDLGCODE:
	{
		return DLGC_WANTALLKEYS;
	}
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		if (dlgPage == 0)
		{
			keymapData.GetState();
			SetWindowText(hWnd, keymapData.ValueString(1));
			return TRUE;
		}
		break;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_KEYMAP_RESTORE_CHK:
		case IDC_KEYMAP_MAXIMIZE_CHK:
		case IDC_KEYMAP_SHOW_CHK:
		case IDC_KEYMAP_ACTIVATING_CHK:
		case IDC_KEYMAP_NATURAL_CHK:
		case IDC_KEYMAP_POSTMESSAGE_CHK:
		case IDC_KEYMAP_EXTENDEDKEY_CHK:
		case IDC_KEYMAP_SCANCODE_CHK:
		case IDC_KEYMAP_IS_W_VISIBLE_CHK:
		{
			if (((LPNMHDR)lParam)->code == NM_CUSTOMDRAW)
			{
				LPNMCUSTOMDRAW DrawMenuCustom = (LPNMCUSTOMDRAW)lParam;
				DrawMenuCustom->rc.right = DrawMenuCustom->rc.left + 12;
				DrawMenuCustom->rc.bottom = DrawMenuCustom->rc.top + 12;

				RECT rect;
				rect.left = DrawMenuCustom->rc.left + 1;
				rect.right = rect.left + 11;
				rect.top = DrawMenuCustom->rc.top + 1;
				rect.bottom = rect.top + 11;

				if (DrawMenuCustom->dwDrawStage == CDDS_PREPAINT)
				{
					switch (IsDlgButtonChecked(m_hDlg, ((LPNMHDR)lParam)->idFrom))
					{
					case BST_UNCHECKED:
					{
						FillRect(DrawMenuCustom->hdc, &rect, tape.hB_CHECKBOX_UNCHECKED);
						break;
					}
					case BST_CHECKED:
					{
						FillRect(DrawMenuCustom->hdc, &rect, tape.hB_CHECKBOX_CHECKED);
						DrawText(DrawMenuCustom->hdc, L"■", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					case BST_INDETERMINATE:
					{
						FillRect(DrawMenuCustom->hdc, &rect, tape.hB_CHECKBOX_INDETERMINATE);
						DrawText(DrawMenuCustom->hdc, L"■", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					}
					return TRUE;
				}
			}
			break;
		}
		case IDC_KEYMAP_CLEAR:
		case IDC_KEYMAP_FINDWINDOW:
		case IDC_KEYMAP_OK:
		case IDC_KEYMAP_CANCEL:
		case IDC_KEYMAP_CLEAR2:
		case IDC_KEYMAP_DELETE:
		case IDC_KEYMAP_OK2:
		case IDC_KEYMAP_CANCEL2:
		{
			if (!tape.DarkTheme)
				break;
			switch (((LPNMHDR)lParam)->code)
			{
			case NM_CUSTOMDRAW:
			{
				LPNMCUSTOMDRAW DrawListCustom = (LPNMCUSTOMDRAW)lParam;
				if (DrawListCustom->uItemState == CDIS_HOT || DrawListCustom->uItemState == CDIS_NEARHOT)
				{
					FillRect(DrawListCustom->hdc, &DrawListCustom->rc, tape.hB_BTN_DARK);
					SelectObject(DrawListCustom->hdc, GetStockObject(DC_PEN));
					SetDCPenColor(DrawListCustom->hdc, tape.ink_grey);
					RoundRect(DrawListCustom->hdc, DrawListCustom->rc.left + 1, DrawListCustom->rc.top + 1, DrawListCustom->rc.right - 1, DrawListCustom->rc.bottom - 1, 6, 6);
				}
				return CDRF_DODEFAULT;
			}
			case BCN_HOTITEMCHANGE:
			{
				switch (((NMBCHOTITEM*)lParam)->dwFlags)
				{
				case (HICF_ENTERING | HICF_MOUSE):
				{
					::SetWindowTheme(((LPNMHDR)lParam)->hwndFrom, L"", L"");
					break;
				}
				case (HICF_LEAVING | HICF_MOUSE):
				{
					::SetWindowTheme(((LPNMHDR)lParam)->hwndFrom, L"Explorer", NULL);
					break;
				}
				}
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_FIND_LIST:
		{
			switch (((LPNMHDR)lParam)->code)
			{
			case NM_DBLCLK:
			{
				if (m_hEdit == NULL)
				{
					LVHITTESTINFO ht;
					GetCursorPos(&ht.pt);
					ScreenToClient(m_hList, &ht.pt);
					if (-1 != ListView_SubItemHitTest(m_hList, &ht))
					{
						RECT rc;
						ListView_GetSubItemRect(m_hList, ht.iItem, ht.iSubItem, LVIR_LABEL, &rc);
						m_hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_WANTRETURN, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, m_hList, 0, GetModuleHandle(NULL), NULL);
						m_editIdx = ht.iItem;
						m_editCol = ht.iSubItem;
						auto buf = keymapData.findWindow.Get(m_editIdx, m_editCol);
						SetWindowText(m_hEdit, buf.c_str());
						HFONT hFont = (HFONT)SendMessage(m_hList, WM_GETFONT, NULL, NULL);
						SendMessage(m_hEdit, WM_SETFONT, WPARAM(hFont), 0);
						m_flag_cancel = true;
						SetFocus(m_hEdit);
					}
				}
				break;
			}
			case NM_CLICK:
			{
				if (m_hEdit != NULL)
				{
					if (m_flag_cancel)
					{
						auto buf = keymapData.findWindow.GetText(m_hEdit);
						keymapData.findWindow.Set(m_editIdx, m_editCol, std::move(buf));
						buf = keymapData.findWindow.Get(m_editIdx, m_editCol);
						ListView_SetItemText(m_hList, m_editIdx, m_editCol, const_cast<WCHAR*>(buf.c_str()));
					}
					DestroyWindow(m_hEdit);
					m_flag_cancel = false;
					m_hEdit = NULL;
				}
				break;
			}
			case NM_RCLICK:
			{
				if (m_hEdit != NULL)
				{
					DestroyWindow(m_hEdit);
					m_hEdit = NULL;
				}
				break;
			}
			default:
				return FALSE;
			}
			break;
		}
		default:
		{
			return FALSE;
		}
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_KEYMAP_OK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (keymapData.ButtonID == 0 && m_mode != 3)
				{
					RECT win;
					GetWindowRect(tape.Ds2hWnd, &win);
					MessageBoxPos(hWnd, I18N.MBOX_NoButtonSelected, I18N.MBOX_ErrTitle, MB_ICONERROR, win.left + 275, win.top + 30);
					return TRUE;
				}
				keymapData.Enable = true;
				int key1 = (int)SendMessage(GetDlgItem(hWnd, IDC_KEYMAP_INPUT1), CB_GETCURSEL, 0, 0);
				int key2 = (int)SendMessage(GetDlgItem(hWnd, IDC_KEYMAP_INPUT2), CB_GETCURSEL, 0, 0);
				int key3 = (int)SendMessage(GetDlgItem(hWnd, IDC_KEYMAP_INPUT3), CB_GETCURSEL, 0, 0);
				if (key1) { Modified[Mofified_vk] = true; keymapData.vk.push_back(keymapData.KeyboardIDtoByte((KeyboardID)key1)); }
				if (key2) { Modified[Mofified_vk] = true; keymapData.vk.push_back(keymapData.KeyboardIDtoByte((KeyboardID)key2)); }
				if (key3) { Modified[Mofified_vk] = true; keymapData.vk.push_back(keymapData.KeyboardIDtoByte((KeyboardID)key3)); }
				PostMessage(tape.Ds2hWnd, WM_ADDKEYMAP, m_mode, 1);
				m_mode = 0;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_CANCEL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				PostMessage(tape.Ds2hWnd, WM_ADDKEYMAP, 0, 0);
				m_mode = 0;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_CLEAR:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.vk.clear();
				keymapData.GetState();
				Modified[Mofified_vk] = true;
				SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_INPUT), L"");
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_BTN_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_KEYMAP_BTN), TRUE);
				break;
			}
			break;
		}
		case IDC_KEYMAP_BTN:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				keymapData.ButtonID = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_ButtonID] = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_BTN_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_BTN_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_BTN_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_RESTORE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.WndRestore = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				Modified[Mofified_WndRestore] = true;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_MAXIMIZE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.WndMaximize = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				Modified[Mofified_WndMaximize] = true;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_SHOW_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.WndShow = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				Modified[Mofified_WndShow] = true;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_INPUT1_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_KEYMAP_INPUT1), TRUE);
				break;
			}
			break;
		}
		case IDC_KEYMAP_INPUT1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_INPUT1_STATIC), (result) ? keymapData.String((KeyboardID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_INPUT1_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_INPUT1_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_INPUT2_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_KEYMAP_INPUT2), TRUE);
				break;
			}
			break;
		}
		case IDC_KEYMAP_INPUT2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_INPUT2_STATIC), (result) ? keymapData.String((KeyboardID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_INPUT2_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_INPUT2_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_INPUT3_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_KEYMAP_INPUT3), TRUE);
				break;
			}
			break;
		}
		case IDC_KEYMAP_INPUT3:
		{
			switch (HIWORD(wParam))
			{
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_INPUT3_STATIC), (result) ? keymapData.String((KeyboardID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_INPUT3_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_INPUT3_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_NATURAL_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.NaturalTyping = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				Modified[Mofified_NaturalTyping] = true;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_INPUT:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE: {
				keymapData.GetState();
				SetWindowText((HWND)lParam, keymapData.ValueString(1));
				Modified[Mofified_vk] = true;
				break;
			}
			default:
				return FALSE;
			}
			break;
		}
		case IDC_KEYMAP_POSTMESSAGE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.usePostmessage = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				if (keymapData.usePostmessage)
				{
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_RESTORE_CHK), TRUE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_MAXIMIZE_CHK), TRUE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_SHOW_CHK), TRUE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_ACTIVATING_CHK), TRUE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_FW_TEXT), TRUE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_FINDWINDOW), TRUE);
				}
				else
				{
					if (keymapData.WndRestore)
					{
						keymapData.WndRestore = 0;
						CheckDlgButton(hWnd, IDC_KEYMAP_RESTORE_CHK, BST_UNCHECKED);
						Modified[Mofified_WndRestore] = true;
					}
					if (keymapData.WndMaximize)
					{
						keymapData.WndMaximize = 0;
						CheckDlgButton(hWnd, IDC_KEYMAP_MAXIMIZE_CHK, BST_UNCHECKED);
						Modified[Mofified_WndMaximize] = true;
					}
					if (keymapData.WndShow)
					{
						keymapData.WndShow = 0;
						CheckDlgButton(hWnd, IDC_KEYMAP_SHOW_CHK, BST_UNCHECKED);
						Modified[Mofified_WndShow] = true;
					}
					if (keymapData.useActivating)
					{
						keymapData.useActivating = false;
						CheckDlgButton(hWnd, IDC_KEYMAP_ACTIVATING_CHK, BST_UNCHECKED);
						SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_METHOD), L"Method: PostMessage");
					}
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_RESTORE_CHK), FALSE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_MAXIMIZE_CHK), FALSE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_SHOW_CHK), FALSE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_ACTIVATING_CHK), FALSE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_FW_TEXT), FALSE);
					EnableWindow(GetDlgItem(hWnd, IDC_KEYMAP_FINDWINDOW), FALSE);
				}
				Modified[Mofified_usePostmessage] = true;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_ACTIVATING_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.useActivating = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				if (keymapData.useActivating)
					SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_METHOD), L"Method: Activating");
				else
					SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_METHOD), L"Method: PostMessage");
				Modified[Mofified_useActivating] = true;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_EXTENDEDKEY_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.ExtendedKey = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				Modified[Mofified_ExtendedKey] = true;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_SCANCODE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.Scancode = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				Modified[Mofified_Scancode] = true;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_FINDWINDOW:
		{
			fw = keymapData.findWindow;
			GetClientRect(tape.Ds2hWnd, &KeymapDataDlgrect);
			KeymapDataDlgrect.left += 3;
			KeymapDataDlgrect.top += 21;
			KeymapDataDlgrect.right -= 6;
			KeymapDataDlgrect.bottom -= 45;
			dlgPage = 1;
			KeymapDataDlgmoved = 1;
			break;
		}
		case IDC_KEYMAP_WINDOW_LIST_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_KEYMAP_WINDOW_LIST), TRUE);
				break;
			}
			break;
		}
		case IDC_KEYMAP_WINDOW_LIST:
		{
			switch (HIWORD(wParam))
			{
			case CBN_DROPDOWN:
			{
				SendMessage((HWND)lParam, CB_RESETCONTENT, 0, 0);
				{
					HWND hwnd = keymapData.findWindow.Find();
					if (hwnd != NULL || keymapData.findWindow.Size() == 0)
					{
						HWND child = NULL;
						int count = 0;
						std::wstring buf;
						while ((child = FindWindowEx(hwnd, child, NULL, NULL)) != NULL)
						{
							if (!m_filter_iwv || IsWindowVisible(child))
							{
								count++;
								buf.clear();
								buf.append(Findwindow::GetClass(child));
								buf.append(L", ");
								buf.append(Findwindow::GetText(child));
								LRESULT idx = SendMessage((HWND)lParam, CB_ADDSTRING, 0, LPARAM(buf.c_str()));
								if (idx != CB_ERR && idx != CB_ERRSPACE)
									SendMessage((HWND)lParam, CB_SETITEMDATA, idx, LPARAM(child));
							}
						}
						if (count == 0)
						{
							WCHAR buf[100];
							swprintf_s(buf, 100, L"HWND:%08x", (int)(size_t)hwnd);
							SendMessage((HWND)lParam, CB_ADDSTRING, 0, LPARAM(buf));
						}
					}
					else if (hwnd == NULL)
						SendMessage((HWND)lParam, CB_ADDSTRING, 0, LPARAM(L"Failed FindWindow"));
				}
				break;
			}
			case CBN_CLOSEUP:
			{
				LRESULT idx = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				if (idx != CB_ERR)
				{
					HWND hWin = (HWND)SendMessage((HWND)lParam, CB_GETITEMDATA, idx, 0);
					if (hWin != (HWND)CB_ERR && hWin != NULL)
					{
						int iItem = ListView_GetItemCount(m_hList);
						auto classname = Findwindow::GetClass(hWin);
						LVITEM item = { 0 };
						item.mask = LVIF_TEXT | LVIF_PARAM;
						item.iItem = iItem;
						item.pszText = const_cast<LPWSTR>(classname.c_str());
						ListView_InsertItem(m_hList, &item);

						auto titlename = Findwindow::GetText(hWin);
						ListView_SetItemText(m_hList, iItem, 1, const_cast<LPWSTR>(titlename.c_str()));

						int idx = 0;
						HWND hwnd = keymapData.findWindow.Find();
						while (idx == 0)
						{
							HWND child = NULL;

							while ((child = FindWindowEx(hwnd, child, (classname.empty()) ? NULL : classname.c_str(), titlename.empty() ? NULL : titlename.c_str())) != hWin)
							{
								idx++;
								if (child == NULL)
								{
									idx = -1;
									break;
								}
							}
							if (idx == -1 && !titlename.empty())
							{
								idx = 0;
								titlename.clear();
							}
							else
								break;
						}
						WCHAR findIdx[10] = L"";
						swprintf_s(findIdx, 10, L"%d", idx);
						ListView_SetItemText(m_hList, iItem, 2, findIdx);

						keymapData.findWindow.Set(-1, 0, classname);
						keymapData.findWindow.Set(-1, 1, titlename);
						keymapData.findWindow.Set(-1, 2, findIdx);

						SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_WINDOW_LIST_STATIC), classname.c_str());
						::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_WINDOW_LIST_STATIC), SW_HIDE);
						::ShowWindow(GetDlgItem(hWnd, IDC_KEYMAP_WINDOW_LIST_STATIC), SW_SHOW);
					}
				}
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_CLEAR2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				int idx = ListView_GetItemCount(m_hList);
				while (--idx >= 0)
					ListView_DeleteItem(m_hList, idx);
				keymapData.findWindow.Clear();
				SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_WINDOW_LIST_STATIC), L"...");
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_DELETE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				int idx = ListView_GetItemCount(m_hList);
				if (idx > 0)
				{
					ListView_DeleteItem(m_hList, --idx);
					keymapData.findWindow.Pop();
				}
				if (idx < 1)
					SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_WINDOW_LIST_STATIC), L"...");
				else
				{
					WCHAR wszBuffer[2048];
					ListView_GetItemText(m_hList, --idx, 0, wszBuffer, 2048);
					std::wstring GetItemText = wszBuffer;
					SetWindowText(GetDlgItem(hWnd, IDC_KEYMAP_WINDOW_LIST_STATIC), GetItemText.c_str());
				}
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_OK2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				keymapData.findWindow = keymapData.findWindow;
				if (m_hEdit != NULL)
				{
					DestroyWindow(m_hEdit);
					m_hEdit = NULL;
				}
				SetWindowText(GetDlgItem(m_hDlg, IDC_KEYMAP_FW_TEXT), keymapData.findWindow.Val().c_str());
				Modified[Mofified_findWindow] = true;
				dlgPage = 0;
				PostMessage(tape.Ds2hWnd, WM_SIZE, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_CANCEL2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				alreadydone = false;
				keymapData.findWindow = fw;
				SendMessage(hWnd, WM_RESET_FINDWINDOW, 0, 0);
				GetClientRect(tape.Ds2hWnd, &KeymapDataDlgrect);
				KeymapDataDlgrect.left += 3;
				KeymapDataDlgrect.top += 21;
				KeymapDataDlgrect.right -= 6;
				KeymapDataDlgrect.bottom -= 45;
				dlgPage = 0;
				KeymapDataDlgmoved = -1;
				break;
			}
			}
			break;
		}
		case IDC_KEYMAP_IS_W_VISIBLE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_filter_iwv = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				break;
			}
			}
			break;
		}
		}
		break;
	}
	default:
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK KeymapDataDlg::ListSubclassProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIDSubClass, DWORD_PTR RefData)
{
	KeymapDataDlg* dlg = reinterpret_cast<KeymapDataDlg*>(RefData);
	if (dlg)
		return dlg->_listSubclassProc(hWnd, message, wParam, lParam);

	return DefSubclassProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK KeymapDataDlg::_listSubclassProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
				return CDRF_NOTIFYITEMDRAW;
			}
			case CDDS_ITEMPREPAINT:
			{
				if (tape.DarkTheme)
				{
					switch (DrawListCustom->dwItemSpec)
					{
					case 0:
					{
						FillRect(DrawListCustom->hdc, &DrawListCustom->rc, tape.hB_LIST_Header_DARK);
						SetBkColor(DrawListCustom->hdc, tape.Bk_LIST_header1_DARK);
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header1_DARK);
						DrawText(DrawListCustom->hdc, I18N.KEYMAP_CLASS, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					case 1:
					{
						FillRect(DrawListCustom->hdc, &DrawListCustom->rc, tape.hB_LIST_Header2_DARK);
						SetBkColor(DrawListCustom->hdc, tape.Bk_LIST_header2_DARK);
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header2_DARK);
						DrawText(DrawListCustom->hdc, I18N.KEYMAP_TITLE, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					case 2:
					{
						FillRect(DrawListCustom->hdc, &DrawListCustom->rc, tape.hB_LIST_Header2_DARK);
						SetBkColor(DrawListCustom->hdc, tape.Bk_LIST_header2_DARK);
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header2_DARK);
						DrawText(DrawListCustom->hdc, I18N.KEYMAP_IDX, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					}
				}
				else
				{
					switch (DrawListCustom->dwItemSpec)
					{
					case 0:
					{
						FillRect(DrawListCustom->hdc, &DrawListCustom->rc, tape.hB_LIST_Header);
						SetBkColor(DrawListCustom->hdc, tape.ink_LIST_Header);
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header1);
						DrawText(DrawListCustom->hdc, I18N.KEYMAP_CLASS, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					case 1:
					{
						FillRect(DrawListCustom->hdc, &DrawListCustom->rc, tape.hB_LIST_Header2);
						SetBkColor(DrawListCustom->hdc, tape.ink_LIST_scndHeader);
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header2_DARK);
						DrawText(DrawListCustom->hdc, I18N.KEYMAP_TITLE, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					case 2:
					{
						FillRect(DrawListCustom->hdc, &DrawListCustom->rc, tape.hB_LIST_Header2);
						SetBkColor(DrawListCustom->hdc, tape.ink_LIST_scndHeader);
						SetTextColor(DrawListCustom->hdc, tape.ink_LIST_header2_DARK);
						DrawText(DrawListCustom->hdc, I18N.KEYMAP_IDX, -1, &DrawListCustom->rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					}
				}
				return CDRF_SKIPDEFAULT;
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

void KeymapDataDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void KeymapDataDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL KeymapDataDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
