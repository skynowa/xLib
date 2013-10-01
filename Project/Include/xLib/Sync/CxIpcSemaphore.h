/**
 * \file  CxIpcSemaphore.h
 * \brief semaphore (interprocess)
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxHandleT.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxIpcSemaphore :
    private CxNonCopyable
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

    const handle_t & handle        () const xWARN_UNUSED_RV;
        ///< get handle
    void_t           create        (clong_t &cliInitialValue, std::ctstring_t &csName);
        ///< create
    void_t           open          (std::ctstring_t &csName);
        ///< open
    void_t           post          () const;
        ///< release
    void_t           wait          (culong_t &culTimeoutMsec) const;
        ///< wait
    long_t           value         () const xWARN_UNUSED_RV;
        ///< get value

private:
    handle_t         _m_hHandle;
    std::tstring_t   _m_sName;

    bool_t           _isValid      () const xWARN_UNUSED_RV;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------

/*
    SysV  semaphores are semget/semop/semctl
    POSIX semaphores are sem_open/sem_close/sem_*
*/
