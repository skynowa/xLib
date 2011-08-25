/**
 * \file  CxThreadPool.inl
 * \brief thread pool
 */


/****************************************************************************
*    public
*
*****************************************************************************/

#if defined(xOS_WIN)
//---------------------------------------------------------------------------
template<class TaskT>
CxCriticalSection CxThreadPool<TaskT>::_m_csList;

template<class TaskT>
CxConsoleLog      CxThreadPool<TaskT>::_m_clLog(FALSE);
//---------------------------------------------------------------------------
//DONE: CxThreadPool (�����������)
template<class TaskT>
CxThreadPool<TaskT>::CxThreadPool(BOOL bIsPaused,      BOOL bIsAutoDelete,
                                  BOOL bIsGroupPaused, BOOL bIsGroupAutoDelete
) :
    CxThread              (bIsPaused, bIsAutoDelete),
    _m_bRes               (FALSE),
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
BOOL
CxThreadPool<TaskT>::bCreateGroup(UINT uiStackSize, const TFuncPtr fpFuncPtr, VOID *pvParam, UINT uiNumTasks, UINT uiMaxRunningTasks) {
    /*DEBUG*/xASSERT_RET(0    <= uiStackSize,       FALSE);    //TODO: MaxValue
    /*DEBUG*/xASSERT_RET(NULL == fpFuncPtr,         FALSE);
    /*DEBUG*/xASSERT_RET(NULL != pvParam,           FALSE);
    /*DEBUG*/xASSERT_RET(0    <  uiNumTasks,        FALSE);
    /*DEBUG*/xASSERT_RET(0    <  uiMaxRunningTasks, FALSE);

    BOOL bRes = FALSE;

    xCHECK_DO(TRUE == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: is running")); return TRUE);

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
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bResumeGroup (�������������)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::bResumeGroup() {
    /*DEBUG*/

    BOOL bRes = FALSE;

    xCHECK_DO(FALSE == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return TRUE);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(FALSE == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRes = (*it)->bResume();
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }
    }

    //-------------------------------------
    //���
    bRes = bResume();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bPauseGroup (������������)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::bPauseGroup() {
    /*DEBUG*/

    BOOL bRes = FALSE;

    xCHECK_DO(FALSE == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return TRUE);

    //-------------------------------------
    //���
    bRes = bPause();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(FALSE == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRes = (*it)->bPause();
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bExitGroup (�����)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::bExitGroup(ULONG ulTimeout) {
    /*DEBUG*/

    BOOL bRes = FALSE;

    xCHECK_DO(FALSE == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return TRUE);

    //-------------------------------------
    //���
    bRes = bExit(ulTimeout/*INFINITE*/);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(FALSE == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); continue);

            bRes = (*it)->bExit(ulTimeout);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: uiKillGroup (����������)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::bKillGroup(ULONG ulTimeout) {
    /*DEBUG*/xASSERT_RET(NULL != this, FALSE);

    BOOL bRes = FALSE;

    xCHECK_DO(FALSE == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return TRUE);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(FALSE == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRes = (*it)->bKill(ulTimeout);
            /////*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }
    }

    //-------------------------------------
    //���
    bRes = bKill(ulTimeout);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWaitGroup (�������� ����������)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::bWaitGroup(ULONG ulTimeout) {
    /*DEBUG*/

    BOOL bRes = FALSE;

    xCHECK_DO(FALSE == bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("CxThreadPool: not running")); return TRUE);

    //-------------------------------------
    //������� ������
    {
        CxAutoCriticalSection CS(_m_csList);

        for (std::list<TaskT *>::iterator it = _m_lstpthTasks.begin();  it != _m_lstpthTasks.end();  ++ it)    {
            xCHECK_DO(FALSE == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            bRes = (*it)->bWait(ulTimeout);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }
    }

    //-------------------------------------
    //��� - !�������� ������ ����!
    //--bRes = bWait(ulTimeout);
    //--xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public:
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: uiGetMaxTasks (���-�� ������������ ���������� �������)
template<class TaskT>
UINT
CxThreadPool<TaskT>::uiGetMaxTasks() const {
    /*DEBUG*/// n/a

    return _m_uiMaxRunningTasks;
}
//---------------------------------------------------------------------------
//TODO: bSetMaxTasks (��������� ���-�� ������������ ���������� �������)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::bSetMaxTasks(UINT uiNum)  {
    /*DEBUG*/// n/a

    BOOL bRes = FALSE;

    //-------------------------------------
    //���������� (���� ������� uiNum �������)
    if (_m_uiMaxRunningTasks < uiNum) {
        //������� ���� �������� � _m_uiMaxRunningTasks, ���� ���� uiNum
        size_t uiTasksForInc = uiNum - _m_uiMaxRunningTasks;

        bRes = _m_semSemaphore.bRelease(uiTasksForInc, NULL);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        _m_uiMaxRunningTasks = uiNum;

        return TRUE;
    }

    //-------------------------------------
    //���������� (��������� ���-�� ������� + ��������� std::list)
    if (_m_uiMaxRunningTasks > uiNum) {
        CxAutoCriticalSection CS(_m_csList);

        size_t uiCount       = 0;
        size_t uiTasksForDec = _m_uiMaxRunningTasks - uiNum;

        for (std::list<TaskT *>::reverse_iterator it = _m_lstpthTasks.rbegin(); it != _m_lstpthTasks.rend(); ++ it)    {
            xCHECK_DO(FALSE == (*it)->bIsRunning(), /*LOG*/_m_clLog.bWrite(xT("Not running")); continue);

            //��������� ����� - �� ����������� �������
            ::InterlockedExchange(&((*it)->m_ulTag), 1);

            bRes = (*it)->bExit(/*ulTimeout*/5000);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

            ++ uiCount;
            xCHECK_DO(uiCount >= uiTasksForDec, break);
        }

        _m_uiMaxRunningTasks = uiNum;

        return TRUE;
    }

    //-------------------------------------
    //������ �� ������, �.�. ���-�� ������� �� ����������
    if (_m_uiMaxRunningTasks == uiNum) {
        _m_uiMaxRunningTasks = uiNum;

        return TRUE;
    }

    /*DEBUG*/xASSERT_RET(FALSE, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: uiGetNumTasks (����� �������)
template<class TaskT>
UINT
CxThreadPool<TaskT>::uiGetNumTasks() const {
    /*DEBUG*/// n/a

    return _m_uiNumTasks;
}
//---------------------------------------------------------------------------
//TODO: bSetNumTasks (��������� ���-�� �������)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::bSetNumTasks(UINT uiNum) {
    /*DEBUG*/// n/a

    _m_uiNumTasks = uiNum;

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bIsEmpty (���� �� ���)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::bIsEmpty() const {
    /*DEBUG*/

    BOOL bRes = TRUE;

    CxAutoCriticalSection CS(_m_csList);

    bRes = _m_lstpthTasks.empty();
    /*DEBUG*/// n/a

    return bRes;
}
//---------------------------------------------------------------------------
//TODO: bIsFull (�������� �� ���)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::bIsFull() const {
    /*DEBUG*///xASSERT_RET(CONDITION, RET_VALUE);

    BOOL bRes = FALSE;

    CxAutoCriticalSection CS(_m_csList, TRUE);

    /*DEBUG*/xASSERT_RET(_m_uiMaxRunningTasks < _m_lstpthTasks.size(), TRUE);

    bRes = (_m_uiMaxRunningTasks == _m_lstpthTasks.size());
    /*DEBUG*/// n/a

    return bRes;
}
//---------------------------------------------------------------------------
//TODO: uiSize (���-�� ������� � ����)
template<class TaskT>
UINT
CxThreadPool<TaskT>::uiGetSize() const {
    /*DEBUG*///xASSERT_RET(CONDITION, RET_VALUE);

    UINT uiRes = 0;

    CxAutoCriticalSection CS(_m_csList, TRUE);

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
UINT
CxThreadPool<TaskT>::uiOnRun(VOID *pvParam) {
    /*DEBUG*/

    UINT uiRes = 0;
    BOOL bRes  = FALSE;

    //-------------------------------------
    //������ �������
    bRes = _m_semSemaphore.bCreate(NULL, _m_uiMaxRunningTasks, /*_m_uiMaxRunningTasks*/2048, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, 0);

    //-------------------------------------
    //������ ����
    /*DEBUG*/xASSERT(true == _m_lstpthTasks.empty());
    _m_lstpthTasks.clear();

    for ( ; ; ) {
        //-------------------------------------
        //�������� ���������� ������
        bRes = _m_semSemaphore.bWait(INFINITE);
        /*DEBUG*/xASSERT_DO(FALSE != bRes, break);

        //-------------------------------------
        //��� �������� (���� ��������� ��� ������� - �����)
        xCHECK_DO(_m_uiCurrTask >= _m_uiNumTasks, break);
        ////xCHECK_DO(TRUE == bIsEmpty(), break);

        //-------------------------------------
        //�� ���� �� ����� ��� ���������������
        bRes = bIsTimeToExit();
        xCHECK_DO(TRUE == bRes, break);

        //-------------------------------------
        //������ ����. ������
        bRes = _bAddTask(NULL);                                    //_m_semSemaphore.bWait(INFINITE);
        /*DEBUG*/xASSERT_DO(FALSE != bRes, break);                //continue ???

        ++ _m_uiCurrTask;

        /*LOG*/////_m_clLog.bWrite(xT("_m_uiCurrTask == %i, _m_uiNumTasks: %i\n"), _m_uiCurrTask, _m_uiNumTasks);
    }

    //-------------------------------------
    //���� ���� ����������� �������� ������ (���� �� ������)
    ////bRes = bWaitGroup(INFINITE/*5000*/);
    /////*DEBUG*/xASSERT_RET(FALSE != bRes, 0);

    for (; ;) {
        xCHECK_DO(TRUE == bIsEmpty(), break);

        bRes = bSleep(500);
        /*DEBUG*/xASSERT_DO(FALSE != bRes, break);
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
BOOL
CxThreadPool<TaskT>::_bAddTask(CxThread *pvItem) {
    /*DEBUG*/

    BOOL bRes = FALSE;

    //-------------------------------------
    //������� ��������� ��������� �����
    try {
            TaskT *pthTask = new TaskT(_m_cbIsGroupPaused, _m_cbIsGroupAutoDelete);
            /*DEBUG*/xASSERT_RET(NULL != pthTask, FALSE);

                   pthTask->m_uiIndex = _m_uiCurrTask;    /*��� �������*/
                   pthTask->vAttachHandler_OnEnter( xCLOSURE(this, &CxThreadPool::_vOnEnterTask) );
                   pthTask->vAttachHandler_OnExit ( xCLOSURE(this, &CxThreadPool::_vOnExitTask ) );

            bRes = pthTask->bCreate(_m_uiStackSize/*0*/, _m_fpFuncPtr/*0*/, _m_pvParam/*NULL*/);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

            bRes = pthTask->bResume();
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        {
            CxAutoCriticalSection CS(_m_csList);
            _m_lstpthTasks.push_back(pthTask);
        }
    } catch (...) {
        /*DEBUG*/xASSERT_RET(FALSE, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bPushTask (��������� ������� � �������, ����������� ������� �������� �� 1)
template<class TaskT>
BOOL
CxThreadPool<TaskT>::_bRemoveTask(CxThread *pvItem) {
    BOOL bRes = FALSE;

    try {
        TaskT *pthTask = static_cast<TaskT *>(pvItem);
        /*DEBUG*/xASSERT_RET(NULL  != pthTask,               FALSE);
        /*DEBUG*/xASSERT_RET(FALSE != pthTask->bIsRunning(), FALSE);

        //-------------------------------------
        //����������� _m_semSemaphore
        if (0 == pthTask->m_ulTag) {
            bRes = _m_semSemaphore.bRelease(1, NULL);
            /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
        }

        //-------------------------------------
        //������� �� ������ ��������� �� �����
        {
            CxAutoCriticalSection CS(_m_csList);

            _m_lstpthTasks.remove(pthTask);
        }

        /*DEBUG*/xASSERT_RET(NULL != pthTask, FALSE);
    } catch (...) {
        /*DEBUG*/xASSERT_RET(FALSE, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: _vOnEnterTask (������ ������� �������)
template<class TaskT>
VOID
CxThreadPool<TaskT>::_vOnEnterTask(CxThread *pthSender)  {
    /*DEBUG*/
    /*DEBUG*/xASSERT_DO(NULL  != pthSender,               return);
    /*DEBUG*/xASSERT_DO(FALSE != pthSender->bIsRunning(), return);

    //...

    /*LOG*///_m_clLog.bWrite(xT("_vOnEnterTask: #%i"), pthTask->m_uiIndex);
}
//---------------------------------------------------------------------------
//TODO: _vOnExitTask (����� ������� �������)
template<class TaskT>
VOID
CxThreadPool<TaskT>::_vOnExitTask(CxThread *pthSender)  {
    /*DEBUG*/
    /*DEBUG*/xASSERT_DO(NULL  != pthSender,               return);
    /*DEBUG*/xASSERT_DO(FALSE != pthSender->bIsRunning(), return);

    BOOL bRes = FALSE;

    bRes = _bRemoveTask(pthSender);    //if (TRUE == bRes)        //bRelease
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);

    /*LOG*///_m_clLog.bWrite(xT("_vOnExitTask stop: #%i"), pthTask->m_uiIndex);
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
