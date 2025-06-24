/**
 * \file   Test_ThreadPool.cpp
 * \brief  test ThreadPool
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_ThreadPool)
//-------------------------------------------------------------------------------------------------
namespace
{

std::ctstring_t thread_param = xT("param1");

}
//-------------------------------------------------------------------------------------------------
class PoolThread :
    public Thread
{
public:
    std::size_t index {};

    explicit  PoolThread(cbool_t isAutoDelete);
    virtual  ~PoolThread() = default;

    xNO_DEFAULT_CONSTRUCT(PoolThread);
    xNO_COPY_ASSIGN(PoolThread);

protected:
    uint_t onRun(void_t *param) final;
};
//-------------------------------------------------------------------------------------------------
PoolThread::PoolThread(
    cbool_t a_isAutoDelete
) :
    Thread(a_isAutoDelete)
{
}
//-------------------------------------------------------------------------------------------------
uint_t
PoolThread::onRun(
    void_t *a_param
)
{
    xTEST_PTR(a_param);

    const auto param = *(static_cast<std::tstring_t *>(a_param));
    xTEST_EQ(param, ::thread_param);

    LogCout() << Format::str(xT("\n\tPoolThread: start #{}, param: {}"), tag(), param);

    uint_t uiRes {};

    // bIsCurrent
    bool_t bRv = Thread::isCurrent();
    xTEST(bRv);

    for (std::size_t i {}; i < 10; ++ i) {
        // interrupt point
        bRv = isTimeToExit();
        xCHECK_DO(bRv, LogCout() << xT("\tPoolThread: break") << tag());
        xCHECK_DO(bRv, break);

        // jobs
        {
            LogCout() << xT("\t*");

            ThreadCurrent::currentSleep(50UL);
            ThreadCurrent::currentYield();
        }
    }

    LogCout() << xT("\tPoolThread: end #") << tag();

    return uiRes;
}
//-------------------------------------------------------------------------------------------------
bool_t
Test_ThreadPool::unit()
{
	{
		// TODO: Test_ThreadPool - fix tests
		xTRACE_NOT_IMPLEMENTED
	}

    cbool_t      isPaused          {true};
    cbool_t      isAutoDelete      {true};
    cbool_t      isGroupPaused     {true};
    cbool_t      isGroupAutoDelete {true};
    std::csize_t tasks_num         {3};

    ThreadPool<PoolThread> *pool {};

	xTEST_CASE("ctor")
	{
    	pool = new ThreadPool<PoolThread>(isPaused, isAutoDelete, isGroupPaused, isGroupAutoDelete);
	}

    xTEST_CASE("numTasks/setNumTasks")
	{
		pool->setNumTasks(tasks_num);

		m_stRv = pool->numTasks();
		xTEST_EQ(m_stRv, tasks_num);
	}

    xTEST_CASE("groupCreate")
    {
        cuint_t        stackSize       {};
        std::tstring_t param           = ::thread_param;
        cuint_t        tasksNum        {5};
        cuint_t        runningTasksMax {10};

        pool->groupCreate(stackSize, nullptr, static_cast<void_t *>(&param), tasksNum, runningTasksMax);
    }

    xTEST_CASE("groupResume")
	{
	    pool->groupResume();
	}

    xTEST_CASE("groupPause")
	{
	    pool->groupPause();
	}

    xTEST_CASE("groupExit")
	{
	    pool->groupExit(500UL);
	}

    xTEST_CASE("groupKill")
	{
	    /// pool->groupKill(500UL);
	}

    xTEST_CASE("groupWait")
	{
	    pool->groupWait(500UL);
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
