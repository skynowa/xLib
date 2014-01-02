/**
 * \file   xFunctions.cpp
 * \brief
 */


xNAMESPACE_BEGIN(NxLib)

#if xOS_FREEBSD
    #include <xLib/Core/CxUtils.h>
#endif

//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline int_t
getTimeOfDay(
    timeval  *a_tv,
    timezone *a_tz
)
{
#if xCOMPILER_MS || defined(_MSC_EXTENSIONS)
    ulonglong_t DELTA_EPOCH_IN_MICROSECS = 11644473600000000Ui64;
#else
    ulonglong_t DELTA_EPOCH_IN_MICROSECS = 11644473600000000ULL;
#endif

    FILETIME     time     = {0};
    ulonglong_t  ullRv    = 0ULL;
    static int_t s_tzFlag = 0;

    if (NULL != a_tv) {
        (void_t)::GetSystemTimeAsFileTime(&time);

        ullRv |= time.dwHighDateTime;
        ullRv <<= 32ULL;
        ullRv |= time.dwLowDateTime;

        // convert to microseconds
        ullRv /= 10ULL;

        // converting file time to unix epoch
        ullRv -= DELTA_EPOCH_IN_MICROSECS;

        a_tv->tv_sec  = static_cast<long_t>( ullRv / 1000000UL );
        a_tv->tv_usec = static_cast<long_t>( ullRv % 1000000UL );
    }

    if (NULL != a_tz) {
        if (!s_tzFlag) {
            _tzset();
            ++ s_tzFlag;
        }

        a_tz->tz_minuteswest = _timezone / 60;
        a_tz->tz_dsttime     = _daylight;
    }

    return 0;
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_FREEBSD

inline std::clock_t
clock()
{
    rusage ruUsage; xSTRUCT_ZERO(ruUsage);

    int_t iRv = ::getrusage(RUSAGE_SELF, &ruUsage);
    if (iRv == - 1) {
        return - 1;
    }

    std::clock_t clkRv =
        static_cast<std::clock_t>( ruUsage.ru_utime.tv_sec  + ruUsage.ru_stime.tv_sec ) * 1000000 +
        ruUsage.ru_utime.tv_usec + ruUsage.ru_stime.tv_usec;

    return clkRv;
}

#endif
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

