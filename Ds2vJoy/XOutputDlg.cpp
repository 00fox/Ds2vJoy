#include "stdafx.h"
#include "XOutputDlg.h"
#include "XOutput.h"

XOutputDlg::XOutputDlg()
{
}

XOutputDlg::~XOutputDlg()
{
}

void XOutputDlg::Init()
{
	m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_XOUTPUT), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));
	Hide();
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_ACTIVE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_VJOY_ACTIVE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_PAD, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_X360, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_DS4, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_1_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_2_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_3_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_4_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_5_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_6_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_7_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_8_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_9_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_10_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_11_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_12_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_13_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_14_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_L1_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_R1_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_L2_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_R2_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_LT_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_RT_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_LX_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_LY_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_RX_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_RY_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_3, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_4, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_5, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_6, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_7, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_8, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_9, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_10, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_11, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_12, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_13, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_14, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_L1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_R1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_L2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_R2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_LT, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_RT, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_LX, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_LY, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_RX, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_SRCE_RY, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_ACTIVE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_X360_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_XOUTPUT_DS4_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_XOUTPUT_ACTIVE), I18N.XOUTPUT_ACTIVE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_XOUTPUT_VJOY_ACTIVE), I18N.XOUTPUT_VJOY_ACTIVE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_XOUTPUT_PAD), I18N.XOUTPUT_PAD);
	SetWindowText(GetDlgItem(m_hDlg, IDC_XOUTPUT_X360), I18N.XOUTPUT_X360);
	SetWindowText(GetDlgItem(m_hDlg, IDC_XOUTPUT_DS4), I18N.XOUTPUT_DS4);
	SetWindowText(GetDlgItem(m_hDlg, IDC_XOUTPUT_INSTALL_VJOY), I18N.XOUTPUT_INSTALL_VJOY);
	SetWindowText(GetDlgItem(m_hDlg, IDC_XOUTPUT_INSTALL), I18N.XOUTPUT_INSTALL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_XOUTPUT_STATUS), I18N.XOUTPUT_STATUS);
}

