/**
 * \file  CxSystemInfo.cpp
 * \brief system information
 */


#include <xLib/Common/CxSystemInfo.h>

#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Sync/CxCurrentProcess.h>



static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;





    double getCurrentValue(){
        //init
        {
            SYSTEM_INFO sysInfo;
            FILETIME ftime, fsys, fuser;


            GetSystemInfo(&sysInfo);
            numProcessors = sysInfo.dwNumberOfProcessors;


            GetSystemTimeAsFileTime(&ftime);
            memcpy(&lastCPU, &ftime, sizeof(FILETIME));


            self = GetCurrentProcess();
            GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
            memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
            memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
        }


        FILETIME ftime, fsys, fuser;
        ULARGE_INTEGER now, sys, user;
        double percent;


        GetSystemTimeAsFileTime(&ftime);
        memcpy(&now, &ftime, sizeof(FILETIME));


        GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
        memcpy(&sys, &fsys, sizeof(FILETIME));
        memcpy(&user, &fuser, sizeof(FILETIME));
        percent = (sys.QuadPart - lastSysCPU.QuadPart) +
                (user.QuadPart - lastUserCPU.QuadPart);
        percent /= (now.QuadPart - lastCPU.QuadPart);
        percent /= numProcessors;
        lastCPU = now;
        lastUserCPU = user;
        lastSysCPU = sys;


        return percent * 100;
    }

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
CxSystemInfo::EOsType
CxSystemInfo::osGetOS() {
    /*DEBUG*/// n/a

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
    /*DEBUG*/// otOsType - n/a

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

        default:                        { sRes = xUNKNOWN_STRING;                  }    break;
    }
#elif xOS_ENV_UNIX
    //TODO: sFormatOsType
    utsname unKernelInfo= {{0}};

    int iRes = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, std::tstring_t());

    sRes = CxString::sFormat(xT("%s %s (%s) %s"), unKernelInfo.sysname, unKernelInfo.release, unKernelInfo.version, unKernelInfo.machine);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
