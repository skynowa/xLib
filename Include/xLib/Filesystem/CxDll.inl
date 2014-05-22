/**
 * \file  CxDll.inl
 * \brief dynamic linking loader
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTrace.h>

#if   xENV_WIN
    #include "Platform/Win/CxDll_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxDll_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxDll_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxDll_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxDll::CxDll() :
    _handle(xPTR_NULL)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxDll::~CxDll()
{
    _destruct();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDll::isLoaded() const
{
    xTESTS_NA;

    return (_handle != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDll::load(
    std::ctstring_t &a_dllPath
)
{
    xTESTS_NA;
    xTEST_EQ(a_dllPath.empty(), false);

    _destruct();

    _load_impl(a_dllPath);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDll::isProcExists(
    std::ctstring_t &a_procName
) const
{
    return _isProcExists_impl(a_procName);
}
//-------------------------------------------------------------------------------------------------
inline CxDll::proc_address_t
CxDll::procAddress(
    std::ctstring_t &a_procName
) const
{
    return _procAddress_impl(a_procName);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxDll::_destruct()
{
    xTESTS_NA;

    xCHECK_DO(!isLoaded(), return);

    _destruct_impl();

    _handle = xPTR_NULL;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
