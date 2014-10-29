/**
 * \file  SystemInfo.inl
 * \brief system information
 */


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline SystemInfo::ExOsType
SystemInfo::_os_impl()
{
    ExOsType otRv = otUnknown;

    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    if      (StringCI::compare(info.sysname, xT("Linux"))) {
        otRv = otLinux;
    }
    else if (StringCI::compare(info.sysname, xT("FreeBSD"))) {
        otRv = otFreeBSD;
    }
    else if (StringCI::compare(info.sysname, xT("Darwin"))) {
        otRv = otMac;
    }
    else {
        otRv = otUnknown;
    }

    _osType = otRv;

    return otRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
SystemInfo::_formatOs_impl()
{
    std::tstring_t sRv;

    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    sRv = String::format(xT("%s %s (%s) %s"), info.sysname, info.release, info.version,
        info.machine);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline SystemInfo::ExOsArch
SystemInfo::_osArch_impl()
{
    ExOsArch oaRv = oaUnknown;

    std::tstring_t infoMachine;
    {
        utsname info; xSTRUCT_ZERO(info);

        int_t iRv = ::uname(&info);
        xTEST_DIFF(iRv, - 1);

        infoMachine.assign(info.machine);
    }

    // 32-bit checks
    if      (StringCI::compare(infoMachine, xT("i386"))) {
        oaRv = oa32bit;
    }
    else if (StringCI::compare(infoMachine, xT("i486"))) {
        oaRv = oa32bit;
    }
    else if (StringCI::compare(infoMachine, xT("i586"))) {
        oaRv = oa32bit;
    }
    else if (StringCI::compare(infoMachine, xT("i686"))) {
        oaRv = oa32bit;
    }

    // 64-bit checks
    else if (StringCI::compare(infoMachine, xT("x86_64"))) {
        oaRv = oa64bit;
    }
    else if (StringCI::compare(infoMachine, xT("ia64"))) {
        oaRv = oa64bit;
    }
    else if (StringCI::compare(infoMachine, xT("amd64"))) {
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
SystemInfo::_desktopName_impl() const
{
    std::tstring_t sRv;

    sRv = Environment::var(xT("DESKTOP_SESSION"));
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
SystemInfo::_hostName_impl() const
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
SystemInfo::_isUserAdmin_impl() const
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
SystemInfo::_loginUserName_impl() const
{
    std::tstring_t sRv;

    // try API
    {
    #if xHAVE_GETLOGIN_R
        char buff[xUSER_NAME_MAX + 1] = {0}; // TODO: SystemInfo::loginUserName() - LOGIN_NAME_MAX

        int_t iRv = ::getlogin_r(buff, xARRAY_SIZE(buff));
        if (iRv == 0) {
            sRv.assign(buff);
            return sRv;
        }
    #else
        const char *buff = ::getlogin();
        if (buff != xPTR_NULL) {
            sRv.assign(buff);
            return sRv;
        }
    #endif
    }

    // try system environment
    {
        std::ctstring_t var = xT("LOGNAME");

        bool_t bRv = Environment::isExists(var);
        if (bRv) {
            sRv = Environment::var(var);
            return sRv;
        }
    }

    // try system environment
    {
        std::ctstring_t var = xT("USER");

        bool_t bRv = Environment::isExists(var);
        if (bRv) {
            sRv = Environment::var(var);
            return sRv;
        }
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
SystemInfo::_userName_impl() const
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
SystemInfo::_userHomeDir_impl() const
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
    sRv = Environment::var(xT("HOME"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
SystemInfo::_userShellPath_impl() const
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
SystemInfo::_currentCpuNum_impl() const
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
#elif defined(_SC_NPROCESSORS_ONLN)
    long_t liRv = ::sysconf(_SC_NPROCESSORS_ONLN);
    xTEST_DIFF(liRv, - 1L);

    ulRv = static_cast<ulong_t>( liRv );
#else
    #pragma message("xLib: SystemInfo::_currentCpuNum_impl() - n/a")
    ulRv = 0UL;
#endif

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
SystemInfo::_pageSize_impl() const
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
SystemInfo::glibcVersion() const
{
    std::tstring_t version;
    {
    #if xHAVE_GNU_GET_LIBC
        ctchar_t *libc_version = ::gnu_get_libc_version();
        if (libc_version == xPTR_NULL) {
            version = Const::strUnknown();
        } else {
            version = libc_version;
        }
    #else
        xBUILD_IMPL("SystemInfo::glibcVersion()");
        version = Const::strUnknown();
    #endif
    }

    std::tstring_t release;
    {
    #if xHAVE_GNU_GET_LIBC
        ctchar_t *libc_release = ::gnu_get_libc_release();
        if (libc_release == xPTR_NULL) {
            release = Const::strUnknown();
        } else {
            release = libc_release;
        }
    #else
        release = Const::strUnknown();
    #endif
    }

    std::ctstring_t sRv = version + Const::space() + release;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
SystemInfo::libPthreadVersion() const
{
    std::tstring_t buff;

#if xHAVE_CS_GNU_LIBPTHREAD_VERSION
    std::size_t buffBytes;
    {
        buffBytes = ::confstr(_CS_GNU_LIBPTHREAD_VERSION, xPTR_NULL, 0);
        xCHECK_RET(buffBytes == 0, Const::strUnknown());

        buff.resize(buffBytes);
    }

    buffBytes = ::confstr(_CS_GNU_LIBPTHREAD_VERSION, &buff.at(0), buff.size());
    xCHECK_RET(buffBytes == 0, Const::strUnknown());

    // remove terminating null byte
    buff.resize(buffBytes - 1);
#else
    xBUILD_IMPL("SystemInfo::libPthreadVersion()");
    buff = Const::strUnknown();
#endif

    return buff;
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
SystemInfo::_passwdFileEntry(
    passwd *a_passwdEntry
) const
{
    xTEST_PTR(a_passwdEntry);

#if xHAVE_GETPWUID_R
    long_t buffSize = - 1L;
    {
        buffSize = ::sysconf(_SC_GETPW_R_SIZE_MAX);
        if (buffSize == - 1L) {
            buffSize = xCUSTOM_SYSCONF_SC_GETPW_R_SIZE_MAX_UNIX;
        }

        xTEST_GR(buffSize, 0L);
    }

    std::string  buff;
    passwd      *pwd = xPTR_NULL;

    buff.resize(buffSize);

    int_t iRv = ::getpwuid_r(::getuid(), a_passwdEntry, &buff.at(0), buff.size(), &pwd);
    xTEST_EQ(iRv, 0);
    xTEST_PTR(pwd);
#else
    struct passwd *pwd = ::getpwuid( ::getuid() );
    xTEST_PTR(pwd);

    a_passwdEntry = pwd;
#endif

#if 0
    Tracer()
        << xTRACE_VAR(a_passwdEntry->pw_name)
        << xTRACE_VAR(a_passwdEntry->pw_uid)
        << xTRACE_VAR(a_passwdEntry->pw_gid)
        << xTRACE_VAR(a_passwdEntry->pw_dir)
        << xTRACE_VAR(a_passwdEntry->pw_shell);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
