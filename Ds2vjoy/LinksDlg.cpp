#include "stdafx.h"
#include "LinksDlg.h"
#include "Ds2vJoy.h"

LinksDlg::LinksDlg()
	:m_hWnd()
	, m_hDlg()
{
}

LinksDlg::~LinksDlg()
{
}

INT_PTR CALLBACK LinksDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LinksDlg* iDlg;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		iDlg = (LinksDlg*)lParam;
	}
	else
		iDlg = (LinksDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (iDlg)
		return iDlg->_proc(hWnd, uMsg, wParam, lParam);
	else
		return NULL;
}

void LinksDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_LINKS), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hWnd = hWnd;
	Hide();
}

INT_PTR LinksDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CTLCOLORDLG:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_DLG);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_DLG);
		return (LRESULT)tape.hB_DLG;
	}
	case WM_CTLCOLORMSGBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_MSGBOX);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_MSGBOX);
		return (LRESULT)tape.hB_MSGBOX;
	}
	case WM_CTLCOLORSCROLLBAR:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_SCROLLBAR);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_SCROLLBAR);
		return (LRESULT)tape.hB_SCROLLBAR;
	}
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_BTN);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_BTN);
		return (LRESULT)tape.hB_BTN;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_STATIC);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_STATIC);
		return (LRESULT)tape.hB_STATIC;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_EDIT);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LRESULT)tape.hB_EDIT;
	}
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.Tx_LISTBOX);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LRESULT)tape.hB_LISTBOX;
	}
	case WM_PAINT:
	{
		if (!IsIconic(hWnd))
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			FillRect(hDC, &rect, tape.hB_BackGround);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
		{
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP1NAME), tape.App1Name);
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP2NAME), tape.App2Name);
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP3NAME), tape.App3Name);
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP4NAME), tape.App4Name);
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP5NAME), tape.App5Name);
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP1LOC), tape.App1Location);
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP2LOC), tape.App2Location);
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP3LOC), tape.App3Location);
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP4LOC), tape.App4Location);
			SetWindowText(GetDlgItem(hWnd, IDC_LINKS_APP5LOC), tape.App5Location);
		}
		break;
	}
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LINKS_APP1NAME:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf1[MAX_PATH];
				GetWindowText((HWND)lParam, buf1, MAX_PATH);
				if (lstrcmpW(tape.App1Name, buf1) != 0)
				{
					tape.setAppName(buf1, 1);
					tape.Save(tape.Setting_App1Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		case IDC_LINKS_APP2NAME:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf2[MAX_PATH];
				GetWindowText((HWND)lParam, buf2, MAX_PATH);
				if (lstrcmpW(tape.App2Name, buf2) != 0)
				{
					tape.setAppName(buf2, 2);
					tape.Save(tape.Setting_App2Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		case IDC_LINKS_APP3NAME:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf3[MAX_PATH];
				GetWindowText((HWND)lParam, buf3, MAX_PATH);
				if (lstrcmpW(tape.App3Name, buf3) != 0)
				{
					tape.setAppName(buf3, 3);
					tape.Save(tape.Setting_App3Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		case IDC_LINKS_APP4NAME:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf4[MAX_PATH];
				GetWindowText((HWND)lParam, buf4, MAX_PATH);
				if (lstrcmpW(tape.App4Name, buf4) != 0)
				{
					tape.setAppName(buf4, 4);
					tape.Save(tape.Setting_App4Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		case IDC_LINKS_APP5NAME:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf5[MAX_PATH];
				GetWindowText((HWND)lParam, buf5, MAX_PATH);
				if (lstrcmpW(tape.App5Name, buf5) != 0)
				{
					tape.setAppName(buf5, 5);
					tape.Save(tape.Setting_App5Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		case IDC_LINKS_APP1LOC:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf6[MAX_PATH];
				GetWindowText((HWND)lParam, buf6, MAX_PATH);
				if (lstrcmpW(tape.App1Location, buf6) != 0)
				{
					tape.setAppLocation(buf6, 1);
					tape.Save(tape.Setting_App1Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		case IDC_LINKS_APP2LOC:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf7[MAX_PATH];
				GetWindowText((HWND)lParam, buf7, MAX_PATH);
				if (lstrcmpW(tape.App2Location, buf7) != 0)
				{
					tape.setAppLocation(buf7, 2);
					tape.Save(tape.Setting_App2Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		case IDC_LINKS_APP3LOC:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf8[MAX_PATH];
				GetWindowText((HWND)lParam, buf8, MAX_PATH);
				if (lstrcmpW(tape.App3Location, buf8) != 0)
				{
					tape.setAppLocation(buf8, 3);
					tape.Save(tape.Setting_App3Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		case IDC_LINKS_APP4LOC:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf9[MAX_PATH];
				GetWindowText((HWND)lParam, buf9, MAX_PATH);
				if (lstrcmpW(tape.App4Location, buf9) != 0)
				{
					tape.setAppLocation(buf9, 4);
					tape.Save(tape.Setting_App4Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		case IDC_LINKS_APP5LOC:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf10[MAX_PATH];
				GetWindowText((HWND)lParam, buf10, MAX_PATH);
				if (lstrcmpW(tape.App5Location, buf10) != 0)
				{
					tape.setAppLocation(buf10, 5);
					tape.Save(tape.Setting_App5Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		default:
			return FALSE;
		}
		break;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_CLICK:
		case NM_RETURN:
		{
			if (wParam == IDC_LINKS_WEBVJOY || wParam == IDC_LINKS_WEBPROJECT || wParam == IDC_LINKS_WEBVIGEM || wParam == IDC_LINKS_WEBGUARDIAN)
			{
				PNMLINK pNMLink = (PNMLINK)lParam;
				LITEM item = pNMLink->item;

				ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOWNORMAL);
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

void LinksDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}

void LinksDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);
}

BOOL LinksDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
