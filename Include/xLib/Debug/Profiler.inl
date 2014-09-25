/**
 * \file  Profiler.inl
 * \brief code profiling
 */


#if !xOPTION_HEADER_ONLY
    #include "Profiler.h"
#endif

#include <xLib/Core/String.h>
#include <xLib/Core/Utils.h>
#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
* public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
Profiler::Profiler() :
    _isStarted(false),
    _log      (FileLog::lsDefaultMb),
    _start    (0),
    _stop     (0),
    _duration (0)
{
    _dataReset();
}
//-------------------------------------------------------------------------------------------------
inline
Profiler::~Profiler()
{
    if ( !_log.filePath().empty() ) {
        _log.write(xT("----------------------------------------"));
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
Profiler::setLogPath(
    std::ctstring_t &a_logPath
)
{
    xTEST_EQ(Path::isValid(a_logPath), true);

    _log.setFilePath(a_logPath);
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
Profiler::logPath() const
{
    return _log.filePath();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Profiler::start()
{
    xTEST_EQ(_isStarted, false);

    _dataReset();

    // TODO: set highest thread priority
    {

    }

    _start = std::clock();
    xTEST_DIFF(static_cast<clock_t>( - 1 ), _start);

    _isStarted = true;
}
//-------------------------------------------------------------------------------------------------
inline size_t
Profiler::stop(
    ctchar_t *a_comment, ...
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
        sRv = String::formatV(a_comment, args);
        xVA_END(args);

        _log.write(xT("%s: %s"), durationTime.c_str(), sRv.c_str());
    }

    _isStarted = false;

    return durationMsec2;
}
//-------------------------------------------------------------------------------------------------
inline size_t
Profiler::restart(
    ctchar_t *a_comment, ...
)
{
    size_t uiRV = 0;

    // format comment
    std::tstring_t sRv;

    if ( !_log.filePath().empty() ) {
        va_list args;
        xVA_START(args, a_comment);
        sRv = String::formatV(a_comment, args);
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
inline void_t
Profiler::_dataReset()
{
    // TODO: set normal thread priority
    {

    }

    _isStarted = false;

    _start    = 0L;
    _stop     = 0L;
    _duration = 0L;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
