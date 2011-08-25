/**
 * \file  CxMutex.h
 * \brief mutex
 */


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
        BOOL     bCreate   (const LPSECURITY_ATTRIBUTES pcsaAttributes, const BOOL cbInitialOwner, const std::tstring &csName);
        BOOL     bOpen     (const ULONG culAccess, const BOOL cbInheritHandle, const std::tstring &csName);
        BOOL     bRelease  () const;
        BOOL     bWait     (const ULONG culTimeout) const;

    private:
        CxHandle _m_hMutex;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxMutexH
