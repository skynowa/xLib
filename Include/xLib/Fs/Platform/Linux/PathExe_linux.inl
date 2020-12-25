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
    std::string asRv;

    std::ctstring_t procFile = Format::str(xT("/proc/{}/exe"), ::getpid());

    bool_t bRv = FileInfo(procFile).isExists();
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

} // namespace
