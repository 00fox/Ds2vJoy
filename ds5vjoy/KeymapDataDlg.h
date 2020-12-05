#pragma once
#include "Keymap.h"

class KeymapDataDlg
{
public:
	KeymapDataDlg();
	~KeymapDataDlg();

	BOOL Open(HWND);
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK InputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	Keymap keymapData;
private:
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _inputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void initdialog();

	HWND m_hWnd;
	HWND m_hDlg;
	WNDPROC m_defaultInputProc;

};

