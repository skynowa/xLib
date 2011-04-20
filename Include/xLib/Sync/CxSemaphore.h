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
#include <xLib/Common/Win/CxHandle.h>
//---------------------------------------------------------------------------
class CxSemaphore : public CxNonCopyable {
    public:
                        CxSemaphore();
        virtual        ~CxSemaphore();

        HANDLE          hGetHandle () const;
        BOOL            bCreate    (PSECURITY_ATTRIBUTES lpsaAttributes, LONG liInitialCount, LONG liMaxCount, LPCTSTR pcszName);
        BOOL            bOpen      (ULONG ulAccess, BOOL bInheritHandle, LPCTSTR lpszName) ;
        BOOL            bRelease   (LONG liReleaseCount/* = 1*/, LONG *pliOldCount/* = NULL*/)  const;
        BOOL            bWait      (ULONG ulTimeout) const;

        LONG            liGetValue () const;
        BOOL            bReset     (LONG liInitialCount, LONG liMaxCount);

    private:
        CxHandle         _m_hSemaphore;
        LPSECURITY_ATTRIBUTES   _m_lpsaAttributes;
        LPCTSTR                 _m_pcszName;
};
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxSemaphoreH
