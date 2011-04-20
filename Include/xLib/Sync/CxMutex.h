/****************************************************************************
* Class name:  CxMutex
* Description: mutex
* File name:   CxMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2009 18:48:30
*
*****************************************************************************/


#ifndef xLib_Sync_CxMutexH
#define xLib_Sync_CxMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandle.h>
//---------------------------------------------------------------------------
class CxMutex : public CxNonCopyable {
    public:
                 CxMutex   ();
        virtual ~CxMutex   ();

        HANDLE   hGetHandle() const;
        BOOL     bCreate   (LPSECURITY_ATTRIBUTES lpsaAttributes, BOOL bInitialOwner, LPCTSTR pcszName);
        BOOL     bOpen     (ULONG ulAccess, BOOL bInheritHandle, LPCTSTR pcszName);
        BOOL     bRelease  () const;
        BOOL     bWait     (ULONG ulTimeout) const;

    private:
        CxHandle _m_hMutex;
};
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxMutexH
