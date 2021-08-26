#include "stdafx.h"
#include "ViGEmDlg.h"
#include "ViGEm.h"
#include "Ds2vJoy.h"
#include <future>		// std::async, std::future

ViGEmDlg::ViGEmDlg()
{
}

ViGEmDlg::~ViGEmDlg()
{
}

INT_PTR CALLBACK ViGEmDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ViGEmDlg* dlg;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (ViGEmDlg*)lParam;
	}
	else
		dlg = (ViGEmDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	else
		return NULL;
}

void ViGEmDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_VIGEM), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hWnd = hWnd;
	Hide();
}

INT_PTR ViGEmDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CTLCOLORDLG:
	case WM_CTLCOLORMSGBOX:
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
	case WM_CTLCOLORBTN:
	{
		DWORD CtrlID = GetDlgCtrlID((HWND)lParam);
		HDC hdcStatic = (HDC)wParam;
		static HBRUSH hBrushColor = CreateSolidBrush(RGB(128, 128, 128));
		static HBRUSH hBrushColor1;
		static HBRUSH hBrushColor2;
		SetBkMode(hdcStatic, TRANSPARENT);

		switch (vg.GetViGEmState())
		{
		case -1:
		case 0:
			if (CtrlID == IDC_VIGEM_INSTALL)
			{
				hBrushColor1 = CreateSolidBrush(RGB(160, 160, 160));
				return (LRESULT)hBrushColor1;
			}
			if (CtrlID == IDC_VIGEM_STATUS)
			{
				hBrushColor2 = CreateSolidBrush(RGB(160, 160, 160));
				return (LRESULT)hBrushColor2;
			}
			break;
		case 1:
			if (CtrlID == IDC_VIGEM_INSTALL)
			{
				hBrushColor1 = CreateSolidBrush(RGB(240, 240, 0));
				return (LRESULT)hBrushColor1;
			}
			if (CtrlID == IDC_VIGEM_STATUS)
			{
				hBrushColor2 = CreateSolidBrush(RGB(240, 240, 0));
				return (LRESULT)hBrushColor2;
			}
			break;
		case 2:
			if (CtrlID == IDC_VIGEM_INSTALL)
			{
				hBrushColor1 = CreateSolidBrush(RGB(240, 240, 0));
				return (LRESULT)hBrushColor1;
			}
			if (CtrlID == IDC_VIGEM_STATUS)
			{
				hBrushColor2 = CreateSolidBrush(RGB(96, 192, 96));
				return (LRESULT)hBrushColor2;
			}
			break;
		}
		return TRUE;
	}
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
		SetTextColor(hdcStatic, RGB(10, 10, 10));
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

			HBRUSH brush = CreateSolidBrush(RGB(210, 210, 215));
			FillRect(hDC, &rect, brush);

			LPCWSTR b1Text = L"Waiting...";
			LPCWSTR b2Text = L"Waiting...";
			SetTextColor(hDC, RGB(10, 10, 10));
			switch (vg.GetViGEmState())
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

			brush = CreateSolidBrush(RGB(195, 195, 200));
			HFONT hFont = CreateFont(13, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

			UINT TextAlign = GetTextAlign(hDC);
			GetClientRect(GetDlgItem(hWnd, IDC_VIGEM_INSTALL), &rect);

			HWND statebutton = GetDlgItem(hWnd, IDC_VIGEM_INSTALL);
			hDC = BeginPaint(statebutton, &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_VIGEM_INSTALL), &rect);
			HFONT oldHFont = (HFONT)SelectObject(hDC, hFont);
			DrawText(hDC, b1Text, 9, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SelectObject(hDC, oldHFont);
			FrameRect(hDC, &rect, brush);

			statebutton = GetDlgItem(hWnd, IDC_VIGEM_STATUS);
			hDC = BeginPaint(statebutton, &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_VIGEM_STATUS), &rect);
			oldHFont = (HFONT)SelectObject(hDC, hFont);
			DrawText(hDC, b2Text, 9, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			SelectObject(hDC, oldHFont);
			FrameRect(hDC, &rect, brush);

			DeleteObject(brush);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
		if (wParam == TRUE || lParam == 3)
			vg.ViGEmStates();
		if (wParam == TRUE)
		{
			CheckDlgButton(hWnd, IDC_VIGEM_ACTIVE, tape.ViGEmActive);
			CheckDlgButton(hWnd, IDC_VIGEM_X360, tape.DesiredVirtualPad == 1 ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hWnd, IDC_VIGEM_DS4, tape.DesiredVirtualPad == 2 ? BST_CHECKED : BST_UNCHECKED);

			switch (tape.DesiredVirtualPad)
			{
			case 1:
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_VJOY_14), false);
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_VJOY_17), false);
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_VJOY_18), false);

				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_1, tape.target_X360[0]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_2, tape.target_X360[1]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_3, tape.target_X360[2]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_4, tape.target_X360[3]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_5, tape.target_X360[4]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_6, tape.target_X360[5]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_7, tape.target_X360[6]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_8, tape.target_X360[7]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_9, tape.target_X360[8]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_10, tape.target_X360[9]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_11, tape.target_X360[10]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_12, tape.target_X360[11]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_13, tape.target_X360[12]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_14, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_15, tape.target_X360[14]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_16, tape.target_X360[15]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_17, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_18, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_19, tape.target_X360[18]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_20, tape.target_X360[19]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_21, tape.target_X360[20]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_22, tape.target_X360[21]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_23, tape.target_X360[22]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_24, tape.target_X360[23]);

				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_DS_14), false);
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_DS_17), false);
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_DS_18), false);

				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_SETCURSEL, (tape.target_X360[0]) ? tape.vjtarget_X360[0] : tape.dstarget_X360[0], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_SETCURSEL, (tape.target_X360[1]) ? tape.vjtarget_X360[1] : tape.dstarget_X360[1], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_SETCURSEL, (tape.target_X360[2]) ? tape.vjtarget_X360[2] : tape.dstarget_X360[2], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_SETCURSEL, (tape.target_X360[3]) ? tape.vjtarget_X360[3] : tape.dstarget_X360[3], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_SETCURSEL, (tape.target_X360[4]) ? tape.vjtarget_X360[4] : tape.dstarget_X360[4], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_SETCURSEL, (tape.target_X360[5]) ? tape.vjtarget_X360[5] : tape.dstarget_X360[5], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_SETCURSEL, (tape.target_X360[6]) ? tape.vjtarget_X360[6] : tape.dstarget_X360[6], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_SETCURSEL, (tape.target_X360[7]) ? tape.vjtarget_X360[7] : tape.dstarget_X360[7], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_SETCURSEL, (tape.target_X360[8]) ? tape.vjtarget_X360[8] : tape.dstarget_X360[8], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_SETCURSEL, (tape.target_X360[9]) ? tape.vjtarget_X360[9] : tape.dstarget_X360[9], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_SETCURSEL, (tape.target_X360[10]) ? tape.vjtarget_X360[10] : tape.dstarget_X360[10], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_SETCURSEL, (tape.target_X360[11]) ? tape.vjtarget_X360[11] : tape.dstarget_X360[11], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_SETCURSEL, (tape.target_X360[12]) ? tape.vjtarget_X360[12] : tape.dstarget_X360[12], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_SETCURSEL, NULL, 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_SETCURSEL, (tape.target_X360[14]) ? tape.vjtarget_X360[14] : tape.dstarget_X360[14], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_SETCURSEL, (tape.target_X360[15]) ? tape.vjtarget_X360[15] : tape.dstarget_X360[15], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_SETCURSEL, NULL, 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_SETCURSEL, NULL, 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_SETCURSEL, (tape.target_X360[18]) ? tape.vjtarget_X360[18] : tape.dstarget_X360[18], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_SETCURSEL, (tape.target_X360[19]) ? tape.vjtarget_X360[19] : tape.dstarget_X360[19], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_SETCURSEL, (tape.target_X360[20]) ? tape.vjtarget_X360[20] : tape.dstarget_X360[20], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_SETCURSEL, (tape.target_X360[21]) ? tape.vjtarget_X360[21] : tape.dstarget_X360[21], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_SETCURSEL, (tape.target_X360[22]) ? tape.vjtarget_X360[22] : tape.dstarget_X360[22], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_SETCURSEL, (tape.target_X360[23]) ? tape.vjtarget_X360[23] : tape.dstarget_X360[23], 0);
				break;
			case 2:
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_VJOY_14), true);
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_VJOY_17), true);
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_VJOY_18), true);

				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_1, tape.target_DS4[0]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_2, tape.target_DS4[1]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_3, tape.target_DS4[2]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_4, tape.target_DS4[3]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_5, tape.target_DS4[4]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_6, tape.target_DS4[5]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_7, tape.target_DS4[6]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_8, tape.target_DS4[7]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_9, tape.target_DS4[8]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_10, tape.target_DS4[9]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_11, tape.target_DS4[10]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_12, tape.target_DS4[11]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_13, tape.target_DS4[12]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_14, tape.target_DS4[13]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_15, tape.target_DS4[14]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_16, tape.target_DS4[15]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_17, tape.target_DS4[16]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_18, tape.target_DS4[17]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_19, tape.target_DS4[18]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_20, tape.target_DS4[19]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_21, tape.target_DS4[20]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_22, tape.target_DS4[21]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_23, tape.target_DS4[22]);
				CheckDlgButton(hWnd, IDC_VIGEM_VJOY_24, tape.target_DS4[23]);
				
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_DS_14), true);
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_DS_17), true);
				EnableWindow(GetDlgItem(hWnd, IDC_VIGEM_DS_18), true);

				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_SETCURSEL, (tape.target_DS4[0]) ? tape.vjtarget_DS4[0] : tape.dstarget_DS4[0], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_SETCURSEL, (tape.target_DS4[1]) ? tape.vjtarget_DS4[1] : tape.dstarget_DS4[1], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_SETCURSEL, (tape.target_DS4[2]) ? tape.vjtarget_DS4[2] : tape.dstarget_DS4[2], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_SETCURSEL, (tape.target_DS4[3]) ? tape.vjtarget_DS4[3] : tape.dstarget_DS4[3], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_SETCURSEL, (tape.target_DS4[4]) ? tape.vjtarget_DS4[4] : tape.dstarget_DS4[4], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_SETCURSEL, (tape.target_DS4[5]) ? tape.vjtarget_DS4[5] : tape.dstarget_DS4[5], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_SETCURSEL, (tape.target_DS4[6]) ? tape.vjtarget_DS4[6] : tape.dstarget_DS4[6], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_SETCURSEL, (tape.target_DS4[7]) ? tape.vjtarget_DS4[7] : tape.dstarget_DS4[7], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_SETCURSEL, (tape.target_DS4[8]) ? tape.vjtarget_DS4[8] : tape.dstarget_DS4[8], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_SETCURSEL, (tape.target_DS4[9]) ? tape.vjtarget_DS4[9] : tape.dstarget_DS4[9], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_SETCURSEL, (tape.target_DS4[10]) ? tape.vjtarget_DS4[10] : tape.dstarget_DS4[10], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_SETCURSEL, (tape.target_DS4[11]) ? tape.vjtarget_DS4[11] : tape.dstarget_DS4[11], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_SETCURSEL, (tape.target_DS4[12]) ? tape.vjtarget_DS4[12] : tape.dstarget_DS4[12], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_SETCURSEL, (tape.target_DS4[13]) ? tape.vjtarget_DS4[13] : tape.dstarget_DS4[13], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_SETCURSEL, (tape.target_DS4[14]) ? tape.vjtarget_DS4[14] : tape.dstarget_DS4[14], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_SETCURSEL, (tape.target_DS4[15]) ? tape.vjtarget_DS4[15] : tape.dstarget_DS4[15], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_SETCURSEL, (tape.target_DS4[16]) ? tape.vjtarget_DS4[16] : tape.dstarget_DS4[16], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_SETCURSEL, (tape.target_DS4[17]) ? tape.vjtarget_DS4[17] : tape.dstarget_DS4[17], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_SETCURSEL, (tape.target_DS4[18]) ? tape.vjtarget_DS4[18] : tape.dstarget_DS4[18], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_SETCURSEL, (tape.target_DS4[19]) ? tape.vjtarget_DS4[19] : tape.dstarget_DS4[19], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_SETCURSEL, (tape.target_DS4[20]) ? tape.vjtarget_DS4[20] : tape.dstarget_DS4[20], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_SETCURSEL, (tape.target_DS4[21]) ? tape.vjtarget_DS4[21] : tape.dstarget_DS4[21], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_SETCURSEL, (tape.target_DS4[22]) ? tape.vjtarget_DS4[22] : tape.dstarget_DS4[22], 0);
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_SETCURSEL, (tape.target_DS4[23]) ? tape.vjtarget_DS4[23] : tape.dstarget_DS4[23], 0);
				break;
			}
			HFONT hFont = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_2, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_3, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_4, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_5, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_6, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_7, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_8, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_9, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_10, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_11, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_12, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_13, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_14, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_15, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_16, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_17, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_18, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_19, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_20, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_21, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_22, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_23, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_24, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		}
		break;
	case WM_CHANGE_COMBO_BOX:
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_1, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_2, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_3, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_4, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_5, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_6, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_7, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_8, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_9, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_10, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_11, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_12, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_13, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_14, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_15, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_16, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_17, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_18, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_19, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_20, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_21, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_22, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_23, CB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hWnd, IDC_VIGEM_DS_24, CB_RESETCONTENT, 0, 0);
	case WM_INITDIALOG:
	{
		for (int i = 0; i < dsButtonID::button_Count; i++)
		{
			WCHAR* str = dsButton::String((dsButtonID)i);
			if ((!tape.target_X360[0] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[0] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_1, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[1] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[1] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_2, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[2] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[2] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_3, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[3] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[3] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_4, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[4] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[4] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_5, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[5] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[5] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_6, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[6] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[6] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_7, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[7] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[7] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_8, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[8] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[8] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_9, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[9] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[9] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_10, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[10] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[10] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_11, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[11] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[11] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_12, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[12] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[12] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_13, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[13] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[13] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_14, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[14] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[14] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_15, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[15] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[15] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_16, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[16] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[16] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_17, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[17] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[17] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_18, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[18] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[18] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_19, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[19] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[19] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_20, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[20] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[20] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_21, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[21] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[21] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_22, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[22] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[22] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_23, CB_ADDSTRING, 0, (LPARAM)str);
			if ((!tape.target_X360[23] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[23] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_24, CB_ADDSTRING, 0, (LPARAM)str);
		}
		for (int i = 0; i < vJoyButtonID::button_Count; i++)
		{
			WCHAR* str = vJoyButton::String((vJoyButtonID)i);
			if ((tape.target_X360[0] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[0] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_1, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[1] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[1] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_2, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[2] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[2] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_3, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[3] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[3] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_4, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[4] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[4] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_5, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[5] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[5] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_6, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[6] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[6] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_7, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[7] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[7] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_8, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[8] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[8] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_9, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[9] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[9] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_10, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[10] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[10] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_11, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[11] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[11] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_12, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[12] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[12] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_13, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[13] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[13] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_14, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[14] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[14] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_15, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[15] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[15] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_16, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[16] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[16] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_17, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[17] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[17] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_18, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[18] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[18] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_19, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[19] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[19] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_20, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[20] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[20] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_21, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[21] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[21] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_22, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[22] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[22] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_23, CB_ADDSTRING, 0, (LPARAM)str);
			if ((tape.target_X360[23] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[23] && tape.DesiredVirtualPad == 2))
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_24, CB_ADDSTRING, 0, (LPARAM)str);
		}
		return TRUE;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDC_VIGEM_ACTIVE:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
				PostMessage(m_hWnd, WM_CHANGE_PAD, 1, 0);
			else
				PostMessage(m_hWnd, WM_CHANGE_PAD, 0, 0);
			break;
		case IDC_VIGEM_X360:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					CheckDlgButton(hWnd, IDC_VIGEM_DS4, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_VIGEM_X360, BST_CHECKED);
				tape.DesiredVirtualPad = 1;
				tape.Save(tape.Setting_DesiredVirtualPad);
				SendMessage(m_hDlg, WM_CHANGE_COMBO_BOX, 0, 0);
				SendMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				Hide();
				Show();
				break;
			}
			break;
		case IDC_VIGEM_DS4:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					CheckDlgButton(hWnd, IDC_VIGEM_X360, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_VIGEM_DS4, BST_CHECKED);
				tape.DesiredVirtualPad = 2;
				tape.Save(tape.Setting_DesiredVirtualPad);
				SendMessage(m_hDlg, WM_CHANGE_COMBO_BOX, 0, 0);
				SendMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				Hide();
				Show();
				break;
			}
			break;
		case IDC_VIGEM_VJOY_1:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[0] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[0] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_1, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[0] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[0] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_SETCURSEL, tape.vjtarget_X360[0], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_SETCURSEL, tape.dstarget_X360[0], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_2:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[1] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[1] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_2, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[1] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[1] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_SETCURSEL, tape.vjtarget_X360[1], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_SETCURSEL, tape.dstarget_X360[1], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_3:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[2] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[2] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_3, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[2] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[2] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_SETCURSEL, tape.vjtarget_X360[2], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_SETCURSEL, tape.dstarget_X360[2], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_4:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[3] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[3] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_4, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[3] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[3] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_SETCURSEL, tape.vjtarget_X360[3], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_SETCURSEL, tape.dstarget_X360[3], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_5:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[4] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[4] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_5, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[4] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[4] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_SETCURSEL, tape.vjtarget_X360[4], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_SETCURSEL, tape.dstarget_X360[4], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_6:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[5] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[5] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_6, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[5] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[5] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_SETCURSEL, tape.vjtarget_X360[5], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_SETCURSEL, tape.dstarget_X360[5], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_7:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[6] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[6] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_7, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[6] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[6] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_SETCURSEL, tape.vjtarget_X360[6], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_SETCURSEL, tape.dstarget_X360[6], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_8:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[7] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[7] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_8, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[7] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[7] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_SETCURSEL, tape.vjtarget_X360[7], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_SETCURSEL, tape.dstarget_X360[7], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_9:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[8] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[8] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_9, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[8] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[8] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_SETCURSEL, tape.vjtarget_X360[8], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_SETCURSEL, tape.dstarget_X360[8], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_10:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[9] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[9] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_10, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[9] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[9] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_SETCURSEL, tape.vjtarget_X360[9], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_SETCURSEL, tape.dstarget_X360[9], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_11:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[10] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[10] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_11, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[10] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[10] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_SETCURSEL, tape.vjtarget_X360[10], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_SETCURSEL, tape.dstarget_X360[10], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_12:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[11] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[11] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_12, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[11] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[11] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_SETCURSEL, tape.vjtarget_X360[11], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_SETCURSEL, tape.dstarget_X360[11], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_13:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[12] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[12] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_13, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[12] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[12] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_SETCURSEL, tape.vjtarget_X360[12], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_SETCURSEL, tape.dstarget_X360[12], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_14:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[13] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[13] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_14, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[13] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[13] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_SETCURSEL, tape.vjtarget_X360[13], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_SETCURSEL, tape.dstarget_X360[13], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_15:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[14] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[14] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_15, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[14] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[14] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_SETCURSEL, tape.vjtarget_X360[14], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_SETCURSEL, tape.dstarget_X360[14], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_16:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[15] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[15] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_16, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[15] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[15] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_SETCURSEL, tape.vjtarget_X360[15], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_SETCURSEL, tape.dstarget_X360[15], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_17:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[16] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[16] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_17, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[16] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[16] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_SETCURSEL, tape.vjtarget_X360[16], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_SETCURSEL, tape.dstarget_X360[16], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_18:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[17] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[17] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_18, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[17] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[17] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_SETCURSEL, tape.vjtarget_X360[17], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_SETCURSEL, tape.dstarget_X360[17], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_19:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[18] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[18] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_19, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[18] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[18] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_SETCURSEL, tape.vjtarget_X360[18], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_SETCURSEL, tape.dstarget_X360[18], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_20:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[19] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[19] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_20, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[19] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[19] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_SETCURSEL, tape.vjtarget_X360[19], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_SETCURSEL, tape.dstarget_X360[19], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_21:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[20] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[20] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_21, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[20] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[20] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_SETCURSEL, tape.vjtarget_X360[20], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_SETCURSEL, tape.dstarget_X360[20], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_22:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[21] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[21] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_22, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[21] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[21] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_SETCURSEL, tape.vjtarget_X360[21], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_SETCURSEL, tape.dstarget_X360[21], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_23:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[22] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[22] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_23, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[22] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[22] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_SETCURSEL, tape.vjtarget_X360[2], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_SETCURSEL, tape.dstarget_X360[22], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_VJOY_24:
			if (tape.DesiredVirtualPad == 1) { tape.target_X360[23] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
			else { tape.target_DS4[23] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_24, CB_RESETCONTENT, 0, 0);
			if ((tape.target_X360[23] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[23] && tape.DesiredVirtualPad == 2))
			{
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_SETCURSEL, tape.vjtarget_X360[23], 0);
			}
			else
			{
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_ADDSTRING, 0, (LPARAM)str);
				}
				SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_SETCURSEL, tape.dstarget_X360[23], 0);
			}
			Hide();
			Show();
			break;
		case IDC_VIGEM_DS_1:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[0]) { tape.vjtarget_X360[0] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[0] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[0]) { tape.vjtarget_DS4[0] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[0] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_2:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[1]) { tape.vjtarget_X360[1] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[1] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[1]) { tape.vjtarget_DS4[1] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[1] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_3:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[2]) { tape.vjtarget_X360[2] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[2] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[2]) { tape.vjtarget_DS4[2] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[2] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_4:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[3]) { tape.vjtarget_X360[3] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[3] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[3]) { tape.vjtarget_DS4[3] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[3] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_5:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[4]) { tape.vjtarget_X360[4] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[4] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[4]) { tape.vjtarget_DS4[4] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[4] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_6:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[5]) { tape.vjtarget_X360[5] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[5] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[5]) { tape.vjtarget_DS4[5] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[5] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_7:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[6]) { tape.vjtarget_X360[6] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[6] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[6]) { tape.vjtarget_DS4[6] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[6] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_8:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[7]) { tape.vjtarget_X360[7] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[7] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[7]) { tape.vjtarget_DS4[7] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[7] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_9:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[8]) { tape.vjtarget_X360[8] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[8] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[8]) { tape.vjtarget_DS4[8] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[8] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_10:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[9]) { tape.vjtarget_X360[9] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[9] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[9]) { tape.vjtarget_DS4[9] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[9] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_11:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[10]) { tape.vjtarget_X360[10] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[10] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[10]) { tape.vjtarget_DS4[10] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[10] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_12:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[11]) { tape.vjtarget_X360[11] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[11] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[11]) { tape.vjtarget_DS4[11] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[11] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_13:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[12]) { tape.vjtarget_X360[12] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[12] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[12]) { tape.vjtarget_DS4[12] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[12] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_14:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[13]) { tape.vjtarget_X360[13] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[13] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[13]) { tape.vjtarget_DS4[13] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[13] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_15:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[14]) { tape.vjtarget_X360[14] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[14] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[14]) { tape.vjtarget_DS4[14] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[14] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_16:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[15]) { tape.vjtarget_X360[15] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[15] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[15]) { tape.vjtarget_DS4[15] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[15] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_17:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[16]) { tape.vjtarget_X360[16] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[16] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[16]) { tape.vjtarget_DS4[16] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[16] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_18:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[17]) { tape.vjtarget_X360[17] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[17] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[17]) { tape.vjtarget_DS4[17] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[17] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_19:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[18]) { tape.vjtarget_X360[18] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[18] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[18]) { tape.vjtarget_DS4[18] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[18] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_20:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[19]) { tape.vjtarget_X360[19] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[19] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[19]) { tape.vjtarget_DS4[19] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[19] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_21:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[20]) { tape.vjtarget_X360[20] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[20] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[20]) { tape.vjtarget_DS4[20] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[20] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_22:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[21]) { tape.vjtarget_X360[21] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[21] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[21]) { tape.vjtarget_DS4[21] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[21] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_23:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[22]) { tape.vjtarget_X360[22] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[22] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[22]) { tape.vjtarget_DS4[22] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[22] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_DS_24:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[23]) { tape.vjtarget_X360[23] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[23] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[23]) { tape.vjtarget_DS4[23] = (vJoyButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[23] = (dsButtonID)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			break;
		case IDC_VIGEM_INSTALL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				int ViGEmtate = vg.GetViGEmState();
				vg.ViGEmStates();
				if (ViGEmtate == vg.GetViGEmState())
				{
					switch (ViGEmtate)
					{
					case -1:
					case 0:
					{
						vg.ViGEmInstall();
						Sleep(500);
						vg.ViGEmStates();
						if (vg.GetViGEmState() == 1)
							SendMessage(m_hWnd, WM_CHANGE_PAD, 1, 0);
						break;
					}
					case 1:
					case 2:
					{
						SendMessage(m_hWnd, WM_CHANGE_PAD, 0, 0);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_ACTIVE), BM_SETCHECK, tape.ViGEmActive ? BST_CHECKED : BST_UNCHECKED, 0);
						if (!tape.ViGEmActive)
						{
							Sleep(500);
							vg.ViGEmUninstall();
						}
					}
					}
				}
				vg.ViGEmStates();
				SendMessage(hWnd, WM_DEVICE_DS_START, 0, 1);
				Hide();
				Show();
				break;
			}
			break;
		}
		case IDC_VIGEM_STATUS:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				int ViGEmtate = vg.GetViGEmState();
				vg.ViGEmStates();
				if (ViGEmtate == vg.GetViGEmState())
				{
					switch (ViGEmtate)
					{
					case -1:
					case 0:
						break;
					case 1:
						SendMessage(m_hWnd, WM_CHANGE_PAD, 0, 0);
						SendMessage(m_hWnd, WM_CHANGE_PAD, 1, 0);
						Hide();
						Show();
						break;
					case 2:
						vg.ViGEmEnable();
						break;
					}
				}
				vg.ViGEmStates();
				Hide();
				Show();
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

void ViGEmDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}

void ViGEmDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);
}

BOOL ViGEmDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
