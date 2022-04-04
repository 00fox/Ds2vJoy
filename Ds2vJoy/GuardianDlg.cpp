#include "stdafx.h"
#include "GuardianDlg.h"
#include "Guardian.h"

GuardianDlg::GuardianDlg()
{
}

GuardianDlg::~GuardianDlg()
{
}

void GuardianDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_GUARDIAN), hWnd, (DLGPROC)Proc, LPARAM(this));
	SendDlgItemMessage(m_hDlg, IDC_HID_ACTIVE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_ACTIVE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_VJOY_SHUTDOWN_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_VJOY_SHUTDOWN, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_WHEN_EXITING, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_BLACKLIST, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_HID1, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_HID2, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_HID3, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_HID1_ENABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_HID2_ENABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_HID3_ENABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_REMOVE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_REMOVE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_WHITELIST, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE1, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE2, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE3, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE4, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE5, WM_SETFONT, WPARAM(tape.hEdit), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE1_ENABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE2_ENABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE3_ENABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE4_ENABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_EXE5_ENABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_PURGE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_PURGE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_CERBERUS_LINK, WM_SETFONT, WPARAM(tape.hLinks), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_INSTALL, WM_SETFONT, WPARAM(tape.hLegend2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_LEGEND, WM_SETFONT, WPARAM(tape.hLegend3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_LEGEND1, WM_SETFONT, WPARAM(tape.hLegend4), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_LEGEND2, WM_SETFONT, WPARAM(tape.hLegend4), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_LEGEND3, WM_SETFONT, WPARAM(tape.hLegend4), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_LEGEND4, WM_SETFONT, WPARAM(tape.hLegend4), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_HID_LEGEND5, WM_SETFONT, WPARAM(tape.hLegend4), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_ACTIVE), I18N.HID_ACTIVE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_VJOY_SHUTDOWN), I18N.HID_VJOY_SHUTDOWN);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_WHEN_EXITING), I18N.HID_WHEN_EXITING);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_BLACKLIST), I18N.HID_BLACKLIST);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_REMOVE), I18N.HID_REMOVE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_WHITELIST), I18N.HID_WHITELIST);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_PURGE), I18N.HID_PURGE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_INSTALL), I18N.HID_INSTALL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_GUARDIAN_INSTALL), I18N.HID_GUARDIAN_INSTALL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_GUARDIAN_STATUS), I18N.HID_GUARDIAN_STATUS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_CERBERUS_INSTALL), I18N.HID_CERBERUS_INSTALL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_CERBERUS_STATUS), I18N.HID_CERBERUS_STATUS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_LEGEND), I18N.HID_LEGEND);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_LEGEND2), I18N.HID_LEGEND2);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_LEGEND1), I18N.HID_LEGEND1);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_LEGEND3), I18N.HID_LEGEND3);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_LEGEND4), I18N.HID_LEGEND4);
	SetWindowText(GetDlgItem(m_hDlg, IDC_HID_LEGEND5), I18N.HID_LEGEND5);

	LITEM item{};
	ZeroMemory(&item, sizeof(item));
	item.mask = LIF_ITEMINDEX | LIF_ITEMID | LIF_URL | LIF_STATE;
	item.state = LIS_ENABLED | LIS_FOCUSED | LIS_HOTTRACK;
	item.stateMask = LIS_ENABLED | LIS_FOCUSED | LIS_HOTTRACK;

	SendMessage(GetDlgItem(m_hDlg, IDC_HID_CERBERUS_LINK), LM_GETITEM, 0, (LPARAM)&item);
	//wcscpy_s(item.szID, MAX_LINKID_TEXT, I18N.HID_CERBERUS_LINK);
	wcscpy_s(item.szUrl, L_MAX_URL_LENGTH, I18N.HID_CERBERUS_URL);
	SendMessage(GetDlgItem(m_hDlg, IDC_HID_CERBERUS_LINK), LM_SETITEM, 0, (LPARAM)&item);
	Hide();
}

