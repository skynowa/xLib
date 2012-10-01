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
    const ExMode a_cpmMode
) :
    _m_pmModeNow (a_cpmMode),
    _m_bIsStarted(false),
    _flLog       (CxFileLog::lsDefaultSize)
{
    (void)_bResetData();
}
//---------------------------------------------------------------------------
CxProfiler::~CxProfiler() {
    if (false == _flLog.sGetFilePath().empty()) {
        bool bRv = _flLog.bWrite(xT("----------------------------------------"));
        /*DEBUG*/xTEST_EQ(true, bRv);
    }
}
//---------------------------------------------------------------------------
bool
CxProfiler::bSetLogPath(
    const std::tstring_t &a_csLogPath
)
{
    /*DEBUG*/

    bool bRv = _flLog.bSetFilePath(a_csLogPath);
    /*DEBUG*/xTEST_EQ(true, bRv);

    return true;
}
//---------------------------------------------------------------------------
const std::tstring_t &
CxProfiler::sGetLogPath() const {
    /*DEBUG*/

    return _flLog.sGetFilePath();
}
//--------------------------------------------------------------------------
bool
CxProfiler::bStart() {
    /*DEBUG*/xTEST_EQ(false, _m_bIsStarted);

    bool bRv = _bResetData();
    /*DEBUG*/xTEST_EQ(true, bRv);

    #if xTODO
        bRv = CxProcess::bSetPriority(CxProcess::ulGetCurrId(), CxProcess::tpTimeCritical);
        /*DEBUG*/xASSERT(true == bRv);
    #endif

    CxCurrentThread::bSleep(10UL);

    switch (_m_pmModeNow) {
        case pmStdClock: {
                #if xOS_FREEBSD
                    _m_ctClocksStart = _liGetClock();
                #else
                    _m_ctClocksStart = std::clock();
                #endif
                /*DEBUG*/xTEST_DIFF(static_cast<clock_t>( - 1 ), _m_ctClocksStart);
            }
            break;

        case pmDateTime: {
                _m_dtTimesStart = CxDateTime::dtGetCurrent();
                /*DEBUG*/// n/a
            }
            break;

        case pmGetTimeOfDay: {
                timeval tv = {0};
                /*::*/gettimeofday(&tv, NULL);

                _m_dMicrosecStart = static_cast<double>( tv.tv_sec ) + static_cast<double>( tv.tv_usec ) * 0.000001;
            }
            break;

        #if   xOS_ENV_WIN
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
                    BOOL blRes = ::GetThreadTimes(CxCurrentThread::hGetHandle(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStart, &_m_lpUserTimeStart);
                    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
                }
                break;
        #endif

        default: {
                /*DEBUG*/xASSERT_MSG_RET(false, xT("Unknown mode"), false);
            }
            break;
    }

    _m_bIsStarted = true;

    return true;
}
//--------------------------------------------------------------------------
bool
CxProfiler::bStop(
    const tchar_t *a_pcszComment, ...
)
{
    /*DEBUG*/xTEST_EQ(true, _m_bIsStarted);

    std::tstring_t sTimeString = xT("0:00:00:000");

    switch (_m_pmModeNow) {
        case pmStdClock: {
                std::clock_t ctClockResolution;

                #if xOS_FREEBSD
                    ctClockResolution = 1000;
                    _m_ctClocksStop   = _liGetClock();

                #else
                    ctClockResolution = CLOCKS_PER_SEC / 1000;
                    _m_ctClocksStop   = std::clock();
                #endif

                /*DEBUG*/xTEST_DIFF(static_cast<clock_t>( - 1 ), _m_ctClocksStop);

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
                /*::*/gettimeofday(&tv, NULL);

                _m_dMicrosecStop = static_cast<double>( tv.tv_sec ) + static_cast<double>( tv.tv_usec ) * 0.000001;

                sTimeString = CxString::sFormat(xT("%.6lf (sec)"), _m_dMicrosecStop - _m_dMicrosecStart);
            }
            break;

        #if   xOS_ENV_WIN
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
                    BOOL blRes = ::GetThreadTimes(CxCurrentThread::hGetHandle(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStop, &_m_lpUserTimeStop);
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
    //format comment
    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, a_pcszComment);
    sRv = CxString::sFormatV(a_pcszComment, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    //write to log
    bool bRv = _flLog.bWrite(xT("%s: %s"), sTimeString.c_str(), sRv.c_str());
    /*DEBUG*/xTEST_EQ(true, bRv);

    _m_bIsStarted = false;

    return true;
}
//--------------------------------------------------------------------------
bool
CxProfiler::bPulse(
    const tchar_t *pcszComment, ...
)
{
    //-------------------------------------
    //format comment
    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, pcszComment);

    sRv = CxString::sFormatV(pcszComment, palArgs);

    xVA_END(palArgs);

    //-------------------------------------
    //stop, start
    bool bRv = bStop(xT("%s"), sRv.c_str());
    /*DEBUG*/xTEST_EQ(true, bRv);

    bRv = bStart();
    /*DEBUG*/xTEST_EQ(true, bRv);

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxProfiler::_bResetData() {
    #if xTODO
        bool bRv = CxProcess::bSetPriority(CxCurrentProcess::ulGetId(), CxProcess::tpNormal);
        /*DEBUG*/xASSERT(true == bRv);
    #endif

    _m_bIsStarted                       = false;

    //pmStdClock
    xSTRUCT_ZERO(_m_ctClocksStart);
    xSTRUCT_ZERO(_m_ctClocksStop);

    //pmDateTime
    _m_dtTimesStart                     = 0ULL;
    _m_dtTimesStop                      = 0ULL;

    //pmGetTimeOfDay
    _m_dMicrosecStart                   = 0.0f;
    _m_dMicrosecStop                    = 0.0f;

#if   xOS_ENV_WIN
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
#elif xOS_ENV_UNIX

#endif

    return true;
}
//--------------------------------------------------------------------------
#if xOS_ENV_UNIX && xOS_FREEBSD

/* static */
std::clock_t
CxProfiler::_liGetClock() {
    /*DEBUG*/

    std::clock_t liRv = static_cast<clock_t>( - 1 );

    rusage ruUsage = {{0}};

    int iRv = ::getrusage(RUSAGE_SELF, &ruUsage);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, static_cast<clock_t>( - 1 ));

    liRv = static_cast<std::clock_t>(ruUsage.ru_utime.tv_sec  + ruUsage.ru_stime.tv_sec) * 1000000 +
            ruUsage.ru_utime.tv_usec + ruUsage.ru_stime.tv_usec;

    return liRv;
}

#endif
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

/* static */
int
CxProfiler::gettimeofday(
    struct timeval  *tv,
    struct timezone *tz
)
{
#if xCOMPILER_MS || defined(_MSC_EXTENSIONS)
    ulonglong_t DELTA_EPOCH_IN_MICROSECS = 11644473600000000Ui64;
#else
    ulonglong_t DELTA_EPOCH_IN_MICROSECS = 11644473600000000ULL;
#endif

    FILETIME    ftTime    = {0};
    ulonglong_t ullRv    = 0ULL;
    static int  s_iTzFlag = 0;

    if (NULL != tv) {
        (void)::GetSystemTimeAsFileTime(&ftTime);

        ullRv |= ftTime.dwHighDateTime;
        ullRv <<= 32ULL;
        ullRv |= ftTime.dwLowDateTime;

        //convert into microseconds
        ullRv /= 10ULL;

        //converting file time to unix epoch
        ullRv -= DELTA_EPOCH_IN_MICROSECS;

        tv->tv_sec  = static_cast<long_t>( ullRv / 1000000UL );
        tv->tv_usec = static_cast<long_t>( ullRv % 1000000UL );
    }

    if (NULL != tz) {
        if (!s_iTzFlag) {
            _tzset();
            ++ s_iTzFlag;
        }

        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime     = _daylight;
    }

    return 0;
}

#endif
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
