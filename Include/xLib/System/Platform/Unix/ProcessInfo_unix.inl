/**
 * \file   ProcessInfo.inl
 * \brief  process information
 */


namespace xl::system
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::_cpuUsage_impl() const
{
    ulong_t ulRv {};

    // TODO: [skynowa] ProcessInfo::cpuUsage()
    // xTRACE_NOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::_ramUsage_impl() const
{
    ulong_t ulRv {};

    if (Process::isCurrent( Process::currentId() )) {
        // TODO: [skynowa] ProcessInfo::ramUsage()
        // xTRACE_NOT_IMPLEMENTED
    } else {
        // TODO: [skynowa] ProcessInfo::ramUsage()
        // xTRACE_NOT_IMPLEMENTED
    }

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::_ioBytes_impl() const
{
    ulong_t ulRv = 0UL;

#if xCOMMENT
    "/proc/[pid]/io"

    1366    rchar: 323934931
    1367    wchar: 323929600
    1368    syscr: 632687
    1369    syscw: 632675
    1370    read_bytes: 0
    1371    write_bytes: 323932160
    1372    cancelled_write_bytes: 0
#endif

    std::tstring_t procPath  = Format::str(xT("/proc/{}/io"), _id);

    ulong_t readBytes {};
    {
        std::tstring_t value = Path::procValue(procPath, xT("read_bytes"));
        readBytes = String::cast<ulong_t>( value );
    }

    ulong_t writeBytes {};
    {
        std::tstring_t value = Path::procValue(procPath, xT("write_bytes"));
        writeBytes = String::cast<ulong_t>( value );
    }

    ulRv = readBytes + writeBytes;

    // xTRACEV("\readBytes: %lu, writeBytes: %lu", readBytes, writeBytes);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
ProcessInfo::_parentId_impl() const
{
    ulong_t ulRv {};

    // TODO: [skynowa] ProcessInfo::parentId()
    // xTRACE_NOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
long_t
ProcessInfo::_commandLineArgsMax_impl()
{
    long_t liRv = ::sysconf(_SC_ARG_MAX) / static_cast< ::ssize_t >( sizeof(std::tstring_t::value_type) );
    xTEST_DIFF(liRv, - 1L);

    return liRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
