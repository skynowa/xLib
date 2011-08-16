/****************************************************************************
* Class name:  CxProfiler
* Description: code profiling (msec)
* File name:   CxProfiler.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.04.2009 16:59:44
*
*****************************************************************************/


#include <xLib/Debug/CxProfiler.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxStdioFile.h>
#include <xLib/Sync/CxThread.h>


/****************************************************************************
* public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxProfiler
CxProfiler::CxProfiler(
    const EMode cpmMode
) :
    _m_bRes      (FALSE),
    _m_pmModeNow (cpmMode),
    _m_bIsStarted(FALSE),
    _flLog       (CxFileLog::lsDefaultSize)
{
    _bResetData();
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ~CxProfiler
CxProfiler::~CxProfiler() {
    if (false == _flLog.sGetFilePath().empty()) {
        _m_bRes = _flLog.bWrite(xT("----------------------------------------"));
        /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
    }
}
//---------------------------------------------------------------------------
//DONE: bSetLogPath (set log path)
BOOL
CxProfiler::bSetLogPath(
    const tString &csLogPath
)
{
    /*DEBUG*/

    _m_bRes = _flLog.bSetFilePath(csLogPath);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetLogPath (get log path)
const tString &
CxProfiler::sGetLogPath() const {
    /*DEBUG*/

    return _flLog.sGetFilePath();
}
//--------------------------------------------------------------------------
//DONE: bStart (start measurement)
BOOL
CxProfiler::bStart() {
    /*DEBUG*/xASSERT_RET(FALSE == _m_bIsStarted, FALSE);

    _m_bRes = _bResetData();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    #if xTODO
        _m_bRes = CxThread::bSetPriority(CxThread::ulGetCurrId(), CxThread::tpTimeCritical);
        /*DEBUG*/xASSERT(FALSE != _m_bRes);
    #endif

    CxThread::bSleep(10UL);

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

        #if defined(xOS_WIN)
            case pmTickCount: {
                    _m_ulTicksStart = ::GetTickCount();
                    /*DEBUG*/// n/a
                }
                break;

            case pmPerformanceCount: {
                    _m_bRes = ::QueryPerformanceFrequency(&_m_liCountersPerfFreq);
                    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

                    _m_bRes = ::QueryPerformanceCounter(&_m_liCountersStart);
                    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
                }
                break;

            case pmThreadTimes: {
                    _m_bRes = ::GetThreadTimes(CxThread::hGetCurrHandle(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStart, &_m_lpUserTimeStart);
                    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
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
//DONE: bStop (stop measurement)
BOOL
CxProfiler::bStop(
    LPCTSTR pcszComment, ...
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_bIsStarted, FALSE);

    tString sTimeString = xT("0:00:00:000");

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

        #if defined(xOS_WIN)
            case pmTickCount: {
                    _m_ulTicksStop = ::GetTickCount();
                    /*DEBUG*/// n/a

                    sTimeString = CxDateTime(_m_ulTicksStop - _m_ulTicksStart).sFormat(CxDateTime::ftTime);
                }
                break;

            case pmPerformanceCount: {
                    _m_bRes = ::QueryPerformanceCounter(&_m_liCountersStop);
                    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

                    sTimeString = CxDateTime((_m_liCountersStop.QuadPart - _m_liCountersStart.QuadPart) * 1000 / _m_liCountersPerfFreq.QuadPart).sFormat(CxDateTime::ftTime);
                }
                break;

            case pmThreadTimes: {
                    _m_bRes = ::GetThreadTimes(CxThread::hGetCurrHandle(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStop, &_m_lpUserTimeStop);
                    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

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
    tString sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszComment);

    sRes = CxString::sFormatV(pcszComment, palArgs);

    xVA_END(palArgs);

    //-------------------------------------
    //write to log
    _m_bRes = _flLog.bWrite(xT("%s: %s"), sTimeString.c_str(), sRes.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bIsStarted = FALSE;

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE: bPulse (stop, start measurement)
BOOL
CxProfiler::bPulse(
    LPCTSTR pcszComment, ...
)
{
    //-------------------------------------
    //format comment
    tString sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszComment);

    sRes = CxString::sFormatV(pcszComment, palArgs);

    xVA_END(palArgs);

    //-------------------------------------
    //stop, start
    _m_bRes = bStop(sRes.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    _m_bRes = bStart();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bResetData (reset all class data)
BOOL
CxProfiler::_bResetData() {
    #if xTODO
        _m_bRes = CxThread::bSetPriority(CxThread::ulGetCurrId(), CxThread::tpNormal);
        /*DEBUG*/xASSERT(FALSE != _m_bRes);
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

#if defined(xOS_WIN)
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
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//--------------------------------------------------------------------------
#if defined(xOS_FREEBSD)
//DONE: _liGetClock (determine processor time used for FreeBSD)
//NOTE: http://bugs.vcmi.eu/view.php?id=719
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
#if defined(xOS_WIN)

//DONE: gettimeofday (like unix gettimeofday)
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
