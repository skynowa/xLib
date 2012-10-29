/**
 * \file  CxProfiler.h
 * \brief code profiling (msec)
 */


#ifndef xLib_Debug_CxProfilerH
#define xLib_Debug_CxProfilerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Log/CxFileLog.h>
#include <xLib/Common/CxDateTime.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxProfiler :
    private CxNonCopyable
    /// code profiling (msec)
{
    public:
        enum ExMode
            /// mode
        {
            pmStdClock,         ///< use std::clock_t
            pmDateTime,         ///< use CxDateTime
            pmGetTimeOfDay,     ///< use gettimeofday
            pmSystemTicks       ///< use system ticks
        #if   xOS_ENV_WIN
            ,
            pmPerformanceCount, ///< use ::QueryPerformanceFrequency
            pmThreadTimes       ///< use ::GetThreadTime
        #endif
        };

        explicit              CxProfiler (const ExMode &cpmMode);
            ///< constructor
        virtual              ~CxProfiler ();
            ///< destructor

        void                  vSetLogPath(const std::tstring_t &csLogPath);
            ///< set log path
        const std::tstring_t &sLogPath   () const;
            ///< get log path

        void                  vStart     ();
            ///< start measurement
        void                  vStop      (const tchar_t *pcszComment, ...);
            ///< stop measurement
        void                  vPulse     (const tchar_t *pcszComment, ...);
            ///< stop, start measurement

    private:
        const ExMode          _m_pmModeNow;           ///< which mode is running now
        bool                  _m_bIsStarted;          ///< is started
        CxFileLog             _flLog;                 ///< file log

        // pmStdClock
        std::clock_t          _m_ctClocksStart;       ///< start value
        std::clock_t          _m_ctClocksStop;        ///< stop value

        // pmDateTime
        CxDateTime            _m_dtTimesStart;        ///< start value
        CxDateTime            _m_dtTimesStop;         ///< stop value

        // pmGetTimeOfDay
        double                _m_dMicrosecStart;      ///< start value
        double                _m_dMicrosecStop;       ///< stop value

        // pmSystemTicks
        ulong_t               _m_ulTicksStartMs;      ///< start value
        ulong_t               _m_ulTicksStopMs;       ///< stop value

    #if xOS_ENV_WIN
        // pmPerformanceCount
        LARGE_INTEGER         _m_liCountersPerfFreq;  ///< ticks per second
        LARGE_INTEGER         _m_liCountersStart;     ///< start value
        LARGE_INTEGER         _m_liCountersStop;      ///< stop value

        // pmThreadTimes
        FILETIME              _m_lpCreationTime;      ///< for private use
        FILETIME              _m_lpExitTime;          ///< for private use
        FILETIME              _m_lpKernelTimeStart;   ///< start value
        FILETIME              _m_lpUserTimeStart;     ///< start value
        FILETIME              _m_lpKernelTimeStop;    ///< stop value
        FILETIME              _m_lpUserTimeStop;      ///< stop value
    #endif

        void                  _vDataReset();
            ///< reset all class data
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxProfilerH


// http://www.metalshell.com/source_code/133/Microsecond_Benchmark.html

#if xTODO
    //system.h:
    #ifndef SYSTEM_H_INCLUDED
    #define SYSTEM_H_INCLUDED

    double time_in_seconds();


    // system_posix.cpp:
    #include "system.h"
    #include <sys/time.h>

    double time_in_seconds() {
        struct timeval tp;
        gettimeofday(&tp,0);
        return tp.tv_sec+.000001*tp.tv_usec;
    }


    // system_standard.cpp:
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
