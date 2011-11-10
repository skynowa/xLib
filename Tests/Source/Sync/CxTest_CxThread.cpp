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
*    CWorkThread
*
*****************************************************************************/

//---------------------------------------------------------------------------
CWorkThread::CWorkThread(
    const BOOL cbAutoDelete
) :
    CxThread (cbAutoDelete),
    m_uiIndex(0U)
{

}
//---------------------------------------------------------------------------
CWorkThread::~CWorkThread() {

}
//---------------------------------------------------------------------------
UINT
CWorkThread::uiOnRun(
    void *pvData
)
{
    #if xTEST_IGNORE
        xTRACEV(xT("\n\tCWorkThread: start #%li"), m_ulTag);
    #endif

    UINT uiRes = 0;
    BOOL bRes  = FALSE;

    //bIsCurrent
    bRes = CxThread::bIsCurrent();
    xTEST_DIFF(FALSE, bRes);

    for (size_t i = 0; i < 10; ++ i) {
        //interrupt point
        bRes = bIsTimeToExit();
        #if xTEST_IGNORE
            xCHECK_DO(FALSE != bRes, xTRACE(xT("\tCWorkThread: break")));
        #endif
        xCHECK_DO(FALSE != bRes, break);

        //jobs
        {
            #if xTEST_IGNORE
                xTRACE(xT("\t*"));
            #endif

            bRes = CxCurrentThread::bSleep(50UL);
            xTEST_DIFF(FALSE, bRes);

            bRes = CxCurrentThread::bYield();
            xTEST_DIFF(FALSE, bRes);
        }
    }

    #if xTEMP_DISABLED
        CxConsole().bPause();
    #endif

    #if xTEST_IGNORE
        xTRACEV(xT("\tCWorkThread: end #%li\n"), m_ulTag);
    #endif

    return uiRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    CxTest_CxThread
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
    const BOOL cbAutoDelete = FALSE;


    CWorkThread *pthT = new CWorkThread(cbAutoDelete);
    xTEST_PTR(pthT);

    pthT->m_ulTag = 0;
    ////pthT->vOnExit2  = vOnExitHandle;


    //-------------------------------------
    //bCreate
    xTEST_BLOCK(1)
    {
        size_t uiParam = 1000;

        m_bRes = pthT->bCreate(cbIsPaused, 0U, &uiParam);
        xTEST_EQ(TRUE, m_bRes);

        m_bRes = pthT->bIsPaused();
        xTEST_EQ(cbIsPaused, m_bRes);
    }


    //-------------------------------------
    //flags
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bIsCreated();
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = pthT->bIsRunning();
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = pthT->bIsPaused();
        xTEST_DIFF(FALSE/*cbIsPaused*/, m_bRes);

        m_bRes = pthT->bIsExited();
        xTEST_EQ(FALSE, m_bRes);
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
        #if defined(xOS_ENV_UNIX)
            m_bRes = pthT->bSetPriority(CxThread::tpLowest);
            xTEST_EQ(FALSE, m_bRes);

            m_iRes = pthT->tpGetPriority();
            xTEST_EQ((int)0, (int)m_iRes);
        #else
            m_bRes = pthT->bSetPriority(CxThread::tpLowest);
            xTEST_DIFF(FALSE, m_bRes);

            m_iRes = pthT->tpGetPriority();
            xTEST_EQ((int)CxThread::tpLowest, (int)m_iRes);
        #endif
    }

    //-------------------------------------
    //sGetPriorityString
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            m_sRes = pthT->sGetPriorityString();
            xTEST_EQ(std::string_t(xT("Lowest")), m_sRes);
        #endif
    }

    //-------------------------------------
    //bPriorityUp, bPriorityDown
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            m_bRes = pthT->bPriorityUp();
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = pthT->bPriorityDown();
            xTEST_DIFF(FALSE, m_bRes);
        #elif defined(xOS_ENV_UNIX)

        #endif
    }

    //-------------------------------------
    //bIsPriorityBoost
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            m_bRes = pthT->bIsPriorityBoost();
            xTEST_DIFF(FALSE, m_bRes);
        #elif defined(xOS_ENV_UNIX)

        #endif
    }

    //-------------------------------------
    //bSetPriorityBoost
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            m_bRes = pthT->bSetPriorityBoost(FALSE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = pthT->bIsPriorityBoost();
            xTEST_EQ(FALSE, m_bRes);

            m_bRes = pthT->bSetPriorityBoost(TRUE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = pthT->bIsPriorityBoost();
            xTEST_DIFF(FALSE, m_bRes);
        #elif defined(xOS_ENV_UNIX)

        #endif
    }


    //-------------------------------------
    //CPU

    //-------------------------------------
    //bSetCpuAffinity
    xTEST_BLOCK(cullBlockLoops)
    {
        for (size_t i = 0; i < CxSystemInfo::ulGetNumOfCpus(); ++ i) {
            m_bRes = pthT->bSetCpuAffinity(i);
            xTEST_DIFF(FALSE, m_bRes);
        }
    }

    //--------------------------------------------------
    //bSetCpuIdeal, ulGetCpuIdeal
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            m_bRes = pthT->bSetCpuIdeal(0);
            xTEST_DIFF(FALSE, m_bRes);

            m_ulRes = pthT->ulGetCpuIdeal();
            xTEST_LESS_EQ(0UL, m_ulRes);

            m_bRes = pthT->bSetCpuIdeal(10);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = pthT->bSetCpuIdeal(0);
            xTEST_DIFF(FALSE, m_bRes);

            m_ulRes = pthT->ulGetCpuIdeal();
            xTEST_EQ(0UL, m_ulRes);
        #elif defined(xOS_ENV_UNIX)

        #endif
    }

    //--------------------------------------------------
    //ulGetCpuCount
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = CxThread::ulGetCpuCount();
        xTEST_LESS(0UL, m_ulRes);
    }


    //-------------------------------------
    //other

    //-------------------------------------
    //hGet
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxHandle hRes = pthT->hGet();
        xTEST_DIFF(0UL, (ULONG)hRes);
    }

    //--------------------------------------------------
    //ulGetId
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThread::TxId idRes = pthT->ulGetId();
        xTEST_DIFF(0UL, (ULONG)idRes);
    }

    //--------------------------------------------------
    //bIsCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bIsCurrent();
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //ulGetExitCode
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = pthT->ulGetExitStatus();
        xTEST_LESS_EQ(0UL, m_ulRes);
    }

    //--------------------------------------------------
    //bSetDebugName
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bSetDebugName(xT("CxThread_Test_Name"));
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //hOpen
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            m_hRes = CxThread::hOpen(THREAD_ALL_ACCESS, FALSE, CxThread::ulGetCurrentId());
            xTEST_PTR(m_hRes);
        #endif
    }

    //--------------------------------------------------
    //hOpen
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            THandle hRes = CxThread::hOpen(const ULONG culAccess, const BOOL cbInheritHandle, const ULONG culId);
        #endif
    }

    //-------------------------------------
    //bResume (start thread)
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = pthT->bResume();
        xTEST_EQ(TRUE, m_bRes);

        m_bRes = pthT->bIsPaused();
        xTEST_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bPause
    xTEST_BLOCK(cullBlockLoops)
    {
        #if 1
            m_bRes = pthT->bIsPaused();
            xTEST_EQ(FALSE, m_bRes);

            m_bRes = pthT->bPause();
            xTEST_EQ(TRUE, m_bRes);

            m_bRes = pthT->bIsPaused();
            xTEST_EQ(TRUE, m_bRes);

            m_bRes = pthT->bResume();
            xTEST_EQ(TRUE, m_bRes);

            m_bRes = pthT->bIsPaused();
            xTEST_EQ(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //var
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            m_bRes = pthT->bExit(xTIMEOUT_INFINITE);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //var
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            m_uiRes = pthT->uiKill(xTIMEOUT_INFINITE);
            xTEST_EQ(0, m_uiRes);
        #endif
    }

    ULONG ulRes = pthT->ulGetExitStatus();
    xUNUSED(ulRes);
    #if xTEST_IGNORE
        xTRACEV("\tulGetExitStatus(): %li", ulRes);
    #endif

    m_bRes = pthT->bWait(xTIMEOUT_INFINITE);
    xTEST_DIFF(FALSE, m_bRes);

    if (FALSE == cbAutoDelete) {
        xTEST_PTR(pthT);
        xPTR_DELETE(pthT);
    }

    ////CxConsole().bPause();

    return TRUE;
}
//---------------------------------------------------------------------------
