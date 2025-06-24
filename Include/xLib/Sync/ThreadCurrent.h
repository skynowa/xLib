/**
 * \file  ThreadCurrent.h
 * \brief Current thread
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/Sync/Thread.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class ThreadCurrent
    /// Current thread
{
public:
    static bool_t           isCurrent(Thread::cid_t id);
        ///< is current id
    static Thread::id_t     id();
        ///< get the thread identifier of the calling thread
    static Thread::handle_t handle();
        ///< get pseudo handle for the calling thread
    static void_t           yield();
        ///< yield
    static void_t           sleep(culong_t timeoutMsec);
        ///< sleep

xPLATFORM_IMPL:
    static bool_t           _isCurrent_impl(Thread::cid_t &id);
    static Thread::id_t     _id_impl();
    static Thread::handle_t _handle_impl();
    static void_t           _yield_impl();
    static void_t           _sleep_impl(culong_t timeoutMsec);
};

} // namespace
//-------------------------------------------------------------------------------------------------
