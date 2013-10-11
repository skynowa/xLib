/**
 * \file  CxProfiler.h
 * \brief code profiling (msec)
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Log/CxFileLog.h>
#include <xLib/Core/CxDateTime.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxProfiler :
    private CxNonCopyable
    /// code profiling
{
public:
    explicit         CxProfiler();
        ///< constructor
    virtual         ~CxProfiler();
        ///< destructor

    void_t           setLogPath(std::ctstring_t &csLogPath);
        ///< set log path
    std::ctstring_t &logPath() const xWARN_UNUSED_RV;
        ///< get log path

    void_t           start();
        ///< start measurement
    size_t           stop(ctchar_t *pcszComment, ...) xWARN_UNUSED_RV;
        ///< stop measurement
    size_t           restart(ctchar_t *pcszComment, ...) xWARN_UNUSED_RV;
        ///< stop, start measurement

private:
    bool_t           _m_bIsStarted;    ///< is started
    CxFileLog        _flLog;           ///< file log

    std::clock_t     _m_clkStart;      ///< start value
    std::clock_t     _m_clkStop;       ///< stop value
    std::clock_t     _m_clkDuration;   ///< duration value

    void_t           _dataReset();
        ///< reset all class data
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------


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
