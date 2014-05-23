/**
 * \file  CxDateTime.inl
 * \brief date, time
 */


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*    public: static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline CxDateTime
CxDateTime::_current_impl()
{
    SYSTEMTIME dateTime = {0};

    (void_t)::GetLocalTime(&dateTime);
    xTEST_EQ(CxValidator::datetime(dateTime.wYear, dateTime.wMonth, dateTime.wDay,
        dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds), true);

    return CxDateTime(dateTime.wYear, dateTime.wMonth, dateTime.wDay,
        dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline longlong_t
CxDateTime::filetimeToInt64(
    const FILETIME &a_fileTime
)
{
    return Int64ShllMod32(a_fileTime.dwHighDateTime, 32) | a_fileTime.dwLowDateTime;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxDateTime::unixTimeToFileTime(
    const time_t &a_unixTime,
    FILETIME     *a_fileTime
)
{
    xTEST_NA(a_unixTime);
    xTEST_PTR(a_fileTime);

    longlong_t llRv = 0LL;

    llRv = Int32x32To64(a_unixTime, 10000000) + 116444736000000000;
    a_fileTime->dwLowDateTime  = static_cast<ulong_t>( llRv );
    a_fileTime->dwHighDateTime = llRv >> 32;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline time_t
CxDateTime::fileTimeToUnixTime(
    const FILETIME &a_fileTime
)
{
    // TEST: CxDateTime::fileTimeToUnixTime()

    const __int64 nanosecsBetweenEpochs = 116444736000000000LL;

    __int64 llRv = 0LL;

    llRv = (static_cast<__int64>( a_fileTime.dwHighDateTime ) << 32) + a_fileTime.dwLowDateTime;
    llRv -= nanosecsBetweenEpochs;
    llRv /= 10000000;

    return static_cast<time_t>( llRv );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
