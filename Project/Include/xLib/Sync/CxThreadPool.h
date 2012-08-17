/**
 * \file  CxThreadPool.h
 * \brief thread pool
 */


#ifndef xLib_Sync_CxThreadPoolH
#define xLib_Sync_CxThreadPoolH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/xClosure.h>
#include <xLib/Sync/CxSemaphore.h>

#include <list>
////#include <boost\function.hpp>
////#include <boost\bind.hpp>
////#include <functional>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxCriticalSection;
class CxAutoCriticalSection;
class CxThread;

template<class TaskT>
class CxThreadPool :
    public CxThread
    /// thread pool
{
    private:
        mutable bool              _m_bRes;

        uint_t                    _m_uiStackSize;
        TFuncPtr                  _m_fpFuncPtr;
        void                     *_m_pvParam;

        const bool                _m_cbIsGroupPaused;
        const bool                _m_cbIsGroupAutoDelete;

        mutable CxSemaphore       _m_semSemaphore;
        std::list<TaskT *>        _m_lstpthTasks;

        size_t                    _m_uiMaxRunningTasks;
        size_t                    _m_uiNumTasks;
        size_t                    _m_uiCurrTask;

        //static
        static CxCriticalSection  _m_csList;
        static CxConsoleLog       _m_clLog;

        bool                      _bAddTask    (CxThread *pvItem);
        bool                      _bRemoveTask (CxThread *pvItem);

        void                      _vOnEnterTask(CxThread *pthSender);
        void                      _vOnExitTask (CxThread *pthSender);

        //WatchDog

    public:
                                  CxThreadPool (bool bIsPaused, bool bIsAutoDelete, bool bIsGroupPaused, bool bIsGroupAutoDelete);
        virtual                  ~CxThreadPool ();

        //�������� � �������
        bool                      bCreateGroup (uint_t uiStackSize, const TFuncPtr fpFuncPtr, void *pvParam, uint_t uiNumTasks, uint_t uiMaxRunningTasks);
        bool                      bResumeGroup ();
        bool                      bPauseGroup  ();
        bool                      bExitGroup   (ulong_t ulTimeout);
        bool                      bKillGroup   (ulong_t ulTimeout);
        bool                      bWaitGroup   (ulong_t ulTimeout);

        size_t                    uiGetMaxTasks() const;
        bool                      bSetMaxTasks (uint_t uiNum);

        size_t                    uiGetNumTasks() const;
        bool                      bSetNumTasks (uint_t uiNum);

        bool                      bIsEmpty     () const;
        bool                      bIsFull      () const;
        size_t                    uiGetSize    () const;

        //������

    protected:
        virtual uint_t            uiOnRun      (void *pvParam);    /*overload*/
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include <xLib/Sync/CxCriticalSection.h>
#include <xLib/Sync/CxAutoCriticalSection.h>
#include <xLib/Sync/CxThread.h>
#include <Sync/CxThreadPool.inl>

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

m_bRes = thpTP->bCreateGroup(0, (uint_t (WINAPI *)(void *))&CTest::s_uiThreadFunc, NULL);
*/
