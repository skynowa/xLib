/**
 * \file   Service.cpp
 * \brief  service
 */


#if !xOPTION_HEADER_ONLY
    #include "Service.h"
#endif

#if   xENV_WIN
    #include "Platform/Win/Service_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Service_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Unix/Service_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Unix/Service_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/Service_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
Service::create()
{
    return _create_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Service::start()
{
    return _start_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Service::stop()
{
    return _stop_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Service::restart()
{
    stop();
    start();
}
//-------------------------------------------------------------------------------------------------
inline void_t
Service::close()
{
    return _close_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
