#pragma once
#include "Mapping.h"

class MappingDlg
{
public:
	MappingDlg();
	~MappingDlg();

	void Init(HINSTANCE hInst, HWND hWnd);
	void Init2(HINSTANCE hInst, HWND hWnd);
	bool isCloned();
	void setCloned(bool cloned);
	void SetTab(int tab);
	int GetTab();
	void addMappingDlgBack();
	void editMappingDlgBack();
	void editMappingDlgBackMulti();
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

	bool moving;

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void redrawMenu(int ntabs, bool menu = false);
	void redrawListReminder();
	void load();
	void save();
	void addMappingDlg();
	void addSeparator();
	void editMappingDlg();
	void deleteMappingDlg();
	void duplicateMappingDlg();
	void moveMappingDlg(int tab);
	int insertMapping(int idx, Mapping* m);
	void BeginDrag(int idx);
	void DragMove(int x, int y);
	void EndDrag(int x, int y);
	void setInsertMark(int idx);

	HWND m_hWnd;
	HWND m_hDlg;
	HWND m_hList;
	HMENU m_hMenu;
	HMENU m_hMenu2;

	unsigned char m_Tab;
	int m_TabsID[14];
	int m_ReminderId[32];
	int m_Randcolor[32];
	bool m_active;
	bool m_flag_drag;
	int m_insrtpos;
	bool m_isClonedList;
	bool m_isCloned;
	int lastidx;
	std::vector<int> lastidxs;
	unsigned char lasttab;
	bool tabSortingMethod;		//false natural single column ordering, true table below:
	//| column | 1      | 2     | 3     | 4     | 5     | 7     | 8    |
	//|:------:|:------ |:----- |:----- |:----- |:----- |:----- |:---- |
	//|   1    | Enable | ds1   | dsor  | dsnot | vj    | Led   | Tags |
	//|   2    | Enable | dsor  | dsnot | vj    | Led   | ds1   | Tags |
	//|   3    | Enable | dsnot | vj    | Led   | ds1   | dsor  | Tags |
	//|   4    | Enable | vj    | Led   | ds1   | dsor  | dsnot | Tags |
	//|   5    | Enable | Tags  | ds1   | dsor  | dsnot | vj    | Led  |
};

extern MappingDlg mDlg;
