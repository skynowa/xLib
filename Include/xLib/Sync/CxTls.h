/****************************************************************************
* Class name:  CxTls
* Description: tread local storage
* File name:   CxTls.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     18.01.2010 14:42:20
*
*****************************************************************************/


#ifndef CxLib_Sync_CxTlsH
#define CxLib_Sync_CxTlsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxTls : public CxNonCopyable {
	public:
		         CxTls();
		virtual ~CxTls();

		BOOL     bAlloc    ();
		BOOL     bFree     ();
		VOID    *pvGetValue();
		BOOL     bSetValue (VOID *pvValue);

	private:
		ULONG    _m_ulIndex;
};
//---------------------------------------------------------------------------
#endif	//CxLib_Sync_CxTlsH
