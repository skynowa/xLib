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
#if defined(xOS_ENV_WIN)
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
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAutoMutexH
