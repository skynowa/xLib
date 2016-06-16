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
xINLINE SystemInfo::ExOsType
SystemInfo::_os_impl()
{
    ExOsType otRv = otUnknown;

    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    if      (StringCI::compare(xA2T(info.sysname), xT("Linux"))) {
        otRv = otLinux;
    }
    else if (StringCI::compare(xA2T(info.sysname), xT("FreeBSD"))) {
        otRv = otFreeBSD;
    }
    else if (StringCI::compare(xA2T(info.sysname), xT("Darwin"))) {
        otRv = otMac;
    }
    else {
        otRv = otUnknown;
    }

    _osType = otRv;

    return otRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::_formatOs_impl()
{
    std::tstring_t sRv;

    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    sRv = Format::str(xT("{} {} ({}) {}"), info.sysname, info.release, info.version,
        info.machine);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE SystemInfo::ExOsArch
SystemInfo::_osArch_impl()
{
    ExOsArch oaRv = oaUnknown;

    std::tstring_t infoMachine;
    {
        utsname info; xSTRUCT_ZERO(info);

        int_t iRv = ::uname(&info);
        xTEST_DIFF(iRv, - 1);

        infoMachine = xA2T(info.machine);
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
xINLINE std::tstring_t
SystemInfo::_desktopName_impl() const
{
    std::tstring_t sRv;

    sRv = Environment::var(xT("DESKTOP_SESSION"));
    xTEST_EQ(sRv.empty(), false);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::_hostName_impl() const
{
    std::tstring_t sRv;

    utsname info; xSTRUCT_ZERO(info);

    int_t iRv = ::uname(&info);
    xTEST_DIFF(iRv, - 1);

    sRv = xA2T(info.nodename);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE ulong_t
SystemInfo::_currentCpuNum_impl() const
{
    ulong_t ulRv = 0UL;

#if defined(SYS_getcpu)
    ulong_t cpu = 0UL;

    long_t liRv = ::syscall(SYS_getcpu, &cpu, xPTR_NULL, xPTR_NULL);
    xTEST_DIFF(liRv, - 1L);

    ulRv = cpu;
#elif cmSCHED_GETCPU_FOUND
    int_t iRv = ::sched_getcpu();
    xTEST_DIFF(iRv, - 1);

    ulRv = static_cast<ulong_t>( iRv );
#elif cmGETCPU_FOUND
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
xINLINE ulong_t
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
xINLINE std::tstring_t
SystemInfo::glibcVersion() const
{
    std::tstring_t version;
    {
    #if cmGNU_GET_LIBC_FOUND
        cchar *libc_version = ::gnu_get_libc_version();
        if (libc_version == xPTR_NULL) {
            version = Const::strUnknown();
        } else {
            version = xA2T(libc_version);
        }
    #else
        xBUILD_IMPL("SystemInfo::glibcVersion()");
        version = Const::strUnknown();
    #endif
    }

    std::tstring_t release;
    {
    #if cmGNU_GET_LIBC_FOUND
        cchar *libc_release = ::gnu_get_libc_release();
        if (libc_release == xPTR_NULL) {
            release = Const::strUnknown();
        } else {
            release = xA2T(libc_release);
        }
    #else
        release = Const::strUnknown();
    #endif
    }

    std::ctstring_t sRv = version + Const::space() + release;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
SystemInfo::libPthreadVersion() const
{
    std::tstring_t sRv;

#if cmCS_GNU_LIBPTHREAD_VERSION_FOUND
    std::string buff;

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

    sRv = xA2T(buff);
#else
    xBUILD_IMPL("SystemInfo::libPthreadVersion()");
    sRv = Const::strUnknown();
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
