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

/****************************************************************************
* public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxProfiler::CxProfiler() :
    _m_bIsStarted(false),
    _flLog       (CxFileLog::lsDefaultSize)
{
    _vDataReset();
}
//---------------------------------------------------------------------------
CxProfiler::~CxProfiler() {
    if (false == _flLog.sFilePath().empty()) {
        _flLog.vWrite(xT("----------------------------------------"));
    }
}
//---------------------------------------------------------------------------
void
CxProfiler::vSetLogPath(
    const std::tstring_t &a_csLogPath
)
{
    xTEST_EQ(true, CxPath::bIsValid(a_csLogPath));

    _flLog.vSetFilePath(a_csLogPath);
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxProfiler::sLogPath() const {
    return _flLog.sFilePath();
}
//--------------------------------------------------------------------------
void
CxProfiler::vStart() {
    xTEST_EQ(false, _m_bIsStarted);

    _vDataReset();

    // TODO: set highest thread priority
    {

    }

    _m_clkStart = xSTD_CLOCK();
    xTEST_DIFF(static_cast<clock_t>( - 1 ), _m_clkStart);

    _m_bIsStarted = true;
}
//--------------------------------------------------------------------------
void
CxProfiler::vStop(
    const tchar_t *a_pcszComment, ...
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

    const double         cdDurationMsec   = (static_cast<double>( _m_clkDuration ) / static_cast<double>( CLOCKS_PER_SEC )) * 1000.0;  // 1 sec = 1000 msec
    const ulonglong_t    cullDurationMsec = CxUtils::roundIntT<ulonglong_t>( cdDurationMsec );
    const std::tstring_t csDurationTime   = CxDateTime(cullDurationMsec).format(CxDateTime::ftTime);

    //-------------------------------------
    // write to log
    {
        std::tstring_t sRv;

        va_list palArgs;
        xVA_START(palArgs, a_pcszComment);
        sRv = CxString::formatV(a_pcszComment, palArgs);
        xVA_END(palArgs);

        _flLog.vWrite(xT("%s: %s"), csDurationTime.c_str(), sRv.c_str());
    }

    _m_bIsStarted = false;
}
//--------------------------------------------------------------------------
void
CxProfiler::vPulse(
    const tchar_t *a_pcszComment, ...
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
    vStop(xT("%s"), sRv.c_str());
    vStart();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxProfiler::_vDataReset() {
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
