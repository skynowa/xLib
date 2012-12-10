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
        virtual uint_t uiOnRun    (void *pData) xOVERRIDE;
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
void
CxTest_CxThread::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const bool cbIsPaused   = true;
    const bool cbAutoDelete = false;


    CWorkThread *pthT = new CWorkThread(cbAutoDelete);
    xTEST_PTR(pthT);

    pthT->m_ulTag = 0;
    ////pthT->vOnExit2  = vOnExitHandle;

    xTEST_CASE("CxThread::vCreate", 1)
    {
        size_t uiParam = 1000;

        pthT->vCreate(cbIsPaused, 0U, &uiParam);

        m_bRv = pthT->bIsPaused();
        xTEST_EQ(cbIsPaused, m_bRv);
    }

    xTEST_CASE("CxThread::flags", cullCaseLoops)
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

    xTEST_CASE("CxThread::messages", cullCaseLoops)
    {
        // TEST: CxThread::messages
        #if xTODO
            m_bRv = pthT->bPostMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRv = pthT->bSendMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRv = pthT->bPostThreadMessage(WM_TEST_MSG_1, 0, 0);
        #endif
    }

    //-------------------------------------
    //priority

    xTEST_CASE("CxThread::vSetPriority CxThread::tpGetPriority", cullCaseLoops)
    {
        const CxThread::ExPriority ctpPriority = CxThread::tpLowest;

        #if   xOS_ENV_WIN
            pthT->vSetPriority(ctpPriority);

            m_iRv = pthT->tpPriority();
            xTEST_EQ((int)ctpPriority, (int)m_iRv);
        #elif xOS_ENV_UNIX
            pthT->vSetPriority(ctpPriority);

            m_iRv = pthT->tpPriority();
            //TODO: xTEST_EQ(ctpPriority, m_iRv);
        #endif
    }

    xTEST_CASE("CxThread::sGetPriorityString", cullCaseLoops)
    {
        // TEST: CxThread::sGetPriorityString
        #if xTODO
            m_sRv = pthT->sGetPriorityString();
            xTEST_EQ(std::tstring_t(xT("Lowest")), m_sRv);
        #endif
    }

    xTEST_CASE("CxThread::vPriorityUp CxThread::vPriorityDown", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            pthT->vPriorityUp();
            pthT->vPriorityDown();
        #elif xOS_ENV_UNIX

        #endif
    }

    xTEST_CASE("CxThread::bIsPriorityBoost", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            m_bRv = pthT->bIsPriorityBoost();
            xTEST_EQ(true, m_bRv);
        #elif xOS_ENV_UNIX

        #endif
    }

    xTEST_CASE("CxThread::vSetPriorityBoost", cullCaseLoops)
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

    xTEST_CASE("CxThread::vSetCpuAffinity", cullCaseLoops)
    {
        for (ulong_t i = 0; i < CxSystemInfo::ulNumOfCpus(); ++ i) {
            pthT->vSetCpuAffinity(i);
        }
    }

    xTEST_CASE("CxThread::vSetCpuIdeal CxThread::ulGetCpuIdeal", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            pthT->vSetCpuIdeal(0);

            m_ulRv = pthT->ulCpuIdeal();
            xTEST_EQ(true, CxSystemInfo::ulNumOfCpus() > m_ulRv);
        #elif xOS_ENV_UNIX

        #endif
    }

    xTEST_CASE("CxThread::ulGetCpuCount", cullCaseLoops)
    {
        m_ulRv = CxThread::ulCpuCount();
        xTEST_LESS(0UL, m_ulRv);
    }

    //-------------------------------------
    // other

    xTEST_CASE("CxThread::hGet", cullCaseLoops)
    {
        CxThread::handle_t hRv = pthT->hHandle();
        xTEST_DIFF(0UL, (ulong_t)hRv);
    }

    xTEST_CASE("CxThread::ulGetId", cullCaseLoops)
    {
        CxThread::id_t idRes = pthT->ulGetId();
        xTEST_DIFF(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("CxThread::bIsCurrent", cullCaseLoops)
    {
        m_bRv = pthT->bIsCurrent();
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxThread::ulGetExitCode", cullCaseLoops)
    {
        m_ulRv = pthT->ulGetExitStatus();
        // n/a
    }

    xTEST_CASE("CxThread::vSetDebugName", cullCaseLoops)
    {
        pthT->vSetDebugName(xT("CxThread_Test_Name"));
    }

    xTEST_CASE("CxThread::hOpen", cullCaseLoops)
    {
        // TEST: CxThread::hOpen
        #if xTODO
            m_hRv = CxThread::hOpen(THREAD_ALL_ACCESS, false, CxThread::ulGetCurrentId());
            xTEST_PTR(m_hRv);
        #endif
    }

    xTEST_CASE("CxThread::hOpen", cullCaseLoops)
    {
        // TEST: CxThread::hOpen
        #if xTODO
            THandle hRv = CxThread::hOpen(const ulong_t culAccess, const bool cbInheritHandle, const ulong_t culId);
        #endif
    }

    //-------------------------------------
    xTEST_CASE("CxThread::vResume", cullCaseLoops)
    {
        pthT->vResume();

        m_bRv = pthT->bIsPaused();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxThread::vPause", cullCaseLoops)
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

    xTEST_CASE("CxThread::vExit", cullCaseLoops)
    {
        // TEST: CxThread::vExit
        #if xTODO
            m_bRv = pthT->vExit(xTIMEOUT_INFINITE);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    xTEST_CASE("CxThread::vKill", cullCaseLoops)
    {
        // TEST: CxThread::vKill
        #if xTODO
            pthT->vKill(xTIMEOUT_INFINITE);
        #endif
    }

    xTEST_CASE("CxThread::ulGetExitStatus", cullCaseLoops)
    {
        ulong_t ulRv = pthT->ulGetExitStatus();
        xUNUSED(ulRv);
        #if xTEST_IGNORE
            xTRACEV("\tulGetExitStatus(): %lu", ulRv);
        #endif
    }

    xTEST_CASE("CxThread::ulGetExitStatus", 1)
    {
        pthT->vWait(xTIMEOUT_INFINITE);
    }

    if (false == cbAutoDelete) {
        xTEST_PTR(pthT);
        xPTR_DELETE(pthT);
    }
}
//---------------------------------------------------------------------------
