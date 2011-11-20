/**
 * \file   CxTest_CxPkcs11.cpp
 * \brief
 */


#include <Test/Crypt/Pkcs11/Win/CxTest_CxPkcs11.h>


//---------------------------------------------------------------------------
CxTest_CxPkcs11::CxTest_CxPkcs11() {

}
//---------------------------------------------------------------------------
CxTest_CxPkcs11::~CxTest_CxPkcs11() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxPkcs11::bUnit(
    const ULONGLONG cullBlockLoops
)
{
#if xOS_ENV_WIN
    CxPkcs11 objPkcs11;
    CxSlot   objSlot(objPkcs11);

    CxSlot::ENotification nfNotif = CxSlot::nfError;  xUNUSED(nfNotif);
    CK_SLOT_ID            ulSlot  = 0;

    /////nfNotif    = objSlot.nfWaitForEvent(0, &ulSlot, NULL_PTR);

    //-------------------------------------
    //bSetData
    xTEST_BLOCK(cullBlockLoops)
    {
    //    const std::tstring csUserPin   = xT("1111");
    //    const std::tstring csDataLabel = xT("Label_Id");
    //    const std::tstring csData      = xT("1203456789");
    //    std::ustring       usData      = xS2US(csData);

    //    m_bRes = CxObject::bSetData(xS2US(csUserPin), xS2US(csDataLabel), usData);
    //    xTEST_DIFF(false, m_bRes);
    }

    //-------------------------------------
    //bGetData
    xTEST_BLOCK(cullBlockLoops)
    {
    //    const std::tstring csUserPin   = xT("1111");
    //    const std::tstring csDataLabel = xT("Label_Id");
    //    std::ustring       usData;

    //    m_bRes = CxObject::bGetData(xS2US(csUserPin), xS2US(csDataLabel), &usData);
    //    xTEST_DIFF(false, m_bRes);
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
        xTEST_EQ((bool)true, (bool)m_bRes);   //TODO: xTEST_EQ
    }
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
