/**
 * \file  SocketInit.inl
 * \brief initiates use of the Winsock DLL by a process
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/LastError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/SocketInit_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/SocketInit_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/SocketInit_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/SocketInit_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
SocketInit::SocketInit(
    cushort_t &a_versionMajor,
    cushort_t &a_versionMinor
)
{
    _construct_impl(a_versionMajor, a_versionMinor);
}
//-------------------------------------------------------------------------------------------------
inline
SocketInit::~SocketInit()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
