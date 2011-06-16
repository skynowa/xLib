/****************************************************************************
* Class name:  CxTest_CxThread
* Description: test CxThread
* File name:   CxTest_CxThread.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxThreadH
#define CxTest_CxThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxThread.h>

#include "CWorkThread.h"
//---------------------------------------------------------------------------
class CxTest_CxThread :
    public CxTest
{
	public:
		CxTest_CxThread();
		virtual     ~CxTest_CxThread();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxThread (constructor)
CxTest_CxThread::CxTest_CxThread() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxThread (destructor)
CxTest_CxThread::~CxTest_CxThread() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxThread::bUnit() {
	size_t uiI = 0;

	//while (true) {
		CWorkThread *pthT = new CWorkThread(TRUE, TRUE);
		xASSERT(pthT != NULL);

		uiI ++;

		pthT->m_uiIndex = uiI;
		///pthT->vOnExit2  = vOnExitHandle;

		//-------------------------------------
		//�������z
		INT iParam = 1000/*00000*/;
		m_bRes = pthT->bCreate(0, &iParam);
		xASSERT(FALSE != m_bRes);
		////LOG("bCreate()");

		//-------------------------------------
		//����� ��������
		m_bRes = pthT->bIsCreated();
		xASSERT(FALSE != m_bRes);
		////LOG("bIsCreated()");

		m_bRes = pthT->bIsRunning();
		xASSERT(FALSE != m_bRes);
		////LOG("bIsRunning()");

		m_bRes = pthT->bIsPaused();
		xASSERT(FALSE != m_bRes);
		////LOG("bIsPaused()");

		//////m_bRes = pthT->bIsSleeping();
		//////xASSERT(FALSE == m_bRes);
		//////////LOG("bIsSleeping()");

		m_bRes = pthT->bIsExited();
		xASSERT(FALSE == m_bRes);
		////LOG("bIsExited()");


		//-------------------------------------
		//���������
		////m_bRes = pthT->bPostMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
		////m_bRes = pthT->bSendMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
		///m_bRes = pthT->bPostThreadMessage(WM_TEST_MSG_1, 0, 0);

		//-------------------------------------
		//���������
		m_bRes = pthT->bSetPriority(CxThread::tpPRIORITY_LOWEST);
		xASSERT(FALSE != m_bRes);

		m_iRes = pthT->tpGetPriority();
		xASSERT(CxThread::tpPRIORITY_LOWEST == m_iRes);

		m_sRes = pthT->sGetPriorityString();
		xASSERT(tString(xT("Lowest")) == m_sRes);

		m_bRes = pthT->bPriorityUp();
		xASSERT(FALSE != m_bRes);

		m_bRes = pthT->bPriorityDown();
		xASSERT(FALSE != m_bRes);

		m_bRes = pthT->bIsPriorityBoost();
		xASSERT(FALSE != m_bRes);

		{
			m_bRes = pthT->bSetPriorityBoost(FALSE);
			xASSERT(FALSE != m_bRes);

			m_bRes = pthT->bIsPriorityBoost();
			xASSERT(FALSE == m_bRes);
		}
		{
			m_bRes = pthT->bSetPriorityBoost(TRUE);
			xASSERT(FALSE != m_bRes);

			m_bRes = pthT->bIsPriorityBoost();
			xASSERT(TRUE == m_bRes);
		}



		//-------------------------------------
		//CPU
		////m_bRes = bSetAffinityMask(DWORD_PTR pulMask);
		////xASSERT(FALSE != m_bRes);

		m_bRes = pthT->bSetIdealCPU(0);
		xASSERT(FALSE != m_bRes);

		m_ulRes = pthT->ulGetIdealCPU();
		xASSERT(0 <= m_ulRes);

		m_bRes = pthT->bSetIdealCPU(10);
		xASSERT(FALSE != m_bRes);
		////LOG("bSetIdealCPU()");

		m_bRes = pthT->bSetIdealCPU(0);
		xASSERT(FALSE != m_bRes);
		////LOG("bSetIdealCPU()");

		m_ulRes = pthT->ulGetIdealCPU();
		xASSERT(0 == m_ulRes);
		////LOG("ulGetIdealCPU()");

		m_ulRes = pthT->ulGetCPUCount();
		xASSERT(0 < m_ulRes);


		//-------------------------------------
		//���������
		m_hRes  = pthT->hGetHandle();
		xASSERT(NULL != m_hRes);

		m_ulRes = pthT->ulGetId();
		xASSERT(0 < m_ulRes);

		m_ulRes = pthT->ulGetExitCode();
		xASSERT(0 <= m_ulRes);

		m_bRes = pthT->bSetDebugName(xT("TestThreadName"));
		xASSERT(FALSE != m_bRes);
		////LOG("bSetDebugName()");


		//-------------------------------------
		//static
		////g_hRes = CxThread::hOpen(THREAD_ALL_ACCESS, FALSE, ::GetCurrentThreadId());
		////xASSERT(NULL != g_hRes);

		m_ulRes = CxThread::ulGetCurrId();
		xASSERT(0 < m_ulRes);

		m_hRes  = CxThread::hGetCurrHandle();
		xASSERT(NULL !=  m_hRes);


		m_bRes = pthT->bResume();
		xASSERT(FALSE != m_bRes);
		////LOG("bResume()");

		m_bRes = pthT->bResume();
		xASSERT(FALSE != m_bRes);
		////LOG("bResume()");

		//-------------------------------------
		//�����
		for (int i = 0; i < 3; i ++) {
			//::MessageBox(0, xT("�������������"), xT(""), MB_OK);

			m_bRes = pthT->bPause();
			xASSERT(FALSE != m_bRes);
			////LOG("bPause()");

			//::MessageBox(0, xT("�����������"), xT(""), MB_OK);

			m_bRes = pthT->bResume();
			xASSERT(FALSE != m_bRes);
			////LOG("bResume()");
		}

		////m_bRes = pthT->bExit(INFINITE);
		////xASSERT(FALSE != m_bRes);
		////////LOG("bExit()");

		////g_uiRes = pthT->uiKill(INFINITE);
		////xASSERT(0 == g_uiRes);
		////////////LOG("uiKill()");

		////m_bRes = pthT->bWait(INFINITE);
		////xASSERT(FALSE != m_bRes);
		////////LOG("bWait(INFINITE)");

		ULONG ulRes = pthT->ulGetExitCode();
		////LOG("ulGetExitCode(): ");
		//////LOG(lexical_cast(ulRes).c_str());

		///////////////////////////////////::Sleep(1000);
		//system("pause");
	//}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxThreadH

