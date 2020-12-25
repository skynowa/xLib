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
PathExe::_exe_impl()
{
    // REVIEW: QueryFullProcessImageName on xOS_WIN_VER > xOS_WIN_S03

    std::tstring_t sRv;
    sRv.resize(xPATH_MAX);

    DWORD stored = ::GetModuleFileName(nullptr, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
