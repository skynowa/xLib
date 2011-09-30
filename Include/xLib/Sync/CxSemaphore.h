/**
 * \file  CxSemaphore.h
 * \brief semaphore
 */


#ifndef xLib_Sync_CxSemaphoreH
#define xLib_Sync_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_ENV_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxSemaphore :
    public CxNonCopyable
    /// semaphore
{
    public:
                        CxSemaphore();
        virtual        ~CxSemaphore();

        HANDLE          hGetHandle () const;
        BOOL            bCreate    (const PSECURITY_ATTRIBUTES pcsaAttributes, const LONG cliInitialCount, const LONG cliMaxCount, const std::tstring &csName);
        BOOL            bOpen      (const ULONG culAccess, const BOOL cbInheritHandle, const std::tstring &csName) ;
        BOOL            bRelease   (const LONG cliReleaseCount/* = 1*/, LONG *pliOldCount/* = NULL*/) const;
        BOOL            bWait      (const ULONG culTimeout) const;

        LONG            liGetValue () const;
        BOOL            bReset     (const LONG cliInitialCount, const LONG cliMaxCount);

    private:
        CxHandle              _m_hSemaphore;
        LPSECURITY_ATTRIBUTES _m_psaAttributes;
        std::tstring          _m_sName;
};
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxSemaphoreH
