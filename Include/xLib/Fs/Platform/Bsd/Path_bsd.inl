/**
 * \file  Path.inl
 * \brief file system path
 */


namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_exe_impl()
{
    std::tstring_t sRv;

#if defined(KERN_PROC_PATHNAME)
    constexpr u_int mibSize      {4};
    int_t           mib[mibSize] {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

    tchar_t     buff[PATH_MAX + 1] {};
    std::size_t buffSize           {sizeof(buff) - 1};

    int_t iRv = ::sysctl(mib, mibSize, buff, &buffSize, nullptr, 0U);
    xTEST_DIFF(iRv, - 1);

    sRv.assign(buff);
#else
    std::vec_tstring_t args;

    ProcessInfo info;
    info.setProcessId(Process::currentId());
    info.commandLine(&args);

    bool_t bRv = info.commandLine(Process::currentId(), &args);
    xTEST_EQ(bRv);
    xTEST_EQ(!args.empty());
    xTEST_EQ(!isAbsolute(args.at(0)));

    sRv = absolute(args.at(0));
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_fileExt_impl(
    cFileExt a_fileExt
)
{
    std::tstring_t sRv;

    switch (a_fileExt) {
    case FileExt::seExe:
        sRv = xT("");
        break;
    case FileExt::seDll:
        sRv = xT("so");
        break;
    case FileExt::seLib:
        sRv = xT("a");
        break;
    case FileExt::seObj:
        sRv = xT("o");
        break;
    case FileExt::seShell:
        sRv = xT("sh");
        break;
    default:
        sRv = xT("");
        break;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Path::_isCaseSensitive_impl() const
{
	xUNUSED(_filePath);

    return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
