/****************************************************************************
* Class name:  CxProfiler
* Description: code profiling
* File name:   CxProfiler.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.04.2009 16:59:44
*
*****************************************************************************/


#include <xLib/Debug/CxProfiler.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxStdioFile.h>


/****************************************************************************
* public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxProfiler (constructor)
CxProfiler::CxProfiler(const tString &csLogFilePath, EMode pmMode) :
	_m_bRes      (FALSE),
    _m_pmModeNow (pmMode),
    _m_bIsStarted(FALSE),
	_flLog       (csLogFilePath, CxFileLog::lsDefaultSize)
{
	/*DEBUG*/xASSERT_DO(false == csLogFilePath.empty(), return);
#if defined(xOS_WIN)
	/*DEBUG*/xASSERT_DO(pmTickCount == pmMode || pmPerformanceCount == pmMode || pmThreadTimes == pmMode || pmClock == pmMode || pmTime == pmMode, return);
#elif defined(xOS_LINUX)
	/*DEBUG*/xASSERT_DO(pmGetTimeOfDay == pmMode || pmClock == pmMode || pmTime == pmMode, return);
#endif
	
	_m_bRes = _flLog.bWrite(xT("----------------------------------------"));
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxProfiler (destructor)
CxProfiler::~CxProfiler() {
	_m_bRes = _flLog.bWrite(xT("----------------------------------------"));
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//--------------------------------------------------------------------------
//DONE: bStart (start measurement)
BOOL
CxProfiler::bStart() {
	/*DEBUG*/xASSERT_RET(FALSE == _m_bIsStarted, FALSE);
	
	_m_bRes = _bResetData();
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
	
#if defined(xOS_WIN)
    _m_bRes = ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    /*DEBUG*/xASSERT(FALSE != _m_bRes);

    ::Sleep(100);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
#endif	

    switch (_m_pmModeNow) {
        case pmClock: {
                _m_ctClocksStart = std::clock();
                /*DEBUG*/xASSERT_RET(- 1 != _m_ctClocksStart, FALSE);
            }
            break;

		case pmTime: {
				_m_dtTimesStart = CxDateTime::dtGetCurrent();
				/*DEBUG*/// n/a
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
                    _m_bRes = ::GetThreadTimes(::GetCurrentThread(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStart, &_m_lpUserTimeStart);
                    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
                }
                break;

        #elif defined(xOS_LINUX)
            case pmGetTimeOfDay: {
                    struct timeval tv = {0};
                    gettimeofday(&tv, NULL);

                    _m_dMicrosecStart = static_cast<double>( tv.tv_sec ) + static_cast<double>( tv.tv_usec ) / 1000000.0;
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
CxProfiler::bStop(LPCTSTR pcszComment, ...) {
	/*DEBUG*/xASSERT_RET(FALSE != _m_bIsStarted, FALSE);

	tString sTimeString = xT("0:00:00:000");
	
	switch (_m_pmModeNow) {
        case pmClock: {
                _m_ctClocksStop = std::clock();
                /*DEBUG*/xASSERT_RET(- 1 != _m_ctClocksStop, FALSE);

                sTimeString = CxDateTime( (_m_ctClocksStop - _m_ctClocksStart) / (CLOCKS_PER_SEC / 1000) ).sFormat(CxDateTime::ftTime);
            }
            break;

		case pmTime: {
				_m_dtTimesStop = CxDateTime::dtGetCurrent();
				/*DEBUG*/// n/a

				//--/*DEBUG*/xASSERT_MSG(_m_dtTimesStop >= _m_dtTimesStart, CxString::sFormat(xT("_m_dtTimesStop: %s, _m_dtTimesStart: %s"), _m_dtTimesStop.sFormat(CxDateTime::ftDateTime).c_str(), _m_dtTimesStart.sFormat(CxDateTime::ftDateTime).c_str()));
                sTimeString = (_m_dtTimesStop - _m_dtTimesStart).sFormat(CxDateTime::ftTime);
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
                    _m_bRes = ::GetThreadTimes(::GetCurrentThread(), &_m_lpCreationTime, &_m_lpExitTime, &_m_lpKernelTimeStop, &_m_lpUserTimeStop);
                    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

                    sTimeString = CxDateTime((CxDateTime::i64FiletimeToInt64(_m_lpUserTimeStop) - CxDateTime::i64FiletimeToInt64(_m_lpUserTimeStart)) / 10000).sFormat(CxDateTime::ftTime);
                }
                break;

        #elif defined(xOS_LINUX)
            case pmGetTimeOfDay: {
                    struct timeval tv = {0};
                    gettimeofday(&tv, NULL);

                    _m_dMicrosecStop = static_cast<double>( tv.tv_sec ) + static_cast<double>( tv.tv_usec ) / 1000000.0;

                    sTimeString = CxString::sFormat(xT("%.6lf (sec)"), _m_dMicrosecStop - _m_dMicrosecStart);
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

	va_list palArgs = NULL;
	va_start(palArgs, pcszComment);

	sRes = CxString::sFormatV(pcszComment, palArgs);

	va_end(palArgs);
	
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
CxProfiler::bPulse(LPCTSTR pcszComment, ...) {
	//-------------------------------------
	//format comment
	tString sRes;

	va_list palArgs = NULL;
	va_start(palArgs, pcszComment);

	sRes = CxString::sFormatV(pcszComment, palArgs);

	va_end(palArgs);
	
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
*	private	
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: _bResetData (reset all class data)
BOOL
CxProfiler::_bResetData() {
#if defined(xOS_WIN)
    _m_bRes = ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_NORMAL);
    /*DEBUG*/xASSERT(FALSE != _m_bRes);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
#endif

    _m_bIsStarted                       = FALSE;
	
    //pmClock
    xSTRUCT_ZERO(_m_ctClocksStart);
    xSTRUCT_ZERO(_m_ctClocksStop);

	//pmTime
	//_m_dtTimesStart - n/a
	//_m_dtTimesStop  - n/a

#if defined(xOS_WIN)
    //pmGetTickCount
    _m_ulTicksStart                     = 0;
    _m_ulTicksStop                      = 0;

    //pmPerformanceCount
    _m_liCountersPerfFreq.QuadPart      = 0;
    _m_liCountersStart.QuadPart         = 0;
    _m_liCountersStop.QuadPart          = 0;

    //pmThreadTimes
    _m_lpCreationTime.dwLowDateTime     = 0;
    _m_lpCreationTime.dwHighDateTime    = 0;
    _m_lpExitTime.dwLowDateTime         = 0;
    _m_lpExitTime.dwHighDateTime        = 0;
    _m_lpKernelTimeStart.dwLowDateTime  = 0;
    _m_lpKernelTimeStart.dwHighDateTime = 0;
    _m_lpUserTimeStart.dwLowDateTime    = 0;
    _m_lpUserTimeStart.dwHighDateTime   = 0;
    _m_lpKernelTimeStop.dwLowDateTime   = 0;
    _m_lpKernelTimeStop.dwHighDateTime  = 0;
    _m_lpUserTimeStop.dwLowDateTime     = 0;
    _m_lpUserTimeStop.dwHighDateTime    = 0;
#elif defined(xOS_LINUX)

    //pmGetTimeOfDay
    _m_dMicrosecStart                   = 0.0;
    _m_dMicrosecStop                    = 0.0;
#endif

	return TRUE;
}
//--------------------------------------------------------------------------


/*
#include <time.h>
...
...
time_t startTime;
startTime = time(NULL);
// do some long process...
time_t stopTime;
stopTime = time(NULL);
time_t elapsedTime = stopTime - startTime;
printf("The number elapsed seconds is %ld",elapsedTime);
...
*/

/*
__int64 GetCPUClock()
{
    __int64 res;
    __asm
    {
        rdtsc
        mov dword ptr res, eax
        mov dword ptr res+4, edx
    }
    return res;
}

__int64 g_FuncTime = 0; //���� ����� �������� ��������� ����� ���������� F.

BOOL F()
{
    __int64 Time = GetCPUClock();
    ///...
    __int64 Difference = GetCPUClock() - Time;
    g_FuncTime += Difference;
}


#include <stdio.h>
INT main()
{

    __int64 Time = GetCPUClock();
    //����� ����
    __int64 Difference = GetCPUClock() - Time;

    printf("%f\n", (double)Difference);
}
*/
