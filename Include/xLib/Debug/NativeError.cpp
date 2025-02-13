/**
 * \file  NativeError.cpp
 * \brief system last error
 */


#include "NativeError.h"

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
        #include "Platform/Apple/NativeError_apple.inl"
    #endif
#endif


namespace xl::debug
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
bool_t
NativeError::isSuccess()
{
    return _isSuccess_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
ulong_t
NativeError::get()
{
    culong_t code = _get_impl();

    reset();

    return code;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
NativeError::set(
    culong_t a_code
)
{
    _set_impl(a_code);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
NativeError::reset()
{
    set( _nativeCodeSuccess() );
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
NativeError::format()
{
    return format( get() );
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
NativeError::format(
    culong_t a_code
)
{
    return Format::str(xT("{} - {}"), a_code, _format_impl(a_code));
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
ulong_t
NativeError::_nativeCodeSuccess()
{
    return _nativeCodeSuccess_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
