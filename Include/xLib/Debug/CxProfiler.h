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
class CxProfiler :
    public CxNonCopyable
    /// code profiling (msec)
{
    public:
        enum EMode
            /// mode
        {
            pmStdClock,         ///< use std::clock_t
            pmDateTime,         ///< use CxDateTime
            pmGetTimeOfDay      ///< use gettimeofday
        #if defined(xOS_ENV_WIN)
            ,
            pmTickCount,        ///< use ::GetTickCount
            pmPerformanceCount, ///< use ::QueryPerformanceFrequency
            pmThreadTimes       ///< use ::GetThreadTime
        #endif
        };

                            CxProfiler (const EMode cpmMode);
            ///< constructor
        virtual            ~CxProfiler ();
            ///< destructor

        BOOL                bSetLogPath(const std::string_t &csLogPath);
            ///< set log path
        const std::string_t &sGetLogPath() const;
            ///< get log path

        BOOL                bStart     ();
            ///< start measurement
        BOOL                bStop      (const char_t *pcszComment, ...);
            ///< stop measurement
        BOOL                bPulse     (const char_t *pcszComment, ...);
            ///< stop, start measurement

    private:
        const EMode         _m_pmModeNow;           ///< which mode is running now
        BOOL                _m_bIsStarted;          ///< is started
        CxFileLog           _flLog;                 ///< file log

        //pmClock
        std::clock_t        _m_ctClocksStart;       ///< start value
        std::clock_t        _m_ctClocksStop;        ///< stop value

        //pmDateTime
        CxDateTime          _m_dtTimesStart;        ///< start value
        CxDateTime          _m_dtTimesStop;         ///< stop value

        //pmGetTimeOfDay
        double              _m_dMicrosecStart;      ///< start value
        double              _m_dMicrosecStop;       ///< stop value

    #if defined(xOS_ENV_WIN)
        //pmTickCount
        ULONG               _m_ulTicksStart;        ///< start value
        ULONG               _m_ulTicksStop;         ///< stop value

        //pmPerformanceCount
        LARGE_INTEGER       _m_liCountersPerfFreq;  ///< ticks per second
        LARGE_INTEGER       _m_liCountersStart;     ///< start value
        LARGE_INTEGER       _m_liCountersStop;      ///< stop value

        //pmThreadTimes
        FILETIME            _m_lpCreationTime;      ///< for private use
        FILETIME            _m_lpExitTime;          ///< for private use
        FILETIME            _m_lpKernelTimeStart;   ///< start value
        FILETIME            _m_lpUserTimeStart;     ///< start value
        FILETIME            _m_lpKernelTimeStop;    ///< stop value
        FILETIME            _m_lpUserTimeStop;      ///< stop value
    #endif

        BOOL                _bResetData();
            ///< reset all class data

    #if defined(xOS_ENV_UNIX) && defined(xOS_FREEBSD)
        static std::clock_t _liGetClock();
            ///< get std::clock_t
            ///< http://bugs.vcmi.eu/view.php?id=719
    #endif

    #if defined(xOS_ENV_WIN)
        struct timezone
            /// for gettimeofday
        {
            int tz_minuteswest; ///< minutes W of Greenwich
            int tz_dsttime;     ///< type of dst correction
        };

        static int          gettimeofday(struct timeval *tv, struct timezone *tz);
            ///< porting from Linux gettimeofday
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
