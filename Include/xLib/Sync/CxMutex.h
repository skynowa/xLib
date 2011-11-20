/**
 * \file  CxMutex.h
 * \brief mutex
 */


#ifndef xLib_Sync_CxMutexH
#define xLib_Sync_CxMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOS_ENV_WIN
    #include <xLib/Common/Win/CxHandleT.h>
#elif xOS_ENV_UNIX

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxMutex :
    public CxNonCopyable
    /// mutex
{
    public:
                 CxMutex   ();
        virtual ~CxMutex   ();

        HANDLE   hGetHandle() const;
        bool     bCreate   (const LPSECURITY_ATTRIBUTES pcsaAttributes, const bool cbInitialOwner, const std::tstring &csName);
        bool     bOpen     (const ULONG culAccess, const bool cbInheritHandle, const std::tstring &csName);
        bool     bRelease  () const;
        bool     bWait     (const ULONG culTimeout) const;

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
