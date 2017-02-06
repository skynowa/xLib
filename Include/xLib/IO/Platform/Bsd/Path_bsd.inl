/**
 * \file  Path.inl
 * \brief file system path
 */


xNAMESPACE_BEGIN2(xl, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Path::_exe_impl()
{
    std::tstring_t sRv;

#if defined(KERN_PROC_PATHNAME)
    int_t mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, - 1};

    tchar_t     buff[PATH_MAX + 1] = {0};
    std::size_t buffSize           = sizeof(buff) - 1;

    int_t iRv = ::sysctl(mib, xARRAY_SIZE(mib), buff, &buffSize, xPTR_NULL, 0U);
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
xINLINE std::tstring_t
Path::_fileExt_impl(
    const ExFileExt &a_fileExt
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

xNAMESPACE_END2(xl, io)
