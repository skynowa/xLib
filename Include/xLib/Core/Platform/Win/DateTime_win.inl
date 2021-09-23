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
    SYSTEMTIME dateTime {};

    (void_t)::GetLocalTime(&dateTime);
    xTEST_EQ(DateTimeValidator::datetime(dateTime.wYear, dateTime.wMonth, dateTime.wDay,
        dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds), true);

    return DateTime(dateTime.wYear, dateTime.wMonth, dateTime.wDay,
        dateTime.wHour, dateTime.wMinute, dateTime.wSecond, dateTime.wMilliseconds);
}
//-------------------------------------------------------------------------------------------------
/* static */
longlong_t
DateTime::fileToInt64(
    const FILETIME &a_fileTime
)
{
    return Int64ShllMod32(a_fileTime.dwHighDateTime, 32) | a_fileTime.dwLowDateTime;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
DateTime::unixToFile(
    const time_t  a_unixTime,
    FILETIME     *out_fileTime
)
{
    xTEST_NA(a_unixTime);
    xTEST_PTR(out_fileTime);

    // Note that LONGLONG is a 64-bit value
    longlong_t llRv {};

    // This algorithm was found in MSDN
    llRv = Int32x32To64(a_unixTime, 10000000) + 116444736000000000;

    // [out]
    out_fileTime->dwLowDateTime  = static_cast<DWORD>(llRv);
    out_fileTime->dwHighDateTime = static_cast<DWORD>(llRv >> 32);
}
//-------------------------------------------------------------------------------------------------
/* static */
time_t
DateTime::fileToUnix(
    const FILETIME &a_fileTime
)
{
    // TEST: DateTime::fileToUnix()

    const __int64 nanosecsBetweenEpochs = 116444736000000000LL;

    __int64 llRv {};

    llRv = (static_cast<__int64>( a_fileTime.dwHighDateTime ) << 32) + a_fileTime.dwLowDateTime;
    llRv -= nanosecsBetweenEpochs;
    llRv /= 10000000;

    return static_cast<time_t>( llRv );
}
//-------------------------------------------------------------------------------------------------

} // namespace
