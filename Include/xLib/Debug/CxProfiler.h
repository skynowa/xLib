/****************************************************************************
* Class name:  CxProfiler
* Description: code profiling (msec)
* File name:   CxProfiler.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
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
class CxProfiler :
    public CxNonCopyable
{
    public:
        enum EMode {
            pmStdClock,
            pmDateTime,
            pmGetTimeOfDay
        #if defined(xOS_WIN)
            ,
            pmTickCount,
            pmPerformanceCount,
            pmThreadTimes
        #endif
        };

                            CxProfiler (const EMode cpmMode);
        virtual            ~CxProfiler ();

        BOOL                bSetLogPath(const tString &csLogPath);
        const tString &     sGetLogPath() const;

        BOOL                bStart     ();
        BOOL                bStop      (LPCTSTR pcszComment, ...);
        BOOL                bPulse     (LPCTSTR pcszComment, ...);

    private:
        BOOL                _m_bRes;
        const EMode         _m_pmModeNow;
        BOOL                _m_bIsStarted;
        CxFileLog           _flLog;

        //pmClock
        std::clock_t        _m_ctClocksStart;
        std::clock_t        _m_ctClocksStop;

        //pmDateTime
        CxDateTime          _m_dtTimesStart;
        CxDateTime          _m_dtTimesStop;

        //pmGetTimeOfDay
        DOUBLE              _m_dMicrosecStart;
        DOUBLE              _m_dMicrosecStop;

    #if defined(xOS_WIN)
        //pmTickCount
        ULONG               _m_ulTicksStart;
        ULONG               _m_ulTicksStop;

        //pmPerformanceCount
        LARGE_INTEGER       _m_liCountersPerfFreq;    //Ticks per second
        LARGE_INTEGER       _m_liCountersStart;
        LARGE_INTEGER       _m_liCountersStop;

        //pmThreadTimes
        FILETIME            _m_lpCreationTime;
        FILETIME            _m_lpExitTime;
        FILETIME            _m_lpKernelTimeStart;
        FILETIME            _m_lpUserTimeStart;
        FILETIME            _m_lpKernelTimeStop;
        FILETIME            _m_lpUserTimeStop;
    #endif

        BOOL                _bResetData();

    #if defined(xOS_FREEBSD)
        static std::clock_t _liGetClock();
    #endif

    #if defined(xOS_WIN)
        //for gettimeofday
        struct timezone {
            INT  tz_minuteswest;    //minutes W of Greenwich
            INT  tz_dsttime;        //type of dst correction
        };

        static INT          gettimeofday(struct timeval *tv, struct timezone *tz);
    #endif
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxProfilerH


//http://www.metalshell.com/source_code/133/Microsecond_Benchmark.html

#if xTODO
    //system.h:
    #ifndef SYSTEM_H_INCLUDED
    #define SYSTEM_H_INCLUDED

    double time_in_seconds();


    //system_posix.cpp:
    #include "system.h"
    #include <sys/time.h>

    double time_in_seconds() {
        struct timeval tp;
        gettimeofday(&tp,0);
        return tp.tv_sec+.000001*tp.tv_usec;
    }


    //system_standard.cpp:
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
#endif
