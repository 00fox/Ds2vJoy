#pragma once
//https://www.codeproject.com/Articles/28870/Better-Way-to-Sleep-Control-Execution-and-Limit-CP

const int DEFAULT_MAX_PERCENTAGE = 20;

/*
CPULimiter:
This class helps to limit the cpu usage/consumption by a thread involving
some kind of repetitive/polling kind of operation in a loop.
The limit can be set by a user through a function of this class.
*/

class CPULimiter
{
	//This integer stores last total system time.
	//total system time is sum of time spent by system 
	//in kernel, user and idle mode
	LARGE_INTEGER m_lastTotalSystemTime;

	//This integer stores last total time spent by this 
	//thread in	kernel space and user space
	LARGE_INTEGER m_lastThreadUsageTime;

	//Variable used to store maximum thread cpu percentage
	//relative to system total time.
	int m_ratio;
public:

	//Constructors
	CPULimiter();
	//Contructor with maximum thread cpu usage percentage
	CPULimiter(int p_ratio);

	//****************Main function.****************** 
	//It evaluates cpu consumption by this thread since 
	//last call to this function, uptill now. 
	//Internally, it calculates if the thread has exceeds 
	//the maximum cpu usage percentage specified.
	//if yes, it makes the thread to sleep for a calculated 
	//time period, to average the total usage to the limit specified.
	//Returns TRUE Successful, else FALSE
	
	BOOL CalculateAndSleep();

	//Inline setter function
	inline void SetRatio(int p_ratio){m_ratio = p_ratio;}
};
