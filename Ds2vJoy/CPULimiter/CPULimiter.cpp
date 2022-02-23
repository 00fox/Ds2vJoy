#include "StdAfx.h"
#include "CPULimiter.h"

//constructors
CPULimiter::CPULimiter(int p_ratio)
:m_ratio(p_ratio)
{
	::ZeroMemory( &m_lastTotalSystemTime, sizeof(LARGE_INTEGER));
	::ZeroMemory( &m_lastThreadUsageTime, sizeof(LARGE_INTEGER));
}

CPULimiter::CPULimiter()
{
	::ZeroMemory( &m_lastTotalSystemTime, sizeof(LARGE_INTEGER));
	::ZeroMemory( &m_lastThreadUsageTime, sizeof(LARGE_INTEGER));
	m_ratio = DEFAULT_MAX_PERCENTAGE;
}

//**********************Main Function ***************************

BOOL CPULimiter::CalculateAndSleep()
{
	//Declare variables;
	FILETIME sysidle, kerusage, userusage, threadkern, threaduser, threadcreat, threadexit; 
	LARGE_INTEGER tmpvar, thissystime, thisthreadtime; 

	//Get system kernel, user and idle times
	if(!::GetSystemTimes(&sysidle, &kerusage, &userusage))
		return FALSE;

	//Get Thread user and kernel times
	if(!::GetThreadTimes(GetCurrentThread(), &threadcreat, &threadexit, &threadkern, &threaduser))
		return FALSE;

	//Calculates total system times
	//This is sum of time used by system in kernel, user and idle mode.
	tmpvar.LowPart = sysidle.dwLowDateTime;
	tmpvar.HighPart = sysidle.dwHighDateTime;
	thissystime.QuadPart = tmpvar.QuadPart;

	tmpvar.LowPart = kerusage.dwLowDateTime;
	tmpvar.HighPart = kerusage.dwHighDateTime;
	thissystime.QuadPart = thissystime.QuadPart + tmpvar.QuadPart;

	tmpvar.LowPart = userusage.dwLowDateTime;
	tmpvar.HighPart = userusage.dwHighDateTime;
	thissystime.QuadPart = thissystime.QuadPart + tmpvar.QuadPart;

	//Calculates time spent by this thread in user and kernel mode.
	tmpvar.LowPart = threadkern.dwLowDateTime;
	tmpvar.HighPart = threadkern.dwHighDateTime;
	thisthreadtime.QuadPart = tmpvar.QuadPart;

	tmpvar.LowPart = threaduser.dwLowDateTime;
	tmpvar.HighPart = threaduser.dwHighDateTime;
	thisthreadtime.QuadPart = thisthreadtime.QuadPart + tmpvar.QuadPart;

	//Check if this is first time this function is called
	//if yes, escape rest after copying current system and thread time
	//for further use
	//Also check if the ratio of differences between current and previous times
	//exceeds the specified ratio.
	
	if( thisthreadtime.QuadPart != 0
		&& (((thisthreadtime.QuadPart - m_lastThreadUsageTime.QuadPart)*100) 
			- ((thissystime.QuadPart - m_lastTotalSystemTime.QuadPart)*m_ratio)) > 0)
	{
		//Calculate the time interval to sleep for averaging the extra cpu usage 
		//by this thread.

		LARGE_INTEGER timetosleepin100ns;
		timetosleepin100ns.QuadPart = (((thisthreadtime.QuadPart-m_lastThreadUsageTime.QuadPart)*100)/m_ratio) 
									- (thissystime.QuadPart - m_lastTotalSystemTime.QuadPart);
		
		//check if time is less then a milli second, if yes, keep it for next time.
		if((timetosleepin100ns.QuadPart/10000) <= 0)
			return FALSE;
		
		//Time to Sleep :)
		Sleep((unsigned long)timetosleepin100ns.QuadPart/10000);
	}  

	//Copy usage time values for next time calculations.
	m_lastTotalSystemTime.QuadPart = thissystime.QuadPart;
	m_lastThreadUsageTime.QuadPart = thisthreadtime.QuadPart;
	return TRUE;
}
