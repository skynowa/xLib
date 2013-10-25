/**
 * \file  CxStdError.cpp
 * \brief standard C library last error
 */


#include <xLib/Debug/CxStdError.h>

#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>

xNAMESPACE_ANONYM_BEGIN

cint_t g_ciCodeSuccess = 0;

xNAMESPACE_ANONYM_END


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxStdError::isSuccess()
{
    bool_t bRv = (g_ciCodeSuccess == errno);

    return bRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO int_t
CxStdError::get()
{
    int_t iCode = errno;

    reset();

    return iCode;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxStdError::set(
    cint_t &a_code
)
{
    errno = a_code;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxStdError::reset()
{
    set(g_ciCodeSuccess);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxStdError::format()
{
    return format(get());
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxStdError::format(
    cint_t &a_code
)
{
    std::tstring_t sRv;

    sRv = CxString::format(xT("%d - "), a_code);

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW
        tchar_t *pcszError = ::xSTRERROR(a_code);
        xCHECK_RET(NULL == pcszError, sRv.append(xT("[Cann't format error message]")));

        sRv.append(pcszError);
    #elif xCOMPILER_MS || xCOMPILER_CODEGEAR
        tchar_t szBuff[64 + 1] = {0};

        errno_t iError = ::xSTRERROR(szBuff, xARRAY_SIZE(szBuff), a_code);
        xCHECK_RET(0 != iError, sRv.append(xT("[Cann't format error message]")));

        sRv.append(szBuff);
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        char szBuff[64 + 1] = {0};

        ctchar_t *pcszError = ::strerror_r(a_code, &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(NULL == pcszError, sRv.append(xT("[Cann't format error message]")));

        sRv.append(pcszError);
    #elif xOS_FREEBSD
        char szBuff[64 + 1] = {0};

        int_t iRv = ::strerror_r(a_code, &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(- 1 == iRv, sRv.append(xT("[Cann't format error message]")));

        sRv.append(&szBuff[0]);
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
