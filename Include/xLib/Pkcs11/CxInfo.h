/****************************************************************************
* Class name:  CxInfo
* Description: Pkcs11 ����������
* File name:   CxInfo.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib, Aladdin eToken SDK
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.03.2010 13:08:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxInfoH
#define xLib_Pkcs11_CxInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxInfo : public CxNonCopyable {
	public:
		                     CxInfo   (const CxPkcs11 &cPkcs11);
	                        ~CxInfo   ();
	   
	   	BOOL                 bGet     (CK_INFO_PTR pInfo);	
		BOOL                 bGetToken(CK_SLOT_ID slotID, CK_TOKEN_INFO_PTR pInfo);	
	   	
	private:
		BOOL                 _m_bRes;
		CK_RV                _m_ulRes;

		CK_FUNCTION_LIST_PTR _m_pFunc;
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CxInfoH
