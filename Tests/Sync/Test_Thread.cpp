/**
 * \file   Test_Thread.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Thread)
//-------------------------------------------------------------------------------------------------
class CWorkThread :
    public Thread
{
public:
	size_t index {};

	explicit  CWorkThread(cbool_t isAutoDelete);
	virtual  ~CWorkThread() = default;

protected:
	uint_t onRun(void_t *data) final;
};
//-------------------------------------------------------------------------------------------------
CWorkThread::CWorkThread(
    cbool_t a_isAutoDelete
) :
    Thread(a_isAutoDelete)
{
}
//-------------------------------------------------------------------------------------------------
uint_t
CWorkThread::onRun(
    void_t *data
)
{
    xUNUSED(data);

    #if xTEST_IGNORE
        xTRACEV(xT("\n\tCWorkThread: start #%lu"), index);
    #endif

    uint_t uiRes {};
    bool_t bRv {};

    // isCurrent
    bRv = Thread::isCurrent();
    xTEST(bRv);

    for (size_t i = 0; i < 10; ++ i) {
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

			ThreadCurrent::currentSleep(50UL);
			ThreadCurrent::currentYield();
        }
    }

    #if xTEST_IGNORE
        xTRACEV(xT("\tCWorkThread: end #%lu\n"), index);
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

   auto *pthT = new CWorkThread(cbAutoDelete);

    pthT->setTag(0);
    ////pthT->vOnExit2  = vOnExitHandle;

    cuint_t stackSizeBytes {16384 * 2};
    size_t  uiParam        {1000};
    pthT->create(cbIsPaused, stackSizeBytes, &uiParam);

    xTEST_CASE("create")
    {
        m_bRv = pthT->isPaused();
        xTEST_EQ(cbIsPaused, m_bRv);
    }

    xTEST_CASE("flags")
    {
        m_bRv = pthT->isCreated();
        xTEST(m_bRv);

        m_bRv = pthT->isRunning();
        xTEST(m_bRv);

        m_bRv = pthT->isPaused();
        xTEST_DIFF(m_bRv, false /* cbIsPaused */);

        m_bRv = pthT->isExited();
        xTEST(!m_bRv);
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
        const auto ctpPriority = Thread::Priority::tpLowest;

        #if   xENV_WIN
            pthT->setPriority(ctpPriority);

            const Thread::Priority tpRv = pthT->priority();
            xTEST_EQ((longlong_t)tpRv, (longlong_t)ctpPriority);
        #elif xENV_UNIX
            pthT->setPriority(ctpPriority);

            const Thread::Priority _ctpPriority = pthT->priority();
            // TODO: xTEST_EQ((longlong_t)tpRv, (longlong_t)ctpPriority);
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
            xTEST(m_bRv);
        #elif xENV_UNIX

        #endif
    }

    xTEST_CASE("setPriorityBoost")
    {
        #if   xENV_WIN
            pthT->setPriorityBoost(false);

            m_bRv = pthT->isPriorityBoost();
            xTEST(!m_bRv);

            pthT->setPriorityBoost(true);

            m_bRv = pthT->isPriorityBoost();
            xTEST(m_bRv);
        #elif xENV_UNIX

        #endif
    }

    //-------------------------------------
    // CPU

    xTEST_CASE("setCpuAffinity")
    {
        culong_t num = info::Cpu().num();

        for (ulong_t i = 0; i < num; ++ i) {
            pthT->setCpuAffinity(static_cast<int_t>(i));
        }
    }

    xTEST_CASE("setCpuIdeal, cpuIdeal")
    {
        #if   xENV_WIN
            pthT->setCpuIdeal(0);

            m_ulRv = pthT->cpuIdeal();
            xTEST(info::Cpu().num() > m_ulRv);
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
        xTEST_DIFF(0UL, (ulonglong_t)hRv);
    }

    xTEST_CASE("id")
    {
        Thread::id_t idRes = pthT->id();
        xTEST_DIFF(0UL, (ulonglong_t)idRes);
    }

    xTEST_CASE("isCurrent")
    {
        m_bRv = pthT->isCurrent();
        xTEST(m_bRv);
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
        xTEST(!m_bRv);
    }

    xTEST_CASE("vPause")
    {
		m_bRv = pthT->isPaused();
		xTEST(!m_bRv);

		pthT->pause();

		m_bRv = pthT->isPaused();
		xTEST(m_bRv);

		pthT->resume();

		m_bRv = pthT->isPaused();
		xTEST(!m_bRv);
    }

    xTEST_CASE("exit")
    {
        // TEST: Thread::exit()
        #if xTODO
            m_bRv = pthT->exit(xTIMEOUT_INFINITE);
            xTEST(m_bRv);
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
        Utils::ptrDeleteT(pthT);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
