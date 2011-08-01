/****************************************************************************
* Class name:  CxTest_CxCookiePv0
* Description: test CxCookiePv0
* File name:   CxTest_CxCookiePv0.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxCookiePv0.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxCookiePv0
CxTest_CxCookiePv0::CxTest_CxCookiePv0() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxCookiePv0
CxTest_CxCookiePv0::~CxTest_CxCookiePv0() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxCookiePv0::bUnit() {
    const tString csName      = xT("Name0");
    const tString csValue     = xT("Value0");
    const tString csDomain    = xT(".domain.com0");
    const tString csPath      = xT("/0");
    const tString csExpires   = xT("Wed, 13-Jan-2021 22:23:01 GMT");  //Thu, 22 Mar 2012 18:16:13 GMT
    const BOOL    cbSecure    = TRUE;
    const BOOL    cbHttpOnly  = TRUE;
    const tString csRawCookie = CxString::sFormat(
                                    xT("%s=%s; Domain=%s; Path=%s; Expires=%s; Secure; HttpOnly"),
                                    csName.c_str(), csValue.c_str(), csDomain.c_str(), csPath.c_str(), csExpires.c_str() /*cbSecure = TRUE, cbHttpOnly = TRUE*/
                                );

    //--------------------------------------------------
    //CxCookiePv0()
    {
        CxCookiePv0 ckCookiePv0;

        m_bRes = ckCookiePv0.bSetName(csName);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        m_sRes = ckCookiePv0.sGetName();
        xASSERT_EQUAL(csName, m_sRes);

        m_bRes = ckCookiePv0.bSetValue(csValue);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        m_sRes = ckCookiePv0.sGetValue();
        xASSERT_EQUAL(csValue, m_sRes);

        m_bRes = ckCookiePv0.bSetDomain(csDomain);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        m_sRes = ckCookiePv0.sGetDomain();
        xASSERT_EQUAL(csDomain, m_sRes);

        m_bRes = ckCookiePv0.bSetPath(csPath);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        m_sRes = ckCookiePv0.sGetPath();
        xASSERT_EQUAL(csPath, m_sRes);

        m_bRes = ckCookiePv0.bSetExpires(csExpires);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        m_sRes = ckCookiePv0.sGetExpires();
        xASSERT_EQUAL(csExpires, m_sRes);

        m_bRes = ckCookiePv0.bSetSecure(cbSecure);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        m_bRes = ckCookiePv0.bGetSecure();
        xASSERT_EQUAL(cbSecure, m_bRes);

        m_bRes = ckCookiePv0.bSetHttpOnly(cbHttpOnly);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        m_bRes = ckCookiePv0.bGetHttpOnly();
        xASSERT_EQUAL(cbHttpOnly, m_bRes);

        m_sRes = ckCookiePv0.sToString();
        xASSERT_EQUAL(csRawCookie, m_sRes);

        {
            CxCookiePv0 _ckCookiePv0(ckCookiePv0.sToString());
            xASSERT_EQUAL(_ckCookiePv0.sToString(), csRawCookie);
            xASSERT_EQUAL(ckCookiePv0.sToString() , _ckCookiePv0.sToString());
        }

        m_bRes = ckCookiePv0.bClear();
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //CxCookiePv0(const tString &);
    {
        CxCookiePv0 ckCookiePv0(csRawCookie);

        m_sRes = ckCookiePv0.sGetName();
        xASSERT_EQUAL(csName, m_sRes);

        m_sRes = ckCookiePv0.sGetValue();
        xASSERT_EQUAL(csValue, m_sRes);

        m_sRes = ckCookiePv0.sGetDomain();
        xASSERT_EQUAL(csDomain, m_sRes);

        m_sRes = ckCookiePv0.sGetPath();
        xASSERT_EQUAL(csPath, m_sRes);

        m_sRes = ckCookiePv0.sGetExpires();
        xASSERT_EQUAL(csExpires, m_sRes);

        m_bRes = ckCookiePv0.bGetSecure();
        xASSERT_EQUAL(cbSecure, m_bRes);

        m_bRes = ckCookiePv0.bGetHttpOnly();
        xASSERT_EQUAL(cbHttpOnly, m_bRes);

        m_sRes = ckCookiePv0.sToString();
        xASSERT_EQUAL(csRawCookie, m_sRes);

        m_bRes = ckCookiePv0.bClear();
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
