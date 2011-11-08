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
INT
CxStdError::iGet() {
    INT iCode = 0; /*= ciCodeSuccess*/;

    iCode = errno;

    (VOID)bReset();

    return iCode;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxStdError::sGet() {
    return sFormat(iGet());
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxStdError::bSet(
    const INT ciCode
)
{
    errno = ciCode;

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxStdError::bReset() {
    const INT ciCodeSuccess = 0;

    return bSet(ciCodeSuccess);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxStdError::sFormat(
    const INT ciCode
)
{
    std::tstring sRes;

    sRes = CxString::sFormat(xT("%li - "), ciCode);

#if defined(xOS_ENV_WIN)
    TCHAR *pcszError = (TCHAR *)_tcserror(ciCode);
    xCHECK_RET(NULL == pcszError, sRes.append(xT("[Cann't format error message]")));

    sRes.append(pcszError);
#elif defined(xOS_ENV_UNIX)
    #if defined(xOS_LINUX)
        CHAR szBuff[64 + 1] = {0};

        const TCHAR *pcszError = strerror_r(ciCode, &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(NULL == pcszError, sRes.append(xT("[Cann't format error message]")));

        sRes.append(pcszError);
    #else
        CHAR szBuff[64 + 1] = {0};

        INT iRes = strerror_r(static_cast<INT>( ciCode ), &szBuff[0], xARRAY_SIZE(szBuff));
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
