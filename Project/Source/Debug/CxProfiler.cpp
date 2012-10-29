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
CxProfiler::CxProfiler(
    const ExMode &a_cpmMode
) :
    _m_pmModeNow (a_cpmMode),
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
    /*DEBUG*/

    _flLog.vSetFilePath(a_csLogPath);
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxProfiler::sLogPath() const {
    /*DEBUG*/

    return _flLog.sFilePath();
}
//--------------------------------------------------------------------------
void
CxProfiler::vStart() {
    /*DEBUG*/xTEST_EQ(false, _m_bIsStarted);

    _vDataReset();

    #if xTODO
         // TODO: CxProcess::vSetPriority
        CxProcess::vSetPriority(CxProcess::ulGetCurrId(), CxProcess::tpTimeCritical);
    #endif

    CxCurrentThread::vSleep(10UL);

    switch (_m_pmModeNow) {
        case pmStdClock: {
                _m_ctClocksStart = xSTD_CLOCK_T();
                /*DEBUG*/xTEST_DIFF(static_cast<clock_t>( - 1 ), _m_ctClocksStart);
            }
            break;

        case pmDateTime: {
                _m_dtTimesStart = CxDateTime::dtCurrent();
                /*DEBUG*/// n/a
            }
            break;

        case pmGetTimeOfDay: {
                timeval tv = {0};
                /*::*/xGETTIMEOFDAY(&tv, NULL);

                _m_dMicrosecStart = static_cast<double>( tv.tv_sec ) + static_cast<double>( tv.tv_usec ) * 0.000001;
            }
            break;

        #if xOS_ENV_WIN
            case pmTickCount: {
                    _m_ulTicksStart = ::GetTickCount();
                    /*DEBUG*/// n/a
                }
                break;

            case pmPerformanceCount: {
                    BOOL blRes = ::QueryPerformanceFrequency(&_m_liCountersPerfFreq);
                    /*DEBUG*/xTEST_DIFF(FALSE, blRes);

                    blRes = ::QueryPerformanceCounter(&_m_liCountersStart);
                    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
                }
                break;

            case pmThreadTimes: {
                    BOOL blRes = ::GetThreadTimes(CxCurrentThread::hHandle(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStart, &_m_lpUserTimeStart);
                    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
                }
                break;
        #endif

        default: {
                /*DEBUG*/xTEST_FAIL;
            }
            break;
    }

    _m_bIsStarted = true;
}
//--------------------------------------------------------------------------
void
CxProfiler::vStop(
    const tchar_t *a_pcszComment, ...
)
{
    /*DEBUG*/xTEST_EQ(true, _m_bIsStarted);

    std::tstring_t sTimeString = xT("0:00:00:000");

    switch (_m_pmModeNow) {
        case pmStdClock: {
                #if xOS_FREEBSD
                    std::clock_t ctClockResolution = 1000;
                #else
                    std::clock_t ctClockResolution = CLOCKS_PER_SEC / 1000;
                #endif

                _m_ctClocksStop = xSTD_CLOCK_T();
                /*DEBUG*/xTEST_DIFF(static_cast<clock_t>( - 1 ), _m_ctClocksStop);

                sTimeString = CxDateTime( (_m_ctClocksStop - _m_ctClocksStart) / ctClockResolution ).sFormat(CxDateTime::ftTime);
            }
            break;

        case pmDateTime: {
                _m_dtTimesStop = CxDateTime::dtCurrent();
                /*DEBUG*/// n/a

                sTimeString = (_m_dtTimesStop - _m_dtTimesStart).sFormat(CxDateTime::ftTime);
            }
            break;

        case pmGetTimeOfDay: {
                timeval tv = {0};
                /*::*/xGETTIMEOFDAY(&tv, NULL);

                _m_dMicrosecStop = static_cast<double>( tv.tv_sec ) + static_cast<double>( tv.tv_usec ) * 0.000001;

                sTimeString = CxString::sFormat(xT("%.6lf (sec)"), _m_dMicrosecStop - _m_dMicrosecStart);
            }
            break;

        #if xOS_ENV_WIN
            case pmTickCount: {
                    _m_ulTicksStop = ::GetTickCount();
                    /*DEBUG*/// n/a

                    sTimeString = CxDateTime(_m_ulTicksStop - _m_ulTicksStart).sFormat(CxDateTime::ftTime);
                }
                break;

            case pmPerformanceCount: {
                    BOOL blRes = ::QueryPerformanceCounter(&_m_liCountersStop);
                    /*DEBUG*/xTEST_DIFF(FALSE, blRes);

                    sTimeString = CxDateTime((_m_liCountersStop.QuadPart - _m_liCountersStart.QuadPart) * 1000 / _m_liCountersPerfFreq.QuadPart).sFormat(CxDateTime::ftTime);
                }
                break;

            case pmThreadTimes: {
                    BOOL blRes = ::GetThreadTimes(CxCurrentThread::hHandle(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStop, &_m_lpUserTimeStop);
                    /*DEBUG*/xTEST_DIFF(FALSE, blRes);

                    sTimeString = CxDateTime((CxDateTime::i64FiletimeToInt64(_m_lpUserTimeStop) - CxDateTime::i64FiletimeToInt64(_m_lpUserTimeStart)) / 10000).sFormat(CxDateTime::ftTime);
                }
                break;
        #endif

        default: {
                /*DEBUG*/xTEST_FAIL;
            }
            break;
    }

    //-------------------------------------
    // format comment
    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, a_pcszComment);
    sRv = CxString::sFormatV(a_pcszComment, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    // write to log
    _flLog.vWrite(xT("%s: %s"), sTimeString.c_str(), sRv.c_str());

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
    sRv = CxString::sFormatV(a_pcszComment, palArgs);
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
    #if xTODO
        // TODO: CxProcess::vSetPriority
        CxProcess::vSetPriority(CxCurrentProcess::ulId(), CxProcess::tpNormal);
    #endif

    _m_bIsStarted                       = false;

    // pmStdClock
    xSTRUCT_ZERO(_m_ctClocksStart);
    xSTRUCT_ZERO(_m_ctClocksStop);

    // pmDateTime
    _m_dtTimesStart                     = 0ULL;
    _m_dtTimesStop                      = 0ULL;

    // pmGetTimeOfDay
    _m_dMicrosecStart                   = 0.0f;
    _m_dMicrosecStop                    = 0.0f;

#if   xOS_ENV_WIN
    // pmGetTickCount
    _m_ulTicksStart                     = 0UL;
    _m_ulTicksStop                      = 0UL;

    // pmPerformanceCount
    _m_liCountersPerfFreq.QuadPart      = 0L;
    _m_liCountersStart.QuadPart         = 0L;
    _m_liCountersStop.QuadPart          = 0L;

    // pmThreadTimes
    _m_lpCreationTime.dwLowDateTime     = 0UL;
    _m_lpCreationTime.dwHighDateTime    = 0UL;
    _m_lpExitTime.dwLowDateTime         = 0UL;
    _m_lpExitTime.dwHighDateTime        = 0UL;
    _m_lpKernelTimeStart.dwLowDateTime  = 0UL;
    _m_lpKernelTimeStart.dwHighDateTime = 0UL;
    _m_lpUserTimeStart.dwLowDateTime    = 0UL;
    _m_lpUserTimeStart.dwHighDateTime   = 0UL;
    _m_lpKernelTimeStop.dwLowDateTime   = 0UL;
    _m_lpKernelTimeStop.dwHighDateTime  = 0UL;
    _m_lpUserTimeStop.dwLowDateTime     = 0UL;
    _m_lpUserTimeStop.dwHighDateTime    = 0UL;
#elif xOS_ENV_UNIX
    xNA;
#endif
}
//--------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
