/**
 * \file  CxSystemInfo.cpp
 * \brief system information
 */


#include <xLib/Common/CxSystemInfo.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Sync/CxCurrentProcess.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
CxSystemInfo::EOsType
CxSystemInfo::osGetOS() {
    EOsType otRes = otUnknown;

#if xOS_ENV_WIN
    OSVERSIONINFO ovVer = {0};
    ovVer.dwOSVersionInfoSize = sizeof(ovVer);

    BOOL blRes = ::GetVersionEx(&ovVer);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, otUnknown);

    switch (ovVer.dwPlatformId) {
        case VER_PLATFORM_WIN32s: {
                otRes = otWindows3;
            }
            break;

        case VER_PLATFORM_WIN32_WINDOWS: {
                xCHECK_DO(0UL  == ovVer.dwMinorVersion, otRes = otWindows95; break);
                xCHECK_DO(10UL == ovVer.dwMinorVersion, otRes = otWindows98; break);
                xCHECK_DO(90UL == ovVer.dwMinorVersion, otRes = otWindows98; break);
            }
            break;

        case VER_PLATFORM_WIN32_NT: {
                xCHECK_DO(ovVer.dwMajorVersion <= 4UL,                                otRes = otWindowsNT;              break);
                xCHECK_DO(5UL == ovVer.dwMajorVersion && 0UL == ovVer.dwMinorVersion, otRes = otWindows2000;            break);
                xCHECK_DO(5UL == ovVer.dwMajorVersion && 1UL == ovVer.dwMinorVersion, otRes = otWindowsXP;              break);
                xCHECK_DO(5UL == ovVer.dwMajorVersion && 2UL == ovVer.dwMinorVersion, otRes = otWindowsXPProx64Edition; break);
                xCHECK_DO(5UL == ovVer.dwMajorVersion && 2UL == ovVer.dwMinorVersion, otRes = otWindowsServer2003;      break);
                xCHECK_DO(5UL == ovVer.dwMajorVersion && 2UL == ovVer.dwMinorVersion, otRes = otWindowsHomeServer;      break);
                xCHECK_DO(5UL == ovVer.dwMajorVersion && 2UL == ovVer.dwMinorVersion, otRes = otWindowsServer2003R2;    break);
                xCHECK_DO(6UL == ovVer.dwMajorVersion && 0UL == ovVer.dwMinorVersion, otRes = otWindowsVista;           break);
                xCHECK_DO(6UL == ovVer.dwMajorVersion && 0UL == ovVer.dwMinorVersion, otRes = otWindowsServer2008;      break);
                xCHECK_DO(6UL == ovVer.dwMajorVersion && 1UL == ovVer.dwMinorVersion, otRes = otWindowsServer2008R2;    break);
                xCHECK_DO(6UL == ovVer.dwMajorVersion && 1UL == ovVer.dwMinorVersion, otRes = otWindows7;               break);

                //for unknown windows/newest windows version
                otRes = otUnknown;
            }
            break;

        default: {
                otRes = otUnknown;
            }
            break;
    }

#elif xOS_ENV_UNIX
    utsname unKernelInfo= {{0}};

    int iRes = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, otUnknown);

    if      (true == CxString::bCompareNoCase(xT("Linux"), unKernelInfo.sysname)) {
        otRes = otLinux;
    }
    else if (true == CxString::bCompareNoCase(xT("FreeBSD"), unKernelInfo.sysname)) {
        otRes = otFreeBSD;
    }
    else {
        otRes = otUnknown;
    }
