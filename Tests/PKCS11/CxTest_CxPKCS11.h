/****************************************************************************
* Class name:  CxTest_CxPkcs11
* Description: test CxPkcs11
* File name:   CxTest_CxPkcs11.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxPkcs11H
#define CxTest_CxPkcs11H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Pkcs11/All.h>
//---------------------------------------------------------------------------
class CxTest_CxPkcs11 :
    public CxTest
{
	public:
		CxTest_CxPkcs11();
		virtual     ~CxTest_CxPkcs11();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxPkcs11 (comment)
CxTest_CxPkcs11::CxTest_CxPkcs11() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxPkcs11 (comment)
CxTest_CxPkcs11::~CxTest_CxPkcs11() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxPkcs11::bUnit() {
	CxPkcs11 objPkcs11;
	CxSlot   objSlot(objPkcs11);

	CxSlot::ENotification nfNotif = CxSlot::nfError;
	CK_SLOT_ID            ulSlot  = 0;

	/////nfNotif	= objSlot.nfWaitForEvent(0, &ulSlot, NULL_PTR);

	//-------------------------------------
	//bSetData
	//{
	//	const tString csUserPin   = xT("1111");
	//	const tString csDataLabel = xT("Label_Id");
	//	const tString csData      = xT("1203456789");
	//	uString       usData      = xS2US(csData);

	//	m_bRes = CxObject::bSetData(xS2US(csUserPin), xS2US(csDataLabel), usData);
	//	xASSERT(FALSE != m_bRes);
	//}

	//-------------------------------------
	//bGetData
	//{
	//	const tString csUserPin   = xT("1111");
	//	const tString csDataLabel = xT("Label_Id");
	//	uString       usData;

	//	m_bRes = CxObject::bGetData(xS2US(csUserPin), xS2US(csDataLabel), &usData);
	//	xASSERT(FALSE != m_bRes);
	//}

	//-------------------------------------
	//
	{
		const tString csUserPin   = xT("1111");
		const tString csDataLabel = xT("Key1.tkey");
		const tString csData      = xT("1203456789");
		uString       usData      = xS2US(csData);

		m_bRes = CxObject::bSetData(ulSlot, xS2US(csUserPin), xS2US(csDataLabel), usData);
		xASSERT(FALSE != m_bRes);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxPkcs11H

