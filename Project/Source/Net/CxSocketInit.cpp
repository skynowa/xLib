/**
 * \file  CxSocketInit.cpp
 * \brief initiates use of the Winsock DLL by a process
 */


#include <xLib/Net/CxSocketInit.h>

#if xOS_ENV_WIN
    #if xCOMPILER_MS
        #pragma comment(lib, "ws2_32.Lib")
    #endif
#endif


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxSocketInit::CxSocketInit(
    cushort_t &a_cusMajorVersion,
    cushort_t &a_cusMinorVersion
)
{
#if xOS_ENV_WIN
    WSADATA wdData = {0};

    int_t iRv = ::WSAStartup(MAKEWORD(a_cusMajorVersion, a_cusMinorVersion), &wdData);
    xTEST_EQ(0, iRv);
    xTEST_EQ((ushort_t)HIBYTE(wdData.wVersion), a_cusMinorVersion);
    xTEST_EQ((ushort_t)LOBYTE(wdData.wVersion), a_cusMajorVersion);
#endif
}
//------------------------------------------------------------------------------
CxSocketInit::~CxSocketInit() {
#if xOS_ENV_WIN
    int_t iRv = ::WSACleanup();
    xTEST_EQ(0, iRv);
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
