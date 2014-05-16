/**
 * \file  CxMutex.h
 * \brief mutex
 */


#pragma once

#ifndef xLib_CxMutexH
#define xLib_CxMutexH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, sync)

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
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_END(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxMutex.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxMutexH
