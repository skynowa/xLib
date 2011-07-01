/****************************************************************************
* Class name:  CxSemaphore
* Description: semaphore
* File name:   CxSemaphore.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2009 18:46:41
*
*****************************************************************************/


#ifndef xLib_Sync_CxSemaphoreH
#define xLib_Sync_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
#include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxSemaphore :
    public CxNonCopyable
{
    public:
                        CxSemaphore();
        virtual        ~CxSemaphore();

        HANDLE          hGetHandle () const;
        BOOL            bCreate    (const PSECURITY_ATTRIBUTES pcsaAttributes, const LONG cliInitialCount, const LONG cliMaxCount, const tString &csName);
        BOOL            bOpen      (const ULONG culAccess, const BOOL cbInheritHandle, const tString &csName) ;
        BOOL            bRelease   (const LONG cliReleaseCount/* = 1*/, LONG *pliOldCount/* = NULL*/) const;
        BOOL            bWait      (const ULONG culTimeout) const;

        LONG            liGetValue () const;
        BOOL            bReset     (const LONG cliInitialCount, const LONG cliMaxCount);

    private:
        CxHandle              _m_hSemaphore;
        LPSECURITY_ATTRIBUTES _m_psaAttributes;
        tString               _m_sName;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxSemaphoreH
