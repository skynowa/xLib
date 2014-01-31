/**
 * \file  CxStdError.cpp
 * \brief standard C library last error
 */


#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>

xNAMESPACE_ANONYM_BEGIN

cint_t stdCodeSuccess = 0;

xNAMESPACE_ANONYM_END


xNAMESPACE2_BEGIN(xlib, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxStdError::isSuccess()
{
    bool_t bRv = (::stdCodeSuccess == errno);

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
    set(::stdCodeSuccess);
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
    std::tstring_t sRv;

    sRv = CxString::format(xT("%d - "), a_code);

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW
        tchar_t *error = xSTRERROR(a_code);
        xCHECK_RET(NULL == error, sRv.append(xT("[Cann't format error message]")));

        sRv.append(error);
    #elif xCOMPILER_MS || xCOMPILER_CODEGEAR
        tchar_t buff[64 + 1] = {0};

        errno_t error = xSTRERROR(buff, xARRAY_SIZE(buff), a_code);
        xCHECK_RET(0 != error, sRv.append(xT("[Cann't format error message]")));

        sRv.append(buff);
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        char buff[64 + 1] = {0};

        ctchar_t *error = ::strerror_r(a_code, &buff[0], xARRAY_SIZE(buff));
        xCHECK_RET(NULL == error, sRv.append(xT("[Cann't format error message]")));

        sRv.append(error);
    #elif xOS_FREEBSD
        char buff[64 + 1] = {0};

        int_t iRv = ::strerror_r(a_code, &buff[0], xARRAY_SIZE(buff));
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
