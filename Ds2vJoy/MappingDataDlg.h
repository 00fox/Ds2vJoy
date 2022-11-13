#pragma once
#include "Mapping.h"

class MappingDataDlg
{
public:
	enum ModifiedMapping : byte
	{
		Mofified_Ifmouse,
		Mofified_Force,
		Mofified_Short,
		Mofified_Double,
		Mofified_Long,
		Mofified_Led,
		Mofified_Macro,
		Mofified_Pause,
		Mofified_Transitivity,
		Mofified_Toggle,
		Mofified_Target1,
		Mofified_Target2,
		Mofified_Target3,
		Mofified_Target4,
		Mofified_Target5,
		Mofified_dsID1,
		Mofified_dsID2,
		Mofified_dsID3,
		Mofified_dsID4,
		Mofified_dsID5,
		Mofified_OrXorNot1,
		Mofified_OrXorNot2,
		Mofified_OrXorNot3,
		Mofified_OrXorNot4,
		Mofified_dsDisable1,
		Mofified_dsDisable2,
		Mofified_dsDisable3,
		Mofified_dsDisable4,
		Mofified_dsDisable5,
		Mofified_ActionType1,
		Mofified_ActionType2,
		Mofified_ActionType3,
		Mofified_ActionType4,
		Mofified_ActionType5,
		Mofified_ActionType6,
		Mofified_ActionType7,
		Mofified_ActionType8,
		Mofified_vjID1,
		Mofified_vjID2,
		Mofified_vjID3,
		Mofified_vjID4,
		Mofified_vjID5,
		Mofified_vjID6,
		Mofified_vjID7,
		Mofified_vjID8,
		Mofified_Overcontrol1,
		Mofified_Overcontrol2,
		Mofified_Overcontrol3,
		Mofified_Overcontrol4,
		Mofified_Overcontrol5,
		Mofified_Overcontrol6,
		Mofified_Overcontrol7,
		Mofified_Overcontrol8,
		Mofified_Switch1,
		Mofified_Switch2,
		Mofified_Switch3,
		Mofified_Switch4,
		Mofified_Switch5,
		Mofified_Switch6,
		Mofified_Switch7,
		Mofified_Switch8,
		Mofified_OnRelease1,
		Mofified_OnRelease2,
		Mofified_OnRelease3,
		Mofified_OnRelease4,
		Mofified_OnRelease5,
		Mofified_OnRelease6,
		Mofified_OnRelease7,
		Mofified_OnRelease8,
		Mofified_NoRelease1,
		Mofified_NoRelease2,
		Mofified_NoRelease3,
		Mofified_NoRelease4,
		Mofified_NoRelease5,
		Mofified_NoRelease6,
		Mofified_NoRelease7,
		Mofified_NoRelease8,
		Mofified_NlRelease1,
		Mofified_NlRelease2,
		Mofified_NlRelease3,
		Mofified_NlRelease4,
		Mofified_NlRelease5,
		Mofified_NlRelease6,
		Mofified_NlRelease7,
		Mofified_NlRelease8,
		Mofified_vjDisable1,
		Mofified_vjDisable2,
		Mofified_vjDisable3,
		Mofified_vjDisable4,
		Mofified_vjDisable5,
		Mofified_vjDisable6,
		Mofified_vjDisable7,
		Mofified_vjDisable8,
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
		ModifiedMapping_Count
	};

	MappingDataDlg();
	~MappingDataDlg();

	void				Init();
	void				Open(HWND parent, int mode, int tab);
	void				Show(HWND hWnd = NULL);
	void				Hide(HWND hWnd = NULL);
	BOOL				MoveWindow(int, int, int, int, BOOL);
	void				SetTransparency(bool transparencyon);
	void				ShowNoRelease();

	HWND				m_hDlg = NULL;

	bool				m_isClonedList = false;
	int					m_mode = 0;

	Mapping				mappingData = { };
	bool				Modified[ModifiedMapping_Count] = { false };

	int					docked = 0;		//0: No, 1: Right, 2: Center, 3: Left
	int					docked_last = 0;
	bool				movable = true;
	int					m_y = 0;

private:
	static	INT_PTR CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			INT_PTR CALLBACK _proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void				_InitDialog(HWND hWnd);

	HWND				m_parent = NULL;
	HWND				m_lists[14] = { NULL };

	POINT				p = { (0, 0) };
	int					m_x = 0;
	int					m_z = 0;
	int					m_t = 0;

	bool				firsttime = false;
	unsigned char		m_Tab = 0;
	bool				grid = false;
	bool				canprint = false;
	bool				danger = false;
	bool				capturehasbeendone = false;
	unsigned char		whohasfocus = 0;
	bool				m_moveLock = false;
	bool				m_drawLock = false;
	bool				m_rightClickOk = false;

	byte				state[8] = { 0 };
	std::vector<unsigned int>	mouseoverCB = { };

	HBRUSH				hbrush_z01 = NULL;
	HBRUSH				hbrush_z02 = NULL;
	HBRUSH				hbrush_z03 = NULL;
	HBRUSH				hbrush_z04 = NULL;
	HBRUSH				hbrush_z05 = NULL;
	HBRUSH				hbrush_z06 = NULL;
	HBRUSH				hbrush_z07 = NULL;
	HBRUSH				hbrush_z08 = NULL;
	HBRUSH				hbrush_z09 = NULL;
	HBRUSH				hbrush_z10 = NULL;
	HBRUSH				hbrush_z11 = NULL;
	HBRUSH				hbrush_z12 = NULL;
	HBRUSH				hbrush_z13 = NULL;
	HBRUSH				hbrush_z14 = NULL;
	HBRUSH				hbrush_z15 = NULL;
	HBRUSH				hbrush_z16 = NULL;
	HBRUSH				hbrush_z17 = NULL;
	HBRUSH				hbrush_z18 = NULL;
	HBRUSH				hbrush_z19 = NULL;
	HBRUSH				hbrush_z20 = NULL;
	HBRUSH				hbrush_z21 = NULL;
	HBRUSH				hbrush_z22 = NULL;

	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now() - std::chrono::milliseconds(4000);
};

	extern MappingDataDlg mDDlg;
