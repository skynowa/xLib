/**
 * \file  CxSocketInit.cpp
 * \brief initiates use of the Winsock DLL by a process
 */


#include <xLib/Net/CxSocketInit.h>

#if xOS_ENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "ws2_32.Lib")
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
#if   xOS_ENV_WIN
    WSADATA wdData = {0};

    int iRes = ::WSAStartup(MAKEWORD(cusMajorVersion, cusMinorVersion), &wdData);
    xASSERT_DO(0 == iRes,                                  return);
    xASSERT_DO(HIBYTE(wdData.wVersion) == cusMinorVersion, return);
    xASSERT_DO(LOBYTE(wdData.wVersion) == cusMajorVersion, return);
#elif xOS_ENV_UNIX
    xNA;
#endif
}
//---------------------------------------------------------------------------
CxSocketInit::~CxSocketInit() {
#if   xOS_ENV_WIN
    int iRes = ::WSACleanup();
    /*DEBUG*/xASSERT_DO(0 == iRes, return);
#elif xOS_ENV_UNIX
    xNA;
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
