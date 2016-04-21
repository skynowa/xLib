/**
 * \file  NativeError.inl
 * \brief system last error
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "NativeError.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>

#if   xENV_WIN
    #include "Platform/Win/NativeError_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/NativeError_unix.inl"

    #if   xENV_LINUX
        #if   xOS_ANDROID
            #include "Platform/Linux/NativeError_android.inl"
        #elif xOS_LINUX
            #include "Platform/Linux/NativeError_linux.inl"
        #endif
    #elif xENV_BSD
        #include "Platform/Bsd/NativeError_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/NativeError_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
NativeError::isSuccess()
{
    return _isSuccess_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE ulong_t
NativeError::get()
{
    culong_t code = _get_impl();

    reset();

    return code;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
NativeError::set(
    culong_t &a_code
)
{
    _set_impl(a_code);
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
NativeError::reset()
{
    set( _nativeCodeSuccess() );
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
NativeError::format()
{
    return format( get() );
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
NativeError::format(
    culong_t &a_code
)
{
    return Format::str(xT("%lu - %s"), a_code, _format_impl(a_code).c_str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE ulong_t
NativeError::_nativeCodeSuccess()
{
    return _nativeCodeSuccess_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
