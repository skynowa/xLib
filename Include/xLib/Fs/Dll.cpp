/**
 * \file  Dll.cpp
 * \brief dynamic linking loader
 */


#include "Dll.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Dll_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Dll_unix.inl"
#endif


namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Dll::Dll(
	std::ctstring_t &a_dllPath
) :
	_dllPath{a_dllPath}
{
}
//-------------------------------------------------------------------------------------------------
bool_t
Dll::isOk() const /* final */
{
	return _handle.isValid();
}
//-------------------------------------------------------------------------------------------------
void_t
Dll::load()
{
    xTESTS_NA;
    xTEST(!_dllPath.empty());

    _load_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
