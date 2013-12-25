/**
 * \file  CxThreadPool.h
 * \brief thread pool
 */


#pragma once

#ifndef xLib_CxThreadPoolH
#define xLib_CxThreadPoolH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Sync/CxIpcSemaphore.h>
#include <xLib/Sync/CxThread.h>

#include <list>

////#include <boost\function.hpp>
////#include <boost\bind.hpp>
////#include <functional>
//-------------------------------------------------------------------------------------------------
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
    typedef void_t (T::*func_ptr_t)(void_t *);

    // construct? destruct
                           CxThreadPool(cbool_t &isPaused, cbool_t &isAutoDelete,
                               cbool_t &isGroupPaused, cbool_t &isGroupAutoDelete);
    virtual               ~CxThreadPool();

    // groups
    void_t                 groupCreate(cuint_t &stackSize, const func_ptr_t funcPtr, void_t *param,
                               std::csize_t &numTasks, std::csize_t &maxRunningTasks);
    void_t                 groupResume();
    void_t                 groupPause();
    void_t                 groupExit(culong_t &timeoutMsec);
    void_t                 groupKill(culong_t &timeoutMsec);
    void_t                 groupWait(culong_t &timeoutMsec);

    size_t                 maxTasks() const xWARN_UNUSED_RV;
    void_t                 setMaxTasks(std::csize_t &num);

    size_t                 numTasks() const xWARN_UNUSED_RV;
    void_t                 setNumTasks(std::csize_t &num);

    bool_t                 isEmpty() const;
    bool_t                 isFull() const;
    size_t                 size() const xWARN_UNUSED_RV;

protected:
    virtual uint_t         onRun(void_t *param) xOVERRIDE xWARN_UNUSED_RV;

private:
    uint_t                 _stackSize;
    func_ptr_t             _funcPtr;
    void_t                *_param;

    cbool_t                _isGroupPaused;
    cbool_t                _isGroupAutoDelete;

    mutable CxIpcSemaphore _semaphore;
    std::list<T *>         _tasks;

    size_t                 _maxRunningTasks;
    size_t                 _numTasks;
    size_t                 _currTask;

    //static
    static CxMutex         _s_mutex;
    static CxTrace         _s_log;

    void_t                 _taskAdd(CxThread *item);
    void_t                 _taskRemove(CxThread *item);

    void_t                 _onEnterTask(CxThread *sender);
    void_t                 _onExitTask(CxThread *sender);

    // WatchDog

    xNO_COPY_ASSIGN(CxThreadPool)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxThreadPool.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxThreadPoolH
