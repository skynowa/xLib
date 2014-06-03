/**
 * \file  CxMutex.inl
 * \brief mutex
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
    #include "Platform/Win/CxMutex_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxMutex_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxMutex_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxMutex_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxMutex_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxMutex::~CxMutex()
{
    _destruc_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
inline const CxMutex::handle_t &
CxMutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::lock()
{
    _lock_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxMutex::tryLock()
{
    return _tryLock_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMutex::unlock()
{
    _unlock_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
