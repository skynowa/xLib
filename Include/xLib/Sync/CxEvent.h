/**
 * \file  CxEvent.h
 * \brief event
 */


#ifndef xLib_Sync_CxEventH
#define xLib_Sync_CxEventH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxEvent :
    public CxNonCopyable
    /// event
{
    public:
                 CxEvent    ();
        virtual ~CxEvent    ();

        HANDLE   hGetHandle () const;
        BOOL     bCreate    (const PSECURITY_ATTRIBUTES pcsaAttributes, const BOOL cbManualReset, const BOOL cbInitialState, const std::tstring &csName);
        BOOL     bOpen      (const ULONG culAccess, BOOL cbInheritHandle, const std::tstring &csName);
        BOOL     bPulse     () const;
        BOOL     bReset     () const;
        BOOL     bSet       () const;
        BOOL     bWait      (const ULONG culTimeout) const;

        BOOL     bIsSignaled() const;

    private:
        CxHandle _m_hEvent;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxEventH
