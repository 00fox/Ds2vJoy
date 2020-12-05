#include "stdafx.h"
#include "resource.h"
#include "FindwindowDlg.h"


FindwindowDlg::FindwindowDlg()
{
}


FindwindowDlg::~FindwindowDlg()
{
}

BOOL FindwindowDlg::Open(HWND hWnd)
{
	HINSTANCE h = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	m_hMenu = LoadMenu(h, MAKEINTRESOURCE(IDR_MENU_MAPPING));
	m_hWnd = hWnd;
	switch (DialogBoxParam(h, L"IDD_FINDWINDOW", hWnd, (DLGPROC)Proc, (LPARAM)this))
	{
	case IDOK: {
		return TRUE;
		break;
	}
	}
	return FALSE;
}



INT_PTR FindwindowDlg::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FindwindowDlg *dlg;
	if (uMsg == WM_INITDIALOG) {
		SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);
		dlg = (FindwindowDlg *)lParam;
	}
	else {
		dlg = (FindwindowDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (dlg) {
		return dlg->_proc(hWnd, uMsg, wParam, lParam);
	}
	else {
		return NULL;
	}
}
INT_PTR FindwindowDlg::_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		m_hDlg = hWnd;
		initdialog();
		break;
	case WM_NOTIFY: {
		switch (((LPNMHDR)lParam)->idFrom) {
		case IDC_FIND_LIST:
			switch (((LPNMLISTVIEW)lParam)->hdr.code) {
			case NM_DBLCLK:{
				if (m_hEdit == NULL) {
					LVHITTESTINFO ht;
					GetCursorPos(&ht.pt);
					ScreenToClient(m_hList, &ht.pt);
					if (-1 != ListView_SubItemHitTest(m_hList, &ht)) {
						RECT rc;
						ListView_GetSubItemRect(m_hList, ht.iItem, ht.iSubItem, LVIR_LABEL, &rc);
						m_hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD |WS_VISIBLE | ES_WANTRETURN, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, m_hList, 0, GetModuleHandle(NULL), NULL);
						SetWindowLongPtr(m_hEdit, GWLP_USERDATA, (LONG_PTR)this);
						m_defaultInputProc = (WNDPROC)SetWindowLongPtr(m_hEdit, GWLP_WNDPROC, (LONG_PTR)InputProc);
						m_editIdx = ht.iItem;
						m_editCol = ht.iSubItem;
						auto buf = findwindow.Get(m_editIdx, m_editCol);
						SetWindowText(m_hEdit, buf.c_str());
						HFONT hf = (HFONT)SendMessage(m_hList, WM_GETFONT, NULL, NULL);
						SendMessage(m_hEdit, WM_SETFONT,(WPARAM) hf, 0);
						m_flag_cancel = false;
						SetFocus(m_hEdit);
					}
				}
				break;
			}
			default:
				return FALSE;
			}
		default:
			return FALSE;
		}
		break;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: {
			return EndDialog(hWnd, IDOK);
		}
		case IDCANCEL:
			return EndDialog(hWnd, IDCANCEL);

		case IDC_WINDOWLIST:
			switch (HIWORD(wParam)) {
			case CBN_CLOSEUP: {
				LRESULT idx = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				if (idx != CB_ERR) {
					HWND hWin = (HWND)SendMessage((HWND)lParam, CB_GETITEMDATA, idx, 0);
					if (hWin != (HWND)CB_ERR && hWin != NULL) {
						int iItem = ListView_GetItemCount(m_hList);
						auto classname = Findwindow::GetClass(hWin);
						LVITEM item = { 0 };
						item.mask = LVIF_TEXT | LVIF_PARAM;
						item.iItem = iItem;
						item.pszText = const_cast<LPWSTR>(classname.c_str());
						ListView_InsertItem(m_hList, &item);

						auto titlename = Findwindow::GetText(hWin);
						ListView_SetItemText(m_hList, iItem, 1, const_cast<LPWSTR>(titlename.c_str()));

						int idx=0;
						HWND hwnd = findwindow.Find();
						while (idx == 0) {
							HWND child = NULL;

							while ((child = FindWindowEx(hwnd, child, classname.empty() ? NULL : classname.c_str(), titlename.empty() ? NULL : titlename.c_str())) != hWin) {
								idx++;
								if (child == NULL) {
									idx = -1;
									break;
								}
							}
							if (idx == -1 && !titlename.empty()){
								idx = 0;
								titlename.clear();
							}
							else
								break;
						}
						WCHAR findIdx[10] = L"";
						wsprintf(findIdx, L"%d", idx);
						ListView_SetItemText(m_hList, iItem, 2, findIdx);

						findwindow.Set(-1,0, classname);
						findwindow.Set(-1,1, titlename);
						findwindow.Set(-1,2,findIdx);
					}
				}
				break;
			}
			case CBN_DROPDOWN:
				SendMessage((HWND)lParam, CB_RESETCONTENT, 0, 0);
				{
					HWND hwnd = findwindow.Find();
					if (hwnd != NULL || findwindow.Size()==0) {
						HWND child = NULL;
						int count = 0;
						std::wstring buf;
						while ((child = FindWindowEx(hwnd, child, NULL, NULL)) != NULL) {
							if (!m_filter_iwv || IsWindowVisible(child)) {
								count++;
								buf.clear();
								buf.append(Findwindow::GetClass(child));
								buf.append(L", ");
								buf.append(Findwindow::GetText(child));
								LRESULT idx = SendMessage((HWND)lParam, CB_ADDSTRING, 0, (LPARAM)buf.c_str());
								if (idx != CB_ERR && idx != CB_ERRSPACE) {
									SendMessage((HWND)lParam, CB_SETITEMDATA, idx, (LPARAM)child);
								}
							}
						}
						if (count == 0) {
							WCHAR buf[100];
							wsprintf(buf, L"HWND:%08x", hwnd);
							SendMessage((HWND)lParam, CB_ADDSTRING, 0, (LPARAM)buf);
						}
					}
					else if (hwnd == NULL) {
						SendMessage((HWND)lParam, CB_ADDSTRING, 0, (LPARAM)L"Failed FindWindow");
					}
				}
				break;
			}


			break;



		case IDC_CLEAR:
		{
			int idx = ListView_GetItemCount(m_hList);
			while (--idx >= 0) {
				ListView_DeleteItem(m_hList, idx);
			}
			findwindow.Clear();
			break;
		}
		case IDC_DELETE:
		{
			int idx = ListView_GetItemCount(m_hList);
			if (idx > 0) {
				ListView_DeleteItem(m_hList, --idx);
				findwindow.Pop();
			}
			break;
		}
		case IDC_IS_W_VISIBLE:
			m_filter_iwv = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
			break;

		}

	default:
		return FALSE;
	}
	return TRUE;
}
INT_PTR FindwindowDlg::InputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FindwindowDlg *dlg = (FindwindowDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_inputProc(hWnd, uMsg, wParam, lParam);
	return 0;

}
INT_PTR FindwindowDlg::_inputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_GETDLGCODE:
		return DLGC_WANTALLKEYS;
	case WM_KEYDOWN:
		switch (wParam ) {
		case VK_ESCAPE:
			m_flag_cancel = true;
			DestroyWindow(hWnd);
			return TRUE;
		case VK_RETURN:
		{
			m_flag_cancel = false;
			DestroyWindow(hWnd);
			return TRUE;
		}
		}
		break;
	case WM_KILLFOCUS:
		if (!m_flag_cancel) {
			auto buf = Findwindow::GetText(hWnd);
			findwindow.Set(m_editIdx, m_editCol, std::move(buf));
			buf = findwindow.Get(m_editIdx, m_editCol);
			ListView_SetItemText(m_hList,m_editIdx,m_editCol, const_cast<WCHAR*>(buf.c_str()));
		}
		DestroyWindow(hWnd);
		m_hEdit = NULL;
		break;
	}
	return CallWindowProc(m_defaultInputProc, hWnd, uMsg, wParam, lParam);
}


INT_PTR FindwindowDlg::ListProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FindwindowDlg *dlg = (FindwindowDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (dlg)
		return dlg->_listProc(hWnd, uMsg, wParam, lParam);
	return 0;

}
INT_PTR FindwindowDlg::_listProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_MOUSEWHEEL:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONDBLCLK:
		if (m_hEdit != NULL)
			SendMessage(m_hEdit, WM_KILLFOCUS, 0, 0);
		break;
	}
	return CallWindowProc(m_defaultListProc, hWnd, uMsg, wParam, lParam);
}
void FindwindowDlg::initdialog()
{

	m_hList = GetDlgItem(m_hDlg, IDC_FIND_LIST);
	SetWindowLongPtr(m_hList, GWLP_USERDATA, (LONG_PTR)this);
	m_defaultListProc = (WNDPROC)SetWindowLongPtr(m_hList, GWLP_WNDPROC, (LONG_PTR)ListProc);

	DWORD dwStyle = ListView_GetExtendedListViewStyle(m_hList);
	dwStyle |= LVS_EX_FULLROWSELECT ;
	ListView_SetExtendedListViewStyle(m_hList, dwStyle);
	LVCOLUMN col;

	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	col.pszText = L"Class";
	ListView_InsertColumn(m_hList, 0, &col);
	col.pszText = L"Title";
	col.cx = 200;
	ListView_InsertColumn(m_hList, 1, &col);
	col.pszText = L"Idx";
	col.cx = 100;
	ListView_InsertColumn(m_hList, 2, &col);

	m_hEdit = NULL;

	SendMessage(GetDlgItem(m_hDlg, IDC_IS_W_VISIBLE), BM_SETCHECK, BST_CHECKED, 0);
	m_filter_iwv = true;
	int length = findwindow.Size();

	LVITEM item = { 0 };
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iSubItem = 0;
	item.lParam = (LPARAM)0;
	for (int i = 0; i < length; i++) {
		auto findClass = findwindow.Get(i, 0);
		auto findTitle = findwindow.Get(i, 1);
		auto findIdx = findwindow.Get(i, 2);
		item.iItem = ListView_GetItemCount(m_hList);
		item.pszText = const_cast<WCHAR*>(findClass.c_str());
		ListView_InsertItem(m_hList, &item);
		ListView_SetItemText(m_hList, item.iItem, 1, const_cast<WCHAR*>(findTitle.c_str()));
		ListView_SetItemText(m_hList, item.iItem, 2, const_cast<WCHAR*>(findIdx.c_str()));
	}
}

