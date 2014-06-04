/**
 * \file   CxProcessInfo.inl
 * \brief  process information
 */


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_cpuUsage_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: CxProcessInfo::cpuUsage()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_ramUsage_impl() const
{
    ulong_t ulRv = 0UL;

    if (CxProcess::isCurrent( CxProcess::currentId() )) {
        // TODO: CxProcessInfo::ramUsage()
        xNOT_IMPLEMENTED
    } else {
        // TODO: CxProcessInfo::ramUsage()
        xNOT_IMPLEMENTED
    }

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_ioBytes_impl() const
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

    std::tstring_t procPath  = CxString::format(xT("/proc/%lu/io"), _id);

    ulong_t readBytes = 0UL;
    {
        std::tstring_t value = CxPath::procValue(procPath, xT("read_bytes"));
        readBytes = CxString::cast<ulong_t>( value );
    }

    ulong_t writeBytes = 0UL;
    {
        std::tstring_t value = CxPath::procValue(procPath, xT("write_bytes"));
        writeBytes = CxString::cast<ulong_t>( value );
    }

    ulRv = readBytes + writeBytes;

    // xTRACEV("\readBytes: %lu, writeBytes: %lu", readBytes, writeBytes);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_parentId_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: CxProcessInfo::parentId()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline long_t
CxProcessInfo::_commandLineArgsMax_impl()
{
    long_t liRv = ::sysconf(_SC_ARG_MAX) / sizeof(std::tstring_t::value_type);
    xTEST_DIFF(liRv, - 1L);

    return liRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
