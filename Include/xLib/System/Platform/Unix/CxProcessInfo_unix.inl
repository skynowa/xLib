/**
 * \file   CxProcessInfo.inl
 * \brief  process information
 */


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_cpuUsage_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: CxProcessInfo::cpuUsage()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_ramUsage_impl() const
{
    ulong_t ulRv = 0UL;

    if (CxProcess::isCurrent( CxProcess::currentId() )) {
        // TODO: CxProcessInfo::ramUsage()
        xNOT_IMPLEMENTED
    } else {
        // TODO: CxProcessInfo::ramUsage()
        xNOT_IMPLEMENTED
    }

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_ioBytes_impl() const
{
    ulong_t ulRv = 0UL;

#if xCOMMENT
    "/proc/[pid]/io"

    1366    rchar: 323934931
    1367    wchar: 323929600
    1368    syscr: 632687
    1369    syscw: 632675
    1370    read_bytes: 0
    1371    write_bytes: 323932160
    1372    cancelled_write_bytes: 0
#endif

    std::tstring_t procPath  = CxString::format(xT("/proc/%lu/io"), _id);

    ulong_t readBytes = 0UL;
    {
        std::tstring_t value = CxPath::procValue(procPath, xT("read_bytes"));
        readBytes = CxString::cast<ulong_t>( value );
    }

    ulong_t writeBytes = 0UL;
    {
        std::tstring_t value = CxPath::procValue(procPath, xT("write_bytes"));
        writeBytes = CxString::cast<ulong_t>( value );
    }

    ulRv = readBytes + writeBytes;

    // xTRACEV("\readBytes: %lu, writeBytes: %lu", readBytes, writeBytes);

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxProcessInfo::_exeName_impl() const
{
    std::tstring_t sRv;

#if   xOS_LINUX
    std::ctstring_t procFile = CxString::format(xT("/proc/%ld/exe"), _id);

    bool_t bRv = CxFile::isExists(procFile);
    xCHECK_RET(!bRv, std::tstring_t());

    ssize_t readed = - 1;
    sRv.resize(xPATH_MAX);

    for ( ; ; ) {
        readed = ::readlink(procFile.c_str(), &sRv.at(0), sRv.size() *
            sizeof(std::tstring_t::value_type));
        xTEST_DIFF(readed, ssize_t(- 1));

        xCHECK_DO(sRv.size() * sizeof(std::tstring_t::value_type) >
            static_cast<size_t>( readed ), break);

        sRv.resize(sRv.size() * 2);
    }

    sRv.resize(readed);
#elif xOS_FREEBSD
    #if defined(KERN_PROC_PATHNAME)
        int_t   mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, _id};

        tchar_t buff[PATH_MAX + 1] = {0};
        size_t  buffSize           = sizeof(buff) - 1;

        int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), buff, &buffSize, xPTR_NULL, 0U);
        xTEST_DIFF(iRv, - 1);

        sRv.assign(buff);
    #else
        // TODO: CxProcessInfo::exeName()
        xNOT_IMPLEMENTED_RET(std::tstring_t());
    #endif
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline ulong_t
CxProcessInfo::_parentId_impl() const
{
    ulong_t ulRv = 0UL;

    // TODO: CxProcessInfo::parentId()
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxProcessInfo::_commandLine_impl(
    std::vec_tstring_t *a_args
) const
{
    std::string        sRv;
    std::vec_tstring_t args;

#if   xOS_LINUX
    // TODO: CxProcessInfo::commandLine() - review
    std::ctstring_t procPath = CxString::format(xT("/proc/%ld/cmdline"), _id);

    FILE *procFile = std::fopen(procPath.c_str(), "r");
    xTEST_PTR(procFile);

    std::csize_t bufferSize       = 2048;
    char         buff[bufferSize] = {0};

    while ( std::fgets(buff, static_cast<int_t>(bufferSize), procFile) ) {
        size_t pos = 0;
        while (pos < bufferSize && buff[pos] != '\0' ) {
            args.push_back(buff + pos);

            pos += std::strlen(buff + pos) + 1;
        }
    }

    xFCLOSE(procFile);
#elif xOS_FREEBSD
    int_t iRv    = - 1;
    int_t mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ARGS, _id};

    std::string buff;
    size_t      buffSize = 0;

    // get buffSize
    iRv = ::sysctl(mib, xARRAY_SIZE(mib), xPTR_NULL, &buffSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    buff.resize(buffSize);

    iRv = ::sysctl(mib, xARRAY_SIZE(mib), &buff.at(0), &buffSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);

    // remove xPTR_NULL terminating symbol
    buff.resize(buffSize - 1);

    CxString::split(buff, CxConst::space(), &args);
#endif

    // out
    a_args->swap(args);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline long_t
CxProcessInfo::_commandLineArgsMax_impl()
{
    long_t liRv = ::sysconf(_SC_ARG_MAX) / sizeof(std::tstring_t::value_type);
    xTEST_DIFF(liRv, - 1L);

    return liRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
