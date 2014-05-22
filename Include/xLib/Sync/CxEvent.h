/**
 * \file  CxEvent.h
 * \brief event (using between threads)
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class CxEvent
    /// event
{
public:
#if   xENV_WIN
    typedef CxHandle       handle_t;   ///< handle
#elif xENV_UNIX
    typedef pthread_cond_t handle_t;   ///< handle
#endif

    enum ExObjectState
        /// current object state
    {
        #if   xENV_WIN
            osSignaled = WAIT_OBJECT_0, ///< signaled
            osTimeout  = WAIT_TIMEOUT,  ///< time-out interval elapsed and the object's state is nonsignaled
            osFailed   = WAIT_FAILED    ///< failed
        #elif xENV_UNIX
            osSignaled = 0,             ///< signaled
            osTimeout  = ETIMEDOUT,     ///< time-out interval elapsed and the object's state is nonsignaled
            osFailed /* other values */ ///< failed
        #endif
    };


                     CxEvent(cbool_t &isAutoReset, cbool_t &isSignaled);
        ///< constructor
    virtual         ~CxEvent();
        ///< destructor

    const handle_t & handle() const xWARN_UNUSED_RV;
        ///< get handle
    void_t           create();
        ///< create
    void_t           set();
        ///< signal the event for the waiting thread (!!! unlock !!!)
    void_t           reset();
        ///< once signaled, the event class must be "reset" before responding to a new signal
    ExObjectState    wait(culong_t &timeoutMs = xTIMEOUT_INFINITE) xWARN_UNUSED_RV;
        ///< wait either for the CxEvent to be signaled by another thread or for the specified
        ///< timeout duration
    bool_t           isSignaled() const xWARN_UNUSED_RV;
        ///< is signaled

private:
#if   xENV_WIN
    CxHandle         _event;        ///< event
#elif xENV_UNIX
    pthread_mutex_t  _mutex;       ///< mutex
    handle_t         _cond;       ///< condition variable
    bool_t           _isSignaled;   ///< is signaled flag
#endif

    cbool_t          _isAutoReset; ///< auto-reset flag
    cbool_t          _initState;   ///< initial state

    xNO_COPY_ASSIGN(CxEvent)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxEvent.inl"
