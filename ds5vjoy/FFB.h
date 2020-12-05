#pragma once
#include "ffb/effect.h"
class FFB
{
	std::map<int,CEffect> m_effects;
	void CALLBACK _callback(FFB_DATA *data);
	void _ctrl(FFB_DATA*);
	void _operation(FFB_DATA*);
	bool m_bActuator;
	bool m_bStoped;
	bool m_bPaused;
	double m_dwPausedTime;
	BYTE m_Gain;
	double getTime();
	LARGE_INTEGER m_gt_start;
	double m_gt_ms;

	std::mutex m_mutex;
	BYTE m_lastLeft,m_lastRight;
public:
	static void CALLBACK callback(PVOID , PVOID );

	bool Calc(BYTE *left, BYTE *right);
	FFB();
	~FFB();
};

