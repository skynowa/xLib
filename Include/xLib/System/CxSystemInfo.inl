/**
 * \file  CxSystemInfo.cpp
 * \brief system information
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDll.h>
#include <xLib/System/CxShell.h>
#include <xLib/System/CxEnvironment.h>

#if xOS_ENV_WIN
    #include <shlobj.h>
#endif

#if xHAVE_GETCPU
    #include <linux/getcpu.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxSystemInfo::CxSystemInfo() :
    _osType(otUnknown),
    _osArch(oaUnknown)
{
}
//-------------------------------------------------------------------------------------------------
inline CxSystemInfo::ExOsType
CxSystemInfo::os()
{
    ExOsType otRv = otUnknown;

#if   xOS_ENV_WIN
    OSVERSIONINFO info = {0};
    info.dwOSVersionInfoSize = sizeof(info);

    BOOL blRv = ::GetVersionEx(&info);
    xTEST_DIFF(FALSE, blRv);

    switch (info.dwPlatformId) {
    case VER_PLATFORM_WIN32s:
        otRv = otWindows3;
        break;
    case VER_PLATFORM_WIN32_WINDOWS:
        xCHECK_DO(0UL  == info.dwMinorVersion, otRv = otWindows95; break);
        xCHECK_DO(10UL == info.dwMinorVersion, otRv = otWindows98; break);
        xCHECK_DO(90UL == info.dwMinorVersion, otRv = otWindows98; break);
        break;
    case VER_PLATFORM_WIN32_NT:
        xCHECK_DO(info.dwMajorVersion <= 4UL,                               otRv = otWindowsNT;              break);
        xCHECK_DO(5UL == info.dwMajorVersion && 0UL == info.dwMinorVersion, otRv = otWindows2000;            break);
        xCHECK_DO(5UL == info.dwMajorVersion && 1UL == info.dwMinorVersion, otRv = otWindowsXP;              break);
        xCHECK_DO(5UL == info.dwMajorVersion && 2UL == info.dwMinorVersion, otRv = otWindowsXPProx64Edition; break);
        xCHECK_DO(5UL == info.dwMajorVersion && 2UL == info.dwMinorVersion, otRv = otWindowsServer2003;      break);
        xCHECK_DO(5UL == info.dwMajorVersion && 2UL == info.dwMinorVersion, otRv = otWindowsHomeServer;      break);
        xCHECK_DO(5UL == info.dwMajorVersion && 2UL == info.dwMinorVersion, otRv = otWindowsServer2003R2;    break);
        xCHECK_DO(6UL == info.dwMajorVersion && 0UL == info.dwMinorVersion, otRv = otWindowsVista;           break);
        xCHECK_DO(6UL == info.dwMajorVersion && 0UL == info.dwMinorVersion, otRv = otWindowsServer2008;      break);
        xCHECK_DO(6UL == info.dwMajorVersion && 1UL == info.dwMinorVersion, otRv = otWindowsServer2008R2;    break);
        xCHECK_DO(6UL == info.dwMajorVersion && 1UL == info.dwMinorVersion, otRv = otWindows7;               break);

        // for unknown windows/newest windows version
        otRv = otUnknown;
        break;
    default:
        otRv = otUnknown;
        break;
    }

#elif xOS_ENV_UNIX
    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(- 1, iRv);

    if      (CxString::compareNoCase(xT("Linux"), info.sysname)) {
        otRv = otLinux;
    }
    else if (CxString::compareNoCase(xT("FreeBSD"), info.sysname)) {
        otRv = otFreeBSD;
    }
    else {
        otRv = otUnknown;
    }
#elif xOS_ENV_MAC
    utsname info= {{0}};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(- 1, iRv);

    if (CxString::compareNoCase(xT("Darwin"), info.sysname)) {
        otRv = otMac;
    }
    else {
        otRv = otUnknown;
    }
#endif

    _osType = otRv;

    return otRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::formatOsType()
{
    xTEST_NA(a_osType);

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    ExOsType type = (_osType == otUnknown) ? os() : _osType;
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
        sRv = CxConst::strUnknown();
        break;
    }
#elif xOS_ENV_UNIX
    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(- 1, iRv);

    sRv = CxString::format(xT("%s %s (%s) %s"), info.sysname, info.release, info.version,
        info.machine);
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline CxSystemInfo::ExOsArch
CxSystemInfo::osArch()
{
    ExOsArch oaRv = oaUnknown;

#if   xOS_ENV_WIN
    #if   xARCH_X86
        BOOL isFuncExist = FALSE;
        {
            CxDll dll;

            dll.load(xT("kernel32.dll"));
            isFuncExist = dll.isProcExists(xT("IsWow64Process"));
        }

        BOOL is64BitOs      = FALSE;
        BOOL isWow64Process = ::IsWow64Process(::GetCurrentProcess(), &is64BitOs);

        oaRv = (isFuncExist && isWow64Process && is64BitOs) ? oa64bit : oa32bit;
    #elif xARCH_X64
        oaRv = oa64bit;
    #else
        // 64-bit Windows does not support Win16
        oaRv = oaUnknown;
    #endif
#elif xOS_ENV_UNIX
    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(- 1, iRv);
    // TODO: xTEST_DIFF(0,   strlen(info.machine));

    // 32-bit checks
    if      (CxString::compareNoCase(xT("i386"), info.machine)) {
        oaRv = oa32bit;
    }
    else if (CxString::compareNoCase(xT("i486"), info.machine)) {
        oaRv = oa32bit;
    }
    else if (CxString::compareNoCase(xT("i586"), info.machine)) {
        oaRv = oa32bit;
    }
    else if (CxString::compareNoCase(xT("i686"), info.machine)) {
        oaRv = oa32bit;
    }

    // 64-bit checks
    else if (CxString::compareNoCase(xT("x86_64"), info.machine)) {
        oaRv = oa64bit;
    }
    else if (CxString::compareNoCase(xT("ia64"), info.machine)) {
        oaRv = oa64bit;
    }
    else if (CxString::compareNoCase(xT("amd64"), info.machine)) {
        oaRv = oa64bit;
    }

    // unknown
    else {
        oaRv = oaUnknown;
    }
#endif

    _osArch = oaRv;

    return oaRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::formatOsArch()
{
    std::tstring_t sRv;

    ExOsArch arch = (_osArch == oaUnknown) ? osArch() : _osArch;
    switch (arch) {
    case CxSystemInfo::oa32bit:
        sRv = xT("32-bit");
        break;
    case CxSystemInfo::oa64bit:
        sRv = xT("64-bit");
        break;
    case CxSystemInfo::oaUnknown:
        sRv = CxConst::strUnknown();
        break;
    default:
        sRv = CxConst::strUnknown();
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::desktopName() const
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    std::ctstring_t nativeDesktop = xT("explorer.exe");

    #if 0
        // TODO: CxSystemInfo::desktopName
        const CxProcess::id_t pid = CxProcess::idByName(nativeDesktop);

        bool_t bRv = CxProcess::isRunning(pid);
        if (bRv) {
            sRv = nativeDesktop;
        } else {
            // TODO: implement some checks for detecting Windows shell
        }

        xTEST_EQ(false, sRv.empty());
    #else
        sRv = nativeDesktop;
    #endif
#elif xOS_ENV_UNIX
    sRv = CxEnvironment::var(xT("DESKTOP_SESSION"));
    xTEST_EQ(false, sRv.empty());
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::hostName() const
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    ulong_t buffSize                 = xHOST_NAME_MAX;
    tchar_t buff[xHOST_NAME_MAX + 1] = {0};

    BOOL blRv = ::GetComputerName(buff, &buffSize);
    xTEST_DIFF(FALSE, blRv);

    sRv.assign(buff, buffSize);
#elif xOS_ENV_UNIX
    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(- 1, iRv);

    sRv.assign(info.nodename);
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxSystemInfo::isUserAdmin() const
{
#if   xOS_ENV_WIN
    bool_t                   isAdmin     = false;
    SID_IDENTIFIER_AUTHORITY ntAuthority = { SECURITY_NT_AUTHORITY };
    PSID                     adminGroup  = NULL;

    BOOL blRv = ::AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, &adminGroup);
    xCHECK_RET(FALSE == blRv, false);

    {
        BOOL isMember = FALSE;

        blRv = ::CheckTokenMembership(NULL, adminGroup, &isMember);
        if (FALSE == blRv || FALSE == isMember) {
            isAdmin = false;
        } else {
            isAdmin = true;
        }
    }

    (void_t)::FreeSid(adminGroup);

    xCHECK_RET(!isAdmin, false);
#elif xOS_ENV_UNIX
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
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::loginUserName() const
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    // try to get from NetAPI
    {
        LPWKSTA_USER_INFO_1 *userInfo = NULL;

        NET_API_STATUS nsRv = ::NetWkstaUserGetInfo(NULL, 1UL, static_cast<LPBYTE *>( &userInfo );
        xTEST_EQ(nsRv == NERR_Success);
        xTEST_PTR(userInfo);

    #if 0
        ::wprintf(L"\n\tUser:        %s\n", userInfo->wkui1_username);
        ::wprintf(L"\tDomain:        %s\n", userInfo->wkui1_logon_domain);
        ::wprintf(L"\tOther Domains: %s\n", userInfo->wkui1_oth_domains);
        ::wprintf(L"\tLogon Server:  %s\n", userInfo->wkui1_logon_server);
    #endif

    #if xUNICODE
        sRv = userInfo->wkui1_username;
    #else
        sRv = CxString::wstrToStr(userInfo->wkui1_username, CP_UTF8);
    #endif

        if (userInfo != NULL)
            nsRv = ::NetApiBufferFree(userInfo);    userInfo = NULL;
            xTEST_EQ(nsRv == NERR_Success);
        }
    }

    // try to get from system environment
    if (nsRv == NERR_Success || userInfo == NULL) {
        sRv = CxEnvironment::var(xT("USERNAME"));
    }
#elif xOS_ENV_UNIX
    char buff[xUSER_NAME_MAX + 1] = {0}; // TODO: LOGIN_NAME_MAX

    int_t iRv = ::getlogin_r(buff, xARRAY_SIZE(buff));
    xTEST_EQ(iRv, 0);

    sRv.assign(buff);
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::userName() const
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    DWORD   buffSize                 = xUSER_NAME_MAX;
    tchar_t buff[xUSER_NAME_MAX + 1] = {0};

    BOOL blRv = ::GetUserName(&buff[0], &buffSize);
    xTEST_DIFF(FALSE, blRv);

    sRv.assign(buff, buffSize);
#elif xOS_ENV_UNIX
    struct passwd passwd;   xSTRUCT_ZERO(passwd);

    _passwdFileEntry(&passwd);
    xTEST_PTR(passwd.pw_name);

    sRv.assign(passwd.pw_name);
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::useHomeDir() const
{
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    tchar_t buff[MAX_PATH + 1] = {0};

    HRESULT hrRv = SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0UL, &buff[0]);
    xTEST_EQ(true, S_OK == hrRv);

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

    // try to get from API
    {
        passwd passwd;   xSTRUCT_ZERO(passwd);

        _passwdFileEntry(&passwd);
        xTEST_PTR(passwd.pw_dir);

        sRv.assign(passwd.pw_dir);
    }

    // try to get from system environment
    sRv = CxEnvironment::var(xT("HOME"));
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::userShellPath() const
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
    sRv.append(CxConst::slash());
    sRv.append(xT("explorer.exe"));
#elif xOS_ENV_UNIX
    passwd passwd;   xSTRUCT_ZERO(passwd);

    _passwdFileEntry(&passwd);
    xTEST_PTR(passwd.pw_shell);

    sRv.assign(passwd.pw_shell);
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::numOfCpus() const
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
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::currentCpuNum() const
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    typedef DWORD (WINAPI *func_t)(void);

    CxDll dll;

    dll.load(xT("kernel32.dll"));

    bool_t bRv = dll.isProcExists(xT("GetCurrentProcessorNumber"));
    xCHECK_RET(!bRv, 0UL);

    func_t func = (func_t)dll.procAddress(xT("GetCurrentProcessorNumber"));
    xTEST_PTR(func);

    ulRv = func();
    xTEST_NA(ulRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        #if defined(SYS_getcpu)
            ulong_t cpu = 0UL;

            long_t liRv = ::syscall(SYS_getcpu, &cpu, NULL, NULL);
            xTEST_DIFF(- 1L, liRv);

            ulRv = cpu;
        #elif (xSTD_LIBC_GNU_VER_MAJOR > 2) || \
              (xSTD_LIBC_GNU_VER_MAJOR == 2 && xSTD_LIBC_GNU_VER_MINOR > 6)
            // ::sched_getcpu() function is available since glibc 2.6, it is glibc specific
            int_t iRv = ::sched_getcpu();
            xTEST_DIFF(- 1, iRv);

            ulRv = static_cast<ulong_t>( iRv );
        #elif xHAVE_GETCPU
            // ::getcpu() was added in kernel 2.6.19 for x86_64 and i386
            uint_t cpu = 0U;

            int_t iRv = ::getcpu(&cpu, NULL, NULL);
            xTEST_DIFF(- 1, iRv);

            ulRv = cpu;
        #else
            // TODO: currentCpuNum
            ulRv = 0UL;
        #endif
    #elif xOS_FREEBSD
        // OS_NOT_SUPPORTED: currentCpuNum
        ulRv = 0UL;
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline CxSystemInfo::ExCpuVendor
CxSystemInfo::cpuVendor() const
{
    ExCpuVendor cvRv = cvUnknown;
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
        // TODO: CxSystemInfo::cpuVendor()
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
        struct _Functor
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

        (void_t)_Functor::__cpuid(cpuInfo, 0);

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
        cvRv = cvIntel;
    }
    else if (std::string("AuthenticAMD") == value) {
        cvRv = cvAmd;
    }
    else {
        cvRv = cvUnknown;
    }

    return cvRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::cpuModel() const
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
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::cpuSpeed() const
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    DWORD cpuSpeedMHz = 0UL;
    DWORD buffSize    = sizeof(cpuSpeedMHz);
    HKEY  key         = NULL;

    LONG lRv = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, xT("HARDWARE\\DESCRIPTION\\System\\"
        "CentralProcessor\\0"), 0UL, KEY_READ, &key);
    xTEST_EQ(ERROR_SUCCESS, lRv);

    lRv = ::RegQueryValueEx(key, xT("~MHz"), NULL, NULL, reinterpret_cast<LPBYTE>( &cpuSpeedMHz ),
        &buffSize);
    xTEST_EQ(ERROR_SUCCESS, lRv);

    lRv = ::RegCloseKey(key);    key = NULL;
    xTEST_EQ(ERROR_SUCCESS, lRv);

    ulRv = cpuSpeedMHz;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // target proc line: "cpu MHz         : 2796.380"
        std::ctstring_t value = CxPath::procValue(xT("/proc/cpuinfo"), xT("cpu MHz"));
        xTEST_EQ(false, value.empty());

        cdouble_t cpuSpeedMHz = CxString::cast<double>( value );

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
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::cpuUsage() const
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


    BOOL blRv = ::GetSystemTimes(&sysIdle, &sysKernel, &sysUser);
    xTEST_DIFF(FALSE, blRv);

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
            dRv    = static_cast<double>( total );
            total += (totalIdle - totalIdleOld);
            dRv   /= static_cast<double>( total );
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
//-------------------------------------------------------------------------------------------------
inline ulonglong_t
CxSystemInfo::ramTotal() const
{
    ulonglong_t ullRv = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX status = {0};
    status.dwLength = sizeof(status);

    BOOL blRv = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(FALSE, blRv);

    ullRv = status.ullTotalPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo info;   xSTRUCT_ZERO(info);

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
//-------------------------------------------------------------------------------------------------
inline ulonglong_t
CxSystemInfo::ramAvailable() const
{
    ulonglong_t ullRv = 0ULL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX status = {0};
    status.dwLength = sizeof(status);

    BOOL blRv = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(FALSE, blRv);

    ullRv = status.ullAvailPhys;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo info;   xSTRUCT_ZERO(info);

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
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::ramUsage() const
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    MEMORYSTATUSEX status = {0};
    status.dwLength = sizeof(status);

    BOOL blRv = ::GlobalMemoryStatusEx(&status);
    xTEST_DIFF(FALSE, blRv);

    ulRv = status.dwMemoryLoad;
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct sysinfo info;   xSTRUCT_ZERO(info);

        int_t iRv = ::sysinfo(&info);
        xTEST_DIFF(- 1, iRv);

        cdouble_t usage = static_cast<cdouble_t>( info.totalram - info.freeram );

        ulRv = static_cast<ulong_t>( CxUtils::safeDivT(usage * 100.0, info.totalram) );
        xTEST_EQ(static_cast<cdouble_t>( info.totalram ), usage + static_cast<cdouble_t>( info.freeram ));
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
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::pageSize() const
{
    ulong_t ulRv = 0UL;

#if   xOS_ENV_WIN
    SYSTEM_INFO sysInfo = {{0}};

    (void_t)::GetNativeSystemInfo(&sysInfo);

    ulRv = sysInfo.dwPageSize;
#elif xOS_ENV_UNIX
    long_t liRv = ::sysconf(xPAGE_SIZE);
    xTEST_DIFF(- 1L, liRv);
    xTEST_LESS(0L,   liRv);

    ulRv = static_cast<ulong_t>( liRv );
#endif

    xTEST_LESS(0UL, ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

#if !xOS_ENV_WIN

//-------------------------------------------------------------------------------------------------
inline void_t
CxSystemInfo::_passwdFileEntry(
    struct passwd *a_passwdEntry
) const
{
    xTEST_PTR(a_passwdEntry);

    long_t buffSize = - 1L;
    {
        buffSize = ::sysconf(_SC_GETPW_R_SIZE_MAX);
        if (- 1L == buffSize) {
            clong_t pwRSizeMax = 16384L;    // CUSTOM: 16384L - custom value

            buffSize = pwRSizeMax;
        }

        xTEST_LESS(0L, buffSize);
    }

    passwd *pwd = NULL;
    char    buff[buffSize];

    void_t *pvRv = std::memset(&buff[0], 0, sizeof(buff));
    xUNUSED(pvRv);

    int_t iRv = ::getpwuid_r(::getuid(), a_passwdEntry, buff, sizeof(buff), &pwd);
    xTEST_EQ(0, iRv);
    xTEST_PTR(pwd);

#if 0
    CxTracer()
        << xTRACE_VAR(a_passwdEntry->pw_name)
        << xTRACE_VAR(a_passwdEntry->pw_uid)
        << xTRACE_VAR(a_passwdEntry->pw_gid)
        << xTRACE_VAR(a_passwdEntry->pw_dir)
        << xTRACE_VAR(a_passwdEntry->pw_shell);
#endif
}

#endif
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
