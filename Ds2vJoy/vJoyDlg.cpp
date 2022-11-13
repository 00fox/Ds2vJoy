#include "stdafx.h"
#include "vJoyDlg.h"

vJoyDlg::vJoyDlg()
{
}

vJoyDlg::~vJoyDlg()
{
}

void vJoyDlg::Init()
{
	m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_VJOY), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));
	Hide();
	SendDlgItemMessage(m_hDlg, IDC_VJOY_AXIS, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_X, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_Y, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_Z, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_RX, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_RY, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_RZ, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_SL0, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_SL1, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_X, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_Y, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_Z, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_RX, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_RY, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_RZ, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_SL0, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_SL1, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_BTN, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_NBTN, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_POV, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_POV_LST, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_POV_DIRS, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_POV_DIRS_DESC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_POV_CONT_DESC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_POV_CONT, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_FFB_CHK, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_FFB_DESC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_CONST, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_RAMP, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_SQUARE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_SINE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_TRI, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_STUP, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_STDN, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_SPRING, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_DAMPER, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_INERTIA, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CHK_FFB_FRICTION, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_CONST, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_RAMP, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_SQUARE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_SINE, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_TRI, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_STUP, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_STDN, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_SPRING, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_DAMPER, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_INERTIA, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DESC_FFB_FRICTION, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_1, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_2, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_3, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_4, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_5, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_6, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_7, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_8, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_9, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_10, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_11, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_12, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_13, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_14, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_15, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVICE_16, WM_SETFONT, WPARAM(tape.hButton3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CANCEL, WM_SETFONT, WPARAM(tape.hCancel), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_DEVNUMBER, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0)); 
	SendDlgItemMessage(m_hDlg, IDC_VJOY_CTRLPANEL, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_APPLY, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_ADDDEL, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VJOY_RESET, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_AXIS), I18N.VJOY_AXIS);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_X), I18N.VJOY_CHK_X);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_Y), I18N.VJOY_CHK_Y);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_Z), I18N.VJOY_CHK_Z);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_RX), I18N.VJOY_CHK_RX);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_RY), I18N.VJOY_CHK_RY);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_RZ), I18N.VJOY_CHK_RZ);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_SL0), I18N.VJOY_CHK_SL0);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_SL1), I18N.VJOY_CHK_SL1);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_BTN), I18N.VJOY_BTN);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_POV), I18N.VJOY_POV);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_POV_DIRS_DESC), I18N.VJOY_POV_DESC);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_POV_CONT_DESC), I18N.VJOY_POV_CONT);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_FFB_DESC), I18N.VJOY_FFB);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_CONST), I18N.VJOY_CHK_FFB_CONST);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_RAMP), I18N.VJOY_CHK_FFB_RAMP);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_SQUARE), I18N.VJOY_CHK_FFB_SQUARE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_SINE), I18N.VJOY_CHK_FFB_SINE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_TRI), I18N.VJOY_CHK_FFB_TRI);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_STUP), I18N.VJOY_CHK_FFB_STUP);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_STDN), I18N.VJOY_CHK_FFB_STDN);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_SPRING), I18N.VJOY_CHK_FFB_SPRING);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_DAMPER), I18N.VJOY_CHK_FFB_DAMPER);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_INERTIA), I18N.VJOY_CHK_FFB_INERTIA);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DESC_FFB_FRICTION), I18N.VJOY_CHK_FFB_FRICTION);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_1), I18N.VJOY_DEVICE_1);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_2), I18N.VJOY_DEVICE_2);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_3), I18N.VJOY_DEVICE_3);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_4), I18N.VJOY_DEVICE_4);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_5), I18N.VJOY_DEVICE_5);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_6), I18N.VJOY_DEVICE_6);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_7), I18N.VJOY_DEVICE_7);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_8), I18N.VJOY_DEVICE_8);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_9), I18N.VJOY_DEVICE_9);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_10), I18N.VJOY_DEVICE_10);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_11), I18N.VJOY_DEVICE_11);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_12), I18N.VJOY_DEVICE_12);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_13), I18N.VJOY_DEVICE_13);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_14), I18N.VJOY_DEVICE_14);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_15), I18N.VJOY_DEVICE_15);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVICE_16), I18N.VJOY_DEVICE_16);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_CANCEL), I18N.VJOY_CANCEL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVNUMBER), (I18N.VJOY_DEVNUMBER + std::to_wstring(m_device + 1)).c_str());
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_CTRLPANEL), I18N.VJOY_CTRLPANEL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_APPLY), I18N.VJOY_APPLY);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_ADDDEL), I18N.VJOY_ADDDEL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_RESET), I18N.VJOY_RESET);
}

void vJoyDlg::_InitDialog(HWND hWnd)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	// Create a vector device objects
	// Vector item n points at vJoy object with id=n+1
	vJoyDevice.clear();
	for (auto i = 1; i <= MAX_N_DEVICES; i++)
	{
		CvJoyDevice* d = new CvJoyDevice(i);
		vJoyDevice.push_back(d);
	};

	// Initialize number-of-POVs list box
	SendMessage(GetDlgItem(hWnd, IDC_VJOY_POV_LST), LB_INSERTSTRING, -1, (LPARAM)TEXT("0"));
	SendMessage(GetDlgItem(hWnd, IDC_VJOY_POV_LST), LB_INSERTSTRING, -1, (LPARAM)TEXT("1"));
	SendMessage(GetDlgItem(hWnd, IDC_VJOY_POV_LST), LB_INSERTSTRING, -1, (LPARAM)TEXT("2"));
	SendMessage(GetDlgItem(hWnd, IDC_VJOY_POV_LST), LB_INSERTSTRING, -1, (LPARAM)TEXT("3"));
	SendMessage(GetDlgItem(hWnd, IDC_VJOY_POV_LST), LB_INSERTSTRING, -1, (LPARAM)TEXT("4"));
	SendMessage(GetDlgItem(hWnd, IDC_VJOY_POV_LST), LB_SETCURSEL, 0, 0);

	// Select default POV type (IDC_VJOY_POV_CONT)
	SendMessage(GetDlgItem(hWnd, IDC_VJOY_POV_CONT), BM_SETCHECK, BST_CHECKED, 0);

	GetFfbState();
	OnSelChanged();

	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void vJoyDlg::_ShowWindow(HWND hWnd)
{
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_DEVNUMBER), (I18N.VJOY_DEVNUMBER + std::to_wstring(m_device + 1)).c_str());
}

INT_PTR CALLBACK vJoyDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	vJoyDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<vJoyDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<vJoyDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR vJoyDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		case IDC_VJOY_AXIS:
		case IDC_VJOY_BTN:
		case IDC_VJOY_POV:
		case IDC_VJOY_FFB_DESC:
		{
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_DARK);
				return (LRESULT)tape.hB_EDIT_DARK2;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_STATIC);
				return (LRESULT)tape.hB_EDIT;
			}
		}
		default:
		{
			if (tape.DarkTheme)
			{
				SetTextColor(hdcStatic, tape.ink_BTN_Light);
				return (LRESULT)tape.hB_BackGround_DARK;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_CHK);
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

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
			std::thread(&vJoyDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&vJoyDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_TIMER:
	{
		if (wParam == 1)
		{
			// Calculate the FFB State
			GetFfbState();

			// Enable controls of the top dialog box
			EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_RESET), TRUE);

			// Update the selected tab
			OnSelChanged();

			KillTimer(hWnd, 1);
			Hide();
			Show();
			break;
		}
		break;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_VJOY_DEVICE_1:
		case IDC_VJOY_DEVICE_2:
		case IDC_VJOY_DEVICE_3:
		case IDC_VJOY_DEVICE_4:
		case IDC_VJOY_DEVICE_5:
		case IDC_VJOY_DEVICE_6:
		case IDC_VJOY_DEVICE_7:
		case IDC_VJOY_DEVICE_8:
		case IDC_VJOY_DEVICE_9:
		case IDC_VJOY_DEVICE_10:
		case IDC_VJOY_DEVICE_11:
		case IDC_VJOY_DEVICE_12:
		case IDC_VJOY_DEVICE_13:
		case IDC_VJOY_DEVICE_14:
		case IDC_VJOY_DEVICE_15:
		case IDC_VJOY_DEVICE_16:
		{
			switch (((LPNMHDR)lParam)->code)
			{
			case NM_CUSTOMDRAW:
			{
				LPNMCUSTOMDRAW DrawListCustom = (LPNMCUSTOMDRAW)lParam;
				switch (DrawListCustom->dwDrawStage)
				{
				case CDDS_PREPAINT:
				{
					SetBkMode(DrawListCustom->hdc, TRANSPARENT);
					if (IsDlgButtonChecked(hWnd, ((LPNMHDR)lParam)->idFrom))
					{
						SelectObject(DrawListCustom->hdc, GetStockObject(DC_PEN));
						SetDCPenColor(DrawListCustom->hdc, tape.ink_grey);
						RoundRect(DrawListCustom->hdc, DrawListCustom->rc.left + 1, DrawListCustom->rc.top + 1, DrawListCustom->rc.right - 1, DrawListCustom->rc.bottom - 1, 6, 6);
					}
					return CDRF_DODEFAULT;
				}
				}
			}
			}
			break;
		}
		case IDC_VJOY_CANCEL:
		case IDC_VJOY_CTRLPANEL:
		case IDC_VJOY_ADDDEL:
		case IDC_VJOY_RESET:
		case IDC_VJOY_APPLY:
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
		case IDC_VJOY_CANCEL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				Changed = false;
				EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_APPLY), Changed);
				PostMessage(tape.Ds2hWnd, WM_SETVJOY, 0, 1);
				break;
			}
			}
			break;
		}
		case IDC_VJOY_CTRLPANEL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				WCHAR* process = WCHARI(L"rundll32.exe shell32.dll,Control_RunDLL joy.cpl");
				LaunchProcess(process);
				break;
			}
			}
			break;
		}
		case IDC_VJOY_ADDDEL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				// Test if it exists and act
				if (vJoyDevice[m_device]->Exists())
				{
					// Delete from registry
					HKEY hParams;
					LONG RegRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_PARAM, 0, KEY_ALL_ACCESS, &hParams);
					if (RegRes != ERROR_SUCCESS)
						return FALSE;	// Error

					// Create target key string from target number
					WCHAR RegParam[sizeof(REG_PARAM_DEV) + 3] = { 0 };
					swprintf_s(RegParam, sizeof(REG_PARAM_DEV) + 3, REG_PARAM_DEV  L"%02d", m_device + 1);
					LPCWSTR lpRegParam = RegParam;

					// Delete
					if (lpRegParam)
						RegDeleteTree(HKEY_LOCAL_MACHINE, lpRegParam);

					RegCloseKey(hParams);

					// Refresh Tab
					m_device = 0;

					// Refresh
					SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_DISABLE, false);
					SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_ENABLE, false);

					// Refresh Tab
					SetTimer(hWnd, 1, 1000, NULL);
				}
				else
				{
					// Apply default configuration
					PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDC_VJOY_APPLY, BN_CLICKED), 0);
				}
				break;
			}
			}
			break;
		}
		case IDC_VJOY_RESET:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				RECT win;
				GetWindowRect(tape.Ds2hWnd, &win);
				if (MessageBoxPos(hWnd, I18N.VJOY_RESET_CONFIRM, I18N.APP_TITLE, MB_YESNO, win.left + 160, win.top + 60) == IDNO)
					break;

				/* Open registry - Most of the path should exist */
				HKEY hParams;
				LONG RegRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_PARAM, 0, KEY_ALL_ACCESS, &hParams);
				if (RegRes != ERROR_SUCCESS)
					return FALSE;	// Error

				for (int i = 1; i <= 16; i++)
				{
					// Create target key string from target number
					WCHAR RegParam[sizeof(REG_PARAM_DEV) + 3] = { 0 };
					swprintf_s(RegParam, sizeof(REG_PARAM_DEV) + 3, REG_PARAM_DEV  L"%02d", i);
					LPCWSTR lpRegParam = RegParam;

					// Delete
					if (lpRegParam)
						RegDeleteTree(HKEY_LOCAL_MACHINE, lpRegParam);
				};

				RegCloseKey(hParams);

				// Select First device tab
				m_device = 0;

				// Disable Apply button
				Changed = false;
				EnableWindow(GetDlgItem(hWnd, IDC_VJOY_APPLY), Changed);

				// Refresh
				SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_DISABLE, false);
				SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_ENABLE, false);

				// Refresh Tab
				SetTimer(hWnd, 1, 1000, NULL);
			}
			}
			break;
		}
		case IDC_VJOY_APPLY:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				bool AxisChecked[8] = { 0 };
				int nPovHatsCont = 0, nPovHatsDir = 0, nButtons = 0;
				bool FfbEn = false;

				// Get changed (current) state
				GetCtrlState(hWnd, &AxisChecked[0], &nPovHatsCont, &nPovHatsDir, &nButtons, &FfbEn);

				///////// Create HID Report Descriptor and load it to the registry                  /////////////////
				///////// We do it twice - once without the FFB section for backwords compatibility ///////////////// 
				///////// Second time (If FFB enabled) with the FFB section

				// Call external C-function that creats an array of bytes that holds
				// the HID Report Descriptor

				/* Create a data buffer large enough to hold the resulting HID Report Descriptor */
				//int buffer_size = 1023;
				static std::vector<BYTE> buffer;
				buffer.clear();
				int desc_size = 0;
				
				/* normalize if illegal parameters are passed */
				// Buttons: 0-128
				if (nButtons > 128)
					nButtons = 128;

				/* Special case of zero buttons - Local Min Usage is 0 rather than 1 */
				UINT localminusage_buttons = nButtons ? 0x01 : 0x00;

				// POV (Cont): 0-4
				if (nPovHatsCont < 0)
					nPovHatsCont = 0;
				if (nPovHatsCont > 4)
					nPovHatsCont = 4;
				// POV (Dir): 0-4
				if (nPovHatsDir < 0)
					nPovHatsDir = 0;
				if (nPovHatsDir > 4)
					nPovHatsDir = 4;

				/* Create standard header */
				NEXT_BYTE(buffer, HIDP_GLOBAL_USAGE_PAGE_1)		// USAGE_PAGE(Generic Desktop):		05 01
				NEXT_BYTE(buffer, HID_USAGE_PAGE_GENERIC)
				NEXT_BYTE(buffer, HIDP_GLOBAL_LOG_MIN_1)		// LOGICAL_MINIMUM(0):				15 00
				NEXT_BYTE(buffer, 0)
				NEXT_BYTE(buffer, HIDP_LOCAL_USAGE_1)			// USAGE (Joystick):				09 04
				NEXT_BYTE(buffer, HID_USAGE_GENERIC_JOYSTICK)
				NEXT_BYTE(buffer, HIDP_MAIN_COLLECTION)			// COLLECTION( Application):		A1 01
				NEXT_BYTE(buffer, HIDP_MAIN_COLLECTION_APP)

				/* Collection 1 */
				NEXT_BYTE(buffer, HIDP_GLOBAL_USAGE_PAGE_1)		// USAGE_PAGE(Generic Desktop):		05 01
				NEXT_BYTE(buffer, HID_USAGE_PAGE_GENERIC)
				NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_ID)		// REPORT_ID (x)					85 ID
				NEXT_BYTE(buffer, int(m_device + 1))
				NEXT_BYTE(buffer, HIDP_LOCAL_USAGE_1)			// USAGE(Pointer):					09 01
				NEXT_BYTE(buffer, HID_USAGE_GENERIC_POINTER)
				NEXT_BYTE(buffer, HIDP_GLOBAL_LOG_MIN_1)		// LOGICAL_MINIMUM(0):				15 00
				NEXT_BYTE(buffer, 0)
				NEXT_BYTE(buffer, HIDP_GLOBAL_LOG_MAX_2)		// LOGICAL_MAXIMUM(32767):			26 FF 7F
				NEXT_SHORT(buffer, 0x7FFF)
				NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_SIZE)		// REPORT_SIZE(32):					75 20
				NEXT_BYTE(buffer, 0x20)
				NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_COUNT_1)	// REPORT_COUNT(1):					95 01
				NEXT_BYTE(buffer, 0x01)
				NEXT_BYTE(buffer, HIDP_MAIN_COLLECTION)			// COLLECTION(Physical):			A1 00
				NEXT_BYTE(buffer, 0x00)

				/** Collection 2 **/
				/* Loop on fitst 8 Axes */
				for (int i = 0; i < 8; i++)
				{
					if (AxisChecked[i])
					{
						// Insert Axis
						NEXT_BYTE(buffer, HIDP_LOCAL_USAGE_1)			// USAGE(X+offset):			0x09 0x30+i
						NEXT_BYTE(buffer, HID_USAGE_GENERIC_X + i)
						NEXT_BYTE(buffer, HIDP_MAIN_INPUT_1)		// INPUT (Data,Var,Abs):	0x81 0x02
						NEXT_BYTE(buffer, 0x02)
					}
					else
					{
						// Insert place holder
						NEXT_BYTE(buffer, HIDP_MAIN_INPUT_1)			// INPUT (Cnst,Ary,Abs):	0x81 0x01
						NEXT_BYTE(buffer, 0x01)
					};
				};
				NEXT_BYTE(buffer, HIDP_MAIN_ENDCOLLECTION)				// END_COLLECTION:			0xC0

				if (nPovHatsDir)
				{
					// POV - supported: One switch at most, 5-state only
					NEXT_BYTE(buffer, HIDP_GLOBAL_LOG_MIN_1)			// LOGICAL_MINIMUM(0):		15 00
					NEXT_BYTE(buffer, 0x00)
					NEXT_BYTE(buffer, HIDP_GLOBAL_LOG_MAX_1)		// LOGICAL_MAXIMUM(3):		25 03
					NEXT_BYTE(buffer, 0x03)
					NEXT_BYTE(buffer, HIDP_GLOBAL_PHY_MIN_1)		// PHYSICAL_MINIMUM (0):	35 00
					NEXT_BYTE(buffer, 0x00)
					NEXT_BYTE(buffer, HIDP_GLOBAL_PHY_MAX_2)		// PHYSICAL_MAXIMUM (270):	46 0e 01
					NEXT_SHORT(buffer, 0x010e)
					NEXT_BYTE(buffer, HIDP_GLOBAL_UNIT_1)			// UNIT (Eng Rot:Angular Pos):	65 14
					NEXT_BYTE(buffer, 0x14)
					// One 4-bit data  + 31 4-bit padding
					NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_SIZE)		// REPORT_SIZE(4):			75 04
					NEXT_BYTE(buffer, 0x04)
					NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_COUNT_1)	// REPORT_COUNT(1):			95 01
					NEXT_BYTE(buffer, 0x01)

					// Insert 1-4 5-state POVs
					for (int i = 1; i <= nPovHatsDir; i++)
					{
						NEXT_BYTE(buffer, HIDP_LOCAL_USAGE_1)		// USAGE(Hat switch):		0x09 0x39
						NEXT_BYTE(buffer, HID_USAGE_GENERIC_HATSWITCH)
						NEXT_BYTE(buffer, HIDP_MAIN_INPUT_1)	// INPUT (Data,Var,Abs):	0x81 0x02
						NEXT_BYTE(buffer, 0x02)
					};

					// Insert 5-state POV place holders
					NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_COUNT_1)	// REPORT_COUNT(31):			95 1F
					NEXT_BYTE(buffer, 0x20 - nPovHatsDir)
					NEXT_BYTE(buffer, HIDP_MAIN_INPUT_1)			// INPUT (Cnst,Ary,Abs):		0x81 0x01
					NEXT_BYTE(buffer, 0x01)
				}
				else if (nPovHatsCont)
				{
					// Continuous POV
					NEXT_BYTE(buffer, HIDP_GLOBAL_LOG_MIN_1)		// LOGICAL_MINIMUM(0):			15 00
					NEXT_BYTE(buffer, 0x00)
					NEXT_BYTE(buffer, HIDP_GLOBAL_LOG_MAX_4)		// LOGICAL_MAXIMUM(35900):		27 3c 8c 00 00
					NEXT_SHORT(buffer, 0x8C3C)
					NEXT_SHORT(buffer, 0x0000)
					NEXT_BYTE(buffer, HIDP_GLOBAL_PHY_MIN_1)		// PHYSICAL_MINIMUM (0):		35 00
					NEXT_BYTE(buffer, 0x00)
					NEXT_BYTE(buffer, HIDP_GLOBAL_PHY_MAX_4)		// PHYSICAL_MAXIMUM (35900):	47 3c 8c 00 00
					NEXT_SHORT(buffer, 0x8C3C)
					NEXT_SHORT(buffer, 0x0000)
					NEXT_BYTE(buffer, HIDP_GLOBAL_UNIT_1)			// UNIT (Eng Rot:Angular Pos):	65 14
					NEXT_BYTE(buffer, 0x14)
					NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_SIZE)		// REPORT_SIZE(32):				75 20
					NEXT_BYTE(buffer, 0x20)
					NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_COUNT_1)	// REPORT_COUNT(1):				95 01
					NEXT_BYTE(buffer, 0x01)

					// Insert 1-4 continuous POVs
					for (int i = 1; i <= nPovHatsCont; i++)
					{
						NEXT_BYTE(buffer, HIDP_LOCAL_USAGE_1)			// USAGE(Hat switch):		0x09 0x39
						NEXT_BYTE(buffer, HID_USAGE_GENERIC_HATSWITCH)
						NEXT_BYTE(buffer, HIDP_MAIN_INPUT_1)			// INPUT (Data,Var,Abs):	0x81 0x02
						NEXT_BYTE(buffer, 0x02)
					};

					// Insert 1-3 continuous POV place holders
					if (nPovHatsCont < 4)
					{
						NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_COUNT_1)	// REPORT_COUNT(3):			95 03
						NEXT_BYTE(buffer, 0x04 - nPovHatsCont)
						NEXT_BYTE(buffer, HIDP_MAIN_INPUT_1)			// INPUT (Cnst,Ary,Abs):	0x81 0x01
						NEXT_BYTE(buffer, 0x01)
					};
				}
				else
				{
					// Sixteen 4-bit padding
					NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_SIZE)		// REPORT_SIZE(32):			75 20
					NEXT_BYTE(buffer, 0x20)
					NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_COUNT_1)	// REPORT_COUNT(4):			95 04
					NEXT_BYTE(buffer, 0x04)
					NEXT_BYTE(buffer, HIDP_MAIN_INPUT_1)			// INPUT (Cnst,Ary,Abs):	0x81 0x01
					NEXT_BYTE(buffer, 0x01)
				};

				// There are buttons
				NEXT_BYTE(buffer, HIDP_GLOBAL_USAGE_PAGE_1)			// USAGE_PAGE(Buttons):		05 09
				NEXT_BYTE(buffer, HID_USAGE_PAGE_BUTTON)
				NEXT_BYTE(buffer, HIDP_GLOBAL_LOG_MIN_1)			// LOGICAL_MINIMUM(0):		15 00
				NEXT_BYTE(buffer, 0x00)
				NEXT_BYTE(buffer, HIDP_GLOBAL_LOG_MAX_1)			// LOGICAL_MAXIMUM(0):		25 01
				NEXT_BYTE(buffer, 0x01)
				NEXT_BYTE(buffer, HIDP_GLOBAL_UNIT_EXP_1)			// UNIT_EXPONENT(0):		55 00
				NEXT_BYTE(buffer, 0x00)
				NEXT_BYTE(buffer, HIDP_GLOBAL_UNIT_1)				// UNIT (None):				65 00
				NEXT_BYTE(buffer, 0x00)
				NEXT_BYTE(buffer, HIDP_LOCAL_USAGE_MIN_1)			// USAGE_MINIMUM(1):		19 01/00
				NEXT_BYTE(buffer, localminusage_buttons)
				NEXT_BYTE(buffer, HIDP_LOCAL_USAGE_MAX_1)			// USAGE_MAXIMUM(nButtons):	29 nButtons
				NEXT_BYTE(buffer, nButtons)
				NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_SIZE)			// REPORT_SIZE(1):			75 01
				NEXT_BYTE(buffer, 0x01)
				NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_COUNT_1)		// REPORT_COUNT(nButtons):	95 nButtons
				NEXT_BYTE(buffer, nButtons)
				NEXT_BYTE(buffer, HIDP_MAIN_INPUT_1)				// INPUT (Data,Var,Abs):	0x81 0x02
				NEXT_BYTE(buffer, 0x02)

				// Padding, if there are less than 32 buttons
				if (nButtons < MAX_BUTTONS)
				{
					NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_SIZE)		// REPORT_SIZE(x):			75 32-nButtons
					NEXT_BYTE(buffer, MAX_BUTTONS - nButtons)
					NEXT_BYTE(buffer, HIDP_GLOBAL_REPORT_COUNT_1)	// REPORT_COUNT(1):			95 nButtons
					NEXT_BYTE(buffer, 0x01)
					NEXT_BYTE(buffer, HIDP_MAIN_INPUT_1)			// INPUT (Cnst,Ary,Abs):	0x81 0x01
					NEXT_BYTE(buffer, 0x01)
				};

				// Insert FFB section to the descriptor if the user chose to
				if (FfbEn)
				{
					std::vector<BYTE>* Vbuffer = &buffer;
					std::vector<BYTE> vars
					{
						static_cast<BYTE>(HID_ID_STATE + 0x10 * BYTE(m_device + 1)),	// Report ID 2
						static_cast<BYTE>(HID_ID_EFFREP + 0x10 * BYTE(m_device + 1)),	// Report ID 1
						static_cast<BYTE>(HID_ID_ENVREP + 0x10 * BYTE(m_device + 1)),	// Report ID 2
						static_cast<BYTE>(HID_ID_CONDREP + 0x10 * BYTE(m_device + 1)),	// Report ID 3
						static_cast<BYTE>(HID_ID_PRIDREP + 0x10 * BYTE(m_device + 1)),	// Report ID 4
						static_cast<BYTE>(HID_ID_CONSTREP + 0x10 * BYTE(m_device + 1)),	// Report ID 5
						static_cast<BYTE>(HID_ID_RAMPREP + 0x10 * BYTE(m_device + 1)),	// Report ID 6
						static_cast<BYTE>(HID_ID_CSTMREP + 0x10 * BYTE(m_device + 1)),	// Report ID 7
						static_cast<BYTE>(HID_ID_SMPLREP + 0x10 * BYTE(m_device + 1)),	// Report ID 8
						static_cast<BYTE>(HID_ID_EFOPREP + 0x10 * BYTE(m_device + 1)),	// Report ID Ah (10d)
						static_cast<BYTE>(HID_ID_BLKFRREP + 0x10 * BYTE(m_device + 1)),	// Report ID Bh (11d)
						static_cast<BYTE>(HID_ID_CTRLREP + 0x10 * BYTE(m_device + 1)),	// Report ID Ch (12d)
						static_cast<BYTE>(HID_ID_GAINREP + 0x10 * BYTE(m_device + 1)),	// Report ID Dh (13d)
						static_cast<BYTE>(HID_ID_SETCREP + 0x10 * BYTE(m_device + 1)),	// Report ID Eh (14d)
						static_cast<BYTE>(HID_ID_NEWEFREP + 0x10 * BYTE(m_device + 1)),	// Report ID 1
						static_cast<BYTE>(HID_ID_BLKLDREP + 0x10 * BYTE(m_device + 1)),	// Report ID 2
						static_cast<BYTE>(HID_ID_POOLREP + 0x10 * BYTE(m_device + 1)),	// Report ID 3
					};

					// Replace the first byte of each sub vector with the corresponding varible (exclude first sub vector)
					// Append modified sub vector to buffer
					Vbuffer->insert(Vbuffer->end(), FfbDescriptor[0].begin(), FfbDescriptor[0].end());
					for (UINT i = 1; i < FfbDescriptor.size(); i++)
					{
						FfbDescriptor[i][0] = vars[i - 1];
						Vbuffer->insert(Vbuffer->end(), FfbDescriptor[i].begin(), FfbDescriptor[i].end());
					}

					HWND h;
					UINT16 mask = 0;

					int cb[]
					{
						IDC_VJOY_CHK_FFB_CONST, IDC_VJOY_CHK_FFB_RAMP, IDC_VJOY_CHK_FFB_SQUARE, IDC_VJOY_CHK_FFB_SINE,
							IDC_VJOY_CHK_FFB_TRI, IDC_VJOY_CHK_FFB_STUP, IDC_VJOY_CHK_FFB_STDN, IDC_VJOY_CHK_FFB_SPRING,
							IDC_VJOY_CHK_FFB_DAMPER, IDC_VJOY_CHK_FFB_INERTIA, IDC_VJOY_CHK_FFB_FRICTION
					};

					for (auto effect : cb)
					{
						bool Checked = false, Enabled = false;
						h = GetDlgItem(m_hDlg, effect);
						if (Button_GetCheck(h) == BST_CHECKED)
							Checked = true;
						Enabled = IsWindowEnabled(h);
						if (Checked && Enabled)
							mask |= 0x01;
						mask = mask << 1;
					};
					mask = mask >> 1;

					int Effect[]{ 0x26, 0x27, 0x30, 0x31, 0x32, 0x33, 0x34, 0x40, 0x41, 0x42, 0x43 };
					BYTE nEff = sizeof(Effect) / sizeof(int);

					// Search for sequence(0x09, 0x25, 0xA1, 0x02)
					for (auto& i : *Vbuffer)
					{
						if ((i == 0x09) && (*std::next(&i, 1) == 0x25) && (*std::next(&i, 2) == 0xA1) && (*std::next(&i, 3) == 0x02))
							// Sequence found - now replace by going over the effects 
							for (BYTE e = 0; e < nEff; e++)
							{
								if ((mask >> (nEff - e - 1)) & 0x01)
									*std::next(&i, 5 + e * 2) = Effect[e];
								else
									*std::next(&i, 5 + e * 2) = 0x29;
							};
					};
				}
				NEXT_BYTE(buffer, HIDP_MAIN_ENDCOLLECTION)			// END_COLLECTION:			0xC0

				desc_size = (int)buffer.size();

				if ((desc_size <= 0))
				{
					RECT win;
					GetWindowRect(tape.Ds2hWnd, &win);
					MessageBoxPos(tape.Ds2hWnd, I18N.VJOY_FAILED, I18N.APP_TITLE, MB_ICONERROR, win.left + 174, win.top + 30);
					return FALSE;
				};

				// Write descriptor to registry
				
				/* Open registry - Most of the path should exist */
				HKEY hParams, hDevDef;
				LONG RegRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_PARAM, 0, KEY_ALL_ACCESS, &hParams);
				if (RegRes != ERROR_SUCCESS)
					return FALSE;	// Error

				LPCWSTR lpRegParam;
				// Create target key string from target number
				WCHAR RegParam[sizeof(REG_PARAM_DEV) + 3] = { 0 };
				swprintf_s(RegParam, sizeof(REG_PARAM_DEV) + 3, REG_PARAM_DEV  L"%02d", (int)(m_device + 1));
				lpRegParam = RegParam;

				// Create Key
				RegRes = RegCreateKey(HKEY_LOCAL_MACHINE, lpRegParam, &hDevDef);
				if (RegRes != ERROR_SUCCESS)
				{
					RegCloseKey(hParams);
					return FALSE;	// Error
				};

				/* Write the data */
				RegRes = RegSetValueEx(hDevDef, DESC_NAME, 0, REG_BINARY, &buffer[0], desc_size);
				if (RegRes != ERROR_SUCCESS)
				{
					RegCloseKey(hParams);
					RegCloseKey(hDevDef);
					return FALSE;	// Error
				};

				/* Write the data Size*/
				DWORD dSize = (DWORD)desc_size;
				RegSetValueEx(hDevDef, DESC_SIZE, 0, REG_DWORD, (const BYTE*)(&dSize), 4);
				RegCloseKey(hParams);
				RegCloseKey(hDevDef);
				
				// Disable Apply button
				Changed = false;
				EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_APPLY), Changed);

				// Refresh
				SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_DISABLE, false);
				SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_ENABLE, false);

				// Refresh Tab
				SetTimer(hWnd, 1, 1000, NULL);
				break;
			}
			}
			break;
		}
		case IDC_VJOY_FFB_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				// Get state of FFB checkbox
				bool Checked = Button_GetCheck(GetDlgItem(m_hDlg, IDC_VJOY_FFB_CHK)) == BST_CHECKED;
				EnableFfbEffectCB(Checked);

				if (Checked)
				{
					if (IsDeviceFfb(m_device + 1))
						UpdateFfbEffectCB(m_device + 1);
					else
					{
						HWND h;
						int cb[]
						{
							IDC_VJOY_CHK_FFB_CONST, IDC_VJOY_CHK_FFB_RAMP, IDC_VJOY_CHK_FFB_SQUARE, IDC_VJOY_CHK_FFB_SINE,
								IDC_VJOY_CHK_FFB_TRI, IDC_VJOY_CHK_FFB_STUP, IDC_VJOY_CHK_FFB_STDN, IDC_VJOY_CHK_FFB_SPRING,
								IDC_VJOY_CHK_FFB_DAMPER, IDC_VJOY_CHK_FFB_INERTIA, IDC_VJOY_CHK_FFB_FRICTION
						};

						for (auto effect : cb)
						{
							h = GetDlgItem(m_hDlg, effect);
							SendMessage(h, BM_SETCHECK, TRUE, 0);
						};
					}
				}
				else
				{
					if (!IsDeviceFfb(m_device + 1))
						ClearFfbEffectCB();
				};
				Changed = true;
				EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_APPLY), Changed);
				break;
			}
			}
			break;
		}
		case IDC_VJOY_CHK_X:
		case IDC_VJOY_CHK_Y:
		case IDC_VJOY_CHK_Z:
		case IDC_VJOY_CHK_RX:
		case IDC_VJOY_CHK_RY:
		case IDC_VJOY_CHK_RZ:
		case IDC_VJOY_CHK_SL0:
		case IDC_VJOY_CHK_SL1:
		case IDC_VJOY_NBTN:
		case IDC_VJOY_POV_LST:
		case IDC_VJOY_POV_DIRS:
		case IDC_VJOY_POV_CONT:
		case IDC_VJOY_CHK_FFB_CONST:
		case IDC_VJOY_CHK_FFB_RAMP:
		case IDC_VJOY_CHK_FFB_SQUARE:
		case IDC_VJOY_CHK_FFB_SINE:
		case IDC_VJOY_CHK_FFB_TRI:
		case IDC_VJOY_CHK_FFB_STUP:
		case IDC_VJOY_CHK_FFB_STDN:
		case IDC_VJOY_CHK_FFB_SPRING:
		case IDC_VJOY_CHK_FFB_DAMPER:
		case IDC_VJOY_CHK_FFB_INERTIA:
		case IDC_VJOY_CHK_FFB_FRICTION:
		{
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
			case CBN_SELCHANGE:
			case BN_CLICKED:
			{
				Changed = true;
				EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_APPLY), Changed);
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 0;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 1;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 2;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 3;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 4;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_6:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 5;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_7:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 6;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_8:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 7;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_9:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 8;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_10:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 9;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_11:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 10;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_12:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 11;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_13:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 12;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_14:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 13;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_15:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 14;
				OnSelChanged();
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VJOY_DEVICE_16:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				m_device = 15;
				OnSelChanged();
				Hide();
				Show();
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

// Enable/Disable tab by tab index (0-based)
void vJoyDlg::EnableTab(bool Enable)
{
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_CHK_X), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_CHK_Y), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_CHK_Z), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_CHK_RX), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_CHK_RY), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_CHK_RZ), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_CHK_SL0), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_CHK_SL1), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_NBTN), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_POV_DIRS), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_POV_CONT), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_POV_LST), Enable);
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_FFB_CHK), Enable);
}

// Read the state of Tab dialog box controls
void vJoyDlg::GetCtrlState(HWND hDlg, bool* AxisArr, int* nPovCont, int* nPovDisc, int* nButtons, bool* Ffb)
{
	// Axes
	AxisArr[0] = (IsDlgButtonChecked(hDlg, IDC_VJOY_CHK_X) == BST_CHECKED);
	AxisArr[1] = (IsDlgButtonChecked(hDlg, IDC_VJOY_CHK_Y) == BST_CHECKED);
	AxisArr[2] = (IsDlgButtonChecked(hDlg, IDC_VJOY_CHK_Z) == BST_CHECKED);
	AxisArr[3] = (IsDlgButtonChecked(hDlg, IDC_VJOY_CHK_RX) == BST_CHECKED);
	AxisArr[4] = (IsDlgButtonChecked(hDlg, IDC_VJOY_CHK_RY) == BST_CHECKED);
	AxisArr[5] = (IsDlgButtonChecked(hDlg, IDC_VJOY_CHK_RZ) == BST_CHECKED);
	AxisArr[6] = (IsDlgButtonChecked(hDlg, IDC_VJOY_CHK_SL0) == BST_CHECKED);
	AxisArr[7] = (IsDlgButtonChecked(hDlg, IDC_VJOY_CHK_SL1) == BST_CHECKED);

	// Number of buttons
	TCHAR nBtnStr[4];
	GetWindowText(GetDlgItem(hDlg, IDC_VJOY_NBTN), nBtnStr, 4);
	_stscanf_s(nBtnStr, TEXT("%d"), nButtons);

	// Number of Continuous POVs
	if (IsDlgButtonChecked(hDlg, IDC_VJOY_POV_CONT) == BST_CHECKED)
		*nPovCont = (int)SendMessage(GetDlgItem(hDlg, IDC_VJOY_POV_LST), LB_GETCURSEL, 0, 0);
	else
		*nPovCont = 0;

	if (IsDlgButtonChecked(hDlg, IDC_VJOY_POV_DIRS) == BST_CHECKED)
		*nPovDisc = (int)SendMessage(GetDlgItem(hDlg, IDC_VJOY_POV_LST), LB_GETCURSEL, 0, 0);
	else
		*nPovDisc = 0;

	// Ffb
	*Ffb = (IsDlgButtonChecked(hDlg, IDC_VJOY_FFB_CHK) == BST_CHECKED);
}

// Called when a tab is selected
void vJoyDlg::OnSelChanged()
{
	// This is a slow function - show a wait cursor
	HCURSOR WaitCursor = LoadCursor(NULL, IDC_WAIT);
	HCURSOR PrevCursor = SetCursor(WaitCursor);

	bool Exist_X = true;
	bool Exist_Y = true;
	bool Exist_Z = true;
	bool Exist_RX = true;
	bool Exist_RY = true;
	bool Exist_RZ = true;
	bool Exist_SL0 = true;
	bool Exist_SL1 = true;
	int nBtn = 32;
	int nDiscPov = 0;
	int nContPov = 0;

	if (vJoyDevice[m_device]->Exists())
	{
		//// Get data from driver
		// Axes
		Exist_X = vJoyDevice[m_device]->AxisExists(HID_USAGE_X);
		Exist_Y = vJoyDevice[m_device]->AxisExists(HID_USAGE_Y);
		Exist_Z = vJoyDevice[m_device]->AxisExists(HID_USAGE_Z);
		Exist_RX = vJoyDevice[m_device]->AxisExists(HID_USAGE_RX);
		Exist_RY = vJoyDevice[m_device]->AxisExists(HID_USAGE_RY);
		Exist_RZ = vJoyDevice[m_device]->AxisExists(HID_USAGE_RZ);
		Exist_SL0 = vJoyDevice[m_device]->AxisExists(HID_USAGE_SL0);
		Exist_SL1 = vJoyDevice[m_device]->AxisExists(HID_USAGE_SL1);

		// Buttons
		nBtn = vJoyDevice[m_device]->GetButtonNumber();

		// POV
		nDiscPov = vJoyDevice[m_device]->GetDiscPovNumber();
		nContPov = vJoyDevice[m_device]->GetContPovNumber();
	};

	//// Write data to User Interface
	// Axes
	CheckDlgButton(m_hDlg, IDC_VJOY_CHK_X, Exist_X);
	CheckDlgButton(m_hDlg, IDC_VJOY_CHK_Y, Exist_Y);
	CheckDlgButton(m_hDlg, IDC_VJOY_CHK_Z, Exist_Z);
	CheckDlgButton(m_hDlg, IDC_VJOY_CHK_RX, Exist_RX);
	CheckDlgButton(m_hDlg, IDC_VJOY_CHK_RY, Exist_RY);
	CheckDlgButton(m_hDlg, IDC_VJOY_CHK_RZ, Exist_RZ);
	CheckDlgButton(m_hDlg, IDC_VJOY_CHK_SL0, Exist_SL0);
	CheckDlgButton(m_hDlg, IDC_VJOY_CHK_SL1, Exist_SL1);

	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_1, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_2, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_3, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_4, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_5, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_6, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_7, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_8, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_9, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_10, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_11, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_12, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_13, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_14, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_15, BST_UNCHECKED);
	CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_16, BST_UNCHECKED);

	switch (m_device)
	{
	case 0: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_1, BST_CHECKED); break;
	case 1: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_2, BST_CHECKED); break;
	case 2: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_3, BST_CHECKED); break;
	case 3: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_4, BST_CHECKED); break;
	case 4: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_5, BST_CHECKED); break;
	case 5: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_6, BST_CHECKED); break;
	case 6: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_7, BST_CHECKED); break;
	case 7: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_8, BST_CHECKED); break;
	case 8: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_9, BST_CHECKED); break;
	case 9: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_10, BST_CHECKED); break;
	case 10: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_11, BST_CHECKED); break;
	case 11: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_12, BST_CHECKED); break;
	case 12: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_13, BST_CHECKED); break;
	case 13: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_14, BST_CHECKED); break;
	case 14: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_15, BST_CHECKED); break;
	case 15: CheckDlgButton(m_hDlg, IDC_VJOY_DEVICE_16, BST_CHECKED); break;
	}
	::SetFocus(NULL);

	// Buttons
	TCHAR nBtnStr[4];
	_stprintf_s(nBtnStr, 4, TEXT("%d"), nBtn);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_NBTN), nBtnStr);

	// POV
	if (nDiscPov)
	{
		SendMessage(GetDlgItem(m_hDlg, IDC_VJOY_POV_DIRS), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(m_hDlg, IDC_VJOY_POV_CONT), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(m_hDlg, IDC_VJOY_POV_LST), LB_SETCURSEL, nDiscPov, 0);
	}
	else
	{
		SendMessage(GetDlgItem(m_hDlg, IDC_VJOY_POV_DIRS), BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(GetDlgItem(m_hDlg, IDC_VJOY_POV_CONT), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(m_hDlg, IDC_VJOY_POV_LST), LB_SETCURSEL, nContPov, 0);
	};

	// FFB
	// Show only for if the device supports FFB 
	// and only for the first 15 tabs
	BOOL FfbSupported = false;
	vJoyFfbCap(&FfbSupported);
	if (m_device >= MAX_N_FFB || !FfbSupported)
	{
		EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_FFB_CHK), FALSE);
		SendMessage(GetDlgItem(m_hDlg, IDC_VJOY_FFB_CHK), BM_SETCHECK, BST_UNCHECKED, 0);
		ClearFfbEffectCB();
	}
	else
	{
		// Show if FFB supported for this device
		if (IsDeviceFfb(m_device + 1))
			SendMessage(GetDlgItem(m_hDlg, IDC_VJOY_FFB_CHK), BM_SETCHECK, BST_CHECKED, 0);
		else
			SendMessage(GetDlgItem(m_hDlg, IDC_VJOY_FFB_CHK), BM_SETCHECK, BST_UNCHECKED, 0);

		if (FfbState == 0) // Prohibited
			EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_FFB_CHK), FALSE);
		else
			EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_FFB_CHK), TRUE);
	};

	// FFB -  Effects
	// If FFB checkbox is checked - Effect checkboxes are enabled
	// If FFB checkbox is unchecked - Effect checkboxes are disabled
	// If Effect Checkboz is enabled then check if effect is configured
	if (vJoyDevice[m_device]->Exists())
		UpdateFfbEffectCB(m_device + 1);
	if (Button_GetCheck(GetDlgItem(m_hDlg, IDC_VJOY_FFB_CHK)) == BST_CHECKED)
		EnableFfbEffectCB(true);
	else
	{
		EnableFfbEffectCB(false);
		ClearFfbEffectCB();
	}

	if ((m_device >= MAX_N_FFB) && (FfbState == 2)) // This is Device 16 + FFB State: Active
	{
		EnableTab(false);
	}

	if (vJoyDevice[m_device]->Exists())
	{
		SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_ADDDEL), I18N.VJOY_DELDEV);
		AddBtn = false;
		EnableTab(true);
	}
	else
	{
		SetWindowText(GetDlgItem(m_hDlg, IDC_VJOY_ADDDEL), I18N.VJOY_ADDDEV);
		AddBtn = true;
		EnableTab(false);
	};

	// If this is the only device then you cannot delete it
	bool isOnlyDevice = true;
	UINT i = 0;
	while (i < (vJoyDevice.size() - 1))
	{
		if (i == m_device)
		{
			if (!vJoyDevice[m_device]->Exists())
				isOnlyDevice = false;
		}
		else
		{
			if (vJoyDevice[i]->Exists())
				isOnlyDevice = false;
		}
		i++;
	};
	if (isOnlyDevice)
		EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_ADDDEL), FALSE);
	else
		EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_ADDDEL), TRUE);

	// If this is Device 16 and FFB State is Active then you cannot add it
	if ((FfbState == 2) && (m_device == 15))
		EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_ADDDEL), FALSE);

	// Apply button is disabled before startting to make changes
	Changed = false;
	EnableWindow(GetDlgItem(m_hDlg, IDC_VJOY_APPLY), Changed);

	SetCursor(PrevCursor);
	//ShowWindow(m_hDlg, SW_SHOW);
}

