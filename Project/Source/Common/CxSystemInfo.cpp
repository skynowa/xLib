/**
 * \file  CxSystemInfo.cpp
 * \brief system information
 */


#include <xLib/Common/CxSystemInfo.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Sync/CxCurrentProcess.h>

#if xOS_ENV_WIN
    #include <shlobj.h>
#endif


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

    int iRv = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, otUnknown);

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

    std::tstring_t sRv;

#if xOS_ENV_WIN
    switch (otOsType) {
        case otWindows3:                { sRv = xT("Windows 3.1");                }    break;
        case otWindows95:               { sRv = xT("Windows 95");                 }    break;
        case otWindows98:               { sRv = xT("Windows 98");                 }    break;
        case otWindowsNT:               { sRv = xT("Windows NT 4.0");             }    break;
        case otWindows2000:             { sRv = xT("Windows 2000");               }    break;
        case otWindowsXP:               { sRv = xT("Windows XP");                 }    break;
        case otWindowsXPProx64Edition:  { sRv = xT("Windows XP Pro x64 Edition"); }    break;
        case otWindowsServer2003:       { sRv = xT("Windows Server 2003");        }    break;
        case otWindowsHomeServer:       { sRv = xT("Windows Home Server");        }    break;
        case otWindowsServer2003R2:     { sRv = xT("Windows Server 2003 R2");     }    break;
        case otWindowsVista:            { sRv = xT("Windows Vista");              }    break;
        case otWindowsServer2008:       { sRv = xT("Windows Server 2008");        }    break;
        case otWindowsServer2008R2:     { sRv = xT("Windows Server 2008 R2");     }    break;
        case otWindows7:                { sRv = xT("Windows 7");                  }    break;

        default:                        { sRv = CxConst::xUNKNOWN_STRING;         }    break;
    }
#elif xOS_ENV_UNIX
    if (osGetOS() == otOsType) {
        // current OS type - get info about OS kernel
        utsname unKernelInfo= {{0}};

        int iRv = ::uname(&unKernelInfo);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, std::tstring_t());

        sRv = CxString::sFormat(xT("%s %s (%s) %s"),
                                 unKernelInfo.sysname, unKernelInfo.release,
                                 unKernelInfo.version, unKernelInfo.machine);
    } else {
        // not current OS type, can't get info about OS kernel - return simple-formatted string
        switch (otOsType) {
            case otLinux:   { sRv = xT("Linux");              } break;
            case otFreeBSD: { sRv = xT("FreeBSD");            } break;

            default:        { sRv = CxConst::xUNKNOWN_STRING; } break;
        }
    }
#endif

    return sRv;
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

    int iRv = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRv,                                       oaUnknown);
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
    std::tstring_t sRv;

    switch (oaOsArch) {
        case CxSystemInfo::oa32bit:     sRv = xT("32-bit");             break;
        case CxSystemInfo::oa64bit:     sRv = xT("64-bit");             break;
        case CxSystemInfo::oaUnknown:   sRv = CxConst::xUNKNOWN_STRING; break;

        default:                        sRv = CxConst::xUNKNOWN_STRING; break;
    }

    return sRv;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxSystemInfo::sGetHostName() {
    std::tstring_t sRv;

#if xOS_ENV_WIN
    ulong_t ulBuffSize                 = xHOST_NAME_MAX;
    tchar_t szBuff[xHOST_NAME_MAX + 1] = {0};

    BOOL blRes = ::GetComputerName(szBuff, &ulBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, xT("localhost"));

    sRv.assign(szBuff, ulBuffSize);
#elif xOS_ENV_UNIX
    utsname unKernelInfo= {{0}};

    int iRv = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, xT("localhost"));

    sRv.assign(unKernelInfo.nodename);
#endif

    return sRv;
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
    std::tstring_t sRv;

#if xOS_ENV_WIN
    DWORD   ulBuffSize        = UNLEN;
    tchar_t szBuff[UNLEN + 1] = {0};

    BOOL blRes = ::GetUserName(&szBuff[0], &ulBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, std::tstring_t());

    sRv.assign(szBuff, ulBuffSize);
#elif xOS_ENV_UNIX
    // FAQ: http://www.metalshell.com/source_code/107/List_Users.html
    // FAQ: http://www.metalshell.com/source_code/83/Get_GID_Name.html

    const uid_t cuiUserId = ::getuid();
    xDEBUG_VAR_NA(cuiUserId);

    passwd *ppwPassword = ::getpwuid(cuiUserId);
    /*DEBUG*/xASSERT_RET(NULL != ppwPassword, std::tstring_t());

    sRv.assign(ppwPassword->pw_name);
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t 
CxSystemInfo::sGetUseHomeDir() {
    std::tstring_t sRv;

#if xOS_ENV_WIN
    tchar_t szBuff[MAX_PATH + 1] = {0};

    HRESULT hrRes = SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0UL, &szBuff[0]);
    xASSERT_RET(S_OK  == hrRes, std::tstring_t());

    sRv.assign(szBuff);
#elif xOS_ENV_UNIX
   /*
    * MAN: 
    *
    * Login programs use the value of this field to initialize 
    * the HOME environment variable for the login shell. 
    * An application that wants to determine its user's home directory 
    * should inspect the value of HOME (rather than the value getpwuid(getuid())->pw_dir) 
    * since this allows the user to modify their notion of "the home directory" 
    * during a login session. To determine the (initial) home directory of another user, 
    * it is necessary to use getpwnam("username")->pw_dir or similar.
    */

    bool bRv = CxEnvironment::bIsExists(xT("HOME"));
    if (true == bRv) {
        sRv = CxEnvironment::sGetVar(xT("HOME"));
    } else {
        passwd *ppwPass = ::getpwuid( ::getuid() );
        xASSERT_RET(NULL != ppwPass, std::tstring_t());

        sRv.assign(ppwPass->pw_dir);
    }
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetNumOfCpus() {
    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
    SYSTEM_INFO siSysInfo = {{0}};

    (void)::GetNativeSystemInfo(&siSysInfo);

    ulRv = siSysInfo.dwNumberOfProcessors;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        long_t liRv = ::sysconf(_SC_NPROCESSORS_ONLN);
        /*DEBUG*/xASSERT_RET(- 1 != liRv, 0UL);

        ulRv = static_cast<ulong_t>( liRv );
    #elif xOS_FREEBSD
        int    aiMib[]   = {CTL_HW, HW_NCPU};
        size_t uiResSize = sizeof(ulRv);

        int iRv = ::sysctl(aiMib, static_cast<u_int>( xARRAY_SIZE(aiMib) ), &ulRv, &uiResSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);
    #endif
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetCurrentCpuNum() {
    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
	typedef DWORD (WINAPI *TDllGetCurrentProcessorNumber)(void);

	CxDll dlDll;

	bool bRv = dlDll.bLoad(xT("kernel32.dll"));
	/*DEBUG*/xASSERT_RET(true == bRv, 0UL);

    bRv = dlDll.bIsProcExists(xT("GetCurrentProcessorNumber"));
    xCHECK_RET(false == bRv, 0UL);

	TDllGetCurrentProcessorNumber DllGetCurrentProcessorNumber = (TDllGetCurrentProcessorNumber)dlDll.fpGetProcAddress(xT("GetCurrentProcessorNumber"));
	/*DEBUG*/xASSERT_RET(NULL != DllGetCurrentProcessorNumber, 0UL);

	ulRv = DllGetCurrentProcessorNumber();
	xDEBUG_VAR_NA(ulRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        #if defined(SYS_getcpu)
            ulong_t ulCpu = 0UL;

            int iRv = ::syscall(SYS_getcpu, &ulCpu, NULL, NULL);
            /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

            ulRv = ulCpu;
        #else
            #if (xSTD_LIBC_GNU_VER_MAJOR > 2) || \
                (xSTD_LIBC_GNU_VER_MAJOR == 2 && xSTD_LIBC_GNU_VER_MINOR > 6)

                // ::sched_getcpu() function is available since glibc 2.6, it is glibc specific
                int iRv = ::sched_getcpu();
                /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

                ulRv = static_cast<ulong_t>( iRv );
            #else
                //TODO: ulGetCurrentCpuNum
                ulRv = 0UL;
            #endif

            #if xTEMP_DISABLED
                // ::getcpu() was added in kernel 2.6.19 for x86_64 and i386
                uint_t uiCpu = 0U;

                int iRv = ::getcpu(&uiCpu, NULL, NULL);
                /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

                ulRv = uiCpu;
            #endif

        #endif
    #elif xOS_FREEBSD
        //TODO: ulGetCurrentCpuNum
        ulRv = 0UL;
    #endif
#endif

    return ulRv;
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
    std::tstring_t sRv;

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

            sRv = CxString::sFormat(xT("%s (%s)"), sCpuName.c_str(), szMan);
        } else {
            sRv = CxString::sFormat(xT("%s"), szMan);
        }
    #elif xCOMPILER_CODEGEAR
        sRv = xUNKNOWN_STRING;
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "model name    : Intel(R) Xeon(R) CPU           E5620  @ 2.40GHz"
        std::tstring_t sValue = CxPath::sGetProcValue(xT("/proc/cpuinfo"), xT("model name"));
        /*DEBUG*/xASSERT_RET(false == sValue.empty(), std::tstring_t());

        sRv = sValue;
    #elif xOS_FREEBSD
        //TODO: CxSystemInfo::sGetCpuModel()
    #endif
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetCpuSpeed() {
    ulong_t ulRv = 0UL;

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

    ulRv = ulCpuSpeedMHz;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "cpu MHz         : 2796.380"
        std::tstring_t sValue = CxPath::sGetProcValue(xT("/proc/cpuinfo"), xT("cpu MHz"));
        /*DEBUG*/xASSERT_RET(false == sValue.empty(), 0UL);

        double dCpuSpeedMHz = CxString::lexical_cast<double>( sValue );

        ulRv = static_cast<ulong_t>( CxMacros::dRound(dCpuSpeedMHz) );
    #elif xOS_FREEBSD
        ulong_t ulCpuSpeedMHz     = 0UL;
        size_t  uiCpuSpeedMHzSize = sizeof(ulCpuSpeedMHz);

        int iRv = ::sysctlbyname("hw.clockrate", &ulCpuSpeedMHz, &uiCpuSpeedMHzSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

        ulRv = ulCpuSpeedMHz;
    #endif
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetCpuUsage() {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    double                dRv             = 0.0;

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

    dRv = CxMacros::dSafeDiv(
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

    ulRv = static_cast<ulong_t>( dRv );
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        double             dRv               = 0.0;
        int                iRv               = - 1;

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

            iRv = fscanf(pFile, "cpu %Ld %Ld %Ld %Ld", &ullUserTotalOld, &ullUserTotalLowOld, &ullSysTotalOld, &ullTotalIdleOld);
            /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

            iRv = fclose(pFile);
            /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

            bIsFirstRun = false;
        }

        //read proc file for the next times
        {
            FILE *pFile = fopen("/proc/stat", "r");
            /*DEBUG*/xASSERT_RET(NULL != pFile, 0UL);

            iRv = fscanf(pFile, "cpu %Ld %Ld %Ld %Ld", &ullUserTotal, &ullUserTotalLow, &ullSysTotal, &ullTotalIdle);
            /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

            iRv = fclose(pFile);
            /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);
        }

        if (ullUserTotal < ullUserTotalOld || ullUserTotalLow < ullUserTotalLowOld ||
            ullSysTotal  < ullSysTotalOld  || ullTotalIdle    < ullTotalIdleOld)
        {
            //Overflow detection. Just skip this value.
            dRv      = 0.0;
        } else {
            ullTotal  = (ullUserTotal - ullUserTotalOld) + (ullUserTotalLow - ullUserTotalLowOld) + (ullSysTotal - ullSysTotalOld);
            dRv      = ullTotal;
            ullTotal += (ullTotalIdle - ullTotalIdleOld);
            dRv     /= ullTotal;
            dRv     *= 100ULL;
        }

        ullUserTotalOld    = ullUserTotal;
        ullUserTotalLowOld = ullUserTotalLow;
        ullSysTotalOld     = ullSysTotal;
        ullTotalIdleOld    = ullTotalIdle;

        ulRv = static_cast<ulong_t>( dRv );
    #elif xOS_FREEBSD
        double         dCpuUsage            = 0.0;

        static ulong_t s_ulTotalOld         = - 1UL;
        static ulong_t s_ulUsedOld          = - 1UL;

        ulong_t        ulUsed               = - 1UL;
        ulong_t        ulTotal              = - 1UL;

        ulong_t        aulCpIime[CPUSTATES] = {0};
        size_t         uiCpTimeSize         = sizeof(aulCpIime);

        int iRv = ::sysctlbyname("kern.cp_time", &aulCpIime, &uiCpTimeSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

        ulUsed       = aulCpIime[CP_USER] + aulCpIime[CP_NICE] + aulCpIime[CP_SYS];
        ulTotal      = aulCpIime[CP_USER] + aulCpIime[CP_NICE] + aulCpIime[CP_SYS] + aulCpIime[CP_IDLE];

        dCpuUsage    = CxMacros::dSafeDiv(ulUsed - s_ulUsedOld, ulTotal - s_ulTotalOld) * 100.0;

        s_ulUsedOld  = ulUsed;
        s_ulTotalOld = ulTotal;

        ulRv = static_cast<ulong_t>( CxMacros::dRound(dCpuUsage) );
    #endif
#endif

    return ulRv;
}
//----------------------------------------------------------------------------------------------------
/*static*/
ulonglong_t
CxSystemInfo::ullGetRamTotal() {
    ulonglong_t ullRv = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX msStatus = {0};
    msStatus.dwLength = sizeof(msStatus);

    BOOL blRes = ::GlobalMemoryStatusEx(&msStatus);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, 0UL);

    ullRv = msStatus.ullTotalPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo siInfo = {0};

        int iRv = ::sysinfo(&siInfo);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, 0ULL);

        ullRv = siInfo.totalram * siInfo.mem_unit;
    #elif xOS_FREEBSD
        ulonglong_t ullRamTotal    = 0ULL;

        int         aiMib[]        = {CTL_HW, HW_PHYSMEM};
        size_t      uiRamTotalSize = sizeof(ullRamTotal);

        int iRv = ::sysctl(aiMib, 2, &ullRamTotal, &uiRamTotalSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

        ullRv = ullRamTotal;
    #endif
#endif

    return ullRv;
}
//----------------------------------------------------------------------------------------------------
/*static*/
ulonglong_t
CxSystemInfo::ullGetRamAvailable() {
    ulonglong_t ullRv = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX msStatus = {0};
    msStatus.dwLength = sizeof(msStatus);

    BOOL blRes = ::GlobalMemoryStatusEx(&msStatus);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, 0UL);

    ullRv = msStatus.ullAvailPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo siInfo = {0};

        int iRv = ::sysinfo(&siInfo);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, 0ULL);

        ullRv = siInfo.freeram * siInfo.mem_unit;
    #elif xOS_FREEBSD
        ulonglong_t ullAvailPhysPages     = 0ULL;
        size_t      ullAvailPhysPagesSize = sizeof(ullAvailPhysPages);

        int iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &ullAvailPhysPages, &ullAvailPhysPagesSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, 0ULL);

        ullRv = ullAvailPhysPages * ulGetPageSize();
    #endif
#endif

    return ullRv;
}
//----------------------------------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetRamUsage() {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX msStatus = {0};
    msStatus.dwLength = sizeof(msStatus);

    BOOL blRes = ::GlobalMemoryStatusEx(&msStatus);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, 0UL);

    ulRv = msStatus.dwMemoryLoad;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo siInfo = {0};

        int iRv = ::sysinfo(&siInfo);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);

        ulong_t ulUsage = siInfo.totalram - siInfo.freeram;

        ulRv = static_cast<ulong_t>( CxMacros::dSafeDiv(ulUsage * 100.0, siInfo.totalram) );
        /*DEBUG*/xASSERT_RET(siInfo.totalram == ulUsage + siInfo.freeram, 0UL);
    #elif xOS_FREEBSD
        ulonglong_t ullRamTotal = 0ULL;
        {
            int     aiMib[]        = {CTL_HW, HW_PHYSMEM};
            size_t  uiRamTotalSize = sizeof(ullRamTotal);

            int iRv = ::sysctl(aiMib, 2, &ullRamTotal, &uiRamTotalSize, NULL, 0);
            /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);
        }

        ulonglong_t ullRamFree = 0ULL;
        {
            ulonglong_t ullAvailPhysPages     = 0ULL;
            size_t      ullAvailPhysPagesSize = sizeof(ullAvailPhysPages);

            int iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &ullAvailPhysPages, &ullAvailPhysPagesSize, NULL, 0);
            /*DEBUG*/xASSERT_RET(- 1 != iRv, 0ULL);

            ullRamFree = ullAvailPhysPages * ulGetPageSize();
        }

        ulonglong_t ullRamUsage = ullRamTotal - ullRamFree;

        ulRv = static_cast<ulong_t>( CxMacros::dSafeDiv(ullRamUsage * 100.0, ullRamTotal) );
        /*DEBUG*/xASSERT_RET(ullRamTotal == ullRamUsage + ullRamFree, 0UL);
    #endif
#endif

    return ulRv;
}
//----------------------------------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetPageSize() {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    SYSTEM_INFO siSysInfo = {{0}};

    (void)::GetNativeSystemInfo(&siSysInfo);

    ulRv = siSysInfo.dwPageSize;
#elif xOS_ENV_UNIX
    int iRv = ::sysconf(xPAGE_SIZE);
    /*DEBUG*/xASSERT_RET(- 1 != iRv, 0UL);
    /*DEBUG*/xASSERT_RET(0   <  iRv, 0UL);

    ulRv = static_cast<ulong_t>( iRv );
#endif

    /*DEBUG*/xASSERT_RET(0UL < ulRv, 0UL);

    return ulRv;
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
