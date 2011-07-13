/****************************************************************************
* Class name:  CxTest_CxThread
* Description: test CxThread
* File name:   CxTest_CxThread.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxThread (constructor)
CxTest_CxThread::CxTest_CxThread() {
    bSetName(xFUNCTION);
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
    #if xTODO
        size_t uiI = 0;

        //while (true) {
            const BOOL cbIsPaused   = TRUE;
            const BOOL cbAutoDelete = TRUE;

            CWorkThread *pthT = new CWorkThread(cbAutoDelete);
            xASSERT(pthT != NULL);

            uiI ++;

            pthT->m_uiIndex = uiI;
            ///pthT->vOnExit2  = vOnExitHandle;

            //-------------------------------------
            //�������z
            INT iParam = 1000/*00000*/;
            m_bRes = pthT->bCreate(cbIsPaused, 0, &iParam);
            xASSERT(FALSE != m_bRes);
            ////LOG("bCreate()");

            m_bRes = pthT->bIsPaused();
            xASSERT(FALSE != m_bRes);

            m_bRes = pthT->bIsPaused();
            xASSERT(FALSE != m_bRes);

            //-------------------------------------
            //����� ��������
            m_bRes = pthT->bIsCreated();
            xASSERT(FALSE != m_bRes);

            m_bRes = pthT->bIsRunning();
            xASSERT(FALSE != m_bRes);

            m_bRes = pthT->bIsPaused();
            xASSERT(FALSE != m_bRes);

            m_bRes = pthT->bIsExited();
            xASSERT(FALSE == m_bRes);

            //-------------------------------------
            //���������
            ////m_bRes = pthT->bPostMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            ////m_bRes = pthT->bSendMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            ///m_bRes = pthT->bPostThreadMessage(WM_TEST_MSG_1, 0, 0);

            //-------------------------------------
            //���������
            m_bRes = pthT->bSetPriority(CxThread::tpLowest);
            xASSERT(FALSE != m_bRes);

            m_iRes = pthT->tpGetPriority();
            xASSERT(CxThread::tpLowest == m_iRes);

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

            m_bRes = pthT->bSetIdealCPU(0);
            xASSERT(FALSE != m_bRes);
            ////LOG("bSetIdealCPU()");

            m_ulRes = pthT->ulGetIdealCPU();
            xASSERT(0 == m_ulRes);

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

            //-------------------------------------
            //�����
            for (int i = 0; i < 3; i ++) {
                m_bRes = pthT->bPause();
                xASSERT(FALSE != m_bRes);

                m_bRes = pthT->bIsPaused();
                xASSERT(TRUE == m_bRes);

                m_bRes = pthT->bResume();
                xASSERT(FALSE != m_bRes);

                m_bRes = pthT->bIsPaused();
                xASSERT(FALSE == m_bRes);
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
    #endif

    //static
    //--------------------------------------------------
    //hOpen
    {
        #if xTODO
            THandle hRes = CxThread::hOpen(const ULONG culAccess, const BOOL cbInheritHandle, const ULONG culId);
        #endif
    }

    //--------------------------------------------------
    //ulGetCurrId
    {
        CxThread::TId idRes = CxThread::ulGetCurrId();
        xASSERT(0 < idRes);
    }

    //--------------------------------------------------
    //hGetCurrHandle
    {
        CxThread::THandle hRes = CxThread::hGetCurrHandle();
        xASSERT(0 < hRes);
    }

    //--------------------------------------------------
    //bYield
    {
        m_bRes = CxThread::bYield();
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //bSleep
    {
        const ULONG caulData[] = {
            0, 
            1,
            (std::numeric_limits<ULONG>::min)(),
            //(std::numeric_limits<ULONG>::max)()
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
	        const UINT cuiMsec = caulData[i];
	
	        CxDateTime dtTime1 = CxDateTime::dtGetCurrent();
	
	        m_bRes = CxThread::bSleep(cuiMsec);
	        xASSERT(FALSE != m_bRes);
	
	        CxDateTime dtTime2 = CxDateTime::dtGetCurrent();
	
	        xASSERT(dtTime2.ullToMilliseconds() >= dtTime1.ullToMilliseconds());
	        //xTRACEV(xT("sNow1: %s,\nsNow2: %s"), dtTime1.sFormat(CxDateTime::ftTime).c_str(), dtTime2.sFormat(CxDateTime::ftTime).c_str());
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
