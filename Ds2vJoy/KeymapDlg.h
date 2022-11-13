#pragma once
#include "Keymap.h"

class KeymapDlg
{
public:
	KeymapDlg();
	~KeymapDlg();

	void				Init();
	void				PageUp();
	void				PageDown();
	void				PageHome();
	void				PageEnd();
	void				addKeymapDlgBack();
	void				editKeymapDlgBack();
	void				editKeymapDlgBackMulti();
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static	LRESULT CALLBACK ListSubclassProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIDSubClass, DWORD_PTR RefData);
			LRESULT CALLBACK _listSubclassProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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
	void				Sort(int column);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HWND				m_hDlg = NULL;
	HWND				m_hList = NULL;
	HMENU				m_hMenu = NULL;

	unsigned char		m_actualColumn = 0;
	unsigned char		m_lastColumn = 0;
	int					m_columnOrder[4];
	unsigned char		m_indexOfSettings = 1;

	int					m_TabsID[5] = { 0 };
	bool				m_active = false;
	bool				m_sorting = false;
	bool				m_flag_drag = false;
	int					m_insrtpos = 0;
	int					lastidx = 0;
	std::vector<int>	lastidxs = { };
};

	extern KeymapDlg	kDlg;
