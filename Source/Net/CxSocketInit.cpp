/**
 * \file  CxSocketInit.cpp
 * \brief initiates use of the Winsock DLL by a process
 */


#include <xLib/Net/CxSocketInit.h>

#if xOS_ENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "WS2_32.Lib")
    #endif
#elif xOS_ENV_UNIX
    // n/a
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxSocketInit::CxSocketInit(
    const ushort_t cusMajorVersion,
    const ushort_t cusMinorVersion
)
{
#if xOS_ENV_WIN
    WSADATA wdData = {0};

    int iRes = ::WSAStartup(MAKEWORD(cusMajorVersion, cusMinorVersion), &wdData);
    /*DEBUG*/xASSERT_DO(0 == iRes, return);

    //Confirm that the WinSock DLL supports some version
    if (HIBYTE(wdData.wVersion) != cusMinorVersion || LOBYTE(wdData.wVersion) != cusMajorVersion) {
        iRes = ::WSACleanup();
        /*DEBUG*/xASSERT_DO(0 == iRes, return);

        /*DEBUG*/xASSERT_DO(false,     return);
    }
#elif xOS_ENV_UNIX
    // n/a
#endif
}
//---------------------------------------------------------------------------
CxSocketInit::~CxSocketInit() {
#if xOS_ENV_WIN
    int iRes = ::WSACleanup();
    /*DEBUG*/xASSERT_DO(0 == iRes, return);
#elif xOS_ENV_UNIX
    // n/a
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
