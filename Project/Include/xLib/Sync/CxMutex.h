/**
 * \file  CxMutex.h
 * \brief critical section (using between threads)
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxNonCopyable.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMutex :
    public CxNonCopyable
    /// critical section
{
public:
#if xOS_ENV_WIN
    typedef CRITICAL_SECTION handle_t;
#else
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
};
//------------------------------------------------------------------------------
xNAMESPACE_END(NxLib)

#if xXLIB_HEADER_ONLY
    #include <Sync/CxMutex.cpp>
#endif
