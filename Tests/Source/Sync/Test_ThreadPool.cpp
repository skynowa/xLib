/**
 * \file   Test_ThreadPool.cpp
 * \brief  test ThreadPool
 */


#include <Test/Sync/Test_ThreadPool.h>

#include <xLib/Sync/Thread.h>

//-------------------------------------------------------------------------------------------------
/*virtual*/
void_t
Test_ThreadPool::unit(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

    cbool_t cbIsPaused            = true;
    cbool_t cbIsAutoDelete        = true;
    cbool_t cbIsGroupPaused       = true;
    cbool_t cbIsGroupAutoDelete   = true;

    ThreadPool<CPoolThread> *tpPool = xPTR_NULL;

    {
        tpPool = new ThreadPool<CPoolThread>(
                        cbIsPaused, cbIsAutoDelete,
                        cbIsGroupPaused, cbIsGroupAutoDelete);
        xTEST_PTR(tpPool);
    }

    {
        cuint_t  cuiStackSize       = 0UL;
        void_t         *pvParam            = xPTR_NULL;
        cuint_t  cuiNumTasks        = 5;
        cuint_t  cuiMaxRunningTasks = 10U;

        tpPool->groupCreate(cuiStackSize, xPTR_NULL, pvParam,
                             cuiNumTasks, cuiMaxRunningTasks);
    }

    tpPool->groupResume();
    tpPool->groupPause();
    tpPool->groupExit(500UL);
    tpPool->groupKill(500UL);
    tpPool->groupWait(500UL);

    m_stRv = tpPool->maxTasks();
    xUNUSED(m_stRv);

    tpPool->setMaxTasks(10);

    m_stRv = tpPool->numTasks();
    xUNUSED(m_stRv);

    tpPool->setNumTasks(10);
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    CPoolThread
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
CPoolThread::CPoolThread(
    cbool_t &cbAutoDelete
) :
    Thread (cbAutoDelete),
    index    (0U)
{
}
//-------------------------------------------------------------------------------------------------
CPoolThread::~CPoolThread() {

}
//-------------------------------------------------------------------------------------------------
uint_t
CPoolThread::uiOnRun(
    void_t *pvData
)
{
    xUNUSED(pvData);

    #if xTEST_IGNORE
        xTRACEV(xT("\n\tCWorkThread: start #%lu"), m_ulTag);
    #endif

    uint_t uiRes = 0;

    // bIsCurrent
    bool_t bRv = Thread::isCurrent();
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
//--------------------------------------------------------------------------
