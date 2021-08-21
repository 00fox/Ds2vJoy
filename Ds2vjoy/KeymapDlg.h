#pragma once
#include "Keymap.h"

class KeymapDlg
{
public:
	KeymapDlg();
	~KeymapDlg();

	void Init(HINSTANCE, HWND);
	void addKeymapDlgBack();
	void editKeymapDlgBack(int idx);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void redrawMenu(int ntabs);
	void load();
	void save();
	void addKeymapDlg();
	void editKeymapDlg();
	void deleteKeymapDlg();
	void duplicateKeymapDlg();
	int insertKeymap(int idx, Keymap* km);
	void BeginDrag(int idx);
	void DragMove(int x, int y);
	void EndDrag(int x, int y);
	void setInsertMark(int idx);

	HWND m_hWnd;
	HWND m_hDlg;
	HWND m_hList;
	HMENU m_hMenu;

	int m_TabsID[4];
	bool m_active;
	bool m_flag_drag;
	int m_insrtpos;
};

extern KeymapDlg kDlg;
