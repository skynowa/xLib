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
    std::string asRv;

    std::ctstring_t procFile = Format::str(xT("/proc/{}/exe"), ::getpid());

    bool_t bRv = File::isExists(procFile);
    xCHECK_RET(!bRv, std::tstring_t());

    ssize_t readed = - 1;
    asRv.resize(xPATH_MAX);

    for ( ; ; ) {
        readed = ::readlink(xT2A(procFile).c_str(), &asRv.at(0), asRv.size() *
            sizeof(std::tstring_t::value_type));
        xTEST_DIFF(readed, ssize_t(- 1));

        xCHECK_DO(asRv.size() * sizeof(std::tstring_t::value_type) >
            static_cast<size_t>( readed ), break);

        asRv.resize(asRv.size() * 2);
    }

    asRv.resize( static_cast<std::size_t>(readed) );

    return xA2T(asRv);
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

xNAMESPACE_END2(xl, fs)
