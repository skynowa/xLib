/**
 * \file  CxThreadPool.h
 * \brief thread pool
 */


#pragma once

#include <xLib/Core/xCore.h>
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
    typedef void_t (T::*func_ptr_t)(void_t *);

    // construct? destruct
                           CxThreadPool(cbool_t &cbIsPaused, cbool_t &cbIsAutoDelete,
                                        cbool_t &cbIsGroupPaused, cbool_t &cbIsGroupAutoDelete);
    virtual               ~CxThreadPool();

    // groups
    void_t                 groupCreate(cuint_t &cuiStackSize, const func_ptr_t fpFuncPtr,
                               void_t *pvParam, std::csize_t &cuiNumTasks,
                               std::csize_t &cuiMaxRunningTasks);
    void_t                 groupResume();
    void_t                 groupPause();
    void_t                 groupExit(culong_t &culTimeout);
    void_t                 groupKill(culong_t &culTimeout);
    void_t                 groupWait(culong_t &culTimeout);

    size_t                 maxTasks() const xWARN_UNUSED_RV;
    void_t                 setMaxTasks(std::csize_t &cuiNum);

    size_t                 numTasks() const xWARN_UNUSED_RV;
    void_t                 setNumTasks(std::csize_t &cuiNum);

    bool_t                 isEmpty() const;
    bool_t                 isFull() const;
    size_t                 size() const xWARN_UNUSED_RV;

protected:
    virtual uint_t         onRun(void_t *pvParam) xOVERRIDE xWARN_UNUSED_RV;

private:
    uint_t                 _m_uiStackSize;
    func_ptr_t             _m_fpFuncPtr;
    void_t                  *_m_pvParam;

    cbool_t                _m_cbIsGroupPaused;
    cbool_t                _m_cbIsGroupAutoDelete;

    mutable CxIpcSemaphore _m_semSemaphore;
    std::list<T *>         _m_lthTasks;

    size_t                 _m_uiMaxRunningTasks;
    size_t                 _m_uiNumTasks;
    size_t                 _m_uiCurrTask;

    //static
    static CxMutex         _m_mtList;
    static CxTracer        _m_clLog;

    void_t                 _taskAdd(CxThread *pvItem);
    void_t                 _taskRemove(CxThread *pvItem);

    void_t                 _onEnterTask(CxThread *pthSender);
    void_t                 _onExitTask(CxThread *pthSender);

    // WatchDog
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#include <xLib/Sync/CxMutex.h>
#include <xLib/Sync/CxAutoMutex.h>
#include <xLib/Sync/CxThread.h>

#include "CxThreadPool.inl"
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif
