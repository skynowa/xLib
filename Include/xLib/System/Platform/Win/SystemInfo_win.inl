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
SystemInfo::OsType
SystemInfo::_os_impl()
{
    OsType otRv = otUnknown;

    OSVERSIONINFO info = {0};
    info.dwOSVersionInfoSize = sizeof(info);

    BOOL blRv = ::GetVersionEx(&info);
    xTEST_DIFF(blRv, FALSE);

    switch (info.dwPlatformId) {
    case VER_PLATFORM_WIN32s:
        otRv = otWindows3;
        break;
    case VER_PLATFORM_WIN32_WINDOWS:
        xCHECK_DO(info.dwMinorVersion == 0UL,  otRv = otWindows95; break);
        xCHECK_DO(info.dwMinorVersion == 10UL, otRv = otWindows98; break);
        xCHECK_DO(info.dwMinorVersion == 90UL, otRv = otWindows98; break);
        break;
    case VER_PLATFORM_WIN32_NT:
        xCHECK_DO(info.dwMajorVersion <= 4UL,                               otRv = otWindowsNT;              break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 0UL, otRv = otWindows2000;            break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 1UL, otRv = otWindowsXP;              break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = otWindowsXPProx64Edition; break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = otWindowsServer2003;      break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = otWindowsHomeServer;      break);
        xCHECK_DO(info.dwMajorVersion == 5UL && info.dwMinorVersion == 2UL, otRv = otWindowsServer2003R2;    break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 0UL, otRv = otWindowsVista;           break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 0UL, otRv = otWindowsServer2008;      break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 1UL, otRv = otWindowsServer2008R2;    break);
        xCHECK_DO(info.dwMajorVersion == 6UL && info.dwMinorVersion == 1UL, otRv = otWindows7;               break);

        // for unknown windows/newest windows version
        otRv = otUnknown;
        break;
    default:
        otRv = otUnknown;
        break;
    }

    _osType = otRv;

    return otRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_formatOs_impl()
{
    std::tstring_t sRv;

    OsType type = (_osType == otUnknown) ? os() : _osType;
    switch (type) {
    case otWindows3:
        sRv = xT("Windows 3.1");
        break;
    case otWindows95:
        sRv = xT("Windows 95");
        break;
    case otWindows98:
        sRv = xT("Windows 98");
        break;
    case otWindowsNT:
        sRv = xT("Windows NT 4.0");
        break;
    case otWindows2000:
        sRv = xT("Windows 2000");
        break;
    case otWindowsXP:
        sRv = xT("Windows XP");
        break;
    case otWindowsXPProx64Edition:
        sRv = xT("Windows XP Pro x64 Edition");
        break;
    case otWindowsServer2003:
        sRv = xT("Windows Server 2003");
        break;
    case otWindowsHomeServer:
        sRv = xT("Windows Home Server");
        break;
    case otWindowsServer2003R2:
        sRv = xT("Windows Server 2003 R2");
        break;
    case otWindowsVista:
        sRv = xT("Windows Vista");
        break;
    case otWindowsServer2008:
        sRv = xT("Windows Server 2008");
        break;
    case otWindowsServer2008R2:
        sRv = xT("Windows Server 2008 R2");
        break;
    case otWindows7:
        sRv = xT("Windows 7");
        break;
    default:
        sRv = Const::strUnknown();
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_distro_impl() const
{
    return formatOs();
}
//-------------------------------------------------------------------------------------------------
SystemInfo::OsArch
SystemInfo::_osArch_impl()
{
    OsArch oaRv = oaUnknown;

#if   xARCH_BITS_32
    BOOL isFuncExist = FALSE;
    {
        Dll dll;

        dll.load(xT("kernel32.dll"));
        isFuncExist = dll.isProcExists(xT("IsWow64Process"));
    }

    BOOL is64BitOs      = FALSE;
    BOOL isWow64Process = ::IsWow64Process(::GetCurrentProcess(), &is64BitOs);

    oaRv = (isFuncExist && isWow64Process && is64BitOs) ? oa64bit : oa32bit;
#elif xARCH_BITS_64
    oaRv = oa64bit;
#else
    // 64-bit Windows does not support Win16
    oaRv = oaUnknown;
#endif

    _osArch = oaRv;

    return oaRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_desktopName_impl() const
{
    std::tstring_t  sRv;
    std::ctstring_t nativeDesktop = xT("explorer.exe");

#if 0
    // TODO: SystemInfo::desktopName()
    const Process::id_t pid = Process::idByName(nativeDesktop);

    bool_t bRv = Process::isRunning(pid);
    if (bRv) {
        sRv = nativeDesktop;
    } else {
        // TODO: SystemInfo::desktopName() - checks for detecting Windows shell
    }

    xTEST_EQ(sRv.empty(), false);
#else
    sRv = nativeDesktop;
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_hostName_impl() const
{
    std::tstring_t sRv;

    ulong_t buffSize                 = xHOST_NAME_MAX;
    tchar_t buff[xHOST_NAME_MAX + 1] = {0};

    BOOL blRv = ::GetComputerName(buff, &buffSize);
    xTEST_DIFF(blRv, FALSE);

    sRv.assign(buff, buffSize);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_numOfCpus_impl() const
{
    SYSTEM_INFO sysInfo = {{0}};

    (void_t)::GetNativeSystemInfo(&sysInfo);

    ulong_t ulRv = sysInfo.dwNumberOfProcessors;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_currentCpuNum_impl() const
{
    typedef DWORD (WINAPI *func_t)(void_t);

    Dll dll;

    dll.load(xT("kernel32.dll"));

    bool_t bRv = dll.isProcExists(xT("GetCurrentProcessorNumber"));
    xCHECK_RET(!bRv, 0UL);

    func_t func = (func_t)dll.procAddress(xT("GetCurrentProcessorNumber"));
    xTEST_PTR(func);

    ulong_t ulRv = func();
    xTEST_NA(ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_cpuVendor_impl() const
{
    std::tstring_t value;

#if   xCOMPILER_MINGW || xCOMPILER_MS
    int_t  cpuInfo[4] = {0};
    char   man[13]    = {0};

    (void_t)::__cpuid(cpuInfo, 0);

    *reinterpret_cast<int_t *>( &man[0] ) = cpuInfo[1];
    *reinterpret_cast<int_t *>( &man[4] ) = cpuInfo[3];
    *reinterpret_cast<int_t *>( &man[8] ) = cpuInfo[2];

    value = std::string(man);
    xTEST_EQ(value.empty(), false);
#elif xCOMPILER_CODEGEAR
    // TODO: SystemInfo::cpuVendor()
    value = std::tstring_t();
#endif

    return value;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
SystemInfo::_cpuModel_impl() const
{
    std::tstring_t sRv;

#if   xCOMPILER_MINGW || xCOMPILER_MS
    char man[13] = {0};

    // get highest feature
    {
        int_t cpuInfo[4] = {0};

        (void_t)::__cpuid(cpuInfo, 0);

        *reinterpret_cast<int_t *>( &man[0] ) = cpuInfo[1];
        *reinterpret_cast<int_t *>( &man[4] ) = cpuInfo[3];
        *reinterpret_cast<int_t *>( &man[8] ) = cpuInfo[2];
    }

    // get highest extended feature
    int_t cpuInfo[4] = {0};

    (void_t)::__cpuid(cpuInfo, 0x80000000);

    uint_t highestFeatureEx = static_cast<uint_t>( cpuInfo[0] );

    // get processor brand name
    if (highestFeatureEx >= 0x80000004) {
        char buff[49] = {0};

        (void_t)::__cpuid(reinterpret_cast<int_t *>( &buff[0]  ), 0x80000002);
        (void_t)::__cpuid(reinterpret_cast<int_t *>( &buff[16] ), 0x80000003);
        (void_t)::__cpuid(reinterpret_cast<int_t *>( &buff[32] ), 0x80000004);

        std::tstring_t cpuName = String::trimSpace( xA2T(buff) );

        sRv = Format::str(xT("{} ({})"), cpuName, man);
    } else {
        sRv = Format::str(xT("{}"), man);
    }
#elif xCOMPILER_CODEGEAR
    sRv = std::tstring_t();
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_cpuSpeed_impl() const
{
    DWORD cpuSpeedMHz = 0UL;
    DWORD buffSize    = sizeof(cpuSpeedMHz);
    HKEY  key         = xPTR_NULL;

    LONG lRv = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, xT("HARDWARE\\DESCRIPTION\\System\\"
        "CentralProcessor\\0"), 0UL, KEY_READ, &key);
    xTEST_EQ(lRv, ERROR_SUCCESS);

    lRv = ::RegQueryValueEx(key, xT("~MHz"), xPTR_NULL, xPTR_NULL, reinterpret_cast<LPBYTE>( &cpuSpeedMHz ),
        &buffSize);
    xTEST_EQ(lRv, ERROR_SUCCESS);

    lRv = ::RegCloseKey(key);    key = xPTR_NULL;
    xTEST_EQ(lRv, ERROR_SUCCESS);

    ulong_t ulRv = cpuSpeedMHz;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_cpuUsage_impl() const
{
    double                dRv            = 0.0;

    FILETIME              sysIdle        = {0};
    FILETIME              sysKernel      = {0};
    FILETIME              sysUser        = {0};

    ULARGE_INTEGER        ulSysIdle      = {{0}};
    ULARGE_INTEGER        ulSysKernel    = {{0}};
    ULARGE_INTEGER        ulSysUser      = {{0}};

    static ULARGE_INTEGER s_sysIdleOld   = {{0}};
    static ULARGE_INTEGER s_sysKernelOld = {{0}};
    static ULARGE_INTEGER s_sysUserOld   = {{0}};


    BOOL blRv = ::GetSystemTimes(&sysIdle, &sysKernel, &sysUser);
    xTEST_DIFF(blRv, FALSE);

    (void_t)::CopyMemory(&ulSysIdle,   &sysIdle,   sizeof(sysIdle));
    (void_t)::CopyMemory(&ulSysKernel, &sysKernel, sizeof(sysKernel));
    (void_t)::CopyMemory(&ulSysUser,   &sysUser,   sizeof(sysUser));

    dRv = Utils::safeDivT(
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
ulonglong_t
SystemInfo::_ramTotal_impl() const
{
    MEMORYSTATUSEX status = {0};
    status.dwLength = sizeof(status);

    BOOL blRv = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(blRv, FALSE);

    ulonglong_t ullRv = status.ullTotalPhys;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulonglong_t
SystemInfo::_ramAvailable_impl() const
{
    MEMORYSTATUSEX status = {0};
    status.dwLength = sizeof(status);

    BOOL blRv = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(blRv, FALSE);

    ulonglong_t ullRv = status.ullAvailPhys;

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_ramUsage_impl() const
{
    MEMORYSTATUSEX status = {0};
    status.dwLength = sizeof(status);

    BOOL blRv = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(blRv, FALSE);

    ulong_t ulRv = status.dwMemoryLoad;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
ulong_t
SystemInfo::_pageSize_impl() const
{
    SYSTEM_INFO sysInfo = {{0}};

    (void_t)::GetNativeSystemInfo(&sysInfo);

    ulong_t ulRv = sysInfo.dwPageSize;
    xTEST_LESS(0UL, ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
