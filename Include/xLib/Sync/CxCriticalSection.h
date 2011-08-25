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
#if defined(xOS_WIN)
class CxCriticalSection :
    public CxNonCopyable
{
    public:
                          CxCriticalSection();
        explicit          CxCriticalSection(const ULONG culSpinCount);
                         ~CxCriticalSection();

        VOID              vEnter           ();
        VOID              vLeave           ();
        ULONG             ulSetSpinCount   (const ULONG culSpinCount);
        BOOL              bTryEnter        ();

    private:
    #if defined(xOS_WIN)
        CRITICAL_SECTION  _m_CS;
    #elif defined(xOS_LINUX)
        //TODO: CxCriticalSection
    #endif
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxCriticalSectionH
