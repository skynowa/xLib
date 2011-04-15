/****************************************************************************
* Class name:  CxSemaphore
* Description: ������ � ����������
* File name:   CxSemaphore.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.05.2009 18:46:41
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxSemaphoreH
#define xLib_Sync_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandleT.h>
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
		CxHandleT<NULL>         _m_hSemaphore;
		LPSECURITY_ATTRIBUTES   _m_lpsaAttributes;
		LPCTSTR                 _m_pcszName;
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxSemaphoreH
