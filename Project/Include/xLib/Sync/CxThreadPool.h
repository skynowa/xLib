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

template<typename T>
class CxThreadPool :
    public CxThread
    /// thread pool
{
public:
    typedef void (T::*func_ptr_t)(void *);

    // construct? destruct
                           CxThreadPool(const bool &cbIsPaused, const bool &cbIsAutoDelete,
                                         const bool &cbIsGroupPaused, const bool &cbIsGroupAutoDelete);
    virtual               ~CxThreadPool();

    // groups
    void                   groupCreate (const uint_t &cuiStackSize, const func_ptr_t fpFuncPtr, void *pvParam,
                                         const size_t &cuiNumTasks, const size_t &cuiMaxRunningTasks);
    void                   groupResume ();
    void                   groupPause  ();
    void                   groupExit   (const ulong_t &culTimeout);
    void                   groupKill   (const ulong_t &culTimeout);
    void                   groupWait   (const ulong_t &culTimeout);

    size_t                 maxTasks    () const xWARN_UNUSED_RESULT;
    void                   setMaxTasks (const size_t &cuiNum);

    size_t                 numTasks    () const xWARN_UNUSED_RESULT;
    void                   setNumTasks (const size_t &cuiNum);

    bool                   isEmpty     () const;
    bool                   isFull      () const;
    size_t                 size        () const xWARN_UNUSED_RESULT;

protected:
    virtual uint_t         onRun       (void *pvParam) xOVERRIDE xWARN_UNUSED_RESULT;

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

    void                   _taskAdd    (CxThread *pvItem);
    void                   _taskRemove (CxThread *pvItem);

    void                   _onEnterTask(CxThread *pthSender);
    void                   _onExitTask (CxThread *pthSender);

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
