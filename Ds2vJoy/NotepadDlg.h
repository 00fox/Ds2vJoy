#pragma once
#include <deque>

class NotepadDlg
{
public:
	NotepadDlg();
	~NotepadDlg();

	void				Init(HINSTANCE, HWND);
	void				Scroll(bool scrollUp = false, bool page = false);
	void				Save();
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

	bool				m_pause = false;
	short				m_back = -1;
	short				m_ink = -1;
	bool				m_colorrand = false;

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);

	HWND				m_hWnd = NULL;
	HWND				m_hDlg = NULL;
	HWND				m_hEdit = NULL;
	
	HANDLE				m_fonthandle = NULL;

	bool				m_error = false;
	std::deque<wchar_t*>queue = { 0 };
	std::mutex			m_mutex = { };
	bool				m_load_dll = false;
	int					m_count = 0;
};
