/**
 * \file  CxAutoCriticalSection.h
 * \brief auto critical section
 */


#ifndef xLib_Sync_CxAutoCriticalSectionH
#define xLib_Sync_CxAutoCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxAutoCriticalSection :
    public CxNonCopyable
{
    public:
                           CxAutoCriticalSection(CxCriticalSection &csCS);
        virtual           ~CxAutoCriticalSection();

    private:
        CxCriticalSection &_m_csCS;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAutoCriticalSectionH
