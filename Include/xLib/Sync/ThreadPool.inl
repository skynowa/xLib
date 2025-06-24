/**
 * \file  ThreadPool.inl
 * \brief thread pool
 */


#include <xLib/Sync/AutoMutex.h>

namespace xl::sync
{

/***************************************************************************************************
*    public
*
***************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename TaskT>
Mutex ThreadPool<TaskT>::_s_mutex;

template<typename TaskT>
Cout  ThreadPool<TaskT>::_s_log;
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
ThreadPool<TaskT>::ThreadPool(
    cbool_t a_isPaused,
    cbool_t a_isAutoDelete,
    cbool_t a_isGroupPaused,
    cbool_t a_isGroupAutoDelete
) :
    Thread            (a_isAutoDelete),
    _isGroupPaused    (a_isGroupPaused),
    _isGroupAutoDelete(a_isGroupAutoDelete)
{
    xUNUSED(a_isPaused);

    // TODO: [skynowa] ThreadPool - a_isPaused()

    // _s_log.trace(xT("--------------------------------"));
    // _s_log.trace(xT("ThreadPool: construct"));
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
ThreadPool<TaskT>::~ThreadPool()
{
    _s_log.trace(xT("ThreadPool: destroy"));
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    public: groups
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::groupCreate(
    cuint_t          &a_stackSize,
    const func_ptr_t  a_funcPtr,
    void_t           *a_param,
    std::csize_t     &a_numTasks,
    std::csize_t     &a_maxRunningTasks
)
{
    xTEST_NA(a_stackSize); // TODO: [skynowa] ThreadPool<TaskT>::groupCreate() - MaxValue
    xTEST_NA(a_funcPtr);
    xTEST_NA(a_param);
    xTEST_NA(a_numTasks);
    xTEST_NA(a_maxRunningTasks);

    xCHECK_DO(isRunning(), _s_log.trace(xT("ThreadPool: is running")); return);

    //-------------------------------------
    //
    _stackSize       = a_stackSize;
    _funcPtr         = a_funcPtr;
    _param           = a_param;
    _numTasks        = a_numTasks;
    _maxRunningTasks = a_maxRunningTasks;

	//-------------------------------------
	//
	{
		cbool_t  isPaused       {false};
		cuint_t  stackSizeBytes {0};
		void_t  *param          {};

		create(isPaused, stackSizeBytes, param);
	}
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::groupResume()
{
    xCHECK_DO(!isRunning(), _s_log.trace(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //
    {
        AutoMutex mutex(&_s_mutex);

        for (const auto &it : _tasks) {
            xCHECK_DO(!it->isRunning(), _s_log.trace(xT("Not running")); continue);

            it->resume();
        }
    }

    //-------------------------------------
    //
    resume();
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::groupPause()
{
    xCHECK_DO(!isRunning(), _s_log.trace(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //
    pause();

    //-------------------------------------
    //
    {
        AutoMutex mutex(&_s_mutex);

        for (const auto &it : _tasks) {
            xCHECK_DO(!it->isRunning(), _s_log.trace(xT("Not running")); continue);

            it->pause();
        }
    }
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::groupExit(
    culong_t &a_timeoutMsec
)
{
    xUNUSED(a_timeoutMsec);

    // TODO: [skynowa] ThreadPool<TaskT>::groupExit() - a_timeoutMsec

    xCHECK_DO(!isRunning(), _s_log.trace(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //
    exit(/* a_timeoutMsec */);

    //-------------------------------------
    //
    {
        AutoMutex mutex(&_s_mutex);

        for (const auto &it : _tasks)    {
            xCHECK_DO(!it->isRunning(), _s_log.trace(xT("ThreadPool: not running"));
                continue);

            it->exit(/* a_timeoutMsec */);
        }
    }
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::groupKill(
    culong_t &a_timeoutMsec
)
{
    xTEST_PTR(this);

    xCHECK_DO(!isRunning(), _s_log.trace(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //
    {
        AutoMutex mutex(&_s_mutex);

        for (const auto &it : _tasks)    {
            xCHECK_DO(!it->isRunning(), _s_log.trace(xT("Not running")); continue);

            it->kill(a_timeoutMsec);
        }
    }

    //-------------------------------------
    //
    kill(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::groupWait(
    culong_t &a_timeoutMsec
)
{
    xCHECK_DO(!isRunning(), _s_log.trace(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //
    {
        AutoMutex mutex(&_s_mutex);

        for (const auto &it : _tasks)    {
            xCHECK_DO(!it->isRunning(), _s_log.trace(xT("Not running")); continue);

            it->wait(a_timeoutMsec);
        }
    }

    //-------------------------------------
    // - !  !
    //-- wait(culTimeout);
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    public:
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename TaskT>
size_t
ThreadPool<TaskT>::maxTasks() const
{
    // n/a

    return _maxRunningTasks;
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::setMaxTasks(
    std::csize_t &a_num
)
{
    // n/a

    //-------------------------------------
    // (  uiNum )
    if (_maxRunningTasks < a_num) {
        //    _maxRunningTasks,   uiNum
        size_t tasksForInc = a_num - _maxRunningTasks;

        for (size_t i = 0U; i < tasksForInc; ++ i) {
            _semaphore.post();
        }

        _maxRunningTasks = a_num;

        return;
    }

    //-------------------------------------
    // ( -  +  std::list)
    if (_maxRunningTasks > a_num) {
        AutoMutex mutex(&_s_mutex);

        size_t count       = 0U;
        size_t tasksForDec = _maxRunningTasks - a_num;

        xFOR_EACH_R_CONST(typename std::list<TaskT *>, it, _tasks) {
            xCHECK_DO(!(*it)->isRunning(), _s_log.trace(xT("Not running")); continue);

            #if   xENV_WIN
                ::InterlockedExchange(&((*it)->tag), 1UL);
            #elif xENV_UNIX

            #endif

            (*it)->exit(/* ulTimeout */);

            ++ count;
            xCHECK_DO(count >= tasksForDec, break);
        }

        _maxRunningTasks = a_num;

        return;
    }

    //-------------------------------------
    //  , .. -
    if (a_num == _maxRunningTasks) {
        _maxRunningTasks = a_num;

        return;
    }

    xTEST_FAIL;
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
size_t
ThreadPool<TaskT>::numTasks() const
{
    // n/a

    return _numTasks;
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::setNumTasks(
    std::csize_t &a_num
)
{
    // n/a

    _numTasks = a_num;
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
bool_t
ThreadPool<TaskT>::isEmpty() const
{
    AutoMutex mutex(&_s_mutex);

    bool_t bRv = _tasks.empty();
    // n/a

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
bool_t
ThreadPool<TaskT>::isFull() const
{
    // xTEST_EQ(CONDITION);

    AutoMutex mutex(&_s_mutex);

    xTEST_LESS(_maxRunningTasks, _tasks.size());

    bool_t bRv = (_maxRunningTasks == _tasks.size());
    // n/a

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
size_t
ThreadPool<TaskT>::size() const
{
    // xTEST_EQ(CONDITION);

    AutoMutex mutex(&_s_mutex);

    size_t uiRes = _tasks.size();
    // n/a

    return uiRes;
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    protected
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename TaskT>
uint_t
ThreadPool<TaskT>::onRun(
    void_t *a_param
) /* override */
{
    xTEST_PTR(a_param);

    xTRACE_FUNC

    // TODO: [skynowa] ThreadPool - a_param

    uint_t uiRes {};

    //-------------------------------------
    //
    _semaphore.create(static_cast<long_t>( _maxRunningTasks ), xT(""));

    //-------------------------------------
    //
    xTEST(_tasks.empty());
    _tasks.clear();

    for ( ; ; ) {
        //-------------------------------------
        //
        _semaphore.wait(xTIMEOUT_INFINITE);

        //-------------------------------------
        //  (    - )
        xCHECK_DO(_currTask >= _numTasks, break);
        ////xCHECK_DO(bIsEmpty(), break);

        //-------------------------------------
        //
        bool_t bRv = isTimeToExit();
        xCHECK_DO(bRv, break);

        //-------------------------------------
        // .
        _taskAdd(nullptr);                       //_semaphore.bWait(INFINITE);

        ++ _currTask;

        ////_s_log.trace(xT("_currTask == %i, _numTasks: %i\n"), _currTask, _numTasks);
    }

    //-------------------------------------
    //     (  )
    ////bRv = bWaitGroup(INFINITE/*5000*/);
    ////xTEST_EQ(bRv, true, 0);

    for ( ; ; ) {
        xCHECK_DO(isEmpty(), break);

        ThreadCurrent::currentSleep(500UL);
    }
    xTEST(_tasks.empty());

    _s_log.trace(xT("ThreadPool: Exit thread function"));
    _s_log.trace(xT("ThreadPool: List size: %u"), _tasks.size());

    return uiRes;
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::_taskAdd(
    Thread *a_item
)
{
    xUNUSED(a_item);

    // TODO: [skynowa] ThreadPool - a_item

    auto *task = new TaskT(_isGroupAutoDelete);

    task->index = _currTask;
    // TODO: [skynowa] task->vAttachHandler_OnEnter( xCLOSURE(this, &ThreadPool::_vOnEnterTask) );
    // TODO: [skynowa] task->vAttachHandler_OnExit ( xCLOSURE(this, &ThreadPool::_vOnExitTask ) );

    task->create(_isGroupPaused, _stackSize, _param);
    task->resume();

    {
        AutoMutex mutex(&_s_mutex);
        _tasks.push_back(task);
    }
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::_taskRemove(
    Thread *a_item
)
{
	auto task = static_cast<TaskT *>( a_item );
    xTEST_PTR(task);
    xTEST(task->isRunning());

    //-------------------------------------
    // _semaphore
    if (task->m_ulTag == 0UL) {
        _semaphore.post();
    }

    //-------------------------------------
    //
    {
        AutoMutex mutex(&_s_mutex);

        _tasks.remove(task);
    }

    xTEST_PTR(task);
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::_onEnterTask(
    Thread *a_sender
)
{
    xTEST_PTR(a_sender);
    xTEST(a_sender->isRunning());

    //...

    //_s_log.trace(xT("_vOnEnterTask: #%i"), a_pthTask->index);
}
//-------------------------------------------------------------------------------------------------
template<typename TaskT>
void_t
ThreadPool<TaskT>::_onExitTask(
    Thread *a_sender
)
{
    xTEST_PTR(a_sender);
    xTEST(a_sender->isRunning());

    _taskRemove(a_sender);

    //_s_log.trace(xT("_vOnExitTask stop: #%i"), a_pthTask->index);
}
//-------------------------------------------------------------------------------------------------

} // namespace