CxSystemInfo::EOsArch
CxSystemInfo::oaGetOsArch() {
    /*DEBUG*/// n/a

    EOsArch oaRes = oaUnknown;

#if xOS_ENV_WIN
    #if xCPU_64BIT
        oaRes = oa64bit;
    #elif xCPU_32BIT
        BOOL blIs64BitOs          = FALSE;
        BOOL blIsWin32MethodExist = FALSE;
        {
            CxDll dlDll;
            blIsWin32MethodExist = ( dlDll.bLoad(xT("kernel32.dll")) && dlDll.bIsProcExists(xT("IsWow64Process")) );
        }
        BOOL blIsWow64Process    = ::IsWow64Process(CxCurrentProcess::hGetHandle(), &blIs64BitOs);

        oaRes = (blIsWin32MethodExist && blIsWow64Process && blIs64BitOs) ? oa64bit : oa32bit;
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
    /*DEBUG*/// n/a

    std::tstring_t sRes;

    switch (oaOsArch) {
        case CxSystemInfo::oa32bit:     sRes = xT("32-bit");    break;
        case CxSystemInfo::oa64bit:     sRes = xT("64-bit");    break;
        case CxSystemInfo::oaUnknown:   sRes = xUNKNOWN_STRING; break;

        default:                        sRes = xUNKNOWN_STRING; break;
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxSystemInfo::sGetComputerName() {
    /*DEBUG*/// n/a

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
    /*DEBUG*/

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
    /*DEBUG*/// n/a
    xCHECK_RET(cuiRootId != uiUserId, false);

    uiUserId = ::geteuid();
    /*DEBUG*/// n/a
    xCHECK_RET(cuiRootId != uiUserId, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxSystemInfo::sGetUserName() {
    /*DEBUG*/// n/a

    std::tstring_t sRes;

#if xOS_ENV_WIN
    DWORD   ulBuffSize        = UNLEN;
    tchar_t szBuff[UNLEN + 1] = {0};

    BOOL blRes = ::GetUserName(&szBuff[0], &ulBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, std::tstring_t());

    sRes.assign(szBuff, ulBuffSize);
#elif xOS_ENV_UNIX
    //http://www.metalshell.com/source_code/107/List_Users.html
    //http://www.metalshell.com/source_code/83/Get_GID_Name.html

    passwd *ppwPassword = ::getpwuid(getuid());
    /*DEBUG*/xASSERT_RET(NULL != ppwPassword, std::tstring_t());

    sRes.assign(ppwPassword->pw_name);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetNumOfCpus() {
    /*DEBUG*/// n/a

    ulong_t ulRes = 0UL;

#if xOS_ENV_WIN
    SYSTEM_INFO siSysInfo = {{0}};

    (void)::GetNativeSystemInfo(&siSysInfo);

    ulRes = siSysInfo.dwNumberOfProcessors;
#elif xOS_ENV_UNIX
    #if xOS_FREEBSD
        int    aiMib[]   = {CTL_HW, HW_NCPU};
        size_t uiResSize = sizeof(ulRes);

        int iRes = ::sysctl(aiMib, static_cast<u_int>( xARRAY_SIZE(aiMib) ), &ulRes, &uiResSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);
    #else
        long_t liRes = ::sysconf(_SC_NPROCESSORS_ONLN);
        /*DEBUG*/xASSERT_RET(- 1 != liRes, 0UL);

        ulRes = static_cast<ulong_t>( liRes );
    #endif
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
//TODO: ulGetCurrentCpuNum
/*static*/
ulong_t
CxSystemInfo::ulGetCurrentCpuNum() {
    /*DEBUG*/// n/a

    ulong_t ulRes = 0UL;

#if xOS_ENV_WIN
    #if (xWINVER >= xWIN32_7)
        ulRes = ::GetCurrentProcessorNumber();
        /*DEBUG*/// n/a
    #else
        //TODO: ulGetCurrentCpuNum
        /*_asm {mov eax, 1}
        _asm {cpuid}
        _asm {shr ebx, 24}
        _asm {mov eax, ebx}*/

        ulRes = 0UL;
    #endif
#elif xOS_ENV_UNIX
    #if xOS_FREEBSD
        //TODO: ulGetCurrentCpuNum
        ulRes = 0UL;
    #else
        #if defined(SYS_getcpu)
            ulong_t ulCpu = 0UL;

            int iRes = ::syscall(SYS_getcpu, &ulCpu, NULL, NULL);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

            ulRes = ulCpu;
        #else
            #if (xSTD_LIBC_GNU_VER > 2) || \
                (xSTD_LIBC_GNU_VER == 2 && (xSTD_LIBC_GNU_VER_MINOR > 6 || (xSTD_LIBC_GNU_VER_MINOR == 6 /*&& __GLIBC_PATCHLEVEL__ >= 19*/)))

                //for GLibc > 2.6.19
                //::getcpu() was added in kernel 2.6.19 for x86_64 and i386
                //int getcpu(unsigned *cpu, unsigned *nodestruct getcpu_cache *" tcache );
                uint_t uiCpu = 0U;

                int iRes = ::getcpu(&uiCpu, NULL, NULL);
                /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

                ulRes = uiCpu;
            #else
                ulRes = 0UL;
            #endif

            #if xTEMP_DISABLED
                //::sched_getcpu() function is available since glibc 2.6, it is glibc specific
                int iRes = ::sched_getcpu();
                /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);

                ulRes = static_cast<ulong_t>( iRes );
            #endif

        #endif
    #endif
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
//TODO: ullGetCpuSpeed
/*static*/
ulong_t
CxSystemInfo::ulGetCpuSpeed() {
    /*DEBUG*/// n/a

    ulong_t ulRes = 0ULL;

#if xOS_ENV_WIN
    DWORD dwCpuSpeedMHz = 0UL;
    HKEY  hKey          = NULL;
    DWORD dwBuffSize    = _MAX_PATH;

    LONG lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                               xT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"),
                               0UL,
                               KEY_READ,
                               &hKey);
    /*DEBUG*/xASSERT_RET(ERROR_SUCCESS == lRes, 0ULL);

    lRes = ::RegQueryValueEx(hKey, xT("~MHz"), NULL, NULL, &dwCpuSpeedMHz, &dwBuffSize);
    /*DEBUG*/xASSERT_RET(ERROR_SUCCESS == lRes, 0ULL);

    ulRes = dwCpuSpeedMHz;
#elif xOS_ENV_UNIX
    //TODO: iGetCpuSpeed
    ullRes = 0UL;

    #if xTODO
        FILE *pfCpuInfo = fopen("/proc/cpuinfo", "r");

        fclose(pfCpuInfo);
    #endif
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
/*static*/
ulong_t
CxSystemInfo::ulGetPageSize() {
    xDEBUG_VARS_NA;

    ulong_t ulRes = 0UL;

#if   xOS_ENV_WIN
    SYSTEM_INFO siSysInfo = {{0}};

    (void)::GetNativeSystemInfo(&siSysInfo);

    ulRes = siSysInfo.dwPageSize;
#elif xOS_ENV_UNIX
    #if   defined(_SC_PAGESIZE)
        #define xSC_PAGESIZE _SC_PAGESIZE
    #elif defined(_SC_PAGE_SIZE)
        #define xSC_PAGESIZE _SC_PAGE_SIZE
    #elif defined()
        #error xLib: xSC_PAGESIZE not defined
    #endif

    int iRes = ::sysconf(xSC_PAGESIZE);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, 0UL);
    /*DEBUG*/xASSERT_RET(0   <  iRes, 0UL);

    ulRes = static_cast<ulong_t>( iRes );
#endif

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
