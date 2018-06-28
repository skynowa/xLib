/**
 * \file  Dll.inl
 * \brief dynamic linking loader
 */


#include "Dll.h"

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
#endif


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Dll::Dll() :
    _handle()
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
Dll::~Dll()
{
}
//-------------------------------------------------------------------------------------------------
HandleDll &
Dll::get()
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
void_t
Dll::load(
    std::ctstring_t &a_dllPath
)
{
    xTEST_NA;
    xTEST_EQ(a_dllPath.empty(), false);

    close();

    _load_impl(a_dllPath);
}
//-------------------------------------------------------------------------------------------------
bool_t
Dll::isProcExists(
    std::ctstring_t &a_procName
) const
{
    return _isProcExists_impl(a_procName);
}
//-------------------------------------------------------------------------------------------------
Dll::proc_address_t
Dll::procAddress(
    std::ctstring_t &a_procName
) const
{
    return _procAddress_impl(a_procName);
}
//-------------------------------------------------------------------------------------------------
void_t
Dll::close()
{
    xTEST_NA;

    _handle.close();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
