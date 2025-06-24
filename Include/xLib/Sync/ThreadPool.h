/**
 * \file  ThreadPool.h
 * \brief thread pool
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Sync/Thread.h>
#include <xLib/Sync/ThreadCurrent.h>
#include <xLib/Sync/IpcSemaphore.h>
#include <xLib/Sync/Mutex.h>
#include <xLib/Log/LogStream.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

template<typename TaskT>
class ThreadPool :
    public Thread
    /// thread pool
{
public:
    using func_ptr_t = void_t (TaskT::*)(void_t *);

///\name ctors, dtor
///\{
			 ThreadPool(cbool_t isPaused, cbool_t isAutoDelete, cbool_t isGroupPaused,
				cbool_t isGroupAutoDelete);
	virtual ~ThreadPool();

    xNO_DEFAULT_CONSTRUCT(ThreadPool);
    xNO_COPY_ASSIGN(ThreadPool);
///\}

    // groups
    void_t      groupCreate(cuint_t &stackSize, const func_ptr_t funcPtr, void_t *param,
    				std::csize_t &numTasks, std::csize_t &maxRunningTasks);
    void_t      groupResume();
    void_t      groupPause();
    void_t      groupExit(culong_t &timeoutMsec);
    void_t      groupKill(culong_t &timeoutMsec);
    void_t      groupWait(culong_t &timeoutMsec);

    std::size_t maxTasks() const;
    void_t      setMaxTasks(std::csize_t &num);

    std::size_t numTasks() const;
    void_t      setNumTasks(std::csize_t &num);

    bool_t      isEmpty() const;
    bool_t      isFull() const;
    std::size_t size() const;

protected:
    uint_t      onRun(void_t *param) final;

private:
    uint_t         _stackSize {};
    func_ptr_t     _funcPtr {};
    void_t        *_param {};

    cbool_t        _isGroupPaused {};
    cbool_t        _isGroupAutoDelete {};

    mutable IpcSemaphore _semaphore;
    std::list<TaskT *> _tasks;

    std::size_t    _maxRunningTasks {};
    std::size_t    _numTasks {};
    std::size_t    _currTask {};

    // static
    static Mutex   _s_mutex;
    static Cout    _s_log;

    void_t         _taskAdd(Thread *item);
    void_t         _taskRemove(Thread *item);

    void_t         _onEnterTask(Thread *sender);
    void_t         _onExitTask(Thread *sender);

    // TODO: WatchDog
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "ThreadPool.inl"
