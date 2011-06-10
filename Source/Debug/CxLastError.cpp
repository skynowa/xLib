/****************************************************************************
* Class name:  CxLastError
* Description: system last error
* File name:   CxLastError.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25 січ. 2011 11:01:46
*
*****************************************************************************/


#include <xLib/Debug/CxLastError.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: ulGet (Retrieves the calling thread's last-error code value)
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
//DONE: bSet (Sets the last-error code for the calling thread)
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
//DONE: sGet (get as string)
/*static*/
tString
CxLastError::sGet() {
    /*DEBUG*/

    return sFormat(ulGet());
}
//---------------------------------------------------------------------------
//DONE: bReset (set last-error code to 0)
/*static*/
BOOL
CxLastError::bReset() {
    /*DEBUG*/// n/a

    const ULONG culCodeSuccess = 0;

    return bSet(culCodeSuccess);
}
//---------------------------------------------------------------------------
//DONE: sFormat (get last error as string)
/*static*/
tString
CxLastError::sFormat(
    const ULONG culCode
)
{
    /*DEBUG*/// ulCode - n/a

    tString sRes;

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
                    NULL
    );

    //317 - "Не удается найти текст сообщения с номером 0x%1 в файле сообщений %2."
    xCHECK_RET(317 == ulGet(), xT("Unknown error"));
    /*DEBUG*/xASSERT_RET(0 != ulRes, tString());

    sRes.append( CxString::sRemoveEol(tString(static_cast<LPCTSTR>(pvBuff), ulRes)) );

    hRes = ::LocalFree(pvBuff);
    /*DEBUG*/xASSERT_RET(NULL == hRes, tString());
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
//DONE: CxLastError
CxLastError::CxLastError() {
    /*DEBUG*/// n/a

}
//---------------------------------------------------------------------------
//DONE: ~CxLastError
/*virtual*/
CxLastError::~CxLastError() {
    /*DEBUG*/// n/a

}
//---------------------------------------------------------------------------
