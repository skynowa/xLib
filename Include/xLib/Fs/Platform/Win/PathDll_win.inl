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
namespace
{

extern "C" IMAGE_DOS_HEADER __ImageBase;

}

/* static */
std::tstring_t
PathDll::_dll_impl()
{
    std::tstring_t sRv;
    sRv.resize(xPATH_MAX);

    HMODULE procAddress = reinterpret_cast<HMODULE>( &__ImageBase );

    DWORD stored = ::GetModuleFileName(procAddress, &sRv.at(0), static_cast<DWORD>( sRv.size() ));
    xTEST_DIFF(stored, 0UL);

    sRv.resize(stored);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
