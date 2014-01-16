/**
 * \file  CxThreadPool.inl
 * \brief thread pool
 */


#include <xLib/Sync/CxMutex.h>
#include <xLib/Sync/CxAutoMutex.h>
#include <xLib/Sync/CxThread.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class T>
CxMutex CxThreadPool<T>::_s_mutex;

template<class T>
CxTrace  CxThreadPool<T>::_s_log;
//-------------------------------------------------------------------------------------------------
template<class T>
CxThreadPool<T>::CxThreadPool(
    cbool_t &a_isPaused,
    cbool_t &a_isAutoDelete,
    cbool_t &a_isGroupPaused,
    cbool_t &a_isGroupAutoDelete
) :
    CxThread          (a_isAutoDelete),
    _stackSize        (0U),
    _funcPtr          (NULL),
    _param            (NULL),
    _isGroupPaused    (a_isGroupPaused),
    _isGroupAutoDelete(a_isGroupAutoDelete),
    _semaphore        (),
    _tasks            (),
    _maxRunningTasks  (0U),
    _numTasks         (0U),
    _currTask         (0U)
{
    xUNUSED(a_isPaused);

    // TODO: CxThreadPool - a_isPaused()

    /*LOG*/_s_log.write(xT("--------------------------------"));
    /*LOG*/_s_log.write(xT("CxThreadPool: construct"));
}
//-------------------------------------------------------------------------------------------------
template<class T>
CxThreadPool<T>::~CxThreadPool()
{


    /*LOG*/_s_log.write(xT("CxThreadPool: destroy"));
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    public: groups
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupCreate(
    cuint_t          &a_stackSize,
    const func_ptr_t  a_funcPtr,
    void_t           *a_param,
    std::csize_t     &a_numTasks,
    std::csize_t     &a_maxRunningTasks
)
{
    xTEST_NA(a_stackSize);    // TODO: MaxValue
    xTEST_NA(a_funcPtr);
    xTEST_NA(a_param);
    xTEST_NA(a_numTasks);
    xTEST_NA(a_maxRunningTasks);

    xCHECK_DO(isRunning(), /*LOG*/_s_log.write(xT("CxThreadPool: is running")); return);

    //-------------------------------------
    //
    _stackSize       = a_stackSize;
    _funcPtr         = a_funcPtr;
    _param           = a_param;
    _numTasks        = a_numTasks;
    _maxRunningTasks = a_maxRunningTasks;

    //-------------------------------------
    //
    create(false, 0U, NULL);
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupResume()
{
    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //
    {
        CxAutoMutex mutex(&_s_mutex);

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
CxThreadPool<T>::groupPause()
{
    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //���
    pause();

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex mutex(&_s_mutex);

        xFOREACH_CONST(typename std::list<T *>, it, _tasks) {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_s_log.write(xT("Not running")); continue);

            (*it)->pause();
        }
    }
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupExit(
    culong_t &a_timeoutMsec
)
{
    xUNUSED(a_timeoutMsec);

    // TODO: CxThreadPool<T>::groupExit() - a_timeoutMsec

    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //���
    exit(/* a_timeoutMsec */);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex mutex(&_s_mutex);

        xFOREACH_CONST(typename std::list<T *>, it, _tasks)    {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_s_log.write(xT("CxThreadPool: not running"));
                continue);

            (*it)->exit(/* a_timeoutMsec */);
        }
    }
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupKill(
    culong_t &a_timeoutMsec
)
{
    xTEST_PTR(this);

    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex mutex(&_s_mutex);

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
CxThreadPool<T>::groupWait(
    culong_t &a_timeoutMsec
)
{
    xCHECK_DO(!isRunning(), /*LOG*/_s_log.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex mutex(&_s_mutex);

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
CxThreadPool<T>::maxTasks() const
{
    // n/a

    return _maxRunningTasks;
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::setMaxTasks(
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
        CxAutoMutex mutex(&_s_mutex);

        size_t count       = 0U;
        size_t tasksForDec = _maxRunningTasks - a_num;

        xFOREACH_R_CONST(typename std::list<T *>, it, _tasks) {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_s_log.write(xT("Not running")); continue);

            #if   xOS_ENV_WIN
                ::InterlockedExchange(&((*it)->tag), 1UL);
            #elif xOS_ENV_UNIX

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
    if (_maxRunningTasks == a_num) {
        _maxRunningTasks = a_num;

        return;
    }

    xTEST_FAIL;
}
//-------------------------------------------------------------------------------------------------
template<class T>
size_t
CxThreadPool<T>::numTasks() const
{
    // n/a

    return _numTasks;
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::setNumTasks(
    std::csize_t &a_num
)
{
    // n/a

    _numTasks = a_num;
}
//-------------------------------------------------------------------------------------------------
template<class T>
bool_t
CxThreadPool<T>::isEmpty() const
{


    CxAutoMutex mutex(&_s_mutex);

    bool_t bRv = _tasks.empty();
    // n/a

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<class T>
bool_t
CxThreadPool<T>::isFull() const
{
    //xTEST_EQ(CONDITION);

    CxAutoMutex mutex(&_s_mutex);

    xTEST_LESS(_maxRunningTasks, _tasks.size());

    bool_t bRv = (_maxRunningTasks == _tasks.size());
    // n/a

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<class T>
size_t
CxThreadPool<T>::size() const
{
    //xTEST_EQ(CONDITION);

    CxAutoMutex mutex(&_s_mutex);

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
CxThreadPool<T>::onRun(
    void_t *a_param
)
{
    xUNUSED(a_param);

    // TODO: CxThreadPool - a_param

    uint_t uiRes = 0U;

    //-------------------------------------
    //������ �������
    _semaphore.create(static_cast<long_t>( _maxRunningTasks ), xT(""));

    //-------------------------------------
    //������ ����
    xTEST_EQ(true, _tasks.empty());
    _tasks.clear();

    xFOREVER {
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
        _taskAdd(NULL);                       //_semaphore.bWait(INFINITE);
        xTEST_EQ(true, bRv);                //continue ???

        ++ _currTask;

        /*LOG*/////_s_log.write(xT("_currTask == %i, _numTasks: %i\n"), _currTask, _numTasks);
    }

    //-------------------------------------
    //���� ���� ����������� �������� ������ (���� �� ������)
    ////bRv = bWaitGroup(INFINITE/*5000*/);
    ////xTEST_EQ(true, bRv, 0);

    xFOREVER {
        xCHECK_DO(isEmpty(), break);

        CxThread::currentSleep(500UL);
    }
    xTEST_EQ(true, _tasks.empty());

    /*LOG*/_s_log.write(xT("CxThreadPool: Exit thread function"));
    /*LOG*/_s_log.write(xT("CxThreadPool: List size: %u"), _tasks.size());

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
CxThreadPool<T>::_taskAdd(
    CxThread *a_item
)
{
    xUNUSED(a_item);

    // TODO: CxThreadPool - a_item

    T *task = new T(_isGroupAutoDelete);
    xTEST_PTR(task);

    task->index = _currTask;
    // TODO: task->vAttachHandler_OnEnter( xCLOSURE(this, &CxThreadPool::_vOnEnterTask) );
    // TODO: task->vAttachHandler_OnExit ( xCLOSURE(this, &CxThreadPool::_vOnExitTask ) );

    task->create(_isGroupPaused, _stackSize, _param);
    task->resume();

    {
        CxAutoMutex mutex(&_s_mutex);
        _tasks.push_back(task);
    }
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::_taskRemove(
    CxThread *a_item
)
{
    T *task = static_cast<T *>( a_item );
    xTEST_PTR(task);
    xTEST_EQ(true, task->isRunning());

    //-------------------------------------
    //����������� _semaphore
    if (0UL == task->m_ulTag) {
        _semaphore.post();
    }

    //-------------------------------------
    //������� �� ������ ��������� �� �����
    {
        CxAutoMutex mutex(&_s_mutex);

        _tasks.remove(task);
    }

    xTEST_PTR(task);
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::_onEnterTask(
    CxThread *a_sender
)
{
    xTEST_PTR(a_sender);
    xTEST_EQ(true, a_sender->isRunning());

    //...

    /*LOG*///_s_log.write(xT("_vOnEnterTask: #%i"), a_pthTask->index);
}
//-------------------------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::_onExitTask(
    CxThread *a_sender
)
{
    xTEST_PTR(a_sender);
    xTEST_EQ(true, a_sender->isRunning());

    _taskRemove(a_sender);

    /*LOG*///_s_log.write(xT("_vOnExitTask stop: #%i"), a_pthTask->index);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
