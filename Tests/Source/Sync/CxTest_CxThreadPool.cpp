/**
 * \file   CxTest_CxThreadPool.cpp
 * \brief  test CxThreadPool
 */


#include <Test/Sync/CxTest_CxThreadPool.h>

#include <xLib/Sync/CxCurrentThread.h>

//---------------------------------------------------------------------------
CxTest_CxThreadPool::CxTest_CxThreadPool() {

}
//---------------------------------------------------------------------------
CxTest_CxThreadPool::~CxTest_CxThreadPool() {

}
//---------------------------------------------------------------------------
/*virtual*/
void
CxTest_CxThreadPool::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const bool cbIsPaused            = true;
    const bool cbIsAutoDelete        = true; 
    const bool cbIsGroupPaused       = true; 
    const bool cbIsGroupAutoDelete   = true;

    CxThreadPool<CPoolThread> *tpPool = NULL;
    
    {
        tpPool = new CxThreadPool<CPoolThread>(
                        cbIsPaused, cbIsAutoDelete, 
                        cbIsGroupPaused, cbIsGroupAutoDelete); 
        xTEST_PTR(tpPool);
    }
    
    {
        const uint_t  cuiStackSize       = 0UL; 
        void         *pvParam            = NULL; 
        const uint_t  cuiNumTasks        = 5; 
        const uint_t  cuiMaxRunningTasks = 10U;

        tpPool->vGroupCreate(cuiStackSize, NULL, pvParam,
                             cuiNumTasks, cuiMaxRunningTasks);
    }

    tpPool->vGroupResume();
    tpPool->vGroupPause();
    tpPool->vGroupExit(500UL);
    tpPool->vGroupKill(500UL);
    tpPool->vGroupWait(500UL);

    tpPool->uiMaxTasks();
    tpPool->vSetMaxTasks (10);

    tpPool->uiNumTasks();
    tpPool->vSetNumTasks (10);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    CPoolThread
*
*****************************************************************************/

//---------------------------------------------------------------------------
CPoolThread::CPoolThread(
    const bool &cbAutoDelete
) :
    CxThread (cbAutoDelete),
    m_uiIndex(0U)
{
}
//---------------------------------------------------------------------------
CPoolThread::~CPoolThread() {

}
//---------------------------------------------------------------------------
uint_t
CPoolThread::uiOnRun(
    void *pvData
)
{
    #if xTEST_IGNORE
        xTRACEV(xT("\n\tCWorkThread: start #%lu"), m_ulTag);
    #endif

    uint_t uiRes = 0;

    // bIsCurrent
    bool bRv = CxThread::bIsCurrent();
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
//--------------------------------------------------------------------------

