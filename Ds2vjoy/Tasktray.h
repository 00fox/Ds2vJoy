#pragma once

class Tasktray
{
	struct MenuPosition {
		UINT flags;
		INT x;
		INT y;
	};

public:
	Tasktray();
	~Tasktray();

	void Init(HINSTANCE hInst, HWND hWnd);
	void CreateMenu();
	void SwapMenuitem(int item = 0);
	void Show();
	void Hide();
	void Tip(WCHAR* buf);
	void Message(WPARAM wPAram, LPARAM lParam);
	UINT GetTaskBarLocation();
	UINT GetTaskBarLocation(RECT* rectangle);
	void GetMenuPosition(struct MenuPosition* test);

private:
	HWND m_hWnd;
	bool m_flag;
	HMENU m_menu;

	NOTIFYICONDATA m_nid = { 0 };
	UINT MenuOffset = 3;
};

extern Tasktray tasktray;
