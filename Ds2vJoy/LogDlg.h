#pragma once
#include <deque>

//Log function
	void				echo();
	void				echo(const char* format, ...);
	void				echo(const wchar_t* format, ...);

class LogDlg
{
public:
	LogDlg();
	~LogDlg();

	void				echo(wchar_t* buffer);
	void				Init();
	void				SetShowTime(bool showtime = true);
	void				PageUp();
	void				PageDown();
	void				PageHome();
	void				PageEnd();
	void				Update();
	void				Show();
	void				Hide();
	BOOL				MoveWindow(int, int, int, int, BOOL);

	HWND				m_hDlg = NULL;

	bool				m_pause = false;
	short				m_back = -1;
	short				m_ink = -1;
	bool				m_colorrand = false;

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);
	void				ColorDemo(HWND hWnd, HWND hEdit);
	void				ColorRand(HWND hWnd, HWND hEdit);
	wchar_t*			LogGet();

	HWND				m_hEdit = NULL;

	std::deque<wchar_t*>queue = { 0 };
	std::mutex			m_mutex = { };
	bool				m_showTime = true;
	int					m_count = 0;
	bool				m_hasfocus = false;
};

	extern bool			log_closing;
	extern LogDlg		_log;