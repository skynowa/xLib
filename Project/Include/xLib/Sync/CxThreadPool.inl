/**
 * \file  CxThreadPool.inl
 * \brief thread pool
 */


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<typename T>
CxMutex CxThreadPool<T>::_m_mtList;

template<typename T>
CxTracer  CxThreadPool<T>::_m_clLog;
//---------------------------------------------------------------------------
template<typename T>
CxThreadPool<T>::CxThreadPool(
    const bool &a_cbIsPaused,
    const bool &a_cbIsAutoDelete,
    const bool &a_cbIsGroupPaused,
    const bool &a_cbIsGroupAutoDelete
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
    /*DEBUG*/

    /*LOG*/_m_clLog.vWrite(xT("--------------------------------"));
    /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: construct"));
}
//---------------------------------------------------------------------------
template<typename T>
CxThreadPool<T>::~CxThreadPool() {
    /*DEBUG*/

    /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: destroy"));
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: groups
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::vGroupCreate(
    const uint_t     &a_cuiStackSize,
    const func_ptr_t  a_fpFuncPtr,
    void             *a_pvParam,
    const size_t     &a_cuiNumTasks,
    const size_t     &a_cuiMaxRunningTasks
)
{
    /*DEBUG*/xTEST_LESS_EQ(0U, a_cuiStackSize);    // TODO: MaxValue
    /*DEBUG*/ xDEBUG_VAR_NA(a_fpFuncPtr);
    /*DEBUG*/ xDEBUG_VAR_NA(a_pvParam);
    /*DEBUG*/xTEST_LESS_EQ(size_t(0), a_cuiNumTasks);
    /*DEBUG*/xTEST_LESS_EQ(size_t(0), a_cuiMaxRunningTasks);

    xCHECK_DO(true == bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: is running")); return);

    //-------------------------------------
    //
    _m_uiStackSize       = a_cuiStackSize;
    _m_fpFuncPtr         = a_fpFuncPtr;
    _m_pvParam           = a_pvParam;
    _m_uiNumTasks        = a_cuiNumTasks;
    _m_uiMaxRunningTasks = a_cuiMaxRunningTasks;

    //-------------------------------------
    //
    vCreate(false, 0U, NULL);
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::vGroupResume() {
    /*DEBUG*/

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(typename std::list<T *>, it, _m_lthTasks) {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("Not running")); continue);

            (*it)->vResume();
        }
    }

    //-------------------------------------
    //
    vResume();
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::vGroupPause() {
    /*DEBUG*/

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //���
    vPause();

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(typename std::list<T *>, it, _m_lthTasks) {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("Not running")); continue);

            (*it)->vPause();
        }
    }
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::vGroupExit(
    const ulong_t &a_culTimeout
)
{
    /*DEBUG*/

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //���
    vExit(/* a_culTimeout */);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(typename std::list<T *>, it, _m_lthTasks)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: not running")); continue);

            (*it)->vExit(/* a_culTimeout */);
        }
    }
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::vGroupKill(
    const ulong_t &a_culTimeout
)
{
    /*DEBUG*/xTEST_PTR(this);

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(typename std::list<T *>, it, _m_lthTasks)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("Not running")); continue);

            (*it)->vKill(a_culTimeout);
        }
    }

    //-------------------------------------
    //
    vKill(a_culTimeout);
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::vGroupWait(
    const ulong_t &a_culTimeout
)
{
    /*DEBUG*/

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: not running")); return);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex amtMutex(&_m_mtList);

        xFOREACH_CONST(typename std::list<T *>, it, _m_lthTasks)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("Not running")); continue);

            (*it)->vWait(a_culTimeout);
        }
    }

    //-------------------------------------
    //��� - !�������� ������ ����!
    //-- vWait(culTimeout);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public:
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<typename T>
size_t
CxThreadPool<T>::uiMaxTasks() const {
    /*DEBUG*/// n/a

    return _m_uiMaxRunningTasks;
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::vSetMaxTasks(
    const size_t &a_cuiNum
)
{
    /*DEBUG*/// n/a

    //-------------------------------------
    //���������� (���� ������� uiNum �������)
    if (_m_uiMaxRunningTasks < a_cuiNum) {
        //������� ���� �������� � _m_uiMaxRunningTasks, ���� ���� uiNum
        size_t uiTasksForInc = a_cuiNum - _m_uiMaxRunningTasks;

        for (size_t i = 0U; i < uiTasksForInc; ++ i) {
            _m_semSemaphore.vPost();
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

        xFOREACH_R_CONST(typename std::list<T *>, it, _m_lthTasks) {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.vWrite(xT("Not running")); continue);

            #if   xOS_ENV_WIN
                ::InterlockedExchange(&((*it)->m_ulTag), 1UL);
            #elif xOS_ENV_UNIX

            #endif

            (*it)->vExit(/* ulTimeout */);

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

    /*DEBUG*/xTEST_FAIL;
}
//---------------------------------------------------------------------------
template<typename T>
size_t
CxThreadPool<T>::uiNumTasks() const {
    /*DEBUG*/// n/a

    return _m_uiNumTasks;
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::vSetNumTasks(
    const size_t &a_cuiNum
)
{
    /*DEBUG*/// n/a

    _m_uiNumTasks = a_cuiNum;
}
//---------------------------------------------------------------------------
template<typename T>
bool
CxThreadPool<T>::bIsEmpty() const {
    /*DEBUG*/

    CxAutoMutex amtMutex(&_m_mtList);

    bool bRv = _m_lthTasks.empty();
    /*DEBUG*/// n/a

    return bRv;
}
//---------------------------------------------------------------------------
template<typename T>
bool
CxThreadPool<T>::bIsFull() const {
    /*DEBUG*///xTEST_EQ(CONDITION);

    CxAutoMutex amtMutex(&_m_mtList, true);

    /*DEBUG*/xTEST_LESS(_m_uiMaxRunningTasks, _m_lthTasks.size());

    bool bRv = (_m_uiMaxRunningTasks == _m_lthTasks.size());
    /*DEBUG*/// n/a

    return bRv;
}
//---------------------------------------------------------------------------
template<typename T>
size_t
CxThreadPool<T>::uiSize() const {
    /*DEBUG*///xTEST_EQ(CONDITION);

    CxAutoMutex amtMutex(&_m_mtList, true);

    size_t uiRes = _m_lthTasks.size();
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<typename T>
uint_t
CxThreadPool<T>::uiOnRun(
    void *a_pvParam
)
{
    /*DEBUG*/

    uint_t uiRes = 0U;

    //-------------------------------------
    //������ �������
    _m_semSemaphore.vCreate(_m_uiMaxRunningTasks, xT(""));

    //-------------------------------------
    //������ ����
    /*DEBUG*/xTEST_EQ(true, _m_lthTasks.empty());
    _m_lthTasks.clear();

    for ( ; ; ) {
        //-------------------------------------
        //�������� ���������� ������
        _m_semSemaphore.vWait(xTIMEOUT_INFINITE);

        //-------------------------------------
        //��� �������� (���� ��������� ��� ������� - �����)
        xCHECK_DO(_m_uiCurrTask >= _m_uiNumTasks, break);
        ////xCHECK_DO(true == bIsEmpty(), break);

        //-------------------------------------
        //�� ���� �� ����� ��� ���������������
        bool bRv = bIsTimeToExit();
        xCHECK_DO(true == bRv, break);

        //-------------------------------------
        //������ ����. ������
        _vTaskAdd(NULL);                       //_m_semSemaphore.bWait(INFINITE);
        /*DEBUG*/xTEST_EQ(true, bRv);                //continue ???

        ++ _m_uiCurrTask;

        /*LOG*/////_m_clLog.vWrite(xT("_m_uiCurrTask == %i, _m_uiNumTasks: %i\n"), _m_uiCurrTask, _m_uiNumTasks);
    }

    //-------------------------------------
    //���� ���� ����������� �������� ������ (���� �� ������)
    ////bRv = bWaitGroup(INFINITE/*5000*/);
    /////*DEBUG*/xTEST_EQ(true, bRv, 0);

    for ( ; ; ) {
        xCHECK_DO(true == bIsEmpty(), break);

        CxCurrentThread::vSleep(500UL);
    }
    /*DEBUG*/xTEST_EQ(true, _m_lthTasks.empty());

    /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: Exit thread function"));
    /*LOG*/_m_clLog.vWrite(xT("CxThreadPool: List size: %u"), _m_lthTasks.size());

    return uiRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::_vTaskAdd(
    CxThread *a_pvItem
)
{
    /*DEBUG*/

    T *pthTask = new T(_m_cbIsGroupAutoDelete);
    /*DEBUG*/xTEST_PTR(pthTask);

    pthTask->m_uiIndex = _m_uiCurrTask;
    // TODO: pthTask->vAttachHandler_OnEnter( xCLOSURE(this, &CxThreadPool::_vOnEnterTask) );
    // TODO: pthTask->vAttachHandler_OnExit ( xCLOSURE(this, &CxThreadPool::_vOnExitTask ) );

    pthTask->vCreate(_m_cbIsGroupPaused, _m_uiStackSize, _m_pvParam);
    pthTask->vResume();

    {
        CxAutoMutex amtMutex(&_m_mtList);
        _m_lthTasks.push_back(pthTask);
    }
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::_vTaskRemove(
    CxThread *a_pvItem
)
{
    T *pthTask = static_cast<T *>( a_pvItem );
    /*DEBUG*/xTEST_PTR(pthTask);
    /*DEBUG*/xTEST_EQ(true, pthTask->bIsRunning());

    //-------------------------------------
    //����������� _m_semSemaphore
    if (0UL == pthTask->m_ulTag) {
        _m_semSemaphore.vPost();
    }

    //-------------------------------------
    //������� �� ������ ��������� �� �����
    {
        CxAutoMutex amtMutex(&_m_mtList);

        _m_lthTasks.remove(pthTask);
    }

    /*DEBUG*/xTEST_PTR(pthTask);

    return true;
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::_vOnEnterTask(
    CxThread *a_pthSender
)
{
    /*DEBUG*/
    /*DEBUG*/xTEST_PTR(a_pthSender);
    /*DEBUG*/xTEST_EQ(true, a_pthSender->bIsRunning());

    //...

    /*LOG*///_m_clLog.vWrite(xT("_vOnEnterTask: #%i"), a_pthTask->m_uiIndex);
}
//---------------------------------------------------------------------------
template<typename T>
void
CxThreadPool<T>::_vOnExitTask(
    CxThread *a_pthSender
)
{
    /*DEBUG*/
    /*DEBUG*/xTEST_PTR(a_pthSender);
    /*DEBUG*/xTEST_EQ(true, a_pthSender->bIsRunning());

    _vTaskRemove(a_pthSender);

    /*LOG*///_m_clLog.vWrite(xT("_vOnExitTask stop: #%i"), a_pthTask->m_uiIndex);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
