#include "stdafx.h"
#include "MappingDataDlg.h"

MappingDataDlg::MappingDataDlg()
{
}

MappingDataDlg::~MappingDataDlg()
{
	DeleteObject(hbrush_z01);
	DeleteObject(hbrush_z02);
	DeleteObject(hbrush_z03);
	DeleteObject(hbrush_z04);
	DeleteObject(hbrush_z05);
	DeleteObject(hbrush_z06);
	DeleteObject(hbrush_z07);
	DeleteObject(hbrush_z08);
	DeleteObject(hbrush_z09);
	DeleteObject(hbrush_z10);
	DeleteObject(hbrush_z11);
	DeleteObject(hbrush_z12);
	DeleteObject(hbrush_z13);
	DeleteObject(hbrush_z14);
	DeleteObject(hbrush_z15);
	DeleteObject(hbrush_z16);
	DeleteObject(hbrush_z17);
	DeleteObject(hbrush_z18);
	DeleteObject(hbrush_z19);
	DeleteObject(hbrush_z20);
	DeleteObject(hbrush_z21);
	DeleteObject(hbrush_z22);
}

void MappingDataDlg::Init()
{
	m_mode = 0;
	docked = 1;
	docked_last = 1;
	m_hDlg = CreateDialogParam(tape.Ds2hInst, MAKEINTRESOURCE(IDD_MAPPING_ADD), tape.Ds2hWnd, (DLGPROC)Proc, LPARAM(this));
	Hide();

	int lStyle = GetWindowLong(m_hDlg, GWL_STYLE);
	lStyle = lStyle & ~WS_CAPTION;
	SetWindowLong(m_hDlg, GWL_STYLE, lStyle);

	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_3, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_4, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_5, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_3, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_4, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_5, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_6, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_7, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_8, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_LED, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_1_START, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_2_START, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_3_START, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_4_START, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_5_START, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_6_START, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_7_START, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_8_START, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_1_STOP, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_2_STOP, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_3_STOP, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_4_STOP, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_5_STOP, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_6_STOP, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_7_STOP, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_8_STOP, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_GRID_X, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_GRID_Y, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_GRID_W, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_GRID_H, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_GRID_NW, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_GRID_NH, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_X, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_Y, WM_SETFONT, WPARAM(tape.hEdit3), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_CANCEL, WM_SETFONT, WPARAM(tape.hCancel), MAKELPARAM(TRUE, 0));
	
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_IF_MOUSE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_FORCE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SHORT, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DOUBLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_LONG, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MACRO, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_PAUSE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_TRANSITIVITY, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_TOGGLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_2_OR, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_3_OR, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_4_NOT, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_5_NOT, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_TARGET_1, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_TARGET_2, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_TARGET_3, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_TARGET_4, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_TARGET_5, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_1_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_2_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_3_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_4_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SRCE_5_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ONRELEASE_1, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ONRELEASE_2, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ONRELEASE_3, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ONRELEASE_4, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ONRELEASE_5, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ONRELEASE_6, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ONRELEASE_7, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ONRELEASE_8, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NORELEASE_1, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NORELEASE_2, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NORELEASE_3, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NORELEASE_4, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NORELEASE_5, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NORELEASE_6, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NORELEASE_7, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NORELEASE_8, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NLRELEASE_1, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NLRELEASE_2, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NLRELEASE_3, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NLRELEASE_4, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NLRELEASE_5, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NLRELEASE_6, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NLRELEASE_7, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_NLRELEASE_8, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ACTION_1, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ACTION_2, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ACTION_3, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ACTION_4, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ACTION_5, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ACTION_6, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ACTION_7, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_ACTION_8, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_OVERCONTROL_1, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_OVERCONTROL_2, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_OVERCONTROL_3, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_OVERCONTROL_4, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_OVERCONTROL_5, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_OVERCONTROL_6, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_OVERCONTROL_7, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_OVERCONTROL_8, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SWITCH_1, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SWITCH_2, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SWITCH_3, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SWITCH_4, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SWITCH_5, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SWITCH_6, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SWITCH_7, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_SWITCH_8, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_1_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_2_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_3_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_4_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_5_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_6_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_7_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_DEST_8_DISABLE, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_01, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_02, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_03, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_04, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_05, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_11, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_12, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_13, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_14, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_15, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_21, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_22, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_23, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_24, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_25, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_MAPPING_MOUSE_GRID, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));

	SetWindowText(GetDlgItem(m_hDlg, IDC_MAPPING_HELP), I18N.MAPPING_HELP);
	SetWindowText(GetDlgItem(m_hDlg, IDC_MAPPING_OK), I18N.MAPPING_OK);
	SetWindowText(GetDlgItem(m_hDlg, IDC_MAPPING_CLEAR), I18N.MAPPING_CLEAR);
	SetWindowText(GetDlgItem(m_hDlg, IDC_MAPPING_CANCEL), I18N.MAPPING_CANCEL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_MAPPING_X), I18N.MAPPING_X);
	SetWindowText(GetDlgItem(m_hDlg, IDC_MAPPING_Y), I18N.MAPPING_Y);
	SetWindowText(GetDlgItem(m_hDlg, IDC_MIND_OK), I18N.MIND_OK);
	SetWindowText(GetDlgItem(m_hDlg, IDC_MIND_CANCEL), I18N.MIND_CANCEL);

	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_1), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_2), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_3), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_4), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_5), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_LED), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_1), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_2), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_3), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_4), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_5), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_6), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_7), 0);
	ComboBox_SetMinVisible(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_8), 0);

	COMBOBOXINFO info = { sizeof(COMBOBOXINFO) };
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_1), &info); m_lists[0] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_2), &info); m_lists[1] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_3), &info); m_lists[2] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_4), &info); m_lists[3] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_5), &info); m_lists[4] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_LED), &info); m_lists[5] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_1), &info); m_lists[6] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_2), &info); m_lists[7] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_3), &info); m_lists[8] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_4), &info); m_lists[9] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_5), &info); m_lists[10] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_6), &info); m_lists[11] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_7), &info); m_lists[12] = info.hwndList;
	GetComboBoxInfo(GetDlgItem(m_hDlg, IDC_MAPPING_DEST_8), &info); m_lists[13] = info.hwndList;
	for (int i = 0; i < 14; i++)
		if (m_lists[i])
			::MoveWindow(m_lists[i], 0, 0, 50, 288, FALSE);

	HBITMAP m_background = LoadBitmap(tape.Ds2hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	HDC srcDC = CreateCompatibleDC(GetDC(NULL));
	HDC newDC = CreateCompatibleDC(GetDC(NULL));
	HBITMAP srcBitmap = (HBITMAP)SelectObject(srcDC, m_background);

	HBITMAP destBitmap = CreateBitmap(26, 13, 1, 32, NULL);
	HBITMAP newBitmap = (HBITMAP)SelectObject(newDC, destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 124, 87, SRCCOPY); hbrush_z01 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 215, 87, SRCCOPY); hbrush_z02 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 306, 87, SRCCOPY); hbrush_z03 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 397, 87, SRCCOPY); hbrush_z04 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 124, 143, SRCCOPY); hbrush_z05 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 215, 143, SRCCOPY); hbrush_z06 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 306, 143, SRCCOPY); hbrush_z07 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 397, 143, SRCCOPY); hbrush_z08 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 166, 87, SRCCOPY); hbrush_z09 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 257, 87, SRCCOPY); hbrush_z10 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 348, 87, SRCCOPY); hbrush_z11 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 439, 87, SRCCOPY); hbrush_z12 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 166, 143, SRCCOPY); hbrush_z13 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 257, 143, SRCCOPY); hbrush_z14 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 348, 143, SRCCOPY); hbrush_z15 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 439, 143, SRCCOPY); hbrush_z16 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 275, 214, SRCCOPY); hbrush_z17 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 275, 234, SRCCOPY); hbrush_z18 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 308, 214, SRCCOPY); hbrush_z19 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 308, 234, SRCCOPY); hbrush_z20 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 341, 214, SRCCOPY); hbrush_z21 = CreatePatternBrush(destBitmap);
	BitBlt(newDC, 0, 0, 26, 13, srcDC, 341, 234, SRCCOPY); hbrush_z22 = CreatePatternBrush(destBitmap);

	SelectObject(srcDC, srcBitmap);
	SelectObject(newDC, newBitmap);
	DeleteDC(srcDC);
	DeleteDC(newDC);
	
	mouseoverCB.push_back(IDC_MAPPING_ONRELEASE_1);
	mouseoverCB.push_back(IDC_MAPPING_ONRELEASE_2);
	mouseoverCB.push_back(IDC_MAPPING_ONRELEASE_3);
	mouseoverCB.push_back(IDC_MAPPING_ONRELEASE_4);
	mouseoverCB.push_back(IDC_MAPPING_ONRELEASE_5);
	mouseoverCB.push_back(IDC_MAPPING_ONRELEASE_6);
	mouseoverCB.push_back(IDC_MAPPING_ONRELEASE_7);
	mouseoverCB.push_back(IDC_MAPPING_ONRELEASE_8);

	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_IF_MOUSE), I18N.HELP_IFMOUSE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_FORCE), I18N.HELP_FORCE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SHORT), I18N.HELP_SHORT);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DOUBLE), I18N.HELP_DOUBLE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_LONG), I18N.HELP_LONG);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_2_OR), I18N.HELP_ORXOR);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_3_OR), I18N.HELP_ORXOR);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_4_NOT), I18N.HELP_NOT);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_5_NOT), I18N.HELP_NOT);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_TARGET_1), I18N.HELP_SOURCE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_TARGET_2), I18N.HELP_SOURCE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_TARGET_3), I18N.HELP_SOURCE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_TARGET_4), I18N.HELP_SOURCE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_TARGET_5), I18N.HELP_SOURCE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ACTION_1), I18N.HELP_DESTINATION);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ACTION_2), I18N.HELP_DESTINATION);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ACTION_3), I18N.HELP_DESTINATION);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ACTION_4), I18N.HELP_DESTINATION);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ACTION_5), I18N.HELP_DESTINATION);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ACTION_6), I18N.HELP_DESTINATION);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ACTION_7), I18N.HELP_DESTINATION);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ACTION_8), I18N.HELP_DESTINATION);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_1_DISABLE), I18N.HELP_DISABLING_S);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_2_DISABLE), I18N.HELP_DISABLING_S);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_3_DISABLE), I18N.HELP_DISABLING_S);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_4_DISABLE), I18N.HELP_DISABLING_S);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SRCE_5_DISABLE), I18N.HELP_DISABLING_S);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_1_DISABLE), I18N.HELP_DISABLING_D);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_2_DISABLE), I18N.HELP_DISABLING_D);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_3_DISABLE), I18N.HELP_DISABLING_D);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_4_DISABLE), I18N.HELP_DISABLING_D);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_5_DISABLE), I18N.HELP_DISABLING_D);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_6_DISABLE), I18N.HELP_DISABLING_D);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_7_DISABLE), I18N.HELP_DISABLING_D);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_8_DISABLE), I18N.HELP_DISABLING_D);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MACRO), I18N.HELP_MACRO);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_PAUSE), I18N.HELP_PAUSE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_TRANSITIVITY), I18N.HELP_TRANSITIVITY);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_TOGGLE), I18N.HELP_TOGGLE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SWITCH_1), I18N.HELP_SWITCH);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SWITCH_2), I18N.HELP_SWITCH);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SWITCH_3), I18N.HELP_SWITCH);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SWITCH_4), I18N.HELP_SWITCH);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SWITCH_5), I18N.HELP_SWITCH);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SWITCH_6), I18N.HELP_SWITCH);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SWITCH_7), I18N.HELP_SWITCH);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_SWITCH_8), I18N.HELP_SWITCH);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_OVERCONTROL_1), I18N.HELP_OVERCONTROL);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_OVERCONTROL_2), I18N.HELP_OVERCONTROL);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_OVERCONTROL_3), I18N.HELP_OVERCONTROL);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_OVERCONTROL_4), I18N.HELP_OVERCONTROL);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_OVERCONTROL_5), I18N.HELP_OVERCONTROL);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_OVERCONTROL_6), I18N.HELP_OVERCONTROL);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_OVERCONTROL_7), I18N.HELP_OVERCONTROL);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_OVERCONTROL_8), I18N.HELP_OVERCONTROL);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_1_START), I18N.HELP_START);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_2_START), I18N.HELP_START);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_3_START), I18N.HELP_START);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_4_START), I18N.HELP_START);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_5_START), I18N.HELP_START);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_6_START), I18N.HELP_START);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_7_START), I18N.HELP_START);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_8_START), I18N.HELP_START);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_1_STOP), I18N.HELP_END);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_2_STOP), I18N.HELP_END);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_3_STOP), I18N.HELP_END);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_4_STOP), I18N.HELP_END);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_5_STOP), I18N.HELP_END);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_6_STOP), I18N.HELP_END);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_7_STOP), I18N.HELP_END);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_DEST_8_STOP), I18N.HELP_END);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ONRELEASE_1), I18N.HELP_ONRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ONRELEASE_2), I18N.HELP_ONRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ONRELEASE_3), I18N.HELP_ONRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ONRELEASE_4), I18N.HELP_ONRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ONRELEASE_5), I18N.HELP_ONRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ONRELEASE_6), I18N.HELP_ONRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ONRELEASE_7), I18N.HELP_ONRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_ONRELEASE_8), I18N.HELP_ONRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_1), I18N.HELP_NORELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_2), I18N.HELP_NORELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_3), I18N.HELP_NORELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_4), I18N.HELP_NORELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_5), I18N.HELP_NORELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_6), I18N.HELP_NORELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_7), I18N.HELP_NORELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_8), I18N.HELP_NORELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_1), I18N.HELP_NLRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_2), I18N.HELP_NLRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_3), I18N.HELP_NLRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_4), I18N.HELP_NLRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_5), I18N.HELP_NLRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_6), I18N.HELP_NLRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_7), I18N.HELP_NLRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_8), I18N.HELP_NLRELEASE);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_01), I18N.HELP_MOUSE_L1);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_02), I18N.HELP_MOUSE_L2);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_03), I18N.HELP_MOUSE_L3);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_04), I18N.HELP_MOUSE_L4);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_05), I18N.HELP_MOUSE_L5);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_11), I18N.HELP_MOUSE_T1);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_12), I18N.HELP_MOUSE_T2);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_13), I18N.HELP_MOUSE_T3);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_14), I18N.HELP_MOUSE_T4);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_15), I18N.HELP_MOUSE_T5);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_21), I18N.HELP_MOUSE_R1);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_22), I18N.HELP_MOUSE_R2);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_23), I18N.HELP_MOUSE_R3);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_24), I18N.HELP_MOUSE_R4);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_25), I18N.HELP_MOUSE_R5);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_MOUSE_GRID), I18N.HELP_MOUSE_GRID);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_GRID_X), I18N.HELP_GRID_X);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_GRID_Y), I18N.HELP_GRID_Y);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_GRID_W), I18N.HELP_GRID_W);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_GRID_H), I18N.HELP_GRID_H);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_GRID_NW), I18N.HELP_GRID_NW);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_GRID_NH), I18N.HELP_GRID_NH);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_X), I18N.HELP_DIGITS);
	CreateToolTip(tape.Ds2hWnd, GetDlgItem(m_hDlg, IDC_MAPPING_Y), I18N.HELP_DIGITS);
}

