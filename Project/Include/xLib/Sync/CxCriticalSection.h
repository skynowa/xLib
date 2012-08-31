/**
 * \file  CxCriticalSection.h
 * \brief critical section (using between threads)
 */


#ifndef xLib_Sync_CxCriticalSectionH
#define xLib_Sync_CxCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCriticalSection :
    private CxNonCopyable
    /// critical section
{
    public:
    #if xOS_ENV_WIN
        typedef CRITICAL_SECTION handle_t;
    #elif xOS_ENV_UNIX
        typedef pthread_mutex_t  handle_t;
    #endif

                          CxCriticalSection();
            ///< constructor
        virtual          ~CxCriticalSection();
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
#endif    //xLib_Sync_CxCriticalSectionH
