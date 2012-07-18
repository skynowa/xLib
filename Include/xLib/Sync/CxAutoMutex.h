/**
 * \file  CxAutoMutex.h
 * \brief auto mutex
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
    /// auto mutex
{
    public:
                 CxAutoMutex(CxMutex &mtMutex);
        virtual ~CxAutoMutex();

    private:
        CxMutex &_m_mtMutex;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAutoMutexH
