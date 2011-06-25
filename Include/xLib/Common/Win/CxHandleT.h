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
namespace {
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
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
class CxHandleT {
	public:
		                    CxHandleT               ();
		explicit            CxHandleT               (const HANDLE chHandle);
		explicit            CxHandleT               (const CxHandleT &chHandle);
		virtual            ~CxHandleT               ();

		CxHandleT &         operator =              (const HANDLE chHandle);
		CxHandleT &         operator =              (const CxHandleT &chHandle);
		                    operator HANDLE         () const;

		HANDLE              hGet                    () const;
		BOOL                bSet                    (const HANDLE chHandle);

		BOOL                bIsValid                () const;
		BOOL                bAttach                 (const HANDLE chHandle);
		HANDLE              hDetach                 ();
		BOOL                bClose                  ();

		ULONG               ulGetInformation        () const;
		BOOL                bSetInformation         (const ULONG culMask, const ULONG culFlags);
		BOOL 	            bIsFlagInherit          () const;
		BOOL                bIsFlagProtectFromClose () const;
		BOOL                bSetFlagInherit         (const BOOL cbFlagInherit);
		BOOL                bSetFlagProtectFromClose(const BOOL cbFlagProtectFromClose);
		HANDLE              hDuplicate              (const HANDLE chTargetProcess, const ULONG cluDesiredAccess, const BOOL cbInheritHandle/* = FALSE*/, const ULONG cluOptions/* = 0*/) const;

		//static
		static HANDLE       hGetCurrentProcess      ();
		static BOOL         bIsValid                (const HANDLE chHandle);

	private:
	    typedef CxHandleFailValue<hvTag>  FailValue;

		mutable BOOL        _m_bRes;
		HANDLE              _m_hHandle;

		static const HANDLE _ms_chCurrProcessHandle;
};
//---------------------------------------------------------------------------
typedef CxHandleT<hvNull>    CxHandle;
typedef CxHandleT<hvInvalid> CxFileHandle;
//---------------------------------------------------------------------------
#include <Common/Win/CxHandleT.inl>
//---------------------------------------------------------------------------
#endif	//xLib_Common_Win_CxHandleTH
