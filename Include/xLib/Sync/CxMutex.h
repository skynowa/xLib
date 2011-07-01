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

#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxMutex :
    public CxNonCopyable
{
    public:
                 CxMutex   ();
        virtual ~CxMutex   ();

        HANDLE   hGetHandle() const;
        BOOL     bCreate   (const LPSECURITY_ATTRIBUTES pcsaAttributes, const BOOL cbInitialOwner, const tString &csName);
        BOOL     bOpen     (const ULONG culAccess, const BOOL cbInheritHandle, const tString &csName);
        BOOL     bRelease  () const;
        BOOL     bWait     (const ULONG culTimeout) const;

    private:
        CxHandle _m_hMutex;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxMutexH
