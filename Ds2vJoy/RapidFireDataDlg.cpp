#include "stdafx.h"
#include "RapidFireDataDlg.h"

RapidFireDataDlg::RapidFireDataDlg()
{
}

RapidFireDataDlg::~RapidFireDataDlg()
{
}

void RapidFireDataDlg::Init()
{
	m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_RAPIDFIRE_ADD), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));
	Hide();
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_SOURCE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_BTN_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_BTN, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_MULTIPLE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_BTN2_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_BTN2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_TEXT_FIRST, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_TEXT_RELEASE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_TEXT_DOWN, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_UNIT_FIRST, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_UNIT_RELEASE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_UNIT_DOWN, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_FIRST, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_RELEASE, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_DOWN, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_OK, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_CANCEL, WM_SETFONT, WPARAM(tape.hCancel), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_RAPIDFIRE_NOTICE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_SOURCE), I18N.RAPIDFIRE_RAPIDFIRE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_MULTIPLE), I18N.RAPIDFIRE_MULTIPLE_PRESS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_TEXT_FIRST), I18N.RAPIDFIRE_TEXT_FIRST);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_TEXT_RELEASE), I18N.RAPIDFIRE_TEXT_RELEASE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_TEXT_DOWN), I18N.RAPIDFIRE_TEXT_DOWN);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_UNIT_FIRST), I18N.RAPIDFIRE_UNIT_FIRST);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_UNIT_RELEASE), I18N.RAPIDFIRE_UNIT_RELEASE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_UNIT_DOWN), I18N.RAPIDFIRE_UNIT_DOWN);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_NOTICE), I18N.RAPIDFIRE_NOTICE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_OK), I18N.RAPIDFIRE_OK);
	SetWindowText(GetDlgItem(m_hDlg, IDC_RAPIDFIRE_CANCEL), I18N.RAPIDFIRE_CANCEL);
}

void RapidFireDataDlg::Open(HWND parent, int mode)
{
	m_mode = mode;
	canprint = false;
	ShowWindow(parent, SW_HIDE);
	Show();
	PostMessage(tape.Ds2hWnd, WM_SIZE, 0, -1);
}

void RapidFireDataDlg::_InitDialog(HWND hWnd)
{
	for (int i = 0; i < DestButtonID::Destination_Count; i++)
	{
		WCHAR* str = DestinationButton::String((DestButtonID)i);
		SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN2, CB_ADDSTRING, 0, LPARAM(str));
	}

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void RapidFireDataDlg::_ShowWindow(HWND hWnd)
{
	SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN, CB_SETCURSEL, rapidFireData.ButtonID, 0);
	SendDlgItemMessage(hWnd, IDC_RAPIDFIRE_BTN2, CB_SETCURSEL, rapidFireData.ButtonID2, 0);

	SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN_STATIC), (rapidFireData.ButtonID) ? DestinationButton::String((DestButtonID)rapidFireData.ButtonID) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN2_STATIC), (rapidFireData.ButtonID2) ? DestinationButton::String((DestButtonID)rapidFireData.ButtonID2) : L"...");

	canprint = false;
	WCHAR buf[MAX_PATH];
	swprintf_s(buf, MAX_PATH, L"%d", rapidFireData.Firsttime);
	SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_FIRST), buf);
	swprintf_s(buf, MAX_PATH, L"%d", rapidFireData.Releasetime);
	SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_RELEASE), buf);
	swprintf_s(buf, MAX_PATH, L"%d", rapidFireData.Presstime);
	SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_DOWN), buf);
	canprint = true;
}

INT_PTR CALLBACK RapidFireDataDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RapidFireDataDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<RapidFireDataDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<RapidFireDataDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR RapidFireDataDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
		SetBkMode(hdcStatic, OPAQUE);
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
		case IDC_RAPIDFIRE_UNIT_FIRST:
		case IDC_RAPIDFIRE_UNIT_RELEASE:
		case IDC_RAPIDFIRE_UNIT_DOWN:
		case IDC_RAPIDFIRE_NOTICE:
		case IDC_RAPIDFIRE_BTN_STATIC:
		case IDC_RAPIDFIRE_BTN2_STATIC:
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
				SetRect(&rect, 207, 78, 270, 98);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK3);
				SetRect(&rect, 207, 122, 270, 142);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK3);
				SetRect(&rect, 207, 162, 270, 182);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK3);

				SetRect(&rect, 207, 79, 270, 97);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK);
				SetRect(&rect, 207, 123, 270, 141);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK);
				SetRect(&rect, 207, 163, 270, 181);
				FrameRect(hDC, &rect, tape.hB_EDIT_DARK);
			}
			else
			{
				SetRect(&rect, 207, 78, 270, 98);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 207, 122, 270, 142);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 207, 162, 270, 182);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);

				SetRect(&rect, 207, 79, 270, 97);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 207, 123, 270, 141);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 207, 163, 270, 181);
				FillRect(hDC, &rect, tape.hB_EDIT);
			}

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
			std::thread(&RapidFireDataDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&RapidFireDataDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_RAPIDFIRE_OK:
		case IDC_RAPIDFIRE_CANCEL:
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
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_RAPIDFIRE_OK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (rapidFireData.ButtonID == 0 && rapidFireData.ButtonID2 == 0 && m_mode != 3)
				{
					RECT win;
					GetWindowRect(tape.Ds2hWnd, &win);
					MessageBoxPos(hWnd, I18N.MBOX_NoButtonSelected, I18N.MBOX_ErrTitle, MB_ICONERROR, win.left + 275, win.top + 30);
					return TRUE;
				}
				rapidFireData.Enable = true;
				PostMessage(tape.Ds2hWnd, WM_ADDRAPIDFIRE, m_mode, 1);
				m_mode = 0;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_CANCEL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				PostMessage(tape.Ds2hWnd, WM_ADDRAPIDFIRE, 0, 0);
				m_mode = 0;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_BTN_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN), TRUE);
				break;
			}
			break;
		}
		case IDC_RAPIDFIRE_BTN:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				rapidFireData.ButtonID = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[ModifiedRapidFire_ButtonID] = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_BTN2_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN2), TRUE);
				break;
			}
			break;
		}
		case IDC_RAPIDFIRE_BTN2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				rapidFireData.ButtonID2 = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[ModifiedRapidFire_ButtonID2] = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN2_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN2_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_RAPIDFIRE_BTN2_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_FIRST:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf1[MAX_PATH];
				GetWindowText((HWND)lParam, buf1, MAX_PATH);
				rapidFireData.Firsttime = max(0, _wtoi(buf1));
				if (canprint) Modified[ModifiedRapidFire_Firsttime] = true;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_RELEASE:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf2[MAX_PATH];
				GetWindowText((HWND)lParam, buf2, MAX_PATH);
				rapidFireData.Releasetime = max(0, _wtoi(buf2));
				if (canprint) Modified[ModifiedRapidFire_Releasetime] = true;
				break;
			}
			}
			break;
		}
		case IDC_RAPIDFIRE_DOWN:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf3[MAX_PATH];
				GetWindowText((HWND)lParam, buf3, MAX_PATH);
				rapidFireData.Presstime = max(0, _wtoi(buf3));
				if (canprint) Modified[ModifiedRapidFire_Presstime] = true;
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

void RapidFireDataDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void RapidFireDataDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL RapidFireDataDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
