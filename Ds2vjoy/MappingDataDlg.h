#pragma once
#include "Mapping.h"

class MappingDataDlg
{
public:
	MappingDataDlg();
	~MappingDataDlg();

	void Init(HINSTANCE hInst, HWND hWnd);
	void Open(HWND parent, int idx = 0);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

	int docked;		//0: No, 1: Right, 2: Center, 3: Left
	int docked_last;
	bool movable = true;
	int m_y;

	Mapping mappingData;

	HWND m_hDlg;
	int m_idx;

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HWND m_parent;

	bool firsttime;
};

extern MappingDataDlg mDDlg;
