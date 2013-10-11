/**
 * \file  CxProfiler.cpp
 * \brief code profiling (msec)
 */


#include <xLib/Debug/CxProfiler.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Sync/CxCurrentProcess.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
* public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxProfiler::CxProfiler() :
    _m_bIsStarted(false),
    _flLog       (CxFileLog::lsDefaultSize)
{
    _dataReset();
}
//------------------------------------------------------------------------------
CxProfiler::~CxProfiler() {
    if ( !_flLog.filePath().empty() ) {
        _flLog.write(xT("----------------------------------------"));
    }
}
//------------------------------------------------------------------------------
void_t
CxProfiler::setLogPath(
    std::ctstring_t &a_csLogPath
)
{
    xTEST_EQ(true, CxPath::isValid(a_csLogPath));

    _flLog.setFilePath(a_csLogPath);
}
//------------------------------------------------------------------------------
std::ctstring_t &
CxProfiler::logPath() const {
    return _flLog.filePath();
}
//--------------------------------------------------------------------------
void_t
CxProfiler::start() {
    xTEST_EQ(false, _m_bIsStarted);

    _dataReset();

    // TODO: set highest thread priority
    {

    }

    _m_clkStart = xSTD_CLOCK();
    xTEST_DIFF(static_cast<clock_t>( - 1 ), _m_clkStart);

    _m_bIsStarted = true;
}
//--------------------------------------------------------------------------
size_t
CxProfiler::stop(
    ctchar_t *a_pcszComment, ...
)
{
    xTEST_EQ(true, _m_bIsStarted);

    //-------------------------------------
    // stop, get duration
    {
        _m_clkStop = xSTD_CLOCK();
        xTEST_DIFF(static_cast<clock_t>( - 1 ), _m_clkStop);

        _m_clkDuration = _m_clkStop - _m_clkStart;
        xTEST_LESS_EQ(static_cast<clock_t>( 0 ), _m_clkDuration);
    }

    cdouble_t       cdDurationMsec   = (static_cast<double>( _m_clkDuration ) / static_cast<double>( CLOCKS_PER_SEC )) * 1000.0;  // 1 sec = 1000 msec
    std::size_t     cullDurationMsec = CxUtils::roundIntT<std::size_t>( cdDurationMsec );

    //-------------------------------------
    // write to log
    if ( !_flLog.filePath().empty() ) {
        std::tstring_t  sRv;
        std::ctstring_t csDurationTime = CxDateTime(cullDurationMsec).format(CxDateTime::ftTime);

        va_list palArgs;
        xVA_START(palArgs, a_pcszComment);
        sRv = CxString::formatV(a_pcszComment, palArgs);
        xVA_END(palArgs);

        _flLog.write(xT("%s: %s"), csDurationTime.c_str(), sRv.c_str());
    }

    _m_bIsStarted = false;

    return cullDurationMsec;
}
//--------------------------------------------------------------------------
size_t
CxProfiler::restart(
    ctchar_t *a_pcszComment, ...
)
{
    size_t uiRV = 0;

    //-------------------------------------
    // format comment
    std::tstring_t sRv;

    if ( !_flLog.filePath().empty() ) {
        va_list palArgs;
        xVA_START(palArgs, a_pcszComment);
        sRv = CxString::formatV(a_pcszComment, palArgs);
        xVA_END(palArgs);
    }

    //-------------------------------------
    // stop, start
    uiRV = stop(xT("%s"), sRv.c_str());
    start();

    return uiRV;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void_t
CxProfiler::_dataReset() {
    // TODO: set normal thread priority
    {

    }

    _m_bIsStarted = false;

    _m_clkStart    = 0L;
    _m_clkStop     = 0L;
    _m_clkDuration = 0L;
}
//--------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
