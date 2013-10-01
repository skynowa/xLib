/**
 * \file   CxTest_CxCookiePv1.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxCookiePv1.h>

#include <xLib/Core/CxString.h>


//------------------------------------------------------------------------------
CxTest_CxCookiePv1::CxTest_CxCookiePv1() {

}
//------------------------------------------------------------------------------
CxTest_CxCookiePv1::~CxTest_CxCookiePv1() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxCookiePv1::unit(
    culonglong_t &a_cullCaseLoops
)
{
    std::ctstring_t csName      = xT("Name1");
    std::ctstring_t csValue     = xT("Value1");
    std::ctstring_t csComment   = xT("Comment1");
    std::ctstring_t csDomain    = xT(".domain.com1");
    std::ctstring_t csPath      = xT("/1");
    clonglong_t     ciMaxAge    = 10 * 60 * 60;
    cbool_t           cbSecure    = true;
    cbool_t           cbHttpOnly  = true;
    std::ctstring_t csRawCookie = CxString::format(
                                        xT("%s=\"%s\"; Comment=\"%s\"; Domain=\"%s\"; Path=\"%s\"; Max-Age=\"%lli\"; Secure; HttpOnly; Version=\"1\""),
                                        csName.c_str(), csValue.c_str(), csComment.c_str(), csDomain.c_str(),
                                        csPath.c_str(), ciMaxAge /*cbSecure = true, cbHttpOnly = true*/);

    xTEST_CASE("CxCookiePv1::CxCookiePv1", a_cullCaseLoops)
    {
        CxCookiePv1 ckCookiePv1;

        ckCookiePv1.setName(csName);

        m_sRv = ckCookiePv1.name();
        xTEST_EQ(csName, m_sRv);

        ckCookiePv1.setValue(csValue);

        m_sRv = ckCookiePv1.value();
        xTEST_EQ(csValue, m_sRv);

        ckCookiePv1.setComment(csComment);

        m_sRv = ckCookiePv1.comment();
        xTEST_EQ(csComment, m_sRv);

        ckCookiePv1.setDomain(csDomain);

        m_sRv = ckCookiePv1.domain();
        xTEST_EQ(csDomain, m_sRv);

        ckCookiePv1.setPath(csPath);

        m_sRv = ckCookiePv1.path();
        xTEST_EQ(csPath, m_sRv);

        ckCookiePv1.setMaxAge(ciMaxAge);

        m_llRv = ckCookiePv1.maxAge();
        xTEST_EQ(ciMaxAge, m_llRv);

        ckCookiePv1.setSecure(cbSecure);

        m_bRv = ckCookiePv1.secure();
        xTEST_EQ(cbSecure, m_bRv);

         ckCookiePv1.setHttpOnly(cbHttpOnly);

        m_bRv = ckCookiePv1.httpOnly();
        xTEST_EQ(cbHttpOnly, m_bRv);

        m_sRv = ckCookiePv1.toString();
        xTEST_EQ(csRawCookie, m_sRv);

        {
            CxCookiePv1 _ckCookiePv0(ckCookiePv1.toString());
            xTEST_EQ(_ckCookiePv0.toString(), csRawCookie);
            xTEST_EQ(ckCookiePv1.toString() , _ckCookiePv0.toString());
        }

        ckCookiePv1.clear();
    }

    xTEST_CASE("CxCookiePv1::CxCookiePv1(std::ctstring_t &)", a_cullCaseLoops)
    {
        CxCookiePv1 ckCookiePv1(csRawCookie);

        m_sRv = ckCookiePv1.name();
        xTEST_EQ(csName, m_sRv);

        m_sRv = ckCookiePv1.value();
        xTEST_EQ(csValue, m_sRv);

        m_sRv = ckCookiePv1.comment();
        xTEST_EQ(csComment, m_sRv);

        m_sRv = ckCookiePv1.domain();
        xTEST_EQ(csDomain, m_sRv);

        m_sRv = ckCookiePv1.path();
        xTEST_EQ(csPath, m_sRv);

        m_llRv = ckCookiePv1.maxAge();
        xTEST_EQ(ciMaxAge, m_llRv);

        m_bRv = ckCookiePv1.secure();
        xTEST_EQ(cbSecure, m_bRv);

        m_bRv = ckCookiePv1.httpOnly();
        xTEST_EQ(cbHttpOnly, m_bRv);

        m_sRv = ckCookiePv1.toString();
        xTEST_EQ(csRawCookie, m_sRv);

        ckCookiePv1.clear();
    }
}
//------------------------------------------------------------------------------
