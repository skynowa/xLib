/**
 * \file  SystemInfo.inl
 * \brief system information
 */


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_distro_impl() const
{
    return formatOs();
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_numOfCpus_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: [skynowa] SystemInfo::_numOfCpus_impl()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_cpuVendor_impl() const
{
    std::tstring_t value;

    // TODO: [skynowa] SystemInfo::_cpuVendor_impl()
    xNOT_IMPLEMENTED

    return value;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_cpuModel_impl() const
{
    std::tstring_t sRv;

    // TODO: [skynowa] SystemInfo::_cpuModel_impl()
    xNOT_IMPLEMENTED

    return sRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_cpuSpeed_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: [skynowa] SystemInfo::_cpuSpeed_impl()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_cpuUsage_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: [skynowa] SystemInfo::_cpuUsage_impl()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
SystemInfo::_ramTotal_impl() const
{
    ulonglong_t ullRv = 0ULL;

    // TODO: [skynowa] SystemInfo::_ramTotal_impl()
    xNOT_IMPLEMENTED

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
SystemInfo::_ramAvailable_impl() const
{
    ulonglong_t ullRv = 0ULL;

    // TODO: [skynowa] SystemInfo::_ramAvailable_impl()
    xNOT_IMPLEMENTED

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_ramUsage_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: [skynowa] SystemInfo::_ramUsage_impl()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
