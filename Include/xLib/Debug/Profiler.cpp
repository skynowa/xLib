/**
 * \file  Profiler.cpp
 * \brief code profiling
 */


#include "Profiler.h"

#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Fs/Path.h>


namespace xl::debug
{

/**************************************************************************************************
* public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Profiler::start()
{
    xTEST(!_isStarted);

    _reset();

    // TODO: [skynowa] set highest thread priority
    {

    }

    _start = std::clock();
    xTEST_DIFF(static_cast<clock_t>( - 1 ), _start);

    _isStarted = true;
}
//-------------------------------------------------------------------------------------------------
size_t
Profiler::stop()
{
	xTEST(_isStarted);

    // stop, get duration
    {
        _stop = std::clock();
        xTEST_DIFF(static_cast<clock_t>(- 1), _stop);

        _duration = _stop - _start;
        xTEST_GR_EQ(_duration, static_cast<clock_t>(0));
    }

    cdouble_t    durationMsec1 = (static_cast<double>(_duration) /
        static_cast<double>(CLOCKS_PER_SEC)) * 1000.0;  // 1 sec = 1000 msec
    std::csize_t durationMsec2 = Utils::roundIntT<std::size_t>(durationMsec1);

    _isStarted = false;

    return durationMsec2;
}
//-------------------------------------------------------------------------------------------------
size_t
Profiler::restart()
{
    size_t uiRV {};

    // stop, start
    uiRV = stop();
    start();

    return uiRV;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Profiler::_reset()
{
    // TODO: [skynowa] set normal thread priority
    {

    }

    _isStarted = false;

    _start    = 0L;
    _stop     = 0L;
    _duration = 0L;
}
//-------------------------------------------------------------------------------------------------

} // namespace
