/**
 * \file  CxIpcSemaphore.h
 * \brief semaphore (interprocess)
 */


#ifndef xLib_Sync_CxIpcSemaphoreH
#define xLib_Sync_CxIpcSemaphoreH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxIpcSemaphore :
    private CxNonCopyable
    /// semaphore (interprocess)
{
public:
#if   xOS_ENV_WIN
    typedef CxHandle handle_t;
#elif xOS_ENV_UNIX
    typedef sem_t *  handle_t;
#endif

                     CxIpcSemaphore();
    virtual         ~CxIpcSemaphore();

    const handle_t & handle        () const xWARN_UNUSED_RV;
        ///< get handle
    void             create        (clong_t &cliInitialValue, const std::tstring_t &csName);
        ///< create
    void             open          (const std::tstring_t &csName);
        ///< open
    void             post          () const;
        ///< release
    void             wait          (culong_t &culTimeoutMsec) const;
        ///< wait
    long_t           value         () const xWARN_UNUSED_RV;
        ///< get value

private:
    handle_t         _m_hHandle;
    std::tstring_t   _m_sName;

    bool_t             _isValid      () const xWARN_UNUSED_RV;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxIpcSemaphoreH

/*
    SysV  semaphores are semget/semop/semctl
    POSIX semaphores are sem_open/sem_close/sem_*

*/
