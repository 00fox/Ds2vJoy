#include "stdafx.h"
#include "GuardianDlg.h"
#include "Guardian.h"
#include "Ds2vJoy.h"

GuardianDlg::GuardianDlg()
	:m_hWnd()
	, m_hDlg()
	, tmpGstate(false)
{
}

GuardianDlg::~GuardianDlg()
{
}

INT_PTR CALLBACK GuardianDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
	GuardianDlg* dlg;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (GuardianDlg*)lParam;
	}
	else
		dlg = (GuardianDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	else
		return NULL;
}

void GuardianDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_GUARDIAN), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hWnd = hWnd;
	Hide();
}

INT_PTR GuardianDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		DWORD CtrlID = GetDlgCtrlID((HWND)lParam);
		SetBkMode(hdcStatic, TRANSPARENT);

		switch (hid.GetHidGState())
		{
		case -1:
		case 0:
			if (CtrlID == IDC_HID_GUARDIAN_INSTALL) return (LRESULT)tape.hB_Not_Installed;
			if (CtrlID == IDC_HID_GUARDIAN_STATUS) return (LRESULT)tape.hB_Not_Installed;
			break;
		case 1:
			if (CtrlID == IDC_HID_GUARDIAN_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_GUARDIAN_STATUS)
			{
				if (tmpGstate)
					return (LRESULT)tape.hB_Paused;
				else
					return (LRESULT)tape.hB_Running;
			}
			break;
		case 2:
			if (CtrlID == IDC_HID_GUARDIAN_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_GUARDIAN_STATUS) return (LRESULT)tape.hB_Paused;
			break;
		}
		switch (hid.GetHidCState())
		{
		case -1:
		case 0:
			if (CtrlID == IDC_HID_CERBERUS_INSTALL) return (LRESULT)tape.hB_Not_Installed;
			if (CtrlID == IDC_HID_CERBERUS_STATUS) return (LRESULT)tape.hB_Not_Installed;
			break;
		case 2:
		case 4:
		case 5:
			if (CtrlID == IDC_HID_CERBERUS_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_CERBERUS_STATUS) return (LRESULT)tape.hB_Running;
			break;
		case 1:
		case 3:
			if (CtrlID == IDC_HID_CERBERUS_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_CERBERUS_STATUS) return (LRESULT)tape.hB_Stopped;
			break;
		case 6:
		case 7:
			if (CtrlID == IDC_HID_CERBERUS_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_CERBERUS_STATUS) return (LRESULT)tape.hB_Paused;
			break;
		}
		return (LRESULT)tape.hB_Grey;
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

			SetRect(&rect, 351, 103, 366, 113);
			FillRect(hDC, &rect, tape.hB_Not_Installed);

			SetRect(&rect, 351, 119, 366, 129);
			FillRect(hDC, &rect, tape.hB_Running);
			
			SetRect(&rect, 402, 103, 415, 113);
			FillRect(hDC, &rect, tape.hB_Stopped);
			
			SetRect(&rect, 402, 119, 415, 129);
			FillRect(hDC, &rect, tape.hB_Paused);

			LPCWSTR b1Text = L"Waiting...";
			LPCWSTR b2Text = L"Waiting...";
			LPCWSTR b3Text = L"Waiting...";
			LPCWSTR b4Text = L"Waiting...";
			SetTextColor(hDC, tape.TextColor);
			switch (hid.GetHidGState())
			{
			case -1:
			case 0:
				b1Text = L" Install ";
				b2Text = L"         ";
				break;
			case 1:
				b1Text = L"Uninstall";
				b2Text = L" Restart ";
				break;
			case 2:
				b1Text = L"Uninstall";
				b2Text = L" Enable  ";
				break;
			}
			switch (hid.GetHidCState())
			{
			case -1:
			case 0:
				b3Text = L" Install ";
				b4Text = L"         ";
				break;
			case 2:
			case 4:
			case 5:
				b3Text = L"Uninstall";
				b4Text = L"  Stop   ";
				break;
			case 1:
			case 3:
				b3Text = L"Uninstall";
				b4Text = L"  Start  ";
				break;
			case 6:
			case 7:
				b3Text = L"Uninstall";
				b4Text = L"  Start  ";
				break;
			}

			HFONT hFont = CreateFont(13, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_HID_GUARDIAN_INSTALL), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_HID_GUARDIAN_INSTALL), &rect);
			HFONT oldHFont = (HFONT)SelectObject(hDC, hFont);
			DrawText(hDC, b1Text, 9, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SelectObject(hDC, oldHFont);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_HID_GUARDIAN_STATUS), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_HID_GUARDIAN_STATUS), &rect);
			oldHFont = (HFONT)SelectObject(hDC, hFont);
			DrawText(hDC, b2Text, 9, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SelectObject(hDC, oldHFont);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_HID_CERBERUS_INSTALL), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_HID_CERBERUS_INSTALL), &rect);
			oldHFont = (HFONT)SelectObject(hDC, hFont);
			DrawText(hDC, b3Text, 9, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SelectObject(hDC, oldHFont);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_HID_CERBERUS_STATUS), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_HID_CERBERUS_STATUS), &rect);
			oldHFont = (HFONT)SelectObject(hDC, hFont);
			DrawText(hDC, b4Text, 9, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SelectObject(hDC, oldHFont);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
		if (wParam == TRUE || lParam == 3)
		{
			hid.HidStates();
			SetActiveWindow(m_hWnd);
		}
		if (wParam == TRUE)
		{
			CheckDlgButton(hWnd, IDC_HID_ACTIVE, tape.GuardianActive);
			CheckDlgButton(hWnd, IDC_HID_REMOVE, tape.RemoveBlacklist);
			CheckDlgButton(hWnd, IDC_HID_PURGE, tape.PurgeWhitelist);
			SetWindowText(GetDlgItem(hWnd, IDC_HID_HID1), tape.dsHID1);
			SetWindowText(GetDlgItem(hWnd, IDC_HID_HID2), tape.dsHID2);
			SetWindowText(GetDlgItem(hWnd, IDC_HID_HID3), tape.dsHID3);
			CheckDlgButton(hWnd, IDC_HID_HID1_ENABLE, tape.dsHID1Enable);
			CheckDlgButton(hWnd, IDC_HID_HID2_ENABLE, tape.dsHID2Enable);
			CheckDlgButton(hWnd, IDC_HID_HID3_ENABLE, tape.dsHID3Enable);
			SetWindowText(GetDlgItem(hWnd, IDC_HID_EXE1), tape.Exe1Name);
			SetWindowText(GetDlgItem(hWnd, IDC_HID_EXE2), tape.Exe2Name);
			SetWindowText(GetDlgItem(hWnd, IDC_HID_EXE3), tape.Exe3Name);
			SetWindowText(GetDlgItem(hWnd, IDC_HID_EXE4), tape.Exe4Name);
			SetWindowText(GetDlgItem(hWnd, IDC_HID_EXE5), tape.Exe5Name);
			CheckDlgButton(hWnd, IDC_HID_EXE1_ENABLE, tape.Exe1NameEnable);
			CheckDlgButton(hWnd, IDC_HID_EXE2_ENABLE, tape.Exe2NameEnable);
			CheckDlgButton(hWnd, IDC_HID_EXE3_ENABLE, tape.Exe3NameEnable);
			CheckDlgButton(hWnd, IDC_HID_EXE4_ENABLE, tape.Exe4NameEnable);
			CheckDlgButton(hWnd, IDC_HID_EXE5_ENABLE, tape.Exe5NameEnable);
			
			HFONT hFont = CreateFont(11, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			SendDlgItemMessage(hWnd, IDC_STATIC_LEGEND1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_STATIC_LEGEND2, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_STATIC_LEGEND3, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_STATIC_LEGEND4, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_STATIC_LEGEND5, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

			hFont = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			SendDlgItemMessage(hWnd, IDC_STATIC_INSTALL, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		}
		break;
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_HID_HID1:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf1[MAX_PATH];
				GetWindowText((HWND)lParam, buf1, MAX_PATH);
				if (lstrcmpW(tape.dsHID1, buf1) != 0)
				{
					tape.setPID(buf1, 1);
					tape.Save(tape.Setting_dsHID1);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 1);
				}
				break;
			}
			break;
		case IDC_HID_HID2:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf2[MAX_PATH];
				GetWindowText((HWND)lParam, buf2, MAX_PATH);
				if (lstrcmpW(tape.dsHID2, buf2) != 0)
				{
					tape.setPID(buf2, 2);
					tape.Save(tape.Setting_dsHID2);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 2);
				}
				break;
			}
			break;
		case IDC_HID_HID3:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf3[MAX_PATH];
				GetWindowText((HWND)lParam, buf3, MAX_PATH);
				if (lstrcmpW(tape.dsHID3, buf3) != 0)
				{
					tape.setPID(buf3, 3);
					tape.Save(tape.Setting_dsHID3);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 3);
				}
				break;
			}
			break;
		case IDC_HID_EXE1:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf4[MAX_PATH];
				GetWindowText((HWND)lParam, buf4, MAX_PATH);
				if (lstrcmpW(tape.Exe1Name, buf4) != 0)
				{
					tape.setExeName(buf4, 1);
					tape.Save(tape.Setting_Exe1Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 1);
				}
				break;
			}
			break;
		case IDC_HID_EXE2:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf5[MAX_PATH];
				GetWindowText((HWND)lParam, buf5, MAX_PATH);
				if (lstrcmpW(tape.Exe2Name, buf5) != 0)
				{
					tape.setExeName(buf5, 2);
					tape.Save(tape.Setting_Exe2Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 2);
				}
				break;
			}
			break;
		case IDC_HID_EXE3:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf6[MAX_PATH];
				GetWindowText((HWND)lParam, buf6, MAX_PATH);
				if (lstrcmpW(tape.Exe3Name, buf6) != 0)
				{
					tape.setExeName(buf6, 3);
					tape.Save(tape.Setting_Exe3Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 3);
				}
				break;
			}
			break;
		case IDC_HID_EXE4:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf7[MAX_PATH];
				GetWindowText((HWND)lParam, buf7, MAX_PATH);
				if (lstrcmpW(tape.Exe4Name, buf7) != 0)
				{
					tape.setExeName(buf7, 4);
					tape.Save(tape.Setting_Exe4Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 4);
				}
				break;
			}
			break;
		case IDC_HID_EXE5:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				WCHAR buf8[MAX_PATH];
				GetWindowText((HWND)lParam, buf8, MAX_PATH);
				if (lstrcmpW(tape.Exe5Name, buf8) != 0)
				{
					tape.setExeName(buf8, 5);
					tape.Save(tape.Setting_Exe5Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 5);
				}
				break;
			}
			break;
		case IDC_HID_ACTIVE:
			tape.GuardianActive = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_GuardianActive);
			PostMessage(m_hWnd, WM_DEVICE_DS_START, 0, 1);
			PostMessage(m_hWnd, WM_CHANGE_HIDS, 0, 0);
			break;
		case IDC_HID_REMOVE:
			tape.RemoveBlacklist = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_RemoveBlacklist);
			break;
		case IDC_HID_PURGE:
			tape.PurgeWhitelist = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_PurgeWhitelist);
			break;
		case IDC_HID_HID1_ENABLE:
			tape.dsHID1Enable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_dsHID1Enable);
			PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 1);
			break;
		case IDC_HID_HID2_ENABLE:
			tape.dsHID2Enable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_dsHID2Enable);
			PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 2);
			break;
		case IDC_HID_HID3_ENABLE:
			tape.dsHID3Enable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_dsHID3Enable);
			PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 3);
			break;
		case IDC_HID_EXE1_ENABLE:
			tape.Exe1NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_Exe1NameEnable);
			PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 1);
			break;
		case IDC_HID_EXE2_ENABLE:
			tape.Exe2NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_Exe2NameEnable);
			PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 2);
			break;
		case IDC_HID_EXE3_ENABLE:
			tape.Exe3NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_Exe3NameEnable);
			PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 3);
			break;
		case IDC_HID_EXE4_ENABLE:
			tape.Exe4NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_Exe4NameEnable);
			PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 4);
			break;
		case IDC_HID_EXE5_ENABLE:
			tape.Exe5NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			tape.Save(tape.Setting_Exe5NameEnable);
			PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 5);
			break;
		case IDC_HID_GUARDIAN_INSTALL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				int HidGState = hid.GetHidGState();
				hid.HidStates();
				if (HidGState == hid.GetHidGState())
				{
					switch (HidGState)
					{
					case -1:
					case 0:
						hid.GuardianInstall();
						break;
					case 1:
					case 2:
						hid.GuardianUninstall();
						break;
					}
				}
				Sleep(500);
				hid.HidStates();
				Hide();
				Show();
				break;
			}
			break;
		}
		case IDC_HID_GUARDIAN_STATUS:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				int HidGState = hid.GetHidGState();
				hid.HidStates();
				if (HidGState == hid.GetHidGState())
				{
					switch (HidGState)
					{
					case -1:
					case 0:
						break;
					case 1:
						tmpGstate = true;
						InvalidateRect(GetDlgItem(hWnd, IDC_HID_GUARDIAN_STATUS), NULL, TRUE);
						UpdateWindow(hWnd);
						hid.AllDevicesRestart();
						tmpGstate = false;
						InvalidateRect(GetDlgItem(hWnd, IDC_HID_GUARDIAN_STATUS), NULL, TRUE);
						SendMessage(hWnd, WM_PAINT, 0, 0);
						return TRUE;
					case 2:
						hid.GuardianEnable();
						break;
					}
				}
				Sleep(500);
				hid.HidStates();
				Hide();
				Show();
				break;
			}
			break;
		}
		case IDC_HID_CERBERUS_INSTALL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				int HidCState = hid.GetHidCState();
				hid.HidStates();
				if (HidCState == hid.GetHidCState())
				{
					switch (HidCState)
					{
					case -1:
					case 0:
						hid.HidCerberusInstall();
						break;
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
						hid.HidCerberusUninstall();
						break;
					}
				}
				SendMessage(m_hWnd, WM_CHANGE_HIDS, -1, 6);
				break;
			}
			break;
		}
		case IDC_HID_CERBERUS_STATUS:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				int HidCState = hid.GetHidCState();
				hid.HidStates();
				if (HidCState == hid.GetHidCState())
				{
					switch (HidCState)
					{
					case -1:
					case 0:
						break;
					case 2:
					case 4:
					case 5:
						hid.HidCerberusStop();
						break;
					case 1:
					case 3:
					case 6:
					case 7:
						hid.HidCerberusStart();
						break;
					}
				}
				SendMessage(m_hWnd, WM_CHANGE_HIDS, -1, 6);
				break;
			}
			break;
		}
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
			if (wParam == IDC_HID_CERBERUS_LINK)
			{
				PNMLINK pNMLink = (PNMLINK)lParam;
				LITEM   item = pNMLink->item;

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

void GuardianDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}

void GuardianDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);
}

BOOL GuardianDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return  ::MoveWindow(m_hDlg, x, y, w, h, r);
}
