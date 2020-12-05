#pragma once
#include "Mapping.h"

class MappingDataDlg
{
public:
	MappingDataDlg();
	~MappingDataDlg();
	BOOL Open(HWND);
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	Mapping mappingData;
private:
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void initdialog();
	HWND m_hWnd;
	HWND m_hDlg;

};

