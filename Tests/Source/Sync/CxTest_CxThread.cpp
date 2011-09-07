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


/****************************************************************************
*	CWorkThread
*
*****************************************************************************/

//---------------------------------------------------------------------------
CWorkThread::CWorkThread(
    const BOOL cbAutoDelete
) :
    CxThread (cbAutoDelete),
    m_uiIndex(0),
    _m_clLog (FALSE)
{

}
//---------------------------------------------------------------------------
CWorkThread::~CWorkThread() {

}
//---------------------------------------------------------------------------
UINT
CWorkThread::uiOnRun(
    VOID *pvData
)
{
    xTRACEV(xT("Start thread: #%i\n"), m_uiIndex);

    UINT uiRes = 0;
    BOOL bRes  = FALSE;

    //bIsCurrent
    bRes = CxThread::bIsCurrent();
    xASSERT_NOT_EQ(FALSE, bRes);

    for (size_t i = 0; i < 10; ++ i, ++ uiRes) {
        bRes = bIsTimeToExit();
        xCHECK_DO(TRUE == bRes, break);

        for (size_t i = 0; i < 20; i ++) {
            //xTRACEV(xT("*\n"));
            bSleep(1000);
        }
    }

    xTRACEV(xT("End thread: #%i\n"), m_uiIndex);

    return uiRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	CxTest_CxThread
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxTest_CxThread::CxTest_CxThread() {

}
//---------------------------------------------------------------------------
CxTest_CxThread::~CxTest_CxThread() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxThread::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const BOOL cbIsPaused   = TRUE;
    const BOOL cbAutoDelete = TRUE;


    CWorkThread *pthT = new CWorkThread(cbAutoDelete);
    xASSERT_PTR(pthT);

    pthT->m_uiIndex = 0;
    ////pthT->vOnExit2  = vOnExitHandle;


    //-------------------------------------
    //bCreate
    {
        size_t uiParam = 1000;

        m_bRes = pthT->bCreate(cbIsPaused, 0, &uiParam);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        ////LOG("bCreate()");

        m_bRes = pthT->bIsPaused();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = pthT->bIsPaused();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }


    //-------------------------------------
    //flags
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bIsCreated();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = pthT->bIsRunning();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = pthT->bIsPaused();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = pthT->bIsExited();
        xASSERT_EQ(FALSE, m_bRes);
    }


    //-------------------------------------
    //messages
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            m_bRes = pthT->bPostMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRes = pthT->bSendMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRes = pthT->bPostThreadMessage(WM_TEST_MSG_1, 0, 0);
        #endif
    }


    //-------------------------------------
    //priority

    //-------------------------------------
    //bSetPriority, tpGetPriority
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bSetPriority(CxThread::tpLowest);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_iRes = pthT->tpGetPriority();
        xASSERT_EQ((INT)CxThread::tpLowest, (INT)m_iRes);
    }

    //-------------------------------------
    //sGetPriorityString
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = pthT->sGetPriorityString();
        xASSERT_EQ(std::tstring(xT("Lowest")), m_sRes);
    }

    //-------------------------------------
    //bPriorityUp, bPriorityDown
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bPriorityUp();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = pthT->bPriorityDown();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsPriorityBoost
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bIsPriorityBoost();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSetPriorityBoost
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bSetPriorityBoost(FALSE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = pthT->bIsPriorityBoost();
        xASSERT_EQ(FALSE, m_bRes);

        m_bRes = pthT->bSetPriorityBoost(TRUE);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = pthT->bIsPriorityBoost();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }


    //-------------------------------------
    //CPU

    //-------------------------------------
    //bSetAffinityMask
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            m_bRes = bSetAffinityMask(DWORD_PTR pulMask);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bSetIdealCpu, ulGetIdealCpu
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bSetIdealCpu(0);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_ulRes = pthT->ulGetIdealCpu();
        xASSERT_LESS_EQ(0UL, m_ulRes);

        m_bRes = pthT->bSetIdealCpu(10);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = pthT->bSetIdealCpu(0);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_ulRes = pthT->ulGetIdealCpu();
        xASSERT_EQ(0UL, m_ulRes);
    }

    //--------------------------------------------------
    //ulGetCpuCount
    xTEST_BLOCK(cullBlockLoops)
    {
            m_ulRes = pthT->ulGetCpuCount();
            xASSERT_LESS(0UL, m_ulRes);
    }


    //-------------------------------------
    //other

    //-------------------------------------
    //
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxHandle hRes = pthT->hGet();
        xASSERT_NOT_EQ(0UL, (ULONG)hRes);
    }

    //--------------------------------------------------
    //ulGetId
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = pthT->ulGetId();
        xASSERT_LESS(0UL, m_ulRes);
    }

    //--------------------------------------------------
    //bIsCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bIsCurrent();
        xASSERT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //ulGetExitCode
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = pthT->ulGetExitCode();
        xASSERT_LESS_EQ(0UL, m_ulRes);
    }

    //--------------------------------------------------
    //bSetDebugName
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bSetDebugName(xT("Thread_Test_Name"));
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }


    //-------------------------------------
    //static

    //-------------------------------------
    //hOpen
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            m_hRes = CxThread::hOpen(THREAD_ALL_ACCESS, FALSE, ::GetCurrentThreadId());
            xASSERT_PTR(m_hRes);
        #endif
    }

    //--------------------------------------------------
    //ulGetCurrId
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = CxThread::ulGetCurrId();
        xASSERT_LESS(0UL, m_ulRes);
    }

    //--------------------------------------------------
    //hGetCurrHandle
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxHandle hRes = CxThread::hGetCurrHandle();
        xASSERT_NOT_EQ(0UL, (ULONG)hRes);
    }


    //--------------------------------------------------
    //non static

    //-------------------------------------
    //bPause, bResume
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bResume();
        xASSERT_NOT_EQ(FALSE, m_bRes);

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
    xTRACEV("ulGetExitCode(): %li", ulRes);

    ///////////////////////////////////::Sleep(1000);


    /****************************************************************************
    *	static
    *
    *****************************************************************************/

    //--------------------------------------------------
    //hOpen
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            THandle hRes = CxThread::hOpen(const ULONG culAccess, const BOOL cbInheritHandle, const ULONG culId);
        #endif
    }

    //--------------------------------------------------
    //ulGetCurrId
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxId idRes = CxThread::ulGetCurrId();
        xASSERT_LESS((ULONG)0, (ULONG)idRes);
    }

    //--------------------------------------------------
    //bIsCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxId aulData[5][2] = {{0}};

        aulData[0][0] = (CxThread::TxId)CxThread::ulGetCurrId();
        aulData[0][1] = (CxThread::TxId)TRUE;

        aulData[1][0] = (CxThread::TxId)((ULONG)CxThread::ulGetCurrId() - 1);
        aulData[1][1] = (CxThread::TxId)FALSE;

        aulData[2][0] = (CxThread::TxId)0;
        aulData[2][1] = (CxThread::TxId)FALSE;

        aulData[3][0] = (CxThread::TxId) - 1;
        aulData[3][1] = (CxThread::TxId)FALSE;

        aulData[4][0] = (CxThread::TxId)- 1;
        aulData[4][1] = (CxThread::TxId)FALSE;

        for (std::size_t i = 0; i < xARRAY_SIZE(aulData); ++ i) {
            const CxThread::TxId culId = aulData[i][0];
            const BOOL          cbRes = (BOOL)(ULONG)aulData[i][1];

            m_bRes = CxThread::bIsCurrent(culId);
            xASSERT_EQ(cbRes, m_bRes);
        }
    }

    //--------------------------------------------------
    //hGetCurrHandle
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxHandle hRes = CxThread::hGetCurrHandle();
        xASSERT_LESS((ULONG)0, (ULONG)hRes);
    }

    //--------------------------------------------------
    //bYield
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxThread::bYield();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bSleep
    xTEST_BLOCK(cullBlockLoops)
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
