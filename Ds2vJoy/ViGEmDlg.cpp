#include "stdafx.h"
#include "ViGEmDlg.h"
#include "ViGEm.h"

ViGEmDlg::ViGEmDlg()
{
}

ViGEmDlg::~ViGEmDlg()
{
}

void ViGEmDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_VIGEM), hWnd, (DLGPROC)Proc, LPARAM(this));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_ACTIVE, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_PAD, WM_SETFONT, WPARAM(tape.hStatic), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_X360, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS4, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_1, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_2, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_3, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_4, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_5, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_6, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_7, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_8, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_9, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_10, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_11, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_12, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_13, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_14, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_15, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_16, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_17, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_18, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_19, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_20, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_21, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_22, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_23, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS_24, WM_SETFONT, WPARAM(tape.hCombo), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_1, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_2, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_3, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_4, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_5, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_6, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_7, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_8, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_9, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_10, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_11, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_12, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_13, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_14, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_15, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_16, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_17, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_18, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_19, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_20, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_21, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_22, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_23, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_24, WM_SETFONT, WPARAM(tape.hCheck), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_ACTIVE_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_X360_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_DS4_CHK, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_1, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_2, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_3, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_4, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_5, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_6, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_7, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_8, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_9, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_10, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_11, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_12, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_13, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_14, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_15, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_16, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_17, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_18, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_19, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_20, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_21, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_22, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_23, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SendDlgItemMessage(m_hDlg, IDC_VIGEM_VJOY_24, WM_SETFONT, WPARAM(tape.hCheck2), MAKELPARAM(TRUE, 0));
	SetWindowText(GetDlgItem(m_hDlg, IDC_VIGEM_ACTIVE), I18N.VIGEM_ACTIVE);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VIGEM_PAD), I18N.VIGEM_PAD);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VIGEM_X360), I18N.VIGEM_X360);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VIGEM_DS4), I18N.VIGEM_DS4);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VIGEM_INSTALL), I18N.VIGEM_INSTALL);
	SetWindowText(GetDlgItem(m_hDlg, IDC_VIGEM_STATUS), I18N.VIGEM_STATUS);
	Hide();
}

void ViGEmDlg::Init2()
{
	std::thread(&ViGEmDlg::_ChangeComboBox, this, m_hDlg).detach();
}

void ViGEmDlg::_ChangeComboBox(HWND hWnd)
{
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
	_InitDialog(hWnd);
}

void ViGEmDlg::_InitDialog(HWND hWnd)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	WCHAR* str = WCHARI();
	for (int i = 0; i < dsButtonID::button_Count; i++)
	{
		str = dsButton::String((dsButtonID)i);
		if ((!tape.target_X360[0] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[0] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_1, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[1] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[1] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_2, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[2] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[2] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_3, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[3] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[3] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_4, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[4] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[4] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_5, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[5] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[5] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_6, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[6] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[6] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_7, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[7] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[7] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_8, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[8] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[8] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_9, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[9] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[9] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_10, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[10] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[10] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_11, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[11] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[11] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_12, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[12] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[12] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_13, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[13] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[13] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_14, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[14] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[14] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_15, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[15] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[15] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_16, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[16] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[16] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_17, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[17] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[17] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_18, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[18] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[18] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_19, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[19] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[19] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_20, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[20] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[20] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_21, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[21] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[21] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_22, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[22] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[22] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_23, CB_ADDSTRING, 0, LPARAM(str));
		if ((!tape.target_X360[23] && tape.DesiredVirtualPad == 1) || (!tape.target_DS4[23] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_24, CB_ADDSTRING, 0, LPARAM(str));
	}
	for (int i = 0; i < vJoyButtonID::button_Count; i++)
	{
		str = vJoyButton::String((vJoyButtonID)i);
		if ((tape.target_X360[0] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[0] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_1, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[1] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[1] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_2, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[2] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[2] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_3, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[3] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[3] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_4, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[4] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[4] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_5, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[5] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[5] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_6, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[6] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[6] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_7, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[7] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[7] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_8, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[8] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[8] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_9, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[9] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[9] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_10, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[10] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[10] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_11, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[11] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[11] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_12, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[12] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[12] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_13, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[13] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[13] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_14, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[14] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[14] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_15, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[15] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[15] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_16, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[16] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[16] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_17, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[17] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[17] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_18, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[18] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[18] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_19, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[19] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[19] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_20, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[20] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[20] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_21, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[21] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[21] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_22, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[22] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[22] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_23, CB_ADDSTRING, 0, LPARAM(str));
		if ((tape.target_X360[23] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[23] && tape.DesiredVirtualPad == 2))
			SendDlgItemMessage(hWnd, IDC_VIGEM_DS_24, CB_ADDSTRING, 0, LPARAM(str));
	}
	if (IsWindowVisible(hWnd))
		_ShowWindow(hWnd);
}

void ViGEmDlg::_ShowWindow(HWND hWnd)
{
	CheckDlgButton(hWnd, IDC_VIGEM_ACTIVE_CHK, tape.ViGEmActive);
	CheckDlgButton(hWnd, IDC_VIGEM_X360_CHK, (tape.DesiredVirtualPad) == 1 ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(hWnd, IDC_VIGEM_DS4_CHK, (tape.DesiredVirtualPad) == 2 ? BST_CHECKED : BST_UNCHECKED);

	switch (tape.DesiredVirtualPad)
	{
	case 1:
	{
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
	}
	case 2:
	{
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
	}
}

INT_PTR CALLBACK ViGEmDlg::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ViGEmDlg* dlg;

	if (message == WM_INITDIALOG)
	{
		dlg = reinterpret_cast<ViGEmDlg*>(lParam);
		SetWindowLongPtr(hWnd, DWLP_USER, lParam);
	}
	else
		dlg = reinterpret_cast<ViGEmDlg*>(GetWindowLongPtr(hWnd, DWLP_USER));
	if (dlg)
	{
		INT_PTR result;
		result = dlg->_proc(hWnd, message, wParam, lParam);
		return result;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR ViGEmDlg::_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		switch (vg.GetViGEmState())
		{
		case -1:
		case 0:
		{
			if (CtrlID == IDC_VIGEM_INSTALL) return (LRESULT)tape.hB_Not_Installed;
			if (CtrlID == IDC_VIGEM_STATUS) return (LRESULT)tape.hB_Not_Installed;
			break;
		}
		case 1:
		{
			if (CtrlID == IDC_VIGEM_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_VIGEM_STATUS) return (LRESULT)tape.hB_Running;
			break;
		}
		case 2:
		{
			if (CtrlID == IDC_VIGEM_INSTALL) return (LRESULT)tape.hB_Running;
			if (CtrlID == IDC_VIGEM_STATUS) return (LRESULT)tape.hB_Paused;
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
		case IDC_VIGEM_ACTIVE_CHK:
		case IDC_VIGEM_X360_CHK:
		case IDC_VIGEM_DS4_CHK:
		case IDC_VIGEM_VJOY_1:
		case IDC_VIGEM_VJOY_2:
		case IDC_VIGEM_VJOY_3:
		case IDC_VIGEM_VJOY_4:
		case IDC_VIGEM_VJOY_5:
		case IDC_VIGEM_VJOY_6:
		case IDC_VIGEM_VJOY_7:
		case IDC_VIGEM_VJOY_8:
		case IDC_VIGEM_VJOY_9:
		case IDC_VIGEM_VJOY_10:
		case IDC_VIGEM_VJOY_11:
		case IDC_VIGEM_VJOY_12:
		case IDC_VIGEM_VJOY_13:
		case IDC_VIGEM_VJOY_14:
		case IDC_VIGEM_VJOY_15:
		case IDC_VIGEM_VJOY_16:
		case IDC_VIGEM_VJOY_17:
		case IDC_VIGEM_VJOY_18:
		case IDC_VIGEM_VJOY_19:
		case IDC_VIGEM_VJOY_20:
		case IDC_VIGEM_VJOY_21:
		case IDC_VIGEM_VJOY_22:
		case IDC_VIGEM_VJOY_23:
		case IDC_VIGEM_VJOY_24:
		{
			SetTextColor(hdcStatic, tape.ink_STATIC_Checkbox2);
			break;
		}
		case IDC_VIGEM_ACTIVE:
		case IDC_VIGEM_X360:
		case IDC_VIGEM_DS4:
		{
			SetTextColor(hdcStatic, tape.ink_STATIC_Checkbox);
			break;
		}
		default:
		{
			SetTextColor(hdcStatic, tape.ink_STATIC);
			break;
		}
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
	case WM_CTLCOLORLISTBOX:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, tape.ink_LIST);
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

			LPCWSTR b1Text = I18N.STATE_WAITING;
			LPCWSTR b2Text = I18N.STATE_WAITING;
			SetTextColor(hDC, tape.ink_BTN_Install);
			switch (vg.GetViGEmState())
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
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_VIGEM_INSTALL), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_VIGEM_INSTALL), &rect);
			SelectObject(hDC, tape.hButton2);
			DrawText(hDC, b1Text, 9, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			hDC = BeginPaint(GetDlgItem(hWnd, IDC_VIGEM_STATUS), &ps);
			GetClientRect(GetDlgItem(hWnd, IDC_VIGEM_STATUS), &rect);
			SelectObject(hDC, tape.hButton2);
			DrawText(hDC, b2Text, 9, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			FrameRect(hDC, &rect, tape.hB_BTN_Border);

			::ReleaseDC(hWnd, hDC);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_SHOWWINDOW:
	{
		if (wParam == TRUE || lParam == 3)
			vg.ViGEmStates();
		if (wParam == TRUE)
			std::thread(&ViGEmDlg::_ShowWindow, this, hWnd).detach();
		break;
	}
	case WM_INITDIALOG:
	{
		std::thread(&ViGEmDlg::_InitDialog, this, hWnd).detach();
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
			case IDC_VIGEM_ACTIVE_CHK:
			case IDC_VIGEM_X360_CHK:
			case IDC_VIGEM_DS4_CHK:
			case IDC_VIGEM_VJOY_1:
			case IDC_VIGEM_VJOY_2:
			case IDC_VIGEM_VJOY_3:
			case IDC_VIGEM_VJOY_4:
			case IDC_VIGEM_VJOY_5:
			case IDC_VIGEM_VJOY_6:
			case IDC_VIGEM_VJOY_7:
			case IDC_VIGEM_VJOY_8:
			case IDC_VIGEM_VJOY_9:
			case IDC_VIGEM_VJOY_10:
			case IDC_VIGEM_VJOY_11:
			case IDC_VIGEM_VJOY_12:
			case IDC_VIGEM_VJOY_13:
			case IDC_VIGEM_VJOY_14:
			case IDC_VIGEM_VJOY_15:
			case IDC_VIGEM_VJOY_16:
			case IDC_VIGEM_VJOY_17:
			case IDC_VIGEM_VJOY_18:
			case IDC_VIGEM_VJOY_19:
			case IDC_VIGEM_VJOY_20:
			case IDC_VIGEM_VJOY_21:
			case IDC_VIGEM_VJOY_22:
			case IDC_VIGEM_VJOY_23:
			case IDC_VIGEM_VJOY_24:
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
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_VIGEM_ACTIVE_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					PostMessage(m_hWnd, WM_CHANGE_PAD, 1, 0);
				else
					PostMessage(m_hWnd, WM_CHANGE_PAD, 0, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_X360_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					CheckDlgButton(hWnd, IDC_VIGEM_DS4_CHK, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_VIGEM_X360_CHK, BST_CHECKED);
				tape.DesiredVirtualPad = 1;
				tape.Save(tape.Setting_DesiredVirtualPad);
				std::thread(&ViGEmDlg::_ChangeComboBox, this, hWnd).detach();
				SendMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS4_CHK:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
					CheckDlgButton(hWnd, IDC_VIGEM_X360_CHK, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_VIGEM_DS4_CHK, BST_CHECKED);
				tape.DesiredVirtualPad = 2;
				tape.Save(tape.Setting_DesiredVirtualPad);
				std::thread(&ViGEmDlg::_ChangeComboBox, this, hWnd).detach();
				SendMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_1:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[0] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[0] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_1, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[0] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[0] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_SETCURSEL, tape.vjtarget_X360[0], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_SETCURSEL, tape.dstarget_X360[0], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_2:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[1] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[1] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_2, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[1] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[1] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_SETCURSEL, tape.vjtarget_X360[1], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_SETCURSEL, tape.dstarget_X360[1], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_3:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[2] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[2] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_3, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[2] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[2] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_SETCURSEL, tape.vjtarget_X360[2], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_SETCURSEL, tape.dstarget_X360[2], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_4:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[3] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[3] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_4, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[3] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[3] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_SETCURSEL, tape.vjtarget_X360[3], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_SETCURSEL, tape.dstarget_X360[3], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_5:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[4] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[4] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_5, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[4] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[4] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_SETCURSEL, tape.vjtarget_X360[4], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_SETCURSEL, tape.dstarget_X360[4], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_6:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[5] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[5] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_6, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[5] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[5] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_SETCURSEL, tape.vjtarget_X360[5], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_SETCURSEL, tape.dstarget_X360[5], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_7:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[6] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[6] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_7, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[6] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[6] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_SETCURSEL, tape.vjtarget_X360[6], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_SETCURSEL, tape.dstarget_X360[6], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_8:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[7] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[7] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_8, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[7] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[7] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_SETCURSEL, tape.vjtarget_X360[7], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_SETCURSEL, tape.dstarget_X360[7], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_9:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[8] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[8] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_9, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[8] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[8] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_SETCURSEL, tape.vjtarget_X360[8], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_SETCURSEL, tape.dstarget_X360[8], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_10:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[9] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[9] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_10, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[9] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[9] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_SETCURSEL, tape.vjtarget_X360[9], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_SETCURSEL, tape.dstarget_X360[9], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_11:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[10] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[10] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_11, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[10] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[10] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_SETCURSEL, tape.vjtarget_X360[10], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_SETCURSEL, tape.dstarget_X360[10], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_12:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[11] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[11] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_12, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[11] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[11] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_SETCURSEL, tape.vjtarget_X360[11], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_SETCURSEL, tape.dstarget_X360[11], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_13:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[12] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[12] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_13, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[12] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[12] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_SETCURSEL, tape.vjtarget_X360[12], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_SETCURSEL, tape.dstarget_X360[12], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_14:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[13] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[13] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_14, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[13] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[13] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_SETCURSEL, tape.vjtarget_X360[13], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_SETCURSEL, tape.dstarget_X360[13], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_15:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[14] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[14] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_15, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[14] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[14] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_SETCURSEL, tape.vjtarget_X360[14], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_SETCURSEL, tape.dstarget_X360[14], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_16:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[15] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[15] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_16, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[15] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[15] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_SETCURSEL, tape.vjtarget_X360[15], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_SETCURSEL, tape.dstarget_X360[15], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_17:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[16] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[16] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_17, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[16] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[16] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_SETCURSEL, tape.vjtarget_X360[16], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_SETCURSEL, tape.dstarget_X360[16], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_18:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[17] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[17] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_18, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[17] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[17] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_SETCURSEL, tape.vjtarget_X360[17], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_SETCURSEL, tape.dstarget_X360[17], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_19:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[18] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[18] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_19, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[18] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[18] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_SETCURSEL, tape.vjtarget_X360[18], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_SETCURSEL, tape.dstarget_X360[18], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_20:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[19] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[19] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_20, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[19] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[19] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_SETCURSEL, tape.vjtarget_X360[19], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_SETCURSEL, tape.dstarget_X360[19], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_21:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[20] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[20] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_21, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[20] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[20] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_SETCURSEL, tape.vjtarget_X360[20], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_SETCURSEL, tape.dstarget_X360[20], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_22:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[21] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[21] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_22, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[21] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[21] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_SETCURSEL, tape.vjtarget_X360[21], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_SETCURSEL, tape.dstarget_X360[21], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_23:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[22] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[22] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_23, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[22] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[22] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_SETCURSEL, tape.vjtarget_X360[2], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_SETCURSEL, tape.dstarget_X360[22], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_VJOY_24:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
				if (tape.DesiredVirtualPad == 1) { tape.target_X360[23] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_X360); }
				else { tape.target_DS4[23] = IsDlgButtonChecked(hWnd, LOWORD(wParam)); tape.Save(tape.Setting_target_DS4); }
				SendDlgItemMessage(hWnd, IDC_VIGEM_DS_24, CB_RESETCONTENT, 0, 0);
				if ((tape.target_X360[23] && tape.DesiredVirtualPad == 1) || (tape.target_DS4[23] && tape.DesiredVirtualPad == 2))
				{
					for (int i = 0; i < vJoyButtonID::button_Count; i++)
					{
						WCHAR* str = vJoyButton::String((vJoyButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_SETCURSEL, tape.vjtarget_X360[23], 0);
				}
				else
				{
					for (int i = 0; i < dsButtonID::button_Count; i++)
					{
						WCHAR* str = dsButton::String((dsButtonID)i);
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_ADDSTRING, 0, LPARAM(str));
					}
					SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_SETCURSEL, tape.dstarget_X360[23], 0);
				}
				Hide();
				Show();
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_1:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[0]) { tape.vjtarget_X360[0] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[0] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[0]) { tape.vjtarget_DS4[0] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[0] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_1), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_2:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[1]) { tape.vjtarget_X360[1] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[1] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[1]) { tape.vjtarget_DS4[1] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[1] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_2), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_3:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[2]) { tape.vjtarget_X360[2] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[2] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[2]) { tape.vjtarget_DS4[2] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[2] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_3), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_4:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[3]) { tape.vjtarget_X360[3] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[3] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[3]) { tape.vjtarget_DS4[3] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[3] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_4), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_5:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[4]) { tape.vjtarget_X360[4] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[4] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[4]) { tape.vjtarget_DS4[4] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[4] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_5), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_6:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[5]) { tape.vjtarget_X360[5] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[5] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[5]) { tape.vjtarget_DS4[5] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[5] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_6), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_7:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[6]) { tape.vjtarget_X360[6] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[6] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[6]) { tape.vjtarget_DS4[6] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[6] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_7), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_8:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[7]) { tape.vjtarget_X360[7] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[7] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[7]) { tape.vjtarget_DS4[7] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[7] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_8), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_9:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[8]) { tape.vjtarget_X360[8] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[8] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[8]) { tape.vjtarget_DS4[8] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[8] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_9), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_10:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[9]) { tape.vjtarget_X360[9] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[9] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[9]) { tape.vjtarget_DS4[9] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[9] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_10), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_11:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[10]) { tape.vjtarget_X360[10] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[10] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[10]) { tape.vjtarget_DS4[10] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[10] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_11), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_12:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[11]) { tape.vjtarget_X360[11] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[11] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[11]) { tape.vjtarget_DS4[11] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[11] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_12), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_13:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[12]) { tape.vjtarget_X360[12] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[12] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[12]) { tape.vjtarget_DS4[12] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[12] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_13), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_14:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[13]) { tape.vjtarget_X360[13] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[13] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[13]) { tape.vjtarget_DS4[13] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[13] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_14), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_15:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[14]) { tape.vjtarget_X360[14] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[14] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[14]) { tape.vjtarget_DS4[14] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[14] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_15), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_16:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[15]) { tape.vjtarget_X360[15] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[15] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[15]) { tape.vjtarget_DS4[15] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[15] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_16), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_17:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[16]) { tape.vjtarget_X360[16] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[16] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[16]) { tape.vjtarget_DS4[16] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[16] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_17), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_18:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[17]) { tape.vjtarget_X360[17] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[17] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[17]) { tape.vjtarget_DS4[17] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[17] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_18), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_19:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[18]) { tape.vjtarget_X360[18] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[18] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[18]) { tape.vjtarget_DS4[18] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[18] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_19), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_20:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[19]) { tape.vjtarget_X360[19] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[19] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[19]) { tape.vjtarget_DS4[19] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[19] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_20), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_21:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[20]) { tape.vjtarget_X360[20] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[20] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[20]) { tape.vjtarget_DS4[20] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[20] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_21), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_22:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[21]) { tape.vjtarget_X360[21] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[21] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[21]) { tape.vjtarget_DS4[21] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[21] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_22), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_23:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[22]) { tape.vjtarget_X360[22] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[22] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[22]) { tape.vjtarget_DS4[22] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[22] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_23), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_DS_24:
		{
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				if (tape.DesiredVirtualPad == 1)
				{
					if (tape.target_X360[23]) { tape.vjtarget_X360[23] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_X360); }
					else { tape.dstarget_X360[23] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_X360); }
				}
				else
				{
					if (tape.target_DS4[23]) { tape.vjtarget_DS4[23] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_vjtarget_DS4); }
					else { tape.dstarget_DS4[23] = (byte)SendMessage(GetDlgItem(hWnd, IDC_VIGEM_DS_24), CB_GETCURSEL, 0, 0); tape.Save(tape.Setting_dstarget_DS4); }
				}
				PostMessage(m_hWnd, WM_CHANGE_PAD, 2, 0);
				break;
			}
			}
			break;
		}
		case IDC_VIGEM_INSTALL:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
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
						SendMessage(GetDlgItem(hWnd, IDC_VIGEM_ACTIVE_CHK), BM_SETCHECK, (tape.ViGEmActive) ? BST_CHECKED : BST_UNCHECKED, 0);
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
			}
			break;
		}
		case IDC_VIGEM_STATUS:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
			{
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
	::ShowWindow(m_hDlg, SW_SHOW);
}

void ViGEmDlg::Hide()
{
	::ShowWindow(m_hDlg, SW_HIDE);
}

BOOL ViGEmDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
