/**
 * \file   Functions_win.inl
 * \brief  function macroses
 */


namespace xl::core
{

//-------------------------------------------------------------------------------------------------
struct timezone
    /// for gettimeofday
{
    int_t tz_minuteswest;
    int_t tz_dsttime;
};

uint_t
gettimeofday(
    timeval  *a_tv, ///< minutes W of Greenwich
    timezone *a_tz  ///< type of dst correction
)
{
#if xCOMPILER_MS || defined(_MSC_EXTENSIONS)
    ulonglong_t DELTA_EPOCH_IN_MICROSECS = 11644473600000000Ui64;
#else
    ulonglong_t DELTA_EPOCH_IN_MICROSECS = 11644473600000000ULL;
#endif

    FILETIME     time     {};
    ulonglong_t  ullRv    {};
    static int_t s_tzFlag {};

    if (a_tv != nullptr) {
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

    if (a_tz != nullptr) {
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

} // namespace
