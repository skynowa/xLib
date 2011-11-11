/**
 * \file  CxAutoCriticalSection.h
 * \brief auto critical section (using between threads)
 */


#ifndef xLib_Sync_CxAutoCriticalSectionH
#define xLib_Sync_CxAutoCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxAutoCriticalSection :
    public CxNonCopyable
    /// auto critical section
{
    public:
                           CxAutoCriticalSection(CxCriticalSection &csCS, const BOOL cbIsUseTry = FALSE);
            ///< constructor
        virtual           ~CxAutoCriticalSection();
            ///< destructor
        BOOL               bIsLocked            () const;
            ///< is locked

    private:
        CxCriticalSection &_m_csCS;         ///< critical section
        BOOL               _m_bIsLocked;    ///< lock flag for explicit unlock
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAutoCriticalSectionH
