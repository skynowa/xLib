/**
 * \file  CxThreadPool.inl
 * \brief thread pool
 */


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<class TaskT>
CxCriticalSection CxThreadPool<TaskT>::_m_csList;

template<class TaskT>
CxConsoleLog      CxThreadPool<TaskT>::_m_clLog(false);
//---------------------------------------------------------------------------
//DONE: CxThreadPool (�����������)
template<class TaskT>
CxThreadPool<TaskT>::CxThreadPool(bool bIsPaused,      bool bIsAutoDelete,
                                  bool bIsGroupPaused, bool bIsGroupAutoDelete
) :
    CxThread              (bIsPaused, bIsAutoDelete),
    _m_bRes               (false),
    _m_uiStackSize        (0),
    _m_fpFuncPtr          (0),
    _m_pvParam            (NULL),
    _m_cbIsGroupPaused    (bIsGroupPaused),
    _m_cbIsGroupAutoDelete(bIsGroupAutoDelete),
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
CxThreadPool<TaskT>::bCreateGroup(uint_t uiStackSize, const TFuncPtr fpFuncPtr, void *pvParam, uint_t uiNumTasks, uint_t uiMaxRunningTasks) {
    /*DEBUG*/xASSERT_RET(0    <= uiStackSize,       false);    //TODO: MaxValue
    /*DEBUG*/xASSERT_RET(NULL == fpFuncPtr,         false);
    /*DEBUG*/xASSERT_RET(NULL != pvParam,           false);
    /*DEBUG*/xASSERT_RET(0    <  uiNumTasks,        false);
    /*DEBUG*/xASSERT_RET(0    <  uiMaxRunningTasks, false);

    bool bRes = false;

    xCHECK_DO(true == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: is running")); return true);

    //-------------------------------------
    //������� ������
    _m_uiStackSize       = uiStackSize;
    _m_fpFuncPtr         = fpFuncPtr;
    _m_pvParam           = pvParam;
    _m_uiNumTasks         = uiNumTasks;
    _m_uiMaxRunningTasks = uiMaxRunningTasks;

    //-------------------------------------
    //���
    bRes = bCreate(0, 0, NULL);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bResumeGroup (�������������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bResumeGroup() {
    /*DEBUG*/

    bool bRes = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRes = (*it)->bResume();
            /*DEBUG*/xASSERT_RET(false != bRes, false);
        }
    }

    //-------------------------------------
    //���
    bRes = bResume();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bPauseGroup (������������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bPauseGroup() {
    /*DEBUG*/

    bool bRes = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //���
    bRes = bPause();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRes = (*it)->bPause();
            /*DEBUG*/xASSERT_RET(false != bRes, false);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
//TODO: bExitGroup (�����)
template<class TaskT>
bool
CxThreadPool<TaskT>::bExitGroup(ulong_t ulTimeout) {
    /*DEBUG*/

    bool bRes = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //���
    bRes = bExit(ulTimeout/*INFINITE*/);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); continue);

            bRes = (*it)->bExit(ulTimeout);
            /*DEBUG*/xASSERT_RET(false != bRes, false);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
//TODO: uiKillGroup (����������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bKillGroup(ulong_t ulTimeout) {
    /*DEBUG*/xASSERT_RET(NULL != this, false);

    bool bRes = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRes = (*it)->bKill(ulTimeout);
            /////*DEBUG*/xASSERT_RET(false != bRes, false);
        }
    }

    //-------------------------------------
    //���
    bRes = bKill(ulTimeout);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//TODO: bWaitGroup (�������� ����������)
template<class TaskT>
bool
CxThreadPool<TaskT>::bWaitGroup(ulong_t ulTimeout) {
    /*DEBUG*/

    bool bRes = false;

    xCHECK_DO(false == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return true);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRes = (*it)->bWait(ulTimeout);
            /*DEBUG*/xASSERT_RET(false != bRes, false);
        }
    }

    //-------------------------------------
    //��� - !�������� ������ ����!
    //--bRes = bWait(ulTimeout);
    //--xASSERT_RET(false != bRes, false);

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
CxThreadPool<TaskT>::bSetMaxTasks(uint_t uiNum)  {
    /*DEBUG*/// n/a

    bool bRes = false;

    //-------------------------------------
    //���������� (���� ������� uiNum �������)
    if (_m_uiMaxRunningTasks < uiNum) {
        //������� ���� �������� � _m_uiMaxRunningTasks, ���� ���� uiNum
        size_t uiTasksForInc = uiNum - _m_uiMaxRunningTasks;

        bRes = _m_semSemaphore.bRelease(uiTasksForInc, NULL);
        /*DEBUG*/xASSERT_RET(false != bRes, false);

        _m_uiMaxRunningTasks = uiNum;

        return true;
    }

    //-------------------------------------
    //���������� (��������� ���-�� ������� + ��������� std::list)
    if (_m_uiMaxRunningTasks > uiNum) {
        CxAutoCriticalSection CS(_m_csList);

        size_t uiCount       = 0;
        size_t uiTasksForDec = _m_uiMaxRunningTasks - uiNum;

        for (std::list<TaskT *>::reverse_iterator it = _m_lstpthTasks.rbegin(); it != _m_lstpthTasks.rend(); ++ it)    {
            xCHECK_DO(false == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            //��������� ����� - �� ����������� �������
            ::InterlockedExchange(&((*it)->m_ulTag), 1);

            bRes = (*it)->bExit(/*ulTimeout*/5000);
            /*DEBUG*/xASSERT_RET(false != bRes, false);

            ++ uiCount;
            xCHECK_DO(uiCount >= uiTasksForDec, break);
        }

        _m_uiMaxRunningTasks = uiNum;

        return true;
    }

    //-------------------------------------
    //������ �� ������, �.�. ���-�� ������� �� ����������
    if (_m_uiMaxRunningTasks == uiNum) {
        _m_uiMaxRunningTasks = uiNum;

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
CxThreadPool<TaskT>::bSetNumTasks(uint_t uiNum) {
    /*DEBUG*/// n/a

    _m_uiNumTasks = uiNum;

    return true;
}
//---------------------------------------------------------------------------
//TODO: bIsEmpty (���� �� ���)
template<class TaskT>
bool
CxThreadPool<TaskT>::bIsEmpty() const {
    /*DEBUG*/

    bool bRes = true;

    CxAutoCriticalSection CS(_m_csList);

    bRes = _m_lstpthTasks.empty();
    /*DEBUG*/// n/a

    return bRes;
}
//---------------------------------------------------------------------------
//TODO: bIsFull (�������� �� ���)
template<class TaskT>
bool
CxThreadPool<TaskT>::bIsFull() const {
    /*DEBUG*///xASSERT_RET(CONDITION, RET_VALUE);

    bool bRes = false;

    CxAutoCriticalSection CS(_m_csList, true);

    /*DEBUG*/xASSERT_RET(_m_uiMaxRunningTasks < _m_lstpthTasks.size(), true);

    bRes = (_m_uiMaxRunningTasks == _m_lstpthTasks.size());
    /*DEBUG*/// n/a

    return bRes;
}
//---------------------------------------------------------------------------
//TODO: uiSize (���-�� ������� � ����)
template<class TaskT>
uint_t
CxThreadPool<TaskT>::uiGetSize() const {
    /*DEBUG*///xASSERT_RET(CONDITION, RET_VALUE);

    uint_t uiRes = 0;

    CxAutoCriticalSection CS(_m_csList, true);

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
CxThreadPool<TaskT>::uiOnRun(void *pvParam) {
    /*DEBUG*/

    uint_t uiRes = 0;
    bool bRes  = false;

    //-------------------------------------
    //������ �������
    bRes = _m_semSemaphore.bCreate(NULL, _m_uiMaxRunningTasks, /*_m_uiMaxRunningTasks*/2048, NULL);
    /*DEBUG*/xASSERT_RET(false != bRes, 0);

    //-------------------------------------
    //������ ����
    /*DEBUG*/xASSERT(true == _m_lstpthTasks.empty());
    _m_lstpthTasks.clear();

    for ( ; ; ) {
        //-------------------------------------
        //�������� ���������� ������
        bRes = _m_semSemaphore.bWait(INFINITE);
        /*DEBUG*/xASSERT_DO(false != bRes, break);

        //-------------------------------------
        //��� �������� (���� ��������� ��� ������� - �����)
        xCHECK_DO(_m_uiCurrTask >= _m_uiNumTasks, break);
        ////xCHECK_DO(true == bIsEmpty(), break);

        //-------------------------------------
        //�� ���� �� ����� ��� ���������������
        bRes = bIsTimeToExit();
        xCHECK_DO(true == bRes, break);

        //-------------------------------------
        //������ ����. ������
        bRes = _bAddTask(NULL);                                    //_m_semSemaphore.bWait(INFINITE);
        /*DEBUG*/xASSERT_DO(false != bRes, break);                //continue ???

        ++ _m_uiCurrTask;

        /*LOG*/////_m_clLog.bWrite(xT("_m_uiCurrTask == %i, _m_uiNumTasks: %i\n"), _m_uiCurrTask, _m_uiNumTasks);
    }

    //-------------------------------------
    //���� ���� ����������� �������� ������ (���� �� ������)
    ////bRes = bWaitGroup(INFINITE/*5000*/);
    /////*DEBUG*/xASSERT_RET(false != bRes, 0);

    for (; ;) {
        xCHECK_DO(true == bIsEmpty(), break);

        bRes = bSleep(500);
        /*DEBUG*/xASSERT_DO(false != bRes, break);
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
CxThreadPool<TaskT>::_bAddTask(CxThread *pvItem) {
    /*DEBUG*/

    bool bRes = false;

    //-------------------------------------
    //������� ��������� ��������� �����
    try {
            TaskT *pthTask = new TaskT(_m_cbIsGroupPaused, _m_cbIsGroupAutoDelete);
            /*DEBUG*/xASSERT_RET(NULL != pthTask, false);

                   pthTask->m_uiIndex = _m_uiCurrTask;    /*��� �������*/
                   pthTask->vAttachHandler_OnEnter( xCLOSURE(this, &CxThreadPool::_vOnEnterTask) );
                   pthTask->vAttachHandler_OnExit ( xCLOSURE(this, &CxThreadPool::_vOnExitTask ) );

            bRes = pthTask->bCreate(_m_uiStackSize/*0*/, _m_fpFuncPtr/*0*/, _m_pvParam/*NULL*/);
            /*DEBUG*/xASSERT_RET(false != bRes, false);

            bRes = pthTask->bResume();
            /*DEBUG*/xASSERT_RET(false != bRes, false);
        {
            CxAutoCriticalSection CS(_m_csList);
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
CxThreadPool<TaskT>::_bRemoveTask(CxThread *pvItem) {
    bool bRes = false;

    try {
        TaskT *pthTask = static_cast<TaskT *>(pvItem);
        /*DEBUG*/xASSERT_RET(NULL  != pthTask,               false);
        /*DEBUG*/xASSERT_RET(false != pthTask->bIsRunning(), false);

        //-------------------------------------
        //����������� _m_semSemaphore
        if (0 == pthTask->m_ulTag) {
            bRes = _m_semSemaphore.bRelease(1, NULL);
            /*DEBUG*/xASSERT_RET(false != bRes, false);
        }

        //-------------------------------------
        //������� �� ������ ��������� �� �����
        {
            CxAutoCriticalSection CS(_m_csList);

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
CxThreadPool<TaskT>::_vOnEnterTask(CxThread *pthSender)  {
    /*DEBUG*/
    /*DEBUG*/xASSERT_DO(NULL  != pthSender,               return);
    /*DEBUG*/xASSERT_DO(false != pthSender->bIsRunning(), return);

    //...

    /*LOG*///_m_clLog.bWrite(xT("_vOnEnterTask: #%i"), pthTask->m_uiIndex);
}
//---------------------------------------------------------------------------
//TODO: _vOnExitTask (����� ������� �������)
template<class TaskT>
void
CxThreadPool<TaskT>::_vOnExitTask(CxThread *pthSender)  {
    /*DEBUG*/
    /*DEBUG*/xASSERT_DO(NULL  != pthSender,               return);
    /*DEBUG*/xASSERT_DO(false != pthSender->bIsRunning(), return);

    bool bRes = false;

    bRes = _bRemoveTask(pthSender);    //if (true == bRes)        //bRelease
    /*DEBUG*/xASSERT_DO(false != bRes, return);

    /*LOG*///_m_clLog.bWrite(xT("_vOnExitTask stop: #%i"), pthTask->m_uiIndex);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
