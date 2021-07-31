#pragma once

class Stopwatch
{
public:
	Stopwatch();
	~Stopwatch();

	void Reset(DWORD bufLen = 0);
	BOOL Lap(double* _nowtime = 0);
	double GetAvg();

private:
	void _close();

	LARGE_INTEGER m_start;
	double* m_logBuf, m_lasttime;
	double m_f_ms;
	int m_logIndex;
	int m_logLength;
	DWORD m_logCount;
};
