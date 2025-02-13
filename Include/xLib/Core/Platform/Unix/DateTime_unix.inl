/**
 * \file  DateTime.inl
 * \brief date, time
 */


namespace xl::core
{

/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
DateTime
DateTime::_current_impl()
{
    // get msec
    timeval timeNow {};

    int_t iRv = ::gettimeofday(&timeNow, nullptr);
    xTEST_DIFF(iRv, - 1);

    // get datetime
    std::tm dateTime {};
    std::tm *dtRv = ::localtime_r(&timeNow.tv_sec, &dateTime);
    xTEST_PTR(dtRv);

    // set datetime
    cint_t year   = dateTime.tm_year + 1900;
    cint_t month  = dateTime.tm_mon  + 1;
    cint_t day    = dateTime.tm_mday;
    cint_t hour   = dateTime.tm_hour;
    cint_t minute = dateTime.tm_min;
    cint_t second = dateTime.tm_sec;
    cint_t msec   = static_cast<int_t>( static_cast<double>(timeNow.tv_usec) * 0.001 );

    return DateTime(year, month, day, hour, minute, second, msec);
}
//-------------------------------------------------------------------------------------------------

} // namespace
