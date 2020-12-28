/**
 * \file  Path.inl
 * \brief file system path
 */


#include <xLib/Core/Const.h>


namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
namespace
{

#if (cmOPTION_PROJECT_LIB_SHARE || cmOPTION_PROJECT_LIB_MODULE)
static void_t function() {}
#endif

}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
PathDll::_dll_impl()
{
    std::tstring_t sRv;

#if (cmOPTION_PROJECT_LIB_SHARE || cmOPTION_PROJECT_LIB_MODULE)
    Dl_info  diInfo {};
    void_t (*procAddress)() = function;

    int_t iRv = ::dladdr(&procAddress, &diInfo);
    xTEST_DIFF(iRv, 0);

    sRv = Path(diInfo.dli_fname).absolute();
#else
    sRv = Const::strEmpty();
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
