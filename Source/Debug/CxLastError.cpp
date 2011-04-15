/****************************************************************************
* Class name:  CxLastError
* Description: system last error
* File name:   CxLastError.cpp
* Compilers:   Visual C++ 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25 січ. 2011 11:01:46
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Debug/CxLastError.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - ulGet (Retrieves the calling thread's last-error code value)
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
//TODO: - bSet (Sets the last-error code for the calling thread)
/*static*/
BOOL
CxLastError::bSet(ULONG ulCode) {
    /*DEBUG*/// ulCode - n/a

#if defined(xOS_WIN)
    (VOID)::SetLastError(ulCode);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    errno = static_cast<INT>( ulCode );
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bReset (set last-error code to 0)
/*static*/
BOOL
CxLastError::bReset() {
    /*DEBUG*/// n/a

    const ULONG culCodeSuccess = 0;

    return bSet(culCodeSuccess);
}
//---------------------------------------------------------------------------
//TODO: - sFormat (get last error as string)
/*static*/
tString
CxLastError::sFormat(ULONG ulCode) {
    /*DEBUG*/// ulCode - n/a

    tString sRes;

#if defined(xOS_WIN)
    ULONG   ulRes  = 0;
    LPVOID  pvBuff = NULL;
    HLOCAL  hRes   = NULL;

    ulRes = ::FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    ulCode,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  // lang by default
                    reinterpret_cast<LPTSTR>( &pvBuff ),
                    0,
                    NULL
    );

    //317 - "Не удается найти текст сообщения с номером 0x%1 в файле сообщений %2."
    xCHECK_RET(317 == ulGet(), xT("Unknown error"));     
    /*DEBUG*/xASSERT_RET(0 != ulRes, tString());

    sRes = CxString::sRemoveEol(tString(static_cast<LPCTSTR>(pvBuff), ulRes));

    hRes = ::LocalFree(pvBuff);
    /*DEBUG*/xASSERT_RET(NULL == hRes, tString());
#elif defined(xOS_LINUX)
    //not thread safe - not thread safe
    {
        sRes.assign( strerror( static_cast<INT>(ulCode) ) );
    }

    //strerror_r - thread safe
    {
        ////INT iRes = - 1;

        ////sRes.resize(256);

        ////iRes = strerror_r(static_cast<INT>(ulCode), &sRes.at(0), sRes.size());
        /////*DEBUG*/xASSERT_RET(- 1 != iRes, tString());

        ////sRes.assign(sRes.c_str());
    }
#endif

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxLastError (constructor)
CxLastError::CxLastError() {
    /*DEBUG*/// n/a

}
//---------------------------------------------------------------------------
//TODO: - ~CxLastError (destructor)
/*virtual*/
CxLastError::~CxLastError() {
    /*DEBUG*/// n/a

}
//---------------------------------------------------------------------------