// Updates Global Variable FfbState
// int FfbState = -1; // 0: Prohibited; 1: Inactive; 2: Active
//
// If device #16 exists (or FFB not supported) - FFB State == Prohibited
// If device #16 does not exist and none of the other devices is FFB - FFB State == Inactive
// If device #16 does not exist and one or more of the other devices is FFB - FFB State == Active
int vJoyDlg::GetFfbState(void)
{
	BOOL FfbSupported = false;
	vJoyFfbCap(&FfbSupported);
	if (!FfbSupported)
	{
		FfbState = 0;
		return 	FfbState;
	};

	// Test if device 16 exists
	int Id = 16;
	if (vJoyDevice[Id - 1]->Exists())
	{
		FfbState = 0;
		return 	FfbState;
	};

	// Test if any of the lower 15 devices supports FFB
	for (int id = 1; id <= MAX_N_FFB; id++)
	{
		if (IsDeviceFfb(id))
		{
			FfbState = 2;
			return 	FfbState;
		};
	}
	FfbState = 1;
	return 	FfbState;
}

// Enable/Disable all Checkboxes related to FFB Effects
void vJoyDlg::EnableFfbEffectCB(bool Enable)
{
	int cb[]
	{
		IDC_VJOY_CHK_FFB_CONST, IDC_VJOY_CHK_FFB_RAMP, IDC_VJOY_CHK_FFB_SQUARE, IDC_VJOY_CHK_FFB_SINE,
		IDC_VJOY_CHK_FFB_TRI, IDC_VJOY_CHK_FFB_STUP, IDC_VJOY_CHK_FFB_STDN, IDC_VJOY_CHK_FFB_SPRING,
		IDC_VJOY_CHK_FFB_DAMPER, IDC_VJOY_CHK_FFB_INERTIA, IDC_VJOY_CHK_FFB_FRICTION
	};

	for (auto effect : cb)
		EnableWindow(GetDlgItem(m_hDlg, effect), Enable);
}

