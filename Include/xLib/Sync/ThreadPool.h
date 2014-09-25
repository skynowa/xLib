/**
 * \file  ThreadPool.h
 * \brief thread pool
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Sync/IpcSemaphore.h>
#include <xLib/Sync/Thread.h>

#include <list>

////#include <boost\function.hpp>
////#include <boost\bind.hpp>
////#include <functional>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class Mutex;
class AutoMutex;
class Thread;

template<class T>
class ThreadPool :
    public Thread
    /// thread pool
{
public:
    typedef void_t (T::*func_ptr_t)(void_t *);

    // construct? destruct
                           ThreadPool(cbool_t &isPaused, cbool_t &isAutoDelete,
                               cbool_t &isGroupPaused, cbool_t &isGroupAutoDelete);
    virtual               ~ThreadPool();

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

    mutable IpcSemaphore _semaphore;
    std::list<T *>         _tasks;

    size_t                 _maxRunningTasks;
    size_t                 _numTasks;
    size_t                 _currTask;

    //static
    static Mutex         _s_mutex;
    static Trace         _s_log;

    void_t                 _taskAdd(Thread *item);
    void_t                 _taskRemove(Thread *item);

    void_t                 _onEnterTask(Thread *sender);
    void_t                 _onExitTask(Thread *sender);

    // WatchDog

    xNO_COPY_ASSIGN(ThreadPool)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "ThreadPool.inl"
#endif
