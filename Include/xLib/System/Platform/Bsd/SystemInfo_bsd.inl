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
ulong_t
SystemInfo::_numOfCpus_impl() const
{
    ulong_t ulRv = 0UL;

    int_t  mib[]   = {CTL_HW, HW_NCPU};
    size_t resSize = sizeof(ulRv);

    int_t iRv = ::sysctl(mib, static_cast<u_int>( xARRAY_SIZE(mib) ), &ulRv, &resSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_cpuVendor_impl() const
{
    std::tstring_t value;

    // Use gcc 4.4 provided cpuid intrinsic
    // 32 bit fpic requires ebx be preserved
    struct _Functor
    {
    #if (defined(__pic__) || defined(__APPLE__)) && defined(__i386__)
        static void_t
        __cpuid(
            int_t  a_cpuInfo[4],
            cint_t a_infoType)
        {
            __asm__ volatile (
                "mov %%ebx, %%edi\n"
                "cpuid\n"
                "xchg %%edi, %%ebx\n"
                : "=a"(a_cpuInfo[0]), "=D"(a_cpuInfo[1]), "=c"(a_cpuInfo[2]), "=d"(a_cpuInfo[3])
                : "a"(a_infoType)
            );
        }
    #elif defined(__i386__) || defined(__x86_64__)
        static void_t
        __cpuid(
            int_t  a_cpuInfo[4],
            cint_t a_infoType)
        {
            __asm__ volatile (
                "cpuid\n"
                : "=a"(a_cpuInfo[0]), "=b"(a_cpuInfo[1]), "=c"(a_cpuInfo[2]), "=d"(a_cpuInfo[3])
                : "a"(a_infoType)
            );
        }
    #else
        // OS_NOT_SUPPORTED: SystemInfo::cvGetCpuVendor()
        #error xLib: Can not define __cpuid
    #endif
    };

    int_t cpuInfo[4] = {0};

    (void_t)_Functor::__cpuid(cpuInfo, 0);

    cpuInfo[0] = cpuInfo[1];  // Reorder output
    cpuInfo[1] = cpuInfo[3];
    cpuInfo[2] = cpuInfo[2];
    cpuInfo[3] = 0;

    value = std::string(Utils::reinterpretCastT<char *>( &cpuInfo[0] ));
    xTEST_EQ(value.empty(), false);

    return value;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_cpuModel_impl() const
{
    std::tstring_t sRv;

    int_t       iRv       = - 1;
    std::string value;
    size_t      valueSize = 0;

    iRv = ::sysctlbyname("hw.model", xPTR_NULL, &valueSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);
    xTEST_DIFF(valueSize, size_t(0));

    value.resize(valueSize);

    iRv = ::sysctlbyname("hw.model", &value.at(0), &valueSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);
    xTEST_EQ(value.size(), valueSize);

    sRv = value;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_cpuSpeed_impl() const
{
    ulong_t ulRv = 0UL;

    ulong_t cpuSpeedMHz     = 0UL;
    size_t  cpuSpeedMHzSize = sizeof(cpuSpeedMHz);

    int_t iRv = ::sysctlbyname("hw.clockrate", &cpuSpeedMHz, &cpuSpeedMHzSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    ulRv = cpuSpeedMHz;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_cpuUsage_impl() const
{
    double         cpuUsage           = 0.0;

    static ulong_t s_totalOld         = - 1UL;
    static ulong_t s_usedOld          = - 1UL;

    ulong_t        used               = - 1UL;
    ulong_t        total              = - 1UL;

    ulong_t        cpuTime[CPUSTATES] = {0};
    size_t         cpuTimeSize        = sizeof(cpuTime);

    int_t iRv = ::sysctlbyname("kern.cp_time", &cpuTime, &cpuTimeSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    used       = cpuTime[CP_USER] + cpuTime[CP_NICE] + cpuTime[CP_SYS];
    total      = cpuTime[CP_USER] + cpuTime[CP_NICE] + cpuTime[CP_SYS] + cpuTime[CP_IDLE];

    cpuUsage   = Utils::safeDivT(used - s_usedOld, total - s_totalOld) * 100.0;

    s_usedOld  = used;
    s_totalOld = total;

    ulong_t ulRv = Utils::roundIntT<ulong_t>( cpuUsage );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
SystemInfo::_ramTotal_impl() const
{
    ulonglong_t ullRv = 0ULL;

    ulonglong_t ramTotal     = 0ULL;

    int_t       mib[]        = {CTL_HW, HW_PHYSMEM};
    size_t      ramTotalSize = sizeof(ramTotal);

    int_t iRv = ::sysctl(mib, 2, &ramTotal, &ramTotalSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    ullRv = ramTotal;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
SystemInfo::_ramAvailable_impl() const
{
    ulonglong_t availPhysPages     = 0ULL;
    size_t      availPhysPagesSize = sizeof(availPhysPages);

    int_t iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &availPhysPages,
        &availPhysPagesSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    ulonglong_t ullRv = availPhysPages * pageSize();

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_ramUsage_impl() const
{
    ulonglong_t ramTotal = 0ULL;
    {
        int_t  mib[]        = {CTL_HW, HW_PHYSMEM};
        size_t ramTotalSize = sizeof(ramTotal);

        int_t iRv = ::sysctl(mib, 2, &ramTotal, &ramTotalSize, xPTR_NULL, 0);
        xTEST_DIFF(iRv, - 1);
    }

    ulonglong_t ramFree = 0ULL;
    {
        ulonglong_t availPhysPages     = 0ULL;
        size_t      availPhysPagesSize = sizeof(availPhysPages);

        int_t iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &availPhysPages,
            &availPhysPagesSize, xPTR_NULL, 0);
        xTEST_DIFF(iRv, - 1);

        ramFree = availPhysPages * pageSize();
    }

    ulonglong_t ramUsage = ramTotal - ramFree;

    ulong_t ulRv = static_cast<ulong_t>( Utils::safeDivT(ramUsage * 100.0, ramTotal) );
    xTEST_EQ(ramTotal, ramUsage + ramFree);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
