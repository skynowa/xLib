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
    /*DEBUG*/// n/a

    ULONG ulCode = 0; /*= culCodeSuccess*/;

#if defined(xOS_WIN)
    ulCode = ::GetLastError();
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    ulCode = static_cast<ULONG>( errno );
#endif

    bReset();
    /*DEBUG*/// n/a

    return ulCode;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxLastError::sGet() {
    /*DEBUG*/

    return sFormat(ulGet());
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxLastError::bSet(
    const ULONG culCode
)
{
    /*DEBUG*/// ulCode - n/a

#if defined(xOS_WIN)
    (VOID)::SetLastError(culCode);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    errno = static_cast<INT>( culCode );
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxLastError::bReset() {
    /*DEBUG*/// n/a

    const ULONG culCodeSuccess = 0;

    return bSet(culCodeSuccess);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring
CxLastError::sFormat(
    const ULONG culCode
)
{
    /*DEBUG*/// ulCode - n/a

    std::tstring sRes;

    sRes.append( CxString::sFormat(xT("%u - "), culCode) );

#if defined(xOS_WIN)
    ULONG   ulRes  = 0;
    LPVOID  pvBuff = NULL;
    HLOCAL  hRes   = NULL;

    ulRes = ::FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    culCode,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    reinterpret_cast<LPTSTR>( &pvBuff ),
                    0,
                    NULL);

    //317 - "Не удается найти текст сообщения с номером 0x%1 в файле сообщений %2."
    xCHECK_RET(317 == ulGet(), xT("Unknown error"));
    /*DEBUG*/xASSERT_RET(0 != ulRes, std::tstring());

    sRes.append( CxString::sRemoveEol(std::tstring(static_cast<LPCTSTR>(pvBuff), ulRes)) );

    hRes = ::LocalFree(pvBuff);
    /*DEBUG*/xASSERT_RET(NULL == hRes, std::tstring());
#elif defined(xOS_LINUX)
    sRes.append( strerror( static_cast<INT>(culCode) ) );
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
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*virtual*/
CxLastError::~CxLastError() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
