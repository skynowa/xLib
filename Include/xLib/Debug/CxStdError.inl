/**
 * \file  CxStdError.inl
 * \brief standard C library last error
 */


#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>

#if   xENV_WIN
    #include "Platform/Win/CxStdError_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxStdError_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxStdError_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxStdError_unix.inl"
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
CxStdError::isSuccess()
{
    bool_t bRv = (errno == _stdCodeSuccess());

    return bRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxStdError::get()
{
    int_t code = errno;

    reset();

    return code;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxStdError::set(
    cint_t &a_code
)
{
    errno = a_code;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxStdError::reset()
{
    set( _stdCodeSuccess() );
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxStdError::format()
{
    return format(get());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxStdError::format(
    cint_t &a_code
)
{
    return CxString::format(xT("%d - %s"), a_code, _format_impl(a_code).c_str());
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline int_t
CxStdError::_stdCodeSuccess()
{
    return 0;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
