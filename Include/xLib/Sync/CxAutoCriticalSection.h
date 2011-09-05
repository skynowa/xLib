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
class CxAutoCriticalSection
    /// auto critical section
{
    public:
        explicit           CxAutoCriticalSection(CxCriticalSection &csCS);
            ///< constructor
        virtual           ~CxAutoCriticalSection();
            ///< destructor
    private:
        CxCriticalSection &_m_csCS;    ///< critical section
};
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAutoCriticalSectionH
