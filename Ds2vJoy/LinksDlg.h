#pragma once

class LinksDlg
{
public:
	LinksDlg();
	~LinksDlg();

	void Init(HINSTANCE, HWND);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HWND m_hDlg;

	bool firsttime;
};

extern LinksDlg iDlg;
