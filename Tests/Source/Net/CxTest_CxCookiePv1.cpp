/****************************************************************************
* Class name:  CxTest_CxCookiePv1
* Description: test CxCookiePv1
* File name:   CxTest_CxCookiePv1.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxCookiePv1.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxCookiePv1
CxTest_CxCookiePv1::CxTest_CxCookiePv1() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxCookiePv1
CxTest_CxCookiePv1::~CxTest_CxCookiePv1() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxCookiePv1::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const tString   csName      = xT("Name1");
    const tString   csValue     = xT("Value1");
    const tString   csComment   = xT("Comment1");
    const tString   csDomain    = xT(".domain.com1");
    const tString   csPath      = xT("/1");
    const LONGLONG  ciMaxAge    = 10 * 60 * 60;
    const BOOL      cbSecure    = TRUE;
    const BOOL      cbHttpOnly  = TRUE;
    const tString   csRawCookie = CxString::sFormat(
                                        xT("%s=\"%s\"; Comment=\"%s\"; Domain=\"%s\"; Path=\"%s\"; Max-Age=\"%lli\"; Secure; HttpOnly; Version=\"1\""),
                                        csName.c_str(), csValue.c_str(), csComment.c_str(), csDomain.c_str(), csPath.c_str(), ciMaxAge /*cbSecure = TRUE, cbHttpOnly = TRUE*/
                                    );

    //--------------------------------------------------
    //CxCookiePv1()
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCookiePv1 ckCookiePv1;

        m_bRes = ckCookiePv1.bSetName(csName);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_sRes = ckCookiePv1.sGetName();
        xASSERT_EQ(csName, m_sRes);

        m_bRes = ckCookiePv1.bSetValue(csValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_sRes = ckCookiePv1.sGetValue();
        xASSERT_EQ(csValue, m_sRes);

        m_bRes = ckCookiePv1.bSetComment(csComment);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_sRes = ckCookiePv1.sGetComment();
        xASSERT_EQ(csComment, m_sRes);

        m_bRes = ckCookiePv1.bSetDomain(csDomain);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_sRes = ckCookiePv1.sGetDomain();
        xASSERT_EQ(csDomain, m_sRes);

        m_bRes = ckCookiePv1.bSetPath(csPath);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_sRes = ckCookiePv1.sGetPath();
        xASSERT_EQ(csPath, m_sRes);

        m_bRes = ckCookiePv1.bSetMaxAge(ciMaxAge);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_llRes = ckCookiePv1.liGetMaxAge();
        xASSERT_EQ(ciMaxAge, m_llRes);

        m_bRes = ckCookiePv1.bSetSecure(cbSecure);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_bRes = ckCookiePv1.bGetSecure();
        xASSERT_EQ(cbSecure, m_bRes);

        m_bRes = ckCookiePv1.bSetHttpOnly(cbHttpOnly);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        m_bRes = ckCookiePv1.bGetHttpOnly();
        xASSERT_EQ(cbHttpOnly, m_bRes);

        m_sRes = ckCookiePv1.sToString();
        xASSERT_EQ(csRawCookie, m_sRes);

        {
            CxCookiePv1 _ckCookiePv0(ckCookiePv1.sToString());
            xASSERT_EQ(_ckCookiePv0.sToString(), csRawCookie);
            xASSERT_EQ(ckCookiePv1.sToString() , _ckCookiePv0.sToString());
        }

        m_bRes = ckCookiePv1.bClear();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //CxCookiePv1(const tString &);
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCookiePv1 ckCookiePv1(csRawCookie);

        m_sRes = ckCookiePv1.sGetName();
        xASSERT_EQ(csName, m_sRes);

        m_sRes = ckCookiePv1.sGetValue();
        xASSERT_EQ(csValue, m_sRes);

        m_sRes = ckCookiePv1.sGetComment();
        xASSERT_EQ(csComment, m_sRes);

        m_sRes = ckCookiePv1.sGetDomain();
        xASSERT_EQ(csDomain, m_sRes);

        m_sRes = ckCookiePv1.sGetPath();
        xASSERT_EQ(csPath, m_sRes);

        m_llRes = ckCookiePv1.liGetMaxAge();
        xASSERT_EQ(ciMaxAge, m_llRes);

        m_bRes = ckCookiePv1.bGetSecure();
        xASSERT_EQ(cbSecure, m_bRes);

        m_bRes = ckCookiePv1.bGetHttpOnly();
        xASSERT_EQ(cbHttpOnly, m_bRes);

        m_sRes = ckCookiePv1.sToString();
        xASSERT_EQ(csRawCookie, m_sRes);

        m_bRes = ckCookiePv1.bClear();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
