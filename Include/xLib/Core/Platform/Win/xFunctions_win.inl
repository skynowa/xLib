/**
 * \file   xFunctions_win.inl
 * \brief  function macroses
 */


xNAMESPACE_BEGIN2(xlib, core)

//-------------------------------------------------------------------------------------------------
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

    if (a_tv != xPTR_NULL) {
        (void_t)::GetSystemTimeAsFileTime(&time);

        ullRv |= time.dwHighDateTime;
        ullRv <<= 32ULL;
        ullRv |= time.dwLowDateTime;

        // convert to microseconds
        ullRv /= 10ULL;

        // convert file time to unix epoch
        ullRv -= DELTA_EPOCH_IN_MICROSECS;

        a_tv->tv_sec  = static_cast<long_t>( ullRv / 1000000UL );
        a_tv->tv_usec = static_cast<long_t>( ullRv % 1000000UL );
    }

    if (a_tz != xPTR_NULL) {
        if (!s_tzFlag) {
            _tzset();
            ++ s_tzFlag;
        }

        a_tz->tz_minuteswest = _timezone / 60;
        a_tz->tz_dsttime     = _daylight;
    }

    return 0;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