void GuardianDlg::_InitDialog(HWND hWnd)
{

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void GuardianDlg::_ShowWindow(HWND hWnd)
{
	CheckDlgButton(hWnd, IDC_HID_ACTIVE_CHK, tape.GuardianActive);
	CheckDlgButton(hWnd, IDC_HID_VJOY_SHUTDOWN_CHK, tape.vJoyShutDown);
	CheckDlgButton(hWnd, IDC_HID_REMOVE_CHK, tape.RemoveBlacklist);
	CheckDlgButton(hWnd, IDC_HID_PURGE_CHK, tape.PurgeWhitelist);
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
}

INT_PTR CALLBACK GuardianDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GuardianDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<GuardianDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<GuardianDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR GuardianDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		DWORD CtrlID = GetDlgCtrlID((HWND)lParam);
		SetBkMode(hdcStatic, TRANSPARENT);

		switch (hid.GetHidGState())
		{
		case -1:
		case 0:
		{
			if (CtrlID == IDC_HID_GUARDIAN_INSTALL) return (LRESULT)tape.hB_Not_Installed;
			if (CtrlID == IDC_HID_GUARDIAN_STATUS) return (LRESULT)tape.hB_Not_Installed;
			break;
		}
		case 1:
		{
			if (CtrlID == IDC_HID_GUARDIAN_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_GUARDIAN_STATUS)
			{
				if (status2lock)
					return (LRESULT)tape.hB_Paused;
				else
					return (LRESULT)tape.hB_Running;
			}
			break;
		}
		case 2:
		{
			if (CtrlID == IDC_HID_GUARDIAN_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_GUARDIAN_STATUS) return (LRESULT)tape.hB_Paused;
			break;
		}
		}
		switch (hid.GetHidCState())
		{
		case -1:
		case 0:
		{
			if (CtrlID == IDC_HID_CERBERUS_INSTALL) return (LRESULT)tape.hB_Not_Installed;
			if (CtrlID == IDC_HID_CERBERUS_STATUS) return (LRESULT)tape.hB_Not_Installed;
			break;
		}
		case 2:
		case 4:
		case 5:
		{
			if (CtrlID == IDC_HID_CERBERUS_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_CERBERUS_STATUS) return (LRESULT)tape.hB_Running;
			break;
		}
		case 1:
		case 3:
		{
			if (CtrlID == IDC_HID_CERBERUS_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_CERBERUS_STATUS) return (LRESULT)tape.hB_Stopped;
			break;
		}
		case 6:
		case 7:
		{
			if (CtrlID == IDC_HID_CERBERUS_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_HID_CERBERUS_STATUS) return (LRESULT)tape.hB_Paused;
			break;
		}
		}
		return (LRESULT)tape.hB_neutral;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		switch (GetDlgCtrlID((HWND)lParam))
		{
		case IDC_HID_ACTIVE_CHK:
		case IDC_HID_VJOY_SHUTDOWN_CHK:
		case IDC_HID_HID2_ENABLE:
		case IDC_HID_HID3_ENABLE:
		case IDC_HID_REMOVE_CHK:
		case IDC_HID_EXE1_ENABLE:
		case IDC_HID_EXE2_ENABLE:
		case IDC_HID_EXE3_ENABLE:
		case IDC_HID_EXE4_ENABLE:
		case IDC_HID_EXE5_ENABLE:
		case IDC_HID_PURGE_CHK: { SetTextColor(hdcStatic, tape.ink_STATIC_Checkbox2); break; }
		case IDC_HID_ACTIVE:
		case IDC_HID_VJOY_SHUTDOWN:
		case IDC_HID_WHEN_EXITING:
		case IDC_HID_REMOVE:
		case IDC_HID_PURGE: { SetTextColor(hdcStatic, tape.ink_STATIC_Checkbox); break; }
		default: { SetTextColor(hdcStatic, tape.ink_STATIC); break; }
		}
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

			SetRect(&rect, 317, 111, 330, 122);
			FillRect(hDC, &rect, tape.hB_Not_Installed);

			SetRect(&rect, 317, 127, 330, 138);
			FillRect(hDC, &rect, tape.hB_Running);
			
			SetRect(&rect, 369, 111, 382, 122);
			FillRect(hDC, &rect, tape.hB_Stopped);
			
			SetRect(&rect, 369, 127, 382, 138);
			FillRect(hDC, &rect, tape.hB_Paused);

			LPCWSTR b1Text = I18N.STATE_WAITING;
			LPCWSTR b2Text = I18N.STATE_WAITING;
			LPCWSTR b3Text = I18N.STATE_WAITING;
			LPCWSTR b4Text = I18N.STATE_WAITING;
			SetTextColor(hDC, tape.ink_BTN_Install);
			switch (hid.GetHidGState())
			{
			case -1:
			case 0:
			{
				b1Text = I18N.STATE_INSTALL;
				b2Text = L"";
				break;
			}
			case 1:
			{
				b1Text = I18N.STATE_UNINSTALL;
				b2Text = I18N.STATE_RESTART;
				break;
			}
			case 2:
			{
				b1Text = I18N.STATE_UNINSTALL;
				b2Text = I18N.STATE_ENABLE;
				break;
			}
			}
			switch (hid.GetHidCState())
			{
			case -1:
			case 0:
			{
				b3Text = I18N.STATE_INSTALL;
				b4Text = L"";
				break;
			}
			case 2:
			case 4:
			case 5:
			{
				b3Text = I18N.STATE_UNINSTALL;
				b4Text = I18N.STATE_STOP;
				break;
			}
			case 1:
			case 3:
			{
				b3Text = I18N.STATE_UNINSTALL;
				b4Text = I18N.STATE_START;
				break;
			}
			case 6:
			case 7:
			{
				b3Text = I18N.STATE_UNINSTALL;
				b4Text = I18N.STATE_START;
				break;
			}
			}

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_HID_GUARDIAN_INSTALL), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_HID_GUARDIAN_INSTALL), &rect);
			SelectObject(hDC, tape.hButton2);
			DrawText(hDC, b1Text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_HID_GUARDIAN_STATUS), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_HID_GUARDIAN_STATUS), &rect);
			SelectObject(hDC, tape.hButton2);
			DrawText(hDC, b2Text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_HID_CERBERUS_INSTALL), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_HID_CERBERUS_INSTALL), &rect);
			SelectObject(hDC, tape.hButton2);
			DrawText(hDC, b3Text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_HID_CERBERUS_STATUS), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_HID_CERBERUS_STATUS), &rect);
			SelectObject(hDC, tape.hButton2);
			DrawText(hDC, b4Text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE || lParam == 3)
		{
			hid.HidStates();
			SetActiveWindow(m_hWnd);
		}
		if (wParam == TRUE)
			std::thread(&GuardianDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&GuardianDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_CUSTOMDRAW:
		{
			LPNMCUSTOMDRAW DrawMenuCustom = (LPNMCUSTOMDRAW)lParam;
			DrawMenuCustom->rc.right = DrawMenuCustom->rc.left + 12;
			DrawMenuCustom->rc.bottom = DrawMenuCustom->rc.top + 12;

			RECT rect;
			rect.left = DrawMenuCustom->rc.left + 1;
			rect.right = rect.left + 11;
			rect.top = DrawMenuCustom->rc.top + 1;
			rect.bottom = rect.top + 11;

			switch (((LPNMHDR)lParam)->idFrom)
			{
			case IDC_HID_ACTIVE_CHK:
			case IDC_HID_VJOY_SHUTDOWN_CHK:
			case IDC_HID_HID1_ENABLE:
			case IDC_HID_HID2_ENABLE:
			case IDC_HID_HID3_ENABLE:
			case IDC_HID_REMOVE_CHK:
			case IDC_HID_EXE1_ENABLE:
			case IDC_HID_EXE2_ENABLE:
			case IDC_HID_EXE3_ENABLE:
			case IDC_HID_EXE4_ENABLE:
			case IDC_HID_EXE5_ENABLE:
			case IDC_HID_PURGE_CHK:
			{
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
			}
			break;
		}
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
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_HID_ACTIVE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.GuardianActive = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_GuardianActive);
				PostMessage(m_hWnd, WM_CHANGE_HIDS, 0, 0);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_HID_VJOY_SHUTDOWN_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.vJoyShutDown = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_vJoyShutDown);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_HID_HID1:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.dsHID1, buf) != 0)
				{
					tape.setPID(buf, 1);
					tape.Save(tape.Setting_dsHID1);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 1);
				}
				break;
			}
			}
			break;
		}
		case IDC_HID_HID2:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.dsHID2, buf) != 0)
				{
					tape.setPID(buf, 2);
					tape.Save(tape.Setting_dsHID2);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 2);
				}
				break;
			}
			}
			break;
		}
		case IDC_HID_HID3:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.dsHID3, buf) != 0)
				{
					tape.setPID(buf, 3);
					tape.Save(tape.Setting_dsHID3);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 3);
				}
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE1:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.Exe1Name, buf) != 0)
				{
					tape.setExeName(buf, 1);
					tape.Save(tape.Setting_Exe1Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 1);
				}
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE2:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.Exe2Name, buf) != 0)
				{
					tape.setExeName(buf, 2);
					tape.Save(tape.Setting_Exe2Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 2);
				}
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE3:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.Exe3Name, buf) != 0)
				{
					tape.setExeName(buf, 3);
					tape.Save(tape.Setting_Exe3Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 3);
				}
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE4:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.Exe4Name, buf) != 0)
				{
					tape.setExeName(buf, 4);
					tape.Save(tape.Setting_Exe4Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 4);
				}
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE5:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				if (lstrcmpW(tape.Exe5Name, buf) != 0)
				{
					tape.setExeName(buf, 5);
					tape.Save(tape.Setting_Exe5Name);
					PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 5);
				}
				break;
			}
			}
			break;
		}
		case IDC_HID_REMOVE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.RemoveBlacklist = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_RemoveBlacklist);
				break;
			}
			}
			break;
		}
		case IDC_HID_PURGE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.PurgeWhitelist = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_PurgeWhitelist);
				break;
			}
			}
			break;
		}
		case IDC_HID_HID1_ENABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.dsHID1Enable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_dsHID1Enable);
				PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 1);
				break;
			}
			}
			break;
		}
		case IDC_HID_HID2_ENABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.dsHID2Enable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_dsHID2Enable);
				PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 2);
				break;
			}
			}
			break;
		}
		case IDC_HID_HID3_ENABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.dsHID3Enable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_dsHID3Enable);
				PostMessage(m_hWnd, WM_CHANGE_HIDS, 1, 3);
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE1_ENABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.Exe1NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_Exe1NameEnable);
				PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 1);
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE2_ENABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.Exe2NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_Exe2NameEnable);
				PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 2);
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE3_ENABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.Exe3NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_Exe3NameEnable);
				PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 3);
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE4_ENABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.Exe4NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_Exe4NameEnable);
				PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 4);
				break;
			}
			}
			break;
		}
		case IDC_HID_EXE5_ENABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.Exe5NameEnable = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_Exe5NameEnable);
				PostMessage(m_hWnd, WM_CHANGE_HIDS, 2, 5);
				break;
			}
			}
			break;
		}
		case IDC_HID_GUARDIAN_INSTALL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (guardianlock)
					break;

				guardianlock = true;
				int HidGState = hid.GetHidGState();
				hid.HidStates();
				if (HidGState == hid.GetHidGState())
				{
					switch (HidGState)
					{
					case -1:
					case 0:
					{
						hid.GuardianInstall();
						break;
					}
					case 1:
					case 2:
					{
						hid.GuardianUninstall();
						break;
					}
					}
				}
				hid.HidStates();
				Hide();
				Show();
				guardianlock = false;
				break;
			}
			}
			break;
		}
		case IDC_HID_GUARDIAN_STATUS:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (statuslock)
					break;

				statuslock = true;
				int HidGState = hid.GetHidGState();
				hid.HidStates();
				if (HidGState == hid.GetHidGState())
				{
					switch (HidGState)
					{
					case 1:
						hid.AllDevicesRestart();
						break;
					case 2:
						hid.GuardianEnable();
						break;
					}
				}
				hid.HidStates();
				Hide();
				Show();
				statuslock = false;
				break;
			}
			}
			break;
		}
		case IDC_HID_CERBERUS_INSTALL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (cerberuslock)
					break;

				cerberuslock = true;
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
				Hide();
				Show();
				cerberuslock = false;
				break;
			}
			}
			break;
		}
		case IDC_HID_CERBERUS_STATUS:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (status2lock)
					break;

				status2lock = true;
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
				Hide();
				Show();
				status2lock = false;
				break;
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
	return TRUE;
}

void GuardianDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void GuardianDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL GuardianDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return  ::MoveWindow(m_hDlg, x, y, w, h, r);
}
