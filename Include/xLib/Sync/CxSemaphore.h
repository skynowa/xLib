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
        virtual              ~CxSemaphore();

        HANDLE                hGetHandle () const;
        bool                  bCreate    (const PSECURITY_ATTRIBUTES pcsaAttributes, const long_t cliInitialCount, const long_t cliMaxCount, const std::tstring_t &csName);
        bool                  bOpen      (const ulong_t culAccess, const bool cbInheritHandle, const std::tstring_t &csName) ;
        bool                  bRelease   (const long_t cliReleaseCount/* = 1*/, long_t *pliOldCount/* = NULL*/) const;
        bool                  bWait      (const ulong_t culTimeout) const;

        long_t                liGetValue () const;
        bool                  bReset     (const long_t cliInitialCount, const long_t cliMaxCount);

    private:
        CxHandle              _m_hSemaphore;
        LPSECURITY_ATTRIBUTES _m_psaAttributes;
        std::tstring_t        _m_sName;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxSemaphoreH
