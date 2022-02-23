#pragma once
#include "Keymap.h"
#include "Findwindow.h"

class KeymapDataDlg
{
public:
	enum ModifiedKeymap {
		Mofified_ButtonID,
		Mofified_WndRestore,
		Mofified_WndMaximize,
		Mofified_WndShow,
		Mofified_vk,
		Mofified_NaturalTyping,
		Mofified_usePostmessage,
		Mofified_useActivating,
		Mofified_ExtendedKey,
		Mofified_Scancode,
		Mofified_findWindow,
		Mofified_count
	};

	KeymapDataDlg();
	~KeymapDataDlg();

	void				Init(HINSTANCE hInst, HWND hWnd);
	void				Open(HWND parent, int mode);
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

	HWND				m_hDlg = NULL;
	int					m_mode = 0;

	int					dlgPage = 0;
	bool				alreadydone = false;
	bool				Modified[Mofified_count] = { 0 };

	Keymap				keymapData;
	Findwindow			fw;

private:
	#define WM_RESET_FINDWINDOW WM_USER + 1

	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);

	HWND				m_hWnd = NULL;
	HWND				m_parent = NULL;
	HWND				m_hList = NULL;
	HWND				m_hEdit = NULL;
	HMENU				m_hMenu = NULL;

	WNDPROC				m_defaultInputProc = nullptr;
	WNDPROC				m_defaultInputProc2 = nullptr;
	WNDPROC				m_defaultListProc = nullptr;

	int					m_editIdx = 0;
	int					m_editCol = 0;
	bool				m_filter_iwv = false;
	bool				m_flag_cancel = false;

	bool				firsttime = false;
	bool				canprint = false;
};

	extern KeymapDataDlg kDDlg;
