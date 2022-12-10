#pragma once
#include "Mapping.h"

class MappingDlg
{
public:
	MappingDlg();
	~MappingDlg();

	void				Init(bool isClone = false);
	void				SetTab(int tab, bool activate = true);
	void				redrawTabs(int tab, bool actualize = true);
	void				PageUp();
	void				PageDown();
	void				PageHome();
	void				PageEnd();
	void				addMappingDlgBack();
	void				editMappingDlgBack();
	void				editMappingDlgBackMulti();
	void				Show();
	void				Show2();
	void				Hide();
	void				Hide2();
	BOOL				MoveWindow(int, int, int, int, BOOL);
	BOOL				MoveWindow2(int, int, int, int, BOOL);
	void				SetTransparency(bool transparencyon);

	unsigned char		m_Tab = 0;
	bool				moving = false;
	bool				m_isCloned = false;

private:
	#define WM_REDRAW_TABS WM_USER + 1

	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);
	void				_ShowWindow(HWND hWnd);
	void				redrawMenu(int ntabs, bool isclonemenu = false);
	void				redrawListReminder();
	void				load();
	void				save();
	void				addMappingDlg();
	void				addSeparator();
	void				editMappingDlg();
	void				stateMappingDlg();
	void				deleteMappingDlg();
	void				duplicateMappingDlg();
	void				moveMappingDlg(int tab);
	void				addNoticeDlg();
	void				addNoticeDlgBack();
	int					insertMapping(int idx, Mapping* m);
	void				BeginDrag(int idx);
	void				DragMove(int x, int y);
	void				EndDrag(int x, int y);
	void				setInsertMark(int idx);

	HWND				m_hDlg = NULL;
	HWND				m_hDlg2 = NULL;
	HWND				m_hTab = NULL;
	HWND				m_hList = NULL;
	HMENU				m_hMenu = NULL;
	HMENU				m_hMenu2 = NULL;
	HMENU				hMenu_Tabs = NULL;
	HMENU				hMenu_Tabs_2 = NULL;

	std::chrono::system_clock::time_point m_timeOfLastDarkMenuCall = std::chrono::system_clock::now();
	unsigned char		tabrightclick;
	int					m_TabsID[17] = { 0 };
	int					m_ReminderId[32] = { 0 };
	int					m_Randcolor[32] = { 0 };
	bool				m_active = false;
	bool				m_flag_drag = false;
	int					m_insrtpos = 0;
	bool				m_isClonedList = false;
	int					lastidx = 0;
	std::vector<int>	lastidxs = { };
	//false natural single column ordering, true table below:
	//
	//| column | 1      | 2     | 3     | 4     | 5     | 7     | 8    |
	//|:------:|:------ |:----- |:----- |:----- |:----- |:----- |:---- |
	//|   1    | Enable | ds1   | dsor  | dsnot | vj    | Led   | Tags |
	//|   2    | Enable | dsor  | dsnot | vj    | Led   | ds1   | Tags |
	//|   3    | Enable | dsnot | vj    | Led   | ds1   | dsor  | Tags |
	//|   4    | Enable | vj    | Led   | ds1   | dsor  | dsnot | Tags |
	//|   5    | Enable | Tags  | ds1   | dsor  | dsnot | vj    | Led  |
	WCHAR				NoticeDlg[MAX_PATH] = { 0 };
};

	extern MappingDlg	mDlg;
