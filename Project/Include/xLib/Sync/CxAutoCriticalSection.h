/**
 * \file  CxAutoCriticalSection.h
 * \brief auto critical section (using between threads)
 */


#ifndef xLib_Sync_CxAutoCriticalSectionH
#define xLib_Sync_CxAutoCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCriticalSection;

class CxAutoCriticalSection :
    private CxNonCopyable
    /// auto critical section
{
    public:
                           CxAutoCriticalSection(CxCriticalSection &csCS, const bool cbIsUseTry = false);
            ///< constructor
        virtual           ~CxAutoCriticalSection();
            ///< destructor
        bool               bIsLocked            () const;
            ///< is locked

    private:
        CxCriticalSection &_m_csCS;         ///< critical section
        bool               _m_bIsLocked;    ///< lock flag for explicit unlock
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAutoCriticalSectionH
