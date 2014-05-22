/**
 * \file  CxIpcSemaphore.h
 * \brief semaphore
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, sync)

class CxIpcSemaphore
    /// semaphore (interprocess)
{
public:
#if   xENV_WIN
    typedef CxHandle handle_t;
#elif xENV_UNIX
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

    xNO_COPY_ASSIGN(CxIpcSemaphore)
};

xNAMESPACE_END2(xlib, sync)
//-------------------------------------------------------------------------------------------------
#include "CxIpcSemaphore.inl"


/*
    SysV  semaphores are semget/semop/semctl
    POSIX semaphores are sem_open/sem_close/sem_*
*/
