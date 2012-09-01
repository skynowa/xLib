/**
 * \file  CxIpcSemaphore.h
 * \brief semaphore
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
    /// semaphore
{
    public:
        #if xOS_ENV_WIN
            typedef CxHandle handle_t;
        #elif xOS_ENV_UNIX
            typedef sem_t *  handle_t;
        #endif

                         CxIpcSemaphore();
        virtual         ~CxIpcSemaphore();

        const handle_t & hGet           () const;
            ///< get handle
        bool             bCreate        (const long_t &cliInitialValue, const long_t &cliMaxValue, const std::tstring_t &csName);
            ///< create
        bool             bOpen          (const std::tstring_t &csName) ;
            ///< open
        bool             bRelease       (const long_t &cliReleaseValue /* = 1 */, long_t *pliOldValue/* = NULL*/) const;
            ///< release
        bool             bWait          (const ulong_t &culTimeoutMsec) const;
            ///< wait
        long_t           liGetValue     () const;
            ///< get value
        bool             bReset         (const long_t &cliInitialValue, const long_t &cliMaxValue);
            ///< reset

    private:
        handle_t         _m_hHandle;
        std::tstring_t   _m_sName;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxIpcSemaphoreH


/*
    SEM_VALUE_MAX

*/
