/**
 * \file  Ram.inl
 * \brief system information
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulonglong_t
Ram::_total_impl() const
{
    MEMORYSTATUSEX status {};
    status.dwLength = sizeof(status);

    BOOL blRv = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(blRv, FALSE);

    ulonglong_t ullRv = status.ullTotalPhys;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
Ram::_available_impl() const
{
    MEMORYSTATUSEX status {};
    status.dwLength = sizeof(status);

    BOOL blRv = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(blRv, FALSE);

    ulonglong_t ullRv = status.ullAvailPhys;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Ram::_usage_impl() const
{
    MEMORYSTATUSEX status {};
    status.dwLength = sizeof(status);

    BOOL blRv = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(blRv, FALSE);

    ulong_t ulRv = status.dwMemoryLoad;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
