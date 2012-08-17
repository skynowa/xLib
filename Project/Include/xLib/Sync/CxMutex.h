/**
 * \file  CxMutex.h
 * \brief mutex
 */


#ifndef xLib_Sync_CxMutexH
#define xLib_Sync_CxMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMutex :
    private CxNonCopyable
    /// mutex
{
    public:
    #if xOS_ENV_WIN
        typedef CxHandle  TxHandle;
    #elif xOS_ENV_UNIX
        typedef int       TxHandle;
    #endif

                          CxMutex();
        virtual          ~CxMutex();

        const TxHandle &  hGet   () const;
            ///< get handle
        bool              bCreate(const std::tstring_t &csName);
            ///< create
        bool              bUnlock() const;
            ///< lock
        bool              bLock  (const ulong_t culTimeout) const;
            ///< unlock

    private:
        TxHandle          _m_hHandle;   ///< mutex section handle
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxMutexH

#if xTODO
    CreateMutex - semget, semctl
    CloseHandle - semctl
    WaitForSingleObject - semop
    ReleaseMutex - semop
#endif
