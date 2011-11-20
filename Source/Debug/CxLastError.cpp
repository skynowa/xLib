/**
 * \file  CxLastError.cpp
 * \brief system last error
 */


#include <xLib/Debug/CxLastError.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
ULONG
CxLastError::ulGet() {
    ULONG ulCode = 0UL; /*= culCodeSuccess*/;

#if xOS_ENV_WIN
    ulCode = ::GetLastError();
#elif xOS_ENV_UNIX
    ulCode = static_cast<ULONG>( errno );
#endif

    (void)bReset();

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
bool
CxLastError::bSet(
    const ULONG culCode
)
{
#if xOS_ENV_WIN
    (void)::SetLastError(culCode);
#elif xOS_ENV_UNIX
    errno = static_cast<int>( culCode );
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
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

    sRes = CxString::sFormat(xT("%lu - "), culCode);

#if xOS_ENV_WIN
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

    (void)::LocalFree(pvBuff);
#elif xOS_ENV_UNIX
    #if xOS_LINUX
        char szBuff[64 + 1] = {0};

        const tchar *pcszError = ::strerror_r(static_cast<int>( culCode ), &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(NULL == pcszError, sRes.append(xT("[Cann't format error message]")));

        sRes.append(pcszError);
    #else
        char szBuff[64 + 1] = {0};

        int iRes = ::strerror_r(static_cast<int>( culCode ), &szBuff[0], xARRAY_SIZE(szBuff));
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

xNAMESPACE_END(NxLib)
