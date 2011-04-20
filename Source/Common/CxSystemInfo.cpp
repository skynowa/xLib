/****************************************************************************
* Class name:  CxSystemInfo
* Description: system information
* File name:   CxSystemInfo.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.07.2009 11:52:01
*
*****************************************************************************/


#include <xLib/Common/CxSystemInfo.h>

#include <xLib/Filesystem/CxEnvironment.h>
#if defined(xOS_WIN)
    #include <Lmcons.h>
#elif defined(xOS_LINUX)
    #include <sys/utsname.h>
    #include <sys/sysinfo.h>
    #include <sched.h>
#endif

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: osGetOS (information about the current operating system)
/*static*/
CxSystemInfo::EOsType
CxSystemInfo::osGetOS() {
    /*DEBUG*/// n/a

#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    /*
    struct _OSVERSIONINFOW {
        DWORD dwOSVersionInfoSize;
        DWORD dwMajorVersion;
        DWORD dwMinorVersion;
        DWORD dwBuildNumber;
        DWORD dwPlatformId;
        WCHAR  szCSDVersion[ 128 ];     // Maintenance string for PSS usage
    }
    */

    /*
    Operating system                    Version number        Other
    -------------------------------------------------------------------------------------------
    Windows 7                            6.1    OSVERSIONINFOEX.wProductType == VER_NT_WORKSTATION
    Windows Server 2008 R2                6.1       OSVERSIONINFOEX.wProductType != VER_NT_WORKSTATION
    Windows Server 2008                    6.0       OSVERSIONINFOEX.wProductType != VER_NT_WORKSTATION
    Windows Vista                        6.0       OSVERSIONINFOEX.wProductType == VER_NT_WORKSTATION
    Windows Server 2003 R2                5.2       GetSystemMetrics(SM_SERVERR2) != 0
    Windows Home Server                    5.2       OSVERSIONINFOEX.wSuiteMask & VER_SUITE_WH_SERVER
    Windows Server 2003                    5.2       GetSystemMetrics(SM_SERVERR2) == 0
    Windows XP Professional x64 Edition    5.2    (OSVERSIONINFOEX.wProductType == VER_NT_WORKSTATION) && (SYSTEM_INFO.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
    Windows XP                            5.1       Not applicable
    Windows 2000                        5.0       Not applicable


    Windows NT    3.10
    Windows 98    4.10
    Windows 95    4.0
    1    30
    1    25
    1    20
    1    15
    1    10
    Win32s    1    0
    */

    OSVERSIONINFO ovVer = {0};

    ovVer.dwOSVersionInfoSize = sizeof(ovVer);
    bRes = ::GetVersionEx(&ovVer);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, otUnknown);

    switch (ovVer.dwPlatformId) {
        case VER_PLATFORM_WIN32s:
            {
                return otWindows3;
            }
            break;

        case VER_PLATFORM_WIN32_WINDOWS:
            {
                xCHECK_RET(0  == ovVer.dwMinorVersion, otWindows95);
                xCHECK_RET(10 == ovVer.dwMinorVersion, otWindows98);
                xCHECK_RET(90 == ovVer.dwMinorVersion, otWindows98);
            }
            break;

        case VER_PLATFORM_WIN32_NT:
            {
                xCHECK_RET(ovVer.dwMajorVersion <= 4,                              otWindowsNT);
                xCHECK_RET(5 == ovVer.dwMajorVersion && 0 == ovVer.dwMinorVersion, otWindows2000);
                xCHECK_RET(5 == ovVer.dwMajorVersion && 1 == ovVer.dwMinorVersion, otWindowsXP);
                xCHECK_RET(5 == ovVer.dwMajorVersion && 2 == ovVer.dwMinorVersion, otWindowsXPProx64Edition);
                xCHECK_RET(5 == ovVer.dwMajorVersion && 2 == ovVer.dwMinorVersion, otWindowsServer2003);
                xCHECK_RET(5 == ovVer.dwMajorVersion && 2 == ovVer.dwMinorVersion, otWindowsHomeServer);
                xCHECK_RET(5 == ovVer.dwMajorVersion && 2 == ovVer.dwMinorVersion, otWindowsServer2003R2);
                xCHECK_RET(6 == ovVer.dwMajorVersion && 0 == ovVer.dwMinorVersion, otWindowsVista);
                xCHECK_RET(6 == ovVer.dwMajorVersion && 0 == ovVer.dwMinorVersion, otWindowsServer2008);
                xCHECK_RET(6 == ovVer.dwMajorVersion && 1 == ovVer.dwMinorVersion, otWindowsServer2008R2);
                xCHECK_RET(6 == ovVer.dwMajorVersion && 1 == ovVer.dwMinorVersion, otWindows7);

                //for unknown windows/newest windows version
                return otUnknown;
            }
            break;

        default:
            {
                return otUnknown;
            }
            break;
    }

    return otUnknown;
#elif defined(xOS_LINUX)
    return otLinux;
