/****************************************************************************
* Class name:  CxSocketInit
* Description: initiates use of the Winsock DLL by a process
* File name:   CxSocketInit.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     22.06.2010 10:25:42
*
*****************************************************************************/


#include <xLib/Net/CxSocketInit.h>

#if defined(xOS_WIN)
    #if defined(xCOMPILER_MS)
        #pragma comment(lib, "WS2_32.Lib")
    #endif
#elif defined(xOS_LINUX)
    // n/a
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxSocketInit (init winsock DLL)
CxSocketInit::CxSocketInit(
    const USHORT cusMajorVersion,
    const USHORT cusMinorVersion
)
{
#if defined(xOS_WIN)
    WSADATA wdData = {0};

    INT iRes = ::WSAStartup(MAKEWORD(cusMajorVersion, cusMinorVersion), &wdData);
    /*DEBUG*/xASSERT_DO(0 == iRes, return);

    //Confirm that the WinSock DLL supports some version
    if (HIBYTE(wdData.wVersion) != cusMinorVersion || LOBYTE(wdData.wVersion) != cusMajorVersion) {
        iRes = ::WSACleanup();
        /*DEBUG*/xASSERT_DO(0 == iRes, return);

        /*DEBUG*/xASSERT_DO(FALSE,     return);
    }
#elif defined(xOS_LINUX)
    // n/a
#endif
}
//---------------------------------------------------------------------------
//DONE: ~CxSocketInit (clean winsock DLL)
CxSocketInit::~CxSocketInit() {
#if defined(xOS_WIN)
    INT iRes = ::WSACleanup();
    /*DEBUG*/xASSERT_DO(0 == iRes, return);
#elif defined(xOS_LINUX)
    // n/a
#endif
}
//---------------------------------------------------------------------------
