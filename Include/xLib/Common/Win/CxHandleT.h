/****************************************************************************
* Class name:  CxHandleT
* Description: handle
* File name:   CxHandleT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.01.2010 14:12:26
*
*****************************************************************************/


#ifndef xLib_Common_Win_CxHandleTH
#define xLib_Common_Win_CxHandleTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
enum EHandleValue { 
    hvNull, 
    hvInvalid 
};

template<EHandleValue hvTag>
struct CxHandleFailValue;

template<>
struct CxHandleFailValue<hvNull> {
    static HANDLE get () { return NULL; }
};

template<>
struct CxHandleFailValue<hvInvalid> {
    static HANDLE get () { return INVALID_HANDLE_VALUE; } 
};
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
class CxHandleT {
	public:
		HANDLE        m_hHandle;

		              CxHandleT               ();
		explicit      CxHandleT               (HANDLE hHandle);
		explicit      CxHandleT               (const CxHandleT &hHandle);
		virtual      ~CxHandleT               ();

		CxHandleT&    operator =              (HANDLE hHandle);
		CxHandleT&    operator =              (const CxHandleT &hHandle);
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

	private:
        typedef CxHandleFailValue<hvTag>  FailValue;

		mutable BOOL  _m_bRes;
		
		static const HANDLE _ms_chCurrProcessHandle;
};
//---------------------------------------------------------------------------
typedef CxHandleT<hvNull>    CxHandle;
typedef CxHandleT<hvInvalid> CxFileHandle;
//---------------------------------------------------------------------------
#include <Common/Win/CxHandleT.inl>
//---------------------------------------------------------------------------
#endif	//xLib_Common_Win_CxHandleTH
