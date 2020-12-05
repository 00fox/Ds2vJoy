#pragma once
#include "Findwindow.h"
class FindwindowDlg
{
public:
	FindwindowDlg();
	~FindwindowDlg();
	BOOL Open(HWND);
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK InputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK ListProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	Findwindow findwindow;
private:
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _inputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _listProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void initdialog();
	HWND m_hWnd;
	HWND m_hDlg;
	HWND m_hList;
	HMENU m_hMenu;

	HWND m_hEdit;
	WNDPROC m_defaultInputProc;
	WNDPROC m_defaultListProc;

	int m_editIdx;
	int m_editCol;

	bool m_filter_iwv;
	bool m_flag_cancel;
	void AddList(const std::wstring findClass, const std::wstring findTitle, const int findIdx);
};

