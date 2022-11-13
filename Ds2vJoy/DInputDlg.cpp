#include "stdafx.h"
#include "DInputDlg.h"
//#include "Source.h"

DInputDlg::DInputDlg()
{
}

DInputDlg::~DInputDlg()
{
}

void DInputDlg::Init()
{
	m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_DINPUT), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));
	Hide();
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_1_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_P1_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_P2_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_P3_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_P4_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_6_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_7_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_8_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_9_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_10_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_11_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_12_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_13_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_14_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_15_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_16_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_17_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_18_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_19_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_20_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_21_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_22_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_23_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_24_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_25_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_26_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_27_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_28_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_29_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_30_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_31_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_32_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_L1_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_R1_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_L2_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_R2_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_LT_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_RT_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_LX_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_LY_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_RX_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_RY_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_S0_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_S1_STATIC, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_P1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_P2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_P3, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_P4, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_6, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_7, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_8, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_9, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_10, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_11, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_12, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_13, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_14, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_15, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_16, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_17, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_18, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_19, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_20, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_21, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_22, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_23, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_24, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_25, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_26, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_27, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_28, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_29, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_30, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_31, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_32, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_L1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_R1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_L2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_R2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_LT, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_RT, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_LX, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_LY, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_RX, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_RY, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_S0, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SRCE_S1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_CANCEL, WM_SETFONT, WPARAM(tape.hCancel), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_LOAD1, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_LOAD2, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_LOAD3, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SAVE1, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SAVE2, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_SAVE3, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_CLEAR, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_DINPUT_CTRLPANEL, WM_SETFONT, WPARAM(tape.hButton2), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_DINPUT_CANCEL), I18N.DINPUT_CANCEL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_DINPUT_LOAD1), I18N.DINPUT_LOAD1);
	SetWindowText(GetDlgItem(m_hDlg, IDC_DINPUT_LOAD2), I18N.DINPUT_LOAD2);
	SetWindowText(GetDlgItem(m_hDlg, IDC_DINPUT_LOAD3), I18N.DINPUT_LOAD3);
	SetWindowText(GetDlgItem(m_hDlg, IDC_DINPUT_SAVE1), I18N.DINPUT_SAVE1);
	SetWindowText(GetDlgItem(m_hDlg, IDC_DINPUT_SAVE2), I18N.DINPUT_SAVE2);
	SetWindowText(GetDlgItem(m_hDlg, IDC_DINPUT_SAVE3), I18N.DINPUT_SAVE3);
	SetWindowText(GetDlgItem(m_hDlg, IDC_DINPUT_CLEAR), I18N.DINPUT_CLEAR);
	SetWindowText(GetDlgItem(m_hDlg, IDC_DINPUT_CTRLPANEL), I18N.DINPUT_CTRLPANEL);

	m_h1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_1_STATIC), I18N.HELP_DINPUT_1);
	m_hP1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_P1_STATIC), I18N.HELP_DINPUT_P1);
	m_hP2 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_P2_STATIC), I18N.HELP_DINPUT_P2);
	m_hP3 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_P3_STATIC), I18N.HELP_DINPUT_P3);
	m_hP4 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_P4_STATIC), I18N.HELP_DINPUT_P4);
	m_h6 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_6_STATIC), I18N.HELP_DINPUT_6);
	m_h7 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_7_STATIC), I18N.HELP_DINPUT_7);
	m_h8 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_8_STATIC), I18N.HELP_DINPUT_8);
	m_h9 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_9_STATIC), I18N.HELP_DINPUT_9);
	m_h10 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_10_STATIC), I18N.HELP_DINPUT_10);
	m_h11 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_11_STATIC), I18N.HELP_DINPUT_11);
	m_h12 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_12_STATIC), I18N.HELP_DINPUT_12);
	m_h13 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_13_STATIC), I18N.HELP_DINPUT_13);
	m_h14 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_14_STATIC), I18N.HELP_DINPUT_14);
	m_h15 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_15_STATIC), I18N.HELP_DINPUT_15);
	m_h16 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_16_STATIC), I18N.HELP_DINPUT_16);
	m_h17 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_17_STATIC), I18N.HELP_DINPUT_17);
	m_h18 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_18_STATIC), I18N.HELP_DINPUT_18);
	m_h19 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_19_STATIC), I18N.HELP_DINPUT_19);
	m_h20 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_20_STATIC), I18N.HELP_DINPUT_20);
	m_h21 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_21_STATIC), I18N.HELP_DINPUT_21);
	m_h22 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_22_STATIC), I18N.HELP_DINPUT_22);
	m_h23 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_23_STATIC), I18N.HELP_DINPUT_23);
	m_h24 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_24_STATIC), I18N.HELP_DINPUT_24);
	m_h25 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_25_STATIC), I18N.HELP_DINPUT_25);
	m_h26 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_26_STATIC), I18N.HELP_DINPUT_26);
	m_h27 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_27_STATIC), I18N.HELP_DINPUT_27);
	m_h28 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_28_STATIC), I18N.HELP_DINPUT_28);
	m_h29 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_29_STATIC), I18N.HELP_DINPUT_29);
	m_h30 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_30_STATIC), I18N.HELP_DINPUT_30);
	m_h31 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_31_STATIC), I18N.HELP_DINPUT_31);
	m_h32 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_32_STATIC), I18N.HELP_DINPUT_32);
	m_hL1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_L1_STATIC), I18N.HELP_DINPUT_L1);
	m_hR1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_R1_STATIC), I18N.HELP_DINPUT_R1);
	m_hL2 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_L2_STATIC), I18N.HELP_DINPUT_L2);
	m_hR2 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_R2_STATIC), I18N.HELP_DINPUT_R2);
	m_hLT = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_LT_STATIC), I18N.HELP_DINPUT_LT);
	m_hRT = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_RT_STATIC), I18N.HELP_DINPUT_RT);
	m_hLX = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_LX_STATIC), I18N.HELP_DINPUT_LX);
	m_hLY = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_LY_STATIC), I18N.HELP_DINPUT_LY);
	m_hRX = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_RX_STATIC), I18N.HELP_DINPUT_RX);
	m_hRY = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_RY_STATIC), I18N.HELP_DINPUT_RY);
	m_hS0 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_S0_STATIC), I18N.HELP_DINPUT_S0);
	m_hS1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_S1_STATIC), I18N.HELP_DINPUT_S1);
}

