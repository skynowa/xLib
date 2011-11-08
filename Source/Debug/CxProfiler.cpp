/**
 * \file  CxProfiler.cpp
 * \brief code profiling (msec)
 */


#include <xLib/Debug/CxProfiler.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxCurrentThread.h>


/****************************************************************************
* public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxProfiler::CxProfiler(
    const EMode cpmMode
) :
    _m_pmModeNow (cpmMode),
    _m_bIsStarted(FALSE),
    _flLog       (CxFileLog::lsDefaultSize)
{
    (VOID)_bResetData();
}
//---------------------------------------------------------------------------
CxProfiler::~CxProfiler() {
    if (false == _flLog.sGetFilePath().empty()) {
        BOOL bRes = _flLog.bWrite(xT("----------------------------------------"));
        /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
    }
}
//---------------------------------------------------------------------------
BOOL
CxProfiler::bSetLogPath(
    const std::tstring &csLogPath
)
{
    /*DEBUG*/

    BOOL bRes = _flLog.bSetFilePath(csLogPath);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
const std::tstring &
CxProfiler::sGetLogPath() const {
    /*DEBUG*/

    return _flLog.sGetFilePath();
}
//--------------------------------------------------------------------------
BOOL
CxProfiler::bStart() {
    /*DEBUG*/xASSERT_RET(FALSE == _m_bIsStarted, FALSE);

    BOOL bRes = _bResetData();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    #if xTODO
        bRes = CxProcess::bSetPriority(CxProcess::ulGetCurrId(), CxProcess::tpTimeCritical);
        /*DEBUG*/xASSERT(FALSE != bRes);
    #endif

    CxCurrentThread::bSleep(10UL);

    switch (_m_pmModeNow) {
        case pmStdClock: {
                #if defined(xOS_FREEBSD)
                    _m_ctClocksStart = _liGetClock();
                #else
                    _m_ctClocksStart = std::clock();
                #endif
                /*DEBUG*/xASSERT_RET(static_cast<clock_t>( - 1 ) != _m_ctClocksStart, FALSE);
            }
            break;

        case pmDateTime: {
                _m_dtTimesStart = CxDateTime::dtGetCurrent();
                /*DEBUG*/// n/a
            }
            break;

        case pmGetTimeOfDay: {
                timeval tv = {0};
                gettimeofday(&tv, NULL);

                _m_dMicrosecStart = static_cast<DOUBLE>( tv.tv_sec ) + static_cast<DOUBLE>( tv.tv_usec ) * 0.000001;
            }
            break;

        #if defined(xOS_ENV_WIN)
            case pmTickCount: {
                    _m_ulTicksStart = ::GetTickCount();
                    /*DEBUG*/// n/a
                }
                break;

            case pmPerformanceCount: {
                    bRes = ::QueryPerformanceFrequency(&_m_liCountersPerfFreq);
                    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

                    bRes = ::QueryPerformanceCounter(&_m_liCountersStart);
                    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
                }
                break;

            case pmThreadTimes: {
                    bRes = ::GetThreadTimes(CxCurrentThread::hGetHandle(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStart, &_m_lpUserTimeStart);
                    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
                }
                break;
        #endif

        default: {
                /*DEBUG*/xASSERT_MSG_RET(FALSE, xT("Unknown mode"), FALSE);
            }
            break;
    }

    _m_bIsStarted = TRUE;

    return TRUE;
}
//--------------------------------------------------------------------------
BOOL
CxProfiler::bStop(
    const TCHAR *pcszComment, ...
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_bIsStarted, FALSE);

    std::tstring sTimeString = xT("0:00:00:000");

    switch (_m_pmModeNow) {
        case pmStdClock: {
                std::clock_t ctClockResolution;

                #if defined(xOS_FREEBSD)
                    ctClockResolution = 1000;
                    _m_ctClocksStop   = _liGetClock();

                #else
                    ctClockResolution = CLOCKS_PER_SEC / 1000;
                    _m_ctClocksStop   = std::clock();
                #endif

                /*DEBUG*/xASSERT_RET(static_cast<clock_t>( - 1 ) != _m_ctClocksStop, FALSE);

                sTimeString = CxDateTime( (_m_ctClocksStop - _m_ctClocksStart) / ctClockResolution ).sFormat(CxDateTime::ftTime);
            }
            break;

        case pmDateTime: {
                _m_dtTimesStop = CxDateTime::dtGetCurrent();
                /*DEBUG*/// n/a

                sTimeString = (_m_dtTimesStop - _m_dtTimesStart).sFormat(CxDateTime::ftTime);
            }
            break;

        case pmGetTimeOfDay: {
                timeval tv = {0};
                gettimeofday(&tv, NULL);

                _m_dMicrosecStop = static_cast<DOUBLE>( tv.tv_sec ) + static_cast<DOUBLE>( tv.tv_usec ) * 0.000001;

                sTimeString = CxString::sFormat(xT("%.6lf (sec)"), _m_dMicrosecStop - _m_dMicrosecStart);
            }
            break;

        #if defined(xOS_ENV_WIN)
            case pmTickCount: {
                    _m_ulTicksStop = ::GetTickCount();
                    /*DEBUG*/// n/a

                    sTimeString = CxDateTime(_m_ulTicksStop - _m_ulTicksStart).sFormat(CxDateTime::ftTime);
                }
                break;

            case pmPerformanceCount: {
                    BOOL bRes = ::QueryPerformanceCounter(&_m_liCountersStop);
                    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

                    sTimeString = CxDateTime((_m_liCountersStop.QuadPart - _m_liCountersStart.QuadPart) * 1000 / _m_liCountersPerfFreq.QuadPart).sFormat(CxDateTime::ftTime);
                }
                break;

            case pmThreadTimes: {
                    BOOL bRes = ::GetThreadTimes(CxCurrentThread::hGetHandle(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStop, &_m_lpUserTimeStop);
                    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

                    sTimeString = CxDateTime((CxDateTime::i64FiletimeToInt64(_m_lpUserTimeStop) - CxDateTime::i64FiletimeToInt64(_m_lpUserTimeStart)) / 10000).sFormat(CxDateTime::ftTime);
                }
                break;
        #endif

        default: {
                /*DEBUG*/xASSERT_RET(FALSE, FALSE);
            }
            break;
    }

    //-------------------------------------
    //format comment
    std::tstring sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszComment);

    sRes = CxString::sFormatV(pcszComment, palArgs);

    xVA_END(palArgs);

    //-------------------------------------
    //write to log
    BOOL bRes = _flLog.bWrite(xT("%s: %s"), sTimeString.c_str(), sRes.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_bIsStarted = FALSE;

    return TRUE;
}
//--------------------------------------------------------------------------
BOOL
CxProfiler::bPulse(
    const TCHAR *pcszComment, ...
)
{
    //-------------------------------------
    //format comment
    std::tstring sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszComment);

    sRes = CxString::sFormatV(pcszComment, palArgs);

    xVA_END(palArgs);

    //-------------------------------------
    //stop, start
    BOOL bRes = bStop(sRes.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    bRes = bStart();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxProfiler::_bResetData() {
    #if xTODO
        BOOL bRes = CxProcess::bSetPriority(CxProcess::ulGetCurrId(), CxProcess::tpNormal);
        /*DEBUG*/xASSERT(FALSE != bRes);
    #endif

    _m_bIsStarted                       = FALSE;

    //pmStdClock
    xSTRUCT_ZERO(_m_ctClocksStart);
    xSTRUCT_ZERO(_m_ctClocksStop);

    //pmDateTime
    _m_dtTimesStart                     = 0ULL;
    _m_dtTimesStop                      = 0ULL;

    //pmGetTimeOfDay
    _m_dMicrosecStart                   = 0.0f;
    _m_dMicrosecStop                    = 0.0f;

#if defined(xOS_ENV_WIN)
    //pmGetTickCount
    _m_ulTicksStart                     = 0UL;
    _m_ulTicksStop                      = 0UL;

    //pmPerformanceCount
    _m_liCountersPerfFreq.QuadPart      = 0L;
    _m_liCountersStart.QuadPart         = 0L;
    _m_liCountersStop.QuadPart          = 0L;

    //pmThreadTimes
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
#elif defined(xOS_ENV_UNIX)

#endif

    return TRUE;
}
//--------------------------------------------------------------------------
#if defined(xOS_ENV_UNI) && defined(xOS_FREEBSD)
/*static*/
std::clock_t
CxProfiler::_liGetClock() {
    /*DEBUG*/

    std::clock_t liRes = static_cast<clock_t>( - 1 );

    rusage ruUsage = {{0}};

    INT iRes = getrusage(RUSAGE_SELF, &ruUsage);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, static_cast<clock_t>( - 1 ));

    liRes = static_cast<std::clock_t>(ruUsage.ru_utime.tv_sec  + ruUsage.ru_stime.tv_sec) * 1000000 +
            ruUsage.ru_utime.tv_usec + ruUsage.ru_stime.tv_usec;

    return liRes;
}
#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

/*static*/
INT
CxProfiler::gettimeofday(
    struct timeval  *tv,
    struct timezone *tz
)
{
#if defined(xCOMPILER_MS) || defined(_MSC_EXTENSIONS)
    ULONGLONG DELTA_EPOCH_IN_MICROSECS = 11644473600000000Ui64;
#else
    ULONGLONG DELTA_EPOCH_IN_MICROSECS = 11644473600000000ULL;
#endif

    FILETIME   ftTime  = {0};
    ULONGLONG  ullRes  = 0ULL;
    static INT iTzFlag = 0;

    if (NULL != tv) {
        ::GetSystemTimeAsFileTime(&ftTime);

        ullRes |= ftTime.dwHighDateTime;
        ullRes <<= 32;
        ullRes |= ftTime.dwLowDateTime;

        //convert into microseconds
        ullRes /= 10ULL;

        //converting file time to unix epoch
        ullRes -= DELTA_EPOCH_IN_MICROSECS;
        tv->tv_sec  = static_cast<long>( ullRes / 1000000UL );
        tv->tv_usec = static_cast<long>( ullRes % 1000000UL );
    }

    if (NULL != tz) {
        if (!iTzFlag) {
            _tzset();
            ++ iTzFlag;
        }

        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime     = _daylight;
    }

    return 0;
}

#endif
//---------------------------------------------------------------------------
