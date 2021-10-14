/**
 * \file  Event.h
 * \brief event (using between threads)
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class Event
    /// event
{
public:
#if   xENV_WIN
    using handle_t = HANDLE;           ///< handle
#elif xENV_UNIX
    using handle_t = pthread_cond_t;   ///< handle
#endif

    enum class ObjectState : ulong_t
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

///@name ctors, dtor
///@{
			 Event(cbool_t isAutoReset, cbool_t isSignaled);
	virtual ~Event();

	xNO_DEFAULT_CONSTRUCT(Event)
	xNO_COPY_ASSIGN(Event)
///@}

    const handle_t & handle() const;
        ///< get handle
    void_t           create();
        ///< create
    void_t           set();
        ///< signal the event for the waiting thread (!!! unlock !!!)
    void_t           reset();
        ///< once signaled, the event class must be "reset" before responding to a new signal
    ObjectState      wait(culong_t &timeoutMs = xTIMEOUT_INFINITE);
        ///< wait either for the Event to be signaled by another thread or for the specified
        ///< timeout duration
    bool_t           isSignaled() const;
        ///< is signaled

private:
#if   xENV_WIN
    Handle           _event;            ///< event
#elif xENV_UNIX
    pthread_mutex_t  _mutex {};         ///< mutex
    handle_t         _cond {};          ///< condition variable
    bool_t           _isSignaled {};    ///< is signaled flag
#endif

    cbool_t          _isAutoReset {};   ///< auto-reset flag
    cbool_t          _initState {};     ///< initial state

xPLATFORM_IMPL:
    void_t           _dectruct_impl();
    const handle_t & _handle_impl() const;
    void_t           _create_impl();
    void_t           _set_impl();
    void_t           _reset_impl();
    ObjectState      _wait_impl(culong_t &timeoutMs = xTIMEOUT_INFINITE);
    bool_t           _isSignaled_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
