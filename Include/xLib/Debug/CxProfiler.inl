/**
 * \file  CxProfiler.cpp
 * \brief code profiling (msec)
 */


#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
* public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxProfiler::CxProfiler() :
    _isStarted(false),
    _log      (CxFileLog::lsDefaultSize)
{
    _dataReset();
}
//-------------------------------------------------------------------------------------------------
inline
CxProfiler::~CxProfiler()
{
    if ( !_log.filePath().empty() ) {
        _log.write(xT("----------------------------------------"));
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProfiler::setLogPath(
    std::ctstring_t &a_logPath
)
{
    xTEST_EQ(true, CxPath::isValid(a_logPath));

    _log.setFilePath(a_logPath);
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxProfiler::logPath() const
{
    return _log.filePath();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxProfiler::start()
{
    xTEST_EQ(false, _isStarted);

    _dataReset();

    // TODO: set highest thread priority
    {

    }

    _start = xSTD_CLOCK();
    xTEST_DIFF(static_cast<clock_t>( - 1 ), _start);

    _isStarted = true;
}
//-------------------------------------------------------------------------------------------------
inline size_t
CxProfiler::stop(
    ctchar_t *a_comment, ...
)
{
    xTEST_EQ(true, _isStarted);

    //-------------------------------------
    // stop, get duration
    {
        _stop = xSTD_CLOCK();
        xTEST_DIFF(static_cast<clock_t>( - 1 ), _stop);

        _duration = _stop - _start;
        xTEST_LESS_EQ(static_cast<clock_t>( 0 ), _duration);
    }

    cdouble_t   durationMsec1 = (static_cast<double>( _duration ) /
        static_cast<double>( CLOCKS_PER_SEC )) * 1000.0;  // 1 sec = 1000 msec
    std::size_t durationMsec2 = CxUtils::roundIntT<std::size_t>( durationMsec1 );

    //-------------------------------------
    // write to log
    if ( !_log.filePath().empty() ) {
        std::tstring_t  sRv;
        // TODO: fix msec
        std::ctstring_t durationTime = CxDateTime(durationMsec2).format(xT("%H:%M:%S"));

        va_list args;
        xVA_START(args, a_comment);
        sRv = CxString::formatV(a_comment, args);
        xVA_END(args);

        _log.write(xT("%s: %s"), durationTime.c_str(), sRv.c_str());
    }

    _isStarted = false;

    return durationMsec2;
}
//-------------------------------------------------------------------------------------------------
inline size_t
CxProfiler::restart(
    ctchar_t *a_comment, ...
)
{
    size_t uiRV = 0;

    //-------------------------------------
    // format comment
    std::tstring_t sRv;

    if ( !_log.filePath().empty() ) {
        va_list args;
        xVA_START(args, a_comment);
        sRv = CxString::formatV(a_comment, args);
        xVA_END(args);
    }

    //-------------------------------------
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
CxProfiler::_dataReset()
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

xNAMESPACE_END(NxLib)
