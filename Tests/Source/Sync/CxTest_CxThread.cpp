/**
 * \file   CxTest_CxThread.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxThread.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Common/CxSystemInfo.h>


/****************************************************************************
*    CWorkThread
*
*****************************************************************************/

//---------------------------------------------------------------------------
class CWorkThread :
    public CxThread
{
    public:
        size_t         m_uiIndex;

                       CWorkThread(const bool &cbAutoDelete);
        virtual       ~CWorkThread();

    protected:
        virtual uint_t uiOnRun    (void *pData);
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
CWorkThread::CWorkThread(
    const bool &cbAutoDelete
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
    bool   bRv   = false;

    // bIsCurrent
    bRv = CxThread::bIsCurrent();
    xTEST_EQ(true, bRv);

    for (size_t i = 0; i < 10; ++ i) {
        // interrupt point
        bRv = bIsTimeToExit();
        #if xTEST_IGNORE
            xCHECK_DO(true == bRv, xTRACE(xT("\tCWorkThread: break")));
        #endif
        xCHECK_DO(true == bRv, break);

        // jobs
        {
            #if xTEST_IGNORE
                xTRACE(xT("\t*"));
            #endif

            CxCurrentThread::vSleep(50UL);
            CxCurrentThread::vYield();
        }
    }

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
/* virtual */
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
    // bCreate
    xTEST_CASE(1)
    {
        size_t uiParam = 1000;

        pthT->vCreate(cbIsPaused, 0U, &uiParam);

        m_bRv = pthT->bIsPaused();
        xTEST_EQ(cbIsPaused, m_bRv);
    }

    //-------------------------------------
    // flags
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = pthT->bIsCreated();
        xTEST_EQ(true, m_bRv);

        m_bRv = pthT->bIsRunning();
        xTEST_EQ(true, m_bRv);

        m_bRv = pthT->bIsPaused();
        xTEST_DIFF(false/*cbIsPaused*/, m_bRv);

        m_bRv = pthT->bIsExited();
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    // messages
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_bRv = pthT->bPostMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRv = pthT->bSendMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRv = pthT->bPostThreadMessage(WM_TEST_MSG_1, 0, 0);
        #endif
    }

    //-------------------------------------
    //priority


    //-------------------------------------
    // bSetPriority, tpGetPriority
    xTEST_CASE(cullCaseLoops)
    {
        const CxThread::ExPriority ctpPriority = CxThread::tpLowest;

        #if   xOS_ENV_WIN
            pthT->vSetPriority(ctpPriority);

            m_iRv = pthT->tpGetPriority();
            xTEST_EQ((int)ctpPriority, (int)m_iRv);
        #elif xOS_ENV_UNIX
            pthT->vSetPriority(ctpPriority);

            m_iRv = pthT->tpGetPriority();
            //TODO: xTEST_EQ(ctpPriority, m_iRv);
        #endif
    }

    //-------------------------------------
    // sGetPriorityString
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_sRv = pthT->sGetPriorityString();
            xTEST_EQ(std::tstring_t(xT("Lowest")), m_sRv);
        #endif
    }

    //-------------------------------------
    // bPriorityUp, bPriorityDown
    xTEST_CASE(cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            pthT->vPriorityUp();
            pthT->vPriorityDown();
        #elif xOS_ENV_UNIX

        #endif
    }

    //-------------------------------------
    // bIsPriorityBoost
    xTEST_CASE(cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            m_bRv = pthT->bIsPriorityBoost();
            xTEST_EQ(true, m_bRv);
        #elif xOS_ENV_UNIX

        #endif
    }

    //-------------------------------------
    // bSetPriorityBoost
    xTEST_CASE(cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            pthT->vSetPriorityBoost(false);

            m_bRv = pthT->bIsPriorityBoost();
            xTEST_EQ(false, m_bRv);

            pthT->vSetPriorityBoost(true);

            m_bRv = pthT->bIsPriorityBoost();
            xTEST_EQ(true, m_bRv);
        #elif xOS_ENV_UNIX

        #endif
    }

    //-------------------------------------
    // CPU


    //-------------------------------------
    // bSetCpuAffinity
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < CxSystemInfo::ulGetNumOfCpus(); ++ i) {
            pthT->vSetCpuAffinity(i);
        }
    }

    //--------------------------------------------------
    //bSetCpuIdeal, ulGetCpuIdeal
    xTEST_CASE(cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            pthT->vSetCpuIdeal(0);

            m_ulRv = pthT->ulGetCpuIdeal();
            xTEST_EQ(true, CxSystemInfo::ulGetNumOfCpus() > m_ulRv);
        #elif xOS_ENV_UNIX

        #endif
    }

    //--------------------------------------------------
    // ulGetCpuCount
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRv = CxThread::ulGetCpuCount();
        xTEST_LESS(0UL, m_ulRv);
    }

    //-------------------------------------
    // other


    //-------------------------------------
    // hGet
    xTEST_CASE(cullCaseLoops)
    {
        CxThread::handle_t hRv = pthT->hGet();
        xTEST_DIFF(0UL, (ulong_t)hRv);
    }

    //--------------------------------------------------
    // ulGetId
    xTEST_CASE(cullCaseLoops)
    {
        CxThread::id_t idRes = pthT->ulGetId();
        xTEST_DIFF(0UL, (ulong_t)idRes);
    }

    //--------------------------------------------------
    // bIsCurrent
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = pthT->bIsCurrent();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    // ulGetExitCode
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRv = pthT->ulGetExitStatus();
        // n/a
    }

    //--------------------------------------------------
    // bSetDebugName
    xTEST_CASE(cullCaseLoops)
    {
        pthT->vSetDebugName(xT("CxThread_Test_Name"));
    }

    //-------------------------------------
    // hOpen
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_hRv = CxThread::hOpen(THREAD_ALL_ACCESS, false, CxThread::ulGetCurrentId());
            xTEST_PTR(m_hRv);
        #endif
    }

    //--------------------------------------------------
    // hOpen
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            THandle hRv = CxThread::hOpen(const ulong_t culAccess, const bool cbInheritHandle, const ulong_t culId);
        #endif
    }

    //-------------------------------------
    // bResume (start thread)
    xTEST_CASE(cullCaseLoops)
    {
        pthT->vResume();

        m_bRv = pthT->bIsPaused();
        xTEST_EQ(false, m_bRv);
    }

    //-------------------------------------
    // bPause
    xTEST_CASE(cullCaseLoops)
    {
        #if 1
            m_bRv = pthT->bIsPaused();
            xTEST_EQ(false, m_bRv);

            pthT->vPause();

            m_bRv = pthT->bIsPaused();
            xTEST_EQ(true, m_bRv);

            pthT->vResume();

            m_bRv = pthT->bIsPaused();
            xTEST_EQ(false, m_bRv);
        #endif
    }

    //--------------------------------------------------
    // var
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_bRv = pthT->bExit(xTIMEOUT_INFINITE);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    // var
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            m_uiRv = pthT->uiKill(xTIMEOUT_INFINITE);
            xTEST_EQ(0, m_uiRv);
        #endif
    }

    ulong_t ulRv = pthT->ulGetExitStatus();
    xUNUSED(ulRv);
    #if xTEST_IGNORE
        xTRACEV("\tulGetExitStatus(): %lu", ulRv);
    #endif

    pthT->vWait(xTIMEOUT_INFINITE);

    if (false == cbAutoDelete) {
        xTEST_PTR(pthT);
        xPTR_DELETE(pthT);
    }

    return true;
}
//---------------------------------------------------------------------------
