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
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxMutex :
    private CxNonCopyable
    /// mutex
{
    public:
                 CxMutex   ();
        virtual ~CxMutex   ();

        HANDLE   hGetHandle() const;
        bool     bCreate   (const LPSECURITY_ATTRIBUTES pcsaAttributes, const bool cbInitialOwner, const std::tstring_t &csName);
        bool     bOpen     (const ulong_t culAccess, const bool cbInheritHandle, const std::tstring_t &csName);
        bool     bRelease  () const;
        bool     bWait     (const ulong_t culTimeout) const;

    private:
        CxHandle _m_hMutex;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxMutexH

#if xTODO
    CreateMutex - semget, semctl
    CloseHandle - semctl
    WaitForSingleObject - semop
    ReleaseMutex - semop
#endif
