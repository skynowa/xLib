/**
 * \file  CxLastError.cpp
 * \brief system last error
 */


#include <xLib/Debug/CxLastError.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
ULONG
CxLastError::ulGet() {
    ULONG ulCode = 0UL; /*= culCodeSuccess*/;

#if defined(xOS_ENV_WIN)
    ulCode = ::GetLastError();
#elif defined(xOS_ENV_UNIX)
    ulCode = static_cast<ULONG>( errno );
#endif

    (VOID)bReset();

    return ulCode;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxLastError::sGet() {
    return sFormat(ulGet());
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxLastError::bSet(
    const ULONG culCode
)
{
#if defined(xOS_ENV_WIN)
    (VOID)::SetLastError(culCode);
#elif defined(xOS_ENV_UNIX)
    errno = static_cast<INT>( culCode );
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxLastError::bReset() {
    const ULONG culCodeSuccess = 0UL;

    return bSet(culCodeSuccess);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxLastError::sFormat(
    const ULONG culCode
)
{
    std::tstring sRes;

    sRes = CxString::sFormat(xT("%li - "), culCode);

#if defined(xOS_ENV_WIN)
    ULONG  ulRes  = 0UL;
    LPVOID pvBuff = NULL;

    ulRes = ::FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    culCode,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    reinterpret_cast<LPTSTR>( &pvBuff ),
                    0UL,
                    NULL);

    xCHECK_RET(ERROR_MR_MID_NOT_FOUND == ulGet(), sRes.append(xT("Unknown error")));
    xCHECK_RET(0UL                    == ulRes,   sRes.append(xT("[Cann't format error message]")));

    std::tstring sMessage;

    sMessage.assign( static_cast<LPCTSTR>( pvBuff ), ulRes );
    sMessage.assign( CxString::sRemoveEol(sMessage) );
    sMessage.assign( CxString::sTrimRightChars(sMessage, CxConst::xDOT) );

    sRes.append(sMessage);

    (VOID)::LocalFree(pvBuff);
#elif defined(xOS_ENV_UNIX)
    #if defined(xOS_LIUNIX)
        CHAR szBuff[64 + 1] = {0};

        const TCHAR *pcszError = strerror_r(static_cast<INT>( culCode ), &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(NULL == pcszError, sRes.append(xT("[Cann't format error message]")));

        sRes.append(pcszError);
    #else
        CHAR szBuff[64 + 1] = {0};

        INT iRes = strerror_r(static_cast<INT>( culCode ), &szBuff[0], xARRAY_SIZE(szBuff));
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
CxLastError::CxLastError() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxLastError::~CxLastError() {

}
//---------------------------------------------------------------------------
