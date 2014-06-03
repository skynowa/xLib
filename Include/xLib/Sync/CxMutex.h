/**
 * \file  CxMutex.h
 * \brief mutex
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class CxMutex
    /// critical section
{
public:
#if   xENV_WIN
    typedef CRITICAL_SECTION handle_t;
#elif xENV_UNIX
    typedef pthread_mutex_t  handle_t;
#endif

                     CxMutex() {}
        ///< constructor
    virtual         ~CxMutex();
        ///< destructor

    const handle_t & handle() const xWARN_UNUSED_RV;
        ///< get handle
    void_t           create();
        ///< create
    void_t           lock();
        ///< lock
    bool_t           tryLock() xWARN_UNUSED_RV;
        ///< try lock
    void_t           unlock();
        ///< unlock

private:
    handle_t         _handle;   ///< mutex native handle

    xNO_COPY_ASSIGN(CxMutex)

xPLATFORM:
    void_t           _destruc_impl();
    void_t           _create_impl();
    void_t           _lock_impl();
    bool_t           _tryLock_impl() xWARN_UNUSED_RV;
    void_t           _unlock_impl();

};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxMutex.inl"
