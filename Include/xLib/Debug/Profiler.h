/**
 * \file  Profiler.h
 * \brief code profiling
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Core/DateTime.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class Profiler
    /// code profiling
{
public:
    explicit       Profiler();
        ///< constructor
    virtual       ~Profiler();
        ///< destructor

    void_t         setLogPath(std::ctstring_t &logPath);
        ///< set log path
    std::tstring_t logPath() const xWARN_UNUSED_RV;
        ///< get log path

    void_t         start();
        ///< start measurement
    size_t         stop(cptr_ctchar_t comment, ...) xWARN_UNUSED_RV;
        ///< stop measurement
    size_t         restart(cptr_ctchar_t comment, ...) xWARN_UNUSED_RV;
        ///< stop, start measurement

private:
    bool_t         _isStarted;  ///< is started
    FileLog        _log;        ///< file log

    std::clock_t   _start;      ///< start value
    std::clock_t   _stop;       ///< stop value
    std::clock_t   _duration;   ///< duration value

    void_t         _reset();
        ///< reset all data

    xNO_COPY_ASSIGN(Profiler)
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Profiler.cpp"
#endif


// http://www.metalshell.com/source_code/133/Microsecond_Benchmark.html

#if xTODO
    //system.h:
    #ifndef SYSTEM_H_INCLUDED
    #define SYSTEM_H_INCLUDED

    double time_in_seconds();


    // system_posix.inl:
    #include "system.h"
    #include <sys/time.h>

    double time_in_seconds() {
        timeval tp;
        gettimeofday(&tp,0);
        return tp.tv_sec+.000001*tp.tv_usec;
    }


    // system_standard.inl:
    #include "system.h"
    #include <ctime>

    double time_in_seconds() {
      return std::clock()/(double)CLOCKS_PER_SEC;
    }


    #include <time.h>

    double time_in_seconds() {
      timespec tp;
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp);
      return tp.tv_sec + .000000001 * tp.tv_nsec;
    }

    #endif
#endif
