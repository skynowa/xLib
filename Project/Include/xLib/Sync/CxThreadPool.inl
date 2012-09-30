/**
 * \file  CxThreadPool.inl
 * \brief thread pool
 */


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<class TaskT>
CxMutex CxThreadPool<TaskT>::_m_csList;

template<class TaskT>
CxConsoleLog      CxThreadPool<TaskT>::_m_clLog(false);
//---------------------------------------------------------------------------
//DONE: CxThreadPool (�����������)
template<class TaskT>
CxThreadPool<TaskT>::CxThreadPool(bool a_bIsPaused,      bool a_bIsAutoDelete,
                                  bool a_bIsGroupPaused, bool a_bIsGroupAutoDelete
) :
    CxThread              (a_bIsPaused, a_bIsAutoDelete),
    _m_bRes               (false),
    _m_uiStackSize        (0),
    _m_fpFuncPtr          (0),
    _m_pvParam            (NULL),
    _m_cbIsGroupPaused    (a_bIsGroupPaused),
    _m_cbIsGroupAutoDelete(a_bIsGroupAutoDelete),
    _m_semSemaphore       (),
    _m_lstpthTasks        (),
    _m_uiMaxRunningTasks  (0),
    _m_uiNumTasks         (0),
    _m_uiCurrTask         (0)
{
    /*DEBUG*/

    /*LOG*/_m_clLog.bWrite(xT("--------------------------------"));
    /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: construct"));
}
//---------------------------------------------------------------------------
//DONE: ~CxThreadPool (����������)
template<class TaskT>
CxThreadPool<TaskT>::~CxThreadPool() {
    /*DEBUG*/

    /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: destroy"));
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: �������� � �������
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bCreateGroup (��������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bCreateGroup(uint_t a_uiStackSize, const TFuncPtr a_fpFuncPtr, void *a_pvParam, uint_t a_uiNumTasks, uint_t a_uiMaxRunningTasks) {
    /*DEBUG*/xASSERT_RET(0    <= a_uiStackSize,       false);    //TODO: MaxValue
    /*DEBUG*/xASSERT_RET(NULL == a_fpFuncPtr,         false);
    /*DEBUG*/xASSERT_RET(NULL != a_pvParam,           false);
    /*DEBUG*/xASSERT_RET(0    <  a_uiNumTasks,        false);
    /*DEBUG*/xASSERT_RET(0    <  a_uiMaxRunningTasks, false);

    bool bRv = false;

    xCHECK_DO(true == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: is running")); return true);

    //-------------------------------------
    //������� ������
    _m_uiStackSize       = a_uiStackSize;
    _m_fpFuncPtr         = a_fpFuncPtr;
    _m_pvParam           = a_pvParam;
    _m_uiNumTasks        = a_uiNumTasks;
    _m_uiMaxRunningTasks = a_uiMaxRunningTasks;

    //-------------------------------------
    //���
    bRv = bCreate(0, 0, NULL);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bResumeGroup (�������������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bResumeGroup() {
    /*DEBUG*/

    bool bRv = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRv = (*it)->bResume();
            /*DEBUG*/xASSERT_RET(true == bRv, false);
        }
    }

    //-------------------------------------
    //���
    bRv = bResume();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bPauseGroup (������������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bPauseGroup() {
    /*DEBUG*/

    bool bRv = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //���
    bRv = bPause();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRv = (*it)->bPause();
            /*DEBUG*/xASSERT_RET(true == bRv, false);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
//TODO: bExitGroup (�����)
template<class TaskT>
bool
CxThreadPool<TaskT>::bExitGroup(ulong_t a_ulTimeout) {
    /*DEBUG*/

    bool bRv = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //���
    bRv = bExit(a_ulTimeout/*INFINITE*/);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); continue);

            bRv = (*it)->bExit(a_ulTimeout);
            /*DEBUG*/xASSERT_RET(true == bRv, false);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
//TODO: uiKillGroup (����������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bKillGroup(ulong_t a_ulTimeout) {
    /*DEBUG*/xASSERT_RET(NULL != this, false);

    bool bRv = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRv = (*it)->bKill(a_ulTimeout);
            /////*DEBUG*/xASSERT_RET(true == bRv, false);
        }
    }

    //-------------------------------------
    //���
    bRv = bKill(ulTimeout);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bWaitGroup (�������� ����������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bWaitGroup(ulong_t a_ulTimeout) {
    /*DEBUG*/

    bool bRv = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //������� ������
    {
        CxAutoMutex CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRv = (*it)->bWait(a_ulTimeout);
            /*DEBUG*/xASSERT_RET(true == bRv, false);
        }
    }

    //-------------------------------------
    //��� - !�������� ������ ����!
    //--bRv = bWait(ulTimeout);
    //--xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public:
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: uiGetMaxTasks (���-�� ������������ ���������� �������)
template<class TaskT>
uint_t
CxThreadPool<TaskT>::uiGetMaxTasks() const {
    /*DEBUG*/// n/a

    return _m_uiMaxRunningTasks;
}
//---------------------------------------------------------------------------
//TODO: bSetMaxTasks (��������� ���-�� ������������ ���������� �������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bSetMaxTasks(uint_t a_uiNum)  {
    /*DEBUG*/// n/a

    bool bRv = false;

    //-------------------------------------
    //���������� (���� ������� uiNum �������)
    if (_m_uiMaxRunningTasks < a_uiNum) {
        //������� ���� �������� � _m_uiMaxRunningTasks, ���� ���� uiNum
        size_t uiTasksForInc = a_uiNum - _m_uiMaxRunningTasks;

        bRv = _m_semSemaphore.bRelease(uiTasksForInc, NULL);
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        _m_uiMaxRunningTasks = a_uiNum;

        return true;
    }

    //-------------------------------------
    //���������� (��������� ���-�� ������� + ��������� std::list)
    if (_m_uiMaxRunningTasks > a_uiNum) {
        CxAutoMutex CS(_m_csList);

        size_t uiCount       = 0;
        size_t uiTasksForDec = _m_uiMaxRunningTasks - a_uiNum;

        for (std::list<TaskT *>::reverse_iterator it = _m_lstpthTasks.rbegin(); it != _m_lstpthTasks.rend(); ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            //��������� ����� - �� ����������� �������
            ::InterlockedExchange(&((*it)->m_ulTag), 1);

            bRv = (*it)->bExit(/*ulTimeout*/5000);
            /*DEBUG*/xASSERT_RET(true == bRv, false);

            ++ uiCount;
            xCHECK_DO(uiCount >= uiTasksForDec, break);
        }

        _m_uiMaxRunningTasks = a_uiNum;

        return true;
    }

    //-------------------------------------
    //������ �� ������, �.�. ���-�� ������� �� ����������
    if (_m_uiMaxRunningTasks == a_uiNum) {
        _m_uiMaxRunningTasks = a_uiNum;

        return true;
    }

    /*DEBUG*/xASSERT_RET(false, false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: uiGetNumTasks (����� �������)
template<class TaskT>
uint_t
CxThreadPool<TaskT>::uiGetNumTasks() const {
    /*DEBUG*/// n/a

    return _m_uiNumTasks;
}
//---------------------------------------------------------------------------
//TODO: bSetNumTasks (��������� ���-�� �������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bSetNumTasks(uint_t a_uiNum) {
    /*DEBUG*/// n/a

    _m_uiNumTasks = a_uiNum;

    return true;
}
//---------------------------------------------------------------------------
//TODO: bIsEmpty (���� �� ���)
template<class TaskT>
bool
CxThreadPool<TaskT>::bIsEmpty() const {
    /*DEBUG*/

    bool bRv = true;

    CxAutoMutex CS(_m_csList);

    bRv = _m_lstpthTasks.empty();
    /*DEBUG*/// n/a

    return bRv;
}
//---------------------------------------------------------------------------
//TODO: bIsFull (�������� �� ���)
template<class TaskT>
bool
CxThreadPool<TaskT>::bIsFull() const {
    /*DEBUG*///xASSERT_RET(CONDITION, RET_VALUE);

    bool bRv = false;

    CxAutoMutex CS(_m_csList, true);

    /*DEBUG*/xASSERT_RET(_m_uiMaxRunningTasks < _m_lstpthTasks.size(), true);

    bRv = (_m_uiMaxRunningTasks == _m_lstpthTasks.size());
    /*DEBUG*/// n/a

    return bRv;
}
//---------------------------------------------------------------------------
//TODO: uiSize (���-�� ������� � ����)
template<class TaskT>
uint_t
CxThreadPool<TaskT>::uiGetSize() const {
    /*DEBUG*///xASSERT_RET(CONDITION, RET_VALUE);

    uint_t uiRes = 0;

    CxAutoMutex CS(_m_csList, true);

    uiRes = _m_lstpthTasks.size();
    /*DEBUG*/// n/a

    return uiRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: uiOnRun (������� �������)
template<class TaskT>
uint_t
CxThreadPool<TaskT>::uiOnRun(void *a_pvParam) {
    /*DEBUG*/

    uint_t uiRes = 0;
    bool   bRv   = false;

    //-------------------------------------
    //������ �������
    bRv = _m_semSemaphore.bCreate(NULL, _m_uiMaxRunningTasks, /*_m_uiMaxRunningTasks*/2048, NULL);
    /*DEBUG*/xASSERT_RET(true == bRv, 0);

    //-------------------------------------
    //������ ����
    /*DEBUG*/xASSERT(true == _m_lstpthTasks.empty());
    _m_lstpthTasks.clear();

    for ( ; ; ) {
        //-------------------------------------
        //�������� ���������� ������
        bRv = _m_semSemaphore.bWait(INFINITE);
        /*DEBUG*/xASSERT_DO(true == bRv, break);

        //-------------------------------------
        //��� �������� (���� ��������� ��� ������� - �����)
        xCHECK_DO(_m_uiCurrTask >= _m_uiNumTasks, break);
        ////xCHECK_DO(true == bIsEmpty(), break);

        //-------------------------------------
        //�� ���� �� ����� ��� ���������������
        bRv = bIsTimeToExit();
        xCHECK_DO(true == bRv, break);

        //-------------------------------------
        //������ ����. ������
        bRv = _bAddTask(NULL);                                    //_m_semSemaphore.bWait(INFINITE);
        /*DEBUG*/xASSERT_DO(true == bRv, break);                //continue ???

        ++ _m_uiCurrTask;

        /*LOG*/////_m_clLog.bWrite(xT("_m_uiCurrTask == %i, _m_uiNumTasks: %i\n"), _m_uiCurrTask, _m_uiNumTasks);
    }

    //-------------------------------------
    //���� ���� ����������� �������� ������ (���� �� ������)
    ////bRv = bWaitGroup(INFINITE/*5000*/);
    /////*DEBUG*/xASSERT_RET(true == bRv, 0);

    for (; ;) {
        xCHECK_DO(true == bIsEmpty(), break);

        bRv = bSleep(500);
        /*DEBUG*/xASSERT_DO(true == bRv, break);
    }
    /*DEBUG*/xASSERT_RET(true == _m_lstpthTasks.empty(), 0);

    /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: Exit thread function"));
    /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: List size: %u"), _m_lstpthTasks.size());

    return uiRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bPopTask (���� ������� �����, �� ������, ��������� ���� �����, ����� ���������� � ��������... )
template<class TaskT>
bool
CxThreadPool<TaskT>::_bAddTask(CxThread *a_pvItem) {
    /*DEBUG*/

    bool bRv = false;

    //-------------------------------------
    //������� ��������� ��������� �����
    try {
            TaskT *pthTask = new TaskT(_m_cbIsGroupPaused, _m_cbIsGroupAutoDelete);
            /*DEBUG*/xASSERT_RET(NULL != pthTask, false);

                   pthTask->m_uiIndex = _m_uiCurrTask;    /*��� �������*/
                   pthTask->vAttachHandler_OnEnter( xCLOSURE(this, &CxThreadPool::_vOnEnterTask) );
                   pthTask->vAttachHandler_OnExit ( xCLOSURE(this, &CxThreadPool::_vOnExitTask ) );

            bRv = pthTask->bCreate(_m_uiStackSize/*0*/, _m_fpFuncPtr/*0*/, _m_pvParam/*NULL*/);
            /*DEBUG*/xASSERT_RET(true == bRv, false);

            bRv = pthTask->bResume();
            /*DEBUG*/xASSERT_RET(true == bRv, false);
        {
            CxAutoMutex CS(_m_csList);
            _m_lstpthTasks.push_back(pthTask);
        }
    } catch (...) {
        /*DEBUG*/xASSERT_RET(false, false);
    }

    return true;
}
//---------------------------------------------------------------------------
//TODO: bPushTask (��������� ������� � �������, ����������� ������� �������� �� 1)
template<class TaskT>
bool
CxThreadPool<TaskT>::_bRemoveTask(CxThread *a_pvItem) {
    bool bRv = false;

    try {
        TaskT *pthTask = static_cast<TaskT *>( a_pvItem );
        /*DEBUG*/xASSERT_RET(NULL  != pthTask,               false);
        /*DEBUG*/xASSERT_RET(false != pthTask->bIsRunning(), false);

        //-------------------------------------
        //����������� _m_semSemaphore
        if (0 == pthTask->m_ulTag) {
            bRv = _m_semSemaphore.bRelease(1, NULL);
            /*DEBUG*/xASSERT_RET(true == bRv, false);
        }

        //-------------------------------------
        //������� �� ������ ��������� �� �����
        {
            CxAutoMutex CS(_m_csList);

            _m_lstpthTasks.remove(pthTask);
        }

        /*DEBUG*/xASSERT_RET(NULL != pthTask, false);
    } catch (...) {
        /*DEBUG*/xASSERT_RET(false, false);
    }

    return true;
}
//---------------------------------------------------------------------------
//TODO: _vOnEnterTask (������ ������� �������)
template<class TaskT>
void
CxThreadPool<TaskT>::_vOnEnterTask(CxThread *a_pthSender)  {
    /*DEBUG*/
    /*DEBUG*/xASSERT_DO(NULL  != a_pthSender,               return);
    /*DEBUG*/xASSERT_DO(false != a_pthSender->bIsRunning(), return);

    //...

    /*LOG*///_m_clLog.bWrite(xT("_vOnEnterTask: #%i"), a_pthTask->m_uiIndex);
}
//---------------------------------------------------------------------------
//TODO: _vOnExitTask (����� ������� �������)
template<class TaskT>
void
CxThreadPool<TaskT>::_vOnExitTask(CxThread *a_pthSender)  {
    /*DEBUG*/
    /*DEBUG*/xASSERT_DO(NULL  != a_pthSender,               return);
    /*DEBUG*/xASSERT_DO(false != a_pthSender->bIsRunning(), return);

    bool bRv = false;

    bRv = _bRemoveTask(a_pthSender);    //if (true == bRv)        //bRelease
    /*DEBUG*/xTEST_EQ(true, bRv);

    /*LOG*///_m_clLog.bWrite(xT("_vOnExitTask stop: #%i"), a_pthTask->m_uiIndex);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
