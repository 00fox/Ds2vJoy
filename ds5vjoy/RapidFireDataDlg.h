#pragma once
#include "RapidFire.h"

class RapidFireDataDlg
{
public:
	RapidFireDataDlg();
	~RapidFireDataDlg();
	BOOL Open(HWND);
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	RapidFire rapidFireData;
private:
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void initdialog();
	HWND m_hWnd;
	HWND m_hDlg;

};

