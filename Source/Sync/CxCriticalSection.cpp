/****************************************************************************
* Class name:  CxCriticalSection
* Description: critical section
* File name:   CxCriticalSection.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2009 21:16:33
*
*****************************************************************************/


#include <xLib/Sync/CxCriticalSection.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxCriticalSection
CxCriticalSection::CxCriticalSection() :
#if defined(xOS_WIN)
    _m_CS()
#elif defined(xOS_LINUX)
    //TODO: CxCriticalSection
#endif
{
    #if defined(xOS_WIN)
        ::InitializeCriticalSection(&_m_CS);
        /*DEBUG*/// n/a
    #elif defined(xOS_LINUX)
        //TODO: CxCriticalSection
    #endif
}
//---------------------------------------------------------------------------
//DONE: CxCriticalSection
CxCriticalSection::CxCriticalSection(
    const ULONG culSpinCount
)
{
    /*DEBUG*///ulSpinCount - not need

    BOOL bRes = FALSE;

    bRes = ::InitializeCriticalSectionAndSpinCount(&_m_CS, culSpinCount);
    /*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxCriticalSection ()
CxCriticalSection::~CxCriticalSection() {
    ::DeleteCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: vEnter ()
VOID
CxCriticalSection::vEnter() {
    ::EnterCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: vLeave ()
VOID
CxCriticalSection::vLeave() {
    ::LeaveCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ulSetSpinCount ()
ULONG
CxCriticalSection::ulSetSpinCount(
    const ULONG culSpinCount
)
{
    /*DEBUG*///ulSpinCount - n/a

    return ::SetCriticalSectionSpinCount(&_m_CS, culSpinCount);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: bTryEnter ()
BOOL
CxCriticalSection::bTryEnter() {
    return ::TryEnterCriticalSection(&_m_CS);
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
