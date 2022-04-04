#pragma once

class Tasktray
{
	struct MenuPosition
	{
		unsigned int flags;
		int x;
		int y;
	};

public:
	enum LedActionID
	{
		Tasktray_Item_MappingPaused,
		Tasktray_Item_RapidFirePaused,
		Tasktray_Item_vJoyPaused,
		Tasktray_Item_ViGEmPaused,
		Tasktray_Item_KeymapPaused,
		Tasktray_Item_GuardianPaused,
	};

	Tasktray();
	~Tasktray();

	void				Init(HINSTANCE hInst, HWND hWnd);
	void				CreateMenu();
	void				SwapMenuitem(int item = 0);
	void				Show();
	void				Hide();
	void				Tip(WCHAR* buf);
	void				Message(WPARAM wPAram, LPARAM lParam);
	UINT				GetTaskBarLocation();
	UINT				GetTaskBarLocation(RECT* rectangle);
	void				GetMenuPosition(struct MenuPosition* test);

private:
	HWND				m_hWnd = NULL;
	HMENU				m_menu = NULL;

	NOTIFYICONDATA		m_nid = { 0 };
	unsigned int		MenuOffset = 3;

	bool				m_flag = false;
};

	extern Tasktray		tasktray;
