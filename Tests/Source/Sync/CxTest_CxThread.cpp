/**
 * \file   CxTest_CxThread.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxThread.h>

#include <xLib/Core/CxDateTime.h>
#include <xLib/System/CxSystemInfo.h>


/*******************************************************************************
*    CWorkThread
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
class CWorkThread :
    public CxThread
{
    public:
        size_t         m_uiIndex;

                       CWorkThread(cbool_t &cbAutoDelete);
        virtual       ~CWorkThread();

    protected:
        virtual uint_t onRun      (void_t *pData) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
CWorkThread::CWorkThread(
    cbool_t &cbAutoDelete
) :
    CxThread (cbAutoDelete),
    m_uiIndex(0U)
{

}
//-------------------------------------------------------------------------------------------------
CWorkThread::~CWorkThread() {

}
//-------------------------------------------------------------------------------------------------
uint_t
CWorkThread::onRun(
    void_t *pvData
)
{
    xUNUSED(pvData);

    #if xTEST_IGNORE
        xTRACEV(xT("\n\tCWorkThread: start #%lu"), m_ulTag);
    #endif

    uint_t uiRes = 0;
    bool_t   bRv   = false;

    // isCurrent
    bRv = CxThread::isCurrent();
    xTEST_EQ(true, bRv);

    for (size_t i = 0; i < 10; ++ i) {
        // interrupt point
        bRv = isTimeToExit();
        #if xTEST_IGNORE
            xCHECK_DO(bRv, xTRACE(xT("\tCWorkThread: break")));
        #endif
        xCHECK_DO(bRv, break);

        // jobs
        {
            #if xTEST_IGNORE
                xTRACE(xT("\t*"));
            #endif

            CxThread::currentSleep(50UL);
            CxThread::currentYield();
        }
    }

    #if xTEST_IGNORE
        xTRACEV(xT("\tCWorkThread: end #%lu\n"), m_ulTag);
    #endif

    return uiRes;
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    CxTest_CxThread
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxThread::unit(
    culonglong_t &a_caseLoops
)
{
    cbool_t cbIsPaused   = true;
    cbool_t cbAutoDelete = false;


    CWorkThread *pthT = new CWorkThread(cbAutoDelete);

    pthT->tag = 0;
    ////pthT->vOnExit2  = vOnExitHandle;

    xTEST_CASE("CxThread::create", 1)
    {
        size_t uiParam = 1000;

        pthT->create(cbIsPaused, 0U, &uiParam);

        m_bRv = pthT->isPaused();
        xTEST_EQ(cbIsPaused, m_bRv);
    }

    xTEST_CASE("CxThread::flags", a_caseLoops)
    {
        m_bRv = pthT->isCreated();
        xTEST_EQ(true, m_bRv);

        m_bRv = pthT->isRunning();
        xTEST_EQ(true, m_bRv);

        m_bRv = pthT->isPaused();
        xTEST_DIFF(false/*cbIsPaused*/, m_bRv);

        m_bRv = pthT->isExited();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxThread::messages", a_caseLoops)
    {
        // TEST: CxThread::messages
        #if xTODO
            m_bRv = pthT->postMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRv = pthT->sendMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRv = pthT->postThreadMessage(WM_TEST_MSG_1, 0, 0);
        #endif
    }

    //-------------------------------------
    //priority

    xTEST_CASE("CxThread::vSetPriority CxThread::tpGetPriority", a_caseLoops)
    {
        const CxThread::ExPriority ctpPriority = CxThread::tpLowest;

        #if   xOS_ENV_WIN
            pthT->setPriority(ctpPriority);

            m_iRv = pthT->priority();
            xTEST_EQ((int_t)ctpPriority, (int_t)m_iRv);
        #elif xOS_ENV_UNIX
            pthT->setPriority(ctpPriority);

            m_iRv = pthT->priority();
            //TODO: xTEST_EQ(ctpPriority, m_iRv);
        #endif
    }

    xTEST_CASE("CxThread::priorityString", a_caseLoops)
    {
        // TEST: CxThread::priorityString
        #if xTODO
            m_sRv = pthT->priorityString();
            xTEST_EQ(std::tstring_t(xT("Lowest")), m_sRv);
        #endif
    }

    xTEST_CASE("CxThread::priorityUp CxThread::priorityDown", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            pthT->priorityUp();
            pthT->priorityDown();
        #elif xOS_ENV_UNIX

        #endif
    }

    xTEST_CASE("CxThread::isPriorityBoost", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            m_bRv = pthT->isPriorityBoost();
            xTEST_EQ(true, m_bRv);
        #elif xOS_ENV_UNIX

        #endif
    }

    xTEST_CASE("CxThread::setPriorityBoost", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            pthT->setPriorityBoost(false);

            m_bRv = pthT->isPriorityBoost();
            xTEST_EQ(false, m_bRv);

            pthT->setPriorityBoost(true);

            m_bRv = pthT->isPriorityBoost();
            xTEST_EQ(true, m_bRv);
        #elif xOS_ENV_UNIX

        #endif
    }

    //-------------------------------------
    // CPU

    xTEST_CASE("CxThread::setCpuAffinity", a_caseLoops)
    {
        for (ulong_t i = 0; i < CxSystemInfo().numOfCpus(); ++ i) {
            pthT->setCpuAffinity(static_cast<int_t>(i));
        }
    }

    xTEST_CASE("CxThread::setCpuIdeal CxThread::cpuIdeal", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            pthT->setCpuIdeal(0);

            m_ulRv = pthT->cpuIdeal();
            xTEST_EQ(true, CxSystemInfo().numOfCpus() > m_ulRv);
        #elif xOS_ENV_UNIX

        #endif
    }

    xTEST_CASE("CxThread::cpuCount", a_caseLoops)
    {
        m_ulRv = CxThread::cpuCount();
        xTEST_LESS(0UL, m_ulRv);
    }

    //-------------------------------------
    // other

    xTEST_CASE("CxThread::handle", a_caseLoops)
    {
        CxThread::handle_t hRv = pthT->handle();
        xTEST_DIFF(0UL, (ulong_t)hRv);
    }

    xTEST_CASE("CxThread::id", a_caseLoops)
    {
        CxThread::id_t idRes = pthT->id();
        xTEST_DIFF(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("CxThread::isCurrent", a_caseLoops)
    {
        m_bRv = pthT->isCurrent();
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxThread::exitStatus", a_caseLoops)
    {
        m_ulRv = pthT->exitStatus();
        // n/a
    }

    xTEST_CASE("CxThread::setDebugName", a_caseLoops)
    {
        pthT->setDebugName(xT("CxThread_Test_Name"));
    }

    xTEST_CASE("CxThread::open", a_caseLoops)
    {
        // TEST: CxThread::open
        #if xTODO
            m_hRv = CxThread::open(THREAD_ALL_ACCESS, false, CxThread::ulGetCurrentId());
            xTEST_PTR(m_hRv);
        #endif
    }

    xTEST_CASE("CxThread::open", a_caseLoops)
    {
        // TEST: CxThread::open
        #if xTODO
            THandle hRv = CxThread::open(culong_t culAccess, cbool_t cbInheritHandle, culong_t culId);
        #endif
    }

    //-------------------------------------
    xTEST_CASE("CxThread::resume", a_caseLoops)
    {
        pthT->resume();

        m_bRv = pthT->isPaused();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxThread::vPause", a_caseLoops)
    {
        #if 1
            m_bRv = pthT->isPaused();
            xTEST_EQ(false, m_bRv);

            pthT->pause();

            m_bRv = pthT->isPaused();
            xTEST_EQ(true, m_bRv);

            pthT->resume();

            m_bRv = pthT->isPaused();
            xTEST_EQ(false, m_bRv);
        #endif
    }

    xTEST_CASE("CxThread::exit", a_caseLoops)
    {
        // TEST: CxThread::exit
        #if xTODO
            m_bRv = pthT->exit(xTIMEOUT_INFINITE);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    xTEST_CASE("CxThread::kill", a_caseLoops)
    {
        // TEST: CxThread::kill
        #if xTODO
            pthT->kill(xTIMEOUT_INFINITE);
        #endif
    }

    xTEST_CASE("CxThread::exitStatus", a_caseLoops)
    {
        ulong_t ulRv = pthT->exitStatus();
        xUNUSED(ulRv);
        #if xTEST_IGNORE
            xTRACEV("\tulGetExitStatus(): %lu", ulRv);
        #endif
    }

    xTEST_CASE("CxThread::exitStatus", 1)
    {
    #if xTODO
        pthT->wait(xTIMEOUT_INFINITE);
    #endif
    }

    if (!cbAutoDelete) {
        xTEST_PTR(pthT);
        xPTR_DELETE(pthT);
    }

    unit1(a_caseLoops);
}
//-------------------------------------------------------------------------------------------------
void_t
CxTest_CxThread::unit1(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxThread::isCurrent", a_caseLoops)
    {
        CxThread::id_t aulData[5][2] = {{0}};

        aulData[0][0] = (CxThread::id_t)CxThread::currentId();
        aulData[0][1] = (CxThread::id_t)true;

        aulData[1][0] = (CxThread::id_t)((ulong_t)CxThread::currentId() - 1);
        aulData[1][1] = (CxThread::id_t)false;

        aulData[2][0] = (CxThread::id_t)0;
        aulData[2][1] = (CxThread::id_t)false;

        aulData[3][0] = (CxThread::id_t) - 1;
        aulData[3][1] = (CxThread::id_t)false;

        aulData[4][0] = (CxThread::id_t)- 1;
        aulData[4][1] = (CxThread::id_t)false;

        for (std::size_t i = 0; i < xARRAY_SIZE(aulData); ++ i) {
            const CxThread::id_t culId = aulData[i][0];
            cbool_t           cbRes = xINT_TO_BOOL( (ulong_t)aulData[i][1] );

            m_bRv = CxThread::isCurrent(culId);
            xTEST_EQ(cbRes, m_bRv);
        }
    }

    xTEST_CASE("CxThread::currentId", a_caseLoops)
    {
        CxThread::id_t idRes = CxThread::currentId();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("CxThread::handle", a_caseLoops)
    {
        CxThread::handle_t hRv = CxThread::currentHandle();
        xTEST_DIFF(0UL, (ulong_t)hRv);
    }

    xTEST_CASE("CxThread::id", a_caseLoops)
    {
        CxThread::id_t idRes = CxThread::currentId();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("CxThread::handle", a_caseLoops)
    {
        CxThread::handle_t hRv = CxThread::currentHandle();
        xTEST_LESS((ulong_t)0, (ulong_t)hRv);
    }

    xTEST_CASE("CxThread::yield", a_caseLoops)
    {
        CxThread::currentYield();
    }

    xTEST_CASE("CxThread::sleep", a_caseLoops)
    {
        culong_t caulData[] = {
            0,
            1
            // ULONG_MIN,
            // ULONG_MAX
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t cuiMsec = caulData[i];

            CxDateTime dtTime1;

            dtTime1 = CxDateTime::current();

            CxThread::currentSleep(cuiMsec);

            CxDateTime dtTime2;

            dtTime2 = CxDateTime::current();

            xTEST_GR_EQ(dtTime2.toMsec(), dtTime1.toMsec());
            // xTRACEV(xT("sNow1: %s,\nsNow2: %s"), dtTime1.sormat(CxDateTime::ftTime).c_str(),
            //    dtTime2.format(CxDateTime::ftTime).c_str());
        }
    }
}
//-------------------------------------------------------------------------------------------------
