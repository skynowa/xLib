/**
 * \file   Functions_win.inl
 * \brief  function macroses
 */


xNAMESPACE_BEGIN2(xl, core)

//-------------------------------------------------------------------------------------------------
struct timezone
    /// for gettimeofday
{
    int_t tz_minuteswest;
    int_t tz_dsttime;
};

xINLINE int
gettimeofday(
    timeval  *a_tv, ///< minutes W of Greenwich
    timezone *a_tz  ///< type of dst correction
) /* xWARN_UNUSED_RV */
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

xNAMESPACE_END2(xl, core)
