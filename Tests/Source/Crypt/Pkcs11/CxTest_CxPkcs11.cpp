/**
 * \file   CxTest_CxPkcs11.cpp
 * \brief
 */


#include <Test/Crypt/Pkcs11/CxTest_CxPkcs11.h>


//---------------------------------------------------------------------------
CxTest_CxPkcs11::CxTest_CxPkcs11() {

}
//---------------------------------------------------------------------------
CxTest_CxPkcs11::~CxTest_CxPkcs11() {

}
//---------------------------------------------------------------------------
/* virtual */
bool
CxTest_CxPkcs11::bUnit(
    const ulonglong_t cullCaseLoops
)
{
#if   xOS_ENV_WIN
    CxPkcs11 objPkcs11;
    CxSlot   objSlot(objPkcs11);

    CxSlot::ENotification nfNotif = CxSlot::nfError;  xUNUSED(nfNotif);
    CK_SLOT_ID            ulSlot  = 0;

    /////nfNotif    = objSlot.nfWaitForEvent(0, &ulSlot, NULL_PTR);

    //-------------------------------------
    //bSetData
    xTEST_CASE(cullCaseLoops)
    {
    //    const std::tstring_t csUserPin   = xT("1111");
    //    const std::tstring_t csDataLabel = xT("Label_Id");
    //    const std::tstring_t csData      = xT("1203456789");
    //    std::ustring_t       usData      = xS2US(csData);

    //    m_bRv = CxObject::bSetData(xS2US(csUserPin), xS2US(csDataLabel), usData);
    //    xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bGetData
    xTEST_CASE(cullCaseLoops)
    {
    //    const std::tstring_t csUserPin   = xT("1111");
    //    const std::tstring_t csDataLabel = xT("Label_Id");
    //    std::ustring_t       usData;

    //    m_bRv = CxObject::bGetData(xS2US(csUserPin), xS2US(csDataLabel), &usData);
    //    xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csUserPin   = xT("1111");
        const std::tstring_t csDataLabel = xT("Key1.tkey");
        const std::tstring_t csData      = xT("1203456789");
        std::ustring_t       usData      = xS2US(csData);

        m_bRv = CxObject::bSetData(ulSlot, xS2US(csUserPin), xS2US(csDataLabel), usData);
        xTEST_EQ(true, m_bRv);
    }
#elif xOS_ENV_UNIX

#endif

    return true;
}
//---------------------------------------------------------------------------
