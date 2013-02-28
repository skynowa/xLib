/**
 * \file  CxProfiler.cpp
 * \brief code profiling (msec)
 */


#include <xLib/Debug/CxProfiler.h>

#include <xLib/Common/CxString.h>
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
    if (false == _flLog.filePath().empty()) {
        _flLog.write(xT("----------------------------------------"));
    }
}
//------------------------------------------------------------------------------
void
CxProfiler::setLogPath(
    const std::tstring_t &a_csLogPath
)
{
    xTEST_EQ(true, CxPath::isValid(a_csLogPath));

    _flLog.setFilePath(a_csLogPath);
}
//------------------------------------------------------------------------------
const std::tstring_t &
CxProfiler::logPath() const {
    return _flLog.filePath();
}
//--------------------------------------------------------------------------
void
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
void
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

    cdouble_t         cdDurationMsec   = (static_cast<double_t>( _m_clkDuration ) / static_cast<double_t>( CLOCKS_PER_SEC )) * 1000.0;  // 1 sec = 1000 msec
    culonglong_t    cullDurationMsec = CxUtils::roundIntT<ulonglong_t>( cdDurationMsec );
    const std::tstring_t csDurationTime   = CxDateTime(cullDurationMsec).format(CxDateTime::ftTime);

    //-------------------------------------
    // write to log
    {
        std::tstring_t sRv;

        va_list palArgs;
        xVA_START(palArgs, a_pcszComment);
        sRv = CxString::formatV(a_pcszComment, palArgs);
        xVA_END(palArgs);

        _flLog.write(xT("%s: %s"), csDurationTime.c_str(), sRv.c_str());
    }

    _m_bIsStarted = false;
}
//--------------------------------------------------------------------------
void
CxProfiler::pulse(
    ctchar_t *a_pcszComment, ...
)
{
    //-------------------------------------
    // format comment
    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, a_pcszComment);
    sRv = CxString::formatV(a_pcszComment, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    // stop, start
    stop(xT("%s"), sRv.c_str());
    start();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
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
