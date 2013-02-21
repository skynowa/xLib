/**
 * \file   CxTest_CxCookiePv1.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxCookiePv1.h>

#include <xLib/Common/CxString.h>


//------------------------------------------------------------------------------
CxTest_CxCookiePv1::CxTest_CxCookiePv1() {

}
//------------------------------------------------------------------------------
CxTest_CxCookiePv1::~CxTest_CxCookiePv1() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxCookiePv1::unit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csName      = xT("Name1");
    const std::tstring_t csValue     = xT("Value1");
    const std::tstring_t csComment   = xT("Comment1");
    const std::tstring_t csDomain    = xT(".domain.com1");
    const std::tstring_t csPath      = xT("/1");
    const longlong_t     ciMaxAge    = 10 * 60 * 60;
    const bool           cbSecure    = true;
    const bool           cbHttpOnly  = true;
    const std::tstring_t csRawCookie = CxString::format(
                                        xT("%s=\"%s\"; Comment=\"%s\"; Domain=\"%s\"; Path=\"%s\"; Max-Age=\"%lli\"; Secure; HttpOnly; Version=\"1\""),
                                        csName.c_str(), csValue.c_str(), csComment.c_str(), csDomain.c_str(), 
                                        csPath.c_str(), ciMaxAge /*cbSecure = true, cbHttpOnly = true*/);

    xTEST_CASE("CxCookiePv1::CxCookiePv1", cullCaseLoops)
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

    xTEST_CASE("CxCookiePv1::CxCookiePv1(const std::tstring_t &)", cullCaseLoops)
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
