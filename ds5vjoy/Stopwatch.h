#pragma once
class Stopwatch
{
	double *m_logBuf, m_lasttime;
	int m_logIndex;
	DWORD m_logCount;
	int m_logLength;
	void _close();

	LARGE_INTEGER m_start;
	double m_f_ms;

public:
	Stopwatch();
	void Reset(DWORD bufLen = 0);
	bool Lap(double *_nowtime=0);
	double GetAvg();
	~Stopwatch();
};

