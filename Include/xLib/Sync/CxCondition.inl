/**
 * \file   CxCondition.inl
 * \brief  condition variable
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>

#if   xENV_WIN
    #include "Platform/Win/CxCondition_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxCondition_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxCondition_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxCondition_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxCondition_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxCondition::CxCondition()
#if !xENV_WIN
    :
    _mutex (),
    _handle()
#endif
{
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxCondition::~CxCondition()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCondition::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCondition::wait(
    culong_t &a_timeoutMs
)
{
    _wait_impl(a_timeoutMs);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCondition::signal()
{
    _signal_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxCondition::broadcast()
{
    _broadcast_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
