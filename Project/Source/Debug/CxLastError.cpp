/**
 * \file  CxLastError.cpp
 * \brief system last error
 */


#include <xLib/Debug/CxLastError.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
ulong_t
CxLastError::ulGet() {
    ulong_t ulCode = 0UL; /* = culCodeSuccess */;

#if   xOS_ENV_WIN
    ulCode = ::GetLastError();
#elif xOS_ENV_UNIX
    ulCode = static_cast<ulong_t>( errno );
#endif

    vReset();

    return ulCode;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxLastError::sGet() {
    return sFormat(ulGet());
}
//---------------------------------------------------------------------------
/* static */
void
CxLastError::vSet(
    const ulong_t &a_culCode
)
{
#if   xOS_ENV_WIN
    (void)::SetLastError(a_culCode);
#elif xOS_ENV_UNIX
    errno = static_cast<int>( a_culCode );
#endif
}
//---------------------------------------------------------------------------
/* static */
void
CxLastError::vReset() {
    const ulong_t culCodeSuccess = 0UL;

    vSet(culCodeSuccess);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxLastError::sFormat(
    const ulong_t &a_culCode
)
{
    std::tstring_t sRv;

    sRv = CxString::sFormat(xT("%lu - "), a_culCode);

#if xOS_ENV_WIN
    DWORD  dwRv   = 0UL;
    LPVOID pvBuff = NULL;

    dwRv = ::FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    a_culCode,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    reinterpret_cast<LPTSTR>( &pvBuff ),
                    0UL,
                    NULL);

    xCHECK_RET(ERROR_MR_MID_NOT_FOUND == ulGet(), sRv.append(xT("Unknown error")));
    xCHECK_RET(0UL                    == dwRv,    sRv.append(xT("[Cann't format error message]")));

    std::tstring_t sMessage;

    sMessage.assign( static_cast<LPCTSTR>( pvBuff ), dwRv );
    sMessage = CxString::sRemoveEol(sMessage);
    sMessage = CxString::sTrimRightChars(sMessage, CxConst::xDOT);

    sRv.append(sMessage);

    (void)::LocalFree(pvBuff);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        char szBuff[64 + 1] = {0};

        const tchar_t *pcszError = ::strerror_r(static_cast<int>( a_culCode ), &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(NULL == pcszError, sRv.append(xT("[Cann't format error message]")));

        sRv.append(pcszError);
    #elif xOS_FREEBSD
        char szBuff[64 + 1] = {0};

        int iRv = ::strerror_r(static_cast<int>( a_culCode ), &szBuff[0], xARRAY_SIZE(szBuff));
        xCHECK_RET(- 1 == iRv, sRv.append(xT("[Cann't format error message]")));

        sRv.append(&szBuff[0]);
    #endif
#endif

    return sRv;
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
/* virtual */
CxLastError::~CxLastError() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
