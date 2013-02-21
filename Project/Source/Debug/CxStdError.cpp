/**
 * \file  CxStdError.cpp
 * \brief standard C library last error
 */


#include <xLib/Debug/CxStdError.h>

#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
int
CxStdError::get() {
    int iCode = 0; /* = ciCodeSuccess */;

    iCode = errno;

    reset();

    return iCode;
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxStdError::toString() {
    return format(get());
}
//------------------------------------------------------------------------------
/* static */
void
CxStdError::set(
    const int &a_ciCode
)
{
    errno = a_ciCode;
}
//------------------------------------------------------------------------------
/* static */
void
CxStdError::reset() {
    const int ciCodeSuccess = 0;

    set(ciCodeSuccess);
}
//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxStdError::format(
    const int &a_ciCode
)
{
    std::tstring_t sRv;

    sRv = CxString::format(xT("%lu - "), a_ciCode);

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

        const tchar_t *pcszError = ::strerror_r(a_ciCode, &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(NULL == pcszError, sRv.append(xT("[Cann't format error message]")));

        sRv.append(pcszError);
    #elif xOS_FREEBSD
        char szBuff[64 + 1] = {0};

        int iRv = ::strerror_r(static_cast<int>( a_ciCode ), &szBuff[0], xARRAY_SIZE(szBuff));
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
