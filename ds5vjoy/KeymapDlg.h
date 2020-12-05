#pragma once
#include "Keymap.h"

class KeymapDlg
{
	HWND m_hWnd;
	HWND m_hList;
	HWND m_hDlg;
	HMENU m_hMenu;

	bool m_change;
	bool m_active;
	INT_PTR CALLBACK _proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	void load();
	void save();
	bool insertKeymapItem(int idx, Keymap*);
	bool addKeymapDlg();
	bool editKeymapDlg();
	bool deleteKeymap();

public:
	KeymapDlg();
	~KeymapDlg();

	void Init(HINSTANCE, HWND);
	static INT_PTR CALLBACK Proc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);
};
