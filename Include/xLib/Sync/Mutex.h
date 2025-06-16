/**
 * \file  Mutex.h
 * \brief mutex
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class Mutex
    /// critical section
{
public:
#if   xENV_WIN
    using handle_t = CRITICAL_SECTION;
#elif xENV_UNIX
    using handle_t = pthread_mutex_t;
#endif

///\name ctors, dtor
///\{
			 Mutex() = default;
	virtual ~Mutex();

	xNO_COPY_ASSIGN(Mutex);
///\}

    const handle_t & handle() const;
        ///< get handle
    void_t           create();
        ///< create
    void_t           lock();
        ///< lock
    bool_t           tryLock();
        ///< try lock
    void_t           unlock();
        ///< unlock

private:
    handle_t _handle {};   ///< mutex native handle

xPLATFORM_IMPL:
    void_t _dtor_impl();
    void_t _create_impl();
    void_t _lock_impl();
    bool_t _tryLock_impl();
    void_t _unlock_impl();

};
//-------------------------------------------------------------------------------------------------
} // namespace
//-------------------------------------------------------------------------------------------------
