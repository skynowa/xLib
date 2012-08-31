/**
 * \file  CxSemaphore.h
 * \brief semaphore
 */


#ifndef xLib_Sync_CxSemaphoreH
#define xLib_Sync_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSemaphore :
    private CxNonCopyable
    /// semaphore
{
    public:
        #if xOS_ENV_WIN
            typedef CxHandle  handle_t;
        #elif xOS_ENV_UNIX
            typedef int       handle_t;
        #endif

                              CxSemaphore();
        virtual              ~CxSemaphore();

        const handle_t &      hGet       () const;
            ///< get handle
        bool                  bCreate    (const long_t cliInitialCount, const long_t cliMaxCount, const std::tstring_t &csName);
            ///< create
        bool                  bOpen      (const ulong_t culAccess, const bool cbInheritHandle, const std::tstring_t &csName) ;
            ///< open
        bool                  bRelease   (const long_t cliReleaseCount/* = 1*/, long_t *pliOldCount/* = NULL*/) const;
            ///< release
        bool                  bWait      (const ulong_t culTimeout) const;
            ///< wait

        long_t                liGetValue () const;
            ///< get value
        bool                  bReset     (const long_t cliInitialCount, const long_t cliMaxCount);
            ///< reset

    private:
        handle_t              _m_hSemaphore;
        std::tstring_t        _m_sName;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxSemaphoreH
