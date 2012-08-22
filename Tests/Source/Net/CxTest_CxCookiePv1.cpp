/**
 * \file   CxTest_CxCookiePv1.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxCookiePv1.h>


//---------------------------------------------------------------------------
CxTest_CxCookiePv1::CxTest_CxCookiePv1() {

}
//---------------------------------------------------------------------------
CxTest_CxCookiePv1::~CxTest_CxCookiePv1() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxCookiePv1::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const std::tstring_t   csName      = xT("Name1");
    const std::tstring_t   csValue     = xT("Value1");
    const std::tstring_t   csComment   = xT("Comment1");
    const std::tstring_t   csDomain    = xT(".domain.com1");
    const std::tstring_t   csPath      = xT("/1");
    const longlong_t  ciMaxAge    = 10 * 60 * 60;
    const bool      cbSecure    = true;
    const bool      cbHttpOnly  = true;
    const std::tstring_t   csRawCookie = CxString::sFormat(
                                        xT("%s=\"%s\"; Comment=\"%s\"; Domain=\"%s\"; Path=\"%s\"; Max-Age=\"%lli\"; Secure; HttpOnly; Version=\"1\""),
                                        csName.c_str(), csValue.c_str(), csComment.c_str(), csDomain.c_str(), csPath.c_str(), ciMaxAge /*cbSecure = true, cbHttpOnly = true*/
                                    );

    //--------------------------------------------------
    //CxCookiePv1()
    xTEST_CASE(cullCaseLoops)
    {
        CxCookiePv1 ckCookiePv1;

        m_bRv = ckCookiePv1.bSetName(csName);
        xTEST_EQ(true, m_bRv);
        m_sRv = ckCookiePv1.sGetName();
        xTEST_EQ(csName, m_sRv);

        m_bRv = ckCookiePv1.bSetValue(csValue);
        xTEST_EQ(true, m_bRv);
        m_sRv = ckCookiePv1.sGetValue();
        xTEST_EQ(csValue, m_sRv);

        m_bRv = ckCookiePv1.bSetComment(csComment);
        xTEST_EQ(true, m_bRv);
        m_sRv = ckCookiePv1.sGetComment();
        xTEST_EQ(csComment, m_sRv);

        m_bRv = ckCookiePv1.bSetDomain(csDomain);
        xTEST_EQ(true, m_bRv);
        m_sRv = ckCookiePv1.sGetDomain();
        xTEST_EQ(csDomain, m_sRv);

        m_bRv = ckCookiePv1.bSetPath(csPath);
        xTEST_EQ(true, m_bRv);
        m_sRv = ckCookiePv1.sGetPath();
        xTEST_EQ(csPath, m_sRv);

        m_bRv = ckCookiePv1.bSetMaxAge(ciMaxAge);
        xTEST_EQ(true, m_bRv);
        m_llRv = ckCookiePv1.liGetMaxAge();
        xTEST_EQ(ciMaxAge, m_llRv);

        m_bRv = ckCookiePv1.bSetSecure(cbSecure);
        xTEST_EQ(true, m_bRv);
        m_bRv = ckCookiePv1.bGetSecure();
        xTEST_EQ(cbSecure, m_bRv);

        m_bRv = ckCookiePv1.bSetHttpOnly(cbHttpOnly);
        xTEST_EQ(true, m_bRv);
        m_bRv = ckCookiePv1.bGetHttpOnly();
        xTEST_EQ(cbHttpOnly, m_bRv);

        m_sRv = ckCookiePv1.sToString();
        xTEST_EQ(csRawCookie, m_sRv);

        {
            CxCookiePv1 _ckCookiePv0(ckCookiePv1.sToString());
            xTEST_EQ(_ckCookiePv0.sToString(), csRawCookie);
            xTEST_EQ(ckCookiePv1.sToString() , _ckCookiePv0.sToString());
        }

        m_bRv = ckCookiePv1.bClear();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //CxCookiePv1(const std::tstring_t &);
    xTEST_CASE(cullCaseLoops)
    {
        CxCookiePv1 ckCookiePv1(csRawCookie);

        m_sRv = ckCookiePv1.sGetName();
        xTEST_EQ(csName, m_sRv);

        m_sRv = ckCookiePv1.sGetValue();
        xTEST_EQ(csValue, m_sRv);

        m_sRv = ckCookiePv1.sGetComment();
        xTEST_EQ(csComment, m_sRv);

        m_sRv = ckCookiePv1.sGetDomain();
        xTEST_EQ(csDomain, m_sRv);

        m_sRv = ckCookiePv1.sGetPath();
        xTEST_EQ(csPath, m_sRv);

        m_llRv = ckCookiePv1.liGetMaxAge();
        xTEST_EQ(ciMaxAge, m_llRv);

        m_bRv = ckCookiePv1.bGetSecure();
        xTEST_EQ(cbSecure, m_bRv);

        m_bRv = ckCookiePv1.bGetHttpOnly();
        xTEST_EQ(cbHttpOnly, m_bRv);

        m_sRv = ckCookiePv1.sToString();
        xTEST_EQ(csRawCookie, m_sRv);

        m_bRv = ckCookiePv1.bClear();
        xTEST_EQ(true, m_bRv);
    }

    return true;
}
//---------------------------------------------------------------------------
