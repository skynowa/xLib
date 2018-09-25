/**
 * \file  Path.inl
 * \brief file system path
 */


xNAMESPACE_BEGIN2(xl, fs)

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
    const u_int mibSize      = 4;
    int_t       mib[mibSize] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

    tchar_t     buff[PATH_MAX + 1] = {0};
    std::size_t buffSize           = sizeof(buff) - 1;

    int_t iRv = ::sysctl(mib, mibSize, buff, &buffSize, nullptr, 0U);
    xTEST_DIFF(iRv, - 1);

    sRv.assign(buff);
#else
    std::vec_tstring_t args;

    ProcessInfo info;
    info.setProcessId(Process::currentId());
    info.commandLine(&args);

    bool_t bRv = info.commandLine(Process::currentId(), &args);
    xTEST_EQ(bRv, true);
    xTEST_EQ(args.empty(), false);
    xTEST_EQ(isAbsolute(args.at(0)), false);

    sRv = absolute(args.at(0));
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Path::_fileExt_impl(
    const FileExt &a_fileExt
)
{
    std::tstring_t sRv;

    switch (a_fileExt) {
    case seExe:
        sRv = xT("");
        break;
    case seDll:
        sRv = xT("so");
        break;
    case seLib:
        sRv = xT("a");
        break;
    case seObj:
        sRv = xT("o");
        break;
    case seShell:
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

xNAMESPACE_END2(xl, fs)
