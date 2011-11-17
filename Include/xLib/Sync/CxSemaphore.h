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
        BOOL            bCreate    (const PSECURITY_ATTRIBUTES pcsaAttributes, const LONG cliInitialCount, const LONG cliMaxCount, const std::string_t &csName);
        BOOL            bOpen      (const ULONG culAccess, const BOOL cbInheritHandle, const std::string_t &csName) ;
        BOOL            bRelease   (const LONG cliReleaseCount/* = 1*/, LONG *pliOldCount/* = NULL*/) const;
        BOOL            bWait      (const ULONG culTimeout) const;

        LONG            liGetValue () const;
        BOOL            bReset     (const LONG cliInitialCount, const LONG cliMaxCount);

    private:
        CxHandle              _m_hSemaphore;
        LPSECURITY_ATTRIBUTES _m_psaAttributes;
        std::string_t          _m_sName;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxSemaphoreH
