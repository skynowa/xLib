/**
 * \file  CxThreadPool.h
 * \brief thread pool
 */


#ifndef xLib_Sync_CxThreadPoolH
#define xLib_Sync_CxThreadPoolH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/xClosure.h>
#include <xLib/Sync/CxCriticalSection.h>
#include <xLib/Sync/CxAutoCriticalSection.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Sync/CxSemaphore.h>

#include <list>
////#include <boost\function.hpp>
////#include <boost\bind.hpp>
////#include <functional>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
template<class TaskT>
class CxThreadPool :
    public CxThread
    /// thread pool
{
    private:
        mutable BOOL              _m_bRes;

        UINT                      _m_uiStackSize;                //������ ����� �������
        TFuncPtr                  _m_fpFuncPtr;                    //����� ������� ������� �������
        VOID                     *_m_pvParam;                    //�������� ��� ������� ������� �������

        const BOOL                _m_cbIsGroupPaused;            //���� ����� �������
        const BOOL                _m_cbIsGroupAutoDelete;        //���� ������������ �������

        mutable CxSemaphore       _m_semSemaphore;                //�������
        std::list<TaskT *>        _m_lstpthTasks;                //�������

        size_t                    _m_uiMaxRunningTasks;            //����� ������������ ���������� �������
        size_t                    _m_uiNumTasks;                //����� ����� �������
        size_t                    _m_uiCurrTask;                //������ �������� �������

        //static
        static CxCriticalSection  _m_csList;                    //������������� std::list<TaskT *>
        static CxConsoleLog       _m_clLog;                        //���

        BOOL                      _bAddTask    (CxThread *pvItem);
        BOOL                      _bRemoveTask (CxThread *pvItem);

        VOID                      _vOnEnterTask(CxThread *pthSender);
        VOID                      _vOnExitTask (CxThread *pthSender);

        //WatchDog

    public:
                                  CxThreadPool (BOOL bIsPaused, BOOL bIsAutoDelete, BOOL bIsGroupPaused, BOOL bIsGroupAutoDelete);
        virtual                  ~CxThreadPool ();

        //�������� � �������
        BOOL                      bCreateGroup (UINT uiStackSize, const TFuncPtr fpFuncPtr, VOID *pvParam, UINT uiNumTasks, UINT uiMaxRunningTasks);
        BOOL                      bResumeGroup ();
        BOOL                      bPauseGroup  ();
        BOOL                      bExitGroup   (ULONG ulTimeout);
        BOOL                      bKillGroup   (ULONG ulTimeout);
        BOOL                      bWaitGroup   (ULONG ulTimeout);

        size_t                    uiGetMaxTasks() const;
        BOOL                      bSetMaxTasks (UINT uiNum);

        size_t                    uiGetNumTasks() const;
        BOOL                      bSetNumTasks (UINT uiNum);

        BOOL                      bIsEmpty     () const;
        BOOL                      bIsFull      () const;
        size_t                    uiGetSize    () const;

        //������

    protected:
        virtual UINT              uiOnRun      (VOID *pvParam);    /*overload*/
};
//---------------------------------------------------------------------------
#include <Sync/CxThreadPool.inl>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxThreadPoolH




/****************************************************************************
*    FAQ
*
*****************************************************************************/

/*
    1. ������� ������ CxThreadPool
    2. ������� ����� CxWorkThread::CxThread
    3. �������� ������ CxWorkThread::CxThread
*/

/*
����� ������������ ������ ������:

m_bRes = thpTP->bCreateGroup(0, (UINT (WINAPI *)(VOID *))&CTest::s_uiThreadFunc, NULL);
*/
