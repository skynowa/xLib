/****************************************************************************
* Class name:  CxTest_CxReport
* Description: test CxReport
* File name:   CxTest_CxReport.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxReport (constructor)
CxTest_CxReport::CxTest_CxReport() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxReport (destructor)
CxTest_CxReport::~CxTest_CxReport() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
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

