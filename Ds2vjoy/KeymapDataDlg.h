#pragma once
#include "Keymap.h"
#include "Findwindow.h"

class KeymapDataDlg
{
public:
	KeymapDataDlg();
	~KeymapDataDlg();

	void Init(HINSTANCE hInst, HWND hWnd);
	void Open(HWND parent, int idx = 0);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

	int dlgPage = 0;
	Keymap keymapData;
	Findwindow fw;
	bool alreadydone;

	HWND m_hDlg;
	int m_idx;

private:
	#define WM_RESET_FINDWINDOW WM_USER + 1

	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HWND m_parent;
	HWND m_hList;
	HMENU m_hMenu;
	HWND m_hEdit;

	WNDPROC m_defaultInputProc;
	WNDPROC m_defaultInputProc2;
	WNDPROC m_defaultListProc;

	int m_editIdx;
	int m_editCol;
	bool m_filter_iwv;
	bool m_flag_cancel;

	bool firsttime;
};

extern KeymapDataDlg kDDlg;
