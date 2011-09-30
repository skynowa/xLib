/**
 * \file  CxSocketInit.cpp
 * \brief initiates use of the Winsock DLL by a process
 */


#include <xLib/Net/CxSocketInit.h>

#if defined(xOS_ENV_WIN)
    #if defined(xCOMPILER_MS)
        #pragma comment(lib, "WS2_32.Lib")
    #endif
#elif defined(xOS_ENV_UNIX)
    // n/a
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSocketInit::CxSocketInit(
    const USHORT cusMajorVersion,
    const USHORT cusMinorVersion
)
{
#if defined(xOS_ENV_WIN)
    WSADATA wdData = {0};

    INT iRes = ::WSAStartup(MAKEWORD(cusMajorVersion, cusMinorVersion), &wdData);
    /*DEBUG*/xASSERT_DO(0 == iRes, return);

    //Confirm that the WinSock DLL supports some version
    if (HIBYTE(wdData.wVersion) != cusMinorVersion || LOBYTE(wdData.wVersion) != cusMajorVersion) {
        iRes = ::WSACleanup();
        /*DEBUG*/xASSERT_DO(0 == iRes, return);

        /*DEBUG*/xASSERT_DO(FALSE,     return);
    }
#elif defined(xOS_ENV_UNIX)
    // n/a
#endif
}
//---------------------------------------------------------------------------
CxSocketInit::~CxSocketInit() {
#if defined(xOS_ENV_WIN)
    INT iRes = ::WSACleanup();
    /*DEBUG*/xASSERT_DO(0 == iRes, return);
#elif defined(xOS_ENV_UNIX)
    // n/a
#endif
}
//---------------------------------------------------------------------------
