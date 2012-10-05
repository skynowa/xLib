/**
 * \file   CxTest_CxCookiePv1.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxCookiePv1.h>

#include <xLib/Common/CxString.h>


//---------------------------------------------------------------------------
CxTest_CxCookiePv1::CxTest_CxCookiePv1() {

}
//---------------------------------------------------------------------------
CxTest_CxCookiePv1::~CxTest_CxCookiePv1() {

}
//---------------------------------------------------------------------------
/* virtual */
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

        ckCookiePv1.vSetName(csName);

        m_sRv = ckCookiePv1.sGetName();
        xTEST_EQ(csName, m_sRv);

        ckCookiePv1.vSetValue(csValue);

        m_sRv = ckCookiePv1.sGetValue();
        xTEST_EQ(csValue, m_sRv);

        ckCookiePv1.vSetComment(csComment);

        m_sRv = ckCookiePv1.sGetComment();
        xTEST_EQ(csComment, m_sRv);

        ckCookiePv1.vSetDomain(csDomain);

        m_sRv = ckCookiePv1.sGetDomain();
        xTEST_EQ(csDomain, m_sRv);

        ckCookiePv1.vSetPath(csPath);

        m_sRv = ckCookiePv1.sGetPath();
        xTEST_EQ(csPath, m_sRv);

        ckCookiePv1.vSetMaxAge(ciMaxAge);

        m_llRv = ckCookiePv1.liGetMaxAge();
        xTEST_EQ(ciMaxAge, m_llRv);

        ckCookiePv1.vSetSecure(cbSecure);

        m_bRv = ckCookiePv1.bGetSecure();
        xTEST_EQ(cbSecure, m_bRv);

         ckCookiePv1.vSetHttpOnly(cbHttpOnly);

        m_bRv = ckCookiePv1.bGetHttpOnly();
        xTEST_EQ(cbHttpOnly, m_bRv);

        m_sRv = ckCookiePv1.sToString();
        xTEST_EQ(csRawCookie, m_sRv);

        {
            CxCookiePv1 _ckCookiePv0(ckCookiePv1.sToString());
            xTEST_EQ(_ckCookiePv0.sToString(), csRawCookie);
            xTEST_EQ(ckCookiePv1.sToString() , _ckCookiePv0.sToString());
        }

        ckCookiePv1.vClear();
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

        ckCookiePv1.vClear();
    }

    return true;
}
//---------------------------------------------------------------------------
