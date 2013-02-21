/**
 * \file   xFunctions.cpp
 * \brief
 */


#include <xLib/Common/xFunctions.h>


xNAMESPACE_BEGIN(NxLib)

//------------------------------------------------------------------------------
#if   xOS_ENV_WIN
    int
    iGetTimeOfDay(
        struct timeval  *a_tv,
        struct timezone *a_tz
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

        if (NULL != a_tv) {
            (void)::GetSystemTimeAsFileTime(&ftTime);

            ullRv |= ftTime.dwHighDateTime;
            ullRv <<= 32ULL;
            ullRv |= ftTime.dwLowDateTime;

            //convert into microseconds
            ullRv /= 10ULL;

            //converting file time to unix epoch
            ullRv -= DELTA_EPOCH_IN_MICROSECS;

            a_tv->tv_sec  = static_cast<long_t>( ullRv / 1000000UL );
            a_tv->tv_usec = static_cast<long_t>( ullRv % 1000000UL );
        }

        if (NULL != a_tz) {
            if (!s_iTzFlag) {
                _tzset();
                ++ s_iTzFlag;
            }

            a_tz->tz_minuteswest = _timezone / 60;
            a_tz->tz_dsttime     = _daylight;
        }

        return 0;
    }
#elif xOS_ENV_UNIX
    xNA;
#endif

//------------------------------------------------------------------------------
#if   xOS_ENV_WIN
        xNA;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        xNA;
    #elif xOS_FREEBSD
        std::clock_t
        liGetClock() {
            rusage ruUsage = {{0}};

            int iRv = ::getrusage(RUSAGE_SELF, &ruUsage);
            xTEST_DIFF(- 1, iRv);

            std::clock_t clkRv =
                static_cast<std::clock_t>( ruUsage.ru_utime.tv_sec  + ruUsage.ru_stime.tv_sec ) * 1000000 +
                ruUsage.ru_utime.tv_usec +
                ruUsage.ru_stime.tv_usec;

            return clkRv;
        }
    #endif
#endif
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

