/**
 * \file  CxSystemInfo.inl
 * \brief system information
 */


#if xHAVE_GETCPU
    #include <linux/getcpu.h>
#endif


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxSystemInfo::ExOsType
CxSystemInfo::_os_impl()
{
    ExOsType otRv = otUnknown;

#if xENV_UNIX
    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    if      (CxStringCI::compare(info.sysname, xT("Linux"))) {
        otRv = otLinux;
    }
    else if (CxStringCI::compare(info.sysname, xT("FreeBSD"))) {
        otRv = otFreeBSD;
    }
    else {
        otRv = otUnknown;
    }
#elif xENV_APPLE
    utsname info= {{0}};

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    if (CxStringCI::compare(info.sysname, xT("Darwin"))) {
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
CxSystemInfo::_formatOsType_impl()
{
    std::tstring_t sRv;

    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    sRv = CxString::format(xT("%s %s (%s) %s"), info.sysname, info.release, info.version,
        info.machine);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline CxSystemInfo::ExOsArch
CxSystemInfo::_osArch_impl()
{
    ExOsArch oaRv = oaUnknown;

    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);
    // TODO: CxSystemInfo::_osArch_impl() - xTEST_DIFF(0, strlen(info.machine));

    // 32-bit checks
    if      (CxStringCI::compare(info.machine, xT("i386"))) {
        oaRv = oa32bit;
    }
    else if (CxStringCI::compare(info.machine, xT("i486"))) {
        oaRv = oa32bit;
    }
    else if (CxStringCI::compare(info.machine, xT("i586"))) {
        oaRv = oa32bit;
    }
    else if (CxStringCI::compare(info.machine, xT("i686"))) {
        oaRv = oa32bit;
    }

    // 64-bit checks
    else if (CxStringCI::compare(info.machine, xT("x86_64"))) {
        oaRv = oa64bit;
    }
    else if (CxStringCI::compare(info.machine, xT("ia64"))) {
        oaRv = oa64bit;
    }
    else if (CxStringCI::compare(info.machine, xT("amd64"))) {
        oaRv = oa64bit;
    }

    // unknown
    else {
        oaRv = oaUnknown;
    }

    _osArch = oaRv;

    return oaRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::_desktopName_impl() const
{
    std::tstring_t sRv;

    sRv = CxEnvironment::var(xT("DESKTOP_SESSION"));
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::_hostName_impl() const
{
    std::tstring_t sRv;

    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    sRv.assign(info.nodename);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxSystemInfo::_isUserAdmin_impl() const
{
    const uid_t rootId = 0;
    uid_t       userId = 0;

    userId = ::getuid();
    xTESTS_NA;
    xCHECK_RET(userId != rootId, false);

    userId = ::geteuid();
    xTESTS_NA;
    xCHECK_RET(userId != rootId, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::_loginUserName_impl() const
{
    std::tstring_t sRv;

    // try API
    {
        char buff[xUSER_NAME_MAX + 1] = {0}; // TODO: CxSystemInfo::loginUserName() - LOGIN_NAME_MAX

        int_t iRv = ::getlogin_r(buff, xARRAY_SIZE(buff));
        if (iRv == 0) {
            sRv.assign(buff);
            return sRv;
        }
    }

    // try system environment
    {
        std::ctstring_t var = xT("LOGNAME");

        bool_t bRv = CxEnvironment::isExists(var);
        if (bRv) {
            sRv = CxEnvironment::var(var);
            return sRv;
        }
    }

    // try system environment
    {
        std::ctstring_t var = xT("USER");

        bool_t bRv = CxEnvironment::isExists(var);
        if (bRv) {
            sRv = CxEnvironment::var(var);
            return sRv;
        }
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::_userName_impl() const
{
    std::tstring_t sRv;

    passwd passwd;   xSTRUCT_ZERO(passwd);

    _passwdFileEntry(&passwd);
    xTEST_PTR(passwd.pw_name);

    sRv.assign(passwd.pw_name);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::_userHomeDir_impl() const
{
    std::tstring_t sRv;

   /*
    * MAN: user's home directory
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

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::_userShellPath_impl() const
{
    std::tstring_t sRv;

    passwd passwd;   xSTRUCT_ZERO(passwd);

    _passwdFileEntry(&passwd);
    xTEST_PTR(passwd.pw_shell);

    sRv.assign(passwd.pw_shell);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::_numOfCpus_impl() const
{
    ulong_t ulRv = 0UL;

#if   xOS_LINUX
    long_t liRv = ::sysconf(_SC_NPROCESSORS_ONLN);
    xTEST_DIFF(liRv, - 1L);

    ulRv = static_cast<ulong_t>( liRv );
#elif xOS_FREEBSD
    int_t  mib[]   = {CTL_HW, HW_NCPU};
    size_t resSize = sizeof(ulRv);

    int_t iRv = ::sysctl(mib, static_cast<u_int>( xARRAY_SIZE(mib) ), &ulRv, &resSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::_currentCpuNum_impl() const
{
    ulong_t ulRv = 0UL;

#if defined(SYS_getcpu)
    ulong_t cpu = 0UL;

    long_t liRv = ::syscall(SYS_getcpu, &cpu, xPTR_NULL, xPTR_NULL);
    xTEST_DIFF(liRv, - 1L);

    ulRv = cpu;
#elif xHAVE_SCHED_GETCPU
    int_t iRv = ::sched_getcpu();
    xTEST_DIFF(iRv, - 1);

    ulRv = static_cast<ulong_t>( iRv );
#elif xHAVE_GETCPU
    // ::getcpu() was added in kernel 2.6.19 for x86_64 and i386
    uint_t cpu = 0U;

    int_t iRv = ::getcpu(&cpu, xPTR_NULL, xPTR_NULL);
    xTEST_DIFF(iRv, - 1);

    ulRv = cpu;
#else
    #pragma message("xLib: CxSystemInfo::currentCpuNum() - n/a")
    ulRv = 0UL;
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::_cpuVendor_impl() const
{
    std::tstring_t value;

#if   xOS_LINUX
    // target proc line: "vendor_id : GenuineIntel"
    value = CxPath::procValue(xT("/proc/cpuinfo"), xT("vendor_id"));
    xTEST_EQ(value.empty(), false);
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
    xTEST_EQ(value.empty(), false);
#endif

    return value;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::_cpuModel_impl() const
{
    std::tstring_t sRv;

#if   xOS_LINUX
    // target proc line: "model name    : Intel(R) Xeon(R) CPU           E5620  @ 2.40GHz"
    std::tstring_t value = CxPath::procValue(xT("/proc/cpuinfo"), xT("model name"));
    xTEST_EQ(value.empty(), false);

    sRv = value;
#elif xOS_FREEBSD
    int_t       iRv       = - 1;
    std::string value;
    size_t      valueSize = 0;

    iRv = ::sysctlbyname("hw.model", xPTR_NULL, &valueSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);
    xTEST_DIFF(valueSize, size_t(0));

    value.resize(valueSize);

    iRv = ::sysctlbyname("hw.model", &value.at(0), &valueSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);
    xTEST_EQ(value.size(), valueSize);

    sRv = value;
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::_cpuSpeed_impl() const
{
    ulong_t ulRv = 0UL;

#if   xOS_LINUX
    // target proc line: "cpu MHz         : 2796.380"
    std::ctstring_t value = CxPath::procValue(xT("/proc/cpuinfo"), xT("cpu MHz"));
    xTEST_EQ(value.empty(), false);

    cdouble_t cpuSpeedMHz = CxString::cast<double>( value );

    ulRv = CxUtils::roundIntT<ulong_t>( cpuSpeedMHz );
#elif xOS_FREEBSD
    ulong_t cpuSpeedMHz     = 0UL;
    size_t  cpuSpeedMHzSize = sizeof(cpuSpeedMHz);

    int_t iRv = ::sysctlbyname("hw.clockrate", &cpuSpeedMHz, &cpuSpeedMHzSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    ulRv = cpuSpeedMHz;
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::_cpuUsage_impl() const
{
    ulong_t ulRv = 0UL;

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
        FILE *file = std::fopen("/proc/stat", "r");
        xTEST_PTR(file);

        iRv = std::fscanf(file, "cpu %" xPR_I64u " %" xPR_I64u " %" xPR_I64u " %" xPR_I64u,
            &userTotalOld, &userTotalLowOld, &sysTotalOld, &totalIdleOld);
        xTEST_DIFF(iRv, - 1);

        iRv = std::fclose(file);
        xTEST_DIFF(iRv, - 1);

        isFirstRun = false;
    }

    // read proc file for the next times
    {
        FILE *file = std::fopen("/proc/stat", "r");
        xTEST_PTR(file);

        iRv = std::fscanf(file, "cpu %" xPR_I64u " %" xPR_I64u " %" xPR_I64u " %" xPR_I64u,
            &userTotal, &userTotalLow, &sysTotal, &totalIdle);
        xTEST_DIFF(iRv, - 1);

        iRv = std::fclose(file);
        xTEST_DIFF(iRv, - 1);
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

    int_t iRv = ::sysctlbyname("kern.cp_time", &cpuTime, &cpuTimeSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    used       = cpuTime[CP_USER] + cpuTime[CP_NICE] + cpuTime[CP_SYS];
    total      = cpuTime[CP_USER] + cpuTime[CP_NICE] + cpuTime[CP_SYS] + cpuTime[CP_IDLE];

    cpuUsage   = CxUtils::safeDivT(used - s_usedOld, total - s_totalOld) * 100.0;

    s_usedOld  = used;
    s_totalOld = total;

    ulRv = CxUtils::roundIntT<ulong_t>( cpuUsage );
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulonglong_t
CxSystemInfo::_ramTotal_impl() const
{
    ulonglong_t ullRv = 0ULL;

#if   xOS_LINUX
    struct sysinfo info;   xSTRUCT_ZERO(info);

    int_t iRv = ::sysinfo(&info);
    xTEST_DIFF(iRv, - 1);

    ullRv = info.totalram * info.mem_unit;
#elif xOS_FREEBSD
    ulonglong_t ramTotal     = 0ULL;

    int_t       mib[]        = {CTL_HW, HW_PHYSMEM};
    size_t      ramTotalSize = sizeof(ramTotal);

    int_t iRv = ::sysctl(mib, 2, &ramTotal, &ramTotalSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    ullRv = ramTotal;
#endif

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
inline ulonglong_t
CxSystemInfo::_ramAvailable_impl() const
{
    ulonglong_t ullRv = 0ULL;

#if   xOS_LINUX
    struct sysinfo info;   xSTRUCT_ZERO(info);

    int_t iRv = ::sysinfo(&info);
    xTEST_DIFF(iRv, - 1);

    ullRv = info.freeram * info.mem_unit;
#elif xOS_FREEBSD
    ulonglong_t availPhysPages     = 0ULL;
    size_t      availPhysPagesSize = sizeof(availPhysPages);

    int_t iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &availPhysPages,
        &availPhysPagesSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    ullRv = availPhysPages * pageSize();
#endif

    return ullRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::_ramUsage_impl() const
{
    ulong_t ulRv = 0UL;

#if   xOS_LINUX
    struct sysinfo info;   xSTRUCT_ZERO(info);

    int_t iRv = ::sysinfo(&info);
    xTEST_DIFF(iRv, - 1);

    cdouble_t usage = static_cast<cdouble_t>( info.totalram - info.freeram );

    ulRv = static_cast<ulong_t>( CxUtils::safeDivT(usage * 100.0, info.totalram) );
    xTEST_EQ(static_cast<cdouble_t>( info.totalram ), usage + static_cast<cdouble_t>( info.freeram ));
#elif xOS_FREEBSD
    ulonglong_t ramTotal = 0ULL;
    {
        int_t  mib[]        = {CTL_HW, HW_PHYSMEM};
        size_t ramTotalSize = sizeof(ramTotal);

        int_t iRv = ::sysctl(mib, 2, &ramTotal, &ramTotalSize, xPTR_NULL, 0);
        xTEST_DIFF(iRv, - 1);
    }

    ulonglong_t ramFree = 0ULL;
    {
        ulonglong_t availPhysPages     = 0ULL;
        size_t      availPhysPagesSize = sizeof(availPhysPages);

        int_t iRv = ::sysctlbyname("vm.stats.vm.v_free_count", &availPhysPages,
            &availPhysPagesSize, xPTR_NULL, 0);
        xTEST_DIFF(iRv, - 1);

        ramFree = availPhysPages * pageSize();
    }

    ulonglong_t ramUsage = ramTotal - ramFree;

    ulRv = static_cast<ulong_t>( CxUtils::safeDivT(ramUsage * 100.0, ramTotal) );
    xTEST_EQ(ramTotal, ramUsage + ramFree);
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxSystemInfo::_pageSize_impl() const
{
    long_t liRv = ::sysconf(xPAGE_SIZE);
    xTEST_DIFF(liRv, - 1L);
    xTEST_LESS(0L,   liRv);

    ulong_t ulRv = static_cast<ulong_t>( liRv );
    xTEST_LESS(0UL, ulRv);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Libs
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::glibcVersion() const
{
    std::tstring_t sRv;

    std::tstring_t version;
    {
        ctchar_t *libc_version = ::gnu_get_libc_version();
        if (libc_version == xPTR_NULL) {
            version += CxConst::strUnknown();
        } else {
            version += libc_version;
        }
    }

    std::tstring_t release;
    {
        ctchar_t *libc_release = ::gnu_get_libc_release();
        if (libc_release == xPTR_NULL) {
            release += CxConst::strUnknown();
        } else {
            release += libc_release;
        }
    }

    sRv = version + CxConst::space() + release;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxSystemInfo::libPthreadVersion() const
{
    std::tstring_t buff;

    std::size_t buffBytes;
    {
        buffBytes = ::confstr(_CS_GNU_LIBPTHREAD_VERSION, xPTR_NULL, 0);
        xCHECK_RET(buffBytes == 0, CxConst::strUnknown());

        buff.resize(buffBytes);
    }

    buffBytes = ::confstr(_CS_GNU_LIBPTHREAD_VERSION, &buff.at(0), buff.size());
    xCHECK_RET(buffBytes == 0, CxConst::strUnknown());

    // remove terminating null byte
    buff.resize(buffBytes - 1);

    return buff;
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxSystemInfo::_passwdFileEntry(
    passwd *a_passwdEntry
) const
{
    xTEST_PTR(a_passwdEntry);

    long_t buffSize = - 1L;
    {
        buffSize = ::sysconf(_SC_GETPW_R_SIZE_MAX);
        if (buffSize == - 1L) {
            clong_t pwRSizeMax = 16384L;    // CUSTOM: 16384L - custom value

            buffSize = pwRSizeMax;
        }

        xTEST_LESS(0L, buffSize);
    }

    std::string  buff;
    passwd      *pwd = xPTR_NULL;

    buff.resize(buffSize);

    int_t iRv = ::getpwuid_r(::getuid(), a_passwdEntry, &buff.at(0), buff.size(), &pwd);
    xTEST_EQ(iRv, 0);
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
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
