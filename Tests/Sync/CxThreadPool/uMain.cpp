#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include <xLib/CxString.h>
#include <xLib/Sync/CxThreadPool.h>
#include <xLib/Debug/CxAssert.h>
#include <xLib/Sync/CxCriticalSection.h>
#include <xLib/Sync/CxAutoCriticalSection.h>
#include <xLib/Fso/CxStdioFile.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>

#include "CWorkThread.h"
//---------------------------------------------------------------------------
BOOL         g_bRes    = FALSE;
INT          g_iRes    = - 1;
UINT         g_uiRes   = 0;
ULONG        g_ulRes   = 0;
ULONGLONG    g_ullRes  = 0UL;
HANDLE       g_hRes    = NULL;
HWND         g_hwndRes = NULL;
std::string  g_sRes;
CxConsoleLog g_clLog;
//---------------------------------------------------------------------------
#define LOG(s) /*g_clLog.bWrite(_T("%s\n"), _T(s)) */
//---------------------------------------------------------------------------
////CxThreadPool<CWorkThread> *thpTP = NULL;
//////---------------------------------------------------------------------------
//////TODO: - uiOnRun
////class CTest {
////	public:
////		UINT        m_uiIndex;
////				    CTest         ();
////			       ~CTest         ();
////		static UINT s_uiThreadFunc(VOID *pData); 
////
////		BOOL bRun();
////};
//////---------------------------------------------------------------------------
////CTest::CTest() :
////	m_uiIndex(0)
////{
////}
////CTest::~CTest() {
////
////}
////UINT CTest::s_uiThreadFunc(VOID *pData) {
////	/*LOG*/thpTP->_m_clLog.bWrite(_T("Start thread: #%i\n"), 0); 
////
////	CTest *pThis = static_cast<CTest *>(pData);
////	/*DEBUG*/xASSERT_RET(NULL != pThis, 0);
////
////	UINT uiRes = 0;
////	BOOL bRes  = FALSE;
////
////	for (UINT i = 0; i < pThis->m_uiIndex + 1; i ++, uiRes ++) {
////		//-------------------------------------
////		//не пора ли выйти или приостановиться
////		////bRes = thpTP->bIsTimeToExit();
////		////xCHECK_DO(FALSE == bRes, break);
////
////		/*if (TRUE == thpTP->bIsExited()) {
////			return uiRes;
////		}*/
////
////		for (UINT j = 0; j < 5; j ++) {
////			/*LOG*/thpTP->_m_clLog.bWrite(_T("*\n")); 
////			::Sleep(500);
////		}
////	}	
////
////	/*LOG*/thpTP->_m_clLog.bWrite(_T("End thread: #%i\n"), 0); 
////
////	return uiRes;
////}
////BOOL CTest::bRun() {
////	m_uiIndex = 1;
////	s_uiThreadFunc(this);
////
////	return TRUE;
////}
//---------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[]) {
	tString              sFilePath = _T("C:/test.txt");
	std::vector<tString> vecsFileContent;

	g_bRes = CxStdioFile::bReadFile(sFilePath, &vecsFileContent);
	xASSERT(FALSE != g_bRes);

	CxThreadPool<CWorkThread> *thpTP = new CxThreadPool<CWorkThread>(TRUE, FALSE, TRUE);
	xASSERT(NULL != thpTP);
     
	g_bRes = thpTP->bCreate(0, 0, NULL);
	xASSERT(FALSE != g_bRes);

	//-------------------------------------
	//действия с группой
	g_bRes = thpTP->bCreateGroup(0, /*(UINT (WINAPI *)(VOID *))&CTest::s_uiThreadFunc*/0, &vecsFileContent);
	xASSERT(FALSE != g_bRes);

	g_bRes = thpTP->bResume();        
	xASSERT(FALSE != g_bRes);

    g_bRes = thpTP->bResumeGroup();
	xASSERT(FALSE != g_bRes);

    g_bRes = thpTP->bPauseGroup();
	xASSERT(FALSE != g_bRes);

	g_bRes = thpTP->bExitGroup(5000);
	xASSERT(FALSE != g_bRes);

	////g_bRes = thpTP->bWaitGroup(5000);
	////xASSERT(FALSE != g_bRes);


	////::Sleep(10000);

	////g_uiRes = thpTP->uiKillGroup(5000);
	////xASSERT(0 == g_uiRes);





    std::cout << std::endl << std::endl << "Complete...\n";
	::Sleep(INFINITE);
	//system("pause");
	return 0;
}
//---------------------------------------------------------------------------