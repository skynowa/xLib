/**
 * \file   ProcessInfo.inl
 * \brief  process information
 */


xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
ProcessInfo::_exeName_impl() const
{
    std::tstring_t sRv;

#if defined(KERN_PROC_PATHNAME)
	const u_int mibSize        = 4;
    int_t       mib[mibSize]   = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, _id};

    tchar_t buff[PATH_MAX + 1] = {0};
    size_t  buffSize           = sizeof(buff) - 1;

    int_t iRv = ::sysctl(mib, mibSize, buff, &buffSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);

    sRv.assign(buff);
#else
    // TODO: ProcessInfo::exeName()
    xNOT_IMPLEMENTED_RET(std::tstring_t());
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
ProcessInfo::_commandLine_impl(
    std::vec_tstring_t *a_args
) const
{
    std::vec_tstring_t args;

    int_t iRv = - 1;

    const u_int mibSize      = 4;
    int_t       mib[mibSize] = {CTL_KERN, KERN_PROC, KERN_PROC_ARGS, _id};

    std::string buff;
    size_t      buffSize = 0;

    // get buffSize
    iRv = ::sysctl(mib, mibSize, xPTR_NULL, &buffSize, xPTR_NULL, 0);
    xTEST_DIFF(iRv, - 1);

    buff.resize(buffSize);

    iRv = ::sysctl(mib, mibSize, &buff.at(0), &buffSize, xPTR_NULL, 0U);
    xTEST_DIFF(iRv, - 1);

    // remove xPTR_NULL terminating symbol
    buff.resize(buffSize - 1);

    String::split(buff, Const::space(), &args);

    // out
    a_args->swap(args);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
