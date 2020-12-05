#pragma once

//ログ
void LogPrintf(const wchar_t *format, ...);

class LogDlg
{
	HWND m_hWnd;
	HWND m_hEdit;
	int m_count;
public:
	LogDlg();
	~LogDlg();

	void Init(HINSTANCE, HWND);
	void Update();
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);
};
