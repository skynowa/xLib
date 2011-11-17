/**
 * \file  CxSystemInfo.cpp
 * \brief system information
 */


#include <xLib/Common/CxSystemInfo.h>

#include <xLib/Filesystem/CxEnvironment.h>


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
    BOOL bRes = ::GetVersionEx(&ovVer);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, otUnknown);

    switch (ovVer.dwPlatformId) {
        case VER_PLATFORM_WIN32s: {
                otRes = otWindows3;
            }
            break;

        case VER_PLATFORM_WIN32_WINDOWS: {
                xCHECK_DO(0  == ovVer.dwMinorVersion, otRes = otWindows95; break);
                xCHECK_DO(10 == ovVer.dwMinorVersion, otRes = otWindows98; break);
                xCHECK_DO(90 == ovVer.dwMinorVersion, otRes = otWindows98; break);
            }
            break;

        case VER_PLATFORM_WIN32_NT: {
                xCHECK_DO(ovVer.dwMajorVersion <= 4,                              otRes = otWindowsNT; break);
                xCHECK_DO(5 == ovVer.dwMajorVersion && 0 == ovVer.dwMinorVersion, otRes = otWindows2000; break);
                xCHECK_DO(5 == ovVer.dwMajorVersion && 1 == ovVer.dwMinorVersion, otRes = otWindowsXP; break);
                xCHECK_DO(5 == ovVer.dwMajorVersion && 2 == ovVer.dwMinorVersion, otRes = otWindowsXPProx64Edition; break);
                xCHECK_DO(5 == ovVer.dwMajorVersion && 2 == ovVer.dwMinorVersion, otRes = otWindowsServer2003; break);
                xCHECK_DO(5 == ovVer.dwMajorVersion && 2 == ovVer.dwMinorVersion, otRes = otWindowsHomeServer; break);
                xCHECK_DO(5 == ovVer.dwMajorVersion && 2 == ovVer.dwMinorVersion, otRes = otWindowsServer2003R2; break);
                xCHECK_DO(6 == ovVer.dwMajorVersion && 0 == ovVer.dwMinorVersion, otRes = otWindowsVista; break);
                xCHECK_DO(6 == ovVer.dwMajorVersion && 0 == ovVer.dwMinorVersion, otRes = otWindowsServer2008; break);
                xCHECK_DO(6 == ovVer.dwMajorVersion && 1 == ovVer.dwMinorVersion, otRes = otWindowsServer2008R2; break);
                xCHECK_DO(6 == ovVer.dwMajorVersion && 1 == ovVer.dwMinorVersion, otRes = otWindows7; break);

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

    if      (TRUE == CxString::bCompareNoCase(xT("Linux"), unKernelInfo.sysname)) {
        otRes = otLinux;
    }
    else if (TRUE == CxString::bCompareNoCase(xT("FreeBSD"), unKernelInfo.sysname)) {
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
std::string_t
CxSystemInfo::sFormatOsType(
    const EOsType otOsType
)
{
    /*DEBUG*/// otOsType - n/a

    std::string_t sRes;

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

        default:                        { sRes = xT("<unknown>");                  }    break;
    }
#elif xOS_ENV_UNIX
    //TODO: sFormatOsType
    utsname unKernelInfo= {{0}};

    int iRes = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, std::string_t());

    sRes.assign( CxString::sFormat(xT("%s %s (%s) %s"), unKernelInfo.sysname, unKernelInfo.release, unKernelInfo.version, unKernelInfo.machine) );
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
    //TODO: oaGetOsArchitecture
    //http://www.tek-tips.com/viewthread.cfm?qid=1573774&page=6


    SYSTEM_INFO siSysInfo = {{0}};

    ::GetSystemInfo(&siSysInfo);
    /*DEBUG*/// n/a

    switch (siSysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_INTEL:
            oaRes = oa32bit;
            break;

        case PROCESSOR_ARCHITECTURE_AMD64:
        case PROCESSOR_ARCHITECTURE_IA64:
            oaRes = oa64bit;
            break;

        case PROCESSOR_ARCHITECTURE_UNKNOWN:
            /*DEBUG*/xASSERT_RET(FALSE, oaUnknown);
            oaRes = oaUnknown;
            break;

        default:
            /*DEBUG*/xASSERT_RET(FALSE, oaUnknown);
            oaRes = oaUnknown;
            break;
    }
#elif xOS_ENV_UNIX
    utsname unKernelInfo= {{0}};

    int iRes = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes,                                 oaUnknown);
    /*DEBUG*/xASSERT_RET(0   != std::string_t(unKernelInfo.machine).size(), oaUnknown);

    //32-bit checks
    if      (TRUE == CxString::bCompareNoCase(xT("i386"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }
    else if (TRUE == CxString::bCompareNoCase(xT("i486"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }
    else if (TRUE == CxString::bCompareNoCase(xT("i586"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }
    else if (TRUE == CxString::bCompareNoCase(xT("i686"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }

    //64-bit checks
    else if (TRUE == CxString::bCompareNoCase(xT("x86_64"), unKernelInfo.machine)) {
        oaRes = oa64bit;
    }
    else if (TRUE == CxString::bCompareNoCase(xT("ia64"), unKernelInfo.machine)) {
        oaRes = oa64bit;
    }
    else if (TRUE == CxString::bCompareNoCase(xT("amd64"), unKernelInfo.machine)) {
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
std::string_t
CxSystemInfo::sFormatOsArch(
    const EOsArch oaOsArch
)
{
    /*DEBUG*/// n/a

    std::string_t sRes;

    switch (oaOsArch) {
        case CxSystemInfo::oa32bit:     sRes = xT("32-bit");    break;
        case CxSystemInfo::oa64bit:     sRes = xT("64-bit");    break;
        case CxSystemInfo::oaUnknown:   sRes = xT("<unknown>"); break;

        default:                        sRes = xT("<unknown>"); break;
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxSystemInfo::sGetComputerName() {
    /*DEBUG*/// n/a

    std::string_t sRes;

#if xOS_ENV_WIN
    ULONG   ulBuffSize                          = MAX_COMPUTERNAME_LENGTH;
    char_t   szBuff[MAX_COMPUTERNAME_LENGTH + 1] = {0};

    BOOL bRes = ::GetComputerName(szBuff, &ulBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, xT("LOCALHOST"));

    sRes.assign(szBuff, ulBuffSize);
#elif xOS_ENV_UNIX
    utsname unKernelInfo= {{0}};

    int iRes = ::uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, xT("LOCALHOST"));

    sRes.assign(unKernelInfo.nodename);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxSystemInfo::bIsUserAnAdmin() {
    /*DEBUG*/

#if xOS_ENV_WIN
    #if xTEMP_DISABLED
        BOOL bRes = IsUserAnAdmin();
        /*DEBUG*/// n/a
        xCHECK_RET(FALSE == bRes, FALSE);
    #endif

    HMODULE hMod = ::GetModuleHandle(xT("kernel32.dll"));
    /*DEBUG*/xASSERT_RET(NULL != hMod, FALSE);

    FARPROC fpAddr = ::GetProcAddress(hMod, "LoadLibraryW");
    xCHECK_RET(NULL == fpAddr, FALSE);
#elif xOS_ENV_UNIX
    const uid_t cuiRootId = 0;

    uid_t       uiUserId  = 0;

    uiUserId = ::getuid();
    /*DEBUG*/// n/a
    xCHECK_RET(cuiRootId != uiUserId, FALSE);

    uiUserId = ::geteuid();
    /*DEBUG*/// n/a
    xCHECK_RET(cuiRootId != uiUserId, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxSystemInfo::sGetUserName() {
    /*DEBUG*/// n/a

    std::string_t sRes;

#if xOS_ENV_WIN
    ULONG ulBuffSize        = UNLEN;
    char_t szBuff[UNLEN + 1] = {0};

    BOOL bRes = ::GetUserName(&szBuff[0], &ulBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::string_t());

    sRes.assign(szBuff, ulBuffSize);
#elif xOS_ENV_UNIX
    //http://www.metalshell.com/source_code/107/List_Users.html
    //http://www.metalshell.com/source_code/83/Get_GID_Name.html

    passwd *ppwPassword = ::getpwuid(getuid());
    /*DEBUG*/xASSERT_RET(NULL != ppwPassword, std::string_t());

    sRes.assign(ppwPassword->pw_name);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
ULONG
CxSystemInfo::ulGetNumOfCpus() {
    /*DEBUG*/// n/a

    ULONG ulRes = 0UL;

#if xOS_ENV_WIN
    SYSTEM_INFO siSysInfo = {{0}};

    ::GetSystemInfo(&siSysInfo);
    /*DEBUG*/// n/a

    ulRes = siSysInfo.dwNumberOfProcessors;
#elif xOS_ENV_UNIX
    #if defined(xOS_FREEBSD)
        int    aiMib[]   = {CTL_HW, HW_NCPU};
        size_t uiResSize = sizeof(ulRes);

        int iRes = sysctl(aiMib, static_cast<u_int>( xARRAY_SIZE(aiMib) ), &ulRes, &uiResSize, NULL, 0);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, 0);
    #else
        LONG liRes = ::sysconf(_SC_NPROCESSORS_ONLN);
        /*DEBUG*/xASSERT_RET(- 1 != liRes, 0);

        ulRes = static_cast<ULONG>( liRes );
    #endif
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
//TODO: ulGetCurrentCpuNum
/*static*/
ULONG
CxSystemInfo::ulGetCurrentCpuNum() {
    /*DEBUG*/// n/a

    ULONG ulRes = static_cast<ULONG>( - 1 );

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
    #if defined(xOS_FREEBSD)
        //TODO: ulGetCurrentCpuNum
        ulRes = 0;
    #else
        #if defined(SYS_getcpu)
            ULONG ulCpu = 0UL;

            int iRes = ::syscall(SYS_getcpu, &ulCpu, NULL, NULL);
            /*DEBUG*/xASSERT_RET(- 1 != iRes, static_cast<ULONG>( - 1 ));

            ulRes = ulCpu;
        #else
            int iRes = sched_getcpu();
            /*DEBUG*/xASSERT_RET(- 1 != iRes, static_cast<ULONG>( - 1 ));

            ulRes = static_cast<ULONG>( iRes );
        #endif
    #endif
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
//TODO: bIsUnicodeOS
BOOL
CxSystemInfo::bIsUnicodeOS()  {
    /*DEBUG*/// n/a

    BOOL bRes = FALSE;

#if xOS_ENV_WIN
    OSVERSIONINFOW oviInfo = {0};

    oviInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);

    bRes = (0 != ::GetVersionExW(&oviInfo));
#elif xOS_ENV_UNIX
    //TODO: bIsUnicodeOS
    bRes = TRUE;
#endif

    return bRes;
}
//---------------------------------------------------------------------------
//TODO: ullGetCpuSpeed
/*static*/
ULONGLONG
CxSystemInfo::ullGetCpuSpeed() {
    /*DEBUG*/// n/a

    ULONGLONG ullRes = 0ULL;

#if xOS_ENV_WIN
    //TODO: ullGetCpuSpeed
    #if xTODO
        //TODO: CxCycle
        class CxCycle {
            public:
                static /*inline*/ unsigned __int64 ullGetCount();
        };

        unsigned __int64 CxCycle::ullGetCount() {
                UINT uiTimeHigh = 0;
                UINT uiTimeLow  = 0;

                __asm {
                    rdtsc
                    mov uiTimeHigh, edx;
                    mov uiTimeLow,  eax;
                }

                return ((unsigned __int64)uiTimeHigh << 32) + (unsigned __int64)uiTimeLow;
        };


        const ULONGLONG ullStartCycle = CxCycle::ullGetCount();

        bSleep(1000);

        ullRes = (CxCycle::ullGetCount() - ullStartCycle) / 1000000;
    #endif

    ullRes = 0UL;
#elif xOS_ENV_UNIX
    //TODO: iGetCpuSpeed
    ullRes = 0UL;
#endif

    return ullRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*virtual*/
CxSystemInfo::CxSystemInfo() {

}
//---------------------------------------------------------------------------
CxSystemInfo::~CxSystemInfo(){

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
