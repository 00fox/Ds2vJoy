#pragma once

class Tasktray
{
	NOTIFYICONDATA m_nid = { 0 };
	HWND m_hWnd;
	bool m_flag;
public:
	Tasktray();
	void Init(HINSTANCE hInst, HWND hWnd);
	void Show();
	void Hide();
	void Tip(WCHAR*buf);
	void Message(WPARAM wPAram, LPARAM lParam);
	~Tasktray();
};

