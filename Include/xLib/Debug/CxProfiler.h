/****************************************************************************
* Class name:  CxProfiler
* Description: code profiling
* File name:   CxProfiler.h
* String type: Ansi (tString)
* Compilers:   Visual C++ 2008
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     07.04.2009 16:59:44
*
*****************************************************************************/


#ifndef xLib_Debug_CxProfilerH
#define xLib_Debug_CxProfilerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Log/CxFileLog.h>
#include <xLib/Common/CxDateTime.h>
//---------------------------------------------------------------------------
//TODO: CxProfiler
class CxProfiler : public CxNonCopyable {
	public:
		//Perfomance mode
		enum EMode {
            pmClock,            //std::clock (msec)
		    pmTime,				//xLib::CxDateTime
        #if defined(xOS_WIN)
            pmTickCount,		//::GetTickCount (msec)
            pmPerformanceCount,	//::QueryPerformanceFrequency (msec)
            pmThreadTimes,		//::GetThreadTimes (msec)
        #elif defined(xOS_LINUX)
            pmGetTimeOfDay      //gettimeofday (microsec)
        #endif
		};
		
		              CxProfiler(const tString &csLogFilePath, EMode pmMode); //TODO: csFileName + iPerfomMode
		virtual      ~CxProfiler();

		BOOL          bStart   ();
		BOOL          bStop    (LPCTSTR pcszComment, ...);
        BOOL          bPulse   (LPCTSTR pcszComment, ...);   

    private:
	    BOOL          _m_bRes;
		EMode		  _m_pmModeNow;		 
        BOOL          _m_bIsStarted;
		CxFileLog     _flLog;

        //pmClock
        std::clock_t  _m_ctClocksStart;
        std::clock_t  _m_ctClocksStop;

		//pmTime
		CxDateTime    _m_dtTimesStart;
		CxDateTime    _m_dtTimesStop;

    #if defined(xOS_WIN)
        //pmTickCount
        ULONG         _m_ulTicksStart;
        ULONG         _m_ulTicksStop;

        //pmPerformanceCount
        LARGE_INTEGER _m_liCountersPerfFreq;	//Ticks per second
        LARGE_INTEGER _m_liCountersStart;
        LARGE_INTEGER _m_liCountersStop;

        //pmThreadTimes
        FILETIME      _m_lpCreationTime;
        FILETIME      _m_lpExitTime;
        FILETIME      _m_lpKernelTimeStart;
        FILETIME      _m_lpUserTimeStart;
        FILETIME      _m_lpKernelTimeStop;
        FILETIME      _m_lpUserTimeStop;
    #elif defined(xOS_LINUX)

        //pmGetTimeOfDay
        DOUBLE        _m_dMicrosecStart;
        DOUBLE        _m_dMicrosecStop;
    #endif

		BOOL          _bResetData();
};
//---------------------------------------------------------------------------
#endif	//xLib_Debug_CxProfilerH

//http://www.metalshell.com/source_code/133/Microsecond_Benchmark.html


/*
system.h:
#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

double time_in_seconds();


system_posix.cpp:
#include "system.h"
#include <sys/time.h>

double time_in_seconds() {
  struct timeval tp;
  gettimeofday(&tp,0);
  return tp.tv_sec+.000001*tp.tv_usec;
}


system_standard.cpp:
#include "system.h"
#include <ctime>

double time_in_seconds() {
  return std::clock()/(double)CLOCKS_PER_SEC;
}


#include <time.h>

double time_in_seconds() {
  struct timespec tp;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp);
  return tp.tv_sec + .000000001 * tp.tv_nsec;
}



#endif
*/
