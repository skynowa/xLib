/**
 * \file  CxIpcSemaphore.h
 * \brief semaphore (interprocess)
 */


#pragma once

#ifndef xLib_CxIpcSemaphoreH
#define xLib_CxIpcSemaphoreH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxIpcSemaphore :
    public CxNonCopyable
    /// semaphore (interprocess)
{
public:
#if xOS_ENV_WIN
    typedef CxHandle handle_t;
#else
    typedef sem_t *  handle_t;
#endif

                     CxIpcSemaphore();
    virtual         ~CxIpcSemaphore();

    const handle_t & handle() const xWARN_UNUSED_RV;
        ///< get handle
    void_t           create(clong_t &initialValue, std::ctstring_t &name);
        ///< create
    void_t           open(std::ctstring_t &name);
        ///< open
    void_t           post() const;
        ///< release
    void_t           wait(culong_t &timeoutMsec) const;
        ///< wait
    long_t           value() const xWARN_UNUSED_RV;
        ///< get value

private:
    handle_t         _handle;
    std::tstring_t   _name;

    bool_t           _isValid() const xWARN_UNUSED_RV;
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Sync/CxIpcSemaphore.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxIpcSemaphoreH


/*
    SysV  semaphores are semget/semop/semctl
    POSIX semaphores are sem_open/sem_close/sem_*
*/
