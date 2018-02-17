/**
 * \file  Profiler.inl
 * \brief code profiling
 */


#include "Profiler.h"

#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Utils.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/File.h>


xNAMESPACE_BEGIN2(xl, debug)

/**************************************************************************************************
* public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Profiler::Profiler() :
    _isStarted(false),
    _log      (FileLog::lsDefaultMb),
    _start    (0),
    _stop     (0),
    _duration (0)
{
    _reset();
}
//-------------------------------------------------------------------------------------------------
Profiler::~Profiler()
{
    if ( !_log.filePath().empty() ) {
        _log.write(xT("----------------------------------------"));
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Profiler::setLogPath(
    std::ctstring_t &a_logPath
)
{
    xTEST_EQ(Path::isValid(a_logPath, xPTR_NULL), true);

    _log.setFilePath(a_logPath);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Profiler::logPath() const
{
    return _log.filePath();
}
//-------------------------------------------------------------------------------------------------
void_t
Profiler::start()
{
    xTEST_EQ(_isStarted, false);

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
Profiler::stop(
    cptr_ctchar_t a_comment, ...
)
{
    xTEST_EQ(_isStarted, true);

    // stop, get duration
    {
        _stop = std::clock();
        xTEST_DIFF(static_cast<clock_t>( - 1 ), _stop);

        _duration = _stop - _start;
        xTEST_LESS_EQ(static_cast<clock_t>( 0 ), _duration);
    }

    cdouble_t   durationMsec1 = (static_cast<double>( _duration ) /
        static_cast<double>( CLOCKS_PER_SEC )) * 1000.0;  // 1 sec = 1000 msec
    std::size_t durationMsec2 = Utils::roundIntT<std::size_t>( durationMsec1 );

    // write to log
    if ( !_log.filePath().empty() ) {
        std::tstring_t  sRv;
        std::ctstring_t durationTime = DateTime(durationMsec2).format(xT("%H:%M:%S"));

        va_list args;
        xVA_START(args, a_comment);
        sRv = FormatC::strV(a_comment, args);
        xVA_END(args);

        _log.write(xT("%s: %s"), durationTime.c_str(), sRv.c_str());
    }

    _isStarted = false;

    return durationMsec2;
}
//-------------------------------------------------------------------------------------------------
size_t
Profiler::restart(
    cptr_ctchar_t a_comment, ...
)
{
    size_t uiRV = 0;

    // format comment
    std::tstring_t sRv;

    if ( !_log.filePath().empty() ) {
        va_list args;
        xVA_START(args, a_comment);
        sRv = FormatC::strV(a_comment, args);
        xVA_END(args);
    }

    // stop, start
    uiRV = stop(xT("%s"), sRv.c_str());
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

xNAMESPACE_END2(xl, debug)
