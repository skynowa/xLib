/**
 * \file  CxSystemInfo.cpp
 * \brief system information
 */


#include <xLib/Common/CxSystemInfo.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Common/CxShell.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Sync/CxCurrentProcess.h>

#if   xOS_ENV_WIN
    #include <shlobj.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
CxSystemInfo::ExOsType
CxSystemInfo::os() {
    ExOsType otRes = otUnknown;

#if   xOS_ENV_WIN
    OSVERSIONINFO ovVer = {0};
    ovVer.dwOSVersionInfoSize = sizeof(ovVer);

    BOOL blRes = ::GetVersionEx(&ovVer);
    xTEST_DIFF(FALSE, blRes);

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

                // for unknown windows/newest windows version
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
    xTEST_DIFF(- 1, iRv);

    if      (true == CxString::compareNoCase(xT("Linux"), unKernelInfo.sysname)) {
        otRes = otLinux;
    }
    else if (true == CxString::compareNoCase(xT("FreeBSD"), unKernelInfo.sysname)) {
        otRes = otFreeBSD;
    }
    else {
        otRes = otUnknown;
    }
#endif

    return otRes;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxSystemInfo::formatOsType(
    const ExOsType &a_otOsType
)
{
    xTEST_NA(a_otOsType);

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    switch (a_otOsType) {
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
    if (os() == a_otOsType) {
        // current OS type - get info about OS kernel
        utsname unKernelInfo= {{0}};

        int iRv = ::uname(&unKernelInfo);
        xTEST_DIFF(- 1, iRv);

        sRv = CxString::format(xT("%s %s (%s) %s"),
                                 unKernelInfo.sysname, unKernelInfo.release,
                                 unKernelInfo.version, unKernelInfo.machine);
    } else {
        // not current OS type, can't get info about OS kernel - return simple-formatted string
        switch (a_otOsType) {
            case otLinux:   { sRv = xT("Linux");              } break;
            case otFreeBSD: { sRv = xT("FreeBSD");            } break;

            default:        { sRv = CxConst::xUNKNOWN_STRING; } break;
        }
    }
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
CxSystemInfo::ExOsArch
CxSystemInfo::osArch() {
    ExOsArch oaRes = oaUnknown;

#if   xOS_ENV_WIN
    #if   xARCH_X86
        BOOL blIsFuncExist = FALSE;
        {
            CxDll dlDll;

            dlDll.load(xT("kernel32.dll"));
            blIsFuncExist = dlDll.isProcExists(xT("IsWow64Process"));
        }

        BOOL blIs64BitOs = FALSE;
        BOOL blIsWow64Process = ::IsWow64Process(CxCurrentProcess::handle(), &blIs64BitOs);

        oaRes = (blIsFuncExist && blIsWow64Process && blIs64BitOs) ? oa64bit : oa32bit;
    #elif xARCH_X64
        oaRes = oa64bit;
    #else
        // 64-bit Windows does not support Win16
        oaRes = oaUnknown;
    #endif
#elif xOS_ENV_UNIX
    utsname unKernelInfo= {{0}};

    int iRv = ::uname(&unKernelInfo);
    xTEST_DIFF(- 1, iRv);
    // TODO: xTEST_DIFF(0,   strlen(unKernelInfo.machine));

    //32-bit checks
    if      (true == CxString::compareNoCase(xT("i386"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }
    else if (true == CxString::compareNoCase(xT("i486"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }
    else if (true == CxString::compareNoCase(xT("i586"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }
    else if (true == CxString::compareNoCase(xT("i686"), unKernelInfo.machine)) {
        oaRes = oa32bit;
    }

    //64-bit checks
    else if (true == CxString::compareNoCase(xT("x86_64"), unKernelInfo.machine)) {
        oaRes = oa64bit;
    }
    else if (true == CxString::compareNoCase(xT("ia64"), unKernelInfo.machine)) {
        oaRes = oa64bit;
    }
    else if (true == CxString::compareNoCase(xT("amd64"), unKernelInfo.machine)) {
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
/* static */
std::tstring_t
CxSystemInfo::formatOsArch(
    const ExOsArch &a_oaOsArch
)
{
    std::tstring_t sRv;

    switch (a_oaOsArch) {
        case CxSystemInfo::oa32bit:     sRv = xT("32-bit");             break;
        case CxSystemInfo::oa64bit:     sRv = xT("64-bit");             break;
        case CxSystemInfo::oaUnknown:   sRv = CxConst::xUNKNOWN_STRING; break;

        default:                        sRv = CxConst::xUNKNOWN_STRING; break;
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxSystemInfo::desktopName() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    const std::tstring_t  csNativeDesktop = xT("explorer.exe");
    const CxProcess::id_t culId           = CxProcess::idByName(csNativeDesktop);

    bool bRv = CxProcess::isRunning(culId);
    if (true == bRv) {
        sRv = csNativeDesktop;
    } else {
        // TODO: implement some checks for detecting Windows shell
    }

    xTEST_EQ(false, sRv.empty());
#elif xOS_ENV_UNIX
    sRv = CxEnvironment::var(xT("DESKTOP_SESSION"));
    xTEST_EQ(false, sRv.empty());
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxSystemInfo::hostName() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    ulong_t ulBuffSize                 = xHOST_NAME_MAX;
    tchar_t szBuff[xHOST_NAME_MAX + 1] = {0};

    BOOL blRes = ::GetComputerName(szBuff, &ulBuffSize);
    xTEST_DIFF(FALSE, blRes);

    sRv.assign(szBuff, ulBuffSize);
#elif xOS_ENV_UNIX
    utsname unKernelInfo= {{0}};

    int iRv = ::uname(&unKernelInfo);
    xTEST_DIFF(- 1, iRv);

    sRv.assign(unKernelInfo.nodename);
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
bool
CxSystemInfo::isUserAdmin() {
#if   xOS_ENV_WIN
    bool                     bIsAdmin       = false;
    SID_IDENTIFIER_AUTHORITY siaNtAuthority = { SECURITY_NT_AUTHORITY };
    PSID                     psAdminiGroup  = NULL;

    BOOL blRes = ::AllocateAndInitializeSid(&siaNtAuthority, 2,
                                            SECURITY_BUILTIN_DOMAIN_RID,
                                            DOMAIN_ALIAS_RID_ADMINS,
                                            0UL, 0UL, 0UL, 0UL, 0UL, 0UL,
                                            &psAdminiGroup);
    xCHECK_RET(FALSE == blRes, false);

    {
        BOOL blIsMember = FALSE;

        blRes = ::CheckTokenMembership(NULL, psAdminiGroup, &blIsMember);
        if (FALSE == blRes || FALSE == blIsMember) {
            bIsAdmin = false;
        } else {
            bIsAdmin = true;
        }
    }

    (void)::FreeSid(psAdminiGroup);

    xCHECK_RET(false == bIsAdmin, false);
#elif xOS_ENV_UNIX
    const uid_t cuiRootId = 0;

    uid_t       uiUserId  = 0;

    uiUserId = ::getuid();
    xTESTS_NA;
    xCHECK_RET(cuiRootId != uiUserId, false);

    uiUserId = ::geteuid();
    xTESTS_NA;
    xCHECK_RET(cuiRootId != uiUserId, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxSystemInfo::userName() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD   ulBuffSize        = UNLEN;
    tchar_t szBuff[UNLEN + 1] = {0};

    BOOL blRes = ::GetUserName(&szBuff[0], &ulBuffSize);
    xTEST_DIFF(FALSE, blRes);

    sRv.assign(szBuff, ulBuffSize);
#elif xOS_ENV_UNIX
    struct passwd pwdPasswd = {0};

    _passwdFileEntry(&pwdPasswd);
    xTEST_PTR(pwdPasswd.pw_name);

    sRv.assign(pwdPasswd.pw_name);
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxSystemInfo::useHomeDir() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    tchar_t szBuff[MAX_PATH + 1] = {0};

    HRESULT hrRes = SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0UL, &szBuff[0]);
    xTEST_EQ(true, S_OK == hrRes);

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

    bool bRv = CxEnvironment::isExists(xT("HOME"));
    if (true == bRv) {
        sRv = CxEnvironment::var(xT("HOME"));
    } else {
        struct passwd pwdPasswd = {0};

        _passwdFileEntry(&pwdPasswd);
        xTEST_PTR(pwdPasswd.pw_dir);

        sRv.assign(pwdPasswd.pw_dir);
    }
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxSystemInfo::userShellPath() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    LPITEMIDLIST pidl = {0};

    HRESULT hrRv = ::SHGetSpecialFolderLocation(NULL, CSIDL_WINDOWS, &pidl);
    xTEST_EQ(S_OK, hrRv);

    tchar_t szBuff[MAX_PATH + 1] = {0};

    BOOL blRv = ::SHGetPathFromIDList(pidl, szBuff);
    xTEST_DIFF(FALSE, blRv);

    sRv.append(szBuff);
    sRv.append(CxConst::xSLASH);
    sRv.append(xT("explorer.exe"));
#elif xOS_ENV_UNIX
    struct passwd pwdPasswd = {0};

    _passwdFileEntry(&pwdPasswd);
    xTEST_PTR(pwdPasswd.pw_shell);

    sRv.assign(pwdPasswd.pw_shell);
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
ulong_t
CxSystemInfo::numOfCpus() {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    SYSTEM_INFO siSysInfo = {{0}};

    (void)::GetNativeSystemInfo(&siSysInfo);

    ulRv = siSysInfo.dwNumberOfProcessors;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        long_t liRv = ::sysconf(_SC_NPROCESSORS_ONLN);
        xTEST_DIFF(- 1L, liRv);

        ulRv = static_cast<ulong_t>( liRv );
    #elif xOS_FREEBSD
        int    aiMib[]   = {CTL_HW, HW_NCPU};
        size_t uiResSize = sizeof(ulRv);

        int iRv = ::sysctl(aiMib, static_cast<u_int>( xARRAY_SIZE(aiMib) ), &ulRv, &uiResSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);
    #endif
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
ulong_t
CxSystemInfo::currentCpuNum() {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    typedef DWORD (WINAPI *DllGetCurrentProcessorNumber_t)(void);

    CxDll dlDll;

    dlDll.load(xT("kernel32.dll"));

    bool bRv = dlDll.isProcExists(xT("GetCurrentProcessorNumber"));
    xCHECK_RET(false == bRv, 0UL);

    DllGetCurrentProcessorNumber_t DllGetCurrentProcessorNumber = (DllGetCurrentProcessorNumber_t)dlDll.procAddress(xT("GetCurrentProcessorNumber"));
    xTEST_PTR(DllGetCurrentProcessorNumber);

    ulRv = DllGetCurrentProcessorNumber();
    xTEST_NA(ulRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        #if defined(SYS_getcpu)
            ulong_t ulCpu = 0UL;

            int iRv = ::syscall(SYS_getcpu, &ulCpu, NULL, NULL);
            xTEST_DIFF(- 1, iRv);

            ulRv = ulCpu;
        #else
            #if (xSTD_LIBC_GNU_VER_MAJOR > 2) || \
                (xSTD_LIBC_GNU_VER_MAJOR == 2 && xSTD_LIBC_GNU_VER_MINOR > 6)

                // ::sched_getcpu() function is available since glibc 2.6, it is glibc specific
                int iRv = ::sched_getcpu();
                xTEST_DIFF(- 1, iRv);

                ulRv = static_cast<ulong_t>( iRv );
            #else
                //TODO: ulGetCurrentCpuNum
                ulRv = 0UL;
            #endif

            #if xTEMP_DISABLED
                // ::getcpu() was added in kernel 2.6.19 for x86_64 and i386
                uint_t uiCpu = 0U;

                int iRv = ::getcpu(&uiCpu, NULL, NULL);
                xTEST_DIFF(- 1, iRv);

                ulRv = uiCpu;
            #endif

        #endif
    #elif xOS_FREEBSD
        // OS_NOT_SUPPORTED: ulGetCurrentCpuNum
        ulRv = 0UL;
    #endif
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
CxSystemInfo::ExCpuVendor
CxSystemInfo::cpuVendor() {
    ExCpuVendor cvRes = cvUnknown;
    std::string sValue;

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW || xCOMPILER_MS
        int    aiCpuInfo[4]     = {0};
        char   szMan[13]        = {0};

        (void)::__cpuid(aiCpuInfo, 0);

        *reinterpret_cast<int *>( &szMan[0] ) = aiCpuInfo[1];
        *reinterpret_cast<int *>( &szMan[4] ) = aiCpuInfo[3];
        *reinterpret_cast<int *>( &szMan[8] ) = aiCpuInfo[2];

        sValue = std::string(szMan);
        xTEST_EQ(false, sValue.empty());
    #elif xCOMPILER_CODEGEAR
        // TODO: CxSystemInfo::cvGetCpuVendor()
        sValue = std::tstring_t();
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "vendor_id : GenuineIntel"
        sValue = CxPath::procValue(xT("/proc/cpuinfo"), xT("vendor_id"));
        xTEST_EQ(false, sValue.empty());
    #elif xOS_FREEBSD
        // Use gcc 4.4 provided cpuid intrinsic
        // 32 bit fpic requires ebx be preserved
        struct _SFunctor {
            #if (defined(__pic__) || defined(__APPLE__)) && defined(__i386__)
                static inline void
                __cpuid(int aiCpuInfo[4], int iInfoType) {
                    __asm__ volatile (
                        "mov %%ebx, %%edi\n"
                        "cpuid\n"
                        "xchg %%edi, %%ebx\n"
                        : "=a"(aiCpuInfo[0]), "=D"(aiCpuInfo[1]), "=c"(aiCpuInfo[2]), "=d"(aiCpuInfo[3])
                        : "a"(iInfoType)
                    );
                }
            #elif defined(__i386__) || defined(__x86_64__)
                static inline void
                __cpuid(int aiCpuInfo[4], int iInfoType) {
                    __asm__ volatile (
                        "cpuid\n"
                        : "=a"(aiCpuInfo[0]), "=b"(aiCpuInfo[1]), "=c"(aiCpuInfo[2]), "=d"(aiCpuInfo[3])
                        : "a"(iInfoType)
                    );
                }
            #else
                // OS_NOT_SUPPORTED: CxSystemInfo::cvGetCpuVendor()
                #error xLib: Can not define __cpuid
            #endif
        };

        int aiCpuInfo[4] = {0};

        (void)_SFunctor::__cpuid(aiCpuInfo, 0);

        aiCpuInfo[0] = aiCpuInfo[1];  // Reorder output
        aiCpuInfo[1] = aiCpuInfo[3];
        aiCpuInfo[2] = aiCpuInfo[2];
        aiCpuInfo[3] = 0;

        sValue = std::string(CxUtils::reinterpretCastT<char *>( &aiCpuInfo[0] ));
        xTEST_EQ(false, sValue.empty());
    #endif
#endif
    if      (std::string("GenuineIntel") == sValue) {
        cvRes = cvIntel;
    }
    else if (std::string("AuthenticAMD") == sValue) {
        cvRes = cvAmd;
    }
    else {
        cvRes = cvUnknown;
    }

    return cvRes;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxSystemInfo::cpuModel() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW || xCOMPILER_MS
        char szMan[13] = {0};

        // get highest feature
        {
            int aiCpuInfo[4] = {0};

            (void)::__cpuid(aiCpuInfo, 0);

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

            std::tstring_t sCpuName = CxString::trimSpace( xS2TS(szCpuName) );

            sRv = CxString::format(xT("%s (%s)"), sCpuName.c_str(), szMan);
        } else {
            sRv = CxString::format(xT("%s"), szMan);
        }
    #elif xCOMPILER_CODEGEAR
        sRv = std::tstring_t();
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "model name    : Intel(R) Xeon(R) CPU           E5620  @ 2.40GHz"
        std::tstring_t sValue = CxPath::procValue(xT("/proc/cpuinfo"), xT("model name"));
        xTEST_EQ(false, sValue.empty());

        sRv = sValue;
    #elif xOS_FREEBSD
        int         iRv         = - 1;
        std::string sValue;
        size_t      uiValueSize = 0;

        iRv = ::sysctlbyname("hw.model", NULL, &uiValueSize, NULL, 0U);
        xTEST_DIFF(- 1, iRv);
        xTEST_DIFF(size_t(0), uiValueSize);

        sValue.resize(uiValueSize);

        iRv = ::sysctlbyname("hw.model", &sValue.at(0), &uiValueSize, NULL, 0U);
        xTEST_DIFF(- 1, iRv);
        xTEST_EQ(sValue.size(), uiValueSize);

        sRv = sValue;
    #endif
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
ulong_t
CxSystemInfo::cpuSpeed() {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    DWORD ulCpuSpeedMHz = 0UL;
    DWORD dwBuffSize    = sizeof(ulCpuSpeedMHz);
    HKEY  hKey          = NULL;

    LONG lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, xT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0UL, KEY_READ, &hKey);
    xTEST_EQ(ERROR_SUCCESS, lRes);

    lRes = ::RegQueryValueEx(hKey, xT("~MHz"), NULL, NULL, reinterpret_cast<LPBYTE>( &ulCpuSpeedMHz ), &dwBuffSize);
    xTEST_EQ(ERROR_SUCCESS, lRes);

    lRes = ::RegCloseKey(hKey);    hKey = NULL;
    xTEST_EQ(ERROR_SUCCESS, lRes);

    ulRv = ulCpuSpeedMHz;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "cpu MHz         : 2796.380"
        std::tstring_t sValue = CxPath::procValue(xT("/proc/cpuinfo"), xT("cpu MHz"));
        xTEST_EQ(false, sValue.empty());

        double dCpuSpeedMHz = CxString::cast<double>( sValue );

        ulRv = CxUtils::roundIntT<ulong_t>( dCpuSpeedMHz );
    #elif xOS_FREEBSD
        ulong_t ulCpuSpeedMHz     = 0UL;
        size_t  uiCpuSpeedMHzSize = sizeof(ulCpuSpeedMHz);

        int iRv = ::sysctlbyname("hw.clockrate", &ulCpuSpeedMHz, &uiCpuSpeedMHzSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);

        ulRv = ulCpuSpeedMHz;
    #endif
#endif

    return ulRv;
}
//---------------------------------------------------------------------------
/* static */
ulong_t
CxSystemInfo::cpuUsage() {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    double                dRv              = 0.0;

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
    xTEST_DIFF(FALSE, blRes);

    (void)::CopyMemory(&ulSysIdle,   &ftSysIdle,   sizeof(ftSysIdle));
    (void)::CopyMemory(&ulSysKernel, &ftSysKernel, sizeof(ftSysKernel));
    (void)::CopyMemory(&ulSysUser,   &ftSysUser,   sizeof(ftSysUser));

    dRv = CxUtils::safeDivT(
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
        double             dRv                = 0.0;
        int                iRv                = - 1;

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

        // read proc file for the first time
        if (true == bIsFirstRun) {
            FILE *pFile = fopen("/proc/stat", "r");
            xTEST_PTR(pFile);

            iRv = fscanf(pFile, "cpu %Ld %Ld %Ld %Ld", &ullUserTotalOld, &ullUserTotalLowOld, &ullSysTotalOld, &ullTotalIdleOld);
            xTEST_DIFF(- 1, iRv);

            iRv = fclose(pFile);
            xTEST_DIFF(- 1, iRv);

            bIsFirstRun = false;
        }

        // read proc file for the next times
        {
            FILE *pFile = fopen("/proc/stat", "r");
            xTEST_PTR(pFile);

            iRv = fscanf(pFile, "cpu %Ld %Ld %Ld %Ld", &ullUserTotal, &ullUserTotalLow, &ullSysTotal, &ullTotalIdle);
            xTEST_DIFF(- 1, iRv);

            iRv = fclose(pFile);
            xTEST_DIFF(- 1, iRv);
        }

        if (ullUserTotal < ullUserTotalOld || ullUserTotalLow < ullUserTotalLowOld ||
            ullSysTotal  < ullSysTotalOld  || ullTotalIdle    < ullTotalIdleOld)
        {
            // Overflow detection. Just skip this value.
            dRv       = 0.0;
        } else {
            ullTotal  = (ullUserTotal - ullUserTotalOld) + (ullUserTotalLow - ullUserTotalLowOld) + (ullSysTotal - ullSysTotalOld);
            dRv       = ullTotal;
            ullTotal += (ullTotalIdle - ullTotalIdleOld);
            dRv      /= ullTotal;
            dRv      *= 100ULL;
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
        xTEST_DIFF(- 1, iRv);

        ulUsed       = aulCpIime[CP_USER] + aulCpIime[CP_NICE] + aulCpIime[CP_SYS];
        ulTotal      = aulCpIime[CP_USER] + aulCpIime[CP_NICE] + aulCpIime[CP_SYS] + aulCpIime[CP_IDLE];

        dCpuUsage    = CxUtils::safeDivT(ulUsed - s_ulUsedOld, ulTotal - s_ulTotalOld) * 100.0;

        s_ulUsedOld  = ulUsed;
        s_ulTotalOld = ulTotal;

        ulRv = CxUtils::roundIntT<ulong_t>( dCpuUsage );
    #endif
#endif

    return ulRv;
}
//----------------------------------------------------------------------------------------------------
/* static */
ulonglong_t
CxSystemInfo::ramTotal() {
    ulonglong_t ullRv = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX msStatus = {0};
    msStatus.dwLength = sizeof(msStatus);

    BOOL blRes = ::GlobalMemoryStatusEx(&msStatus);
    xTEST_DIFF(FALSE, blRes);

    ullRv = msStatus.ullTotalPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo siInfo = {0};

        int iRv = ::sysinfo(&siInfo);
        xTEST_DIFF(- 1, iRv);

        ullRv = siInfo.totalram * siInfo.mem_unit;
    #elif xOS_FREEBSD
        ulonglong_t ullRamTotal    = 0ULL;

        int         aiMib[]        = {CTL_HW, HW_PHYSMEM};
        size_t      uiRamTotalSize = sizeof(ullRamTotal);

        int iRv = ::sysctl(aiMib, 2, &ullRamTotal, &uiRamTotalSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);

        ullRv = ullRamTotal;
    #endif
#endif

    return ullRv;
}
//----------------------------------------------------------------------------------------------------
/* static */
ulonglong_t
CxSystemInfo::ramAvailable() {
    ulonglong_t ullRv = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX msStatus = {0};
    msStatus.dwLength = sizeof(msStatus);

    BOOL blRes = ::GlobalMemoryStatusEx(&msStatus);
    xTEST_DIFF(FALSE, blRes);

    ullRv = msStatus.ullAvailPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo siInfo = {0};

        int iRv = ::sysinfo(&siInfo);
        xTEST_DIFF(- 1, iRv);

        ullRv = siInfo.freeram * siInfo.mem_unit;
    #elif xOS_FREEBSD
        ulonglong_t ullAvailPhysPages     = 0ULL;
        size_t      ullAvailPhysPagesSize = sizeof(ullAvailPhysPages);

        int iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &ullAvailPhysPages, &ullAvailPhysPagesSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);

        ullRv = ullAvailPhysPages * pageSize();
    #endif
#endif

    return ullRv;
}
//----------------------------------------------------------------------------------------------------
/* static */
ulong_t
CxSystemInfo::ramUsage() {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX msStatus = {0};
    msStatus.dwLength = sizeof(msStatus);

    BOOL blRes = ::GlobalMemoryStatusEx(&msStatus);
    xTEST_DIFF(FALSE, blRes);

    ulRv = msStatus.dwMemoryLoad;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo siInfo = {0};

        int iRv = ::sysinfo(&siInfo);
        xTEST_DIFF(- 1, iRv);

        ulong_t ulUsage = siInfo.totalram - siInfo.freeram;

        ulRv = static_cast<ulong_t>( CxUtils::safeDivT(ulUsage * 100.0, siInfo.totalram) );
        xTEST_EQ(siInfo.totalram, ulUsage + siInfo.freeram);
    #elif xOS_FREEBSD
        ulonglong_t ullRamTotal = 0ULL;
        {
            int     aiMib[]        = {CTL_HW, HW_PHYSMEM};
            size_t  uiRamTotalSize = sizeof(ullRamTotal);

            int iRv = ::sysctl(aiMib, 2, &ullRamTotal, &uiRamTotalSize, NULL, 0);
            xTEST_DIFF(- 1, iRv);
        }

        ulonglong_t ullRamFree = 0ULL;
        {
            ulonglong_t ullAvailPhysPages     = 0ULL;
            size_t      ullAvailPhysPagesSize = sizeof(ullAvailPhysPages);

            int iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &ullAvailPhysPages, &ullAvailPhysPagesSize, NULL, 0);
            xTEST_DIFF(- 1, iRv);

            ullRamFree = ullAvailPhysPages * pageSize();
        }

        ulonglong_t ullRamUsage = ullRamTotal - ullRamFree;

        ulRv = static_cast<ulong_t>( CxUtils::safeDivT(ullRamUsage * 100.0, ullRamTotal) );
        xTEST_EQ(ullRamTotal, ullRamUsage + ullRamFree);
    #endif
#endif

    return ulRv;
}
//----------------------------------------------------------------------------------------------------
/* static */
ulong_t
CxSystemInfo::pageSize() {
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    SYSTEM_INFO siSysInfo = {{0}};

    (void)::GetNativeSystemInfo(&siSysInfo);

    ulRv = siSysInfo.dwPageSize;
#elif xOS_ENV_UNIX
    int iRv = ::sysconf(xPAGE_SIZE);
    xTEST_DIFF(- 1, iRv);
    xTEST_LESS(0, iRv);

    ulRv = static_cast<ulong_t>( iRv );
#endif

    xTEST_LESS(0UL, ulRv);

    return ulRv;
}
//----------------------------------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* virtual */
CxSystemInfo::CxSystemInfo() {

}
//---------------------------------------------------------------------------
CxSystemInfo::~CxSystemInfo() {

}
//---------------------------------------------------------------------------
#if xOS_ENV_UNIX

/* static */
void
CxSystemInfo::_passwdFileEntry(
    struct passwd *a_pwdPasswd
)
{
    xTEST_PTR(a_pwdPasswd);

    const uid_t cuiUserId = ::getuid();
    xTEST_NA(cuiUserId);

    long_t liBuffSize = - 1L;

    // get liBuffSize
    {
        liBuffSize = ::sysconf(_SC_GETPW_R_SIZE_MAX);
        if (- 1L == liBuffSize) {
            const long_t cliPwRSizeMax = 1024L;    // CUSTOM: 1024L - custom value

            liBuffSize = cliPwRSizeMax;
        }

        xTEST_LESS(0L, liBuffSize);
    }

    struct passwd *pwdResult = NULL;
    char           szBuff[ liBuffSize ];   (void *)std::memset(&szBuff[0], 0, sizeof(szBuff));

    int iRv = ::getpwuid_r(cuiUserId, a_pwdPasswd, szBuff, sizeof(szBuff), &pwdResult);
    xTEST_EQ(0, iRv);
    xTEST_PTR(pwdResult);

#if 0
    printf("\nThe user name is: %s\n",          a_pwdPasswd->pw_name);
    printf("The user id   is: %u\n",            a_pwdPasswd->pw_uid);
    printf("The group id  is: %u\n",            a_pwdPasswd->pw_gid);
    printf("The initial directory is:    %s\n", a_pwdPasswd->pw_dir);
    printf("The initial user program is: %s\n", a_pwdPasswd->pw_shell);
#endif
}

#endif
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
