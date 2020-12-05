#pragma once
#include "RapidFire.h"

class RapidFireDlg
{

	HWND m_hWnd;
	HWND m_hDlg;
	HWND m_hList;
	HMENU m_hMenu;

	bool m_change;
	bool m_active;
	INT_PTR CALLBACK _proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	void load();
	void save();
	void addRapidFireDlg();
	void editRapidFireDlg();
	void deleteRapidFire();
	void insertRapidFireData(int idx, RapidFire*_rf);
public:
	RapidFireDlg();
	~RapidFireDlg();

	void Init(HINSTANCE hInst, HWND hWnd);
	static INT_PTR CALLBACK Proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

};

