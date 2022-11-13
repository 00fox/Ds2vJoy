#pragma once
#include "DestinationButton.h"

struct Point {
	double x, y;
};

class Destination
{
public:
	Destination();
	~Destination();

	void				Init(bool verbose = false);
	BOOL				Open(int DevID, bool verbose = false);
	void				Close();
	BOOL				Active();
	void				Clear();
	void				ClearState();
	void				UpdateState();
	BOOL				Update();
	DestinationButton*	GetButton(DestButtonID);
	DestinationButton*	GetAxis(DestAxisMoveID);
	DestinationButton*	GetEffect(DestAfterEffectID id);

private:
	double				distSum(Point p, Point arr[], int n);
	Point				geometricMedian(Point arr[], int n);

	void				loadAxis(DestButtonID id, long* data, byte axis);
	void				loadTrigger(DestButtonID id, long* data, byte axis);
	void				loadAxisToTrigger(DestButtonID id, long* data, byte axis);
	void				loadAxisInv(DestButtonID id, long* data, byte axis);
	void				loadTriggerInv(DestButtonID id, long* data, byte axis);
	void				loadAxisToTriggerInv(DestButtonID id, long* data, byte axis);
	void				loadRing(DestAxisMoveID id, long* data, long* data2, byte axis);
	void				loadEffet(DestAfterEffectID id, long* data, long* data2);

	int					m_devID = 0;
	DestinationButton	m_buttons[DestButtonID::Destination_Count];
	DestinationButton	m_axis[DestAxisMoveID::AxisMove_Count];
	DestinationButton	m_effect[DestAfterEffectID::AfterEffect_Count];
	JOYSTICK_POSITION_V2 m_iReportDefault;
	JOYSTICK_POSITION_V2 m_iReport;
	byte				Dpad[32] = { 0 };

	bool				firsttime = true;
};
