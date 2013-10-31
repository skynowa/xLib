/**
 * \file  CxThreadPool.inl
 * \brief thread pool
 */


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<class T>
CxMutex CxThreadPool<T>::_m_mtList;

template<class T>
CxTracer  CxThreadPool<T>::_m_clLog;
//------------------------------------------------------------------------------
template<class T>
CxThreadPool<T>::CxThreadPool(
    cbool_t &a_cbIsPaused,
    cbool_t &a_cbIsAutoDelete,
    cbool_t &a_cbIsGroupPaused,
    cbool_t &a_cbIsGroupAutoDelete
) :
    CxThread              (a_cbIsAutoDelete),
    _m_uiStackSize        (0U),
    _m_fpFuncPtr          (NULL),
    _m_pvParam            (NULL),
    _m_cbIsGroupPaused    (a_cbIsGroupPaused),
    _m_cbIsGroupAutoDelete(a_cbIsGroupAutoDelete),
    _m_semSemaphore       (),
    _m_lthTasks           (),
    _m_uiMaxRunningTasks  (0U),
    _m_uiNumTasks         (0U),
    _m_uiCurrTask         (0U)
{


    /*LOG*/_m_clLog.write(xT("--------------------------------"));
    /*LOG*/_m_clLog.write(xT("CxThreadPool: construct"));
}
//------------------------------------------------------------------------------
template<class T>
CxThreadPool<T>::~CxThreadPool() {


    /*LOG*/_m_clLog.write(xT("CxThreadPool: destroy"));
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public: groups
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupCreate(
    cuint_t          &a_cuiStackSize,
    const func_ptr_t  a_fpFuncPtr,
    void_t           *a_pvParam,
    std::csize_t     &a_cuiNumTasks,
    std::csize_t     &a_cuiMaxRunningTasks
)
{
    xTEST_LESS_EQ(0U, a_cuiStackSize);    // TODO: MaxValue
    xTEST_NA(a_fpFuncPtr);
    xTEST_NA(a_pvParam);
    xTEST_LESS_EQ(size_t(0), a_cuiNumTasks);
    xTEST_LESS_EQ(size_t(0), a_cuiMaxRunningTasks);

    xCHECK_DO(isRunning(), /*LOG*/_m_clLog.write(xT("CxThreadPool: is running")); return);

    //-------------------------------------
    //
    _m_uiStackSize       = a_cuiStackSize;
    _m_fpFuncPtr         = a_fpFuncPtr;
    _m_pvParam           = a_pvParam;
    _m_uiNumTasks        = a_cuiNumTasks;
    _m_uiMaxRunningTasks = a_cuiMaxRunningTasks;

    //-------------------------------------
    //
    create(false, 0U, NULL);
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupResume() {
    xCHECK_DO(!isRunning(), /*LOG*/_m_clLog.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(class std::list<T *>, it, _m_lthTasks) {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_m_clLog.write(xT("Not running")); continue);

            (*it)->resume();
        }
    }

    //-------------------------------------
    //
    resume();
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupPause() {
    xCHECK_DO(!isRunning(), /*LOG*/_m_clLog.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //���
    pause();

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(class std::list<T *>, it, _m_lthTasks) {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_m_clLog.write(xT("Not running")); continue);

            (*it)->pause();
        }
    }
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupExit(
    culong_t &a_culTimeout
)
{
    xCHECK_DO(!isRunning(), /*LOG*/_m_clLog.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //���
    exit(/* a_culTimeout */);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(class std::list<T *>, it, _m_lthTasks)    {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_m_clLog.write(xT("CxThreadPool: not running")); continue);

            (*it)->exit(/* a_culTimeout */);
        }
    }
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupKill(
    culong_t &a_culTimeout
)
{
    xTEST_PTR(this);

    xCHECK_DO(!isRunning(), /*LOG*/_m_clLog.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(class std::list<T *>, it, _m_lthTasks)    {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_m_clLog.write(xT("Not running")); continue);

            (*it)->kill(a_culTimeout);
        }
    }

    //-------------------------------------
    //
    kill(a_culTimeout);
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::groupWait(
    culong_t &a_culTimeout
)
{
    xCHECK_DO(!isRunning(), /*LOG*/_m_clLog.write(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(class std::list<T *>, it, _m_lthTasks)    {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_m_clLog.write(xT("Not running")); continue);

            (*it)->wait(a_culTimeout);
        }
    }

    //-------------------------------------
    //��� - !�������� ������ ����!
    //-- wait(culTimeout);
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    public:
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<class T>
size_t
CxThreadPool<T>::maxTasks() const {
    // n/a

    return _m_uiMaxRunningTasks;
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::setMaxTasks(
    std::csize_t &a_cuiNum
)
{
    // n/a

    //-------------------------------------
    //���������� (���� ������� uiNum �������)
    if (_m_uiMaxRunningTasks < a_cuiNum) {
        //������� ���� �������� � _m_uiMaxRunningTasks, ���� ���� uiNum
        size_t uiTasksForInc = a_cuiNum - _m_uiMaxRunningTasks;

        for (size_t i = 0U; i < uiTasksForInc; ++ i) {
            _m_semSemaphore.post();
        }

        _m_uiMaxRunningTasks = a_cuiNum;

        return;
    }

    //-------------------------------------
    //���������� (��������� ���-�� ������� + ��������� std::list)
    if (_m_uiMaxRunningTasks > a_cuiNum) {
        CxAutoMutex amtMutex(&_m_mtList);

        size_t uiCount       = 0U;
        size_t uiTasksForDec = _m_uiMaxRunningTasks - a_cuiNum;

        xFOREACH_R_CONST(class std::list<T *>, it, _m_lthTasks) {
            xCHECK_DO(!(*it)->isRunning(), /*LOG*/_m_clLog.write(xT("Not running")); continue);

            #if   xOS_ENV_WIN
                ::InterlockedExchange(&((*it)->m_ulTag), 1UL);
            #elif xOS_ENV_UNIX

            #endif

            (*it)->exit(/* ulTimeout */);

            ++ uiCount;
            xCHECK_DO(uiCount >= uiTasksForDec, break);
        }

        _m_uiMaxRunningTasks = a_cuiNum;

        return;
    }

    //-------------------------------------
    //������ �� ������, �.�. ���-�� ������� �� ����������
    if (_m_uiMaxRunningTasks == a_cuiNum) {
        _m_uiMaxRunningTasks = a_cuiNum;

        return;
    }

    xTEST_FAIL;
}
//------------------------------------------------------------------------------
template<class T>
size_t
CxThreadPool<T>::numTasks() const {
    // n/a

    return _m_uiNumTasks;
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::setNumTasks(
    std::csize_t &a_cuiNum
)
{
    // n/a

    _m_uiNumTasks = a_cuiNum;
}
//------------------------------------------------------------------------------
template<class T>
bool_t
CxThreadPool<T>::isEmpty() const {


    CxAutoMutex amtMutex(&_m_mtList);

    bool_t bRv = _m_lthTasks.empty();
    // n/a

    return bRv;
}
//------------------------------------------------------------------------------
template<class T>
bool_t
CxThreadPool<T>::isFull() const {
    //xTEST_EQ(CONDITION);

    CxAutoMutex amtMutex(&_m_mtList, true);

    xTEST_LESS(_m_uiMaxRunningTasks, _m_lthTasks.size());

    bool_t bRv = (_m_uiMaxRunningTasks == _m_lthTasks.size());
    // n/a

    return bRv;
}
//------------------------------------------------------------------------------
template<class T>
size_t
CxThreadPool<T>::size() const {
    //xTEST_EQ(CONDITION);

    CxAutoMutex amtMutex(&_m_mtList, true);

    size_t uiRes = _m_lthTasks.size();
    // n/a

    return uiRes;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    protected
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<class T>
uint_t
CxThreadPool<T>::onRun(
    void_t *a_pvParam
)
{
    uint_t uiRes = 0U;

    //-------------------------------------
    //������ �������
    _m_semSemaphore.create(static_cast<long_t>( _m_uiMaxRunningTasks ), xT(""));

    //-------------------------------------
    //������ ����
    xTEST_EQ(true, _m_lthTasks.empty());
    _m_lthTasks.clear();

    xFOREVER {
        //-------------------------------------
        //�������� ���������� ������
        _m_semSemaphore.wait(xTIMEOUT_INFINITE);

        //-------------------------------------
        //��� �������� (���� ��������� ��� ������� - �����)
        xCHECK_DO(_m_uiCurrTask >= _m_uiNumTasks, break);
        ////xCHECK_DO(bIsEmpty(), break);

        //-------------------------------------
        //�� ���� �� ����� ��� ���������������
        bool_t bRv = isTimeToExit();
        xCHECK_DO(bRv, break);

        //-------------------------------------
        //������ ����. ������
        _taskAdd(NULL);                       //_m_semSemaphore.bWait(INFINITE);
        xTEST_EQ(true, bRv);                //continue ???

        ++ _m_uiCurrTask;

        /*LOG*/////_m_clLog.write(xT("_m_uiCurrTask == %i, _m_uiNumTasks: %i\n"), _m_uiCurrTask, _m_uiNumTasks);
    }

    //-------------------------------------
    //���� ���� ����������� �������� ������ (���� �� ������)
    ////bRv = bWaitGroup(INFINITE/*5000*/);
    ////xTEST_EQ(true, bRv, 0);

    xFOREVER {
        xCHECK_DO(isEmpty(), break);

        CxThread::currentSleep(500UL);
    }
    xTEST_EQ(true, _m_lthTasks.empty());

    /*LOG*/_m_clLog.write(xT("CxThreadPool: Exit thread function"));
    /*LOG*/_m_clLog.write(xT("CxThreadPool: List size: %u"), _m_lthTasks.size());

    return uiRes;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::_taskAdd(
    CxThread *a_pvItem
)
{
    T *pthTask = new T(_m_cbIsGroupAutoDelete);
    xTEST_PTR(pthTask);

    pthTask->m_uiIndex = _m_uiCurrTask;
    // TODO: pthTask->vAttachHandler_OnEnter( xCLOSURE(this, &CxThreadPool::_vOnEnterTask) );
    // TODO: pthTask->vAttachHandler_OnExit ( xCLOSURE(this, &CxThreadPool::_vOnExitTask ) );

    pthTask->create(_m_cbIsGroupPaused, _m_uiStackSize, _m_pvParam);
    pthTask->resume();

    {
        CxAutoMutex amtMutex(&_m_mtList);
        _m_lthTasks.push_back(pthTask);
    }
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::_taskRemove(
    CxThread *a_pvItem
)
{
    T *pthTask = static_cast<T *>( a_pvItem );
    xTEST_PTR(pthTask);
    xTEST_EQ(true, pthTask->isRunning());

    //-------------------------------------
    //����������� _m_semSemaphore
    if (0UL == pthTask->m_ulTag) {
        _m_semSemaphore.post();
    }

    //-------------------------------------
    //������� �� ������ ��������� �� �����
    {
        CxAutoMutex amtMutex(&_m_mtList);

        _m_lthTasks.remove(pthTask);
    }

    xTEST_PTR(pthTask);

    return true;
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::_onEnterTask(
    CxThread *a_pthSender
)
{
    xTEST_PTR(a_pthSender);
    xTEST_EQ(true, a_pthSender->isRunning());

    //...

    /*LOG*///_m_clLog.write(xT("_vOnEnterTask: #%i"), a_pthTask->m_uiIndex);
}
//------------------------------------------------------------------------------
template<class T>
void_t
CxThreadPool<T>::_onExitTask(
    CxThread *a_pthSender
)
{
    xTEST_PTR(a_pthSender);
    xTEST_EQ(true, a_pthSender->isRunning());

    _taskRemove(a_pthSender);

    /*LOG*///_m_clLog.write(xT("_vOnExitTask stop: #%i"), a_pthTask->m_uiIndex);
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
