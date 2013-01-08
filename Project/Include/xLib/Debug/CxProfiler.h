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
    /// code profiling
{
public:
    explicit              CxProfiler();
        ///< constructor
    virtual              ~CxProfiler();
        ///< destructor

    void                  setLogPath(const std::tstring_t &csLogPath);
        ///< set log path
    const std::tstring_t &logPath   () const xWARN_UNUSED_RESULT;
        ///< get log path

    void                  start     ();
        ///< start measurement
    void                  stop      (const tchar_t *pcszComment, ...);
        ///< stop measurement
    void                  pulse     (const tchar_t *pcszComment, ...);
        ///< stop, start measurement

private:
    bool                  _m_bIsStarted;    ///< is started
    CxFileLog             _flLog;           ///< file log

    std::clock_t          _m_clkStart;      ///< start value
    std::clock_t          _m_clkStop;       ///< stop value
    std::clock_t          _m_clkDuration;   ///< duration value

    void                  _dataReset();
        ///< reset all class data
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Debug_CxProfilerH


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
