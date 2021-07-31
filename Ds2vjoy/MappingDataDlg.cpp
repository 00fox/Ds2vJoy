#include "stdafx.h"
#include "MappingDataDlg.h"
#include "Ds2vJoy.h"

MappingDataDlg::MappingDataDlg()
{
}

MappingDataDlg::~MappingDataDlg()
{
}

void MappingDataDlg::Init(HINSTANCE hInst, HWND hWnd)
{
	docked = 1;
	docked_last = 1;
	m_idx = -2;
	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_MAPPING_ADD), hWnd, (DLGPROC)Proc, (LPARAM)this);
	m_hWnd = hWnd;
	LONG lStyle = GetWindowLong(m_hDlg, GWL_STYLE);
//	lStyle |= WS_THICKFRAME;
	lStyle = lStyle & ~WS_CAPTION;
	SetWindowLong(m_hDlg, GWL_STYLE, lStyle);
	Hide();
}

void MappingDataDlg::Open(HWND parent, int idx)
{
	m_idx = idx;
	firsttime = false;
//	ShowWindow(parent, SW_HIDE);
	ShowWindow(m_hDlg, SW_SHOW);
	PostMessage(m_hWnd, WM_SIZE, -1, -2);
}

INT_PTR MappingDataDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MappingDataDlg* dlg;
	if (uMsg == WM_INITDIALOG)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (MappingDataDlg*)lParam;
	}
	else
		dlg = (MappingDataDlg*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	else
		return NULL;
}

INT_PTR MappingDataDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT p;
	static int m_x;
	static int m_y;
	static int m_z;
	static int m_t;
	switch (uMsg)
	{
	case WM_NCCALCSIZE:
		if (wParam)
		{
//			NCCALCSIZE_PARAMS FAR* lpncsp = (NCCALCSIZE_PARAMS FAR*)lParam;
//			lpncsp->rgrc[0].top -= 6;
//			return FALSE;
			return TRUE;
		}
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
		SetTextColor(hdcStatic, RGB(62, 20, 102));
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
			DeleteObject(brush);
			EndPaint(hWnd, &ps);
		}
		return FALSE;
	}
	case WM_LBUTTONDOWN:
	{
		SetCapture(m_hDlg);
		GetCursorPos(&p);
		RECT rect;
		GetWindowRect(hWnd, &rect);
		m_x = rect.left - p.x;
		m_y = rect.top - p.y;
		m_z = rect.right - p.x;
		m_t = rect.bottom - p.y;
		break;
	}
	case WM_MOUSEMOVE:
		if (movable)
		{
			RECT win;
			GetWindowRect(m_hWnd, &win);
			if ((GetKeyState(VK_LBUTTON) & 0x800) == 0)
			{
				if (docked == 2)
					::MoveWindow(m_hDlg, win.left + 9, win.top + 31, 474, 287, FALSE);
				ReleaseCapture();
				break;
			}
			GetCursorPos(&p);
			RECT rect;
			GetWindowRect(hWnd, &rect);

			if (abs(win.right - m_x - 6 - p.x) < 40)															//docked right
			{
				docked = 1;
				docked_last = 1;
				::MoveWindow(m_hDlg, win.right - 6, m_y + p.y, 474, 287, FALSE);
			}
			else if ((abs(win.left - m_x + 9 - p.x) < 40) && (p.y > win.top + 20) && (p.y < win.bottom - 20))	//docked center
			{
				docked = 2;
				docked_last = 2;
				::MoveWindow(m_hDlg, win.left + 9, m_y + p.y, 474, 287, FALSE);
			}
			else if (abs(win.left - m_z + 6 - p.x) < 40)														//docked left
			{
				docked = 3;
				docked_last = 3;
				::MoveWindow(m_hDlg, win.left + 6 - 474, m_y + p.y, 474, 287, FALSE);
			}
			else																								//no docked
			{
				docked = 0;
				docked_last = 0;
				::MoveWindow(m_hDlg, m_x + p.x, m_y + p.y, 474, 287, FALSE);
			}
		}
		else
			SetFocus(m_hWnd);
		break;
	case WM_SHOWWINDOW:
		if (wParam == TRUE)
		{
			if (!firsttime)
			{
				ShowWindow(GetDlgItem(hWnd, IDC_STATIC), SW_SHOW);
				ShowWindow(GetDlgItem(hWnd, IDC_STATIC_HELP), SW_HIDE);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DS_1, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DS_2, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DS_3, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DS_4, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_DS_5, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_RESETCONTENT, 0, 0);
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_RESETCONTENT, 0, 0);
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					if (!(WPARAM)mappingData.Target[0])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_1, CB_ADDSTRING, 0, (LPARAM)str);
					if (!(WPARAM)mappingData.Target[1])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_2, CB_ADDSTRING, 0, (LPARAM)str);
					if (!(WPARAM)mappingData.Target[2])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_3, CB_ADDSTRING, 0, (LPARAM)str);
					if (!(WPARAM)mappingData.Target[3])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_4, CB_ADDSTRING, 0, (LPARAM)str);
					if (!(WPARAM)mappingData.Target[4])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_5, CB_ADDSTRING, 0, (LPARAM)str);
				}
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					if ((WPARAM)mappingData.Target[0])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_1, CB_ADDSTRING, 0, (LPARAM)str);
					if ((WPARAM)mappingData.Target[1])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_2, CB_ADDSTRING, 0, (LPARAM)str);
					if ((WPARAM)mappingData.Target[2])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_3, CB_ADDSTRING, 0, (LPARAM)str);
					if ((WPARAM)mappingData.Target[3])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_4, CB_ADDSTRING, 0, (LPARAM)str);
					if ((WPARAM)mappingData.Target[4])
						SendDlgItemMessage(hWnd, IDC_MAPPING_DS_5, CB_ADDSTRING, 0, (LPARAM)str);
					if ((WPARAM)mappingData.MouseAction[0] == 0)
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_ADDSTRING, 0, (LPARAM)str);
					if ((WPARAM)mappingData.MouseAction[1] == 0)
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_ADDSTRING, 0, (LPARAM)str);
					if ((WPARAM)mappingData.MouseAction[2] == 0)
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_ADDSTRING, 0, (LPARAM)str);
					if ((WPARAM)mappingData.MouseAction[3] == 0)
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_ADDSTRING, 0, (LPARAM)str);
				}
				if ((WPARAM)mappingData.MouseAction[0])
				{
					for (int i = 0; i < MouseActionID::mouse_Count; i++)
					{
						WCHAR* str = Mapping::String((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_ADDSTRING, 0, (LPARAM)str);
					}
				}
				if ((WPARAM)mappingData.MouseAction[1])
				{
					for (int i = 0; i < MouseActionID::mouse_Count; i++)
					{
						WCHAR* str = Mapping::String((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_ADDSTRING, 0, (LPARAM)str);
					}
				}
				if ((WPARAM)mappingData.MouseAction[2])
				{
					for (int i = 0; i < MouseActionID::mouse_Count; i++)
					{
						WCHAR* str = Mapping::String((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_ADDSTRING, 0, (LPARAM)str);
					}
				}
				if ((WPARAM)mappingData.MouseAction[3])
				{
					for (int i = 0; i < MouseActionID::mouse_Count; i++)
					{
						WCHAR* str = Mapping::String((MouseActionID)i);
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_ADDSTRING, 0, (LPARAM)str);
					}
				}

				firsttime = true;
			}

			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_1, CB_SETCURSEL, ((WPARAM)mappingData.Target[0]) ? (WPARAM)mappingData.vjID[0] : (WPARAM)mappingData.dsID[0], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_2, CB_SETCURSEL, ((WPARAM)mappingData.Target[1]) ? (WPARAM)mappingData.vjID[1] : (WPARAM)mappingData.dsID[1], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_3, CB_SETCURSEL, ((WPARAM)mappingData.Target[2]) ? (WPARAM)mappingData.vjID[2] : (WPARAM)mappingData.dsID[2], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_4, CB_SETCURSEL, ((WPARAM)mappingData.Target[3]) ? (WPARAM)mappingData.vjID[3] : (WPARAM)mappingData.dsID[3], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_5, CB_SETCURSEL, ((WPARAM)mappingData.Target[4]) ? (WPARAM)mappingData.vjID[4] : (WPARAM)mappingData.dsID[4], 0);
			if ((WPARAM)mappingData.MouseAction[0])
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_SETCURSEL, (WPARAM)mappingData.MouseAction[0], 0);
			else
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_SETCURSEL, (WPARAM)mappingData.vjID[5], 0);

			if ((WPARAM)mappingData.MouseAction[1])
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_SETCURSEL, (WPARAM)mappingData.MouseAction[1], 0);
			else
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_SETCURSEL, (WPARAM)mappingData.vjID[6], 0);

			if ((WPARAM)mappingData.MouseAction[2])
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_SETCURSEL, (WPARAM)mappingData.MouseAction[2], 0);
			else
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_SETCURSEL, (WPARAM)mappingData.vjID[7], 0);

			if ((WPARAM)mappingData.MouseAction[3])
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_SETCURSEL, (WPARAM)mappingData.MouseAction[3], 0);
			else
				SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_SETCURSEL, (WPARAM)mappingData.vjID[8], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_5, CB_SETCURSEL, (WPARAM)mappingData.vjID[9], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_6, CB_SETCURSEL, (WPARAM)mappingData.vjID[10], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_7, CB_SETCURSEL, (WPARAM)mappingData.vjID[11], 0);
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_8, CB_SETCURSEL, (WPARAM)mappingData.vjID[12], 0);
			CheckDlgButton(hWnd, IDC_MAPPING_TARGET_1, (WPARAM)mappingData.Target[0]);
			CheckDlgButton(hWnd, IDC_MAPPING_TARGET_2, (WPARAM)mappingData.Target[1]);
			CheckDlgButton(hWnd, IDC_MAPPING_TARGET_3, (WPARAM)mappingData.Target[2]);
			CheckDlgButton(hWnd, IDC_MAPPING_TARGET_4, (WPARAM)mappingData.Target[3]);
			CheckDlgButton(hWnd, IDC_MAPPING_TARGET_5, (WPARAM)mappingData.Target[4]);
			CheckDlgButton(hWnd, IDC_MAPPING_DS_1_DISABLE, (WPARAM)mappingData.Disbale[0]);
			CheckDlgButton(hWnd, IDC_MAPPING_DS_2_DISABLE, (WPARAM)mappingData.Disbale[1]);
			CheckDlgButton(hWnd, IDC_MAPPING_DS_3_DISABLE, (WPARAM)mappingData.Disbale[2]);
			CheckDlgButton(hWnd, IDC_MAPPING_DS_4_DISABLE, (WPARAM)mappingData.Disbale[3]);
			CheckDlgButton(hWnd, IDC_MAPPING_DS_5_DISABLE, (WPARAM)mappingData.Disbale[4]);
			if ((WPARAM)mappingData.MouseAction[0])
			{
				CheckDlgButton(hWnd, IDC_MAPPING_VJOY_1_DISABLE, BST_UNCHECKED);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_VJOY_1_DISABLE), false);
			}
			else
			{
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_VJOY_1_DISABLE), true);
				CheckDlgButton(hWnd, IDC_MAPPING_VJOY_1_DISABLE, (WPARAM)mappingData.Disbale[5]);
			}
			if ((WPARAM)mappingData.MouseAction[1])
			{
				CheckDlgButton(hWnd, IDC_MAPPING_VJOY_2_DISABLE, BST_UNCHECKED);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_VJOY_2_DISABLE), false);
			}
			else
			{
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_VJOY_2_DISABLE), true);
				CheckDlgButton(hWnd, IDC_MAPPING_VJOY_2_DISABLE, (WPARAM)mappingData.Disbale[6]);
			}
			if ((WPARAM)mappingData.MouseAction[2])
			{
				CheckDlgButton(hWnd, IDC_MAPPING_VJOY_3_DISABLE, BST_UNCHECKED);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_VJOY_3_DISABLE), false);
			}
			else
			{
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_VJOY_3_DISABLE), true);
				CheckDlgButton(hWnd, IDC_MAPPING_VJOY_3_DISABLE, (WPARAM)mappingData.Disbale[7]);
			}
			if ((WPARAM)mappingData.MouseAction[3])
			{
				CheckDlgButton(hWnd, IDC_MAPPING_VJOY_4_DISABLE, BST_UNCHECKED);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_VJOY_4_DISABLE), false);
			}
			else
			{
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_VJOY_4_DISABLE), true);
				CheckDlgButton(hWnd, IDC_MAPPING_VJOY_4_DISABLE, (WPARAM)mappingData.Disbale[8]);
			}
			CheckDlgButton(hWnd, IDC_MAPPING_VJOY_5_DISABLE, (WPARAM)mappingData.Disbale[9]);
			CheckDlgButton(hWnd, IDC_MAPPING_VJOY_6_DISABLE, (WPARAM)mappingData.Disbale[10]);
			CheckDlgButton(hWnd, IDC_MAPPING_VJOY_7_DISABLE, (WPARAM)mappingData.Disbale[11]);
			CheckDlgButton(hWnd, IDC_MAPPING_VJOY_8_DISABLE, (WPARAM)mappingData.Disbale[12]);
			CheckDlgButton(hWnd, IDC_MAPPING_DS_2_OR, (WPARAM)mappingData.OrXorNot[0]);
			CheckDlgButton(hWnd, IDC_MAPPING_DS_3_OR, (WPARAM)mappingData.OrXorNot[1]);
			CheckDlgButton(hWnd, IDC_MAPPING_DS_4_NOT, (WPARAM)mappingData.OrXorNot[2]);
			CheckDlgButton(hWnd, IDC_MAPPING_DS_5_NOT, (WPARAM)mappingData.OrXorNot[3]);
			CheckDlgButton(hWnd, IDC_MAPPING_IF_MOUSE_ACTIVE, (WPARAM)mappingData.Ifmouse);
			CheckDlgButton(hWnd, IDC_MAPPING_FORCE, (WPARAM)mappingData.Force);
			SendDlgItemMessage(hWnd, IDC_MAPPING_LED, CB_SETCURSEL, (WPARAM)mappingData.Led, 0);
			CheckDlgButton(hWnd, IDC_MAPPING_SHORT, (WPARAM)mappingData.Short);
			CheckDlgButton(hWnd, IDC_MAPPING_DOUBLE, (WPARAM)mappingData.Double);
			CheckDlgButton(hWnd, IDC_MAPPING_LONG, (WPARAM)mappingData.Long);
			CheckDlgButton(hWnd, IDC_MAPPING_MACRO, (WPARAM)mappingData.Macro);
			CheckDlgButton(hWnd, IDC_MAPPING_TOGGLE, (WPARAM)mappingData.Toggle);
			CheckDlgButton(hWnd, IDC_MAPPING_ONRELEASE_1, (WPARAM)mappingData.OnRelease[0]);
			CheckDlgButton(hWnd, IDC_MAPPING_ONRELEASE_2, (WPARAM)mappingData.OnRelease[1]);
			CheckDlgButton(hWnd, IDC_MAPPING_ONRELEASE_3, (WPARAM)mappingData.OnRelease[2]);
			CheckDlgButton(hWnd, IDC_MAPPING_ONRELEASE_4, (WPARAM)mappingData.OnRelease[3]);
			CheckDlgButton(hWnd, IDC_MAPPING_ONRELEASE_5, (WPARAM)mappingData.OnRelease[4]);
			CheckDlgButton(hWnd, IDC_MAPPING_ONRELEASE_6, (WPARAM)mappingData.OnRelease[5]);
			CheckDlgButton(hWnd, IDC_MAPPING_ONRELEASE_7, (WPARAM)mappingData.OnRelease[6]);
			CheckDlgButton(hWnd, IDC_MAPPING_ONRELEASE_8, (WPARAM)mappingData.OnRelease[7]);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_ACTION_1, (WPARAM)mappingData.MouseAction[0]);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_ACTION_2, (WPARAM)mappingData.MouseAction[1]);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_ACTION_3, (WPARAM)mappingData.MouseAction[2]);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_ACTION_4, (WPARAM)mappingData.MouseAction[3]);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_01, ((WPARAM)mappingData.Mouse[0] == 1) ? (((WPARAM)mappingData.Mouse[3]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_02, ((WPARAM)mappingData.Mouse[0] == 2) ? (((WPARAM)mappingData.Mouse[3]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_03, ((WPARAM)mappingData.Mouse[0] == 3) ? (((WPARAM)mappingData.Mouse[3]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_04, ((WPARAM)mappingData.Mouse[0] == 4) ? (((WPARAM)mappingData.Mouse[3]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_05, ((WPARAM)mappingData.Mouse[0] == 5) ? (((WPARAM)mappingData.Mouse[3]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_11, ((WPARAM)mappingData.Mouse[1] == 1) ? (((WPARAM)mappingData.Mouse[4]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_12, ((WPARAM)mappingData.Mouse[1] == 2) ? (((WPARAM)mappingData.Mouse[4]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_13, ((WPARAM)mappingData.Mouse[1] == 3) ? (((WPARAM)mappingData.Mouse[4]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_14, ((WPARAM)mappingData.Mouse[1] == 4) ? (((WPARAM)mappingData.Mouse[4]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_15, ((WPARAM)mappingData.Mouse[1] == 5) ? (((WPARAM)mappingData.Mouse[4]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_21, ((WPARAM)mappingData.Mouse[2] == 1) ? (((WPARAM)mappingData.Mouse[5]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_22, ((WPARAM)mappingData.Mouse[2] == 2) ? (((WPARAM)mappingData.Mouse[5]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_23, ((WPARAM)mappingData.Mouse[2] == 3) ? (((WPARAM)mappingData.Mouse[5]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_24, ((WPARAM)mappingData.Mouse[2] == 4) ? (((WPARAM)mappingData.Mouse[5]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_25, ((WPARAM)mappingData.Mouse[2] == 5) ? (((WPARAM)mappingData.Mouse[5]) ? 2 : 1) : 0);
			CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_GRID_DEFAULT, (WPARAM)mappingData.Mouse[6]);
			TCHAR buf[20];
			swprintf_s(buf, TEXT("%d"), mappingData.Start[0]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_1_START), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Start[1]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_2_START), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Start[2]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_3_START), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Start[3]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_4_START), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Start[4]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_5_START), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Start[5]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_6_START), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Start[6]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_7_START), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Start[7]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_8_START), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Stop[0]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_1_STOP), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Stop[1]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_2_STOP), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Stop[2]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_3_STOP), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Stop[3]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_4_STOP), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Stop[4]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_5_STOP), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Stop[5]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_6_STOP), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Stop[6]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_7_STOP), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Stop[7]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_8_STOP), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Grid[0]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_X), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Grid[1]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Grid[2]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_W), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Grid[3]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_H), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Grid[4]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW), buf);
			swprintf_s(buf, TEXT("%d"), mappingData.Grid[5]);
			SetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH), buf);

			if (
				((WPARAM)mappingData.Mouse[0] == 5 && !(WPARAM)mappingData.Mouse[3]) ||
				((WPARAM)mappingData.Mouse[1] == 5 && !(WPARAM)mappingData.Mouse[4]) ||
				((WPARAM)mappingData.Mouse[2] == 5 && !(WPARAM)mappingData.Mouse[5])
				)
			{
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_X), true);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y), true);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_W), true);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_H), true);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW), true);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH), true);
			}
			else
			{
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_X), false);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y), false);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_W), false);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_H), false);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW), false);
				EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH), false);

				for (int i = 0; i < 4; i++)
				{
					if ((WPARAM)mappingData.MouseAction[i] == mappingData.MOVE_TO_XY || (WPARAM)mappingData.MouseAction[i] == mappingData.SAVE_AND_MOVE_TO_XY)
					{
						EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_X), true);
						EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y), true);
					}
					if ((WPARAM)mappingData.MouseAction[i] == mappingData.MOVE_TO_WH || (WPARAM)mappingData.MouseAction[i] == mappingData.SAVE_AND_MOVE_TO_WH)
					{
						EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_W), true);
						EnableWindow(GetDlgItem(hWnd, IDC_MAPPING_GRID_H), true);
					}
				}
			}

			HFONT hFont = CreateFont(12, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_2, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_3, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_4, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_5, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_5, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_6, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_7, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_8, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_LED, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1_START, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2_START, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3_START, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4_START, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_5_START, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_6_START, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_7_START, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_8_START, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1_STOP, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2_STOP, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3_STOP, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4_STOP, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_5_STOP, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_6_STOP, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_7_STOP, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_8_STOP, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_GRID_X, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_GRID_Y, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_GRID_W, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_GRID_H, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_GRID_NW, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hWnd, IDC_MAPPING_GRID_NH, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		}
		break;
	case WM_INITDIALOG:
	{
		SendMessage(GetDlgItem(hWnd, IDC_MAPPING_LED), CB_ADDSTRING, 0, (LPARAM)L"");
		for (int i = 1; i < 6; i++)
			SendDlgItemMessage(hWnd, IDC_MAPPING_LED, CB_ADDSTRING, 0, (LPARAM)std::to_wstring(i).c_str());
		SendMessage(GetDlgItem(hWnd, IDC_MAPPING_LED), CB_ADDSTRING, 0, (LPARAM)L"Battery status");
		for (int i = 0; i < vJoyButtonID::button_Count; i++)
		{
			WCHAR* str = vJoyButton::String((vJoyButtonID)i);
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_5, CB_ADDSTRING, 0, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_6, CB_ADDSTRING, 0, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_7, CB_ADDSTRING, 0, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_8, CB_ADDSTRING, 0, (LPARAM)str);
		}
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			mappingData.Enable = true;
			if (m_idx == -1)
			{
				SendMessage(m_hWnd, WM_ADDMAPPING, m_idx, 1);
				Mapping m;
				mDDlg.mappingData = m;
				Hide();
				Show();
			}
			else
			{
				PostMessage(m_hWnd, WM_ADDMAPPING, m_idx, 1);
				m_idx = -2;
			}
			break;
		}
		case IDCANCEL:
			PostMessage(m_hWnd, WM_ADDMAPPING, 0, 0);
			m_idx = -2;
			break;
		case IDHELP:
			ShowWindow(GetDlgItem(hWnd, IDC_STATIC_HELP), SW_SHOW);
			ShowWindow(GetDlgItem(hWnd, IDC_STATIC), SW_HIDE);
			break;
		case IDC_CLEAR:
		{
			Mapping m;
			mDDlg.mappingData = m;
			Hide();
			Show();
			break;
		}
		case IDC_MAPPING_DS_1:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				if (IsDlgButtonChecked(hWnd, IDC_MAPPING_TARGET_1))
					mappingData.vjID[0] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				else
					mappingData.dsID[0] = (dsButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_MAPPING_DS_2:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				if (IsDlgButtonChecked(hWnd, IDC_MAPPING_TARGET_2))
					mappingData.vjID[1] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				else
					mappingData.dsID[1] = (dsButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_MAPPING_DS_3:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				if (IsDlgButtonChecked(hWnd, IDC_MAPPING_TARGET_3))
					mappingData.vjID[2] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				else
					mappingData.dsID[2] = (dsButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_MAPPING_DS_4:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				if (IsDlgButtonChecked(hWnd, IDC_MAPPING_TARGET_4))
					mappingData.vjID[3] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				else
					mappingData.dsID[3] = (dsButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_MAPPING_DS_5:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				if (IsDlgButtonChecked(hWnd, IDC_MAPPING_TARGET_5))
					mappingData.vjID[4] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				else
					mappingData.dsID[4] = (dsButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_MAPPING_VJOY_1:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				if (IsDlgButtonChecked(hWnd, IDC_MAPPING_MOUSE_ACTION_1))
				{
					mappingData.MouseAction[0] = (MouseActionID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
					if (!mappingData.MouseAction[0])
					{
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < vJoyButtonID::button_Count; i++)
						{
							WCHAR* str = vJoyButton::String((vJoyButtonID)i);
							SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_ADDSTRING, 0, (LPARAM)str);
						}
					}
					Hide();
					Show();
				}
				else
					mappingData.vjID[5] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_MAPPING_VJOY_2:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				if (IsDlgButtonChecked(hWnd, IDC_MAPPING_MOUSE_ACTION_2))
				{
					mappingData.MouseAction[1] = (MouseActionID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
					if (!mappingData.MouseAction[1])
					{
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < vJoyButtonID::button_Count; i++)
						{
							WCHAR* str = vJoyButton::String((vJoyButtonID)i);
							SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_ADDSTRING, 0, (LPARAM)str);
						}
					}
					Hide();
					Show();
				}
				else
					mappingData.vjID[6] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_MAPPING_VJOY_3:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				if (IsDlgButtonChecked(hWnd, IDC_MAPPING_MOUSE_ACTION_3))
				{
					mappingData.MouseAction[2] = (MouseActionID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
					if (!mappingData.MouseAction[2])
					{
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < vJoyButtonID::button_Count; i++)
						{
							WCHAR* str = vJoyButton::String((vJoyButtonID)i);
							SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_ADDSTRING, 0, (LPARAM)str);
						}
					}
					Hide();
					Show();
				}
				else
					mappingData.vjID[7] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_MAPPING_VJOY_4:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				if (IsDlgButtonChecked(hWnd, IDC_MAPPING_MOUSE_ACTION_4))
				{
					mappingData.MouseAction[3] = (MouseActionID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
					if (!mappingData.MouseAction[3])
					{
						SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_RESETCONTENT, 0, 0);
						for (int i = 0; i < vJoyButtonID::button_Count; i++)
						{
							WCHAR* str = vJoyButton::String((vJoyButtonID)i);
							SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_ADDSTRING, 0, (LPARAM)str);
						}
					}
					Hide();
					Show();
				}
				else
					mappingData.vjID[8] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_MAPPING_VJOY_5:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				mappingData.vjID[9] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_MAPPING_VJOY_6:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				mappingData.vjID[10] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_MAPPING_VJOY_7:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				mappingData.vjID[11] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_MAPPING_VJOY_8:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				mappingData.vjID[12] = (vJoyButtonID)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_MAPPING_TARGET_1:
			mappingData.Target[0] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_1, CB_RESETCONTENT, 0, 0);
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.dsID[0] = (dsButtonID)dsButtonID::none;
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_1, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			else
			{
				mappingData.vjID[0] = (vJoyButtonID)vJoyButtonID::none;
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_1, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_TARGET_2:
			mappingData.Target[1] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_2, CB_RESETCONTENT, 0, 0);
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.dsID[1] = (dsButtonID)dsButtonID::none;
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_2, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			else
			{
				mappingData.vjID[1] = (vJoyButtonID)vJoyButtonID::none;
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_2, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_TARGET_3:
			mappingData.Target[2] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_3, CB_RESETCONTENT, 0, 0);
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.dsID[2] = (dsButtonID)dsButtonID::none;
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_3, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			else
			{
				mappingData.vjID[2] = (vJoyButtonID)vJoyButtonID::none;
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_3, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_TARGET_4:
			mappingData.Target[3] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_4, CB_RESETCONTENT, 0, 0);
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.dsID[3] = (dsButtonID)dsButtonID::none;
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_4, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			else
			{
				mappingData.vjID[3] = (vJoyButtonID)vJoyButtonID::none;
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_4, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_TARGET_5:
			mappingData.Target[4] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			SendDlgItemMessage(hWnd, IDC_MAPPING_DS_5, CB_RESETCONTENT, 0, 0);
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.dsID[4] = (dsButtonID)dsButtonID::none;
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_5, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			else
			{
				mappingData.vjID[4] = (vJoyButtonID)vJoyButtonID::none;
				for (int i = 0; i < dsButtonID::button_Count; i++)
				{
					WCHAR* str = dsButton::String((dsButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_DS_5, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_DS_1_DISABLE:
			mappingData.Disbale[0] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_DS_2_DISABLE:
			mappingData.Disbale[1] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_DS_3_DISABLE:
			mappingData.Disbale[2] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_DS_4_DISABLE:
			mappingData.Disbale[3] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_DS_5_DISABLE:
			mappingData.Disbale[4] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_VJOY_1_DISABLE:
			if (IsDlgButtonChecked(hWnd, IDC_MAPPING_MOUSE_ACTION_1))
			{
				mappingData.Disbale[5] = false;
				CheckDlgButton(hWnd, LOWORD(wParam), BST_UNCHECKED);
			}
			else
				mappingData.Disbale[5] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_VJOY_2_DISABLE:
			if (IsDlgButtonChecked(hWnd, IDC_MAPPING_MOUSE_ACTION_2))
			{
				mappingData.Disbale[6] = false;
				CheckDlgButton(hWnd, LOWORD(wParam), BST_UNCHECKED);
			}
			else
				mappingData.Disbale[6] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_VJOY_3_DISABLE:
			if (IsDlgButtonChecked(hWnd, IDC_MAPPING_MOUSE_ACTION_3))
			{
				mappingData.Disbale[7] = false;
				CheckDlgButton(hWnd, LOWORD(wParam), BST_UNCHECKED);
			}
			else
				mappingData.Disbale[7] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_VJOY_4_DISABLE:
			if (IsDlgButtonChecked(hWnd, IDC_MAPPING_MOUSE_ACTION_4))
			{
				mappingData.Disbale[8] = false;
				CheckDlgButton(hWnd, LOWORD(wParam), BST_UNCHECKED);
			}
			else
				mappingData.Disbale[8] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_VJOY_5_DISABLE:
			mappingData.Disbale[9] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_VJOY_6_DISABLE:
			mappingData.Disbale[10] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_VJOY_7_DISABLE:
			mappingData.Disbale[11] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_VJOY_8_DISABLE:
			mappingData.Disbale[12] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_DS_2_OR:
			mappingData.OrXorNot[0] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_DS_3_OR:
			mappingData.OrXorNot[1] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_DS_4_NOT:
			mappingData.OrXorNot[2] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_DS_5_NOT:
			mappingData.OrXorNot[3] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_IF_MOUSE_ACTIVE:
			mappingData.Ifmouse = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_FORCE:
			mappingData.Force = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_LED:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				mappingData.Led = (int)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			break;
		case IDC_MAPPING_SHORT:
			mappingData.Short = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_LONG:
			mappingData.Long = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_DOUBLE:
			mappingData.Double = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_MACRO:
			mappingData.Macro = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_TOGGLE:
			mappingData.Toggle = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_ONRELEASE_1:
			mappingData.OnRelease[0] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_ONRELEASE_2:
			mappingData.OnRelease[1] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_ONRELEASE_3:
			mappingData.OnRelease[2] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_ONRELEASE_4:
			mappingData.OnRelease[3] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_ONRELEASE_5:
			mappingData.OnRelease[4] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_ONRELEASE_6:
			mappingData.OnRelease[5] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_ONRELEASE_7:
			mappingData.OnRelease[6] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_ONRELEASE_8:
			mappingData.OnRelease[7] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_VJOY_1_START:
			WCHAR bufstart1[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_1_START), bufstart1, MAX_PATH);
			mappingData.Start[0] = max(0, min(9999, _wtoi(bufstart1)));
			break;
		case IDC_MAPPING_VJOY_2_START:
			WCHAR bufstart2[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_2_START), bufstart2, MAX_PATH);
			mappingData.Start[1] = max(0, min(9999, _wtoi(bufstart2)));
			break;
		case IDC_MAPPING_VJOY_3_START:
			WCHAR bufstart3[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_3_START), bufstart3, MAX_PATH);
			mappingData.Start[2] = max(0, min(9999, _wtoi(bufstart3)));
			break;
		case IDC_MAPPING_VJOY_4_START:
			WCHAR bufstart4[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_4_START), bufstart4, MAX_PATH);
			mappingData.Start[3] = max(0, min(9999, _wtoi(bufstart4)));
			break;
		case IDC_MAPPING_VJOY_5_START:
			WCHAR bufstart5[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_5_START), bufstart5, MAX_PATH);
			mappingData.Start[4] = max(0, min(9999, _wtoi(bufstart5)));
			break;
		case IDC_MAPPING_VJOY_6_START:
			WCHAR bufstart6[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_6_START), bufstart6, MAX_PATH);
			mappingData.Start[5] = max(0, min(9999, _wtoi(bufstart6)));
			break;
		case IDC_MAPPING_VJOY_7_START:
			WCHAR bufstart7[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_7_START), bufstart7, MAX_PATH);
			mappingData.Start[6] = max(0, min(9999, _wtoi(bufstart7)));
			break;
		case IDC_MAPPING_VJOY_8_START:
			WCHAR bufstart8[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_8_START), bufstart8, MAX_PATH);
			mappingData.Start[7] = max(0, min(9999, _wtoi(bufstart8)));
			break;
		case IDC_MAPPING_VJOY_1_STOP:
			WCHAR bufstop1[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_1_STOP), bufstop1, MAX_PATH);
			mappingData.Stop[0] = max(0, min(9999, _wtoi(bufstop1)));
			break;
		case IDC_MAPPING_VJOY_2_STOP:
			WCHAR bufstop2[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_2_STOP), bufstop2, MAX_PATH);
			mappingData.Stop[1] = max(0, min(9999, _wtoi(bufstop2)));
			break;
		case IDC_MAPPING_VJOY_3_STOP:
			WCHAR bufstop3[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_3_STOP), bufstop3, MAX_PATH);
			mappingData.Stop[2] = max(0, min(9999, _wtoi(bufstop3)));
			break;
		case IDC_MAPPING_VJOY_4_STOP:
			WCHAR bufstop4[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_4_STOP), bufstop4, MAX_PATH);
			mappingData.Stop[3] = max(0, min(9999, _wtoi(bufstop4)));
			break;
		case IDC_MAPPING_VJOY_5_STOP:
			WCHAR bufstop5[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_5_STOP), bufstop5, MAX_PATH);
			mappingData.Stop[4] = max(0, min(9999, _wtoi(bufstop5)));
			break;
		case IDC_MAPPING_VJOY_6_STOP:
			WCHAR bufstop6[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_6_STOP), bufstop6, MAX_PATH);
			mappingData.Stop[5] = max(0, min(9999, _wtoi(bufstop6)));
			break;
		case IDC_MAPPING_VJOY_7_STOP:
			WCHAR bufstop7[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_7_STOP), bufstop7, MAX_PATH);
			mappingData.Stop[6] = max(0, min(9999, _wtoi(bufstop7)));
			break;
		case IDC_MAPPING_VJOY_8_STOP:
			WCHAR bufstop8[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_VJOY_8_STOP), bufstop8, MAX_PATH);
			mappingData.Stop[7] = max(0, min(9999, _wtoi(bufstop8)));
			break;
		case IDC_MAPPING_MOUSE_ACTION_1:
			mappingData.MouseAction[0] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_RESETCONTENT, 0, 0);
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.vjID[5] = (vJoyButtonID)vJoyButtonID::none;
				mappingData.Disbale[5] = false;
				for (int i = 0; i < MouseActionID::mouse_Count; i++)
				{
					WCHAR* str = Mapping::String((MouseActionID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			else
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_1, CB_ADDSTRING, 0, (LPARAM)str);
				}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_ACTION_2:
			mappingData.MouseAction[1] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_RESETCONTENT, 0, 0);
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.vjID[6] = (vJoyButtonID)vJoyButtonID::none;
				mappingData.Disbale[6] = false;
				for (int i = 0; i < MouseActionID::mouse_Count; i++)
				{
					WCHAR* str = Mapping::String((MouseActionID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			else
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_2, CB_ADDSTRING, 0, (LPARAM)str);
				}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_ACTION_3:
			mappingData.MouseAction[2] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_RESETCONTENT, 0, 0);
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.vjID[7] = (vJoyButtonID)vJoyButtonID::none;
				mappingData.Disbale[7] = false;
				for (int i = 0; i < MouseActionID::mouse_Count; i++)
				{
					WCHAR* str = Mapping::String((MouseActionID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			else
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_3, CB_ADDSTRING, 0, (LPARAM)str);
				}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_ACTION_4:
			mappingData.MouseAction[3] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_RESETCONTENT, 0, 0);
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.vjID[8] = (vJoyButtonID)vJoyButtonID::none;
				mappingData.Disbale[8] = false;
				for (int i = 0; i < MouseActionID::mouse_Count; i++)
				{
					WCHAR* str = Mapping::String((MouseActionID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_ADDSTRING, 0, (LPARAM)str);
				}
			}
			else
				for (int i = 0; i < vJoyButtonID::button_Count; i++)
				{
					WCHAR* str = vJoyButton::String((vJoyButtonID)i);
					SendDlgItemMessage(hWnd, IDC_MAPPING_VJOY_4, CB_ADDSTRING, 0, (LPARAM)str);
				}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_01:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[0] = 1;
				mappingData.Mouse[3] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_02, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_03, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_04, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_05, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[0] = 0;
				mappingData.Mouse[3] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_02:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[0] = 2;
				mappingData.Mouse[3] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_01, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_03, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_04, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_05, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[0] = 0;
				mappingData.Mouse[3] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_03:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[0] = 3;
				mappingData.Mouse[3] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_01, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_02, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_04, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_05, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[0] = 0;
				mappingData.Mouse[3] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_04:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[0] = 4;
				mappingData.Mouse[3] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_01, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_02, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_03, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_05, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[0] = 0;
				mappingData.Mouse[3] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_05:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[0] = 5;
				mappingData.Mouse[3] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_01, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_02, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_03, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_04, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[0] = 0;
				mappingData.Mouse[3] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_11:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[1] = 1;
				mappingData.Mouse[4] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_12, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_13, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_14, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_15, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[1] = 0;
				mappingData.Mouse[4] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_12:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[1] = 2;
				mappingData.Mouse[4] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_11, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_13, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_14, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_15, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[1] = 0;
				mappingData.Mouse[4] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_13:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[1] = 3;
				mappingData.Mouse[4] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_11, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_12, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_14, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_15, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[1] = 0;
				mappingData.Mouse[4] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_14:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[1] = 4;
				mappingData.Mouse[4] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_11, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_12, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_13, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_15, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[1] = 0;
				mappingData.Mouse[4] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_15:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[1] = 5;
				mappingData.Mouse[4] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_11, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_12, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_13, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_14, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[1] = 0;
				mappingData.Mouse[4] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_21:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[2] = 1;
				mappingData.Mouse[5] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_22, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_23, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_24, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_25, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[2] = 0;
				mappingData.Mouse[5] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_22:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[2] = 2;
				mappingData.Mouse[5] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_21, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_23, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_24, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_25, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[2] = 0;
				mappingData.Mouse[5] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_23:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[2] = 3;
				mappingData.Mouse[5] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_21, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_22, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_24, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_25, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[2] = 0;
				mappingData.Mouse[5] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_24:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[2] = 4;
				mappingData.Mouse[5] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_21, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_22, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_23, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_25, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[2] = 0;
				mappingData.Mouse[5] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_25:
			if (IsDlgButtonChecked(hWnd, LOWORD(wParam)))
			{
				mappingData.Mouse[2] = 5;
				mappingData.Mouse[5] = (IsDlgButtonChecked(hWnd, LOWORD(wParam)) == 1) ? false : true;
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_21, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_22, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_23, BST_UNCHECKED);
				CheckDlgButton(hWnd, IDC_MAPPING_MOUSE_24, BST_UNCHECKED);
			}
			else
			{
				mappingData.Mouse[2] = 0;
				mappingData.Mouse[5] = false;
			}
			Hide();
			Show();
			break;
		case IDC_MAPPING_MOUSE_GRID_DEFAULT:
			mappingData.Mouse[6] = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			break;
		case IDC_MAPPING_GRID_X:
			WCHAR buf1[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_X), buf1, MAX_PATH);
			mappingData.Grid[0] = max(0, min(9999, _wtoi(buf1)));
			break;
		case IDC_MAPPING_GRID_Y:
			WCHAR buf2[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_Y), buf2, MAX_PATH);
			mappingData.Grid[1] = max(0, min(9999, _wtoi(buf2)));
			break;
		case IDC_MAPPING_GRID_W:
			WCHAR buf3[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_W), buf3, MAX_PATH);
			mappingData.Grid[2] = max(0, min(9999, _wtoi(buf3)));
			break;
		case IDC_MAPPING_GRID_H:
			WCHAR buf4[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_H), buf4, MAX_PATH);
			mappingData.Grid[3] = max(0, min(9999, _wtoi(buf4)));
			break;
		case IDC_MAPPING_GRID_NW:
			WCHAR buf5[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_NW), buf5, MAX_PATH);
			mappingData.Grid[4] = max(0, min(99, _wtoi(buf5)));
			break;
		case IDC_MAPPING_GRID_NH:
			WCHAR buf6[MAX_PATH];
			GetWindowText(GetDlgItem(hWnd, IDC_MAPPING_GRID_NH), buf6, MAX_PATH);
			mappingData.Grid[5] = max(0, min(99, _wtoi(buf6)));
			break;
		}
	default:
		return FALSE;
	}
	return TRUE;
}

void MappingDataDlg::Show()
{
	ShowWindow(m_hDlg, SW_SHOW);
}

void MappingDataDlg::Hide()
{
	ShowWindow(m_hDlg, SW_HIDE);
}

BOOL MappingDataDlg::MoveWindow(int x, int y, int w, int h, BOOL r)
{
	return ::MoveWindow(m_hDlg, x, y, w, h, r);
}
