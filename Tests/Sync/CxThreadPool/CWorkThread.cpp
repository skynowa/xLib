/****************************************************************************
* Class name:  CWorkThread
* Description: рабочий поток
* File name:   CWorkThread.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.12.2009 22:10:16
*
*****************************************************************************/


#include "CWorkThread.h"

#include <xLib/CxString.h>
#include <xLib/Sync/CxThreadPool.h>
//---------------------------------------------------------------------------


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CWorkThread
CWorkThread::CWorkThread(BOOL bIsPaused, BOOL bAutoDelete, BOOL bIsUsingCOM) :
	CxThread (bIsPaused, bAutoDelete, bIsUsingCOM),
	m_uiIndex(0)
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
	/*LOG*/_m_clLog.bWrite(_T("Start thread: #%i\n"), m_uiIndex); 
	
	UINT uiRes = 0;
	BOOL bRes  = FALSE;

	std::vector<tString> *pvecsThis = static_cast<std::vector<tString> *>(pData);
	/*DEBUG*/xASSERT_RET(NULL != pvecsThis, 0);

	for (UINT i = 0; i < pvecsThis->size(); i ++, uiRes ++) {
		//-------------------------------------
		//не пора ли выйти или приостановиться
		bRes = bIsTimeToExit();
		xCHECK_DO(FALSE == bRes, break);
		

		/*LOG*/_m_clLog.bWrite(_T("%i: %s\n"), i, pvecsThis->at(i).c_str()); 
		bSleep(500);
	}	

	/*LOG*///_m_clLog.bWrite(_T("End thread: #%i\n"), m_uiIndex); 

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
	//LOG("vOnExit");
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------