#endif
}
//---------------------------------------------------------------------------
//DONE: oaGetOsArchitecture (get OS architecture)
/*static*/
CxSystemInfo::EOsArchitecture
CxSystemInfo::oaGetOsArchitecture() {
    /*DEBUG*/// n/a

    EOsArchitecture oaRes = oaUnknown;

#if defined(xOS_WIN)
    //TODO: xOS_WIN
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
#elif defined(xOS_LINUX)
    utsname unKernelInfo= {{0}};

    INT iRes = uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1   != iRes, oaUnknown);
    /*DEBUG*/xASSERT_RET(0 != tString(unKernelInfo.machine).size(), oaUnknown);

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

    //error
    else {
        /*DEBUG*/xASSERT_MSG_RET(FALSE, unKernelInfo.machine, oaUnknown);
        oaRes = oaUnknown;
    }
#endif

    return oaRes;
}
//---------------------------------------------------------------------------
//DONE: sFormatOsType ()
/*static*/
tString
CxSystemInfo::sFormatOsType(EOsType otOsType) {
    /*DEBUG*/// otOsType - n/a

    tString sRes;

#if defined(xOS_WIN)
    switch (otOsType) {
        case otWindows3:                   { sRes = xT("Windows 3.1");                }    break;
        case otWindows95:               { sRes = xT("Windows 95");                 }    break;
        case otWindows98:               { sRes = xT("Windows 98");                 }    break;
        case otWindowsNT:               { sRes = xT("Windows NT 4.0");             }    break;
        case otWindows2000:               { sRes = xT("Windows 2000");               }    break;
        case otWindowsXP:               { sRes = xT("Windows XP");                 }    break;
        case otWindowsXPProx64Edition:  { sRes = xT("Windows XP Pro x64 Edition"); }    break;
        case otWindowsServer2003:       { sRes = xT("Windows Server 2003");        }    break;
        case otWindowsHomeServer:       { sRes = xT("Windows Home Server");        }    break;
        case otWindowsServer2003R2:       { sRes = xT("Windows Server 2003 R2");     }    break;
        case otWindowsVista:               { sRes = xT("Windows Vista");              }    break;
        case otWindowsServer2008:       { sRes = xT("Windows Server 2008");        }    break;
        case otWindowsServer2008R2:       { sRes = xT("Windows Server 2008 R2");     }    break;
        case otWindows7:                   { sRes = xT("Windows 7");                  }    break;

        default:                          { sRes = xT("Unknown Windows OS");         }    break;
    }
#elif defined(xOS_LINUX)
    //Linux user-exm-5 2.6.35-27-generic #48-Ubuntu SMP Tue Feb 22 20:25:29 UTC 2011 i686 GNU/Linux

    /*struct utsname {
        sysname    char[65];  // "Linux"
        nodename   char[65];  // "user-exm-5"
        release    char[65];  // "2.6.35-24-generic"
        version    char[65];  // "#42-Ubuntu SMP Thu Dec 2 01:41:57 UTC 2010"
        machine    char[65];  // "i686"
        domainname char[65];  // "(none)"
    };*/

    utsname unKernelInfo= {{0}};

    INT iRes = uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, xT("Linux"));

    sRes.assign( CxString::sFormat(xT("%s %s (%s) %s"), unKernelInfo.sysname, unKernelInfo.release, unKernelInfo.version, unKernelInfo.machine) );

    //out:  Linux 2.6.35-27-generic (#48-Ubuntu SMP Tue Feb 22 20:25:29 UTC 2011) i686
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sGetComputerName (Retrieves the NetBIOS name of the local computer)
/*static*/
tString
CxSystemInfo::sGetComputerName() {
    /*DEBUG*/// n/a

    tString sRes;

#if defined(xOS_WIN)
    BOOL    bRes                                = FALSE;
    ULONG   ulBuffSize                          = MAX_COMPUTERNAME_LENGTH;
    TCHAR   szBuff[MAX_COMPUTERNAME_LENGTH + 1] = {0};

    bRes = ::GetComputerName(szBuff, &ulBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, xT("LOCALHOST"));

    sRes.assign(szBuff, ulBuffSize);
#elif defined(xOS_LINUX)
    utsname unKernelInfo= {{0}};

    INT iRes = uname(&unKernelInfo);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, xT("LOCALHOST"));

    sRes.assign(unKernelInfo.nodename);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bIsUserAnAdmin (is current user an admin)
