/**
 * \file  CxSemaphore.h
 * \brief semaphore
 */


#ifndef xLib_Sync_CxSemaphoreH
#define xLib_Sync_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOS_ENV_WIN
    #include <xLib/Common/Win/CxHandleT.h>
#elif xOS_ENV_UNIX

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxSemaphore :
    public CxNonCopyable
    /// semaphore
{
    public:
                        CxSemaphore();
        virtual        ~CxSemaphore();

        HANDLE          hGetHandle () const;
        bool            bCreate    (const PSECURITY_ATTRIBUTES pcsaAttributes, const LONG cliInitialCount, const LONG cliMaxCount, const std::tstring &csName);
        bool            bOpen      (const ULONG culAccess, const bool cbInheritHandle, const std::tstring &csName) ;
        bool            bRelease   (const LONG cliReleaseCount/* = 1*/, LONG *pliOldCount/* = NULL*/) const;
        bool            bWait      (const ULONG culTimeout) const;

        LONG            liGetValue () const;
        bool            bReset     (const LONG cliInitialCount, const LONG cliMaxCount);

    private:
        CxHandle              _m_hSemaphore;
        LPSECURITY_ATTRIBUTES _m_psaAttributes;
        std::tstring          _m_sName;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxSemaphoreH
