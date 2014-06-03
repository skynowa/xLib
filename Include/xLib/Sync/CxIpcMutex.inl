/**
 * \file  CxIpcMutex.inl
 * \brief mutex
 */


#include <xLib/Core/CxConst.h>

#if   xENV_WIN
    #include "Platform/Win/CxIpcMutex_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxIpcMutex_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxIpcMutex_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxIpcMutex_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxIpcMutex_apple.inl"
    #endif
#endif

xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxIpcMutex::CxIpcMutex() :
#if   xENV_WIN
    _handle(),
#elif xENV_UNIX
    _handle(xPTR_NULL),
#endif
    _name  ()
{
}
//-------------------------------------------------------------------------------------------------
inline const CxIpcMutex::handle_t &
CxIpcMutex::handle() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::create(
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
CxIpcMutex::open(
    std::ctstring_t &a_name
)
{
    _open_impl(a_name);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::lock(
    culong_t &a_timeoutMsec
) const
{
    ////xTEST_EQ(_handle.isValid(), true);
    xTEST_NA(a_timeoutMsec);

    _lock_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcMutex::unlock() const
{
    ////xTEST_EQ(_handle.isValid(), true);

    _unlock_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