/*static*/
BOOL
CxSystemInfo::bIsUserAnAdmin() {
    /*DEBUG*/

#if defined(xOS_WIN)
    ////BOOL bRes = IsUserAnAdmin();
    /////*DEBUG*/// n/a
    ////xCHECK_RET(FALSE == bRes, FALSE);

    HMODULE hMod = ::GetModuleHandle(xT("kernel32.dll"));
    /*DEBUG*/xASSERT_RET(NULL != hMod, FALSE);

    FARPROC fpAddr = ::GetProcAddress(hMod, "LoadLibraryW");
    xCHECK_RET(NULL == fpAddr, FALSE);
#elif defined(xOS_LINUX)
    const uid_t cuiRootId = 0;

    uid_t       uiUserId = - 1;

    uiUserId = getuid();
    /*DEBUG*/// n/a
    xCHECK_RET(cuiRootId != uiUserId, FALSE);

    uiUserId = geteuid();
    /*DEBUG*/// n/a
    xCHECK_RET(cuiRootId != uiUserId, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetUserName (Retrieves the name of the user associated with the current thread)
/*static*/
tString
CxSystemInfo::sGetUserName() {
    /*DEBUG*/// n/a

    tString sRes;

#if defined(xOS_WIN)
    BOOL  bRes              = FALSE;
    ULONG ulBuffSize        = UNLEN;
    TCHAR szBuff[UNLEN + 1] = {0};

    bRes = ::GetUserName(&szBuff[0], &ulBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, tString());

    sRes.assign(szBuff, ulBuffSize);
#elif defined(xOS_LINUX)
    //http://www.metalshell.com/source_code/107/List_Users.html
    //http://www.metalshell.com/source_code/83/Get_GID_Name.html

    passwd *ppwPassword = getpwuid(getuid());
    /*DEBUG*/xASSERT_RET(NULL != ppwPassword, tString());

    sRes.assign(ppwPassword->pw_name);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: ulGetNumOfCPUs ()
/*static*/
ULONG
CxSystemInfo::ulGetNumOfCPUs() {
    /*DEBUG*/// n/a

    ULONG ulRes = 0;

#if defined(xOS_WIN)
    SYSTEM_INFO siSysInfo = {{0}};

    ::GetSystemInfo(&siSysInfo);
    /*DEBUG*/// n/a

    ulRes = siSysInfo.dwNumberOfProcessors;
#elif defined(xOS_LINUX)
    //--------------------------------------------------
    //1-st version
    ////INT iNumberOfProcessors = get_nprocs();
    /////*DEBUG*/xASSERT_RET(0 < iNumberOfProcessors, 0);

    ////ulRes = static_cast<ULONG>( iNumberOfProcessors );

    //--------------------------------------------------
    //2-nd version
    ulRes = static_cast<ULONG>( sysconf(_SC_NPROCESSORS_ONLN) );
    /*DEBUG*/xASSERT_RET(static_cast<ULONG>( -1 ) != ulRes, 0);
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
//TODO: ulGetCurrentCpuNum (Retrieves the number of the processor the current thread was running on during the call to this function)
/*static*/
ULONG
CxSystemInfo::ulGetCurrentCpuNum() {
    /*DEBUG*/// n/a

    ULONG ulRes = - 1;

#if defined(xOS_WIN)
    #if (xWINVER >= xWIN32_7)
        ulRes = ::GetCurrentProcessorNumber();
        /*DEBUG*/// n/a
    #else
        //TODO: ulGetCurrentCpuNum
        /*_asm {mov eax, 1}
        _asm {cpuid}
        _asm {shr ebx, 24}
        _asm {mov eax, ebx}*/

        ulRes = 0;
    #endif
#elif defined(xOS_LINUX)
    ulRes = static_cast<ULONG>( sched_getcpu() );
    /*DEBUG*/xASSERT_RET(static_cast<ULONG>( - 1) != ulRes, - 1);
#endif

    return ulRes;
}
//---------------------------------------------------------------------------
//TODO: bIsUnicodeOS (is OS support unicode)
BOOL
CxSystemInfo::bIsUnicodeOS()  {
    /*DEBUG*/// n/a

    BOOL bRes = FALSE;

#if defined(xOS_WIN)
    OSVERSIONINFOW oviInfo = {0};

    oviInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);

    bRes = (0 != ::GetVersionExW(&oviInfo));
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    bRes = TRUE;
#endif

    return bRes;
}
//---------------------------------------------------------------------------
//TODO: - iGetCpuSpeed (calculates the CPU speed in MHz)
/*static*/
INT
CxSystemInfo::iGetCpuSpeed() {
    /*DEBUG*/// n/a

    INT iRes = - 1;

#if defined(xOS_WIN)
    //TODO: xOS_WIN
//    //TODO: CxCycle
//    class CxCycle {
//        public:
//            static /*inline*/ unsigned __int64 ullGetCount();
//    };
//    unsigned __int64 CxCycle::ullGetCount() {
//            UINT uiTimeHigh = 0;
//            UINT uiTimeLow  = 0;
//
//            __asm {
//                rdtsc
//                mov uiTimeHigh, edx;
//                mov uiTimeLow,  eax;
//            }
//
//            return ((unsigned __int64)uiTimeHigh << 32) + (unsigned __int64)uiTimeLow;
//    };
//
//
//    const ULONGLONG ullStartCycle = CxCycle::ullGetCount();
//
//    ::Sleep(1000);
//
//    iRes = static_cast<INT>( (CxCycle::ullGetCount() - ullStartCycle) / 1000000 );

    xNOT_IMPLEMENTED_RET(- 1);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    xNOT_IMPLEMENTED_RET(- 1);
#endif

    return iRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxSystemInfo (construcor)
/*virtual*/
CxSystemInfo::CxSystemInfo() {

}
//---------------------------------------------------------------------------
//DONE: ~CxSystemInfo (destructor)
CxSystemInfo::~CxSystemInfo(){

}
//---------------------------------------------------------------------------
