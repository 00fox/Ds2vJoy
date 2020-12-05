#include "stdafx.h"
#include "Stopwatch.h"


void Stopwatch::_close()
{
	if (m_logBuf) {
		free(m_logBuf);
		m_logBuf = 0;
		m_logLength = 0;
	}
}

Stopwatch::Stopwatch():m_logBuf(0),m_logIndex(0),m_logCount(0),m_logLength(0), m_lasttime(0)
{

}

void Stopwatch::Reset(DWORD bufLen)
{

	if (bufLen>0) {
		_close();
		m_logBuf = (double*)malloc(sizeof(double)*bufLen);
		m_logLength = bufLen;
	}
	m_logIndex = 0;
	m_logCount = 0;
	m_lasttime = 0;
	if(m_logBuf)
		memset(m_logBuf, 0, sizeof(double)*m_logLength);
	m_f_ms = 0;
}

bool Stopwatch::Lap(double *_nowtime)
{
	if (!m_logBuf)
		return false;
	if (m_f_ms == 0) {
		LARGE_INTEGER f;
		QueryPerformanceFrequency(&f);
		m_f_ms = double(f.QuadPart) / 1000.0;
		QueryPerformanceCounter(&m_start);
	}
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	double now = (double)(t.QuadPart - m_start.QuadPart ) / m_f_ms;
	if (_nowtime != NULL)
		*_nowtime = now;
	if (m_lasttime) {
		m_logBuf[m_logIndex] = now - m_lasttime;
		++m_logIndex;
		if(m_logIndex >= m_logLength){
			++m_logCount;
			m_logIndex = 0;
			m_lasttime = now;
			return true;
		}
	}
	m_lasttime = now;
	return false;
}

double Stopwatch::GetAvg()
{
	double avg = 0;
	int max = m_logCount ? m_logLength : m_logIndex;
	for (int i = 0; i < max; i++) {
		avg += m_logBuf[i];
	}
	return max ? avg / max : 0;
}


Stopwatch::~Stopwatch()
{
	_close();
}
