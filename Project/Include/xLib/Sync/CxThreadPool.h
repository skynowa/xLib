/**
 * \file  CxThreadPool.h
 * \brief thread pool
 */


#ifndef xLib_Sync_CxThreadPoolH
#define xLib_Sync_CxThreadPoolH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxIpcSemaphore.h>
#include <xLib/Sync/CxThread.h>

#include <list>

////#include <boost\function.hpp>
////#include <boost\bind.hpp>
////#include <functional>
//------------------------------------------------------------------------------
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
                           CxThreadPool(cbool_t &cbIsPaused, cbool_t &cbIsAutoDelete,
                                         cbool_t &cbIsGroupPaused, cbool_t &cbIsGroupAutoDelete);
    virtual               ~CxThreadPool();

    // groups
    void                   groupCreate (cuint_t &cuiStackSize, const func_ptr_t fpFuncPtr, void *pvParam,
                                         const size_t &cuiNumTasks, const size_t &cuiMaxRunningTasks);
    void                   groupResume ();
    void                   groupPause  ();
    void                   groupExit   (culong_t &culTimeout);
    void                   groupKill   (culong_t &culTimeout);
    void                   groupWait   (culong_t &culTimeout);

    size_t                 maxTasks    () const xWARN_UNUSED_RV;
    void                   setMaxTasks (const size_t &cuiNum);

    size_t                 numTasks    () const xWARN_UNUSED_RV;
    void                   setNumTasks (const size_t &cuiNum);

    bool_t                   isEmpty     () const;
    bool_t                   isFull      () const;
    size_t                 size        () const xWARN_UNUSED_RV;

protected:
    virtual uint_t         onRun       (void *pvParam) xOVERRIDE xWARN_UNUSED_RV;

private:
    uint_t                 _m_uiStackSize;
    func_ptr_t             _m_fpFuncPtr;
    void                  *_m_pvParam;

    cbool_t             _m_cbIsGroupPaused;
    cbool_t             _m_cbIsGroupAutoDelete;

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
//------------------------------------------------------------------------------
#include <xLib/Sync/CxMutex.h>
#include <xLib/Sync/CxAutoMutex.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Sync/CxCurrentThread.h>

#include "CxThreadPool.inl"
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxThreadPoolH
