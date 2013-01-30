/**
 * \file  CxIpcSemaphore.h
 * \brief semaphore (interprocess)
 */


#ifndef xLib_Sync_CxIpcSemaphoreH
#define xLib_Sync_CxIpcSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//---------------------------------------------------------------------------
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

    const handle_t & hHandle       () const;
        ///< get handle
    void             create       (const long_t &cliInitialValue, const std::tstring_t &csName);
        ///< create
    void             vOpen         (const std::tstring_t &csName);
        ///< open
    void             vPost         () const;
        ///< release
    void             vWait         (const ulong_t &culTimeoutMsec) const;
        ///< wait
    long_t           liValue       () const;
        ///< get value

private:
    handle_t         _m_hHandle;
    std::tstring_t   _m_sName;

    bool             _bIsValid     () const;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Sync_CxIpcSemaphoreH

/*
    SysV  semaphores are semget/semop/semctl
    POSIX semaphores are sem_open/sem_close/sem_*

*/
