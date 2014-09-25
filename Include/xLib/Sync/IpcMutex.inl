/**
 * \file  IpcMutex.inl
 * \brief mutex
 */


#if !xOPTION_HEADER_ONLY
    #include "IpcMutex.h"
#endif

#include <xLib/Core/Const.h>

#if   xENV_WIN
    #include "Platform/Win/IpcMutex_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/IpcMutex_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/IpcMutex_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/IpcMutex_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/IpcMutex_apple.inl"
    #endif
#endif

xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
IpcMutex::IpcMutex() :
#if   xENV_WIN
    _handle(),
#elif xENV_UNIX
    _handle(xPTR_NULL),
#endif
    _name  ()
{
}
//-------------------------------------------------------------------------------------------------
inline const IpcMutex::handle_t &
IpcMutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline void_t
IpcMutex::create(
    std::ctstring_t &a_name
)
{
    ////xTEST_EQ(_handle.isValid(), false);
#if   xENV_WIN
    // name
#elif xENV_UNIX
    xTEST_GR(xNAME_MAX - 4, a_name.size());
#endif

    _create_impl(a_name);
}
//-------------------------------------------------------------------------------------------------
inline void_t
IpcMutex::open(
    std::ctstring_t &a_name
)
{
    _open_impl(a_name);
}
//-------------------------------------------------------------------------------------------------
inline void_t
IpcMutex::lock(
    culong_t &a_timeoutMsec
) const
{
    ////xTEST_EQ(_handle.isValid(), true);
    xTEST_NA(a_timeoutMsec);

    _lock_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
inline void_t
IpcMutex::unlock() const
{
    ////xTEST_EQ(_handle.isValid(), true);

    _unlock_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
