/**
 * \file  CxSocketInit.cpp
 * \brief initiates use of the Winsock DLL by a process
 */


#include <xLib/Net/CxSocketInit.h>

#if   xOS_ENV_WIN
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
    const ushort_t a_cusMajorVersion,
    const ushort_t a_cusMinorVersion
)
{
#if   xOS_ENV_WIN
    WSADATA wdData = {0};

    int iRv = ::WSAStartup(MAKEWORD(a_cusMajorVersion, a_cusMinorVersion), &wdData);
    xTEST_EQ(0, iRv);
    xTEST_EQ((ushort_t)HIBYTE(wdData.wVersion), a_cusMinorVersion);
    xTEST_EQ((ushort_t)LOBYTE(wdData.wVersion), a_cusMajorVersion);
#elif xOS_ENV_UNIX
    xNA;
#endif
}
//---------------------------------------------------------------------------
CxSocketInit::~CxSocketInit() {
#if   xOS_ENV_WIN
    int iRv = ::WSACleanup();
    /*DEBUG*/xTEST_EQ(0, iRv);
#elif xOS_ENV_UNIX
    xNA;
#endif
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
