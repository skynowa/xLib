/**
 * \file  CxCriticalSection.cpp
 * \brief critical section
 */


#include <xLib/Sync/CxCriticalSection.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxCriticalSection::CxCriticalSection() :
#if defined(xOS_WIN)
    _m_CS    ()
#elif defined(xOS_LINUX)
    _m_mMutex()
#endif
{
#if defined(xOS_WIN)
    ::InitializeCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    INT iRes = - 1;

    pthread_mutexattr_t maAttr;

    iRes = pthread_mutexattr_settype(&maAttr, PTHREAD_MUTEX_RECURSIVE_NP);
    /*DEBUG*/xASSERT_DO(0 == iRes, return);

    {
	    iRes = pthread_mutex_init(&_m_mMutex, &maAttr);
	    /*DEBUG*/xASSERT_DO(0 == iRes, return);
    }

    iRes = pthread_mutexattr_destroy(&maAttr);
    /*DEBUG*/xASSERT_DO(0 == iRes, return);
#endif
}
//---------------------------------------------------------------------------
CxCriticalSection::CxCriticalSection(
    const ULONG culSpinCount
)
{
    /*DEBUG*///ulSpinCount - n/a

#if defined(xOS_WIN)
    BOOL bRes = ::InitializeCriticalSectionAndSpinCount(&_m_CS, culSpinCount);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
#elif defined(xOS_LINUX)
    //TODO: CxCriticalSection
#endif
}
//---------------------------------------------------------------------------
CxCriticalSection::~CxCriticalSection() {
#if defined(xOS_WIN)
    ::DeleteCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_mutex_destroy(&_m_mMutex);
	///*DEBUG*/xASSERT_DO(0 == iRes, return);
	xASSERT_EQ(0, iRes);
#endif
}
//---------------------------------------------------------------------------
BOOL
CxCriticalSection::bEnter() {
#if defined(xOS_WIN)
    ::EnterCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_mutex_lock(&_m_mMutex);
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCriticalSection::bTryEnter() {
#if defined(xOS_WIN)
    BOOL bRes = ::TryEnterCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_mutex_trylock(&_m_mMutex);
    xCHECK_RET(0 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxCriticalSection::bLeave() {
#if defined(xOS_WIN)
    ::LeaveCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    INT iRes = pthread_mutex_unlock(&_m_mMutex);
    /*DEBUG*/xASSERT_RET(0 == iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
ULONG
CxCriticalSection::ulSetSpinCount(
    const ULONG culSpinCount
)
{
    /*DEBUG*///ulSpinCount - n/a

#if defined(xOS_WIN)
    return ::SetCriticalSectionSpinCount(&_m_CS, culSpinCount);
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    //TODO: ulSetSpinCount

    return 0UL;
#endif
}
//---------------------------------------------------------------------------