void DInputDlg::_InitDialog(HWND hWnd)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	const WCHAR* str = WCHARI();
	for (int i = 0; i < Source::DIAxisID_Count; i++)
	{
		str = Source::DIAxisString((SrceDIAxisID)i);
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_LT, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_RT, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_LX, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_LY, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_RX, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_RY, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_S0, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_S1, CB_ADDSTRING, 0, LPARAM(str));
	}
	for (int i = 0; i < Source::DIPOVID_Count; i++)
	{
		str = Source::DIPOVString((SrceDIPOVID)i);
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_P1, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_P2, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_P3, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_P4, CB_ADDSTRING, 0, LPARAM(str));
	}
	for (int i = 0; i < Source::DIButtonID_Count; i++)
	{
		str = Source::DIButtonString((SrceDIButtonID)i);
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_6, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_7, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_8, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_9, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_10, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_11, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_12, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_13, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_14, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_15, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_16, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_L1, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_R1, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_L2, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_R2, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_17, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_18, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_19, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_20, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_21, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_22, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_23, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_24, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_25, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_26, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_27, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_28, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_29, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_30, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_31, CB_ADDSTRING, 0, LPARAM(str));
		SendDlgItemMessage(hWnd, IDC_DINPUT_SRCE_32, CB_ADDSTRING, 0, LPARAM(str));
	}
	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void DInputDlg::_ShowWindow(HWND hWnd)
{
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LT), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_L2TR], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RT), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_R2TR], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LX), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_LX], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LY), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_LY], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RX), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_RX], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RY), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_RY], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S0), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_SL0], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S1), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_SL1], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P1), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_DPAD], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P2), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_DPAD2], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P3), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_DPAD3], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P4), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_DPAD4], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_1), CB_SETCURSEL,  tape.diDispatch[SrceDispatchID::Dispatch_L3], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_6), CB_SETCURSEL,  tape.diDispatch[SrceDispatchID::Dispatch_SHARE], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_7), CB_SETCURSEL,  tape.diDispatch[SrceDispatchID::Dispatch_OPTIONS], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_8), CB_SETCURSEL,  tape.diDispatch[SrceDispatchID::Dispatch_SQUARE], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_9), CB_SETCURSEL,  tape.diDispatch[SrceDispatchID::Dispatch_TRIANGLE], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_10), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_CIRCLE], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_11), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_CROSS], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_12), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_R3], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_13), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_PS], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_14), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_TOUCH], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_15), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_MUTE], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_16), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON16], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L1), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_L1], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R1), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_R1], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L2), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_L2], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R2), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_R2], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_17), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON17], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_18), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON18], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_19), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON19], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_20), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON20], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_21), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON21], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_22), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON22], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_23), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON23], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_24), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON24], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_25), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON25], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_26), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON26], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_27), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON27], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_28), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON28], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_29), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON29], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_30), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON30], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_31), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON31], 0);
	SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_32), CB_SETCURSEL, tape.diDispatch[SrceDispatchID::Dispatch_BUTTON32], 0);

	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LT_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_L2TR]) ? Source::DIAxisString((SrceDIAxisID)tape.diDispatch[SrceDispatchID::Dispatch_L2TR]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RT_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_R2TR]) ? Source::DIAxisString((SrceDIAxisID)tape.diDispatch[SrceDispatchID::Dispatch_R2TR]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LX_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_LX]) ? Source::DIAxisString((SrceDIAxisID)tape.diDispatch[SrceDispatchID::Dispatch_LX]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LY_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_LY]) ? Source::DIAxisString((SrceDIAxisID)tape.diDispatch[SrceDispatchID::Dispatch_LY]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RX_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_RX]) ? Source::DIAxisString((SrceDIAxisID)tape.diDispatch[SrceDispatchID::Dispatch_RX]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RY_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_RY]) ? Source::DIAxisString((SrceDIAxisID)tape.diDispatch[SrceDispatchID::Dispatch_RY]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S0_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_SL0]) ? Source::DIAxisString((SrceDIAxisID)tape.diDispatch[SrceDispatchID::Dispatch_SL0]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S1_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_SL1]) ? Source::DIAxisString((SrceDIAxisID)tape.diDispatch[SrceDispatchID::Dispatch_SL1]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P1_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_DPAD]) ? Source::DIPOVString((SrceDIPOVID)tape.diDispatch[SrceDispatchID::Dispatch_DPAD]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P2_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_DPAD2]) ? Source::DIPOVString((SrceDIPOVID)tape.diDispatch[SrceDispatchID::Dispatch_DPAD2]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P3_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_DPAD3]) ? Source::DIPOVString((SrceDIPOVID)tape.diDispatch[SrceDispatchID::Dispatch_DPAD3]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P4_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_DPAD4]) ? Source::DIPOVString((SrceDIPOVID)tape.diDispatch[SrceDispatchID::Dispatch_DPAD4]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_1_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_L3]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_L3]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_6_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_SHARE]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_SHARE]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_7_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_OPTIONS]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_OPTIONS]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_8_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_SQUARE]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_SQUARE]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_9_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_TRIANGLE]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_TRIANGLE]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_10_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_CIRCLE]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_CIRCLE]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_11_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_CROSS]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_CROSS]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_12_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_R3]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_R3]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_13_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_PS]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_PS]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_14_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_TOUCH]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_TOUCH]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_15_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_MUTE]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_MUTE]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_16_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON16]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON16]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L1_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_L1]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_L1]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R1_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_R1]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_R1]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L2_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_L2]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_L2]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R2_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_R2]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_R2]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_17_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON17]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON17]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_18_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON18]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON18]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_19_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON19]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON19]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_20_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON20]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON20]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_21_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON21]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON21]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_22_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON22]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON22]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_23_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON23]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON23]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_24_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON24]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON24]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_25_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON25]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON25]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_26_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON26]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON26]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_27_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON27]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON27]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_28_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON28]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON28]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_29_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON29]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON29]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_30_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON30]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON30]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_31_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON31]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON31]) : L"...");
	SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_32_STATIC), (tape.diDispatch[SrceDispatchID::Dispatch_BUTTON32]) ? Source::DIButtonString((SrceDIButtonID)tape.diDispatch[SrceDispatchID::Dispatch_BUTTON32]) : L"...");
}

INT_PTR CALLBACK DInputDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DInputDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<DInputDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<DInputDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR DInputDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_BTN);
		if (tape.DarkTheme)
			return (LRESULT)tape.hB_BTN_DARK;
		else
			switch (GetDlgCtrlID((HWND)lParam))
			{
			case IDC_DINPUT_CANCEL:
			{
				return (LRESULT)tape.hB_BTN;
			}
			case IDC_DINPUT_LOAD1:
			case IDC_DINPUT_LOAD2:
			case IDC_DINPUT_LOAD3:
			{
				return (LRESULT)tape.hB_blue;
				break;
			}
			case IDC_DINPUT_SAVE1:
			case IDC_DINPUT_SAVE2:
			case IDC_DINPUT_SAVE3:
			{
				return (LRESULT)tape.hB_red;
				break;
			}
			case IDC_DINPUT_CLEAR:
			{
				return (LRESULT)tape.hB_yellow;
				break;
			}
			case IDC_DINPUT_CTRLPANEL:
			{
				return (LRESULT)tape.hB_grey;
				break;
			}
			}
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
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

			if (!tape.DarkTheme)
			{
				SetRect(&rect, 26,  9,  86,  26);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 304, 9,  364, 26);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 26,  29, 86,  46);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 96, 29,  156,  46);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 234, 29,  294, 46);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 304, 29, 364, 46);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 26,  49, 86,  66);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 304, 49, 364, 66);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 131, 55,  191, 72);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 203, 55,  263, 72);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 52,  75, 112,  92);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 280, 82,  340, 99);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 52,  93, 112,  110);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 52,  111, 112,  128);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 251, 103, 311, 120);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 318, 103, 378, 120);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 52,  129, 112,  146);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 289, 123, 349, 140);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 9,   153, 69,   170);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 76,  153, 136, 170);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 254, 153, 314, 170);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 321, 153, 381, 170);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 76,  173, 136,  190);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 254, 173, 314, 190);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 166, 80,  226, 97);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 166, 117, 226, 134);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 166, 145, 226, 162);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 166, 164, 226, 181);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);

				SetRect(&rect, 8, 198, 60,   215);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 65, 198, 117, 215);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 122, 198, 174, 215);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 179, 198, 231, 215);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 236, 198, 288, 215);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 293, 198, 345, 215);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 350, 198, 402, 215);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 407, 198, 459, 215);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 8, 217, 60,  234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 65, 217, 117, 234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 122, 217, 174, 234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 179, 217, 231, 234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 236, 217, 288, 234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 293, 217, 345, 234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 350, 217, 402, 234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
				SetRect(&rect, 407, 217, 459, 234);
				FrameRect(hDC, &rect, tape.hB_EDIT_BORDER);
			}

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
			std::thread(&DInputDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&DInputDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_DINPUT_CANCEL:
		case IDC_DINPUT_LOAD1:
		case IDC_DINPUT_LOAD2:
		case IDC_DINPUT_LOAD3:
		case IDC_DINPUT_SAVE1:
		case IDC_DINPUT_SAVE2:
		case IDC_DINPUT_SAVE3:
		case IDC_DINPUT_CLEAR:
		case IDC_DINPUT_CTRLPANEL:
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
		case IDC_DINPUT_CANCEL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				PostMessage(tape.Ds2hWnd, WM_SETDINPUT, 0, 1);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_LOAD1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
					tape.diDispatch[i] = tape.diDispatch1[i];
				tape.Save(tape.Setting_Dispatch);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_LOAD2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
					tape.diDispatch[i] = tape.diDispatch2[i];
				tape.Save(tape.Setting_Dispatch);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_LOAD3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
					tape.diDispatch[i] = tape.diDispatch3[i];
				tape.Save(tape.Setting_Dispatch);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SAVE1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
					tape.diDispatch1[i] = tape.diDispatch[i];
				tape.Save(tape.Setting_Dispatch1);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SAVE2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
					tape.diDispatch2[i] = tape.diDispatch[i];
				tape.Save(tape.Setting_Dispatch2);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SAVE3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
					tape.diDispatch3[i] = tape.diDispatch[i];
				tape.Save(tape.Setting_Dispatch3);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_CLEAR:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				for (int i = 0; i < SrceDispatchID::Dispatch_Count; i++)
					tape.diDispatch[i] = 0;
				tape.Save(tape.Setting_Dispatch);
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_CTRLPANEL:
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
		case IDC_DINPUT_SRCE_LT_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LT), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_LT:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_L2TR] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LT), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LT_STATIC), (result) ? Source::DIAxisString((SrceDIAxisID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LT_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LT_STATIC), SW_SHOW);
				DestroyWindow(m_hLT);
				m_hLT = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_LT_STATIC), I18N.HELP_DINPUT_LT);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_RT_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RT), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_RT:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_R2TR] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RT), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RT_STATIC), (result) ? Source::DIAxisString((SrceDIAxisID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RT_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RT_STATIC), SW_SHOW);
				DestroyWindow(m_hRT);
				m_hRT = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_RT_STATIC), I18N.HELP_DINPUT_RT);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_LX_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LX), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_LX:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_LX] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LX), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LX_STATIC), (result) ? Source::DIAxisString((SrceDIAxisID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LX_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LX_STATIC), SW_SHOW);
				DestroyWindow(m_hLX);
				m_hLX = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_LX_STATIC), I18N.HELP_DINPUT_LX);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_LY_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LY), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_LY:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_LY] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LY), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LY_STATIC), (result) ? Source::DIAxisString((SrceDIAxisID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LY_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_LY_STATIC), SW_SHOW);
				DestroyWindow(m_hLY);
				m_hLY = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_LY_STATIC), I18N.HELP_DINPUT_LY);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_RX_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RX), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_RX:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_RX] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RX), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RX_STATIC), (result) ? Source::DIAxisString((SrceDIAxisID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RX_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RX_STATIC), SW_SHOW);
				DestroyWindow(m_hRX);
				m_hRX = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_RX_STATIC), I18N.HELP_DINPUT_RX);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_RY_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RY), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_RY:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_RY] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RY), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RY_STATIC), (result) ? Source::DIAxisString((SrceDIAxisID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RY_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_RY_STATIC), SW_SHOW);
				DestroyWindow(m_hRY);
				m_hRY = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_RY_STATIC), I18N.HELP_DINPUT_RY);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_S0_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S0), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_S0:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_SL0] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S0), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S0_STATIC), (result) ? Source::DIAxisString((SrceDIAxisID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S0_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S0_STATIC), SW_SHOW);
				DestroyWindow(m_hS0);
				m_hS0 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_S0_STATIC), I18N.HELP_DINPUT_S0);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_S1_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S1), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_S1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_SL1] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S1), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S1_STATIC), (result) ? Source::DIAxisString((SrceDIAxisID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S1_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_S1_STATIC), SW_SHOW);
				DestroyWindow(m_hS1);
				m_hS1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_S1_STATIC), I18N.HELP_DINPUT_S1);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_1_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_1), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_L3] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_1), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_1_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_1_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_1_STATIC), SW_SHOW);
				DestroyWindow(m_h1);
				m_h1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_1_STATIC), I18N.HELP_DINPUT_1);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_P1_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P1), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_P1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_DPAD] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P1), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P1_STATIC), (result) ? Source::DIPOVString((SrceDIPOVID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P1_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P1_STATIC), SW_SHOW);
				DestroyWindow(m_hP1);
				m_hP1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_P1_STATIC), I18N.HELP_DINPUT_P1);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_P2_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P2), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_P2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_DPAD2] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P2), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P2_STATIC), (result) ? Source::DIPOVString((SrceDIPOVID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P2_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P2_STATIC), SW_SHOW);
				DestroyWindow(m_hP2);
				m_hP2 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_P1_STATIC), I18N.HELP_DINPUT_P2);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_P3_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P3), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_P3:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_DPAD3] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P3), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P3_STATIC), (result) ? Source::DIPOVString((SrceDIPOVID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P3_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P3_STATIC), SW_SHOW);
				DestroyWindow(m_hP3);
				m_hP3 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_P3_STATIC), I18N.HELP_DINPUT_P3);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_P4_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P4), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_P4:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_DPAD4] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P4), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P4_STATIC), (result) ? Source::DIPOVString((SrceDIPOVID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P4_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_P4_STATIC), SW_SHOW);
				DestroyWindow(m_hP4);
				m_hP4 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_P4_STATIC), I18N.HELP_DINPUT_P4);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_6_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_6), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_6:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_SHARE] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_6), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_6_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_6_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_6_STATIC), SW_SHOW);
				DestroyWindow(m_h6);
				m_h6 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_6_STATIC), I18N.HELP_DINPUT_6);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_7_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_7), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_7:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_OPTIONS] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_7), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_7_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_7_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_7_STATIC), SW_SHOW);
				DestroyWindow(m_h7);
				m_h7 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_7_STATIC), I18N.HELP_DINPUT_7);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_8_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_8), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_8:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_SQUARE] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_8), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_8_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_8_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_8_STATIC), SW_SHOW);
				DestroyWindow(m_h8);
				m_h8 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_8_STATIC), I18N.HELP_DINPUT_8);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_9_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_9), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_9:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_TRIANGLE] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_9), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_9_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_9_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_9_STATIC), SW_SHOW);
				DestroyWindow(m_h9);
				m_h9 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_9_STATIC), I18N.HELP_DINPUT_9);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_10_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_10), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_10:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_CIRCLE] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_10), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_10_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_10_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_10_STATIC), SW_SHOW);
				DestroyWindow(m_h10);
				m_h10 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_10_STATIC), I18N.HELP_DINPUT_10);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_11_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_11), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_11:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_CROSS] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_11), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_11_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_11_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_11_STATIC), SW_SHOW);
				DestroyWindow(m_h11);
				m_h11 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_11_STATIC), I18N.HELP_DINPUT_11);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_12_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_12), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_12:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_R3] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_12), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_12_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_12_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_12_STATIC), SW_SHOW);
				DestroyWindow(m_h12);
				m_h12 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_12_STATIC), I18N.HELP_DINPUT_12);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_13_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_13), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_13:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_PS] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_13), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_13_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_13_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_13_STATIC), SW_SHOW);
				DestroyWindow(m_h13);
				m_h13 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_13_STATIC), I18N.HELP_DINPUT_13);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_14_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_14), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_14:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_TOUCH] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_14), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_14_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_14_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_14_STATIC), SW_SHOW);
				DestroyWindow(m_h14);
				m_h14 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_14_STATIC), I18N.HELP_DINPUT_14);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_15_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_15), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_15:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_MUTE] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_15), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_15_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_15_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_15_STATIC), SW_SHOW);
				DestroyWindow(m_h15);
				m_h15 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_15_STATIC), I18N.HELP_DINPUT_15);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_16_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_16), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_16:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON16] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_16), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_16_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_16_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_16_STATIC), SW_SHOW);
				DestroyWindow(m_h16);
				m_h16 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_16_STATIC), I18N.HELP_DINPUT_16);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_L1_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L1), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_L1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_L1] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L1), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L1_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L1_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L1_STATIC), SW_SHOW);
				DestroyWindow(m_hL1);
				m_hL1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_L1_STATIC), I18N.HELP_DINPUT_L1);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_R1_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R1), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_R1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_R1] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R1), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R1_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R1_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R1_STATIC), SW_SHOW);
				DestroyWindow(m_hR1);
				m_hR1 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_R1_STATIC), I18N.HELP_DINPUT_R1);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_L2_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L2), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_L2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_L2] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L2), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L2_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L2_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_L2_STATIC), SW_SHOW);
				DestroyWindow(m_hL2);
				m_hL2 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_L2_STATIC), I18N.HELP_DINPUT_L2);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_R2_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R2), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_R2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_R2] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R2), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R2_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R2_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_R2_STATIC), SW_SHOW);
				DestroyWindow(m_hR2);
				m_hR2 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_R2_STATIC), I18N.HELP_DINPUT_R2);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_17_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_17), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_17:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON17] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_17), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_17_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_17_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_17_STATIC), SW_SHOW);
				DestroyWindow(m_h17);
				m_h17 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_17_STATIC), I18N.HELP_DINPUT_17);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_18_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_18), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_18:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON18] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_18), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_18_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_18_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_18_STATIC), SW_SHOW);
				DestroyWindow(m_h18);
				m_h18 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_18_STATIC), I18N.HELP_DINPUT_18);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_19_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_19), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_19:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON19] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_19), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_19_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_19_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_19_STATIC), SW_SHOW);
				DestroyWindow(m_h19);
				m_h19 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_19_STATIC), I18N.HELP_DINPUT_16);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_20_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_20), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_20:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON20] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_20), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_20_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_20_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_20_STATIC), SW_SHOW);
				DestroyWindow(m_h20);
				m_h20 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_20_STATIC), I18N.HELP_DINPUT_20);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_21_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_21), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_21:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON21] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_21), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_21_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_21_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_21_STATIC), SW_SHOW);
				DestroyWindow(m_h21);
				m_h21 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_21_STATIC), I18N.HELP_DINPUT_21);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_22_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_22), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_22:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON22] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_22), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_22_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_22_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_22_STATIC), SW_SHOW);
				DestroyWindow(m_h22);
				m_h22 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_22_STATIC), I18N.HELP_DINPUT_22);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_23_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_23), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_23:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON23] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_23), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_23_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_23_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_23_STATIC), SW_SHOW);
				DestroyWindow(m_h23);
				m_h23 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_23_STATIC), I18N.HELP_DINPUT_23);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_24_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_24), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_24:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON24] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_24), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_24_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_24_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_24_STATIC), SW_SHOW);
				DestroyWindow(m_h24);
				m_h24 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_24_STATIC), I18N.HELP_DINPUT_24);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_25_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_25), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_25:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON25] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_25), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_25_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_25_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_25_STATIC), SW_SHOW);
				DestroyWindow(m_h25);
				m_h25 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_25_STATIC), I18N.HELP_DINPUT_25);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_26_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_26), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_26:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON26] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_26), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_26_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_26_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_26_STATIC), SW_SHOW);
				DestroyWindow(m_h26);
				m_h26 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_26_STATIC), I18N.HELP_DINPUT_26);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_27_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_27), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_27:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON27] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_27), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_27_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_27_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_27_STATIC), SW_SHOW);
				DestroyWindow(m_h27);
				m_h27 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_27_STATIC), I18N.HELP_DINPUT_27);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_28_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_28), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_28:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON28] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_28), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_28_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_28_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_28_STATIC), SW_SHOW);
				DestroyWindow(m_h28);
				m_h28 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_28_STATIC), I18N.HELP_DINPUT_28);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_29_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_29), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_29:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON29] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_29), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_29_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_29_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_29_STATIC), SW_SHOW);
				DestroyWindow(m_h29);
				m_h29 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_29_STATIC), I18N.HELP_DINPUT_29);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_30_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_30), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_30:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON30] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_30), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_30_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_30_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_30_STATIC), SW_SHOW);
				DestroyWindow(m_h30);
				m_h30 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_30_STATIC), I18N.HELP_DINPUT_30);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_31_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_31), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_31:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON31] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_31), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_31_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_31_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_31_STATIC), SW_SHOW);
				DestroyWindow(m_h31);
				m_h31 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_31_STATIC), I18N.HELP_DINPUT_31);
				break;
			}
			}
			break;
		}
		case IDC_DINPUT_SRCE_32_STATIC:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_DINPUT_SRCE_32), TRUE);
				break;
			}
			break;
		}
		case IDC_DINPUT_SRCE_32:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				tape.diDispatch[SrceDispatchID::Dispatch_BUTTON32] = (byte)SendMessage(GetDlgItem(hWnd, IDC_DINPUT_SRCE_32), CB_GETCURSEL, 0, 0);
				tape.Save(tape.Setting_Dispatch);
				break;
			}
			case CBN_CLOSEUP:
			{
				byte result = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(GetDlgItem(hWnd, IDC_DINPUT_SRCE_32_STATIC), (result) ? Source::DIButtonString((SrceDIButtonID)result) : L"...");
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_32_STATIC), SW_HIDE);
				::ShowWindow(GetDlgItem(hWnd, IDC_DINPUT_SRCE_32_STATIC), SW_SHOW);
				DestroyWindow(m_h32);
				m_h32 = CreateToolTip(m_hDlg, GetDlgItem(m_hDlg, IDC_DINPUT_SRCE_32_STATIC), I18N.HELP_DINPUT_32);
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

void DInputDlg::Show()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void DInputDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL DInputDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
