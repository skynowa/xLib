/**
 * \file   Test_Thread.cpp
 * \brief
 */


#include <Test/Sync/Test_Thread.h>

#include <xLib/Core/DateTime.h>
#include <xLib/System/SystemInfo.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Thread)
//-------------------------------------------------------------------------------------------------

/*******************************************************************************
*    CWorkThread
*
*******************************************************************************/

class CWorkThread :
    public Thread
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
    Thread (cbAutoDelete),
    m_uiIndex(0U)
{
}
//-------------------------------------------------------------------------------------------------
CWorkThread::~CWorkThread()
{
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
    bRv = Thread::isCurrent();
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

            Thread::currentSleep(50UL);
            Thread::currentYield();
        }
    }

    #if xTEST_IGNORE
        xTRACEV(xT("\tCWorkThread: end #%lu\n"), m_ulTag);
    #endif

    return uiRes;
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    Test_Thread
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Thread::unit()
{
    cbool_t cbIsPaused   = true;
    cbool_t cbAutoDelete = false;

    CWorkThread *pthT = new CWorkThread(cbAutoDelete);

    pthT->setTag(0);
    ////pthT->vOnExit2  = vOnExitHandle;

    size_t uiParam = 1000;
    pthT->create(cbIsPaused, 0U, &uiParam);

    xTEST_CASE("create")
    {
        m_bRv = pthT->isPaused();
        xTEST_EQ(cbIsPaused, m_bRv);
    }

    xTEST_CASE("flags")
    {
        m_bRv = pthT->isCreated();
        xTEST_EQ(m_bRv, true);

        m_bRv = pthT->isRunning();
        xTEST_EQ(m_bRv, true);

        m_bRv = pthT->isPaused();
        xTEST_DIFF(m_bRv, false /* cbIsPaused */);

        m_bRv = pthT->isExited();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("messages")
    {
        // TEST: Thread::messages()
        #if xTODO
            m_bRv = pthT->postMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRv = pthT->sendMessage(::GetDesktopWindow(), WM_CHAR, 0, 0);
            m_bRv = pthT->postThreadMessage(WM_TEST_MSG_1, 0, 0);
        #endif
    }

    //-------------------------------------
    //priority

    xTEST_CASE("vSetPriority, tpGetPriority")
    {
        const Thread::ExPriority ctpPriority = Thread::tpLowest;

        #if   xENV_WIN
            pthT->setPriority(ctpPriority);

            m_iRv = pthT->priority();
            xTEST_EQ((int_t)ctpPriority, (int_t)m_iRv);
        #elif xENV_UNIX
            pthT->setPriority(ctpPriority);

            m_iRv = pthT->priority();
            //TODO: xTEST_EQ(ctpPriority, m_iRv);
        #endif
    }

    xTEST_CASE("priorityString")
    {
        // TEST: Thread::priorityString()
        #if xTODO
            m_sRv = pthT->priorityString();
            xTEST_EQ(std::tstring_t(xT("Lowest")), m_sRv);
        #endif
    }

    xTEST_CASE("priorityUp, priorityDown")
    {
        #if   xENV_WIN
            pthT->priorityUp();
            pthT->priorityDown();
        #elif xENV_UNIX

        #endif
    }

    xTEST_CASE("isPriorityBoost")
    {
        #if   xENV_WIN
            m_bRv = pthT->isPriorityBoost();
            xTEST_EQ(m_bRv, true);
        #elif xENV_UNIX

        #endif
    }

    xTEST_CASE("setPriorityBoost")
    {
        #if   xENV_WIN
            pthT->setPriorityBoost(false);

            m_bRv = pthT->isPriorityBoost();
            xTEST_EQ(m_bRv, false);

            pthT->setPriorityBoost(true);

            m_bRv = pthT->isPriorityBoost();
            xTEST_EQ(m_bRv, true);
        #elif xENV_UNIX

        #endif
    }

    //-------------------------------------
    // CPU

    xTEST_CASE("setCpuAffinity")
    {
        for (ulong_t i = 0; i < SystemInfo().numOfCpus(); ++ i) {
            pthT->setCpuAffinity(static_cast<int_t>(i));
        }
    }

    xTEST_CASE("setCpuIdeal, cpuIdeal")
    {
        #if   xENV_WIN
            pthT->setCpuIdeal(0);

            m_ulRv = pthT->cpuIdeal();
            xTEST_EQ(true, SystemInfo().numOfCpus() > m_ulRv);
        #elif xENV_UNIX

        #endif
    }

    xTEST_CASE("cpuCount")
    {
        m_ulRv = Thread::cpuCount();
        xTEST_LESS(0UL, m_ulRv);
    }

    //-------------------------------------
    // other

    xTEST_CASE("handle")
    {
        Thread::handle_t hRv = pthT->handle();
        xTEST_DIFF(0UL, (ulong_t)hRv);
    }

    xTEST_CASE("id")
    {
        Thread::id_t idRes = pthT->id();
        xTEST_DIFF(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("isCurrent")
    {
        m_bRv = pthT->isCurrent();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("exitStatus")
    {
        m_ulRv = pthT->exitStatus();
        // n/a
    }

    xTEST_CASE("setDebugName")
    {
        pthT->setDebugName(xT("Thread_Test_Name"));
    }

    xTEST_CASE("open")
    {
        // TEST: Thread::open()
        #if xTODO
            m_hRv = Thread::open(THREAD_ALL_ACCESS, false, Thread::ulGetCurrentId());
            xTEST_PTR(m_hRv);
        #endif
    }

    xTEST_CASE("open")
    {
        // TEST: Thread::open()
        #if xTODO
            THandle hRv = Thread::open(culong_t culAccess, cbool_t cbInheritHandle, culong_t culId);
        #endif
    }

    //-------------------------------------
    xTEST_CASE("resume")
    {
        pthT->resume();

        m_bRv = pthT->isPaused();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("vPause")
    {
        #if 1
            m_bRv = pthT->isPaused();
            xTEST_EQ(m_bRv, false);

            pthT->pause();

            m_bRv = pthT->isPaused();
            xTEST_EQ(m_bRv, true);

            pthT->resume();

            m_bRv = pthT->isPaused();
            xTEST_EQ(m_bRv, false);
        #endif
    }

    xTEST_CASE("exit")
    {
        // TEST: Thread::exit()
        #if xTODO
            m_bRv = pthT->exit(xTIMEOUT_INFINITE);
            xTEST_EQ(m_bRv, true);
        #endif
    }

    xTEST_CASE("kill")
    {
        // TEST: Thread::kill()
        #if xTODO
            pthT->kill(xTIMEOUT_INFINITE);
        #endif
    }

    xTEST_CASE("exitStatus")
    {
        ulong_t ulRv = pthT->exitStatus();
        xUNUSED(ulRv);
        #if xTEST_IGNORE
            xTRACEV("\tulGetExitStatus(): %lu", ulRv);
        #endif
    }

    xTEST_CASE("exitStatus")
    {
    #if xTODO
        pthT->wait(xTIMEOUT_INFINITE);
    #endif
    }

    if (!cbAutoDelete) {
        xTEST_PTR(pthT);
        xPTR_DELETE(pthT);
    }

    unit1();
}
//-------------------------------------------------------------------------------------------------
void_t
Test_Thread::unit1()
{
    xTEST_CASE("isCurrent")
    {
        Thread::id_t aulData[5][2] = {{0}};

        aulData[0][0] = (Thread::id_t)Thread::currentId();
        aulData[0][1] = (Thread::id_t)true;

        aulData[1][0] = (Thread::id_t)((ulong_t)Thread::currentId() - 1);
        aulData[1][1] = (Thread::id_t)false;

        aulData[2][0] = (Thread::id_t)0;
        aulData[2][1] = (Thread::id_t)false;

        aulData[3][0] = (Thread::id_t) - 1;
        aulData[3][1] = (Thread::id_t)false;

        aulData[4][0] = (Thread::id_t)- 1;
        aulData[4][1] = (Thread::id_t)false;

        for (std::size_t i = 0; i < xARRAY_SIZE(aulData); ++ i) {
            const Thread::id_t culId = aulData[i][0];
            cbool_t           cbRes = xINT_TO_BOOL( (ulong_t)aulData[i][1] );

            m_bRv = Thread::isCurrent(culId);
            xTEST_EQ(cbRes, m_bRv);
        }
    }

    xTEST_CASE("currentId")
    {
        Thread::id_t idRes = Thread::currentId();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("handle")
    {
        Thread::handle_t hRv = Thread::currentHandle();
        xTEST_DIFF(0UL, (ulong_t)hRv);
    }

    xTEST_CASE("id")
    {
        Thread::id_t idRes = Thread::currentId();
        xTEST_LESS(0UL, (ulong_t)idRes);
    }

    xTEST_CASE("handle")
    {
        Thread::handle_t hRv = Thread::currentHandle();
        xTEST_LESS((ulong_t)0, (ulong_t)hRv);
    }

    xTEST_CASE("yield")
    {
        Thread::currentYield();
    }

    xTEST_CASE("sleep")
    {
        culong_t caulData[] = {
            0,
            1
            // ULONG_MIN,
            // ULONG_MAX
        };

        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            culong_t cuiMsec = caulData[i];

            DateTime dtTime1;

            dtTime1 = DateTime::current();

            Thread::currentSleep(cuiMsec);

            DateTime dtTime2;

            dtTime2 = DateTime::current();

            xTEST_GR_EQ(dtTime2.toMsec(), dtTime1.toMsec());
            // xTRACEV(xT("sNow1: %s,\nsNow2: %s"), dtTime1.sormat(DateTime::ftTime).c_str(),
            //    dtTime2.format(DateTime::ftTime).c_str());
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