void XOutputDlg::_InitDialog(HWND hWnd)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	const WCHAR* str = WCHARI();
	for (int i = 0; i < DestButtonID::Destination_Count; i++)
	{
		str = DestinationButton::String((DestButtonID)i);
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_2, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_3, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_4, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_5, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_6, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_7, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_8, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_9, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_10, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_11, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_12, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_13, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_14, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_L1, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_R1, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_L2, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_R2, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_LT, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_RT, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_LX, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_LY, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_RX, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_XOUTPUT_SRCE_RY, CB_ADDSTRING, 0, LPARAM(str));
	}
	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void XOutputDlg::_ShowWindow(HWND hWnd)
{
	CheckDlgButton(hWnd, IDC_XOUTPUT_ACTIVE_CHK, tape.XOutputActive);
	CheckDlgButton(hWnd, IDC_XOUTPUT_VJOY_ACTIVE_CHK, tape.vJoyActive);
	CheckDlgButton(hWnd, IDC_XOUTPUT_DS4_CHK, (tape.DesiredVirtualPad) == 1 ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(hWnd, IDC_XOUTPUT_X360_CHK, (tape.DesiredVirtualPad) == 2 ? BST_CHECKED : BST_UNCHECKED);

	switch (tape.DesiredVirtualPad)
	{
	case 1:
	{
		EnableWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14), true);
		EnableWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2), true);
		EnableWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2), true);
		::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14_STATIC), SW_SHOW);
		::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2_STATIC), SW_SHOW);
		::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2_STATIC), SW_SHOW);

		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1), CB_SETCURSEL,  tape.target_DS4[0], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2), CB_SETCURSEL,  tape.target_DS4[1], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3), CB_SETCURSEL,  tape.target_DS4[2], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4), CB_SETCURSEL,  tape.target_DS4[3], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5), CB_SETCURSEL,  tape.target_DS4[4], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6), CB_SETCURSEL,  tape.target_DS4[5], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7), CB_SETCURSEL,  tape.target_DS4[6], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8), CB_SETCURSEL,  tape.target_DS4[7], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9), CB_SETCURSEL,  tape.target_DS4[8], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10), CB_SETCURSEL, tape.target_DS4[9], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11), CB_SETCURSEL, tape.target_DS4[10], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12), CB_SETCURSEL, tape.target_DS4[11], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13), CB_SETCURSEL, tape.target_DS4[12], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14), CB_SETCURSEL, tape.target_DS4[13], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1), CB_SETCURSEL, tape.target_DS4[14], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1), CB_SETCURSEL, tape.target_DS4[15], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2), CB_SETCURSEL, tape.target_DS4[16], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2), CB_SETCURSEL, tape.target_DS4[17], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT), CB_SETCURSEL, tape.target_DS4[18], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT), CB_SETCURSEL, tape.target_DS4[19], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX), CB_SETCURSEL, tape.target_DS4[20], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY), CB_SETCURSEL, tape.target_DS4[21], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX), CB_SETCURSEL, tape.target_DS4[22], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY), CB_SETCURSEL, tape.target_DS4[23], 0);

		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1_STATIC), (tape.target_DS4[0]) ? DestinationButton::String((DestButtonID)tape.target_DS4[0]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2_STATIC), (tape.target_DS4[1]) ? DestinationButton::String((DestButtonID)tape.target_DS4[1]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3_STATIC), (tape.target_DS4[2]) ? DestinationButton::String((DestButtonID)tape.target_DS4[2]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4_STATIC), (tape.target_DS4[3]) ? DestinationButton::String((DestButtonID)tape.target_DS4[3]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5_STATIC), (tape.target_DS4[4]) ? DestinationButton::String((DestButtonID)tape.target_DS4[4]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6_STATIC), (tape.target_DS4[5]) ? DestinationButton::String((DestButtonID)tape.target_DS4[5]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7_STATIC), (tape.target_DS4[6]) ? DestinationButton::String((DestButtonID)tape.target_DS4[6]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8_STATIC), (tape.target_DS4[7]) ? DestinationButton::String((DestButtonID)tape.target_DS4[7]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9_STATIC), (tape.target_DS4[8]) ? DestinationButton::String((DestButtonID)tape.target_DS4[8]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10_STATIC), (tape.target_DS4[9]) ? DestinationButton::String((DestButtonID)tape.target_DS4[9]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11_STATIC), (tape.target_DS4[10]) ? DestinationButton::String((DestButtonID)tape.target_DS4[10]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12_STATIC), (tape.target_DS4[11]) ? DestinationButton::String((DestButtonID)tape.target_DS4[11]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13_STATIC), (tape.target_DS4[12]) ? DestinationButton::String((DestButtonID)tape.target_DS4[12]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14_STATIC), (tape.target_DS4[13]) ? DestinationButton::String((DestButtonID)tape.target_DS4[13]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1_STATIC), (tape.target_DS4[14]) ? DestinationButton::String((DestButtonID)tape.target_DS4[14]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1_STATIC), (tape.target_DS4[15]) ? DestinationButton::String((DestButtonID)tape.target_DS4[15]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2_STATIC), (tape.target_DS4[16]) ? DestinationButton::String((DestButtonID)tape.target_DS4[16]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2_STATIC), (tape.target_DS4[17]) ? DestinationButton::String((DestButtonID)tape.target_DS4[17]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT_STATIC), (tape.target_DS4[18]) ? DestinationButton::String((DestButtonID)tape.target_DS4[18]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT_STATIC), (tape.target_DS4[19]) ? DestinationButton::String((DestButtonID)tape.target_DS4[19]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX_STATIC), (tape.target_DS4[20]) ? DestinationButton::String((DestButtonID)tape.target_DS4[20]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY_STATIC), (tape.target_DS4[21]) ? DestinationButton::String((DestButtonID)tape.target_DS4[21]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX_STATIC), (tape.target_DS4[22]) ? DestinationButton::String((DestButtonID)tape.target_DS4[22]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY_STATIC), (tape.target_DS4[23]) ? DestinationButton::String((DestButtonID)tape.target_DS4[23]) : L"...");
		break;
	}
	case 2:
	{
		EnableWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14), false);
		EnableWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2), false);
		EnableWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2), false);
		::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14_STATIC), SW_HIDE);
		::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2_STATIC), SW_HIDE);
		::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2_STATIC), SW_HIDE);

		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1), CB_SETCURSEL, tape.target_X360[0], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2), CB_SETCURSEL, tape.target_X360[1], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3), CB_SETCURSEL, tape.target_X360[2], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4), CB_SETCURSEL, tape.target_X360[3], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5), CB_SETCURSEL, tape.target_X360[4], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6), CB_SETCURSEL, tape.target_X360[5], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7), CB_SETCURSEL, tape.target_X360[6], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8), CB_SETCURSEL, tape.target_X360[7], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9), CB_SETCURSEL, tape.target_X360[8], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10), CB_SETCURSEL, tape.target_X360[9], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11), CB_SETCURSEL, tape.target_X360[10], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12), CB_SETCURSEL, tape.target_X360[11], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13), CB_SETCURSEL, tape.target_X360[12], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14), CB_SETCURSEL, NULL, 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1), CB_SETCURSEL, tape.target_X360[14], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1), CB_SETCURSEL, tape.target_X360[15], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2), CB_SETCURSEL, NULL, 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2), CB_SETCURSEL, NULL, 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT), CB_SETCURSEL, tape.target_X360[18], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT), CB_SETCURSEL, tape.target_X360[19], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX), CB_SETCURSEL, tape.target_X360[20], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY), CB_SETCURSEL, tape.target_X360[21], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX), CB_SETCURSEL, tape.target_X360[22], 0);
		SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY), CB_SETCURSEL, tape.target_X360[23], 0);

		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1_STATIC), (tape.target_X360[0]) ? DestinationButton::String((DestButtonID)tape.target_X360[0]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2_STATIC), (tape.target_X360[1]) ? DestinationButton::String((DestButtonID)tape.target_X360[1]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3_STATIC), (tape.target_X360[2]) ? DestinationButton::String((DestButtonID)tape.target_X360[2]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4_STATIC), (tape.target_X360[3]) ? DestinationButton::String((DestButtonID)tape.target_X360[3]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5_STATIC), (tape.target_X360[4]) ? DestinationButton::String((DestButtonID)tape.target_X360[4]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6_STATIC), (tape.target_X360[5]) ? DestinationButton::String((DestButtonID)tape.target_X360[5]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7_STATIC), (tape.target_X360[6]) ? DestinationButton::String((DestButtonID)tape.target_X360[6]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8_STATIC), (tape.target_X360[7]) ? DestinationButton::String((DestButtonID)tape.target_X360[7]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9_STATIC), (tape.target_X360[8]) ? DestinationButton::String((DestButtonID)tape.target_X360[8]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10_STATIC), (tape.target_X360[9]) ? DestinationButton::String((DestButtonID)tape.target_X360[9]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11_STATIC), (tape.target_X360[10]) ? DestinationButton::String((DestButtonID)tape.target_X360[10]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12_STATIC), (tape.target_X360[11]) ? DestinationButton::String((DestButtonID)tape.target_X360[11]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13_STATIC), (tape.target_X360[12]) ? DestinationButton::String((DestButtonID)tape.target_X360[12]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14_STATIC), L"");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1_STATIC), (tape.target_X360[14]) ? DestinationButton::String((DestButtonID)tape.target_X360[14]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1_STATIC), (tape.target_X360[15]) ? DestinationButton::String((DestButtonID)tape.target_X360[15]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2_STATIC), L"");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2_STATIC), L"");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT_STATIC), (tape.target_X360[18]) ? DestinationButton::String((DestButtonID)tape.target_X360[18]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT_STATIC), (tape.target_X360[19]) ? DestinationButton::String((DestButtonID)tape.target_X360[19]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX_STATIC), (tape.target_X360[20]) ? DestinationButton::String((DestButtonID)tape.target_X360[20]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY_STATIC), (tape.target_X360[21]) ? DestinationButton::String((DestButtonID)tape.target_X360[21]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX_STATIC), (tape.target_X360[22]) ? DestinationButton::String((DestButtonID)tape.target_X360[22]) : L"...");
		SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY_STATIC), (tape.target_X360[23]) ? DestinationButton::String((DestButtonID)tape.target_X360[23]) : L"...");
		break;
	}
	}
}

INT_PTR CALLBACK XOutputDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	XOutputDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<XOutputDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<XOutputDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR XOutputDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		DWORD CtrlID = GetDlgCtrlID((HWND)lParam);
		SetBkMode(hdcStatic, TRANSPARENT);
		switch (CtrlID)
		{
		case IDC_XOUTPUT_INSTALL:
		case IDC_XOUTPUT_STATUS:
		{
			switch (xi.GetXOutputState())
			{
			case -1:
			case 0:
			{
				if (CtrlID == IDC_XOUTPUT_INSTALL) return (LRESULT)tape.hB_Not_Installed;
				if (CtrlID == IDC_XOUTPUT_STATUS) return (LRESULT)tape.hB_Not_Installed;
				break;
			}
			case 1:
			{
				if (CtrlID == IDC_XOUTPUT_INSTALL) return (LRESULT)tape.hB_Running;
				if (CtrlID == IDC_XOUTPUT_STATUS) return (LRESULT)tape.hB_Running;
				break;
			}
			case 2:
			{
				if (CtrlID == IDC_XOUTPUT_INSTALL) return (LRESULT)tape.hB_Running;
				if (CtrlID == IDC_XOUTPUT_STATUS) return (LRESULT)tape.hB_Paused;
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_INSTALL_VJOY:
		{
			switch (xi.GetvJoyState())
			{
			case -1:
			case 0:
			{
				return (LRESULT)tape.hB_Not_Installed;
				break;
			}
			case 1:
			{
				return (LRESULT)tape.hB_Running;
				break;
			}
			case 2:
			{
				return (LRESULT)tape.hB_Paused;
				break;
			}
			}
			break;
		}
		}
		return (LRESULT)tape.hB_neutral;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		switch (GetDlgCtrlID((HWND)lParam))
		{
		case IDC_XOUTPUT_ACTIVE_CHK:
		case IDC_XOUTPUT_VJOY_ACTIVE_CHK:
		case IDC_XOUTPUT_X360_CHK:
		case IDC_XOUTPUT_DS4_CHK:
		{
			SetTextColor(hdcStatic, tape.ink_STATIC);
			if (tape.DarkTheme)
				return (LRESULT)tape.hB_BackGround_DARK;
			else
				return (LRESULT)tape.hB_BackGround;
		}
		case IDC_XOUTPUT_PAD:
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
		case IDC_XOUTPUT_ACTIVE:
		case IDC_XOUTPUT_VJOY_ACTIVE:
		case IDC_XOUTPUT_X360:
		case IDC_XOUTPUT_DS4:
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
		default:
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
				if (tape.DesiredVirtualPad == 1)
				{
					SetRect(&rect, 30, 36, 107, 56);
					FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
					SetRect(&rect, 360, 36, 437, 56);
					FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
					SetRect(&rect, 194, 120, 271, 140);
					FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				}
				SetRect(&rect, 108, 36, 185, 56);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 282, 36, 359, 56);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 30, 60, 107, 80);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 360, 60, 437, 80);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 156, 89, 233, 109);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 234, 89, 311, 109);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 63, 106, 140, 126);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 327, 106, 404, 126);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 15, 130, 92, 150);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 93, 130, 170, 150);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 297, 130, 374, 150);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 375, 130, 452, 150);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 53, 154, 130, 174);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 337, 154, 414, 174);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 13, 190, 90, 210);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 91, 190, 168, 210);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 299, 190, 376, 210);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 377, 190, 454, 210);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 91, 214, 168, 234);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 299, 214, 376, 234);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
				SetRect(&rect, 194, 162, 271, 182);
				FillRect(hDC, &rect, tape.hB_EDIT_DARK2);
			}
			else
			{
				if (tape.DesiredVirtualPad == 1)
				{
					SetRect(&rect, 30, 36, 107, 56);
					FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
					SetRect(&rect, 360, 36, 437, 56);
					FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
					SetRect(&rect, 194, 120, 271, 140);
					FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);

					SetRect(&rect, 30, 37, 107, 55);
					FillRect(hDC, &rect, tape.hB_EDIT);
					SetRect(&rect, 360, 37, 437, 55);
					FillRect(hDC, &rect, tape.hB_EDIT);
					SetRect(&rect, 194, 121, 271, 139);
					FillRect(hDC, &rect, tape.hB_EDIT);
				}
				SetRect(&rect, 108, 36, 185, 56);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 282, 36, 359, 56);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 30, 60, 107, 80);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 360, 60, 437, 80);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 156, 89, 233, 109);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 234, 89, 311, 109);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 63, 106, 140, 126);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 327, 106, 404, 126);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 15, 130, 92, 150);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 93, 130, 170, 150);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 297, 130, 374, 150);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 375, 130, 452, 150);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 53, 154, 130, 174);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 337, 154, 414, 174);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 13, 190, 90, 210);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 91, 190, 168, 210);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 299, 190, 376, 210);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 377, 190, 454, 210);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 91, 214, 168, 234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 299, 214, 376, 234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 194, 162, 271, 182);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);

				SetRect(&rect, 108, 37, 185, 55);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 282, 37, 359, 55);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 30, 61, 107, 79);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 360, 61, 437, 79);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 156, 90, 233, 108);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 234, 90, 311, 108);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 63, 107, 140, 125);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 327, 107, 404, 125);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 15, 131, 92, 149);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 93, 131, 170, 149);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 297, 131, 374, 149);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 375, 131, 452, 149);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 53, 155, 130, 173);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 337, 155, 414, 173);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 13, 191, 90, 209);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 91, 191, 168, 209);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 299, 191, 376, 209);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 377, 191, 454, 209);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 91, 215, 168, 233);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 299, 215, 376, 233);
				FillRect(hDC, &rect, tape.hB_EDIT);
				SetRect(&rect, 194, 163, 271, 181);
				FillRect(hDC, &rect, tape.hB_EDIT);
			}

			LPCWSTR b0Text = I18N.STATE_WAITING;
			SetTextColor(hDC, tape.ink_BTN_Install);
			switch (xi.GetvJoyState())
			{
			case -1:
			case 0:
			{
				b0Text = I18N.STATE_VJOY_INSTALL;
				break;
			}
			case 1:
			case 2:
			{
				b0Text = I18N.STATE_VJOY_UNINSTALL;
				break;
			}
			}

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_XOUTPUT_INSTALL_VJOY), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_XOUTPUT_INSTALL_VJOY), &rect);
			SelectObject(hDC, tape.hButton2);
			DrawText(hDC, b0Text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (tape.DarkTheme)
				FrameRect(hDC, &rect, tape.hB_BTN_Border_DARK);
			else
				FrameRect(hDC, &rect, tape.hB_BTN_Border);

			LPCWSTR b1Text = I18N.STATE_WAITING;
			LPCWSTR b2Text = I18N.STATE_WAITING;
			switch (xi.GetXOutputState())
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

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_XOUTPUT_INSTALL), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_XOUTPUT_INSTALL), &rect);
			SelectObject(hDC, tape.hButton2);
			DrawText(hDC, b1Text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (tape.DarkTheme)
				FrameRect(hDC, &rect, tape.hB_BTN_Border_DARK);
			else
				FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_XOUTPUT_STATUS), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_XOUTPUT_STATUS), &rect);
			SelectObject(hDC, tape.hButton2);
			DrawText(hDC, b2Text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (tape.DarkTheme)
				FrameRect(hDC, &rect, tape.hB_BTN_Border_DARK);
			else
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
			xi.XOutputStates();
			xi.vJoyStates();
		}
		if (wParam == TRUE)
			std::thread(&XOutputDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&XOutputDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_XOUTPUT_ACTIVE_CHK:
		case IDC_XOUTPUT_VJOY_ACTIVE_CHK:
		case IDC_XOUTPUT_X360_CHK:
		case IDC_XOUTPUT_DS4_CHK:
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
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_XOUTPUT_ACTIVE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.XOutputActive = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_XOutputActive);
				if (tape.XOutputActive)
					PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 1, 0);
				else
					PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 0, 0);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_VJOY_ACTIVE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				tape.vJoyActive = IsDlgButtonChecked(hWnd, LOWORD(wParam));
				tape.Save(tape.Setting_vJoyActive);
				if (tape.vJoyActive)
					SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_ENABLE, false);
				else
					SetDeviceState(L"ROOT\\HIDCLASS", L"root\\VID_1234&PID_BEAD&REV_0219", DICS_DISABLE, false);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_DS4_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					CheckDlgButton(hWnd, IDC_XOUTPUT_X360_CHK, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_XOUTPUT_DS4_CHK, BST_CHECKED);
				tape.DesiredVirtualPad = 1;
				tape.Save(tape.Setting_DesiredVirtualPad);
				std::thread(&XOutputDlg::_ShowWindow, this, hWnd).detach();
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_X360_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					CheckDlgButton(hWnd, IDC_XOUTPUT_DS4_CHK, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_XOUTPUT_X360_CHK, BST_CHECKED);
				tape.DesiredVirtualPad = 2;
				tape.Save(tape.Setting_DesiredVirtualPad);
				std::thread(&XOutputDlg::_ShowWindow, this, hWnd).detach();
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_1_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[0] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[0] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_1_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_2_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[1] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[1] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_2_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_3_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_3:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[2] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[2] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_3_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_4_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_4:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[3] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[3] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_4_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_5_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_5:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[4] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[4] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_5_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_6_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_6:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[5] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[5] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_6_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_7_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_7:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[6] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[6] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_7_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_8_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_8:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[7] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[7] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_8_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_9_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_9:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[8] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[8] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_9_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_10_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_10:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[9] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[9] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_10_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_11_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_11:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[10] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[10] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_11_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_12_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_12:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[11] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[11] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_12_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_13_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_13:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[12] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[12] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_13_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_14_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_14:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[13] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[13] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_14_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_L1_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_L1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[14] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[14] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L1_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_R1_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_R1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[15] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[15] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R1_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_L2_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_L2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[16] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[16] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_L2_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_R2_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_R2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[17] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[17] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_R2_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_LT_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_LT:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[18] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[18] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LT_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_RT_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_RT:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[19] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[19] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RT_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_LX_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_LX:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[20] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[20] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LX_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_LY_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_LY:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[21] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[21] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_LY_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_RX_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_RX:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[22] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[22] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RX_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_RY_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY), TRUE);
				break;
			}
			break;
		}
		case IDC_XOUTPUT_SRCE_RY:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					tape.target_DS4[23] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_DS4);
				}
				else
				{
					tape.target_X360[23] = (byte)SendMessage(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY), CB_GETCURSEL, 0, 0);
					tape.Save(tape.Setting_target_X360);
				}
				PostMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY_STATIC), (result) ? DestinationButton::String((DestButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_XOUTPUT_SRCE_RY_STATIC), SW_SHOW);
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_INSTALL_VJOY:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (vjoylock)
					break;

				vjoylock = true;
				char vJoyStates = xi.GetvJoyState();
				xi.vJoyStates();
				if (vJoyStates == xi.GetvJoyState())
				{
					RECT win;
					GetWindowRect(tape.Ds2hWnd, &win);
					switch (vJoyStates)
					{
					case 0:
					{
						if (MessageBoxPos(m_hDlg, I18N.XOutput_vJoy_Install_text, I18N.XOutput_vJoy_Install_tittle, MB_YESNO, win.left + 100, win.top + 60) == IDYES)
							xi.vJoyInstall();
						break;
					}
					case 1:
					case 2:
					{
						if (MessageBoxPos(m_hDlg, I18N.XOutput_vJoy_Uninstall_text, I18N.XOutput_vJoy_Uninstall_tittle, MB_YESNO, win.left + 100, win.top + 60) == IDYES)
							xi.vJoyUninstall();
						break;
					}
					}
				}
				xi.vJoyStates();
				if (tape.vJoyActive)
					PostMessage(hWnd, WM_DEVICE_SRCE_START, 0, 1);
				InvalidateRect(hWnd, NULL, TRUE);
				vjoylock = false;
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_INSTALL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (vigemlock)
					break;

				vigemlock = true;
				int XOutputState = xi.GetXOutputState();
				xi.XOutputStates();
				if (XOutputState == xi.GetXOutputState())
				{
					switch (XOutputState)
					{
					case 0:
					{
						xi.XOutputInstall();
						break;
					}
					case 1:
					case 2:
					{
						xi.XOutputUninstall();
						break;
					}
					}
				}
				xi.XOutputStates();
				if (tape.XOutputActive)
					PostMessage(hWnd, WM_DEVICE_SRCE_START, 0, 1);
				InvalidateRect(hWnd, NULL, TRUE);
				vigemlock = false;
				break;
			}
			}
			break;
		}
		case IDC_XOUTPUT_STATUS:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (statuslock)
					break;

				statuslock = true;
				int XOutputState = xi.GetXOutputState();
				xi.XOutputStates();
				if (XOutputState == xi.GetXOutputState())
				{
					switch (XOutputState)
					{
					case 1:
						SendMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 0, 0);
						SendMessage(tape.Ds2hWnd, WM_CHANGE_PAD, 1, 0);
						break;
					case 2:
						xi.XOutputEnable();
						break;
					}
				}
				xi.XOutputStates();
				if (tape.XOutputActive)
					PostMessage(hWnd, WM_DEVICE_SRCE_START, 0, 1);
				InvalidateRect(hWnd, NULL, TRUE);
				statuslock = false;
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

void XOutputDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void XOutputDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL XOutputDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
