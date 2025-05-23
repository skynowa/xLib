/**
 * \file  Profiler.h
 * \brief code profiling
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Log/FileLog.h>
//-------------------------------------------------------------------------------------------------
namespace xl::debug
{

class Profiler
    /// code profiling
{
public:
///\name ctors, dtor
///\{
             Profiler() = default;
	virtual ~Profiler() = default;

	xNO_COPY_ASSIGN(Profiler);
///\}

    void_t start();
        ///< start measurement
    size_t stop();
        ///< stop measurement
    size_t restart();
        ///< stop, start measurement

private:
    bool_t       _isStarted {}; ///< is started

    std::clock_t _start {};     ///< start value
    std::clock_t _stop {};      ///< stop value
    std::clock_t _duration {};  ///< duration value

    void_t _reset();
        ///< reset all data
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * \file  Profiler.h
 *
 * \todo
 *
 * - Port to std::chrono
 * - http://www.metalshell.com/source_code/133/Microsecond_Benchmark.html
 */

#if xTODO
    #ifndef SYSTEM_H_INCLUDED
    #define SYSTEM_H_INCLUDED

    double time_in_seconds();

    // system_posix.inl:
    #include <sys/time.h>

    double time_in_seconds()
    {
        timeval tp;
        gettimeofday(&tp,0);
        return tp.tv_sec+.000001*tp.tv_usec;
    }

    // system_standard.inl:
    #include <ctime>

    double time_in_seconds()
    {
        return std::clock()/(double)CLOCKS_PER_SEC;
    }

    #include <time.h>

    double time_in_seconds()
    {
        timespec tp {};
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp);
        return tp.tv_sec + .000000001 * tp.tv_nsec;
    }

    #endif
#endif
