/****************************************************************************
* Class name:  CxTest_CxCookiePv1
* Description: test CxCookiePv1
* File name:   CxTest_CxCookiePv1.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCookiePv1H
#define CxTest_CxCookiePv1H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxCookiePv1.h>
//---------------------------------------------------------------------------
class CxTest_CxCookiePv1 :
    public CxTest
{
	public:
		CxTest_CxCookiePv1();
		virtual     ~CxTest_CxCookiePv1();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxCookiePv1 (constructor)
CxTest_CxCookiePv1::CxTest_CxCookiePv1() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxCookiePv1 (destructor)
CxTest_CxCookiePv1::~CxTest_CxCookiePv1() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxCookiePv1::bUnit() {
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
    {
        CxCookiePv1 ckCookiePv1;

        m_bRes = ckCookiePv1.bSetName(csName);
        xASSERT(FALSE != m_bRes);
        m_sRes = ckCookiePv1.sGetName();
        xASSERT(csName == m_sRes);

        m_bRes = ckCookiePv1.bSetValue(csValue);
        xASSERT(FALSE != m_bRes);
        m_sRes = ckCookiePv1.sGetValue();
        xASSERT(csValue == m_sRes);

        m_bRes = ckCookiePv1.bSetComment(csComment);
        xASSERT(FALSE != m_bRes);
        m_sRes = ckCookiePv1.sGetComment();
        xASSERT(csComment == m_sRes);

        m_bRes = ckCookiePv1.bSetDomain(csDomain);
        xASSERT(FALSE != m_bRes);
        m_sRes = ckCookiePv1.sGetDomain();
        xASSERT(csDomain == m_sRes);

        m_bRes = ckCookiePv1.bSetPath(csPath);
        xASSERT(FALSE != m_bRes);
        m_sRes = ckCookiePv1.sGetPath();
        xASSERT(csPath == m_sRes);

        m_bRes = ckCookiePv1.bSetMaxAge(ciMaxAge);
        xASSERT(FALSE != m_bRes);
        m_ullRes = ckCookiePv1.liGetMaxAge();
        xASSERT(ciMaxAge == m_ullRes);

        m_bRes = ckCookiePv1.bSetSecure(cbSecure);
        xASSERT(FALSE != m_bRes);
        m_bRes = ckCookiePv1.bGetSecure();
        xASSERT(cbSecure == m_bRes);

        m_bRes = ckCookiePv1.bSetHttpOnly(cbHttpOnly);
        xASSERT(FALSE != m_bRes);
        m_bRes = ckCookiePv1.bGetHttpOnly();
        xASSERT(cbHttpOnly == m_bRes);

        m_sRes = ckCookiePv1.sToString();
        xASSERT_MSG(csRawCookie == m_sRes, csRawCookie + CxConst::xNL + m_sRes);

        {
            CxCookiePv1 _ckCookiePv0(ckCookiePv1.sToString());
            xASSERT_MSG(_ckCookiePv0.sToString() == csRawCookie,              _ckCookiePv0.sToString());
            xASSERT_MSG(ckCookiePv1.sToString()  == _ckCookiePv0.sToString(), _ckCookiePv0.sToString());
        }

        m_bRes = ckCookiePv1.bClear();
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //CxCookiePv1(const tString &);
    {
        CxCookiePv1 ckCookiePv1(csRawCookie);

        m_sRes = ckCookiePv1.sGetName();
        xASSERT(csName == m_sRes);

        m_sRes = ckCookiePv1.sGetValue();
        xASSERT(csValue == m_sRes);

        m_sRes = ckCookiePv1.sGetComment();
        xASSERT(csComment == m_sRes);

        m_sRes = ckCookiePv1.sGetDomain();
        xASSERT(csDomain == m_sRes);

        m_sRes = ckCookiePv1.sGetPath();
        xASSERT(csPath == m_sRes);

        m_llRes = ckCookiePv1.liGetMaxAge();
        xASSERT(ciMaxAge == m_llRes);

        m_bRes = ckCookiePv1.bGetSecure();
        xASSERT(cbSecure == m_bRes);

        m_bRes = ckCookiePv1.bGetHttpOnly();
        xASSERT(cbHttpOnly == m_bRes);

        m_sRes = ckCookiePv1.sToString();
        xASSERT_MSG(csRawCookie == m_sRes, csRawCookie + CxConst::xNL + m_sRes);

        m_bRes = ckCookiePv1.bClear();
        xASSERT(FALSE != m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxCookiePv1H
