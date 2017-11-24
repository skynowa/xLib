/**
 * \file  SocketInit.inl
 * \brief initiates use of the Winsock DLL by a process
 */


#include "SocketInit.h"

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/SocketInit_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/SocketInit_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


xNAMESPACE_BEGIN2(xl, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
SocketInit::SocketInit(
    cushort_t &a_versionMajor,
    cushort_t &a_versionMinor
)
{
    _construct_impl(a_versionMajor, a_versionMinor);
}
//-------------------------------------------------------------------------------------------------
SocketInit::~SocketInit()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, net)
