/**
 * \file  CxStdError.cpp
 * \brief standard C library last error
 */


#include <xLib/Debug/CxStdError.h>

#include <xLib/Common/CxString.h>

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
bool_t
CxStdError::isSuccess() {
    bool_t bRv = (g_ciCodeSuccess == errno);

    return bRv;
}
//------------------------------------------------------------------------------
/* static */
int_t
CxStdError::get() {
    int_t iCode = errno;

    reset();

    return iCode;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxStdError::set(
    cint_t &a_ciCode
)
{
    errno = a_ciCode;
}
//------------------------------------------------------------------------------
/* static */
void_t
CxStdError::reset() {
    set(g_ciCodeSuccess);
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxStdError::format() {
    return format(get());
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxStdError::format(
    cint_t &a_ciCode
)
{
    std::tstring_t sRv;

    sRv = CxString::format(xT("%d - "), a_ciCode);

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW
        tchar_t *pcszError = ::xSTRERROR(a_ciCode);
        xCHECK_RET(NULL == pcszError, sRv.append(xT("[Cann't format error message]")));

        sRv.append(pcszError);
    #elif xCOMPILER_MS || xCOMPILER_CODEGEAR
        tchar_t szBuff[64 + 1] = {0};

        errno_t iError = ::xSTRERROR(szBuff, xARRAY_SIZE(szBuff), a_ciCode);
        xCHECK_RET(0 != iError, sRv.append(xT("[Cann't format error message]")));

        sRv.append(szBuff);
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        char szBuff[64 + 1] = {0};

        ctchar_t *pcszError = ::strerror_r(a_ciCode, &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(NULL == pcszError, sRv.append(xT("[Cann't format error message]")));

        sRv.append(pcszError);
    #elif xOS_FREEBSD
        char szBuff[64 + 1] = {0};

        int_t iRv = ::strerror_r(a_ciCode, &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(- 1 == iRv, sRv.append(xT("[Cann't format error message]")));

        sRv.append(&szBuff[0]);
    #endif
#endif

    return sRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxStdError::CxStdError() {

}
//------------------------------------------------------------------------------
/* virtual */
CxStdError::~CxStdError() {

}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
