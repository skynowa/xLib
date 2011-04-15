/****************************************************************************
* Class name:  CxTls
* Description: ��������� ������ ������
* File name:   CxTls.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     18.01.2010 14:42:20
* Version:     1.0.0.0 Debug
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
