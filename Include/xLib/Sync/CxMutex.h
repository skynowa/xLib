/**
 * \file  CxMutex.h
 * \brief mutex
 */


#ifndef xLib_Sync_CxMutexH
#define xLib_Sync_CxMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_ENV_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

xNAMESPACE_BEGIN(NxLib)

class CxMutex :
    public CxNonCopyable
    /// mutex
{
    public:
                 CxMutex   ();
        virtual ~CxMutex   ();

        HANDLE   hGetHandle() const;
        BOOL     bCreate   (const LPSECURITY_ATTRIBUTES pcsaAttributes, const BOOL cbInitialOwner, const std::string_t &csName);
        BOOL     bOpen     (const ULONG culAccess, const BOOL cbInheritHandle, const std::string_t &csName);
        BOOL     bRelease  () const;
        BOOL     bWait     (const ULONG culTimeout) const;

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
