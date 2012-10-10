/**
 * \file  CxThreadPool.h
 * \brief thread pool
 */


#ifndef xLib_Sync_CxThreadPoolH
#define xLib_Sync_CxThreadPoolH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxIpcSemaphore.h>
#include <xLib/Sync/CxThread.h>

#include <list>

////#include <boost\function.hpp>
////#include <boost\bind.hpp>
////#include <functional>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMutex;
class CxAutoMutex;
class CxThread;

template<class T>
class CxThreadPool :
    public CxThread
    /// thread pool
{
    public:
        typedef void (T::*func_ptr_t)(void *);

        // construct? destruct
                               CxThreadPool (const bool &cbIsPaused, const bool &cbIsAutoDelete,
                                             const bool &cbIsGroupPaused, const bool &cbIsGroupAutoDelete);
        virtual               ~CxThreadPool ();

        // groups
        void                   vGroupCreate (const uint_t &cuiStackSize, const func_ptr_t fpFuncPtr, void *pvParam,
                                             const size_t &cuiNumTasks, const size_t &cuiMaxRunningTasks);
        void                   vGroupResume ();
        void                   vGroupPause  ();
        void                   vGroupExit   (const ulong_t &culTimeout);
        void                   vGroupKill   (const ulong_t &culTimeout);
        void                   vGroupWait   (const ulong_t &culTimeout);

        size_t                 uiMaxTasks   () const;
        void                   vSetMaxTasks (const size_t &cuiNum);

        size_t                 uiNumTasks   () const;
        void                   vSetNumTasks (const size_t &cuiNum);

        bool                   bIsEmpty     () const;
        bool                   bIsFull      () const;
        size_t                 uiSize       () const;

    protected:
        virtual uint_t         uiOnRun      (void *pvParam);    /* overload */

    private:
        uint_t                 _m_uiStackSize;
        func_ptr_t             _m_fpFuncPtr;
        void                  *_m_pvParam;

        const bool             _m_cbIsGroupPaused;
        const bool             _m_cbIsGroupAutoDelete;

        mutable CxIpcSemaphore _m_semSemaphore;
        std::list<T *>         _m_lthTasks;

        size_t                 _m_uiMaxRunningTasks;
        size_t                 _m_uiNumTasks;
        size_t                 _m_uiCurrTask;

        //static
        static CxMutex         _m_mtList;
        static CxTracer        _m_clLog;

        void                   _vTaskAdd    (CxThread *pvItem);
        void                   _vTaskRemove (CxThread *pvItem);

        void                   _vOnEnterTask(CxThread *pthSender);
        void                   _vOnExitTask (CxThread *pthSender);

        //WatchDog

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include <xLib/Sync/CxMutex.h>
#include <xLib/Sync/CxAutoMutex.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Sync/CxCurrentThread.h>

#include "CxThreadPool.inl"
//---------------------------------------------------------------------------
#endif // xLib_Sync_CxThreadPoolH
