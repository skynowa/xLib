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
    SYSTEM_INFO sysInfo {};

    (void_t)::GetNativeSystemInfo(&sysInfo);

    ulong_t ulRv = sysInfo.dwNumberOfProcessors;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_currentNum_impl() const
{
    using func_t = DWORD (WINAPI *)(void_t);

    Dll dll;
    dll.load(xT("kernel32.dll"));

    bool_t bRv = dll.isProcExists(xT("GetCurrentProcessorNumber"));
    xCHECK_RET(!bRv, 0UL);

    auto func = dll.proc<func_t>(xT("GetCurrentProcessorNumber"));
    xTEST_PTR(func);

    ulong_t ulRv = func();
    xTEST_NA(ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Cpu::_vendor_impl() const
{
    std::tstring_t value;

#if   xCOMPILER_MINGW || xCOMPILER_MS
    int_t  cpuInfo[4] {};
    char   man[13]    {};

    (void_t)::__cpuid(cpuInfo, 0);

    *reinterpret_cast<int_t *>( &man[0] ) = cpuInfo[1];
    *reinterpret_cast<int_t *>( &man[4] ) = cpuInfo[3];
    *reinterpret_cast<int_t *>( &man[8] ) = cpuInfo[2];

    value = std::string(man);
    xTEST(!value.empty());
#endif

    return value;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Cpu::_model_impl() const
{
    std::tstring_t sRv;

#if   xCOMPILER_MINGW || xCOMPILER_MS
    char man[13] {};

    // get highest feature
    {
        int_t cpuInfo[4] {};

        (void_t)::__cpuid(cpuInfo, 0);

        *reinterpret_cast<int_t *>( &man[0] ) = cpuInfo[1];
        *reinterpret_cast<int_t *>( &man[4] ) = cpuInfo[3];
        *reinterpret_cast<int_t *>( &man[8] ) = cpuInfo[2];
    }

    // get highest extended feature
    int_t cpuInfo[4] {};

    (void_t)::__cpuid(cpuInfo, 0x80000000);

    uint_t highestFeatureEx = static_cast<uint_t>( cpuInfo[0] );

    // get processor brand name
    if (highestFeatureEx >= 0x80000004) {
        char buff[49] {};

        (void_t)::__cpuid(reinterpret_cast<int_t *>( &buff[0]  ), 0x80000002);
        (void_t)::__cpuid(reinterpret_cast<int_t *>( &buff[16] ), 0x80000003);
        (void_t)::__cpuid(reinterpret_cast<int_t *>( &buff[32] ), 0x80000004);

        std::tstring_t cpuName = String::trimSpace( xA2T(buff) );

        sRv = Format::str(xT("{} ({})"), cpuName, man);
    } else {
        sRv = Format::str(xT("{}"), man);
    }
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_speed_impl() const
{
    DWORD cpuSpeedMHz {};
    DWORD buffSize    = sizeof(cpuSpeedMHz);
    HKEY  key         {};

    LONG lRv = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, xT("HARDWARE\\DESCRIPTION\\System\\"
        "CentralProcessor\\0"), 0UL, KEY_READ, &key);
    xTEST_EQ(lRv, ERROR_SUCCESS);

    lRv = ::RegQueryValueEx(key, xT("~MHz"), nullptr, nullptr, reinterpret_cast<LPBYTE>( &cpuSpeedMHz ),
        &buffSize);
    xTEST_EQ(lRv, ERROR_SUCCESS);

    lRv = ::RegCloseKey(key);    key = nullptr;
    xTEST_EQ(lRv, ERROR_SUCCESS);

    ulong_t ulRv = cpuSpeedMHz;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
Cpu::_usage_impl() const
{
    double                dRv            {};

    FILETIME              sysIdle        {};
    FILETIME              sysKernel      {};
    FILETIME              sysUser        {};

    ULARGE_INTEGER        ulSysIdle      {};
    ULARGE_INTEGER        ulSysKernel    {};
    ULARGE_INTEGER        ulSysUser      {};

    static ULARGE_INTEGER s_sysIdleOld   {};
    static ULARGE_INTEGER s_sysKernelOld {};
    static ULARGE_INTEGER s_sysUserOld   {};

    BOOL blRv = ::GetSystemTimes(&sysIdle, &sysKernel, &sysUser);
    xTEST_DIFF(blRv, FALSE);

    (void_t)::CopyMemory(&ulSysIdle,   &sysIdle,   sizeof(sysIdle));
    (void_t)::CopyMemory(&ulSysKernel, &sysKernel, sizeof(sysKernel));
    (void_t)::CopyMemory(&ulSysUser,   &sysUser,   sizeof(sysUser));

    dRv = Utils::intSafeDiv(
                (ulSysKernel.QuadPart - s_sysKernelOld.QuadPart) +
                (ulSysUser.QuadPart   - s_sysUserOld.QuadPart)   -
                (ulSysIdle.QuadPart   - s_sysIdleOld.QuadPart)
                ,
                (ulSysKernel.QuadPart - s_sysKernelOld.QuadPart) +
                (ulSysUser.QuadPart   - s_sysUserOld.QuadPart)
    ) * 100.0;

    s_sysIdleOld.QuadPart   = ulSysIdle.QuadPart;
    s_sysUserOld.QuadPart   = ulSysUser.QuadPart;
    s_sysKernelOld.QuadPart = ulSysKernel.QuadPart;

    ulong_t ulRv = static_cast<ulong_t>( dRv );

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
