/**
 * \file  CxCriticalSection.h
 * \brief critical section
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
                          CxCriticalSection();
        explicit          CxCriticalSection(const ULONG culSpinCount);
                         ~CxCriticalSection();

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


#if xTODO
    InitializeCriticalSection, InitializeCriticalSectionAndSpinCount - pthread_mutex_init 
    EnterCriticalSection    - pthread_mutex_lock 
    TryEnterCriticalSection - pthread_mutex_trylock 
    LeaveCriticalSection    - pthread_mutex_unlock 
    DeleteCriticalSection   - pthread_mutex_destroy
#endif


#if xTODO
CRITICAL_SECTION cs; - pthread_mutex_t _m_mMutex;


InitializeCriticalSection(&cs); - 
                        //create mutex attribute variable
                        pthread_mutexattr_t _m_maAttr; 

                        // setup recursive mutex for mutex attribute
                        pthread_mutexattr_settype(&_m_maAttr, PTHREAD_MUTEX_RECURSIVE_NP);

                        // Use the mutex attribute to create the mutex 
                        pthread_mutex_init(&_m_mMutex, &_m_maAttr);

                        // Mutex attribute can be destroy after initializing the mutex variable
                        pthread_mutexattr_destroy(&_m_maAttr)


EnterCriticalSection(&cs);  - pthread_mutex_lock (&_m_mMutex);
LeaveCriticalSection(&cs);  - pthread_mutex_unlock (&_m_mMutex);
DeleteCriticalSection(&cs); - pthread_mutex_destroy (&_m_mMutex);
#endif
