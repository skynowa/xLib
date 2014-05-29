/**
 * \file  CxSocketInit.inl
 * \brief initiates use of the Winsock DLL by a process
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
    #include "Platform/Win/CxSocketInit_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxSocketInit_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxSocketInit_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxSocketInit_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, net)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxSocketInit::CxSocketInit(
    cushort_t &a_versionMajor,
    cushort_t &a_versionMinor
)
{
    _construct_impl(a_versionMajor, a_versionMinor);
}
//-------------------------------------------------------------------------------------------------
inline
CxSocketInit::~CxSocketInit()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
