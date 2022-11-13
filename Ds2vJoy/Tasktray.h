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
	enum TasktrayItem : unsigned char
	{
		TasktrayItem_MappingPaused,
		TasktrayItem_RapidFirePaused,
		TasktrayItem_vJoyPaused,
		TasktrayItem_XOutputPaused,
		TasktrayItem_KeymapPaused,
		TasktrayItem_GuardianPaused,
	};

	Tasktray();
	~Tasktray();

	void				Init();
	void				CreateMenu();
	void				SwapMenuitem(int item = 0);
	void				Show();
	void				Hide();
	void				Tip(WCHAR* buf);
	void				Message(WPARAM wPAram, LPARAM lParam);
	UINT				GetTaskBarLocation();
	UINT				GetTaskBarLocation(RECT* rectangle);
	void				GetMenuPosition(struct MenuPosition* test);

	NOTIFYICONDATA		m_nid = { 0 };

private:
	HMENU				m_menu = NULL;

	unsigned int		MenuOffset = 3;

	bool				m_flag = false;
};

	extern Tasktray		tasktray;
