/**
 * \file  ThreadPool.inl
 * \brief thread pool
 */


#if !xOPTION_HEADER_ONLY
    #include "ThreadPool.h"
#endif

#include <xLib/Sync/Mutex.h>
#include <xLib/Sync/AutoMutex.h>
#include <xLib/Sync/Thread.h>


xNAMESPACE_BEGIN2(xlib, sync)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class T>
Mutex ThreadPool<T>::_s_mutex;

template<class T>
Trace  ThreadPool<T>::_s_log;
//-------------------------------------------------------------------------------------------------
template<class T>
ThreadPool<T>::ThreadPool(
    cbool_t &a_isPaused,
    cbool_t &a_isAutoDelete,
    cbool_t &a_isGroupPaused,
    cbool_t &a_isGroupAutoDelete
) :
    Thread          (a_isAutoDelete),
    _stackSize        (0U),
    _funcPtr          (xPTR_NULL),
    _param            (xPTR_NULL),
    _isGroupPaused    (a_isGroupPaused),
    _isGroupAutoDelete(a_isGroupAutoDelete),
    _semaphore        (),
    _tasks            (),
    _maxRunningTasks  (0U),
    _numTasks         (0U),
    _currTask         (0U)
{
    xUNUSED(a_isPaused);

    // TODO: ThreadPool - a_isPaused()

    /*LOG*/_s_log.write(xT("--------------------------------"));
    /*LOG*/_s_log.write(xT("ThreadPool: construct"));
}
//-------------------------------------------------------------------------------------------------
template<class T>
ThreadPool<T>::~ThreadPool()
{
    /*LOG*/_s_log.write(xT("ThreadPool: destroy"));
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    public: groups
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::groupCreate(
    cuint_t          &a_stackSize,
    const func_ptr_t  a_funcPtr,
    void_t           *a_param,
    std::csize_t     &a_numTasks,
    std::csize_t     &a_maxRunningTasks
)
{
    xTEST_NA(a_stackSize);    // TODO: ThreadPool<T>::groupCreate() - MaxValue
    xTEST_NA(a_funcPtr);
    xTEST_NA(a_param);
    xTEST_NA(a_numTasks);
    xTEST_NA(a_maxRunningTasks);

    xCHECK_DO(isRunning(), /*LOG*/_s_log.write(xT("ThreadPool: is running")); return);

    //-------------------------------------
    //
    _stackSize       = a_stackSize;
    _funcPtr         = a_funcPtr;
    _param           = a_param;
    _numTasks        = a_numTasks;
    _maxRunningTasks = a_maxRunningTasks;

    //-------------------------------------
    //
    create(false, 0U, xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::groupResume()
{
    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //
    {
        AutoMutex mutex(&_s_mutex);

        xFOREACH_CONST(typename std::list<T *>, it, _tasks) {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_s_log.write(xT("Not running")); continue);

            (*it)->resume();
        }
    }

    //-------------------------------------
    //
    resume();
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::groupPause()
{
    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //���
    pause();

    //-------------------------------------
    //������� ������
    {
        AutoMutex mutex(&_s_mutex);

        xFOREACH_CONST(typename std::list<T *>, it, _tasks) {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_s_log.write(xT("Not running")); continue);

            (*it)->pause();
        }
    }
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::groupExit(
    culong_t &a_timeoutMsec
)
{
    xUNUSED(a_timeoutMsec);

    // TODO: ThreadPool<T>::groupExit() - a_timeoutMsec

    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //���
    exit(/* a_timeoutMsec */);

    //-------------------------------------
    //������� ������
    {
        AutoMutex mutex(&_s_mutex);

        xFOREACH_CONST(typename std::list<T *>, it, _tasks)    {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_s_log.write(xT("ThreadPool: not running"));
                continue);

            (*it)->exit(/* a_timeoutMsec */);
        }
    }
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::groupKill(
    culong_t &a_timeoutMsec
)
{
    xTEST_PTR(this);

    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //������� ������
    {
        AutoMutex mutex(&_s_mutex);

        xFOREACH_CONST(typename std::list<T *>, it, _tasks)    {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_s_log.write(xT("Not running")); continue);

            (*it)->kill(a_timeoutMsec);
        }
    }

    //-------------------------------------
    //
    kill(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::groupWait(
    culong_t &a_timeoutMsec
)
{
    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("ThreadPool: not running")); return);

    //-------------------------------------
    //������� ������
    {
        AutoMutex mutex(&_s_mutex);

        xFOREACH_CONST(typename std::list<T *>, it, _tasks)    {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_s_log.write(xT("Not running")); continue);

            (*it)->wait(a_timeoutMsec);
        }
    }

    //-------------------------------------
    //��� - !�������� ������ ����!
    //-- wait(culTimeout);
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    public:
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class T>
size_t
ThreadPool<T>::maxTasks() const
{
    // n/a

    return _maxRunningTasks;
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::setMaxTasks(
    std::csize_t &a_num
)
{
    // n/a

    //-------------------------------------
    //���������� (���� ������� uiNum �������)
    if (_maxRunningTasks < a_num) {
        //������� ���� �������� � _maxRunningTasks, ���� ���� uiNum
        size_t tasksForInc = a_num - _maxRunningTasks;

        for (size_t i = 0U; i < tasksForInc; ++ i) {
            _semaphore.post();
        }

        _maxRunningTasks = a_num;

        return;
    }

    //-------------------------------------
    //���������� (��������� ���-�� ������� + ��������� std::list)
    if (_maxRunningTasks > a_num) {
        AutoMutex mutex(&_s_mutex);

        size_t count       = 0U;
        size_t tasksForDec = _maxRunningTasks - a_num;

        xFOREACH_R_CONST(typename std::list<T *>, it, _tasks) {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_s_log.write(xT("Not running")); continue);

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
    //������ �� ������, �.�. ���-�� ������� �� ����������
    if (a_num == _maxRunningTasks) {
        _maxRunningTasks = a_num;

        return;
    }

    xTEST_FAIL;
}
//-------------------------------------------------------------------------------------------------
template<class T>
size_t
ThreadPool<T>::numTasks() const
{
    // n/a

    return _numTasks;
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::setNumTasks(
    std::csize_t &a_num
)
{
    // n/a

    _numTasks = a_num;
}
//-------------------------------------------------------------------------------------------------
template<class T>
bool_t
ThreadPool<T>::isEmpty() const
{


    AutoMutex mutex(&_s_mutex);

    bool_t bRv = _tasks.empty();
    // n/a

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<class T>
bool_t
ThreadPool<T>::isFull() const
{
    //xTEST_EQ(CONDITION);

    AutoMutex mutex(&_s_mutex);

    xTEST_LESS(_maxRunningTasks, _tasks.size());

    bool_t bRv = (_maxRunningTasks == _tasks.size());
    // n/a

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<class T>
size_t
ThreadPool<T>::size() const
{
    //xTEST_EQ(CONDITION);

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
template<class T>
uint_t
ThreadPool<T>::onRun(
    void_t *a_param
)
{
    xUNUSED(a_param);

    // TODO: ThreadPool - a_param

    uint_t uiRes = 0U;

    //-------------------------------------
    //������ �������
    _semaphore.create(static_cast<long_t>( _maxRunningTasks ), xT(""));

    //-------------------------------------
    //������ ����
    xTEST_EQ(_tasks.empty(), true);
    _tasks.clear();

    for ( ; ; ) {
        //-------------------------------------
        //�������� ���������� ������
        _semaphore.wait(xTIMEOUT_INFINITE);

        //-------------------------------------
        //��� �������� (���� ��������� ��� ������� - �����)
        xCHECK_DO(_currTask >= _numTasks, break);
        ////xCHECK_DO(bIsEmpty(), break);

        //-------------------------------------
        //�� ���� �� ����� ��� ���������������
        bool_t bRv = isTimeToExit();
        xCHECK_DO(bRv, break);

        //-------------------------------------
        //������ ����. ������
        _taskAdd(xPTR_NULL);                       //_semaphore.bWait(INFINITE);
        xTEST_EQ(bRv, true);                //continue ???

        ++ _currTask;

        /*LOG*/////_s_log.write(xT("_currTask == %i, _numTasks: %i\n"), _currTask, _numTasks);
    }

    //-------------------------------------
    //���� ���� ����������� �������� ������ (���� �� ������)
    ////bRv = bWaitGroup(INFINITE/*5000*/);
    ////xTEST_EQ(bRv, true, 0);

    for ( ; ; ) {
        xCHECK_DO(isEmpty(), break);

        Thread::currentSleep(500UL);
    }
    xTEST_EQ(_tasks.empty(), true);

    /*LOG*/_s_log.write(xT("ThreadPool: Exit thread function"));
    /*LOG*/_s_log.write(xT("ThreadPool: List size: %u"), _tasks.size());

    return uiRes;
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::_taskAdd(
    Thread *a_item
)
{
    xUNUSED(a_item);

    // TODO: ThreadPool - a_item

    T *task = new T(_isGroupAutoDelete);
    xTEST_PTR(task);

    task->index = _currTask;
    // TODO: task->vAttachHandler_OnEnter( xCLOSURE(this, &ThreadPool::_vOnEnterTask) );
    // TODO: task->vAttachHandler_OnExit ( xCLOSURE(this, &ThreadPool::_vOnExitTask ) );

    task->create(_isGroupPaused, _stackSize, _param);
    task->resume();

    {
        AutoMutex mutex(&_s_mutex);
        _tasks.push_back(task);
    }
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::_taskRemove(
    Thread *a_item
)
{
    T *task = static_cast<T *>( a_item );
    xTEST_PTR(task);
    xTEST_EQ(task->isRunning(), true);

    //-------------------------------------
    //����������� _semaphore
    if (task->m_ulTag == 0UL) {
        _semaphore.post();
    }

    //-------------------------------------
    //������� �� ������ ��������� �� �����
    {
        AutoMutex mutex(&_s_mutex);

        _tasks.remove(task);
    }

    xTEST_PTR(task);
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::_onEnterTask(
    Thread *a_sender
)
{
    xTEST_PTR(a_sender);
    xTEST_EQ(a_sender->isRunning(), true);

    //...

    /*LOG*///_s_log.write(xT("_vOnEnterTask: #%i"), a_pthTask->index);
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
ThreadPool<T>::_onExitTask(
    Thread *a_sender
)
{
    xTEST_PTR(a_sender);
    xTEST_EQ(a_sender->isRunning(), true);

    _taskRemove(a_sender);

    /*LOG*///_s_log.write(xT("_vOnExitTask stop: #%i"), a_pthTask->index);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
