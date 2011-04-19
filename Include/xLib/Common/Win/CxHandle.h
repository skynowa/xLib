/****************************************************************************
* Class name:  CxHandle
* Description: handle
* File name:   CxHandle.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.01.2010 14:12:26
*
*****************************************************************************/


#ifndef xLib_Common_Win_CxHandleH
#define xLib_Common_Win_CxHandleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxHandle {
    private:
		mutable BOOL  _m_bRes;

		HANDLE hFailValueT;
		static const HANDLE _ms_chCurrProcessHandle;

	public:
		HANDLE        m_hHandle;

		              CxHandle               ();
		explicit      CxHandle               (HANDLE hHandle);
		explicit      CxHandle               (const CxHandle &hHandle);
		virtual      ~CxHandle               ();

		CxHandle&     operator =              (HANDLE hHandle);
		CxHandle&     operator =              (const CxHandle &hHandle);
		              operator HANDLE         () const;

		BOOL          bIsValid                () const;
		BOOL          bAttach                 (HANDLE hHandle);
		HANDLE        hDetach                 ();
		BOOL          bClose                  ();

		ULONG         ulGetInformation        () const;
		BOOL          bSetInformation         (ULONG ulMask, ULONG ulFlags);
		BOOL 	      bIsFlagInherit          () const;
		BOOL          bIsFlagProtectFromClose () const;
		BOOL          bSetFlagInherit         (BOOL bFlagInherit);
		BOOL          bSetFlagProtectFromClose(BOOL bFlagProtectFromClose);
		HANDLE        hDuplicate              (HANDLE hTargetProcess, ULONG luDesiredAccess, BOOL bInheritHandle/* = FALSE*/, ULONG luOptions/* = 0*/) const;

		//static
		static HANDLE hGetCurrentProcess      ();
		static BOOL   bIsValid                (HANDLE hHandle);
};
//---------------------------------------------------------------------------
//typedef CxHandle<NULL>                 CxHandle;
//typedef CxHandle<INVALID_HANDLE_VALUE> CxFileHandle;
//---------------------------------------------------------------------------
#endif	//xLib_Common_Win_CxHandleH
