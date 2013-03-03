/**
 * \file   CxTest_CxThreadPool.cpp
 * \brief  test CxThreadPool
 */


#include <Test/Sync/CxTest_CxThreadPool.h>

#include <xLib/Sync/CxCurrentThread.h>

//------------------------------------------------------------------------------
CxTest_CxThreadPool::CxTest_CxThreadPool() {

}
//------------------------------------------------------------------------------
CxTest_CxThreadPool::~CxTest_CxThreadPool() {

}
//------------------------------------------------------------------------------
/*virtual*/
void_t
CxTest_CxThreadPool::unit(
    culonglong_t &cullCaseLoops
)
{
    cbool_t cbIsPaused            = true;
    cbool_t cbIsAutoDelete        = true;
    cbool_t cbIsGroupPaused       = true;
    cbool_t cbIsGroupAutoDelete   = true;

    CxThreadPool<CPoolThread> *tpPool = NULL;

    {
        tpPool = new CxThreadPool<CPoolThread>(
                        cbIsPaused, cbIsAutoDelete,
                        cbIsGroupPaused, cbIsGroupAutoDelete);
        xTEST_PTR(tpPool);
    }

    {
        cuint_t  cuiStackSize       = 0UL;
        void_t         *pvParam            = NULL;
        cuint_t  cuiNumTasks        = 5;
        cuint_t  cuiMaxRunningTasks = 10U;

        tpPool->groupCreate(cuiStackSize, NULL, pvParam,
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
//------------------------------------------------------------------------------


/*******************************************************************************
*    CPoolThread
*
*******************************************************************************/

//------------------------------------------------------------------------------
CPoolThread::CPoolThread(
    cbool_t &cbAutoDelete
) :
    CxThread (cbAutoDelete),
    m_uiIndex(0U)
{
}
//------------------------------------------------------------------------------
CPoolThread::~CPoolThread() {

}
//------------------------------------------------------------------------------
uint_t
CPoolThread::uiOnRun(
    void_t *pvData
)
{
    #if xTEST_IGNORE
        xTRACEV(xT("\n\tCWorkThread: start #%lu"), m_ulTag);
    #endif

    uint_t uiRes = 0;

    // bIsCurrent
    bool_t bRv = CxThread::isCurrent();
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

            CxCurrentThread::sleep(50UL);
            CxCurrentThread::yield();
        }
    }

    #if xTEST_IGNORE
        xTRACEV(xT("\tCWorkThread: end #%lu\n"), m_ulTag);
    #endif

    return uiRes;
}
//--------------------------------------------------------------------------

