/****************************************************************************
* Class name:  CxSocketInit
* Description: initiates use of the Winsock DLL by a process
* File name:   CxSocketInit.cpp
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     22.06.2010 10:25:42
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Net/CxSocketInit.h>


/****************************************************************************
*    public                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxSocketInit (init winsock DLL)
CxSocketInit::CxSocketInit(USHORT usMajorVersion, USHORT usMinorVersion) {
#if defined(xOS_WIN)
    WSADATA wdData = {0};

	INT iRes = ::WSAStartup(MAKEWORD(usMajorVersion, usMinorVersion), &wdData);
	/*DEBUG*/xASSERT_DO(0 == iRes, return);

	//Confirm that the WinSock DLL supports some version
	if (HIBYTE(wdData.wVersion) != usMinorVersion || LOBYTE(wdData.wVersion) != usMajorVersion) {
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