// Clear all all Checkboxes related to FFB Effects
void vJoyDlg::ClearFfbEffectCB(void)
{
	HWND h;
	int cb[]
	{
		IDC_VJOY_CHK_FFB_CONST, IDC_VJOY_CHK_FFB_RAMP, IDC_VJOY_CHK_FFB_SQUARE, IDC_VJOY_CHK_FFB_SINE,
			IDC_VJOY_CHK_FFB_TRI, IDC_VJOY_CHK_FFB_STUP, IDC_VJOY_CHK_FFB_STDN, IDC_VJOY_CHK_FFB_SPRING,
			IDC_VJOY_CHK_FFB_DAMPER, IDC_VJOY_CHK_FFB_INERTIA, IDC_VJOY_CHK_FFB_FRICTION
	};

	for (auto effect : cb)
	{
		h = GetDlgItem(m_hDlg, effect);
		SendMessage(h, BM_SETCHECK, FALSE, 0);
	};

}

// Get all active FFB effects
// Check/Uncheck the respective checkboxes accordingly
void vJoyDlg::UpdateFfbEffectCB(int rID)
{
	bool isEffect;
	HWND h;
	int pairs[][2]
	{
		{ IDC_VJOY_CHK_FFB_CONST, 0x26 }, { IDC_VJOY_CHK_FFB_RAMP, 0x27 }, { IDC_VJOY_CHK_FFB_SQUARE, 0x30 }, { IDC_VJOY_CHK_FFB_SINE, 0x31 },
		{ IDC_VJOY_CHK_FFB_TRI, 0x32 }, { IDC_VJOY_CHK_FFB_STUP, 0x33 }, { IDC_VJOY_CHK_FFB_STDN, 0x34 }, { IDC_VJOY_CHK_FFB_SPRING, 0x40 },
		{ IDC_VJOY_CHK_FFB_DAMPER, 0x41 }, { IDC_VJOY_CHK_FFB_INERTIA, 0x42 }, { IDC_VJOY_CHK_FFB_FRICTION, 0x43 }
	};

	for (auto effect : pairs)
	{
		if (!vJoyDevice[rID - 1]->Exists())
			isEffect = false;
		else
			isEffect = IsDeviceFfbEffect(rID, effect[1]);
		h = GetDlgItem(m_hDlg, effect[0]);
		SendMessage(h, BM_SETCHECK, isEffect, 0);
	}
}

void vJoyDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void vJoyDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL vJoyDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
