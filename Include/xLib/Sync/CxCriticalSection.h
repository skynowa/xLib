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
class CxCriticalSection :
    public CxNonCopyable
    /// critical section
{
    public:
    #if defined(xOS_WIN)
        typedef CRITICAL_SECTION TxHandle;
    #elif defined(xOS_LINUX)
        typedef pthread_mutex_t  TxHandle;
    #endif

                          CxCriticalSection();
            ///< constructor
        virtual          ~CxCriticalSection();
            ///< destructor

        const TxHandle &  hGet             () const;
            ///< get handle
        BOOL              bLock            ();
            ///< lock
        BOOL              bTryLock         ();
            ///< try lock
        BOOL              bUnlock          ();
            ///< unlock

    private:
        TxHandle          _m_hHandle;   ///< critical section handle
};
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxCriticalSectionH
