/**
 * \file   CxTest_CxThread.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxThread.h>

#include <xLib/Common/CxDateTime.h>


/****************************************************************************
*    CWorkThread
*
*****************************************************************************/

//---------------------------------------------------------------------------
CWorkThread::CWorkThread(
    const bool cbAutoDelete
) :
    CxThread (cbAutoDelete),
    m_uiIndex(0U)
{

}
//---------------------------------------------------------------------------
CWorkThread::~CWorkThread() {

}
//---------------------------------------------------------------------------
uint_t
CWorkThread::uiOnRun(
    void *pvData
)
{
    #if xTEST_IGNORE
        xTRACEV(xT("\n\tCWorkThread: start #%lu"), m_ulTag);
    #endif

    uint_t uiRes = 0;
    bool bRes  = false;

    //bIsCurrent
    bRes = CxThread::bIsCurrent();
    xTEST_EQ(true, bRes);

    for (size_t i = 0; i < 10; ++ i) {
        //interrupt point
        bRes = bIsTimeToExit();
        #if xTEST_IGNORE
            xCHECK_DO(false != bRes, xTRACE(xT("\tCWorkThread: break")));
        #endif
        xCHECK_DO(false != bRes, break);

        //jobs
        {
            #if xTEST_IGNORE
                xTRACE(xT("\t*"));
            #endif

            bRes = CxCurrentThread::bSleep(50UL);
            xTEST_EQ(true, bRes);

            bRes = CxCurrentThread::bYield();
            xTEST_EQ(true, bRes);
        }
    }

    #if xTEMP_DISABLED
        CxConsole().bPause();
    #endif

    #if xTEST_IGNORE
        xTRACEV(xT("\tCWorkThread: end #%lu\n"), m_ulTag);
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
bool
CxTest_CxThread::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const bool cbIsPaused   = true;
    const bool cbAutoDelete = false;


    CWorkThread *pthT = new CWorkThread(cbAutoDelete);
    xTEST_PTR(pthT);

    pthT->m_ulTag = 0;
    ////pthT->vOnExit2  = vOnExitHandle;


    //-------------------------------------
    //bCreate
    xTEST_CASE(1)
    {
        size_t uiParam = 1000;

        m_bRes = pthT->bCreate(cbIsPaused, 0U, &uiParam);
        xTEST_EQ(true, m_bRes);

        m_bRes = pthT->bIsPaused();
        xTEST_EQ(cbIsPaused, m_bRes);
    }


    //-------------------------------------
    //flags
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = pthT->bIsCreated();
        xTEST_EQ(true, m_bRes);

        m_bRes = pthT->bIsRunning();
        xTEST_EQ(true, m_bRes);

        m_bRes = pthT->bIsPaused();
        xTEST_DIFF(false/*cbIsPaused*/, m_bRes);

        m_bRes = pthT->bIsExited();
        xTEST_EQ(false, m_bRes);
    }


    //-------------------------------------
    //messages
    xTEST_CASE(cullCaseLoops)
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
    xTEST_CASE(cullCaseLoops)
    {
        const CxThread::EPriority ctpPriority = CxThread::tpLowest;

        #if xOS_ENV_WIN
            m_bRes = pthT->bSetPriority(ctpPriority);
            xTEST_EQ(true, m_bRes);

            m_iRes = pthT->tpGetPriority();
            xTEST_EQ((int)ctpPriority, (int)m_iRes);
        #elif xOS_ENV_UNIX
            m_bRes = pthT->bSetPriority(ctpPriority);
            //TODO: xTEST_EQ(true, m_bRes);

            m_iRes = pthT->tpGetPriority();
            //TODO: xTEST_EQ(ctpPriority, m_iRes);
        #endif
    }

    //-------------------------------------
    //sGetPriorityString
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_sRes = pthT->sGetPriorityString();
            xTEST_EQ(std::tstring_t(xT("Lowest")), m_sRes);
        #endif
    }

    //-------------------------------------
    //bPriorityUp, bPriorityDown
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            m_bRes = pthT->bPriorityUp();
            xTEST_EQ(true, m_bRes);

            m_bRes = pthT->bPriorityDown();
            xTEST_EQ(true, m_bRes);
        #elif xOS_ENV_UNIX

        #endif
    }

    //-------------------------------------
    //bIsPriorityBoost
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            m_bRes = pthT->bIsPriorityBoost();
            xTEST_EQ(true, m_bRes);
        #elif xOS_ENV_UNIX

        #endif
    }

    //-------------------------------------
    //bSetPriorityBoost
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            m_bRes = pthT->bSetPriorityBoost(false);
            xTEST_EQ(true, m_bRes);

            m_bRes = pthT->bIsPriorityBoost();
            xTEST_EQ(false, m_bRes);

            m_bRes = pthT->bSetPriorityBoost(true);
            xTEST_EQ(true, m_bRes);

            m_bRes = pthT->bIsPriorityBoost();
            xTEST_EQ(true, m_bRes);
        #elif xOS_ENV_UNIX

        #endif
    }


    //-------------------------------------
    //CPU

    //-------------------------------------
    //bSetCpuAffinity
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < CxSystemInfo::ulGetNumOfCpus(); ++ i) {
            m_bRes = pthT->bSetCpuAffinity(i);
            xTEST_EQ(true, m_bRes);
        }
    }

    //--------------------------------------------------
    //bSetCpuIdeal, ulGetCpuIdeal
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            m_bRes = pthT->bSetCpuIdeal(0);
            xTEST_EQ(true, m_bRes);

            m_ulRes = pthT->ulGetCpuIdeal();
            xTEST_LESS_EQ(0UL, m_ulRes);

            m_bRes = pthT->bSetCpuIdeal(10);
            xTEST_EQ(true, m_bRes);

            m_bRes = pthT->bSetCpuIdeal(0);
            xTEST_EQ(true, m_bRes);

            m_ulRes = pthT->ulGetCpuIdeal();
            xTEST_EQ(0UL, m_ulRes);
        #elif xOS_ENV_UNIX

        #endif
    }

    //--------------------------------------------------
    //ulGetCpuCount
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxThread::ulGetCpuCount();
        xTEST_LESS(0UL, m_ulRes);
    }


    //-------------------------------------
    //other

    //-------------------------------------
    //hGet
    xTEST_CASE(cullCaseLoops)
    {
        CxThread::TxHandle hRes = pthT->hGet();
        xTEST_DIFF(0UL, (ulong_t)hRes);
    }

    //--------------------------------------------------
    //ulGetId
    xTEST_CASE(cullCaseLoops)
    {
        CxThread::TxId idRes = pthT->ulGetId();
        xTEST_DIFF(0UL, (ulong_t)idRes);
    }

    //--------------------------------------------------
    //bIsCurrent
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = pthT->bIsCurrent();
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //ulGetExitCode
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = pthT->ulGetExitStatus();
        xTEST_LESS_EQ(0UL, m_ulRes);
    }

    //--------------------------------------------------
    //bSetDebugName
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = pthT->bSetDebugName(xT("CxThread_Test_Name"));
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //hOpen
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_hRes = CxThread::hOpen(THREAD_ALL_ACCESS, false, CxThread::ulGetCurrentId());
            xTEST_PTR(m_hRes);
        #endif
    }

    //--------------------------------------------------
    //hOpen
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            THandle hRes = CxThread::hOpen(const ulong_t culAccess, const bool cbInheritHandle, const ulong_t culId);
        #endif
    }

    //-------------------------------------
    //bResume (start thread)
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = pthT->bResume();
        xTEST_EQ(true, m_bRes);

        m_bRes = pthT->bIsPaused();
        xTEST_EQ(false, m_bRes);
    }

    //-------------------------------------
    //bPause
    xTEST_CASE(cullCaseLoops)
    {
        #if 1
            m_bRes = pthT->bIsPaused();
            xTEST_EQ(false, m_bRes);

            m_bRes = pthT->bPause();
            xTEST_EQ(true, m_bRes);

            m_bRes = pthT->bIsPaused();
            xTEST_EQ(true, m_bRes);

            m_bRes = pthT->bResume();
            xTEST_EQ(true, m_bRes);

            m_bRes = pthT->bIsPaused();
            xTEST_EQ(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //var
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_bRes = pthT->bExit(xTIMEOUT_INFINITE);
            xTEST_EQ(true, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //var
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_uiRes = pthT->uiKill(xTIMEOUT_INFINITE);
            xTEST_EQ(0, m_uiRes);
        #endif
    }

    ulong_t ulRes = pthT->ulGetExitStatus();
    xUNUSED(ulRes);
    #if xTEST_IGNORE
        xTRACEV("\tulGetExitStatus(): %lu", ulRes);
    #endif

    m_bRes = pthT->bWait(xTIMEOUT_INFINITE);
    xTEST_EQ(true, m_bRes);

    if (false == cbAutoDelete) {
        xTEST_PTR(pthT);
        xPTR_DELETE(pthT);
    }

    ////CxConsole().bPause();

    return true;
}
//---------------------------------------------------------------------------
