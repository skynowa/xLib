/**
 * \file  CxLastError.cpp
 * \brief system last error
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>


xNAMESPACE2_BEGIN(xlib, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

xNAMESPACE_ANONYM_BEGIN

#if   xOS_ENV_WIN
    culong_t nativeCodeSuccess = ERROR_SUCCESS;
#elif xOS_ENV_UNIX
    culong_t nativeCodeSuccess = 0UL;
#endif

xNAMESPACE_ANONYM_END

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxLastError::isSuccess()
{
    bool_t bRv = false;

#if   xOS_ENV_WIN
    bRv = (::nativeCodeSuccess == ::GetLastError());
#elif xOS_ENV_UNIX
    bRv = (::nativeCodeSuccess == static_cast<ulong_t>( errno ));
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline ulong_t
CxLastError::get()
{
    ulong_t code = ::nativeCodeSuccess;

#if   xOS_ENV_WIN
    code = ::GetLastError();
#elif xOS_ENV_UNIX
    code = static_cast<ulong_t>( errno );
#endif

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
#if   xOS_ENV_WIN
    (void_t)::SetLastError(a_code);
#elif xOS_ENV_UNIX
    errno = static_cast<int_t>( a_code );
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxLastError::reset()
{
    set(::nativeCodeSuccess);
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
    std::tstring_t sRv;

    sRv = CxString::format(xT("%lu - "), a_code);

#if   xOS_ENV_WIN
    DWORD  dwRv = 0UL;
    LPVOID buff = NULL;

    dwRv = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS, NULL, a_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPTSTR>( &buff ), 0UL, NULL);

    xCHECK_RET(ERROR_MR_MID_NOT_FOUND == get(), sRv.append(xT("Unknown error")));
    xCHECK_RET(0UL                    == dwRv,  sRv.append(xT("[Cann't format error message]")));

    std::tstring_t msg;

    msg.assign( static_cast<LPCTSTR>( buff ), dwRv );
    msg = CxString::removeEol(msg);
    msg = CxString::trimRightChars(msg, CxConst::dot());

    sRv.append(msg);

    (void_t)::LocalFree(buff);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        char buff[64 + 1] = {0};

        ctchar_t *error = ::strerror_r(static_cast<int_t>( a_code ), &buff[0], xARRAY_SIZE(buff));
        xCHECK_RET(NULL == error, sRv.append(xT("[Cann't format error message]")));

        sRv.append(error);
    #elif xOS_FREEBSD
        char buff[64 + 1] = {0};

        int_t iRv = ::strerror_r(static_cast<int_t>( a_code ), &buff[0], xARRAY_SIZE(buff));
        xCHECK_RET(- 1 == iRv, sRv.append(xT("[Cann't format error message]")));

        sRv.append(&buff[0]);
    #endif
#elif xOS_ENV_APPLE
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, debug)
