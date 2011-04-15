/****************************************************************************
* Class name:  CWorkThread
* Description: рабочий поток
* File name:   CWorkThread.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     10.12.2009 22:10:16
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include "CWorkThread.h"

#include <XLib/CxString.h>
#include <XLib/Sync/CxThreadPool.h>
//---------------------------------------------------------------------------
CxCriticalSection g_csCounter;
volatile size_t   g_uiLinesCount = 0;
//---------------------------------------------------------------------------


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CWorkThread
CWorkThread::CWorkThread(BOOL bIsPaused, BOOL bAutoDelete) :
	CxThread    (bIsPaused, bAutoDelete),
	_m_clLog    (FALSE),
	m_uiIndex   (0)
{
}
//---------------------------------------------------------------------------
//TODO: - ~CWorkThread
CWorkThread::~CWorkThread() {

}
//---------------------------------------------------------------------------



/****************************************************************************
*    Protected methods                                                       
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - uiOnRun
UINT CWorkThread::uiOnRun(VOID *pData) { 
	/*LOG*///_m_clLog.bWrite(_T("uiOnRun start: #%i"), m_uiIndex); 
	
	UINT uiRes = 0;
	BOOL bRes  = FALSE;

	std::vector<tString> *pvecsThis = static_cast<std::vector<tString> *>(pData);
	/*DEBUG*/xASSERT_RET(NULL != pvecsThis, 0);

	////for (UINT i = 0; i < pvecsThis->size(); i ++, uiRes ++) {
	////	//-------------------------------------
	////	//не пора ли выйти или приостановиться
	////	bRes = bIsTimeToExit();
	////	xCHECK_DO(TRUE == bRes, break);
	////	

	////	/*LOG*///_m_clLog.bWrite(_T("Thread #%i  %i: %s"), m_uiIndex, i, pvecsThis->at(i).c_str()); 
	////	/*LOG*///_m_clLog.bWrite(_T("*")); 
	////	bSleep(300);
	////}	

	for (; ;) {
		//-------------------------------------
		//не пора ли выйти или приостановиться
		bRes = bIsTimeToExit();
		xCHECK_DO(TRUE == bRes, break);

		{
			CxAutoCriticalSection CS(g_csCounter);

			if (g_uiLinesCount >= /*pvecsThis->size()*/100) {
				break;
			}
			
			/*LOG*/_m_clLog.bWrite(_T("Thread #%i  %i: %s"), m_uiIndex, g_uiLinesCount, pvecsThis->at(g_uiLinesCount).c_str()); 

			++ g_uiLinesCount;
		}

		bSleep(1000);
	}
	

	/*LOG*///_m_clLog.bWrite(_T("uiOnRun stop: #%i"), m_uiIndex); 

	return uiRes;
}
//---------------------------------------------------------------------------
//TODO: - vOnEnter
VOID CWorkThread::vOnEnter() {
	//LOG("vOnEnter");
}
//---------------------------------------------------------------------------
//TODO: - vOnExit
VOID CWorkThread::vOnExit() {        
	//::OutputDebugString(_T("vOnExit (virtual)\n"));
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------