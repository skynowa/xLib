/**
 * \file  LastError.inl
 * \brief system last error
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Utils.h>

#if   xENV_WIN
    #include "Platform/Win/LastError_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/LastError_unix.inl"

    #if   xENV_LINUX
        #if   xOS_ANDROID
            #include "Platform/Linux/LastError_android.inl"
        #elif xOS_LINUX
            #include "Platform/Linux/LastError_linux.inl"
        #endif
    #elif xENV_BSD
        #include "Platform/Bsd/LastError_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/LastError_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
LastError::isSuccess()
{
    return _isSuccess_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline ulong_t
LastError::get()
{
    culong_t code = _get_impl();

    reset();

    return code;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
LastError::set(
    culong_t &a_code
)
{
    _set_impl(a_code);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
LastError::reset()
{
    set( _nativeCodeSuccess() );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
LastError::format()
{
    return format( get() );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
LastError::format(
    culong_t &a_code
)
{
    return String::format(xT("%lu - %s"), a_code, _format_impl(a_code).c_str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline ulong_t
LastError::_nativeCodeSuccess()
{
    return _nativeCodeSuccess_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
