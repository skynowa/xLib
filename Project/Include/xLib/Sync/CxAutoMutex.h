/**
 * \file  CxAutoMutex.h
 * \brief auto critical section (using between threads)
 */


#ifndef xLib_Sync_CxAutoMutexH
#define xLib_Sync_CxAutoMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMutex;

class CxAutoMutex :
    private CxNonCopyable
    /// auto critical section
{
    public:
                 CxAutoMutex(CxMutex &mtMutex, const bool &cbIsUseTry = false);
            ///< constructor
        virtual ~CxAutoMutex();
            ///< destructor

        bool     bIsLocked  () const;
            ///< is locked

    private:
        CxMutex &_m_mtMutex;    ///< mutex
        bool     _m_bIsLocked;  ///< lock flag for explicit unlock
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAutoMutexH
