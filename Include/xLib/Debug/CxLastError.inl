/**
 * \file  CxLastError.inl
 * \brief system last error
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>

#if   xENV_WIN
    #include "Platform/Win/CxLastError_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxLastError_unix.inl"

    #if   xENV_LINUX
        #include "Platform/Linux/CxLastError_linux.inl"
    #elif xENV_BSD
        #include "Platform/Bsd/CxLastError_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxLastError_apple.inl"
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
CxLastError::isSuccess()
{
    return _isSuccess_impl();
}
//-------------------------------------------------------------------------------------------------
/* static */
inline ulong_t
CxLastError::get()
{
    culong_t code = _get_impl();

    reset();

    return code;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxLastError::set(
    culong_t &a_code
)
{
    _set_impl(a_code);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxLastError::reset()
{
    set( _nativeCodeSuccess() );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxLastError::format()
{
    return format( get() );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxLastError::format(
    culong_t &a_code
)
{
    return CxString::format(xT("%lu - %s"), a_code, _format_impl(a_code).c_str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline ulong_t
CxLastError::_nativeCodeSuccess()
{
    return _nativeCodeSuccess_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
