#include "stdafx.h"
#include "LinksDlg.h"

LinksDlg::LinksDlg()
{
}

LinksDlg::~LinksDlg()
{
}

void LinksDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_LINKS), hWnd, (DLGPROC)Proc, LPARAM(this));
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_TEXT1), WM_SETFONT, WPARAM(tape.hStatic), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_TEXT2), WM_SETFONT, WPARAM(tape.hStatic), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL0), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL1), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL2), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL3), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL4), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL5), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL6), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL7), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL8), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBURL9), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_TEXT3), WM_SETFONT, WPARAM(tape.hStatic), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_TEXT4), WM_SETFONT, WPARAM(tape.hStatic), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP1NAME), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP2NAME), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP3NAME), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP4NAME), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP5NAME), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP1LOC), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP2LOC), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP3LOC), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP4LOC), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_APP5LOC), WM_SETFONT, WPARAM(tape.hEdit2), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_DS4VJOY), WM_SETFONT, WPARAM(tape.hLinks), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_VJOY), WM_SETFONT, WPARAM(tape.hLinks), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBVIEW2), WM_SETFONT, WPARAM(tape.hLinks), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_VIGEMBUS), WM_SETFONT, WPARAM(tape.hLinks), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_VIGEMCLIENT), WM_SETFONT, WPARAM(tape.hLinks), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_HIDGUARDIAN), WM_SETFONT, WPARAM(tape.hLinks), TRUE);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_HIDCERBERUS), WM_SETFONT, WPARAM(tape.hLinks), TRUE);

	SetWindowText(GetDlgItem(m_hDlg, IDC_LINKS_TEXT1), I18N.LINKS_TEXT1);
	SetWindowText(GetDlgItem(m_hDlg, IDC_LINKS_TEXT2), I18N.LINKS_TEXT2);
	SetWindowText(GetDlgItem(m_hDlg, IDC_LINKS_TEXT3), I18N.LINKS_TEXT3);
	SetWindowText(GetDlgItem(m_hDlg, IDC_LINKS_TEXT4), I18N.LINKS_TEXT4);

	LITEM item {};
	ZeroMemory(&item, sizeof(item));
	item.mask = LIF_ITEMINDEX | LIF_ITEMID | LIF_URL | LIF_STATE;
	item.state = LIS_ENABLED | LIS_FOCUSED | LIS_HOTTRACK;
	item.stateMask = LIS_ENABLED | LIS_FOCUSED | LIS_HOTTRACK;

	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_DS4VJOY), LM_GETITEM, 0, (LPARAM)&item);
	//wcscpy_s(item.szID, MAX_LINKID_TEXT, I18N.LINKS_DS4VJOY);
	wcscpy_s(item.szUrl, L_MAX_URL_LENGTH, I18N.LINKS_URL_DS4VJOY);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_DS4VJOY), LM_SETITEM, 0, (LPARAM)&item);

	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_VJOY), LM_GETITEM, 0, (LPARAM)&item);
	wcscpy_s(item.szUrl, L_MAX_URL_LENGTH, I18N.LINKS_URL_VJOY);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_VJOY), LM_SETITEM, 0, (LPARAM)&item);

	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBVIEW2), LM_GETITEM, 0, (LPARAM)&item);
	wcscpy_s(item.szUrl, L_MAX_URL_LENGTH, I18N.LINKS_URL_WEBVIEW2);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_WEBVIEW2), LM_SETITEM, 0, (LPARAM)&item);

	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_VIGEMBUS), LM_GETITEM, 0, (LPARAM)&item);
	wcscpy_s(item.szUrl, L_MAX_URL_LENGTH, I18N.LINKS_URL_VIGEMBUS);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_VIGEMBUS), LM_SETITEM, 0, (LPARAM)&item);

	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_VIGEMCLIENT), LM_GETITEM, 0, (LPARAM)&item);
	wcscpy_s(item.szUrl, L_MAX_URL_LENGTH, I18N.LINKS_URL_VIGEMCLIENT);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_VIGEMCLIENT), LM_SETITEM, 0, (LPARAM)&item);

	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_HIDGUARDIAN), LM_GETITEM, 0, (LPARAM)&item);
	wcscpy_s(item.szUrl, L_MAX_URL_LENGTH, I18N.LINKS_URL_HIDGUARDIAN);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_HIDGUARDIAN), LM_SETITEM, 0, (LPARAM)&item);

	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_HIDCERBERUS), LM_GETITEM, 0, (LPARAM)&item);
	wcscpy_s(item.szUrl, L_MAX_URL_LENGTH, I18N.LINKS_URL_HIDCERBERUS);
	SendMessage(GetDlgItem(m_hDlg, IDC_LINKS_HIDCERBERUS), LM_SETITEM, 0, (LPARAM)&item);
	Hide();
}

