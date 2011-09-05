/****************************************************************************
* Class name:  CxTest_CxThread
* Description: test CxThread
* File name:   CxTest_CxThread.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxThread.h>

#include <xLib/Common/CxDateTime.h>

//---------------------------------------------------------------------------
//DONE: CxTest_CxThread
CxTest_CxThread::CxTest_CxThread() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxThread
CxTest_CxThread::~CxTest_CxThread() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxThread::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    #if xTODO
        size_t uiI = 0;

        //while (true) {
            const BOOL cbIsPaused   = TRUE;
            const BOOL cbAutoDelete = TRUE;

            CWorkThread *pthT = new CWorkThread(cbAutoDelete);
            xASSERT_NOT_EQ(NULL, pthT);

            uiI ++;

            pthT->m_uiIndex = uiI;
            ////pthT->vOnExit2  = vOnExitHandle;

            //-------------------------------------
            //�������z
            INT iParam = 1000/*00000*/;
            m_bRes = pthT->bCreate(cbIsPaused, 0, &iParam);
            xASSERT_NOT_EQ(FALSE, m_bRes);
            ////LOG("bCreate()");

            m_bRes = pthT->bIsPaused();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = pthT->bIsPaused();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            //-------------------------------------
            //����� ��������
            m_bRes = pthT->bIsCreated();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = pthT->bIsRunning();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = pthT->bIsPaused();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = pthT->bIsExited();
            xASSERT_EQ(FALSE, m_bRes);

            //-------------------------------------
            //���������
            ////m_bRes = pthT->bPostMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            ////m_bRes = pthT->bSendMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            ////m_bRes = pthT->bPostThreadMessage(WM_TEST_MSG_1, 0, 0);

            //-------------------------------------
            //���������
            m_bRes = pthT->bSetPriority(CxThread::tpLowest);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_iRes = pthT->tpGetPriority();
            xASSERT_EQ(CxThread::tpLowest, m_iRes);

            m_sRes = pthT->sGetPriorityString();
            xASSERT_EQ(std::tstring(xT("Lowest")), m_sRes);

            m_bRes = pthT->bPriorityUp();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = pthT->bPriorityDown();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = pthT->bIsPriorityBoost();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            {
                m_bRes = pthT->bSetPriorityBoost(FALSE);
                xASSERT_NOT_EQ(FALSE, m_bRes);

                m_bRes = pthT->bIsPriorityBoost();
                xASSERT_EQ(FALSE, m_bRes);
            }
            {
                m_bRes = pthT->bSetPriorityBoost(TRUE);
                xASSERT_NOT_EQ(FALSE, m_bRes);

                m_bRes = pthT->bIsPriorityBoost();
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }

            //-------------------------------------
            //CPU
            ////m_bRes = bSetAffinityMask(DWORD_PTR pulMask);
            ////xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = pthT->bSetIdealCPU(0);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_ulRes = pthT->ulGetIdealCPU();
            xASSERT_LESS_EQ(0, m_ulRes);

            m_bRes = pthT->bSetIdealCPU(10);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = pthT->bSetIdealCPU(0);
            xASSERT_NOT_EQ(FALSE, m_bRes);
            ////LOG("bSetIdealCPU()");

            m_ulRes = pthT->ulGetIdealCPU();
            xASSERT_EQ(0, m_ulRes);

            m_ulRes = pthT->ulGetCPUCount();
            xASSERT_LESS(0 < m_ulRes);

            //-------------------------------------
            //���������
            m_hRes  = pthT->hGetHandle();
            xASSERT_NOT_EQ(NULL, m_hRes);

            m_ulRes = pthT->ulGetId();
            xASSERT_LESS(0, m_ulRes);

            //bIsCurrent
            m_bRes = pthT->bIsCurrent();
            xASSERT_EQ(FALSE, m_bRes);

            m_ulRes = pthT->ulGetExitCode();
            xASSERT_LESS_EQ(0, m_ulRes);

            m_bRes = pthT->bSetDebugName(xT("TestThreadName"));
            xASSERT_NOT_EQ(FALSE, m_bRes);
            ////LOG("bSetDebugName()");

            //-------------------------------------
            //static
            ////g_hRes = CxThread::hOpen(THREAD_ALL_ACCESS, FALSE, ::GetCurrentThreadId());
            ////xASSERT_EQ(NULL != g_hRes);

            m_ulRes = CxThread::ulGetCurrId();
            xASSERT_EQ(0 < m_ulRes);

            m_hRes  = CxThread::hGetCurrHandle();
            xASSERT_EQ(NULL !=  m_hRes);

            m_bRes = pthT->bResume();
            xASSERT_NOT_EQ(FALSE, m_bRes);
            ////LOG("bResume()");

            //-------------------------------------
            //�����
            for (int i = 0; i < 3; i ++) {
                m_bRes = pthT->bPause();
                xASSERT_NOT_EQ(FALSE, m_bRes);

                m_bRes = pthT->bIsPaused();
                xASSERT_NOT_EQ(FALSE, m_bRes);

                m_bRes = pthT->bResume();
                xASSERT_NOT_EQ(FALSE, m_bRes);

                m_bRes = pthT->bIsPaused();
                xASSERT_EQ(FALSE, m_bRes);
            }

            ////m_bRes = pthT->bExit(INFINITE);
            ////xASSERT_NOT_EQ(FALSE, m_bRes);
            ////////LOG("bExit()");

            ////g_uiRes = pthT->uiKill(INFINITE);
            ////xASSERT_EQ(0, g_uiRes);
            ////////////LOG("uiKill()");

            ////m_bRes = pthT->bWait(INFINITE);
            ////xASSERT_NOT_EQ(FALSE, m_bRes);
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
        xASSERT_LESS((ULONG)0, (ULONG)idRes);
    }

    //--------------------------------------------------
    //bIsCurrent
    {
        CxThread::TId aulData[5][2] = {{0}};

        aulData[0][0] = (CxThread::TId)CxThread::ulGetCurrId();
        aulData[0][1] = (CxThread::TId)TRUE;

        aulData[1][0] = (CxThread::TId)((ULONG)CxThread::ulGetCurrId() - 1);
        aulData[1][1] = (CxThread::TId)FALSE;

        aulData[2][0] = (CxThread::TId)0;
        aulData[2][1] = (CxThread::TId)FALSE;

        aulData[3][0] = (CxThread::TId) - 1;
        aulData[3][1] = (CxThread::TId)FALSE;

        aulData[4][0] = (CxThread::TId)- 1;
        aulData[4][1] = (CxThread::TId)FALSE;

        for (std::size_t i = 0; i < xARRAY_SIZE(aulData); ++ i) {
            const CxThread::TId culId = aulData[i][0];
            const BOOL          cbRes = (BOOL)(ULONG)aulData[i][1];

            m_bRes = CxThread::bIsCurrent(culId);
            xASSERT_EQ(cbRes, m_bRes);
        }
    }

    //--------------------------------------------------
    //hGetCurrHandle
    {
        CxThread::THandle hRes = CxThread::hGetCurrHandle();
        xASSERT_LESS((ULONG)0, (ULONG)hRes);
    }

    //--------------------------------------------------
    //bYield
    {
        m_bRes = CxThread::bYield();
        xASSERT_NOT_EQ(FALSE, m_bRes);
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
	        xASSERT_NOT_EQ(FALSE, m_bRes);

	        CxDateTime dtTime2 = CxDateTime::dtGetCurrent();

	        xASSERT_GREATER_EQ(dtTime2.ullToMilliseconds(), dtTime1.ullToMilliseconds());
	        //xTRACEV(xT("sNow1: %s,\nsNow2: %s"), dtTime1.sFormat(CxDateTime::ftTime).c_str(), dtTime2.sFormat(CxDateTime::ftTime).c_str());
        }
    }


    /****************************************************************************
    *    public: CPU
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bSetAffinityMask
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            const INT ciProcCount = 2;

            for (INT i = 0; i < ciProcCount; ++ i) {
                m_bRes = CxThread::bSetAffinityMask(i);
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
