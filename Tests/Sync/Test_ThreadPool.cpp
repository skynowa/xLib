/**
 * \file   Test_ThreadPool.cpp
 * \brief  test ThreadPool
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_ThreadPool)
xTEST_UNIT(Test_ThreadPool)
//-------------------------------------------------------------------------------------------------
class PoolThread :
    public Thread
{
public:
    std::size_t    index;

    explicit       PoolThread(cbool_t &isAutoDelete);
    virtual       ~PoolThread();

protected:
    virtual uint_t onRun(void_t *param) xOVERRIDE;
};
//-------------------------------------------------------------------------------------------------
PoolThread::PoolThread(
    cbool_t &a_isAutoDelete
) :
    Thread(a_isAutoDelete),
    index (0U)
{
}
//-------------------------------------------------------------------------------------------------
PoolThread::~PoolThread() {

}
//-------------------------------------------------------------------------------------------------
uint_t
PoolThread::onRun(
    void_t *a_param
)
{
    xUNUSED(a_param);

    Trace() << xT("\n\tPoolThread: start #") << tag();

    uint_t uiRes = 0;

    // bIsCurrent
    bool_t bRv = Thread::isCurrent();
    xTEST_EQ(bRv, true);

    for (std::size_t i = 0; i < 10; ++ i) {
        // interrupt point
        bRv = isTimeToExit();
        xCHECK_DO(bRv, Trace() << xT("\tPoolThread: break") << tag());
        xCHECK_DO(bRv, break);

        // jobs
        {
            Trace() << xT("\t*");

            Thread::currentSleep(50UL);
            Thread::currentYield();
        }
    }

    Trace() << xT("\tPoolThread: end #") << tag();

    return uiRes;
}
//--------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/*virtual*/
bool_t
Test_ThreadPool::unit()
{
    cbool_t isPaused          = true;
    cbool_t isAutoDelete      = true;
    cbool_t isGroupPaused     = true;
    cbool_t isGroupAutoDelete = true;

    ThreadPool<PoolThread> *pool = new ThreadPool<PoolThread>(isPaused, isAutoDelete,
    	isGroupPaused, isGroupAutoDelete);

    {
        cuint_t  stackSize       = 0UL;
        void_t  *param           = xPTR_NULL;
        cuint_t  tasksNum        = 5;
        cuint_t  runningTasksMax = 10U;

        pool->groupCreate(stackSize, xPTR_NULL, param, tasksNum, runningTasksMax);
    }

    pool->groupResume();
    pool->groupPause();
    pool->groupExit(500UL);
    pool->groupKill(500UL);
    pool->groupWait(500UL);

    m_stRv = pool->maxTasks();
    xUNUSED(m_stRv);

    pool->setMaxTasks(10);

    m_stRv = pool->numTasks();
    xUNUSED(m_stRv);

    pool->setNumTasks(10);

    return true;
}
//-------------------------------------------------------------------------------------------------
