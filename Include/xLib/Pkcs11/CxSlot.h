/****************************************************************************
* Class name:  CxSlot
* Description: Pkcs11 ����
* File name:   CxSlot.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib, Aladdin eToken SDK
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.03.2010 13:07:29
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Pkcs11_CxSlotH
#define xLib_Pkcs11_CxSlotH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Pkcs11/Common.h>
#include <xLib/Pkcs11/CxPkcs11.h>
//---------------------------------------------------------------------------
class CxSlot : public CxNonCopyable {
	public:
		//���������
		enum ENotification {
			nfError,
			nfInsertion,
			nfRemoval
		};

					         CxSlot          (const CxPkcs11 &cPkcs11);
				            ~CxSlot          ();

		BOOL                 bGetList        (CK_BBOOL bTokenPresent, std::vector<CK_SLOT_ID> *pvecSlotList);	
		BOOL                 bGetInfo        (CK_SLOT_ID slotID, CK_SLOT_INFO_PTR pInfo);									
		ENotification        nfWaitForEvent  (CK_FLAGS flags, CK_SLOT_ID_PTR pSlot, CK_VOID_PTR pRserved);				
	   	
	private:
		BOOL                 _m_bRes;
		CK_RV                _m_ulRes;
		CK_FUNCTION_LIST_PTR _m_pFunc;
};
//---------------------------------------------------------------------------
#endif	//xLib_Pkcs11_CxSlotH