void MappingDataDlg::Open(HWND parent, int mode, int tab)
{
	m_mode = mode;
	m_Tab = tab;
	firsttime = false;
	canprint = false;
	m_rightClickOk = false;

	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_1));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_2));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_3));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_4));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_5));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_6));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_7));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_8));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_1));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_2));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_3));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_4));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_5));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_6));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_7));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_8));

	Show();
	PostMessage(tape.Ds2hWnd, WM_SIZE, -1, -2);
	danger = false;
	capturehasbeendone = false;
	whohasfocus = 0;
	SetTimer(m_hDlg, 2, 50, NULL);
}

void MappingDataDlg::_InitDialog(HWND hWnd)
{
	for (int i = 0; i < Mapping::LedAction_Count; i++)
	{
		WCHAR* str = Mapping::LedString((LedActionID)i);
		SendDlgItemMessage(hWnd, IDC_MAPPING_LED, CB_ADDSTRING, 0, LPARAM(str));
	}
}

INT_PTR CALLBACK MappingDataDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MappingDataDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<MappingDataDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<MappingDataDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR MappingDataDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
//	case WM_NCCALCSIZE:
// 	{
//		if (wParam)
//		{
//			NCCALCSIZE_PARAMS FAR* lpncsp = (NCCALCSIZE_PARAMS FAR*)lParam;
//			lpncsp->rgrc[0].top -= 6;
//			return FALSE;
//			return TRUE;
//		}
//		return FALSE;
//	}
	case WM_CTLCOLORDLG:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_DLG);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_DLG);
		return (LRESULT)tape.hB_DLG;
	}
	case WM_CTLCOLORMSGBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_MSGBOX);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_MSGBOX);
		return (LRESULT)tape.hB_MSGBOX;
	}
	case WM_CTLCOLORBTN:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_BTN);
		SetBkMode(hdcStatic, TRANSPARENT);
		SetBkColor(hdcStatic, tape.Bk_BTN);
		return (LRESULT)tape.hB_BTN;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		DWORD CtrlID = GetDlgCtrlID((HWND)lParam);
		SetBkMode(hdcStatic, TRANSPARENT);
		if (CtrlID == IDC_MAPPING_X || CtrlID == IDC_MAPPING_Y)
		{
			SetBkColor(hdcStatic, tape.Bk_STATIC);
			if (danger)
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_Mouse2);
				return (LRESULT)tape.hB_STATIC_Mouse2;
			}
			else
			{
				SetTextColor(hdcStatic, tape.ink_STATIC_Mouse1);
				return (LRESULT)tape.hB_STATIC_Mouse1;
			}
		}
		else
		{
			SetBkColor(hdcStatic, tape.Bk_STATIC);
			SetTextColor(hdcStatic, tape.ink_POSTIT);
			return (LRESULT)tape.hB_BackGround;
		}
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetBkMode(hdcStatic, TRANSPARENT);
		switch (GetDlgCtrlID((HWND)lParam))
		{
		case IDC_MAPPING_DEST_1_START:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z01;
		}
		case IDC_MAPPING_DEST_2_START:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z02;
		}
		case IDC_MAPPING_DEST_3_START:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z03;
		}
		case IDC_MAPPING_DEST_4_START:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z04;
		}
		case IDC_MAPPING_DEST_5_START:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z05;
		}
		case IDC_MAPPING_DEST_6_START:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z06;
		}
		case IDC_MAPPING_DEST_7_START:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z07;
		}
		case IDC_MAPPING_DEST_8_START:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z08;
		}
		case IDC_MAPPING_DEST_1_STOP:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z09;
		}
		case IDC_MAPPING_DEST_2_STOP:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z10;
		}
		case IDC_MAPPING_DEST_3_STOP:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z11;
		}
		case IDC_MAPPING_DEST_4_STOP:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z12;
		}
		case IDC_MAPPING_DEST_5_STOP:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z13;
		}
		case IDC_MAPPING_DEST_6_STOP:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z14;
		}
		case IDC_MAPPING_DEST_7_STOP:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z15;
		}
		case IDC_MAPPING_DEST_8_STOP:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z16;
		}
		case IDC_MAPPING_GRID_X:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z17;
		}
		case IDC_MAPPING_GRID_Y:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z18;
		}
		case IDC_MAPPING_GRID_W:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z19;
		}
		case IDC_MAPPING_GRID_H:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z20;
		}
		case IDC_MAPPING_GRID_NW:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z21;
		}
		case IDC_MAPPING_GRID_NH:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT_TIMELINE);
			return (LRESULT)hbrush_z22;
		}
		default:
		{
			SetTextColor(hdcStatic, tape.ink_EDIT);
			return (LRESULT)tape.hB_EDIT;
		}
		}
	}
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_COMBO);
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LRESULT)tape.hB_LIST;
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
	case WM_MEASUREITEM:
	{
		LPMEASUREITEMSTRUCT DrawMenuSize = (LPMEASUREITEMSTRUCT)lParam;
		if (DrawMenuSize->CtlType == ODT_COMBOBOX)
		{
			DrawMenuSize->itemHeight = 14;
		}
		break;
	}
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* DrawMenuStructure = (DRAWITEMSTRUCT*)lParam;

		if (DrawMenuStructure->CtlType == ODT_BUTTON)
		{
			if (DrawMenuStructure->CtlID == IDC_MAPPING_CANCEL)
				break;

			BOOL selected = (DrawMenuStructure->itemState & ODS_SELECTED) || (DrawMenuStructure->itemState & ODS_HOTLIGHT);
			if (selected)
			{
				switch (DrawMenuStructure->CtlID)
				{
				case IDC_MAPPING_OK:
				case IDC_MAPPING_RELOAD:
				{
					HDC hDC = GetDC(GetDlgItem(hWnd, IDC_MAPPING_OK));
					SelectObject(hDC, GetStockObject(DC_PEN));
					SetDCPenColor(hDC, tape.ink_yellow);

					RECT rect;
					GetClientRect(GetDlgItem(hWnd, IDC_MAPPING_OK), &rect);

					POINT Pt;
					MoveToEx(hDC, rect.right, rect.bottom, &Pt);
					LineTo(hDC, rect.left, rect.bottom);
					LineTo(hDC, rect.left, rect.top);
					LineTo(hDC, rect.right, rect.top);

					hDC = GetDC(GetDlgItem(hWnd, IDC_MAPPING_RELOAD));
					SelectObject(hDC, GetStockObject(DC_PEN));
					SetDCPenColor(hDC, tape.ink_yellow);

					GetClientRect(GetDlgItem(hWnd, IDC_MAPPING_RELOAD), &rect);

					MoveToEx(hDC, rect.left, rect.top, &Pt);
					LineTo(hDC, rect.right, rect.top);
					LineTo(hDC, rect.right, rect.bottom);
					LineTo(hDC, rect.left, rect.bottom);

					::ReleaseDC(hWnd, hDC);
					break;
				}
				default: { FrameRect(DrawMenuStructure->hDC, &DrawMenuStructure->rcItem, tape.hB_yellow); break; }
				}
			}

			RECT square = DrawMenuStructure->rcItem;
			square.left += 1;
			square.top += 1;
			square.right -= 1;
			square.bottom -= 1;
			RECT square2 = square;
			square2.top += 1;
			RECT square3 = square2;
			square3.left += 1;
			RECT square4 = square2;
			square4.top += 1;

			WCHAR wszBuffer[MAX_PATH];
			WCHAR* buf = wszBuffer;
			int nCharCount = 0;
			switch (DrawMenuStructure->CtlID)
			{
			case IDC_MAPPING_BTN_SRCE_1: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_SRCE_1), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_SRCE_2: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_SRCE_2), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_SRCE_3: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_SRCE_3), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_SRCE_4: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_SRCE_4), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_SRCE_5: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_SRCE_5), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_LED: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_LED), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_DEST_1: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_1), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_DEST_2: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_2), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_DEST_3: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_3), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_DEST_4: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_4), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_DEST_5: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_5), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_DEST_6: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_6), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_DEST_7: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_7), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_BTN_DEST_8: { nCharCount = GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_8), wszBuffer, MAX_PATH); break; }
			case IDC_MAPPING_IF_MOUSE:
			{
				switch (mappingData.Ifmouse)
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_purple); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_FORCE:
			{
				switch (mappingData.Force)
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_orange); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_SHORT:
			{
				switch (mappingData.Short)
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_red); break; }
				}
				break;
			}
			case IDC_MAPPING_DOUBLE:
			{
				switch (mappingData.Double)
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_red); break; }
				}
				break;
			}
			case IDC_MAPPING_LONG:
			{
				switch (mappingData.Long)
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_red); break; }
				}
				break;
			}
			case IDC_MAPPING_MACRO:
			{
				switch (mappingData.Macro)
				{
				case 1: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"I"); break; }
				case 2: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"N"); break; }
				}
				break;
			}
			case IDC_MAPPING_PAUSE:
			{
				switch (mappingData.Pause)
				{
				case 1: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"1"); break; }
				case 2: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"2"); break; }
				case 3: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"B"); break; }
				}
				break;
			}
			case IDC_MAPPING_TRANSITIVITY:
			{
				switch (mappingData.Transitivity)
				{
				case 1: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L">"); break; }
				case 2: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"C"); break; }
				case 3: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"L"); break; }
				case 4: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"R"); break; }
				case 5: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"O"); break; }
				}
				break;
			}
			case IDC_MAPPING_TOGGLE:
			{
				switch (mappingData.Toggle)
				{
				case 1: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"A"); break; }
				case 2: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"D"); break; }
				}
				break;
			}
			case IDC_MAPPING_SRCE_2_OR:
			{
				switch (mappingData.OrXorNot[0])
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_yellow); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_SRCE_3_OR:
			{
				switch (mappingData.OrXorNot[1])
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_yellow); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_SRCE_4_NOT:
			{
				switch (mappingData.OrXorNot[2])
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_grey); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_SRCE_5_NOT:
			{
				switch (mappingData.OrXorNot[3])
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_grey); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"▬", -1, &square4, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_TARGET_1:
			case IDC_MAPPING_TARGET_2:
			case IDC_MAPPING_TARGET_3:
			case IDC_MAPPING_TARGET_4:
			case IDC_MAPPING_TARGET_5:
			{
				switch (mappingData.Target[DrawMenuStructure->CtlID - IDC_MAPPING_TARGET_1])
				{
				case 1: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"S"); break; }
				case 2: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"K"); break; }
				case 3: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"D"); break; }
				}
				break;
			}
			case IDC_MAPPING_SRCE_1_DISABLE:
			case IDC_MAPPING_SRCE_2_DISABLE:
			case IDC_MAPPING_SRCE_3_DISABLE:
			case IDC_MAPPING_SRCE_4_DISABLE:
			case IDC_MAPPING_SRCE_5_DISABLE:
			{
				switch (mappingData.srceDisable[DrawMenuStructure->CtlID - IDC_MAPPING_SRCE_1_DISABLE])
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_green); DrawText(DrawMenuStructure->hDC, L"❌", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"❌", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_ONRELEASE_1:
			case IDC_MAPPING_ONRELEASE_2:
			case IDC_MAPPING_ONRELEASE_3:
			case IDC_MAPPING_ONRELEASE_4:
			case IDC_MAPPING_ONRELEASE_5:
			case IDC_MAPPING_ONRELEASE_6:
			case IDC_MAPPING_ONRELEASE_7:
			case IDC_MAPPING_ONRELEASE_8:
			{
				SetTextColor(DrawMenuStructure->hDC, tape.ink_POSTIT);
				switch (mappingData.OnRelease[DrawMenuStructure->CtlID - IDC_MAPPING_ONRELEASE_1])
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_emerald); DrawText(DrawMenuStructure->hDC, L"◾", -1, &square3, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"◾", -1, &square3, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_ACTION_1:
			case IDC_MAPPING_ACTION_2:
			case IDC_MAPPING_ACTION_3:
			case IDC_MAPPING_ACTION_4:
			case IDC_MAPPING_ACTION_5:
			case IDC_MAPPING_ACTION_6:
			case IDC_MAPPING_ACTION_7:
			case IDC_MAPPING_ACTION_8:
			{
				switch (mappingData.ActionType[DrawMenuStructure->CtlID - IDC_MAPPING_ACTION_1])
				{
				case 1: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"M"); break; }
				case 2: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"S"); break; }
				case 3: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"A"); break; }
				case 4: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"E"); break; }
				case 5: { nCharCount = 1; buf += swprintf_s(buf, MAX_PATH, L"W"); break; }
				}
				break;
			}
			case IDC_MAPPING_SWITCH_1:
			case IDC_MAPPING_SWITCH_2:
			case IDC_MAPPING_SWITCH_3:
			case IDC_MAPPING_SWITCH_4:
			case IDC_MAPPING_SWITCH_5:
			case IDC_MAPPING_SWITCH_6:
			case IDC_MAPPING_SWITCH_7:
			case IDC_MAPPING_SWITCH_8:
			{
				switch (mappingData.Switch[DrawMenuStructure->CtlID - IDC_MAPPING_SWITCH_1])
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_emerald); DrawText(DrawMenuStructure->hDC, L"◾", -1, &square3, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"◾", -1, &square3, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_OVERCONTROL_1:
			case IDC_MAPPING_OVERCONTROL_2:
			case IDC_MAPPING_OVERCONTROL_3:
			case IDC_MAPPING_OVERCONTROL_4:
			case IDC_MAPPING_OVERCONTROL_5:
			case IDC_MAPPING_OVERCONTROL_6:
			case IDC_MAPPING_OVERCONTROL_7:
			case IDC_MAPPING_OVERCONTROL_8:
			{
			switch (mappingData.Overcontrol[DrawMenuStructure->CtlID - IDC_MAPPING_OVERCONTROL_1])
			{
			case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_emerald); DrawText(DrawMenuStructure->hDC, L"◾", -1, &square3, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
			case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"◾", -1, &square3, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
			}
			break;
			}
			case IDC_MAPPING_DEST_1_DISABLE:
			case IDC_MAPPING_DEST_2_DISABLE:
			case IDC_MAPPING_DEST_3_DISABLE:
			case IDC_MAPPING_DEST_4_DISABLE:
			case IDC_MAPPING_DEST_5_DISABLE:
			case IDC_MAPPING_DEST_6_DISABLE:
			case IDC_MAPPING_DEST_7_DISABLE:
			case IDC_MAPPING_DEST_8_DISABLE:
			{
				switch (mappingData.destDisable[DrawMenuStructure->CtlID - IDC_MAPPING_DEST_1_DISABLE])
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_green); DrawText(DrawMenuStructure->hDC, L"❌", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"❌", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			case IDC_MAPPING_MOUSE_01:
			case IDC_MAPPING_MOUSE_02:
			case IDC_MAPPING_MOUSE_03:
			case IDC_MAPPING_MOUSE_04:
			case IDC_MAPPING_MOUSE_05:
			{
				if (mappingData.Mouse[0] == DrawMenuStructure->CtlID - IDC_MAPPING_MOUSE_01 + 1)
					switch (mappingData.Mouse[3])
					{
					case 0: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_green); DrawText(DrawMenuStructure->hDC, L"⬧", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
					case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"⬧", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
					}
				break;
			}
			case IDC_MAPPING_MOUSE_11:
			case IDC_MAPPING_MOUSE_12:
			case IDC_MAPPING_MOUSE_13:
			case IDC_MAPPING_MOUSE_14:
			case IDC_MAPPING_MOUSE_15:
			{
				if (mappingData.Mouse[1] == DrawMenuStructure->CtlID - IDC_MAPPING_MOUSE_11 + 1)
					switch (mappingData.Mouse[4])
					{
					case 0: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_green); DrawText(DrawMenuStructure->hDC, L"⬧", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
					case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"⬧", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
					}
				break;
			}
			case IDC_MAPPING_MOUSE_21:
			case IDC_MAPPING_MOUSE_22:
			case IDC_MAPPING_MOUSE_23:
			case IDC_MAPPING_MOUSE_24:
			case IDC_MAPPING_MOUSE_25:
			{
				if (mappingData.Mouse[2] == DrawMenuStructure->CtlID - IDC_MAPPING_MOUSE_21 + 1)
					switch (mappingData.Mouse[5])
					{
					case 0: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_green); DrawText(DrawMenuStructure->hDC, L"⬧", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
					case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"⬧", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
					}
				break;
			}
			case IDC_MAPPING_MOUSE_GRID:
			{
				switch (mappingData.Mouse[6])
				{
				case 1: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_purple); DrawText(DrawMenuStructure->hDC, L"⬧", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				case 2: { FillRect(DrawMenuStructure->hDC, &square, tape.hB_blue); DrawText(DrawMenuStructure->hDC, L"⬧", -1, &square2, DT_CENTER | DT_VCENTER | DT_SINGLELINE); break; }
				}
				break;
			}
			default: { nCharCount = GetWindowText(GetDlgItem(hWnd, DrawMenuStructure->CtlID), wszBuffer, MAX_PATH); break; }
			}

			if (nCharCount > 0 && !m_drawLock && !selected)
			{
				DrawMenuStructure->rcItem.top -= 1;
				switch (DrawMenuStructure->CtlID)
				{
				case IDC_MAPPING_OK: SetTextColor(DrawMenuStructure->hDC, tape.ink_BTN_MAPPING_OK); break;
				case IDC_MAPPING_CLEAR: SetTextColor(DrawMenuStructure->hDC, tape.ink_BTN_MAPPING_CLEAR); break;
				case IDC_MAPPING_HELP: SetTextColor(DrawMenuStructure->hDC, tape.ink_BTN_MAPPING_HELP); break;
				default: SetTextColor(DrawMenuStructure->hDC, tape.ink_BTN_MAPPING); break;
				}
				
				int nCharacters;
				for (nCharacters = 0;
					nCharacters < nCharCount; nCharacters++)
					if (wszBuffer[nCharacters] == L'\t' ||
						wszBuffer[nCharacters] == L'\b')
						break;

				SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
				switch (DrawMenuStructure->CtlID)
				{
				case IDC_MAPPING_BTN_SRCE_1:
				case IDC_MAPPING_BTN_SRCE_2:
				case IDC_MAPPING_BTN_SRCE_3:
				case IDC_MAPPING_BTN_SRCE_4:
				case IDC_MAPPING_BTN_SRCE_5:
				case IDC_MAPPING_BTN_LED:
				case IDC_MAPPING_BTN_DEST_1:
				case IDC_MAPPING_BTN_DEST_2:
				case IDC_MAPPING_BTN_DEST_3:
				case IDC_MAPPING_BTN_DEST_4:
				case IDC_MAPPING_BTN_DEST_5:
				case IDC_MAPPING_BTN_DEST_6:
				case IDC_MAPPING_BTN_DEST_7:
				case IDC_MAPPING_BTN_DEST_8:
				{
					DrawMenuStructure->rcItem.left -= 7;
					SelectObject(DrawMenuStructure->hDC, tape.hCombo2);
					break;
				}
				case IDC_MAPPING_OK:
				{
					DrawMenuStructure->rcItem.right += 20;
					SelectObject(DrawMenuStructure->hDC, tape.hCheck3);
					break;
				}
				default:
				{
					SelectObject(DrawMenuStructure->hDC, tape.hCheck3);
					break;
				}
				}
				DrawTextW(DrawMenuStructure->hDC, wszBuffer, nCharacters, &(DrawMenuStructure->rcItem), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		else if (DrawMenuStructure->CtlType == ODT_COMBOBOX)
		{
			BOOL selected = DrawMenuStructure->itemState & ODS_SELECTED;

			if (DrawMenuStructure->itemID == -1)
				break;

			if (DrawMenuStructure->itemState & ODS_SELECTED)
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU_HIGHLIGHT);
			else
				FillRect(DrawMenuStructure->hDC, &(DrawMenuStructure->rcItem), tape.hB_MENU);

			SelectObject(DrawMenuStructure->hDC, tape.hCombo);
			WCHAR wszBuffer[MAX_PATH];
			ComboBox_GetLBText(DrawMenuStructure->hwndItem, DrawMenuStructure->itemID, wszBuffer);
			int nCharCount = ComboBox_GetLBTextLen(DrawMenuStructure->hwndItem, DrawMenuStructure->itemID);
			if (nCharCount > 0)
			{
				COLORREF crCurrText = 0;
				crCurrText = (selected) ? tape.ink_MENU_HIGHLIGHT : tape.ink_MENU;
				SetTextColor(DrawMenuStructure->hDC, crCurrText);

				int nCharacters;
				for (nCharacters = 0;
					nCharacters < nCharCount; nCharacters++)
					if (wszBuffer[nCharacters] == L'\t' ||
						wszBuffer[nCharacters] == L'\b')
						break;

				SetBkMode(DrawMenuStructure->hDC, TRANSPARENT);
				DrawMenuStructure->rcItem.left += 2;
				DrawTextW(DrawMenuStructure->hDC, wszBuffer, nCharacters, &(DrawMenuStructure->rcItem), DT_VCENTER | DT_SINGLELINE);
			}
		}
		break;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE)
		{
			if (!firsttime)
			{
				GetCursorPos(&p);
				ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_PICTURE), SW_SHOW);
				ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_PICTURE2), SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_HELP), SW_SHOW);
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_RESETCONTENT, 0, 0);
				for (int i = 0; i < SrceButtonID::Button_Count; i++)
				{
					const WCHAR* str = SourceButton::String((SrceButtonID)i);
					if (mappingData.Target[0] == 0)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[1] == 0)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[2] == 0)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[3] == 0)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[4] == 0)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_ADDSTRING, 0, LPARAM(str));
				}
				for (int i = SrceButtonID::Sisaxis_None; i < SrceButtonID::Sisaxis_Count; i++)
				{
					const WCHAR* str = SourceButton::String((SrceButtonID)i);
					if (mappingData.Target[0] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[1] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[2] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[3] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[4] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_ADDSTRING, 0, LPARAM(str));
				}
				for (int i = SrceButtonID::Keyboard_None; i < SrceButtonID::Keyboard_Count; i++)
				{
					const WCHAR* str = SourceButton::String((SrceButtonID)i);
					if (mappingData.Target[0] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[1] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[2] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[3] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[4] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_ADDSTRING, 0, LPARAM(str));
				}
				for (int i = 0; i < DestButtonID::Destination_Count; i++)
				{
					WCHAR* str = DestinationButton::String((DestButtonID)i);
					if (mappingData.Target[0] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[1] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[2] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[3] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.Target[4] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_ADDSTRING, 0, LPARAM(str));
					if (!mappingData.ActionType[0])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					if (!mappingData.ActionType[1])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					if (!mappingData.ActionType[2])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					if (!mappingData.ActionType[3])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					if (!mappingData.ActionType[4])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					if (!mappingData.ActionType[5])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					if (!mappingData.ActionType[6])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					if (!mappingData.ActionType[7])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
				}
				for (int i = 0; i < Mapping::MouseAction_Count; i++)
				{
					const WCHAR* str = Mapping::MouseString((MouseActionID)i);
					if (mappingData.ActionType[0] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[1] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[2] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[3] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[4] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[5] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[6] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[7] == 1)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
				}
				for (int i = 0; i < Mapping::SpecialAction_Count; i++)
				{
					const WCHAR* str = Mapping::SpecialString((SpecialActionID)i);
					if (mappingData.ActionType[0] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[1] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[2] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[3] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[4] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[5] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[6] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[7] == 2)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
				}
				for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
				{
					WCHAR* str = DestinationButton::StringAxis((DestAxisMoveID)i);
					if (mappingData.ActionType[0] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[1] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[2] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[3] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[4] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[5] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[6] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[7] == 3)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
				}
				for (int i = 0; i < DestAfterEffectID::AfterEffect_Count; i++)
				{
					WCHAR* str = DestinationButton::StringEffect((DestAfterEffectID)i);
					if (mappingData.ActionType[0] == 4)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[1] == 4)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[2] == 4)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[3] == 4)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[4] == 4)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[5] == 4)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[6] == 4)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[7] == 4)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
				}
				for (int i = 0; i < Mapping::ModulesAction_Count; i++)
				{
					const WCHAR* str = Mapping::ModulesString((ModulesActionID)i);
					if (mappingData.ActionType[0] == 5)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[1] == 5)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[2] == 5)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[3] == 5)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[4] == 5)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[5] == 5)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[6] == 5)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					if (mappingData.ActionType[7] == 5)
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
				}
				SendMessage(hWnd, WM_GRID, 0, 0);
			}

			bool no[8];
			bool nl[8];
			for (int i = 0; i < 8; i++)
				{
					nl[i] = mappingData.NlRelease[i];
					no[i] = nl[i] || mappingData.NoRelease[i];
				}
			if (no[0]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NORELEASE_1), SW_SHOW); if (nl[0]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NLRELEASE_1), SW_SHOW);
			if (no[1]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NORELEASE_2), SW_SHOW); if (nl[1]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NLRELEASE_2), SW_SHOW);
			if (no[2]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NORELEASE_3), SW_SHOW); if (nl[2]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NLRELEASE_3), SW_SHOW);
			if (no[3]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NORELEASE_4), SW_SHOW); if (nl[3]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NLRELEASE_4), SW_SHOW);
			if (no[4]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NORELEASE_5), SW_SHOW); if (nl[4]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NLRELEASE_5), SW_SHOW);
			if (no[5]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NORELEASE_6), SW_SHOW); if (nl[5]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NLRELEASE_6), SW_SHOW);
			if (no[6]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NORELEASE_7), SW_SHOW); if (nl[6]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NLRELEASE_7), SW_SHOW);
			if (no[7]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NORELEASE_8), SW_SHOW); if (nl[7]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_NLRELEASE_8), SW_SHOW);

			if (mappingData.Overcontrol[0]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_OVERCONTROL_1), SW_SHOW);
			if (mappingData.Overcontrol[1]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_OVERCONTROL_2), SW_SHOW);
			if (mappingData.Overcontrol[2]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_OVERCONTROL_3), SW_SHOW);
			if (mappingData.Overcontrol[3]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_OVERCONTROL_4), SW_SHOW);
			if (mappingData.Overcontrol[4]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_OVERCONTROL_5), SW_SHOW);
			if (mappingData.Overcontrol[5]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_OVERCONTROL_6), SW_SHOW);
			if (mappingData.Overcontrol[6]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_OVERCONTROL_7), SW_SHOW);
			if (mappingData.Overcontrol[7]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_OVERCONTROL_8), SW_SHOW);

			if (mappingData.Switch[0]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_SWITCH_1), SW_SHOW);
			if (mappingData.Switch[1]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_SWITCH_2), SW_SHOW);
			if (mappingData.Switch[2]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_SWITCH_3), SW_SHOW);
			if (mappingData.Switch[3]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_SWITCH_4), SW_SHOW);
			if (mappingData.Switch[4]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_SWITCH_5), SW_SHOW);
			if (mappingData.Switch[5]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_SWITCH_6), SW_SHOW);
			if (mappingData.Switch[6]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_SWITCH_7), SW_SHOW);
			if (mappingData.Switch[7]) ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_SWITCH_8), SW_SHOW);
			
			SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_SETCURSEL, (mappingData.srceID[0] - ((mappingData.Target[0] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[0] == 1) ? SourceButton::Sisaxis_None : 0))), 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_SETCURSEL, (mappingData.srceID[1] - ((mappingData.Target[1] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[1] == 1) ? SourceButton::Sisaxis_None : 0))), 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_SETCURSEL, (mappingData.srceID[2] - ((mappingData.Target[2] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[2] == 1) ? SourceButton::Sisaxis_None : 0))), 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_SETCURSEL, (mappingData.srceID[3] - ((mappingData.Target[3] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[3] == 1) ? SourceButton::Sisaxis_None : 0))), 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_SETCURSEL, (mappingData.srceID[4] - ((mappingData.Target[4] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[4] == 1) ? SourceButton::Sisaxis_None : 0))), 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_SETCURSEL, mappingData.destID[0], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_SETCURSEL, mappingData.destID[1], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_SETCURSEL, mappingData.destID[2], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_SETCURSEL, mappingData.destID[3], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_SETCURSEL, mappingData.destID[4], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_SETCURSEL, mappingData.destID[5], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_SETCURSEL, mappingData.destID[6], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_SETCURSEL, mappingData.destID[7], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_LED, CB_SETCURSEL, mappingData.Led, 0);
			CheckDlgButton(hWnd, IDC_MAPPING_NORELEASE_1, mappingData.NoRelease[0]);
			CheckDlgButton(hWnd, IDC_MAPPING_NORELEASE_2, mappingData.NoRelease[1]);
			CheckDlgButton(hWnd, IDC_MAPPING_NORELEASE_3, mappingData.NoRelease[2]);
			CheckDlgButton(hWnd, IDC_MAPPING_NORELEASE_4, mappingData.NoRelease[3]);
			CheckDlgButton(hWnd, IDC_MAPPING_NORELEASE_5, mappingData.NoRelease[4]);
			CheckDlgButton(hWnd, IDC_MAPPING_NORELEASE_6, mappingData.NoRelease[5]);
			CheckDlgButton(hWnd, IDC_MAPPING_NORELEASE_7, mappingData.NoRelease[6]);
			CheckDlgButton(hWnd, IDC_MAPPING_NORELEASE_8, mappingData.NoRelease[7]);
			CheckDlgButton(hWnd, IDC_MAPPING_NLRELEASE_1, mappingData.NlRelease[0]);
			CheckDlgButton(hWnd, IDC_MAPPING_NLRELEASE_2, mappingData.NlRelease[1]);
			CheckDlgButton(hWnd, IDC_MAPPING_NLRELEASE_3, mappingData.NlRelease[2]);
			CheckDlgButton(hWnd, IDC_MAPPING_NLRELEASE_4, mappingData.NlRelease[3]);
			CheckDlgButton(hWnd, IDC_MAPPING_NLRELEASE_5, mappingData.NlRelease[4]);
			CheckDlgButton(hWnd, IDC_MAPPING_NLRELEASE_6, mappingData.NlRelease[5]);
			CheckDlgButton(hWnd, IDC_MAPPING_NLRELEASE_7, mappingData.NlRelease[6]);
			CheckDlgButton(hWnd, IDC_MAPPING_NLRELEASE_8, mappingData.NlRelease[7]);

			canprint = false;
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_1_START), WCHARI(20, L"%d", mappingData.Start[0]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_2_START), WCHARI(20, L"%d", mappingData.Start[1]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_3_START), WCHARI(20, L"%d", mappingData.Start[2]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_4_START), WCHARI(20, L"%d", mappingData.Start[3]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_5_START), WCHARI(20, L"%d", mappingData.Start[4]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_6_START), WCHARI(20, L"%d", mappingData.Start[5]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_7_START), WCHARI(20, L"%d", mappingData.Start[6]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_8_START), WCHARI(20, L"%d", mappingData.Start[7]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_1_STOP), WCHARI(20, L"%d", mappingData.Stop[0]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_2_STOP), WCHARI(20, L"%d", mappingData.Stop[1]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_3_STOP), WCHARI(20, L"%d", mappingData.Stop[2]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_4_STOP), WCHARI(20, L"%d", mappingData.Stop[3]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_5_STOP), WCHARI(20, L"%d", mappingData.Stop[4]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_6_STOP), WCHARI(20, L"%d", mappingData.Stop[5]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_7_STOP), WCHARI(20, L"%d", mappingData.Stop[6]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_DEST_8_STOP), WCHARI(20, L"%d", mappingData.Stop[7]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_X), WCHARI(20, L"%d", mappingData.Grid[0]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y), WCHARI(20, L"%d", mappingData.Grid[1]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_W), WCHARI(20, L"%d", mappingData.Grid[2]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_H), WCHARI(20, L"%d", mappingData.Grid[3]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW), WCHARI(20, L"%d", mappingData.Grid[4]));
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH), WCHARI(20, L"%d", mappingData.Grid[5]));
			canprint = true;
			
			firsttime = true;
		}
		break;
	}
	case WM_GRID:
	{
		if (
			(mappingData.Mouse[0] == 5 && !mappingData.Mouse[3]) ||
			(mappingData.Mouse[1] == 5 && !mappingData.Mouse[4]) ||
			(mappingData.Mouse[2] == 5 && !mappingData.Mouse[5])
			)
		{
			Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_X));
			Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y));
			Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_W));
			Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_H));
			Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW));
			Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH));
		}
		else
		{
			Hide(GetDlgItem(hWnd, IDC_MAPPING_GRID_X));
			Hide(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y));
			Hide(GetDlgItem(hWnd, IDC_MAPPING_GRID_W));
			Hide(GetDlgItem(hWnd, IDC_MAPPING_GRID_H));
			Hide(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW));
			Hide(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH));

			for (int i = 0; i < 8; i++)
			{
				if (mappingData.ActionType[i] == 1)
				{
					if (mappingData.destID[i] == mappingData.MOVE_TO_XY || mappingData.destID[i] == mappingData.SAVE_AND_MOVE_TO_XY)
					{
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_X));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y));
					}
					if (mappingData.destID[i] == mappingData.MOVE_TO_WH || mappingData.destID[i] == mappingData.SAVE_AND_MOVE_TO_WH)
					{
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_W));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_H));
					}
					if (mappingData.destID[i] == mappingData.MOVE_TO_NN || mappingData.destID[i] == mappingData.SAVE_AND_MOVE_TO_NN)
					{
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH));
					}
					if (mappingData.destID[i] == mappingData.MAGNIFY)
					{
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_X));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_W));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_H));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH));
					}
				}
				else if (mappingData.ActionType[i] == 2)
					if (mappingData.destID[i] == mappingData.SCREENSHOT)
					{
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_X));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_W));
						Show(GetDlgItem(hWnd, IDC_MAPPING_GRID_H));
					}
			}
		}
		if (mappingData.ActionType[0])
		{
			mappingData.destDisable[0] = false;
			Modified[Mofified_vjDisable1] = true;
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_1_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_1_DISABLE));
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_1_DISABLE), false);
		}
		else
		{
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_1_DISABLE), true);
			CheckDlgButton(hWnd, IDC_MAPPING_DEST_1_DISABLE, mappingData.destDisable[0]);
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_1_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_1_DISABLE));
		}
		if (mappingData.ActionType[1])
		{
			mappingData.destDisable[1] = false;
			Modified[Mofified_vjDisable2] = true;
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_2_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_2_DISABLE));
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_2_DISABLE), false);
		}
		else
		{
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_2_DISABLE), true);
			CheckDlgButton(hWnd, IDC_MAPPING_DEST_2_DISABLE, mappingData.destDisable[1]);
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_2_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_2_DISABLE));
		}
		if (mappingData.ActionType[2])
		{
			mappingData.destDisable[2] = false;
			Modified[Mofified_vjDisable3] = true;
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_3_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_3_DISABLE));
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_3_DISABLE), false);
		}
		else
		{
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_3_DISABLE), true);
			CheckDlgButton(hWnd, IDC_MAPPING_DEST_3_DISABLE, mappingData.destDisable[2]);
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_3_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_3_DISABLE));
		}
		if (mappingData.ActionType[3])
		{
			mappingData.destDisable[3] = false;
			Modified[Mofified_vjDisable4] = true;
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_4_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_4_DISABLE));
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_4_DISABLE), false);
		}
		else
		{
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_4_DISABLE), true);
			CheckDlgButton(hWnd, IDC_MAPPING_DEST_4_DISABLE, mappingData.destDisable[3]);
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_4_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_4_DISABLE));
		}
		if (mappingData.ActionType[4])
		{
			mappingData.destDisable[4] = false;
			Modified[Mofified_vjDisable5] = true;
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_5_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_5_DISABLE));
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_5_DISABLE), false);
		}
		else
		{
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_5_DISABLE), true);
			CheckDlgButton(hWnd, IDC_MAPPING_DEST_5_DISABLE, mappingData.destDisable[4]);
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_5_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_5_DISABLE));
		}
		if (mappingData.ActionType[5])
		{
			mappingData.destDisable[5] = false;
			Modified[Mofified_vjDisable6] = true;
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_6_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_6_DISABLE));
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_6_DISABLE), false);
		}
		else
		{
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_6_DISABLE), true);
			CheckDlgButton(hWnd, IDC_MAPPING_DEST_6_DISABLE, mappingData.destDisable[5]);
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_6_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_6_DISABLE));
		}
		if (mappingData.ActionType[6])
		{
			mappingData.destDisable[6] = false;
			Modified[Mofified_vjDisable7] = true;
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_7_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_7_DISABLE));
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_7_DISABLE), false);
		}
		else
		{
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_7_DISABLE), true);
			CheckDlgButton(hWnd, IDC_MAPPING_DEST_7_DISABLE, mappingData.destDisable[6]);
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_7_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_7_DISABLE));
		}
		if (mappingData.ActionType[7])
		{
			mappingData.destDisable[7] = false;
			Modified[Mofified_vjDisable8] = true;
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_8_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_8_DISABLE));
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_8_DISABLE), false);
		}
		else
		{
			EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_DEST_8_DISABLE), true);
			CheckDlgButton(hWnd, IDC_MAPPING_DEST_8_DISABLE, mappingData.destDisable[7]);
			Hide(GetDlgItem(hWnd, IDC_MAPPING_DEST_8_DISABLE));
			Show(GetDlgItem(hWnd, IDC_MAPPING_DEST_8_DISABLE));
		}
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&MappingDataDlg::_InitDialog, this, hWnd).detach();
		return FALSE;
	}
	case WM_TIMER:
	{
		if (IsIconic(hWnd) || !IsWindowVisible(m_hDlg))
			break;

		switch (wParam)
		{
		case 1:
		{
			now = std::chrono::system_clock::now();
			if (now - start < std::chrono::milliseconds(3000))
			{
				danger = true;
				GetCursorPos(&tape.mousepoint);
				SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_X), WCHARI(6, L"%d", tape.mousepoint.x));
				SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_Y), WCHARI(6, L"%d", tape.mousepoint.y));
			}
			else if (danger)
			{
				danger = false;
				capturehasbeendone = true;
				KillTimer(m_hDlg, 1);
				if (IsWindowVisible(m_hDlg))
				{
					ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_X), SW_HIDE);
					ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_Y), SW_HIDE);
					ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_X), SW_SHOW);
					ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_Y), SW_SHOW);
				}
			}
			break;
		}
		case 2:
		{
			NMBCHOTITEM hot = { 0 };
			hot.hdr.hwndFrom = hWnd;
#pragma warning(suppress:26454)
			hot.hdr.code = BCN_HOTITEMCHANGE;

			RECT win;
			GetCursorPos(&tape.mousepoint);

			int j = 0;
			for (int i : mouseoverCB)
			{
				hot.hdr.idFrom = i;
				GetWindowRect(GetDlgItem(hWnd, i), &win);
				bool inControl = PtInRect(&win, tape.mousepoint);
				if (inControl != (state[j] & 0x1))
				{
					if (inControl)
						hot.dwFlags = HICF_ENTERING | HICF_MOUSE;
					else
						hot.dwFlags = HICF_LEAVING | HICF_MOUSE;
					SendMessage(hWnd, WM_NOTIFY, 0, LPARAM(&hot));
				}
				j++;

			}
			break;
		}
		}
		break;
	}
	case WM_RBUTTONDOWN:
	{
		PostMessage(tape.Ds2hWnd, WM_TRANSPARENCY, 0, 1);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		m_moveLock = false;
		SetCapture(m_hDlg);
		GetCursorPos(&tape.mousepoint);
		RECT win;
		GetWindowRect(hWnd, &win);
		m_x = win.left - tape.mousepoint.x;
		m_y = win.top - tape.mousepoint.y;
		m_z = win.right - tape.mousepoint.x;
		m_t = win.bottom - tape.mousepoint.y;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (m_moveLock)
			return TRUE;

		if (movable)
		{
			RECT win;
			GetWindowRect(tape.Ds2hWnd, &win);
			if ((GetKeyState(VK_LBUTTON) & 0x800) == 0)
			{
				if (docked == 2)
					::MoveWindow(m_hDlg, win.left + 9, win.top + 31, 474, 287, FALSE);
				ReleaseCapture();
				break;
			}

			GetCursorPos(&p);
			if (abs(win.right - m_x - 7 - p.x) < 40)															//docked right
			{
				docked = 1;
				docked_last = 1;
				::MoveWindow(m_hDlg, win.right - 7, m_y + p.y, 474, 287, FALSE);
			}
			else if ((abs(win.left - m_x + 9 - p.x) < 40) && (p.y > win.top + 20) && (p.y < win.bottom - 20))	//docked center
			{
				docked = 2;
				docked_last = 2;
				::MoveWindow(m_hDlg, win.left + 9, m_y + p.y, 474, 287, FALSE);
			}
			else if (abs(win.left - m_z + 7 - p.x) < 40)														//docked left
			{
				docked = 3;
				docked_last = 3;
				::MoveWindow(m_hDlg, win.left + 7 - 474, m_y + p.y, 474, 287, FALSE);
			}
			else																								//no docked
			{
				docked = 0;
				docked_last = 0;
				::MoveWindow(m_hDlg, m_x + p.x, m_y + p.y, 474, 287, FALSE);
			}
		}
		else
			SetFocus(tape.Ds2hWnd);
		break;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case BCN_HOTITEMCHANGE:
		{
			switch (((NMBCHOTITEM*)lParam)->dwFlags)
				// HICF_OTHER			= 0x00000000
				// HICF_MOUSE			= 0x00000001	Triggered by mouse
				// HICF_ARROWKEYS		= 0x00000002	Triggered by arrow keys
				// HICF_ACCELERATOR		= 0x00000004	Triggered by accelerator
				// HICF_DUPACCEL		= 0x00000008	This accelerator is not unique
				// HICF_ENTERING		= 0x00000010	idOld is invalid
				// HICF_LEAVING			= 0x00000020	idNew is invalid
				// HICF_RESELECT		= 0x00000040	hot item reselected
				// HICF_LMOUSE			= 0x00000080	left mouse button selected
				// HICF_TOGGLEDROPDOWN	= 0x00000100	Toggle button's dropdown state
			{
			case (HICF_ENTERING | HICF_MOUSE):
			{
				switch (((LPNMHDR)lParam)->idFrom)
				{
				case IDC_MAPPING_ONRELEASE_1:		{ state[0] = state[0] | 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_2:		{ state[1] = state[1] | 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_3:		{ state[2] = state[2] | 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_4:		{ state[3] = state[3] | 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_5:		{ state[4] = state[4] | 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_6:		{ state[5] = state[5] | 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_7:		{ state[6] = state[6] | 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_8:		{ state[7] = state[7] | 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_1:		{ state[0] = state[0] | 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_2:		{ state[1] = state[1] | 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_3:		{ state[2] = state[2] | 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_4:		{ state[3] = state[3] | 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_5:		{ state[4] = state[4] | 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_6:		{ state[5] = state[5] | 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_7:		{ state[6] = state[6] | 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_8:		{ state[7] = state[7] | 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_1:		{ state[0] = state[0] | 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_2:		{ state[1] = state[1] | 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_3:		{ state[2] = state[2] | 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_4:		{ state[3] = state[3] | 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_5:		{ state[4] = state[4] | 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_6:		{ state[5] = state[5] | 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_7:		{ state[6] = state[6] | 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_8:		{ state[7] = state[7] | 0x4; ShowNoRelease(); break; }
				default:
					return FALSE;
				}
				break;
			}
			case (HICF_LEAVING | HICF_MOUSE):
			{
				switch (((LPNMHDR)lParam)->idFrom)
				{
				case IDC_MAPPING_ONRELEASE_1:		{ state[0] = state[0] ^ 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_2:		{ state[1] = state[1] ^ 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_3:		{ state[2] = state[2] ^ 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_4:		{ state[3] = state[3] ^ 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_5:		{ state[4] = state[4] ^ 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_6:		{ state[5] = state[5] ^ 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_7:		{ state[6] = state[6] ^ 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_ONRELEASE_8:		{ state[7] = state[7] ^ 0x1; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_1:		{ state[0] = state[0] ^ 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_2:		{ state[1] = state[1] ^ 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_3:		{ state[2] = state[2] ^ 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_4:		{ state[3] = state[3] ^ 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_5:		{ state[4] = state[4] ^ 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_6:		{ state[5] = state[5] ^ 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_7:		{ state[6] = state[6] ^ 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NORELEASE_8:		{ state[7] = state[7] ^ 0x2; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_1:		{ state[0] = state[0] ^ 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_2:		{ state[1] = state[1] ^ 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_3:		{ state[2] = state[2] ^ 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_4:		{ state[3] = state[3] ^ 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_5:		{ state[4] = state[4] ^ 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_6:		{ state[5] = state[5] ^ 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_7:		{ state[6] = state[6] ^ 0x4; ShowNoRelease(); break; }
				case IDC_MAPPING_NLRELEASE_8:		{ state[7] = state[7] ^ 0x4; ShowNoRelease(); break; }
				default:
					return FALSE;
				}
				break;
			}
			default:
				return FALSE;
			}
			break;
		}
		case NM_CUSTOMDRAW:
		{
			LPNMCUSTOMDRAW DrawMenuCustom = (LPNMCUSTOMDRAW)lParam;
			DrawMenuCustom->rc.right = DrawMenuCustom->rc.left + 12;
			DrawMenuCustom->rc.bottom = DrawMenuCustom->rc.top + 12;

			RECT rect;
			rect.left = DrawMenuCustom->rc.left;
			rect.top = DrawMenuCustom->rc.top;
			rect.right = rect.left + 12;
			rect.bottom = rect.top + 12;
			FrameRect(DrawMenuCustom->hdc, &rect, tape.hB_white);

			rect.left += 1;
			rect.top += 1;
			rect.right = rect.left + 10;
			rect.bottom = rect.top + 10;

			RECT rect2 = rect;
			rect2.top += 1;

			switch (((LPNMHDR)lParam)->idFrom)
			{
			case IDC_MAPPING_NORELEASE_1:
			case IDC_MAPPING_NORELEASE_2:
			case IDC_MAPPING_NORELEASE_3:
			case IDC_MAPPING_NORELEASE_4:
			case IDC_MAPPING_NORELEASE_5:
			case IDC_MAPPING_NORELEASE_6:
			case IDC_MAPPING_NORELEASE_7:
			case IDC_MAPPING_NORELEASE_8:
			case IDC_MAPPING_NLRELEASE_1:
			case IDC_MAPPING_NLRELEASE_2:
			case IDC_MAPPING_NLRELEASE_3:
			case IDC_MAPPING_NLRELEASE_4:
			case IDC_MAPPING_NLRELEASE_5:
			case IDC_MAPPING_NLRELEASE_6:
			case IDC_MAPPING_NLRELEASE_7:
			case IDC_MAPPING_NLRELEASE_8:
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
						FillRect(DrawMenuCustom->hdc, &rect, tape.hB_red);
						DrawText(DrawMenuCustom->hdc, L"◾", -1, &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					case BST_INDETERMINATE:
					{
						FillRect(DrawMenuCustom->hdc, &rect, tape.hB_blue);
						DrawText(DrawMenuCustom->hdc, L"◾", -1, &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
					}
					return CDRF_SKIPDEFAULT | CDRF_NOTIFYITEMDRAW;
				}
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

		case IDC_MAPPING_RELOAD:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (m_mode == 1 || m_mode == 2)
				{
					m_rightClickOk = true;
					PostMessage(m_hDlg, WM_COMMAND, MAKEWPARAM(IDC_MAPPING_OK, BN_CLICKED), 0);
				}
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_OK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (mappingData.srceID[0] == 0 && m_mode != 3)
				{
					KillTimer(m_hDlg, 1);
					RECT win;
					GetWindowRect(tape.Ds2hWnd, &win);
					MessageBoxPos(hWnd, I18N.MBOX_NoButtonSelected, I18N.MBOX_ErrTitle, MB_ICONERROR, win.left + 275, win.top + 30);
					return TRUE;
				}
				if (m_mode == 1)
				{
					mappingData.Enable = 1;
					if (m_rightClickOk)
					{
						m_rightClickOk = false;
						SendMessage(tape.Ds2hWnd, WM_ADDMAPPING, 1, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
						Mapping m;
						mDDlg.mappingData = m;
						Hide();
						firsttime = false;
						Show();
					}
					else
					{
						KillTimer(m_hDlg, 1);
						KillTimer(m_hDlg, 2);
						PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, 1, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
						m_mode = 0;
					}
				}
				else
				{
					if (m_rightClickOk)
					{
						m_rightClickOk = false;
						SendMessage(tape.Ds2hWnd, WM_ADDMAPPING, 2, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
						Show();
					}
					else
					{
						KillTimer(m_hDlg, 1);
						KillTimer(m_hDlg, 2);
						PostMessage(tape.Ds2hWnd, WM_ADDMAPPING, m_mode, MAKELPARAM((m_isClonedList) ? 2 : 1, m_Tab));
						m_mode = 0;
					}
				}
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_CANCEL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				KillTimer(m_hDlg, 2);
				KillTimer(m_hDlg, 1);
				m_mode = 0;
				Hide();
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_HELP:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_HELP), SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_PICTURE2), SW_SHOW);
				ShowWindow(GetDlgItem(hWnd, IDC_MAPPING_PICTURE), SW_HIDE);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_CLEAR:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				Mapping m;
				mDDlg.mappingData = m;
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.srceID[0] = (unsigned short)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0) + ((mappingData.Target[0] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[0] == 1) ? SourceButton::Sisaxis_None : 0));
				Modified[Mofified_dsID1] = true;
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_1));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_1));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.srceID[1] = (unsigned short)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0) + ((mappingData.Target[1] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[1] == 1) ? SourceButton::Sisaxis_None : 0));
				Modified[Mofified_dsID2] = true;
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_2));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_2));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_3:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.srceID[2] = (unsigned short)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0) + ((mappingData.Target[2] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[2] == 1) ? SourceButton::Sisaxis_None : 0));
				Modified[Mofified_dsID3] = true;
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_3));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_3));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_4:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.srceID[3] = (unsigned short)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0) + ((mappingData.Target[3] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[3] == 1) ? SourceButton::Sisaxis_None : 0));
				Modified[Mofified_dsID4] = true;
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_4));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_4));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_5:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.srceID[4] = (unsigned short)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0) + ((mappingData.Target[4] == 2) ? SourceButton::Keyboard_None : ((mappingData.Target[4] == 1) ? SourceButton::Sisaxis_None : 0));
				Modified[Mofified_dsID5] = true;
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_5));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_5));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_LED:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				Modified[Mofified_Led] = true;
				mappingData.Led = (int)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_LED));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_LED));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.destID[0] = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_vjID1] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_1));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_1));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.destID[1] = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_vjID2] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_2));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_2));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_3:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.destID[2] = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_vjID3] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_3));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_3));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_4:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.destID[3] = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_vjID4] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_4));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_4));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_5:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.destID[4] = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_vjID5] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			case CBN_DROPDOWN:
			{
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_5));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_5));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_6:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.destID[5] = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_vjID6] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_6));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_6));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_7:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.destID[6] = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_vjID7] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_7));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_7));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_8:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				mappingData.destID[7] = (byte)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				Modified[Mofified_vjID8] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			case CBN_DROPDOWN:
			{
				m_drawLock = true;
				m_moveLock = true;
				break;
			}
			case CBN_CLOSEUP:
			{
				m_drawLock = false;
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_8));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_8));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_TARGET_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Target[0] = (mappingData.Target[0] + 1) % 4;
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_RESETCONTENT, 0, 0);
				if (mappingData.Target[0] == 3)
				{
					mappingData.srceID[0] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.Target[0] == 2)
				{
					mappingData.srceID[0] = SrceButtonID::Keyboard_None;
					for (int i = SrceButtonID::Keyboard_None; i < SrceButtonID::Keyboard_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.Target[0])
				{
					mappingData.srceID[0] = SrceButtonID::Sisaxis_None;
					for (int i = SrceButtonID::Sisaxis_None; i < SrceButtonID::Sisaxis_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.srceID[0] = SrceButtonID::Button_None;
					for (int i = 0; i < SrceButtonID::Button_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_Target1] = true;
				Modified[Mofified_dsID1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_1));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_1));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_TARGET_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Target[1] = (mappingData.Target[1] + 1) % 4;
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_RESETCONTENT, 0, 0);
				if (mappingData.Target[1] == 3)
				{
					mappingData.srceID[1] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.Target[1] == 2)
				{
					mappingData.srceID[1] = SrceButtonID::Keyboard_None;
					for (int i = SrceButtonID::Keyboard_None; i < SrceButtonID::Keyboard_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.Target[1])
				{
					mappingData.srceID[1] = SrceButtonID::Sisaxis_None;
					for (int i = SrceButtonID::Sisaxis_None; i < SrceButtonID::Sisaxis_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.srceID[1] = SrceButtonID::Button_None;
					for (int i = 0; i < SrceButtonID::Button_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_Target2] = true;
				Modified[Mofified_dsID2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_2));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_2));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_TARGET_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Target[2] = (mappingData.Target[2] + 1) % 4;
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_RESETCONTENT, 0, 0);
				if (mappingData.Target[2] == 3)
				{
					mappingData.srceID[2] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.Target[2] == 2)
				{
					mappingData.srceID[2] = SrceButtonID::Keyboard_None;
					for (int i = SrceButtonID::Keyboard_None; i < SrceButtonID::Keyboard_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.Target[2])
				{
					mappingData.srceID[2] = SrceButtonID::Sisaxis_None;
					for (int i = SrceButtonID::Sisaxis_None; i < SrceButtonID::Sisaxis_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.srceID[2] = SrceButtonID::Button_None;
					for (int i = 0; i < SrceButtonID::Button_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_Target3] = true;
				Modified[Mofified_dsID3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_3));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_3));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_TARGET_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Target[3] = (mappingData.Target[3] + 1) % 4;
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_RESETCONTENT, 0, 0);
				if (mappingData.Target[3] == 3)
				{
					mappingData.srceID[3] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.Target[3] == 2)
				{
					mappingData.srceID[3] = SrceButtonID::Keyboard_None;
					for (int i = SrceButtonID::Keyboard_None; i < SrceButtonID::Keyboard_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.Target[3])
				{
					mappingData.srceID[3] = SrceButtonID::Sisaxis_None;
					for (int i = SrceButtonID::Sisaxis_None; i < SrceButtonID::Sisaxis_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.srceID[3] = SrceButtonID::Button_None;
					for (int i = 0; i < SrceButtonID::Button_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_Target4] = true;
				Modified[Mofified_dsID4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_4));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_4));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_TARGET_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Target[4] = (mappingData.Target[4] + 1) % 4;
				SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_RESETCONTENT, 0, 0);
				if (mappingData.Target[4] == 3)
				{
					mappingData.srceID[4] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.Target[4] == 2)
				{
					mappingData.srceID[4] = SrceButtonID::Keyboard_None;
					for (int i = SrceButtonID::Keyboard_None; i < SrceButtonID::Keyboard_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if(mappingData.Target[4])
				{
					mappingData.srceID[4] = SrceButtonID::Sisaxis_None;
					for (int i = SrceButtonID::Sisaxis_None; i < SrceButtonID::Sisaxis_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.srceID[4] = SrceButtonID::Button_None;
					for (int i = 0; i < SrceButtonID::Button_Count; i++)
					{
						const WCHAR* str = SourceButton::String((SrceButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_SRCE_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_Target5] = true;
				Modified[Mofified_dsID5] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_5));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_SRCE_5));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_1_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.srceDisable[0] = (mappingData.srceDisable[0] + 1) % 3;
				Modified[Mofified_dsDisable1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_2_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.srceDisable[1] = (mappingData.srceDisable[1] + 1) % 3;
				Modified[Mofified_dsDisable2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_3_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.srceDisable[2] = (mappingData.srceDisable[2] + 1) % 3;
				Modified[Mofified_dsDisable3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_4_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.srceDisable[3] = (mappingData.srceDisable[3] + 1) % 3;
				Modified[Mofified_dsDisable4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_5_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.srceDisable[4] = (mappingData.srceDisable[4] + 1) % 3;
				Modified[Mofified_dsDisable5] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_1_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (mappingData.ActionType[0])
					mappingData.destDisable[0] = 0;
				else
					mappingData.destDisable[0] = (mappingData.destDisable[0] + 1) % 3;
				Modified[Mofified_vjDisable1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_2_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (mappingData.ActionType[1])
					mappingData.destDisable[1] = 0;
				else
					mappingData.destDisable[1] = (mappingData.destDisable[1] + 1) % 3;
				Modified[Mofified_vjDisable2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_3_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (mappingData.ActionType[2])
					mappingData.destDisable[2] = 0;
				else
					mappingData.destDisable[2] = (mappingData.destDisable[2] + 1) % 3;
				Modified[Mofified_vjDisable3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_4_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (mappingData.ActionType[3])
					mappingData.destDisable[3] = 0;
				else
					mappingData.destDisable[3] = (mappingData.destDisable[3] + 1) % 3;
				Modified[Mofified_vjDisable4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_5_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (mappingData.ActionType[4])
					mappingData.destDisable[4] = 0;
				else
					mappingData.destDisable[4] = (mappingData.destDisable[4] + 1) % 3;
				Modified[Mofified_vjDisable5] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_6_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (mappingData.ActionType[5])
					mappingData.destDisable[5] = 0;
				else
					mappingData.destDisable[5] = (mappingData.destDisable[5] + 1) % 3;
				Modified[Mofified_vjDisable6] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_7_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (mappingData.ActionType[6])
					mappingData.destDisable[6] = 0;
				else
					mappingData.destDisable[6] = (mappingData.destDisable[6] + 1) % 3;
				Modified[Mofified_vjDisable7] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_8_DISABLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (mappingData.ActionType[7])
					mappingData.destDisable[7] = 0;
				else
					mappingData.destDisable[7] = (mappingData.destDisable[7] + 1) % 3;
				Modified[Mofified_vjDisable8] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_2_OR:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OrXorNot[0] = (mappingData.OrXorNot[0] + 1) % 3;
				Modified[Mofified_OrXorNot1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_3_OR:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OrXorNot[1] = (mappingData.OrXorNot[1] + 1) % 3;
				Modified[Mofified_OrXorNot2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_4_NOT:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OrXorNot[2] = (mappingData.OrXorNot[2] + 1) % 3;
				Modified[Mofified_OrXorNot3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SRCE_5_NOT:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OrXorNot[3] = (mappingData.OrXorNot[3] + 1) % 3;
				Modified[Mofified_OrXorNot4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_IF_MOUSE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Ifmouse = (mappingData.Ifmouse + 1) % 3;
				Modified[Mofified_Ifmouse] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_FORCE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Force = (mappingData.Force + 1) % 3;
				Modified[Mofified_Force] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SHORT:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Short = !mappingData.Short;
				Modified[Mofified_Short] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DOUBLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Double = !mappingData.Double;
				Modified[Mofified_Double] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_LONG:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Long = !mappingData.Long;
				Modified[Mofified_Long] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MACRO:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Macro = (mappingData.Macro + 1) % 3;
				Modified[Mofified_Macro] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_PAUSE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Pause = (mappingData.Pause + 1) % 4;
				Modified[Mofified_Pause] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_TRANSITIVITY:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Transitivity = (mappingData.Transitivity + 1) % 6;
				Modified[Mofified_Transitivity] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_TOGGLE:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Toggle = (mappingData.Toggle + 1) % 3;
				Modified[Mofified_Toggle] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ONRELEASE_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OnRelease[0] = (mappingData.OnRelease[0] + 1) % 3;
				Modified[Mofified_OnRelease1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ONRELEASE_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OnRelease[1] = (mappingData.OnRelease[1] + 1) % 3;
				Modified[Mofified_OnRelease2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ONRELEASE_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OnRelease[2] = (mappingData.OnRelease[2] + 1) % 3;
				Modified[Mofified_OnRelease3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ONRELEASE_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OnRelease[3] = (mappingData.OnRelease[3] + 1) % 3;
				Modified[Mofified_OnRelease4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ONRELEASE_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OnRelease[4] = (mappingData.OnRelease[4] + 1) % 3;
				Modified[Mofified_OnRelease5] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ONRELEASE_6:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OnRelease[5] = (mappingData.OnRelease[5] + 1) % 3;
				Modified[Mofified_OnRelease6] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ONRELEASE_7:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OnRelease[6] = (mappingData.OnRelease[6] + 1) % 3;
				Modified[Mofified_OnRelease7] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ONRELEASE_8:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.OnRelease[7] = (mappingData.OnRelease[7] + 1) % 3;
				Modified[Mofified_OnRelease8] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NORELEASE_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NoRelease[0] = (mappingData.NoRelease[0] + 1) % 3;
				Modified[Mofified_NoRelease1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NORELEASE_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NoRelease[1] = (mappingData.NoRelease[1] + 1) % 3;
				Modified[Mofified_NoRelease2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NORELEASE_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NoRelease[2] = (mappingData.NoRelease[2] + 1) % 3;
				Modified[Mofified_NoRelease3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NORELEASE_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NoRelease[3] = (mappingData.NoRelease[3] + 1) % 3;
				Modified[Mofified_NoRelease4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NORELEASE_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NoRelease[4] = (mappingData.NoRelease[4] + 1) % 3;
				Modified[Mofified_NoRelease5] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NORELEASE_6:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NoRelease[5] = (mappingData.NoRelease[5] + 1) % 3;
				Modified[Mofified_NoRelease6] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NORELEASE_7:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NoRelease[6] = (mappingData.NoRelease[6] + 1) % 3;
				Modified[Mofified_NoRelease7] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NORELEASE_8:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NoRelease[7] = (mappingData.NoRelease[7] + 1) % 3;
				Modified[Mofified_NoRelease8] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NLRELEASE_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NlRelease[0] = (mappingData.NlRelease[0] + 1) % 3;
				Modified[Mofified_NlRelease1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NLRELEASE_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NlRelease[1] = (mappingData.NlRelease[1] + 1) % 3;
				Modified[Mofified_NlRelease2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NLRELEASE_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NlRelease[2] = (mappingData.NlRelease[2] + 1) % 3;
				Modified[Mofified_NlRelease3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NLRELEASE_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NlRelease[3] = (mappingData.NlRelease[3] + 1) % 3;
				Modified[Mofified_NlRelease4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NLRELEASE_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NlRelease[4] = (mappingData.NlRelease[4] + 1) % 3;
				Modified[Mofified_NlRelease5] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NLRELEASE_6:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NlRelease[5] = (mappingData.NlRelease[5] + 1) % 3;
				Modified[Mofified_NlRelease6] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NLRELEASE_7:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NlRelease[6] = (mappingData.NlRelease[6] + 1) % 3;
				Modified[Mofified_NlRelease7] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_NLRELEASE_8:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.NlRelease[7] = (mappingData.NlRelease[7] + 1) % 3;
				Modified[Mofified_NlRelease8] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_1_START:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstart1[MAX_PATH];
				GetWindowText((HWND)lParam, bufstart1, MAX_PATH);
				mappingData.Start[0] = max(0, min(9999, _wtoi(bufstart1)));
				if (canprint)
					Modified[Mofified_Start1] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_2_START:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstart2[MAX_PATH];
				GetWindowText((HWND)lParam, bufstart2, MAX_PATH);
				mappingData.Start[1] = max(0, min(9999, _wtoi(bufstart2)));
				if (canprint)
					Modified[Mofified_Start2] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_3_START:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstart3[MAX_PATH];
				GetWindowText((HWND)lParam, bufstart3, MAX_PATH);
				mappingData.Start[2] = max(0, min(9999, _wtoi(bufstart3)));
				if (canprint)
					Modified[Mofified_Start3] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_4_START:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstart4[MAX_PATH];
				GetWindowText((HWND)lParam, bufstart4, MAX_PATH);
				mappingData.Start[3] = max(0, min(9999, _wtoi(bufstart4)));
				if (canprint)
					Modified[Mofified_Start4] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_5_START:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstart5[MAX_PATH];
				GetWindowText((HWND)lParam, bufstart5, MAX_PATH);
				mappingData.Start[4] = max(0, min(9999, _wtoi(bufstart5)));
				if (canprint)
					Modified[Mofified_Start5] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_6_START:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstart6[MAX_PATH];
				GetWindowText((HWND)lParam, bufstart6, MAX_PATH);
				mappingData.Start[5] = max(0, min(9999, _wtoi(bufstart6)));
				if (canprint)
					Modified[Mofified_Start6] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_7_START:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstart7[MAX_PATH];
				GetWindowText((HWND)lParam, bufstart7, MAX_PATH);
				mappingData.Start[6] = max(0, min(9999, _wtoi(bufstart7)));
				if (canprint)
					Modified[Mofified_Start7] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_8_START:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstart8[MAX_PATH];
				GetWindowText((HWND)lParam, bufstart8, MAX_PATH);
				mappingData.Start[7] = max(0, min(9999, _wtoi(bufstart8)));
				if (canprint)
					Modified[Mofified_Start8] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_1_STOP:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstop1[MAX_PATH];
				GetWindowText((HWND)lParam, bufstop1, MAX_PATH);
				mappingData.Stop[0] = max(0, min(9999, _wtoi(bufstop1)));
				if (canprint)
					Modified[Mofified_Stop1] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_2_STOP:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstop2[MAX_PATH];
				GetWindowText((HWND)lParam, bufstop2, MAX_PATH);
				mappingData.Stop[1] = max(0, min(9999, _wtoi(bufstop2)));
				if (canprint)
					Modified[Mofified_Stop2] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_3_STOP:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstop3[MAX_PATH];
				GetWindowText((HWND)lParam, bufstop3, MAX_PATH);
				mappingData.Stop[2] = max(0, min(9999, _wtoi(bufstop3)));
				if (canprint)
					Modified[Mofified_Stop3] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_4_STOP:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstop4[MAX_PATH];
				GetWindowText((HWND)lParam, bufstop4, MAX_PATH);
				mappingData.Stop[3] = max(0, min(9999, _wtoi(bufstop4)));
				if (canprint)
					Modified[Mofified_Stop4] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_5_STOP:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstop5[MAX_PATH];
				GetWindowText((HWND)lParam, bufstop5, MAX_PATH);
				mappingData.Stop[4] = max(0, min(9999, _wtoi(bufstop5)));
				if (canprint)
					Modified[Mofified_Stop5] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_6_STOP:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstop6[MAX_PATH];
				GetWindowText((HWND)lParam, bufstop6, MAX_PATH);
				mappingData.Stop[5] = max(0, min(9999, _wtoi(bufstop6)));
				if (canprint)
					Modified[Mofified_Stop6] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_7_STOP:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstop7[MAX_PATH];
				GetWindowText((HWND)lParam, bufstop7, MAX_PATH);
				mappingData.Stop[6] = max(0, min(9999, _wtoi(bufstop7)));
				if (canprint)
					Modified[Mofified_Stop7] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_DEST_8_STOP:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR bufstop8[MAX_PATH];
				GetWindowText((HWND)lParam, bufstop8, MAX_PATH);
				mappingData.Stop[7] = max(0, min(9999, _wtoi(bufstop8)));
				if (canprint)
					Modified[Mofified_Stop8] = true;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ACTION_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.ActionType[0] = (mappingData.ActionType[0] + 1) % 6;
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_RESETCONTENT, 0, 0);
				if (mappingData.ActionType[0] == 1)
				{
					mappingData.destID[0] = Mapping::MouseAction_None;
					mappingData.destDisable[0] = false;
					Modified[Mofified_vjDisable1] = true;
					for (int i = 0; i < Mapping::MouseAction_Count; i++)
					{
						const WCHAR* str = Mapping::MouseString((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[0] == 2)
				{
					mappingData.destID[0] = Mapping::SpecialAction_None;
					mappingData.destDisable[0] = false;
					Modified[Mofified_vjDisable1] = true;
					for (int i = 0; i < Mapping::SpecialAction_Count; i++)
					{
						const WCHAR* str = Mapping::SpecialString((SpecialActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[0] == 3)
				{
					mappingData.destID[0] = DestAxisMoveID::AxisMove_None;
					mappingData.destDisable[0] = false;
					Modified[Mofified_vjDisable1] = true;
					for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
					{
						WCHAR* str = DestinationButton::StringAxis((DestAxisMoveID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[0] == 4)
				{
					mappingData.destID[0] = DestAfterEffectID::AfterEffect_None;
					mappingData.destDisable[0] = false;
					Modified[Mofified_vjDisable1] = true;
					for (int i = 0; i < DestAfterEffectID::AfterEffect_Count; i++)
					{
						WCHAR* str = DestinationButton::StringEffect((DestAfterEffectID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[0] == 5)
				{
					mappingData.destID[0] = Mapping::ModulesAction_None;
					mappingData.destDisable[0] = false;
					Modified[Mofified_vjDisable1] = true;
					for (int i = 0; i < Mapping::ModulesAction_Count; i++)
					{
						const WCHAR* str = Mapping::ModulesString((ModulesActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.destID[0] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_1, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_ActionType1] = true;
				Modified[Mofified_vjID1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_1));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_1));
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ACTION_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.ActionType[1] = (mappingData.ActionType[1] + 1) % 6;
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_RESETCONTENT, 0, 0);
				if (mappingData.ActionType[1] == 1)
				{
					mappingData.destID[1] = Mapping::MouseAction_None;
					mappingData.destDisable[1] = false;
					Modified[Mofified_vjDisable2] = true;
					for (int i = 0; i < Mapping::MouseAction_Count; i++)
					{
						const WCHAR* str = Mapping::MouseString((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[1] == 2)
				{
					mappingData.destID[1] = Mapping::SpecialAction_None;
					mappingData.destDisable[1] = false;
					Modified[Mofified_vjDisable2] = true;
					for (int i = 0; i < Mapping::SpecialAction_Count; i++)
					{
						const WCHAR* str = Mapping::SpecialString((SpecialActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[1] == 3)
				{
					mappingData.destID[1] = DestAxisMoveID::AxisMove_None;
					mappingData.destDisable[1] = false;
					Modified[Mofified_vjDisable2] = true;
					for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
					{
						WCHAR* str = DestinationButton::StringAxis((DestAxisMoveID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[1] == 4)
				{
					mappingData.destID[1] = DestAfterEffectID::AfterEffect_None;
					mappingData.destDisable[1] = false;
					Modified[Mofified_vjDisable2] = true;
					for (int i = 0; i < DestAfterEffectID::AfterEffect_Count; i++)
					{
						WCHAR* str = DestinationButton::StringEffect((DestAfterEffectID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[1] == 5)
				{
					mappingData.destID[1] = Mapping::ModulesAction_None;
					mappingData.destDisable[1] = false;
					Modified[Mofified_vjDisable2] = true;
					for (int i = 0; i < Mapping::ModulesAction_Count; i++)
					{
						const WCHAR* str = Mapping::ModulesString((ModulesActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.destID[1] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_2, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_ActionType2] = true;
				Modified[Mofified_vjID2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_2));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_2));
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ACTION_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.ActionType[2] = (mappingData.ActionType[2] + 1) % 6;
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_RESETCONTENT, 0, 0);
				if (mappingData.ActionType[2] == 1)
				{
					mappingData.destID[2] = Mapping::MouseAction_None;
					mappingData.destDisable[2] = false;
					Modified[Mofified_vjDisable3] = true;
					for (int i = 0; i < Mapping::MouseAction_Count; i++)
					{
						const WCHAR* str = Mapping::MouseString((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[2] == 2)
				{
					mappingData.destID[2] = Mapping::SpecialAction_None;
					mappingData.destDisable[2] = false;
					Modified[Mofified_vjDisable3] = true;
					for (int i = 0; i < Mapping::SpecialAction_Count; i++)
					{
						const WCHAR* str = Mapping::SpecialString((SpecialActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[2] == 3)
				{
					mappingData.destID[2] = DestAxisMoveID::AxisMove_None;
					mappingData.destDisable[2] = false;
					Modified[Mofified_vjDisable3] = true;
					for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
					{
						WCHAR* str = DestinationButton::StringAxis((DestAxisMoveID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[2] == 4)
				{
					mappingData.destID[2] = DestAfterEffectID::AfterEffect_None;
					mappingData.destDisable[2] = false;
					Modified[Mofified_vjDisable3] = true;
					for (int i = 0; i < DestAfterEffectID::AfterEffect_Count; i++)
					{
						WCHAR* str = DestinationButton::StringEffect((DestAfterEffectID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[2] == 5)
				{
					mappingData.destID[2] = Mapping::ModulesAction_None;
					mappingData.destDisable[2] = false;
					Modified[Mofified_vjDisable3] = true;
					for (int i = 0; i < Mapping::ModulesAction_Count; i++)
					{
						const WCHAR* str = Mapping::ModulesString((ModulesActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.destID[2] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_3, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_ActionType3] = true;
				Modified[Mofified_vjID3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_3));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_3));
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ACTION_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.ActionType[3] = (mappingData.ActionType[3] + 1) % 6;
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_RESETCONTENT, 0, 0);
				if (mappingData.ActionType[3] == 1)
				{
					mappingData.destID[3] = Mapping::MouseAction_None;
					mappingData.destDisable[3] = false;
					Modified[Mofified_vjDisable4] = true;
					for (int i = 0; i < Mapping::MouseAction_Count; i++)
					{
						const WCHAR* str = Mapping::MouseString((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[3] == 2)
				{
					mappingData.destID[3] = Mapping::SpecialAction_None;
					mappingData.destDisable[3] = false;
					Modified[Mofified_vjDisable4] = true;
					for (int i = 0; i < Mapping::SpecialAction_Count; i++)
					{
						const WCHAR* str = Mapping::SpecialString((SpecialActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[3] == 3)
				{
					mappingData.destID[3] = DestAxisMoveID::AxisMove_None;
					mappingData.destDisable[3] = false;
					Modified[Mofified_vjDisable4] = true;
					for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
					{
						WCHAR* str = DestinationButton::StringAxis((DestAxisMoveID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[3] == 4)
				{
					mappingData.destID[3] = DestAfterEffectID::AfterEffect_None;
					mappingData.destDisable[3] = false;
					Modified[Mofified_vjDisable4] = true;
					for (int i = 0; i < DestAfterEffectID::AfterEffect_Count; i++)
					{
						WCHAR* str = DestinationButton::StringEffect((DestAfterEffectID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[3] == 5)
				{
					mappingData.destID[3] = Mapping::ModulesAction_None;
					mappingData.destDisable[3] = false;
					Modified[Mofified_vjDisable4] = true;
					for (int i = 0; i < Mapping::ModulesAction_Count; i++)
					{
						const WCHAR* str = Mapping::ModulesString((ModulesActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.destID[3] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_4, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_ActionType4] = true;
				Modified[Mofified_vjID4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_4));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_4));
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ACTION_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.ActionType[4] = (mappingData.ActionType[4] + 1) % 6;
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_RESETCONTENT, 0, 0);
				if (mappingData.ActionType[4] == 1)
				{
					mappingData.destID[4] = Mapping::MouseAction_None;
					mappingData.destDisable[4] = false;
					Modified[Mofified_vjDisable5] = true;
					for (int i = 0; i < Mapping::MouseAction_Count; i++)
					{
						const WCHAR* str = Mapping::MouseString((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[4] == 2)
				{
					mappingData.destID[4] = Mapping::SpecialAction_None;
					mappingData.destDisable[4] = false;
					Modified[Mofified_vjDisable5] = true;
					for (int i = 0; i < Mapping::SpecialAction_Count; i++)
					{
						const WCHAR* str = Mapping::SpecialString((SpecialActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[4] == 3)
				{
					mappingData.destID[4] = DestAxisMoveID::AxisMove_None;
					mappingData.destDisable[4] = false;
					Modified[Mofified_vjDisable5] = true;
					for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
					{
						WCHAR* str = DestinationButton::StringAxis((DestAxisMoveID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[4] == 4)
				{
					mappingData.destID[4] = DestAfterEffectID::AfterEffect_None;
					mappingData.destDisable[4] = false;
					Modified[Mofified_vjDisable5] = true;
					for (int i = 0; i < DestAfterEffectID::AfterEffect_Count; i++)
					{
						WCHAR* str = DestinationButton::StringEffect((DestAfterEffectID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[4] == 5)
				{
					mappingData.destID[4] = Mapping::ModulesAction_None;
					mappingData.destDisable[4] = false;
					Modified[Mofified_vjDisable5] = true;
					for (int i = 0; i < Mapping::ModulesAction_Count; i++)
					{
						const WCHAR* str = Mapping::ModulesString((ModulesActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.destID[4] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_5, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_ActionType5] = true;
				Modified[Mofified_vjID5] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_5));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_5));
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ACTION_6:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.ActionType[5] = (mappingData.ActionType[5] + 1) % 6;
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_RESETCONTENT, 0, 0);
				if (mappingData.ActionType[5] == 1)
				{
					mappingData.destID[5] = Mapping::MouseAction_None;
					mappingData.destDisable[5] = false;
					Modified[Mofified_vjDisable6] = true;
					for (int i = 0; i < Mapping::MouseAction_Count; i++)
					{
						const WCHAR* str = Mapping::MouseString((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[5] == 2)
				{
					mappingData.destID[5] = Mapping::SpecialAction_None;
					mappingData.destDisable[5] = false;
					Modified[Mofified_vjDisable6] = true;
					for (int i = 0; i < Mapping::SpecialAction_Count; i++)
					{
						const WCHAR* str = Mapping::SpecialString((SpecialActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[5] == 3)
				{
					mappingData.destID[5] = DestAxisMoveID::AxisMove_None;
					mappingData.destDisable[5] = false;
					Modified[Mofified_vjDisable6] = true;
					for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
					{
						WCHAR* str = DestinationButton::StringAxis((DestAxisMoveID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[5] == 4)
				{
					mappingData.destID[5] = DestAfterEffectID::AfterEffect_None;
					mappingData.destDisable[5] = false;
					Modified[Mofified_vjDisable6] = true;
					for (int i = 0; i < DestAfterEffectID::AfterEffect_Count; i++)
					{
						WCHAR* str = DestinationButton::StringEffect((DestAfterEffectID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[5] == 5)
				{
					mappingData.destID[5] = Mapping::ModulesAction_None;
					mappingData.destDisable[5] = false;
					Modified[Mofified_vjDisable6] = true;
					for (int i = 0; i < Mapping::ModulesAction_Count; i++)
					{
						const WCHAR* str = Mapping::ModulesString((ModulesActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.destID[5] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_6, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_ActionType6] = true;
				Modified[Mofified_vjID6] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_6));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_6));
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ACTION_7:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.ActionType[6] = (mappingData.ActionType[6] + 1) % 6;
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_RESETCONTENT, 0, 0);
				if (mappingData.ActionType[6] == 1)
				{
					mappingData.destID[6] = Mapping::MouseAction_None;
					mappingData.destDisable[6] = false;
					Modified[Mofified_vjDisable7] = true;
					for (int i = 0; i < Mapping::MouseAction_Count; i++)
					{
						const WCHAR* str = Mapping::MouseString((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[6] == 2)
				{
					mappingData.destID[6] = Mapping::SpecialAction_None;
					mappingData.destDisable[6] = false;
					Modified[Mofified_vjDisable7] = true;
					for (int i = 0; i < Mapping::SpecialAction_Count; i++)
					{
						const WCHAR* str = Mapping::SpecialString((SpecialActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[6] == 3)
				{
					mappingData.destID[6] = DestAxisMoveID::AxisMove_None;
					mappingData.destDisable[6] = false;
					Modified[Mofified_vjDisable7] = true;
					for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
					{
						WCHAR* str = DestinationButton::StringAxis((DestAxisMoveID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[6] == 4)
				{
					mappingData.destID[6] = DestAfterEffectID::AfterEffect_None;
					mappingData.destDisable[6] = false;
					Modified[Mofified_vjDisable7] = true;
					for (int i = 0; i < DestAfterEffectID::AfterEffect_Count; i++)
					{
						WCHAR* str = DestinationButton::StringEffect((DestAfterEffectID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[6] == 5)
				{
					mappingData.destID[6] = Mapping::ModulesAction_None;
					mappingData.destDisable[6] = false;
					Modified[Mofified_vjDisable7] = true;
					for (int i = 0; i < Mapping::ModulesAction_Count; i++)
					{
						const WCHAR* str = Mapping::ModulesString((ModulesActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.destID[6] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_7, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_ActionType7] = true;
				Modified[Mofified_vjID7] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_7));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_7));
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_ACTION_8:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.ActionType[7] = (mappingData.ActionType[7] + 1) % 6;
				SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_RESETCONTENT, 0, 0);
				if (mappingData.ActionType[7] == 1)
				{
					mappingData.destID[7] = Mapping::MouseAction_None;
					mappingData.destDisable[7] = false;
					Modified[Mofified_vjDisable8] = true;
					for (int i = 0; i < Mapping::MouseAction_Count; i++)
					{
						const WCHAR* str = Mapping::MouseString((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[7] == 2)
				{
					mappingData.destID[7] = Mapping::SpecialAction_None;
					mappingData.destDisable[7] = false;
					Modified[Mofified_vjDisable8] = true;
					for (int i = 0; i < Mapping::SpecialAction_Count; i++)
					{
						const WCHAR* str = Mapping::SpecialString((SpecialActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[7] == 3)
				{
					mappingData.destID[7] = DestAxisMoveID::AxisMove_None;
					mappingData.destDisable[7] = false;
					Modified[Mofified_vjDisable8] = true;
					for (int i = 0; i < DestAxisMoveID::AxisMove_Count; i++)
					{
						WCHAR* str = DestinationButton::StringAxis((DestAxisMoveID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[7] == 4)
				{
					mappingData.destID[7] = DestAfterEffectID::AfterEffect_None;
					mappingData.destDisable[7] = false;
					Modified[Mofified_vjDisable8] = true;
					for (int i = 0; i < DestAfterEffectID::AfterEffect_Count; i++)
					{
						WCHAR* str = DestinationButton::StringEffect((DestAfterEffectID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else if (mappingData.ActionType[7] == 5)
				{
					mappingData.destID[7] = Mapping::ModulesAction_None;
					mappingData.destDisable[7] = false;
					Modified[Mofified_vjDisable8] = true;
					for (int i = 0; i < Mapping::ModulesAction_Count; i++)
					{
						const WCHAR* str = Mapping::ModulesString((ModulesActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				else
				{
					mappingData.destID[7] = DestButtonID::Destination_None;
					for (int i = 0; i < DestButtonID::Destination_Count; i++)
					{
						WCHAR* str = DestinationButton::String((DestButtonID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_DEST_8, CB_ADDSTRING, 0, LPARAM(str));
					}
				}
				Modified[Mofified_ActionType8] = true;
				Modified[Mofified_vjID8] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				Hide(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_8));
				Show(GetDlgItem(hWnd, IDC_MAPPING_BTN_DEST_8));
				SendMessage(hWnd, WM_GRID, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_OVERCONTROL_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Overcontrol[0] = (mappingData.Overcontrol[0] + 1) % 3;
				Modified[Mofified_Overcontrol1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_OVERCONTROL_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Overcontrol[1] = (mappingData.Overcontrol[1] + 1) % 3;
				Modified[Mofified_Overcontrol2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_OVERCONTROL_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Overcontrol[2] = (mappingData.Overcontrol[2] + 1) % 3;
				Modified[Mofified_Overcontrol3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_OVERCONTROL_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Overcontrol[3] = (mappingData.Overcontrol[3] + 1) % 3;
				Modified[Mofified_Overcontrol4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_OVERCONTROL_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Overcontrol[4] = (mappingData.Overcontrol[4] + 1) % 3;
				Modified[Mofified_Overcontrol5] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_OVERCONTROL_6:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Overcontrol[5] = (mappingData.Overcontrol[5] + 1) % 3;
				Modified[Mofified_Overcontrol6] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_OVERCONTROL_7:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Overcontrol[6] = (mappingData.Overcontrol[6] + 1) % 3;
				Modified[Mofified_Overcontrol7] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_OVERCONTROL_8:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Overcontrol[7] = (mappingData.Overcontrol[7] + 1) % 3;
				Modified[Mofified_Overcontrol8] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SWITCH_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Switch[0] = (mappingData.Switch[0] + 1) % 3;
				Modified[Mofified_Switch1] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SWITCH_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Switch[1] = (mappingData.Switch[1] + 1) % 3;
				Modified[Mofified_Switch2] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SWITCH_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Switch[2] = (mappingData.Switch[2] + 1) % 3;
				Modified[Mofified_Switch3] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SWITCH_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Switch[3] = (mappingData.Switch[3] + 1) % 3;
				Modified[Mofified_Switch4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SWITCH_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Switch[4] = (mappingData.Switch[4] + 1) % 3;
				Modified[Mofified_Switch5] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SWITCH_6:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Switch[5] = (mappingData.Switch[5] + 1) % 3;
				Modified[Mofified_Switch6] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SWITCH_7:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Switch[6] = (mappingData.Switch[6] + 1) % 3;
				Modified[Mofified_Switch7] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_SWITCH_8:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Switch[7] = (mappingData.Switch[7] + 1) % 3;
				Modified[Mofified_Switch8] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_01:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[0];
				if (old == 1)
				{
					if (mappingData.Mouse[3])
						mappingData.Mouse[0] = 0;
					mappingData.Mouse[3] = (mappingData.Mouse[3]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[0] = 1;
					mappingData.Mouse[3] = 0;
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_02)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_02)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_03)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_03)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_04)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_04)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_05)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_05)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_02:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[0];
				if (old == 2)
				{
					if (mappingData.Mouse[3])
						mappingData.Mouse[0] = 0;
					mappingData.Mouse[3] = (mappingData.Mouse[3]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[0] = 2;
					mappingData.Mouse[3] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_01)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_01)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_03)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_03)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_04)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_04)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_05)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_05)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_03:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[0];
				if (old == 3)
				{
					if (mappingData.Mouse[3])
						mappingData.Mouse[0] = 0;
					mappingData.Mouse[3] = (mappingData.Mouse[3]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[0] = 3;
					mappingData.Mouse[3] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_01)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_01)); }
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_02)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_02)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_04)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_04)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_05)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_05)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_04:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[0];
				if (old == 4)
				{
					if (mappingData.Mouse[3])
						mappingData.Mouse[0] = 0;
					mappingData.Mouse[3] = (mappingData.Mouse[3]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[0] = 4;
					mappingData.Mouse[3] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_01)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_01)); }
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_02)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_02)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_03)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_03)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_05)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_05)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_05:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[0];
				if (old == 5)
				{
					if (mappingData.Mouse[3])
						mappingData.Mouse[0] = 0;
					mappingData.Mouse[3] = (mappingData.Mouse[3]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[0] = 5;
					mappingData.Mouse[3] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_01)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_01)); }
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_02)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_02)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_03)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_03)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_04)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_04)); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_11:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[1];
				if (old == 1)
				{
					if (mappingData.Mouse[4])
						mappingData.Mouse[1] = 0;
					mappingData.Mouse[4] = (mappingData.Mouse[4]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[1] = 1;
					mappingData.Mouse[4] = 0;
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_12)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_12)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_13)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_13)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_14)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_14)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_15)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_15)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_12:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[1];
				if (old == 2)
				{
					if (mappingData.Mouse[4])
						mappingData.Mouse[1] = 0;
					mappingData.Mouse[4] = (mappingData.Mouse[4]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[1] = 2;
					mappingData.Mouse[4] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_11)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_11)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_13)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_13)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_14)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_14)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_15)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_15)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_13:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[1];
				if (old == 3)
				{
					if (mappingData.Mouse[4])
						mappingData.Mouse[1] = 0;
					mappingData.Mouse[4] = (mappingData.Mouse[4]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[1] = 3;
					mappingData.Mouse[4] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_11)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_11)); }
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_12)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_12)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_14)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_14)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_15)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_15)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_14:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[1];
				if (old == 4)
				{
					if (mappingData.Mouse[4])
						mappingData.Mouse[1] = 0;
					mappingData.Mouse[4] = (mappingData.Mouse[4]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[1] = 4;
					mappingData.Mouse[4] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_11)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_11)); }
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_12)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_12)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_13)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_13)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_15)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_15)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_15:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[1];
				if (old == 5)
				{
					if (mappingData.Mouse[4])
						mappingData.Mouse[1] = 0;
					mappingData.Mouse[4] = (mappingData.Mouse[4]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[1] = 5;
					mappingData.Mouse[4] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_11)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_11)); }
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_12)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_12)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_13)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_13)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_14)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_14)); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_21:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[2];
				if (old == 1)
				{
					if (mappingData.Mouse[5])
						mappingData.Mouse[2] = 0;
					mappingData.Mouse[5] = (mappingData.Mouse[5]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[2] = 1;
					mappingData.Mouse[5] = 0;
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_22)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_22)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_23)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_23)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_24)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_24)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_25)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_25)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_22:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[2];
				if (old == 2)
				{
					if (mappingData.Mouse[5])
						mappingData.Mouse[2] = 0;
					mappingData.Mouse[5] = (mappingData.Mouse[5]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[2] = 2;
					mappingData.Mouse[5] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_21)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_21)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_23)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_23)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_24)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_24)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_25)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_25)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_23:
		{
			unsigned char old = mappingData.Mouse[2];
			if (old == 3)
			{
				if (mappingData.Mouse[5])
					mappingData.Mouse[2] = 0;
				mappingData.Mouse[5] = (mappingData.Mouse[5]) ? 0 : 1;
			}
			else
			{
				mappingData.Mouse[2] = 3;
				mappingData.Mouse[5] = 0;
				if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_21)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_21)); }
				if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_22)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_22)); }
				if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_24)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_24)); }
				if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_25)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_25)); SendMessage(hWnd, WM_GRID, 0, 0); }
			}
			Modified[Mofified_Mouse1] = true;
			Modified[Mofified_Mouse4] = true;
			Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
			break;
		}
		case IDC_MAPPING_MOUSE_24:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[2];
				if (old == 4)
				{
					if (mappingData.Mouse[5])
						mappingData.Mouse[2] = 0;
					mappingData.Mouse[5] = (mappingData.Mouse[5]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[2] = 4;
					mappingData.Mouse[5] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_21)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_21)); }
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_22)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_22)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_23)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_23)); }
					if (old == 5) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_25)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_25)); SendMessage(hWnd, WM_GRID, 0, 0); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_25:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				unsigned char old = mappingData.Mouse[2];
				if (old == 5)
				{
					if (mappingData.Mouse[5])
						mappingData.Mouse[2] = 0;
					mappingData.Mouse[5] = (mappingData.Mouse[5]) ? 0 : 1;
				}
				else
				{
					mappingData.Mouse[2] = 5;
					mappingData.Mouse[5] = 0;
					if (old == 1) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_21)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_21)); }
					if (old == 2) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_22)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_22)); }
					if (old == 3) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_23)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_23)); }
					if (old == 4) { Hide(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_24)); Show(GetDlgItem(hWnd, IDC_MAPPING_MOUSE_24)); }
				}
				Modified[Mofified_Mouse1] = true;
				Modified[Mofified_Mouse4] = true;
				SendMessage(hWnd, WM_GRID, 0, 0);
				Hide(GetDlgItem(hWnd, LOWORD(wParam))); Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_MOUSE_GRID:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				mappingData.Mouse[6] = (mappingData.Mouse[6] + 1) % 3;
				Modified[Mofified_Mouse7] = true;
				Hide(GetDlgItem(hWnd, LOWORD(wParam)));
				Show(GetDlgItem(hWnd, LOWORD(wParam)));
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_GRID_X:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				mappingData.Grid[0] = max(-32768, min(32767, _wtoi(buf)));
				if (canprint) Modified[Mofified_Grid1] = true;
				break;
			}
			case EN_SETFOCUS:
			{
				whohasfocus = 1;
				break;
			}
			case EN_KILLFOCUS:
			{
				whohasfocus = 0;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_GRID_Y:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				mappingData.Grid[1] = max(-32768, min(32767, _wtoi(buf)));
				if (canprint) Modified[Mofified_Grid2] = true;
				break;
			}
			case EN_SETFOCUS:
			{
				whohasfocus = 1;
				break;
			}
			case EN_KILLFOCUS:
			{
				whohasfocus = 0;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_GRID_W:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				mappingData.Grid[2] = max(0, min(65535, _wtoi(buf)));
				if (canprint) Modified[Mofified_Grid3] = true;
				break;
			}
			case EN_SETFOCUS:
			{
				whohasfocus = 2;
				break;
			}
			case EN_KILLFOCUS:
			{
				whohasfocus = 0;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_GRID_H:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				mappingData.Grid[3] = max(0, min(65535, _wtoi(buf)));
				if (canprint) Modified[Mofified_Grid4] = true;
				break;
			}
			case EN_SETFOCUS:
			{
				whohasfocus = 2;
				break;
			}
			case EN_KILLFOCUS:
			{
				whohasfocus = 0;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_GRID_NW:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				mappingData.Grid[4] = max(0, min(65535, _wtoi(buf)));
				if (canprint) Modified[Mofified_Grid5] = true;
				break;
			}
			case EN_SETFOCUS:
			{
				whohasfocus = 3;
				break;
			}
			case EN_KILLFOCUS:
			{
				whohasfocus = 0;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_GRID_NH:
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				WCHAR buf[MAX_PATH];
				GetWindowText((HWND)lParam, buf, MAX_PATH);
				mappingData.Grid[5] = max(0, min(65535, _wtoi(buf)));
				if (canprint) Modified[Mofified_Grid6] = true;
				break;
			}
			case EN_SETFOCUS:
			{
				whohasfocus = 3;
				break;
			}
			case EN_KILLFOCUS:
			{
				whohasfocus = 0;
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_X:
		{
			switch (HIWORD(wParam))
			{
			case STN_CLICKED:
			{
				start = std::chrono::system_clock::now();
				SetTimer(m_hDlg, 1, 10, NULL);
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_Y:
		{
			switch (HIWORD(wParam))
			{
			case STN_CLICKED:
			{
				if (capturehasbeendone)
				{
					WCHAR buf[6];
					switch (whohasfocus)
					{
					case 1:
						GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_X), buf, 6);
						SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_X), buf);
						GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_Y), buf, 6);
						SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y), buf);
						break;
					case 2:
						GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_X), buf, 6);
						SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_W), buf);
						GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_Y), buf, 6);
						SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_H), buf);
						break;
					case 3:
						GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_X), buf, 6);
						SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW), buf);
						GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_Y), buf, 6);
						SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH), buf);
						break;
					}
				}
				break;
			}
			}
			break;
		}
		case IDC_MAPPING_BTN_SRCE_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_SRCE_1), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_SRCE_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_SRCE_2), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_SRCE_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_SRCE_3), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_SRCE_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_SRCE_4), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_SRCE_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_SRCE_5), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_LED:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_LED), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_DEST_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_DEST_1), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_DEST_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_DEST_2), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_DEST_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_DEST_3), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_DEST_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_DEST_4), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_DEST_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_DEST_5), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_DEST_6:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_DEST_6), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_DEST_7:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_DEST_7), TRUE);
				break;
			}
			break;
		}
		case IDC_MAPPING_BTN_DEST_8:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				ComboBox_ShowDropdown(GetDlgItem(hWnd, IDC_MAPPING_DEST_8), TRUE);
				break;
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

void MappingDataDlg::ShowNoRelease()
{
	bool no[8];
	bool nl[8];
	for (int i = 0; i < 8; i++)
	{
		nl[i] = !mappingData.NlRelease[i];
		no[i] = nl[i] && !mappingData.NoRelease[i];
	}
	if (state[0]) { Show(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_1)); Show(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_1)); } else { if (no[0]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_1)); if (nl[0]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_1)); }
	if (state[1]) { Show(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_2)); Show(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_2)); } else { if (no[1]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_2)); if (nl[1]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_2)); }
	if (state[2]) { Show(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_3)); Show(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_3)); } else { if (no[2]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_3)); if (nl[2]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_3)); }
	if (state[3]) { Show(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_4)); Show(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_4)); } else { if (no[3]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_4)); if (nl[3]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_4)); }
	if (state[4]) { Show(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_5)); Show(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_5)); } else { if (no[4]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_5)); if (nl[4]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_5)); }
	if (state[5]) { Show(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_6)); Show(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_6)); } else { if (no[5]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_6)); if (nl[5]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_6)); }
	if (state[6]) { Show(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_7)); Show(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_7)); } else { if (no[6]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_7)); if (nl[6]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_7)); }
	if (state[7]) { Show(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_8)); Show(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_8)); } else { if (no[7]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NORELEASE_8)); if (nl[7]) Hide(GetDlgItem(m_hDlg, IDC_MAPPING_NLRELEASE_8)); }
}

void MappingDataDlg::Show(HWND hWnd)
{
	::ShowWindow((hWnd == NULL) ? m_hDlg : hWnd, SW_SHOW);
}

void MappingDataDlg::Hide(HWND hWnd)
{
	::ShowWindow((hWnd == NULL) ? m_hDlg : hWnd, SW_HIDE);
}

BOOL MappingDataDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}

void MappingDataDlg::SetTransparency(bool transparencyon)
{
	if (transparencyon)
		SetWindowTransparent(m_hDlg, true, tape.Opacity);
	else
		SetWindowTransparent(m_hDlg, false, NULL);
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_1));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_1));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_2));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_2));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_3));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_3));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_4));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_4));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_5));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_SRCE_5));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_LED));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_LED));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_1));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_1));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_2));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_2));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_3));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_3));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_4));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_4));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_5));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_5));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_6));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_6));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_7));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_7));
	Hide(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_8));
	Show(GetDlgItem(m_hDlg, IDC_MAPPING_BTN_DEST_8));
}
