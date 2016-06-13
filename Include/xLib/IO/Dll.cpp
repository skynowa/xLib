/**
 * \file  Dll.inl
 * \brief dynamic linking loader
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Dll.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Dll_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Dll_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Dll::Dll() :
    _handle(xPTR_NULL)
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Dll::~Dll()
{
    _destruct();
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Dll::isLoaded() const
{
    xTESTS_NA;

    return (_handle != xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Dll::load(
    std::ctstring_t &a_dllPath
)
{
    xTESTS_NA;
    xTEST_EQ(a_dllPath.empty(), false);

    _destruct();

    _load_impl(a_dllPath);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Dll::isProcExists(
    std::ctstring_t &a_procName
) const
{
    return _isProcExists_impl(a_procName);
}
//-------------------------------------------------------------------------------------------------
xINLINE Dll::proc_address_t
Dll::procAddress(
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
xINLINE void_t
Dll::_destruct()
{
    xTESTS_NA;

    xCHECK_DO(!isLoaded(), return);

    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
