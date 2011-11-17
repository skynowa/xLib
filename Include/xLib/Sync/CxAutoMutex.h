/**
 * \file  CxAutoMutex.h
 * \brief auto mutex
 */


#ifndef xLib_Sync_CxAutoMutexH
#define xLib_Sync_CxAutoMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxMutex.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxAutoMutex :
    public CxNonCopyable
    /// auto mutex
{
    public:
                 CxAutoMutex(CxMutex &mtMutex);
        virtual ~CxAutoMutex();

    private:
        CxMutex &_m_mtMutex;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAutoMutexH
