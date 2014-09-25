/**
 * \file  Mutex.inl
 * \brief mutex
 */


#if !xOPTION_HEADER_ONLY
    #include "Mutex.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Mutex_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Mutex_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/Mutex_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/Mutex_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Mutex_apple.inl"
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
Mutex::~Mutex()
{
    _destruc_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Mutex::create()
{
    _create_impl();
}
//-------------------------------------------------------------------------------------------------
inline const Mutex::handle_t &
Mutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline void_t
Mutex::lock()
{
    _lock_impl();
}
//-------------------------------------------------------------------------------------------------
inline bool_t
Mutex::tryLock()
{
    return _tryLock_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Mutex::unlock()
{
    _unlock_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
