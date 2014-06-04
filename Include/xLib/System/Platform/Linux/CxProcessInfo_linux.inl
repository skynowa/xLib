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
inline std::tstring_t
CxProcessInfo::_exeName_impl() const
{
    std::tstring_t sRv;

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

    return sRv;
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

    // out
    a_args->swap(args);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
