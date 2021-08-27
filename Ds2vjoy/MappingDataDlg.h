#pragma once
#include "Mapping.h"

class MappingDataDlg
{
public:
	enum ModifiedMapping {
		Mofified_dsID1,
		Mofified_dsID2,
		Mofified_dsID3,
		Mofified_dsID4,
		Mofified_dsID5,
		Mofified_vjID1,
		Mofified_vjID2,
		Mofified_vjID3,
		Mofified_vjID4,
		Mofified_vjID5,
		Mofified_vjID6,
		Mofified_vjID7,
		Mofified_vjID8,
		Mofified_vjID9,
		Mofified_vjID10,
		Mofified_vjID11,
		Mofified_vjID12,
		Mofified_vjID13,
		Mofified_Target1,
		Mofified_Target2,
		Mofified_Target3,
		Mofified_Target4,
		Mofified_Target5,
		Mofified_Disable1,
		Mofified_Disable2,
		Mofified_Disable3,
		Mofified_Disable4,
		Mofified_Disable5,
		Mofified_Disable6,
		Mofified_Disable7,
		Mofified_Disable8,
		Mofified_Disable9,
		Mofified_Disable10,
		Mofified_Disable11,
		Mofified_Disable12,
		Mofified_Disable13,
		Mofified_OrXorNot1,
		Mofified_OrXorNot2,
		Mofified_OrXorNot3,
		Mofified_OrXorNot4,
		Mofified_Ifmouse,
		Mofified_Force,
		Mofified_Led,
		Mofified_Short,
		Mofified_Double,
		Mofified_Long,
		Mofified_Macro,
		Mofified_Pause,
		Mofified_Toggle,
		Mofified_OnRelease1,
		Mofified_OnRelease2,
		Mofified_OnRelease3,
		Mofified_OnRelease4,
		Mofified_OnRelease5,
		Mofified_OnRelease6,
		Mofified_OnRelease7,
		Mofified_OnRelease8,
		Mofified_Start1,
		Mofified_Start2,
		Mofified_Start3,
		Mofified_Start4,
		Mofified_Start5,
		Mofified_Start6,
		Mofified_Start7,
		Mofified_Start8,
		Mofified_Stop1,
		Mofified_Stop2,
		Mofified_Stop3,
		Mofified_Stop4,
		Mofified_Stop5,
		Mofified_Stop6,
		Mofified_Stop7,
		Mofified_Stop8,
		Mofified_MouseAction1,
		Mofified_MouseAction2,
		Mofified_MouseAction3,
		Mofified_MouseAction4,
		Mofified_Mouse1,
		Mofified_Mouse2,
		Mofified_Mouse3,
		Mofified_Mouse4,
		Mofified_Mouse5,
		Mofified_Mouse6,
		Mofified_Mouse7,
		Mofified_Grid1,
		Mofified_Grid2,
		Mofified_Grid3,
		Mofified_Grid4,
		Mofified_Grid5,
		Mofified_Grid6,
		Mofified_count
	};

	MappingDataDlg();
	~MappingDataDlg();

	void Init(HINSTANCE hInst, HWND hWnd);
	void Open(HWND parent, int mode);
	void Show();
	void Hide();
	BOOL MoveWindow(int, int, int, int, BOOL);

	int docked;		//0: No, 1: Right, 2: Center, 3: Left
	int docked_last;
	bool movable = true;
	int m_y;

	Mapping mappingData;
	bool Modified[Mofified_count];

	HWND m_hDlg;
	bool m_isClonedList;
	int m_mode;

private:
	static INT_PTR CALLBACK Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	HWND m_parent;

	bool firsttime;
	bool canprint;
};

extern MappingDataDlg mDDlg;