void LinksDlg::_InitDialog(HWND hWnd)
{

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void LinksDlg::_ShowWindow(HWND hWnd)
{
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL0), tape.WebURL[0]);
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL1), tape.WebURL[1]);
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL2), tape.WebURL[2]);
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL3), tape.WebURL[3]);
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL4), tape.WebURL[4]);
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL5), tape.WebURL[5]);
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL6), tape.WebURL[6]);
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL7), tape.WebURL[7]);
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL8), tape.WebURL[8]);
	SetWindowText(GetDlgItem(hWnd, IDC_LINKS_WEBURL9), tape.WebURL[9]);
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

INT_PTR CALLBACK LinksDlg::Proc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	LinksDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<LinksDlg*>(lparam);
		SetWindowLongPtrW(hWnd, DWLP_USER, lparam);
	}
	else
		dlg = reinterpret_cast<LinksDlg*>(GetWindowLongPtrW(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wparam, lparam);
		return result;
	}
	return DefWindowProcW(hWnd, message, wparam, lparam);
}

INT_PTR LinksDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_STATIC);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_STATIC);
		return (LRESULT)tape.hB_STATIC;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_EDIT);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LRESULT)tape.hB_EDIT;
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
			std::thread(&LinksDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&LinksDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_CLICK:
		case NM_RETURN:
		{
			if (wParam == IDC_LINKS_DS4VJOY ||
				wParam == IDC_LINKS_VJOY ||
				wParam == IDC_LINKS_WEBVIEW2 ||
				wParam == IDC_LINKS_VIGEMBUS ||
				wParam == IDC_LINKS_VIGEMCLIENT ||
				wParam == IDC_LINKS_HIDGUARDIAN ||
				wParam == IDC_LINKS_HIDCERBERUS)
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
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LINKS_WEBURL0:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[0], buf) != 0)
				{
					tape.setWebURL(buf, 0);
					tape.Save(tape.Setting_WebURL0);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_WEBURL1:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[1], buf) != 0)
				{
					tape.setWebURL(buf, 1);
					tape.Save(tape.Setting_WebURL1);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_WEBURL2:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[2], buf) != 0)
				{
					tape.setWebURL(buf, 2);
					tape.Save(tape.Setting_WebURL2);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_WEBURL3:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[3], buf) != 0)
				{
					tape.setWebURL(buf, 3);
					tape.Save(tape.Setting_WebURL3);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_WEBURL4:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[4], buf) != 0)
				{
					tape.setWebURL(buf, 4);
					tape.Save(tape.Setting_WebURL4);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_WEBURL5:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[5], buf) != 0)
				{
					tape.setWebURL(buf, 5);
					tape.Save(tape.Setting_WebURL5);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_WEBURL6:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[6], buf) != 0)
				{
					tape.setWebURL(buf, 6);
					tape.Save(tape.Setting_WebURL6);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_WEBURL7:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[7], buf) != 0)
				{
					tape.setWebURL(buf, 7);
					tape.Save(tape.Setting_WebURL7);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_WEBURL8:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[8], buf) != 0)
				{
					tape.setWebURL(buf, 8);
					tape.Save(tape.Setting_WebURL8);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_WEBURL9:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.WebURL[9], buf) != 0)
				{
					tape.setWebURL(buf, 9);
					tape.Save(tape.Setting_WebURL9);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP1NAME:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App1Name, buf) != 0)
				{
					tape.setAppName(buf, 1);
					tape.Save(tape.Setting_App1Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP2NAME:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App2Name, buf) != 0)
				{
					tape.setAppName(buf, 2);
					tape.Save(tape.Setting_App2Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP3NAME:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App3Name, buf) != 0)
				{
					tape.setAppName(buf, 3);
					tape.Save(tape.Setting_App3Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP4NAME:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App4Name, buf) != 0)
				{
					tape.setAppName(buf, 4);
					tape.Save(tape.Setting_App4Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP5NAME:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App5Name, buf) != 0)
				{
					tape.setAppName(buf, 5);
					tape.Save(tape.Setting_App5Name);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP1LOC:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App1Location, buf) != 0)
				{
					tape.setAppLocation(buf, 1);
					tape.Save(tape.Setting_App1Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP2LOC:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App2Location, buf) != 0)
				{
					tape.setAppLocation(buf, 2);
					tape.Save(tape.Setting_App2Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP3LOC:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App3Location, buf) != 0)
				{
					tape.setAppLocation(buf, 3);
					tape.Save(tape.Setting_App3Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP4LOC:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App4Location, buf) != 0)
				{
					tape.setAppLocation(buf, 4);
					tape.Save(tape.Setting_App4Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
			}
			break;
		}
		case IDC_LINKS_APP5LOC:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.App5Location, buf) != 0)
				{
					tape.setAppLocation(buf, 5);
					tape.Save(tape.Setting_App5Location);
					PostMessage(m_hWnd, WM_CREATE_MENU, 0, 0);
				}
				break;
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
	return TRUE;
}

void LinksDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void LinksDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL LinksDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
