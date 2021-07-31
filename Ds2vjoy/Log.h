#pragma once
#include <deque>

//Log function
void echo();
void echo(const char* format, ...);
void echo(const wchar_t* format, ...);

class LogDlg
{
public:
	LogDlg();
	~LogDlg();

	void Init(HINSTANCE, HWND, bool loadvJoy = true);
	void echo(wchar_t* buffer);
	void Update();
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

private:
	wchar_t* LogGet();

	HWND m_hWnd;
	HWND m_hDlg;

	std::deque<wchar_t*> queue;
	std::mutex m_mutex;
	bool m_loadvJoy;
	int m_count;
};

extern LogDlg _log;