#endif

    return otRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxSystemInfo::sFormatOsType(
    const EOsType otOsType
)
{
    xDEBUG_VAR_NA(otOsType);

    std::tstring_t sRes;

#if xOS_ENV_WIN
    switch (otOsType) {
        case otWindows3:                { sRes = xT("Windows 3.1");                }    break;
        case otWindows95:               { sRes = xT("Windows 95");                 }    break;
        case otWindows98:               { sRes = xT("Windows 98");                 }    break;
        case otWindowsNT:               { sRes = xT("Windows NT 4.0");             }    break;
        case otWindows2000:             { sRes = xT("Windows 2000");               }    break;
        case otWindowsXP:               { sRes = xT("Windows XP");                 }    break;
        case otWindowsXPProx64Edition:  { sRes = xT("Windows XP Pro x64 Edition"); }    break;
        case otWindowsServer2003:       { sRes = xT("Windows Server 2003");        }    break;
        case otWindowsHomeServer:       { sRes = xT("Windows Home Server");        }    break;
        case otWindowsServer2003R2:     { sRes = xT("Windows Server 2003 R2");     }    break;
        case otWindowsVista:            { sRes = xT("Windows Vista");              }    break;
        case otWindowsServer2008:       { sRes = xT("Windows Server 2008");        }    break;
        case otWindowsServer2008R2:     { sRes = xT("Windows Server 2008 R2");     }    break;
        case otWindows7:                { sRes = xT("Windows 7");                  }    break;

        default:                        { sRes = CxConst::xUNKNOWN_STRING;         }    break;
    }
#elif xOS_ENV_UNIX
    if (osGetOS() == otOsType) {
        // current OS type - get info about OS kernel
        utsname unKernelInfo= {{0}};

        int iRes = ::uname(&unKernelInfo);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, std::tstring_t());

        sRes = CxString::sFormat(xT("%s %s (%s) %s"),
                                 unKernelInfo.sysname, unKernelInfo.release,
                                 unKernelInfo.version, unKernelInfo.machine);
    } else {
        // not current OS type, can't get info about OS kernel - return simple-formatted string
        switch (otOsType) {
            case otLinux:   { sRes = xT("Linux");              } break;
            case otFreeBSD: { sRes = xT("FreeBSD");            } break;

            default:        { sRes = CxConst::xUNKNOWN_STRING; } break;
        }
    }
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
CxSystemInfo::EOsArch
CxSystemInfo::oaGetOsArch() {
    EOsArch oaRes = oaUnknown;

#if xOS_ENV_WIN
    #if xCPU_64BIT
        oaRes = oa64bit;
    #elif xCPU_32BIT
        BOOL blIs64BitOs   = FALSE;
        BOOL blIsFuncExist = FALSE;
        {
            CxDll dlDll;
            blIsFuncExist = dlDll.bLoad(xT("kernel32.dll")) && dlDll.bIsProcExists(xT("IsWow64Process"));
        }
        BOOL blIsWow64Process = ::IsWow64Process(CxCurrentProcess::hGetHandle(), &blIs64BitOs);

        oaRes = (blIsFuncExist && blIsWow64Process && blIs64BitOs) ? oa64bit : oa32bit;
    #else
        // 64-bit Windows does not support Win16
        oaRes = oaUnknown;
    #endif
#elif xOS_ENV_UNIX
    utsname unKernelInfo= {{0}};

    int iRes = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes,                                       oaUnknown);
    /*DEBUG*/xASSERT_RET(0   != std::tstring_t(unKernelInfo.machine).size(), oaUnknown);

    //32-bit checks
    if      (true == CxString::bCompareNoCase(xT("i386"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }
    else if (true == CxString::bCompareNoCase(xT("i486"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }
    else if (true == CxString::bCompareNoCase(xT("i586"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }
    else if (true == CxString::bCompareNoCase(xT("i686"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }

    //64-bit checks
    else if (true == CxString::bCompareNoCase(xT("x86_64"), unKernelInfo.machine)) {
        oaRes = oa64bit;
    }
    else if (true == CxString::bCompareNoCase(xT("ia64"), unKernelInfo.machine)) {
        oaRes = oa64bit;
    }
    else if (true == CxString::bCompareNoCase(xT("amd64"), unKernelInfo.machine)) {
        oaRes = oa64bit;
    }

    //unknown
    else {
        oaRes = oaUnknown;
    }
#endif

    return oaRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxSystemInfo::sFormatOsArch(
    const EOsArch oaOsArch
)
{
    std::tstring_t sRes;

    switch (oaOsArch) {
        case CxSystemInfo::oa32bit:     sRes = xT("32-bit");             break;
        case CxSystemInfo::oa64bit:     sRes = xT("64-bit");             break;
        case CxSystemInfo::oaUnknown:   sRes = CxConst::xUNKNOWN_STRING; break;

        default:                        sRes = CxConst::xUNKNOWN_STRING; break;
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxSystemInfo::sGetHostName() {
    std::tstring_t sRes;

#if xOS_ENV_WIN
    ulong_t ulBuffSize                 = xHOST_NAME_MAX;
    tchar_t szBuff[xHOST_NAME_MAX + 1] = {0};

    BOOL blRes = ::GetComputerName(szBuff, &ulBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, xT("localhost"));

    sRes.assign(szBuff, ulBuffSize);
#elif xOS_ENV_UNIX
    utsname unKernelInfo= {{0}};

    int iRes = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, xT("localhost"));

    sRes.assign(unKernelInfo.nodename);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxSystemInfo::bIsUserAnAdmin() {
#if xOS_ENV_WIN
    bool                     bIsAdmin              = false;
    SID_IDENTIFIER_AUTHORITY siaNtAuthority        = { SECURITY_NT_AUTHORITY };
    PSID                     psAdministratorsGroup = NULL;

    BOOL blRes = ::AllocateAndInitializeSid(&siaNtAuthority, 2,
                                            SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL,
                                            &psAdministratorsGroup);
    xCHECK_RET(FALSE == blRes, false);

    {
	    BOOL blIsMember = FALSE;

	    blRes = ::CheckTokenMembership(NULL, psAdministratorsGroup, &blIsMember);
        if (FALSE == blRes || FALSE == blIsMember) {
            bIsAdmin = false;
        } else {
            bIsAdmin = true;
        }
    }

    (void)::FreeSid(psAdministratorsGroup);

    xCHECK_RET(false == bIsAdmin, false);
#elif xOS_ENV_UNIX
    const uid_t cuiRootId = 0;

    uid_t       uiUserId  = 0;

    uiUserId = ::getuid();
    xDEBUG_VARS_NA;
    xCHECK_RET(cuiRootId != uiUserId, false);

    uiUserId = ::geteuid();
    xDEBUG_VARS_NA;
    xCHECK_RET(cuiRootId != uiUserId, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxSystemInfo::sGetUserName() {
    std::tstring_t sRes;

#if xOS_ENV_WIN
    DWORD   ulBuffSize        = UNLEN;
    tchar_t szBuff[UNLEN + 1] = {0};

    BOOL blRes = ::GetUserName(&szBuff[0], &ulBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, std::tstring_t());

    sRes.assign(szBuff, ulBuffSize);
#elif xOS_ENV_UNIX
    // FAQ: http://www.metalshell.com/source_code/107/List_Users.html
    // FAQ: http://www.metalshell.com/source_code/83/Get_GID_Name.html

    const uid_t cuiUserId = ::getuid();
    xDEBUG_VAR_NA(cuiUserId);

    passwd *ppwPassword = ::getpwuid(cuiUserId);
    /*DEBUG*/xASSERT_RET(NULL != ppwPassword, std::tstring_t());

    sRes.assign(ppwPassword->pw_name);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetNumOfCpus() {
    ulong_t ulRes = 0UL;

#if xOS_ENV_WIN
    SYSTEM_INFO siSysInfo = {{0}};

    (void)::GetNativeSystemInfo(&siSysInfo);

    ulRes = siSysInfo.dwNumberOfProcessors;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        long_t liRes = ::sysconf(_SC_NPROCESSORS_ONLN);
        /*DEBUG*/xASSERT_RET(- 1 != liRes, 0UL);

        ulRes = static_cast<ulong_t>( liRes );
    #elif xOS_FREEBSD
        int    aiMib[]   = {CTL_HW, HW_NCPU};
        size_t uiResSize = sizeof(ulRes);

        int iRes = ::sysctl(aiMib, static_cast<u_int>( xARRAY_SIZE(aiMib) ), &ulRes, &uiResSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);
    #endif
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetCurrentCpuNum() {
    ulong_t ulRes = 0UL;

#if xOS_ENV_WIN
	typedef DWORD (WINAPI *TDllGetCurrentProcessorNumber)(void);

	CxDll dlDll;

	bool bRes = dlDll.bLoad(xT("kernel32.dll"));
	/*DEBUG*/xASSERT_RET(true == bRes, 0UL);

    bRes = dlDll.bIsProcExists(xT("GetCurrentProcessorNumber"));
    xCHECK_RET(false == bRes, 0UL);

	TDllGetCurrentProcessorNumber DllGetCurrentProcessorNumber = (TDllGetCurrentProcessorNumber)dlDll.fpGetProcAddress(xT("GetCurrentProcessorNumber"));
	/*DEBUG*/xASSERT_RET(NULL != DllGetCurrentProcessorNumber, 0UL);

	ulRes = DllGetCurrentProcessorNumber();
	xDEBUG_VAR_NA(ulRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        #if defined(SYS_getcpu)
            ulong_t ulCpu = 0UL;

            int iRes = ::syscall(SYS_getcpu, &ulCpu, NULL, NULL);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

            ulRes = ulCpu;
        #else
            #if (xSTD_LIBC_GNU_VER_MAJOR > 2) || \
                (xSTD_LIBC_GNU_VER_MAJOR == 2 && xSTD_LIBC_GNU_VER_MINOR > 6)

                // ::sched_getcpu() function is available since glibc 2.6, it is glibc specific
                int iRes = ::sched_getcpu();
                /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

                ulRes = static_cast<ulong_t>( iRes );
            #else
                //TODO: ulGetCurrentCpuNum
                ulRes = 0UL;
            #endif

            #if xTEMP_DISABLED
                // ::getcpu() was added in kernel 2.6.19 for x86_64 and i386
                uint_t uiCpu = 0U;

                int iRes = ::getcpu(&uiCpu, NULL, NULL);
                /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

                ulRes = uiCpu;
            #endif

        #endif
    #elif xOS_FREEBSD
        //TODO: ulGetCurrentCpuNum
        ulRes = 0UL;
    #endif
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
CxSystemInfo::ECpuVendor
CxSystemInfo::cvGetCpuVendor() {
    ECpuVendor cvRes = cvUnknown;

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW32 || xCOMPILER_MS
        uint_t uiHighestFeature = 0U;
        int    aiCpuInfo[4]     = {0};
        char   szMan[13]        = {0};

        (void)::__cpuid(aiCpuInfo, 0);

        uiHighestFeature = static_cast<uint_t>( aiCpuInfo[0] );

        *reinterpret_cast<int *>( &szMan[0] ) = aiCpuInfo[1];
        *reinterpret_cast<int *>( &szMan[4] ) = aiCpuInfo[3];
        *reinterpret_cast<int *>( &szMan[8] ) = aiCpuInfo[2];

        if      (std::string("GenuineIntel") == szMan) {
            cvRes = cvIntel;
        }
        else if (std::string("AuthenticAMD") == szMan) {
            cvRes = cvAmd;
        }
        else {
            cvRes = cvUnknown;
        }
    #elif xCOMPILER_CODEGEAR
        cvRes = cvUnknown;
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "vendor_id : GenuineIntel"
        std::tstring_t sValue = CxPath::sGetProcValue(xT("/proc/cpuinfo"), xT("vendor_id"));
        /*DEBUG*/xASSERT_RET(false == sValue.empty(), cvUnknown);

        if      (std::string("GenuineIntel") == sValue) {
            cvRes = cvIntel;
        }
        else if (std::string("AuthenticAMD") == sValue) {
            cvRes = cvAmd;
        }
        else {
            cvRes = cvUnknown;
        }
    #elif xOS_FREEBSD
        //TODO: CxSystemInfo::cvGetCpuVendor()
    #endif
#endif

    return cvRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxSystemInfo::sGetCpuModel() {
    std::tstring_t sRes;

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW32 || xCOMPILER_MS
        char szMan[13] = {0};

        // get szMan
        {
            int aiCpuInfo[4] = {0};

            (void)::__cpuid(aiCpuInfo, 0);

            uint_t uiHighestFeature = static_cast<uint_t>( aiCpuInfo[0] );

            *reinterpret_cast<int *>( &szMan[0] ) = aiCpuInfo[1];
            *reinterpret_cast<int *>( &szMan[4] ) = aiCpuInfo[3];
            *reinterpret_cast<int *>( &szMan[8] ) = aiCpuInfo[2];
        }

        // get highest extended feature
        int aiCpuInfo[4] = {0};

        (void)::__cpuid(aiCpuInfo, 0x80000000);

        uint_t uiHighestFeatureEx = static_cast<uint_t>( aiCpuInfo[0] );

        // get processor brand name
        if (uiHighestFeatureEx >= 0x80000004) {
            char szCpuName[49] = {0};

            (void)::__cpuid(reinterpret_cast<int *>( &szCpuName[0]  ), 0x80000002);
            (void)::__cpuid(reinterpret_cast<int *>( &szCpuName[16] ), 0x80000003);
            (void)::__cpuid(reinterpret_cast<int *>( &szCpuName[32] ), 0x80000004);

            std::tstring_t sCpuName = CxString::sTrimSpace(szCpuName);

            sRes = CxString::sFormat(xT("%s (%s)"), sCpuName.c_str(), szMan);
        } else {
            sRes = CxString::sFormat(xT("%s"), szMan);
        }
    #elif xCOMPILER_CODEGEAR
        sRes = xUNKNOWN_STRING;
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "model name    : Intel(R) Xeon(R) CPU           E5620  @ 2.40GHz"
        std::tstring_t sValue = CxPath::sGetProcValue(xT("/proc/cpuinfo"), xT("model name"));
        /*DEBUG*/xASSERT_RET(false == sValue.empty(), std::tstring_t());

        sRes = sValue;
    #elif xOS_FREEBSD
        //TODO: CxSystemInfo::sGetCpuModel()
    #endif
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetCpuSpeed() {
    ulong_t ulRes = 0UL;

#if xOS_ENV_WIN
    DWORD ulCpuSpeedMHz = 0UL;
    DWORD dwBuffSize    = sizeof(ulCpuSpeedMHz);
    HKEY  hKey          = NULL;

    LONG lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, xT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0UL, KEY_READ, &hKey);
    /*DEBUG*/xASSERT_RET(ERROR_SUCCESS == lRes, 0UL);

    lRes = ::RegQueryValueEx(hKey, xT("~MHz"), NULL, NULL, reinterpret_cast<LPBYTE>( &ulCpuSpeedMHz ), &dwBuffSize);
    /*DEBUG*/xASSERT_RET(ERROR_SUCCESS == lRes, 0UL);

    lRes = ::RegCloseKey(hKey);    hKey = NULL;
    /*DEBUG*/xASSERT_RET(ERROR_SUCCESS == lRes, 0UL);

    ulRes = ulCpuSpeedMHz;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "cpu MHz         : 2796.380"
        std::tstring_t sValue = CxPath::sGetProcValue(xT("/proc/cpuinfo"), xT("cpu MHz"));
        /*DEBUG*/xASSERT_RET(false == sValue.empty(), 0UL);

        double dCpuSpeedMHz = CxString::lexical_cast<double>( sValue );

        ulRes = static_cast<ulong_t>( CxMacros::dRound(dCpuSpeedMHz) );
    #elif xOS_FREEBSD
        ulong_t ulCpuSpeedMHz     = 0UL;
        size_t  uiCpuSpeedMHzSize = sizeof(ulCpuSpeedMHz);

        int iRes = ::sysctlbyname("hw.clockrate", &ulCpuSpeedMHz, &uiCpuSpeedMHzSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

        ulRes = ulCpuSpeedMHz;
    #endif
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetCpuUsage() {
    ulong_t ulRes = 0UL;

#if   xOS_ENV_WIN
    double                dRes             = 0.0;

    FILETIME              ftSysIdle        = {0};
    FILETIME              ftSysKernel      = {0};
    FILETIME              ftSysUser        = {0};

    ULARGE_INTEGER        ulSysIdle        = {{0}};
    ULARGE_INTEGER        ulSysKernel      = {{0}};
    ULARGE_INTEGER        ulSysUser        = {{0}};

    static ULARGE_INTEGER s_ulSysIdleOld   = {{0}};
    static ULARGE_INTEGER s_ulSysKernelOld = {{0}};
    static ULARGE_INTEGER s_ulSysUserOld   = {{0}};


    BOOL blRes = ::GetSystemTimes(&ftSysIdle, &ftSysKernel, &ftSysUser);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, 0UL);

    (void)::CopyMemory(&ulSysIdle,   &ftSysIdle,   sizeof(ftSysIdle));
    (void)::CopyMemory(&ulSysKernel, &ftSysKernel, sizeof(ftSysKernel));
    (void)::CopyMemory(&ulSysUser,   &ftSysUser,   sizeof(ftSysUser));

    dRes = CxMacros::dSafeDiv(
                (ulSysKernel.QuadPart - s_ulSysKernelOld.QuadPart) +
                (ulSysUser.QuadPart   - s_ulSysUserOld.QuadPart)   -
                (ulSysIdle.QuadPart   - s_ulSysIdleOld.QuadPart)
                ,
                (ulSysKernel.QuadPart - s_ulSysKernelOld.QuadPart) +
                (ulSysUser.QuadPart   - s_ulSysUserOld.QuadPart)
    ) * 100.0;

    s_ulSysIdleOld.QuadPart   = ulSysIdle.QuadPart;
    s_ulSysUserOld.QuadPart   = ulSysUser.QuadPart;
    s_ulSysKernelOld.QuadPart = ulSysKernel.QuadPart;

    ulRes = static_cast<ulong_t>( dRes );
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        double             dRes               = 0.0;
        int                iRes               = - 1;

        static bool        bIsFirstRun        = true;

        static ulonglong_t ullUserTotalOld    = 0ULL;
        static ulonglong_t ullUserTotalLowOld = 0ULL;
        static ulonglong_t ullSysTotalOld     = 0ULL;
        static ulonglong_t ullTotalIdleOld    = 0ULL;

        ulonglong_t        ullUserTotal       = 0ULL;
        ulonglong_t        ullUserTotalLow    = 0ULL;
        ulonglong_t        ullSysTotal        = 0ULL;
        ulonglong_t        ullTotalIdle       = 0ULL;
        ulonglong_t        ullTotal           = 0ULL;

        //read proc file for the first time
        if (true == bIsFirstRun) {
            FILE *pFile = fopen("/proc/stat", "r");
            /*DEBUG*/xASSERT_RET(NULL != pFile, 0UL);

            iRes = fscanf(pFile, "cpu %Ld %Ld %Ld %Ld", &ullUserTotalOld, &ullUserTotalLowOld, &ullSysTotalOld, &ullTotalIdleOld);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

            iRes = fclose(pFile);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

            bIsFirstRun = false;
        }

        //read proc file for the next times
        {
            FILE *pFile = fopen("/proc/stat", "r");
            /*DEBUG*/xASSERT_RET(NULL != pFile, 0UL);

            iRes = fscanf(pFile, "cpu %Ld %Ld %Ld %Ld", &ullUserTotal, &ullUserTotalLow, &ullSysTotal, &ullTotalIdle);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

            iRes = fclose(pFile);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);
        }

        if (ullUserTotal < ullUserTotalOld || ullUserTotalLow < ullUserTotalLowOld ||
            ullSysTotal  < ullSysTotalOld  || ullTotalIdle    < ullTotalIdleOld)
        {
            //Overflow detection. Just skip this value.
            dRes      = 0.0;
        } else {
            ullTotal  = (ullUserTotal - ullUserTotalOld) + (ullUserTotalLow - ullUserTotalLowOld) + (ullSysTotal - ullSysTotalOld);
            dRes      = ullTotal;
            ullTotal += (ullTotalIdle - ullTotalIdleOld);
            dRes     /= ullTotal;
            dRes     *= 100ULL;
        }

        ullUserTotalOld    = ullUserTotal;
        ullUserTotalLowOld = ullUserTotalLow;
        ullSysTotalOld     = ullSysTotal;
        ullTotalIdleOld    = ullTotalIdle;

        ulRes = static_cast<ulong_t>( dRes );
    #elif xOS_FREEBSD
        double         dCpuUsage            = 0.0;

        static ulong_t s_ulTotalOld         = - 1UL;
        static ulong_t s_ulUsedOld          = - 1UL;

        ulong_t        ulUsed               = - 1UL;
        ulong_t        ulTotal              = - 1UL;

        ulong_t        aulCpIime[CPUSTATES] = {0};
        size_t         uiCpTimeSize         = sizeof(aulCpIime);

        int iRes = ::sysctlbyname("kern.cp_time", &aulCpIime, &uiCpTimeSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

        ulUsed       = aulCpIime[CP_USER] + aulCpIime[CP_NICE] + aulCpIime[CP_SYS];
        ulTotal      = aulCpIime[CP_USER] + aulCpIime[CP_NICE] + aulCpIime[CP_SYS] + aulCpIime[CP_IDLE];

        dCpuUsage    = CxMacros::dSafeDiv(ulUsed - s_ulUsedOld, ulTotal - s_ulTotalOld) * 100.0;

        s_ulUsedOld  = ulUsed;
        s_ulTotalOld = ulTotal;

        ulRes = static_cast<ulong_t>( CxMacros::dRound(dCpuUsage) );
    #endif
#endif

    return ulRes;
}
//----------------------------------------------------------------------------------------------------
/*static*/
ulonglong_t
CxSystemInfo::ullGetRamTotal() {
    ulonglong_t ullRes = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX msStatus = {0};
    msStatus.dwLength = sizeof(msStatus);

    BOOL blRes = ::GlobalMemoryStatusEx(&msStatus);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, 0UL);

    ullRes = msStatus.ullTotalPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo siInfo = {0};

        int iRes = ::sysinfo(&siInfo);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0ULL);

        ullRes = siInfo.totalram * siInfo.mem_unit;
    #elif xOS_FREEBSD
        ulonglong_t ullRamTotal    = 0ULL;

        int         aiMib[]        = {CTL_HW, HW_PHYSMEM};
        size_t      uiRamTotalSize = sizeof(ullRamTotal);

        int iRes = ::sysctl(aiMib, 2, &ullRamTotal, &uiRamTotalSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

        ullRes = ullRamTotal;
    #endif
#endif

    return ullRes;
}
//----------------------------------------------------------------------------------------------------
/*static*/
ulonglong_t
CxSystemInfo::ullGetRamAvailable() {
    ulonglong_t ullRes = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX msStatus = {0};
    msStatus.dwLength = sizeof(msStatus);

    BOOL blRes = ::GlobalMemoryStatusEx(&msStatus);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, 0UL);

    ullRes = msStatus.ullAvailPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo siInfo = {0};

        int iRes = ::sysinfo(&siInfo);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0ULL);

        ullRes = siInfo.freeram * siInfo.mem_unit;
    #elif xOS_FREEBSD
        ulonglong_t ullAvailPhysPages     = 0ULL;
        size_t      ullAvailPhysPagesSize = sizeof(ullAvailPhysPages);

        int iRes = ::sysctlbyname("vm.stats.vm.v_free_count", &ullAvailPhysPages, &ullAvailPhysPagesSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0ULL);

        ullRes = ullAvailPhysPages * ulGetPageSize();
    #endif
#endif

    return ullRes;
}
//----------------------------------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetRamUsage() {
    ulong_t ulRes = 0UL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX msStatus = {0};
    msStatus.dwLength = sizeof(msStatus);

    BOOL blRes = ::GlobalMemoryStatusEx(&msStatus);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, 0UL);

    ulRes = msStatus.dwMemoryLoad;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo siInfo = {0};

        int iRes = ::sysinfo(&siInfo);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

        ulong_t ulUsage = siInfo.totalram - siInfo.freeram;

        ulRes = static_cast<ulong_t>( CxMacros::dSafeDiv(ulUsage * 100.0, siInfo.totalram) );
        /*DEBUG*/xASSERT_RET(siInfo.totalram == ulUsage + siInfo.freeram, 0UL);
    #elif xOS_FREEBSD
        ulonglong_t ullRamTotal = 0ULL;
        {
            int     aiMib[]        = {CTL_HW, HW_PHYSMEM};
            size_t  uiRamTotalSize = sizeof(ullRamTotal);

            int iRes = ::sysctl(aiMib, 2, &ullRamTotal, &uiRamTotalSize, NULL, 0);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);
        }

        ulonglong_t ullRamFree = 0ULL;
        {
            ulonglong_t ullAvailPhysPages     = 0ULL;
            size_t      ullAvailPhysPagesSize = sizeof(ullAvailPhysPages);

            int iRes = ::sysctlbyname("vm.stats.vm.v_free_count", &ullAvailPhysPages, &ullAvailPhysPagesSize, NULL, 0);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, 0ULL);

            ullRamFree = ullAvailPhysPages * ulGetPageSize();
        }

        ulonglong_t ullRamUsage = ullRamTotal - ullRamFree;

        ulRes = static_cast<ulong_t>( CxMacros::dSafeDiv(ullRamUsage * 100.0, ullRamTotal) );
        /*DEBUG*/xASSERT_RET(ullRamTotal == ullRamUsage + ullRamFree, 0UL);
    #endif
#endif

    return ulRes;
}
//----------------------------------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetPageSize() {
    ulong_t ulRes = 0UL;

#if   xOS_ENV_WIN
    SYSTEM_INFO siSysInfo = {{0}};

    (void)::GetNativeSystemInfo(&siSysInfo);

    ulRes = siSysInfo.dwPageSize;
#elif xOS_ENV_UNIX
    int iRes = ::sysconf(xPAGE_SIZE);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);
    /*DEBUG*/xASSERT_RET(0   <  iRes, 0UL);

    ulRes = static_cast<ulong_t>( iRes );
#endif

    /*DEBUG*/xASSERT_RET(0UL < ulRes, 0UL);

    return ulRes;
}
//----------------------------------------------------------------------------------------------------



/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*virtual*/
CxSystemInfo::CxSystemInfo() {

}
//---------------------------------------------------------------------------
CxSystemInfo::~CxSystemInfo() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
