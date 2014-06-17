/**
 * \file  CxPath.inl
 * \brief file system path
 */


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxPath::_exe_impl()
{
    std::tstring_t sRv;

    std::ctstring_t procFile = CxString::format(xT("/proc/%ld/exe"), ::getpid());

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

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
