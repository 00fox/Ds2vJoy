#pragma once
#include "Keymap.h"

class KeymapDlg
{
public:
	KeymapDlg();
	~KeymapDlg();

	void				Init(HINSTANCE, HWND);
	void				addKeymapDlgBack();
	void				editKeymapDlgBack();
	void				editKeymapDlgBackMulti();
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				redrawMenu(int ntabs);
	void				load();
	void				save();
	void				addKeymapDlg();
	void				addSeparator();
	void				editKeymapDlg();
	void				deleteKeymapDlg();
	void				duplicateKeymapDlg();
	int					insertKeymap(int idx, Keymap* km);
	void				BeginDrag(int idx);
	void				DragMove(int x, int y);
	void				EndDrag(int x, int y);
	void				setInsertMark(int idx);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HWND				m_hWnd = NULL;
	HWND				m_hDlg = NULL;
	HWND				m_hList = NULL;
	HMENU				m_hMenu = NULL;

	int					m_TabsID[5] = { 0 };
	bool				m_active = false;
	bool				m_flag_drag = false;
	int					m_insrtpos = 0;
	int					lastidx = 0;
	std::vector<int>	lastidxs = { };
	unsigned char		lasttab = 0;
	bool				tabSortingMethod = false;
};

	extern KeymapDlg	kDlg;
