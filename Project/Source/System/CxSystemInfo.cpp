/**
 * \file  CxSystemInfo.cpp
 * \brief system information
 */


#include <xLib/System/CxSystemInfo.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/Sync/CxProcess.h>
#include <xLib/System/CxShell.h>
#include <xLib/System/CxEnvironment.h>

#if xOS_ENV_WIN
    #include <shlobj.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO CxSystemInfo::ExOsType
CxSystemInfo::os()
{
    ExOsType otRes = otUnknown;

#if   xOS_ENV_WIN
    OSVERSIONINFO info = {0};
    info.dwOSVersionInfoSize = sizeof(info);

    BOOL blRes = ::GetVersionEx(&info);
    xTEST_DIFF(FALSE, blRes);

    switch (info.dwPlatformId) {
    case VER_PLATFORM_WIN32s:
        otRes = otWindows3;
        break;
    case VER_PLATFORM_WIN32_WINDOWS:
        xCHECK_DO(0UL  == info.dwMinorVersion, otRes = otWindows95; break);
        xCHECK_DO(10UL == info.dwMinorVersion, otRes = otWindows98; break);
        xCHECK_DO(90UL == info.dwMinorVersion, otRes = otWindows98; break);
        break;
    case VER_PLATFORM_WIN32_NT:
        xCHECK_DO(info.dwMajorVersion <= 4UL,                               otRes = otWindowsNT;              break);
        xCHECK_DO(5UL == info.dwMajorVersion && 0UL == info.dwMinorVersion, otRes = otWindows2000;            break);
        xCHECK_DO(5UL == info.dwMajorVersion && 1UL == info.dwMinorVersion, otRes = otWindowsXP;              break);
        xCHECK_DO(5UL == info.dwMajorVersion && 2UL == info.dwMinorVersion, otRes = otWindowsXPProx64Edition; break);
        xCHECK_DO(5UL == info.dwMajorVersion && 2UL == info.dwMinorVersion, otRes = otWindowsServer2003;      break);
        xCHECK_DO(5UL == info.dwMajorVersion && 2UL == info.dwMinorVersion, otRes = otWindowsHomeServer;      break);
        xCHECK_DO(5UL == info.dwMajorVersion && 2UL == info.dwMinorVersion, otRes = otWindowsServer2003R2;    break);
        xCHECK_DO(6UL == info.dwMajorVersion && 0UL == info.dwMinorVersion, otRes = otWindowsVista;           break);
        xCHECK_DO(6UL == info.dwMajorVersion && 0UL == info.dwMinorVersion, otRes = otWindowsServer2008;      break);
        xCHECK_DO(6UL == info.dwMajorVersion && 1UL == info.dwMinorVersion, otRes = otWindowsServer2008R2;    break);
        xCHECK_DO(6UL == info.dwMajorVersion && 1UL == info.dwMinorVersion, otRes = otWindows7;               break);

        // for unknown windows/newest windows version
        otRes = otUnknown;
        break;
    default:
        otRes = otUnknown;
        break;
    }

#elif xOS_ENV_UNIX
    utsname info = {{0}};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(- 1, iRv);

    if      (CxString::compareNoCase(xT("Linux"), info.sysname)) {
        otRes = otLinux;
    }
    else if (CxString::compareNoCase(xT("FreeBSD"), info.sysname)) {
        otRes = otFreeBSD;
    }
    else {
        otRes = otUnknown;
    }
#elif xOS_ENV_MAC
    utsname info= {{0}};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(- 1, iRv);

    if (CxString::compareNoCase(xT("Darwin"), info.sysname)) {
        otRes = otMac;
    }
    else {
        otRes = otUnknown;
    }
#endif

    return otRes;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSystemInfo::formatOsType(
    const ExOsType &a_osType
)
{
    xTEST_NA(a_osType);

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    switch (a_osType) {
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
        sRv = CxConst::xUNKNOWN_STRING();
        break;
    }
#elif xOS_ENV_UNIX
    if (os() == a_osType) {
        // current OS type - get info about OS kernel
        utsname info= {{0}};

        int_t iRv = ::uname(&info);
        xTEST_DIFF(- 1, iRv);

        sRv = CxString::format(xT("%s %s (%s) %s"), info.sysname, info.release, info.version,
            info.machine);
    } else {
        // not current OS type, can't get info about OS kernel -
        // return simple-formatted string
        switch (a_osType) {
        case otLinux:
            sRv = xT("Linux");
            break;
        case otFreeBSD:
            sRv = xT("FreeBSD");
            break;
        default:
            sRv = CxConst::xUNKNOWN_STRING();
            break;
        }
    }
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO CxSystemInfo::ExOsArch
CxSystemInfo::osArch()
{
    ExOsArch oaRes = oaUnknown;

#if   xOS_ENV_WIN
    #if   xARCH_X86
        BOOL isFuncExist = FALSE;
        {
            CxDll dll;

            dll.load(xT("kernel32.dll"));
            isFuncExist = dll.isProcExists(xT("IsWow64Process"));
        }

        BOOL is64BitOs      = FALSE;
        BOOL isWow64Process = ::IsWow64Process(CxProcess::currentHandle(), &is64BitOs);

        oaRes = (isFuncExist && isWow64Process && is64BitOs) ? oa64bit : oa32bit;
    #elif xARCH_X64
        oaRes = oa64bit;
    #else
        // 64-bit Windows does not support Win16
        oaRes = oaUnknown;
    #endif
#else
    utsname info= {{0}};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(- 1, iRv);
    // TODO: xTEST_DIFF(0,   strlen(info.machine));

    // 32-bit checks
    if      (CxString::compareNoCase(xT("i386"), info.machine)) {
        oaRes = oa32bit;
    }
    else if (CxString::compareNoCase(xT("i486"), info.machine)) {
        oaRes = oa32bit;
    }
    else if (CxString::compareNoCase(xT("i586"), info.machine)) {
        oaRes = oa32bit;
    }
    else if (CxString::compareNoCase(xT("i686"), info.machine)) {
        oaRes = oa32bit;
    }

    // 64-bit checks
    else if (CxString::compareNoCase(xT("x86_64"), info.machine)) {
        oaRes = oa64bit;
    }
    else if (CxString::compareNoCase(xT("ia64"), info.machine)) {
        oaRes = oa64bit;
    }
    else if (CxString::compareNoCase(xT("amd64"), info.machine)) {
        oaRes = oa64bit;
    }

    // unknown
    else {
        oaRes = oaUnknown;
    }
#endif

    return oaRes;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSystemInfo::formatOsArch(
    const ExOsArch &a_osArch
)
{
    std::tstring_t sRv;

    switch (a_osArch) {
    case CxSystemInfo::oa32bit:
        sRv = xT("32-bit");
        break;
    case CxSystemInfo::oa64bit:
        sRv = xT("64-bit");
        break;
    case CxSystemInfo::oaUnknown:
        sRv = CxConst::xUNKNOWN_STRING();
        break;
    default:
        sRv = CxConst::xUNKNOWN_STRING();
        break;
    }

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSystemInfo::desktopName()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    std::ctstring_t       nativeDesktop = xT("explorer.exe");
    const CxProcess::id_t pid           = CxProcess::idByName(nativeDesktop);

    bool_t bRv = CxProcess::isRunning(pid);
    if (bRv) {
        sRv = nativeDesktop;
    } else {
        // TODO: implement some checks for detecting Windows shell
    }

    xTEST_EQ(false, sRv.empty());
#elif xOS_ENV_UNIX
    sRv = CxEnvironment::var(xT("DESKTOP_SESSION"));
    xTEST_EQ(false, sRv.empty());
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSystemInfo::hostName()
{
    std::tstring_t sRv;

#if xOS_ENV_WIN
    ulong_t buffSize                 = xHOST_NAME_MAX;
    tchar_t buff[xHOST_NAME_MAX + 1] = {0};

    BOOL blRes = ::GetComputerName(buff, &buffSize);
    xTEST_DIFF(FALSE, blRes);

    sRv.assign(buff, buffSize);
#else
    utsname info= {{0}};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(- 1, iRv);

    sRv.assign(info.nodename);
#endif

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO bool_t
CxSystemInfo::isUserAdmin()
{
#if xOS_ENV_WIN
    bool_t                   isAdmin     = false;
    SID_IDENTIFIER_AUTHORITY ntAuthority = { SECURITY_NT_AUTHORITY };
    PSID                     adminGroup  = NULL;

    BOOL blRes = ::AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, &adminGroup);
    xCHECK_RET(FALSE == blRes, false);

    {
        BOOL isMember = FALSE;

        blRes = ::CheckTokenMembership(NULL, adminGroup, &isMember);
        if (FALSE == blRes || FALSE == isMember) {
            isAdmin = false;
        } else {
            isAdmin = true;
        }
    }

    (void_t)::FreeSid(adminGroup);

    xCHECK_RET(!isAdmin, false);
#else
    const uid_t rootId = 0;
    uid_t       userId = 0;

    userId = ::getuid();
    xTESTS_NA;
    xCHECK_RET(rootId != userId, false);

    userId = ::geteuid();
    xTESTS_NA;
    xCHECK_RET(rootId != userId, false);
#endif

    return true;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSystemInfo::userName()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD   buffSize        = UNLEN;
    tchar_t buff[UNLEN + 1] = {0};

    BOOL blRes = ::GetUserName(&buff[0], &buffSize);
    xTEST_DIFF(FALSE, blRes);

    sRv.assign(buff, buffSize);
#elif xOS_ENV_UNIX
    struct passwd passwd = {0};

    _passwdFileEntry(&passwd);
    xTEST_PTR(passwd.pw_name);

    sRv.assign(passwd.pw_name);
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

#if 0
    // TODO: CxSystemInfo::userName()
    char * userName = ::getenv("LOGNAME");
    char * userName = ::getenv("USERNAME");
    ::getlogin_r
#endif

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSystemInfo::useHomeDir()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    tchar_t buff[MAX_PATH + 1] = {0};

    HRESULT hrRes = SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0UL, &buff[0]);
    xTEST_EQ(true, S_OK == hrRes);

    sRv.assign(buff);
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

    bool_t bRv = CxEnvironment::isExists(xT("HOME"));
    if (bRv) {
        sRv = CxEnvironment::var(xT("HOME"));
    } else {
        struct passwd passwd = {0};

        _passwdFileEntry(&passwd);
        xTEST_PTR(passwd.pw_dir);

        sRv.assign(passwd.pw_dir);
    }
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSystemInfo::userShellPath()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    LPITEMIDLIST idList = {0};

    HRESULT hrRv = ::SHGetSpecialFolderLocation(NULL, CSIDL_WINDOWS, &idList);
    xTEST_EQ(S_OK, hrRv);

    tchar_t buff[MAX_PATH + 1] = {0};

    BOOL blRv = ::SHGetPathFromIDList(idList, buff);
    xTEST_DIFF(FALSE, blRv);

    sRv.append(buff);
    sRv.append(CxConst::xSLASH());
    sRv.append(xT("explorer.exe"));
#elif xOS_ENV_UNIX
    struct passwd passwd = {0};

    _passwdFileEntry(&passwd);
    xTEST_PTR(passwd.pw_shell);

    sRv.assign(passwd.pw_shell);
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxSystemInfo::numOfCpus()
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    SYSTEM_INFO sysInfo = {{0}};

    (void_t)::GetNativeSystemInfo(&sysInfo);

    ulRv = sysInfo.dwNumberOfProcessors;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        long_t liRv = ::sysconf(_SC_NPROCESSORS_ONLN);
        xTEST_DIFF(- 1L, liRv);

        ulRv = static_cast<ulong_t>( liRv );
    #elif xOS_FREEBSD
        int_t  mib[]   = {CTL_HW, HW_NCPU};
        size_t resSize = sizeof(ulRv);

        int_t iRv = ::sysctl(mib, static_cast<u_int>( xARRAY_SIZE(mib) ), &ulRv, &resSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxSystemInfo::currentCpuNum()
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    typedef DWORD (WINAPI *DllGetCurrentProcessorNumber_t)(void);

    CxDll dll;

    dll.load(xT("kernel32.dll"));

    bool_t bRv = dll.isProcExists(xT("GetCurrentProcessorNumber"));
    xCHECK_RET(!bRv, 0UL);

    DllGetCurrentProcessorNumber_t DllGetCurrentProcessorNumber =
        (DllGetCurrentProcessorNumber_t)dll.procAddress(xT("GetCurrentProcessorNumber"));
    xTEST_PTR(DllGetCurrentProcessorNumber);

    ulRv = DllGetCurrentProcessorNumber();
    xTEST_NA(ulRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        #if defined(SYS_getcpu)
            ulong_t cpu = 0UL;

            int_t iRv = ::syscall(SYS_getcpu, &cpu, NULL, NULL);
            xTEST_DIFF(- 1, iRv);

            ulRv = cpu;
        #else
            #if (xSTD_LIBC_GNU_VER_MAJOR > 2) || \
                (xSTD_LIBC_GNU_VER_MAJOR == 2 && xSTD_LIBC_GNU_VER_MINOR > 6)

                // ::sched_getcpu() function is available since glibc 2.6, it is glibc specific
                int_t iRv = ::sched_getcpu();
                xTEST_DIFF(- 1, iRv);

                ulRv = static_cast<ulong_t>( iRv );
            #else
                //TODO: ulGetCurrentCpuNum
                ulRv = 0UL;
            #endif

            #if xTEMP_DISABLED
                // ::getcpu() was added in kernel 2.6.19 for x86_64 and i386
                uint_t cpu = 0U;

                int_t iRv = ::getcpu(&cpu, NULL, NULL);
                xTEST_DIFF(- 1, iRv);

                ulRv = cpu;
            #endif

        #endif
    #elif xOS_FREEBSD
        // OS_NOT_SUPPORTED: ulGetCurrentCpuNum
        ulRv = 0UL;
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
xINLINE_HO CxSystemInfo::ExCpuVendor
CxSystemInfo::cpuVendor()
{
    ExCpuVendor cvRes = cvUnknown;
    std::string value;

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW || xCOMPILER_MS
        int_t  cpuInfo[4] = {0};
        char   man[13]    = {0};

        (void_t)::__cpuid(cpuInfo, 0);

        *reinterpret_cast<int_t *>( &man[0] ) = cpuInfo[1];
        *reinterpret_cast<int_t *>( &man[4] ) = cpuInfo[3];
        *reinterpret_cast<int_t *>( &man[8] ) = cpuInfo[2];

        value = std::string(man);
        xTEST_EQ(false, value.empty());
    #elif xCOMPILER_CODEGEAR
        // TODO: CxSystemInfo::cvGetCpuVendor()
        value = std::tstring_t();
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "vendor_id : GenuineIntel"
        value = CxPath::procValue(xT("/proc/cpuinfo"), xT("vendor_id"));
        xTEST_EQ(false, value.empty());
    #elif xOS_FREEBSD
        // Use gcc 4.4 provided cpuid intrinsic
        // 32 bit fpic requires ebx be preserved
        struct _SFunctor
        {
        #if (defined(__pic__) || defined(__APPLE__)) && defined(__i386__)
            static inline void_t
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
            static inline void_t
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
            // OS_NOT_SUPPORTED: CxSystemInfo::cvGetCpuVendor()
            #error xLib: Can not define __cpuid
        #endif
        };

        int_t cpuInfo[4] = {0};

        (void_t)_SFunctor::__cpuid(cpuInfo, 0);

        cpuInfo[0] = cpuInfo[1];  // Reorder output
        cpuInfo[1] = cpuInfo[3];
        cpuInfo[2] = cpuInfo[2];
        cpuInfo[3] = 0;

        value = std::string(CxUtils::reinterpretCastT<char *>( &cpuInfo[0] ));
        xTEST_EQ(false, value.empty());
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif
    if      (std::string("GenuineIntel") == value) {
        cvRes = cvIntel;
    }
    else if (std::string("AuthenticAMD") == value) {
        cvRes = cvAmd;
    }
    else {
        cvRes = cvUnknown;
    }

    return cvRes;
}
//------------------------------------------------------------------------------
xINLINE_HO std::tstring_t
CxSystemInfo::cpuModel()
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
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

        uint_t uiHighestFeatureEx = static_cast<uint_t>( cpuInfo[0] );

        // get processor brand name
        if (uiHighestFeatureEx >= 0x80000004) {
            char buff[49] = {0};

            (void_t)::__cpuid(reinterpret_cast<int_t *>( &buff[0]  ), 0x80000002);
            (void_t)::__cpuid(reinterpret_cast<int_t *>( &buff[16] ), 0x80000003);
            (void_t)::__cpuid(reinterpret_cast<int_t *>( &buff[32] ), 0x80000004);

            std::tstring_t cpuName = CxString::trimSpace( xS2TS(buff) );

            sRv = CxString::format(xT("%s (%s)"), cpuName.c_str(), man);
        } else {
            sRv = CxString::format(xT("%s"), man);
        }
    #elif xCOMPILER_CODEGEAR
        sRv = std::tstring_t();
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "model name    : Intel(R) Xeon(R) CPU           E5620  @ 2.40GHz"
        std::tstring_t value = CxPath::procValue(xT("/proc/cpuinfo"), xT("model name"));
        xTEST_EQ(false, value.empty());

        sRv = value;
    #elif xOS_FREEBSD
        int_t       iRv       = - 1;
        std::string value;
        size_t      valueSize = 0;

        iRv = ::sysctlbyname("hw.model", NULL, &valueSize, NULL, 0U);
        xTEST_DIFF(- 1, iRv);
        xTEST_DIFF(size_t(0), valueSize);

        value.resize(valueSize);

        iRv = ::sysctlbyname("hw.model", &value.at(0), &valueSize, NULL, 0U);
        xTEST_DIFF(- 1, iRv);
        xTEST_EQ(value.size(), valueSize);

        sRv = value;
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxSystemInfo::cpuSpeed()
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    DWORD cpuSpeedMHz = 0UL;
    DWORD buffSize    = sizeof(cpuSpeedMHz);
    HKEY  key         = NULL;

    LONG lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, xT("HARDWARE\\DESCRIPTION\\System\\"
        "CentralProcessor\\0"), 0UL, KEY_READ, &key);
    xTEST_EQ(ERROR_SUCCESS, lRes);

    lRes = ::RegQueryValueEx(key, xT("~MHz"), NULL, NULL, reinterpret_cast<LPBYTE>( &cpuSpeedMHz ),
        &buffSize);
    xTEST_EQ(ERROR_SUCCESS, lRes);

    lRes = ::RegCloseKey(key);    key = NULL;
    xTEST_EQ(ERROR_SUCCESS, lRes);

    ulRv = cpuSpeedMHz;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "cpu MHz         : 2796.380"
        std::tstring_t value = CxPath::procValue(xT("/proc/cpuinfo"), xT("cpu MHz"));
        xTEST_EQ(false, value.empty());

        double cpuSpeedMHz = CxString::cast<double>( value );

        ulRv = CxUtils::roundIntT<ulong_t>( cpuSpeedMHz );
    #elif xOS_FREEBSD
        ulong_t cpuSpeedMHz     = 0UL;
        size_t  cpuSpeedMHzSize = sizeof(cpuSpeedMHz);

        int_t iRv = ::sysctlbyname("hw.clockrate", &cpuSpeedMHz, &cpuSpeedMHzSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);

        ulRv = cpuSpeedMHz;
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxSystemInfo::cpuUsage()
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
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


    BOOL blRes = ::GetSystemTimes(&sysIdle, &sysKernel, &sysUser);
    xTEST_DIFF(FALSE, blRes);

    (void_t)::CopyMemory(&ulSysIdle,   &sysIdle,   sizeof(sysIdle));
    (void_t)::CopyMemory(&ulSysKernel, &sysKernel, sizeof(sysKernel));
    (void_t)::CopyMemory(&ulSysUser,   &sysUser,   sizeof(sysUser));

    dRv = CxUtils::safeDivT(
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

    ulRv = static_cast<ulong_t>( dRv );
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        double             dRv             = 0.0;
        int_t              iRv             = - 1;

        static bool_t      isFirstRun      = true;

        static ulonglong_t userTotalOld    = 0ULL;
        static ulonglong_t userTotalLowOld = 0ULL;
        static ulonglong_t sysTotalOld     = 0ULL;
        static ulonglong_t totalIdleOld    = 0ULL;

        ulonglong_t        userTotal       = 0ULL;
        ulonglong_t        userTotalLow    = 0ULL;
        ulonglong_t        sysTotal        = 0ULL;
        ulonglong_t        totalIdle       = 0ULL;
        ulonglong_t        total           = 0ULL;

        // read proc file for the first time
        if (isFirstRun) {
            FILE *file = fopen("/proc/stat", "r");
            xTEST_PTR(file);

            iRv = fscanf(file, "cpu %Ld %Ld %Ld %Ld", &userTotalOld, &userTotalLowOld,
                &sysTotalOld, &totalIdleOld);
            xTEST_DIFF(- 1, iRv);

            iRv = fclose(file);
            xTEST_DIFF(- 1, iRv);

            isFirstRun = false;
        }

        // read proc file for the next times
        {
            FILE *file = fopen("/proc/stat", "r");
            xTEST_PTR(file);

            iRv = fscanf(file, "cpu %Ld %Ld %Ld %Ld", &userTotal, &userTotalLow, &sysTotal, &totalIdle);
            xTEST_DIFF(- 1, iRv);

            iRv = fclose(file);
            xTEST_DIFF(- 1, iRv);
        }

        if (userTotal < userTotalOld || userTotalLow < userTotalLowOld ||
            sysTotal  < sysTotalOld  || totalIdle    < totalIdleOld)
        {
            // Overflow detection. Just skip this value.
            dRv = 0.0;
        } else {
            total  = (userTotal - userTotalOld) + (userTotalLow - userTotalLowOld) +
                (sysTotal - sysTotalOld);
            dRv    = total;
            total += (totalIdle - totalIdleOld);
            dRv   /= total;
            dRv   *= 100ULL;
        }

        userTotalOld    = userTotal;
        userTotalLowOld = userTotalLow;
        sysTotalOld     = sysTotal;
        totalIdleOld    = totalIdle;

        ulRv = static_cast<ulong_t>( dRv );
    #elif xOS_FREEBSD
        double         cpuUsage           = 0.0;

        static ulong_t s_totalOld         = - 1UL;
        static ulong_t s_usedOld          = - 1UL;

        ulong_t        used               = - 1UL;
        ulong_t        total              = - 1UL;

        ulong_t        cpuTime[CPUSTATES] = {0};
        size_t         cpuTimeSize        = sizeof(cpuTime);

        int_t iRv = ::sysctlbyname("kern.cp_time", &cpuTime, &cpuTimeSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);

        used       = cpuTime[CP_USER] + cpuTime[CP_NICE] + cpuTime[CP_SYS];
        total      = cpuTime[CP_USER] + cpuTime[CP_NICE] + cpuTime[CP_SYS] + cpuTime[CP_IDLE];

        cpuUsage   = CxUtils::safeDivT(used - s_usedOld, total - s_totalOld) * 100.0;

        s_usedOld  = used;
        s_totalOld = total;

        ulRv = CxUtils::roundIntT<ulong_t>( cpuUsage );
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------------
xINLINE_HO ulonglong_t
CxSystemInfo::ramTotal()
{
    ulonglong_t ullRv = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX status = {0};
    status.dwLength = sizeof(status);

    BOOL blRes = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(FALSE, blRes);

    ullRv = status.ullTotalPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo info = {0};

        int_t iRv = ::sysinfo(&info);
        xTEST_DIFF(- 1, iRv);

        ullRv = info.totalram * info.mem_unit;
    #elif xOS_FREEBSD
        ulonglong_t ramTotal     = 0ULL;

        int_t       mib[]        = {CTL_HW, HW_PHYSMEM};
        size_t      ramTotalSize = sizeof(ramTotal);

        int_t iRv = ::sysctl(mib, 2, &ramTotal, &ramTotalSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);

        ullRv = ramTotal;
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ullRv;
}
//-------------------------------------------------------------------------------------------------------
xINLINE_HO ulonglong_t
CxSystemInfo::ramAvailable()
{
    ulonglong_t ullRv = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX status = {0};
    status.dwLength = sizeof(status);

    BOOL blRes = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(FALSE, blRes);

    ullRv = status.ullAvailPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo info = {0};

        int_t iRv = ::sysinfo(&info);
        xTEST_DIFF(- 1, iRv);

        ullRv = info.freeram * info.mem_unit;
    #elif xOS_FREEBSD
        ulonglong_t availPhysPages     = 0ULL;
        size_t      availPhysPagesSize = sizeof(availPhysPages);

        int_t iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &availPhysPages,
            &availPhysPagesSize, NULL, 0);
        xTEST_DIFF(- 1, iRv);

        ullRv = availPhysPages * pageSize();
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ullRv;
}
//-------------------------------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxSystemInfo::ramUsage()
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX status = {0};
    status.dwLength = sizeof(status);

    BOOL blRes = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(FALSE, blRes);

    ulRv = status.dwMemoryLoad;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo info = {0};

        int_t iRv = ::sysinfo(&info);
        xTEST_DIFF(- 1, iRv);

        ulong_t usage = info.totalram - info.freeram;

        ulRv = static_cast<ulong_t>( CxUtils::safeDivT(usage * 100.0, info.totalram) );
        xTEST_EQ(info.totalram, usage + info.freeram);
    #elif xOS_FREEBSD
        ulonglong_t ramTotal = 0ULL;
        {
            int_t  mib[]        = {CTL_HW, HW_PHYSMEM};
            size_t ramTotalSize = sizeof(ramTotal);

            int_t iRv = ::sysctl(mib, 2, &ramTotal, &ramTotalSize, NULL, 0);
            xTEST_DIFF(- 1, iRv);
        }

        ulonglong_t ramFree = 0ULL;
        {
            ulonglong_t availPhysPages     = 0ULL;
            size_t      availPhysPagesSize = sizeof(availPhysPages);

            int_t iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &availPhysPages,
                &availPhysPagesSize, NULL, 0);
            xTEST_DIFF(- 1, iRv);

            ramFree = availPhysPages * pageSize();
        }

        ulonglong_t ramUsage = ramTotal - ramFree;

        ulRv = static_cast<ulong_t>( CxUtils::safeDivT(ramUsage * 100.0, ramTotal) );
        xTEST_EQ(ramTotal, ramUsage + ramFree);
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------------
xINLINE_HO ulong_t
CxSystemInfo::pageSize()
{
    ulong_t ulRv = 0UL;

#if xOS_ENV_WIN
    SYSTEM_INFO sysInfo = {{0}};

    (void_t)::GetNativeSystemInfo(&sysInfo);

    ulRv = sysInfo.dwPageSize;
#else
    int_t iRv = ::sysconf(xPAGE_SIZE);
    xTEST_DIFF(- 1, iRv);
    xTEST_LESS(0, iRv);

    ulRv = static_cast<ulong_t>( iRv );
#endif

    xTEST_LESS(0UL, ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

#if !xOS_ENV_WIN

//------------------------------------------------------------------------------
xINLINE_HO void_t
CxSystemInfo::_passwdFileEntry(
    struct passwd *a_passwdEntry
)
{
    xTEST_PTR(a_passwdEntry);

    const uid_t userId = ::getuid();
    xTEST_NA(userId);

    long_t buffSize = - 1L;

    // get buffSize
    {
        buffSize = ::sysconf(_SC_GETPW_R_SIZE_MAX);
        if (- 1L == buffSize) {
            clong_t cliPwRSizeMax = 1024L;    // CUSTOM: 1024L - custom value

            buffSize = cliPwRSizeMax;
        }

        xTEST_LESS(0L, buffSize);
    }

    struct passwd *pwd = NULL;
    char           buff[ buffSize ];

    void_t *pvRv = std::memset(&buff[0], 0, sizeof(buff));
    xUNUSED(pvRv);

    int_t iRv = ::getpwuid_r(userId, a_passwdEntry, buff, sizeof(buff), &pwd);
    xTEST_EQ(0, iRv);
    xTEST_PTR(pwd);

#if 0
    printf("\nThe user name is: %s\n",          a_passwdEntry->pw_name);
    printf("The user id is: %u\n",              a_passwdEntry->pw_uid);
    printf("The group id is: %u\n",             a_passwdEntry->pw_gid);
    printf("The initial directory is: %s\n",    a_passwdEntry->pw_dir);
    printf("The initial user program is: %s\n", a_passwdEntry->pw_shell);
#endif
}

#endif
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
