/**
 * \file  CxStdError.cpp
 * \brief standard C library last error
 */


#include <xLib/Debug/CxStdError.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
int
CxStdError::iGet() {
    int iCode = 0; /*= ciCodeSuccess*/;

    iCode = errno;

    (void)bReset();

    return iCode;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxStdError::sGet() {
    return sFormat(iGet());
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxStdError::bSet(
    const int ciCode
)
{
    errno = ciCode;

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxStdError::bReset() {
    const int ciCodeSuccess = 0;

    return bSet(ciCodeSuccess);
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxStdError::sFormat(
    const int ciCode
)
{
    std::string_t sRes;

    sRes = CxString::sFormat(xT("%li - "), ciCode);

#if defined(xOS_ENV_WIN)
    char_t *pcszError = (char_t *)_tcserror(ciCode);
    xCHECK_RET(NULL == pcszError, sRes.append(xT("[Cann't format error message]")));

    sRes.append(pcszError);
#elif defined(xOS_ENV_UNIX)
    #if defined(xOS_LINUX)
        char szBuff[64 + 1] = {0};

        const char_t *pcszError = strerror_r(ciCode, &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(NULL == pcszError, sRes.append(xT("[Cann't format error message]")));

        sRes.append(pcszError);
    #else
        char szBuff[64 + 1] = {0};

        int iRes = strerror_r(static_cast<int>( ciCode ), &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(- 1 == iRes, sRes.append(xT("[Cann't format error message]")));

        sRes.append(&szBuff[0]);
    #endif
#endif

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxStdError::CxStdError() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxStdError::~CxStdError() {

}
//---------------------------------------------------------------------------
