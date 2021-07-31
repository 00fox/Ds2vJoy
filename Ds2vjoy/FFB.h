#pragma once
#include "CEffect.h"

class FFB
{
public:
	FFB();
	~FFB();

	BOOL Calc(BYTE* left, BYTE* right);

	static void CALLBACK callback(PVOID, PVOID);

private:
	void CALLBACK _callback(FFB_DATA* data);

	void _ctrl(FFB_DATA*);
	void _operation(FFB_DATA*);
	double getTime();

	std::map<int, CEffect> m_effects;
	bool m_bActuator;
	bool m_bStoped;
	bool m_bPaused;
	BYTE m_Gain;
	LARGE_INTEGER m_gt_start;
	double m_gt_ms;
	double m_dwPausedTime;
	std::mutex m_mutex;
	BYTE m_lastLeft, m_lastRight;
};
