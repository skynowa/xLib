/****************************************************************************
* Class name:  CxAutoMutex
* Description: auto mutex
* File name:   CxAutoMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     16.12.2009 10:06:46
*
*****************************************************************************/


#ifndef xLib_Sync_CxAutoMutexH
#define xLib_Sync_CxAutoMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxMutex.h>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxAutoMutex :
    public CxNonCopyable
{
    public:
                 CxAutoMutex(CxMutex &mtMutex);
        virtual ~CxAutoMutex();

    private:
        CxMutex &_m_mtMutex;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAutoMutexH
