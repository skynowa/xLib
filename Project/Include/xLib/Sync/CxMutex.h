/**
 * \file  CxMutex.h
 * \brief critical section (using between threads)
 */


#ifndef xLib_Sync_CxMutexH
#define xLib_Sync_CxMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMutex :
    private CxNonCopyable
    /// critical section
{
    public:
    #if xOS_ENV_WIN
        typedef CRITICAL_SECTION handle_t;
    #elif xOS_ENV_UNIX
        typedef pthread_mutex_t  handle_t;
    #endif

                          CxMutex();
            ///< constructor
        virtual          ~CxMutex();
            ///< destructor

        const handle_t &  hGet             () const;
            ///< get handle
        bool              bCreate          ();
            ///< create
        bool              bLock            ();
            ///< lock
        bool              bTryLock         ();
            ///< try lock
        bool              bUnlock          ();
            ///< unlock

    private:
        handle_t          _m_hHandle;   ///< critical section handle
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxMutexH
