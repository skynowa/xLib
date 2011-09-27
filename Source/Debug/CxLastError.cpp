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

#if defined(xOS_WIN)
    ulCode = ::GetLastError();
#elif defined(xOS_LINUX)
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
#if defined(xOS_WIN)
    (VOID)::SetLastError(culCode);
#elif defined(xOS_LINUX)
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

#if defined(xOS_WIN)
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
#elif defined(xOS_LINUX)
    CHAR szBuff[64 + 1] = {0};

    const TCHAR *pszError = strerror_r(static_cast<INT>( culCode ), &szBuff[0], xARRAY_SIZE(szBuff));

    sRes.append(pszError);
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
