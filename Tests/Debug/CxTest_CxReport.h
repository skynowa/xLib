/****************************************************************************
* Class name:  CxTest_CxReport
* Description: test CxReport
* File name:   CxTest_CxReport.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxReportH
#define CxTest_CxReportH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxReport.h>
//---------------------------------------------------------------------------
class CxTest_CxReport : public CxTest {
	public:
		CxTest_CxReport();
		virtual     ~CxTest_CxReport();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxReport (constructor)
CxTest_CxReport::CxTest_CxReport() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxReport (destructor)
CxTest_CxReport::~CxTest_CxReport() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxReport::bUnit() {
    //--------------------------------------------------
    //CxReport
    {
        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xT(__FILE__), __LINE__,  xT(xFUNCTION),  xT(__DATE__), xT(__TIME__), xT("Simple comment: %s"), xT("comment"));

        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }

    //--------------------------------------------------
    //CxReport
    {
        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xT(__FILE__), __LINE__,  xT(xFUNCTION),  xT(__DATE__), xT(__TIME__), tString(xT("Simple comment")));

        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }


    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxReportH

