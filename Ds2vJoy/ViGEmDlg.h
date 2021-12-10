#pragma once

class ViGEmDlg
{
public:
	HWND m_hDlg;
	ViGEmDlg();
	~ViGEmDlg();

	void Init(HINSTANCE, HWND);
	void Init2();
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

private:

	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
};

extern ViGEmDlg vDlg;
