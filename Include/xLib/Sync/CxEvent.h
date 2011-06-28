/****************************************************************************
* Class name:  CxEvent
* Description: event
* File name:   CxEvent.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2009 17:53:15
*
*****************************************************************************/


#ifndef xLib_Sync_CxEventH
#define xLib_Sync_CxEventH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandleT.h>
//---------------------------------------------------------------------------
class CxEvent :
    public CxNonCopyable
{
    public:
                 CxEvent    ();
        virtual ~CxEvent    ();

        HANDLE   hGetHandle () const;
        BOOL     bCreate    (const PSECURITY_ATTRIBUTES pcsaAttributes, const BOOL cbManualReset, const BOOL cbInitialState, const tString &csName);
        BOOL     bOpen      (const ULONG culAccess, BOOL cbInheritHandle, const tString &csName);
        BOOL     bPulse     () const;
        BOOL     bReset     () const;
        BOOL     bSet       () const;
        BOOL     bWait      (const ULONG culTimeout) const;

        BOOL     bIsSignaled() const;

    private:
        CxHandle _m_hEvent;
};
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxEventH
