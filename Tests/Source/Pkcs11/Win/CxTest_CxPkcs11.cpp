/****************************************************************************
* Class name:  CxTest_CxPkcs11
* Description: test CxPkcs11
* File name:   CxTest_CxPkcs11.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Pkcs11/Win/CxTest_CxPkcs11.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxPkcs11
CxTest_CxPkcs11::CxTest_CxPkcs11() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxPkcs11
CxTest_CxPkcs11::~CxTest_CxPkcs11() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxPkcs11::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if defined(xOS_WIN)
    CxPkcs11 objPkcs11;
    CxSlot   objSlot(objPkcs11);

    CxSlot::ENotification nfNotif = CxSlot::nfError;
    CK_SLOT_ID            ulSlot  = 0;

    /////nfNotif	= objSlot.nfWaitForEvent(0, &ulSlot, NULL_PTR);

    //-------------------------------------
    //bSetData
    xTEST_BLOCK(cullBlockLoops)
    {
    //	const std::tstring csUserPin   = xT("1111");
    //	const std::tstring csDataLabel = xT("Label_Id");
    //	const std::tstring csData      = xT("1203456789");
    //	std::ustring       usData      = xS2US(csData);

    //	m_bRes = CxObject::bSetData(xS2US(csUserPin), xS2US(csDataLabel), usData);
    //	xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bGetData
    xTEST_BLOCK(cullBlockLoops)
    {
    //	const std::tstring csUserPin   = xT("1111");
    //	const std::tstring csDataLabel = xT("Label_Id");
    //	std::ustring       usData;

    //	m_bRes = CxObject::bGetData(xS2US(csUserPin), xS2US(csDataLabel), &usData);
    //	xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring csUserPin   = xT("1111");
        const std::tstring csDataLabel = xT("Key1.tkey");
        const std::tstring csData      = xT("1203456789");
        std::ustring       usData      = xS2US(csData);

        m_bRes = CxObject::bSetData(ulSlot, xS2US(csUserPin), xS2US(csDataLabel), usData);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }
#elif defined(xOS_LINUX)

#endif

	return TRUE;
}
//---------------------------------------------------------------------------
