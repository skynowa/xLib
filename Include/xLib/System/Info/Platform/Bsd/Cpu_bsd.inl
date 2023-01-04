/**
 * \file  Cpu.inl
 * \brief system information
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_num_impl() const
{
    ulong_t ulRv {};

    int_t  mib[]   = {CTL_HW, HW_NCPU};
    size_t resSize = sizeof(ulRv);

    int_t iRv = ::sysctl(mib, static_cast<u_int>( xARRAY_SIZE(mib) ), &ulRv, &resSize, nullptr, 0);
    xTEST_DIFF(iRv, - 1);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Cpu::_vendor_impl() const
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
        // OS_NOT_SUPPORTED: Cpu::cvGetCpuVendor()
        #error xLib: Can not define __cpuid
    #endif
    };

    int_t cpuInfo[4] {};

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
Cpu::_model_impl() const
{
    std::tstring_t sRv;

    int_t       iRv       {- 1};
    std::string value;
    size_t      valueSize {};

    iRv = ::sysctlbyname("hw.model", nullptr, &valueSize, nullptr, 0U);
    xTEST_DIFF(iRv, - 1);
    xTEST_DIFF(valueSize, size_t(0));

    value.resize(valueSize);

    iRv = ::sysctlbyname("hw.model", &value.at(0), &valueSize, nullptr, 0U);
    xTEST_DIFF(iRv, - 1);
    xTEST_EQ(value.size(), valueSize);

    sRv = value;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_speed_impl() const
{
    ulong_t ulRv {};

    ulong_t cpuSpeedMHz     {};
    size_t  cpuSpeedMHzSize = sizeof(cpuSpeedMHz);

    int_t iRv = ::sysctlbyname("hw.clockrate", &cpuSpeedMHz, &cpuSpeedMHzSize, nullptr, 0);
    xTEST_DIFF(iRv, - 1);

    ulRv = cpuSpeedMHz;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_usage_impl() const
{
    double_t       usage              {};

    static ulong_t s_totalOld         {- 1UL};
    static ulong_t s_usedOld          {- 1UL};

    ulong_t        used               {- 1UL};
    ulong_t        total              {- 1UL};

    ulong_t        cpuTime[CPUSTATES] {};
    size_t         cpuTimeSize        = sizeof(cpuTime);

    int_t iRv = ::sysctlbyname("kern.cp_time", &cpuTime, &cpuTimeSize, nullptr, 0);
    xTEST_DIFF(iRv, - 1);

    used  = cpuTime[CP_USER] + cpuTime[CP_NICE] + cpuTime[CP_SYS];
    total = cpuTime[CP_USER] + cpuTime[CP_NICE] + cpuTime[CP_SYS] + cpuTime[CP_IDLE];

    usage = Utils::intSafeDiv(used - s_usedOld, total - s_totalOld) * 100.0;

    s_usedOld  = used;
    s_totalOld = total;

    ulong_t ulRv = Utils::roundIntT<ulong_t>( usage );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
