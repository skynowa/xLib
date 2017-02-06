/**
 * \file  StdError.inl
 * \brief standard C library last error
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "StdError.h"
#endif

#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Utils.h>

#if   xENV_WIN
    #include "Platform/Win/StdError_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/StdError_unix.inl"

    #if   xENV_LINUX
        #if   xOS_ANDROID
            #include "Platform/Linux/StdError_android.inl"
        #elif xOS_LINUX
            #include "Platform/Linux/StdError_linux.inl"
        #endif
    #elif xENV_BSD
        #include "Platform/Bsd/StdError_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/StdError_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
StdError::isSuccess()
{
    bool_t bRv = (errno == _stdCodeSuccess());

    return bRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE int_t
StdError::get()
{
    int_t code = errno;

    reset();

    return code;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
StdError::set(
    cint_t &a_code
)
{
    errno = a_code;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
StdError::reset()
{
    set( _stdCodeSuccess() );
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
StdError::format()
{
    return format(get());
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
StdError::format(
    cint_t &a_code
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
xINLINE int_t
StdError::_stdCodeSuccess()
{
    return 0;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
