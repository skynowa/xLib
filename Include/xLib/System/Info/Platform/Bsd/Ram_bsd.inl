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
    ulonglong_t ullRv {};

    ulonglong_t ramTotal     {};

    int_t       mib[]        = {CTL_HW, HW_PHYSMEM};
    size_t      ramTotalSize = sizeof(ramTotal);

    int_t iRv = ::sysctl(mib, 2, &ramTotal, &ramTotalSize, nullptr, 0);
    xTEST_DIFF(iRv, - 1);

    ullRv = ramTotal;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
Ram::_available_impl() const
{
    ulonglong_t availPhysPages     {};
    size_t      availPhysPagesSize = sizeof(availPhysPages);

    int_t iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &availPhysPages,
        &availPhysPagesSize, nullptr, 0);
    xTEST_DIFF(iRv, - 1);

    ulonglong_t ullRv = availPhysPages * pageSize();

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Ram::_usage_impl() const
{
    ulonglong_t ramTotal {};
    {
        int_t  mib[]        = {CTL_HW, HW_PHYSMEM};
        size_t ramTotalSize = sizeof(ramTotal);

        int_t iRv = ::sysctl(mib, 2, &ramTotal, &ramTotalSize, nullptr, 0);
        xTEST_DIFF(iRv, - 1);
    }

    ulonglong_t ramFree {};
    {
        ulonglong_t availPhysPages     {};
        size_t      availPhysPagesSize = sizeof(availPhysPages);

        int_t iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &availPhysPages,
            &availPhysPagesSize, nullptr, 0);
        xTEST_DIFF(iRv, - 1);

        ramFree = availPhysPages * pageSize();
    }

    culonglong_t ramUsage = ramTotal - ramFree;

    ulong_t ulRv = static_cast<ulong_t>( Utils::intSafeDiv(ramUsage * 100.0, ramTotal) );
    xTEST_EQ(ramTotal, ramUsage + ramFree);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
