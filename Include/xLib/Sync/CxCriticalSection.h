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
        explicit          CxCriticalSection(const ULONG culSpinCount);
                         ~CxCriticalSection();

        const TxHandle &  hGet             () const;
        BOOL              bEnter           ();
        BOOL              bTryEnter        ();
        BOOL              bLeave           ();
        ULONG             ulSetSpinCount   (const ULONG culSpinCount);

    private:
    #if defined(xOS_WIN)
        CRITICAL_SECTION  _m_CS;
    #elif defined(xOS_LINUX)
        pthread_mutex_t   _m_mMutex;
    #endif
};
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxCriticalSectionH
