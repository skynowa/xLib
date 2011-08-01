/****************************************************************************
* Class name:  CxTest_CxFileLog
* Description: test CxFileLog
* File name:   CxFileLog.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#include <Test/Log/CxTest_CxFileLog.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxFileLog
CxTest_CxFileLog::CxTest_CxFileLog() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxFileLog
CxTest_CxFileLog::~CxTest_CxFileLog() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxFileLog::bUnit() {
    const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.log");

    CxFileLog flLog(1);

    //--------------------------------------------------
    //bSetFilePath, sGetFilePath
    {
        m_bRes = flLog.bSetFilePath(csFilePath);
        xASSERT_EQUAL(TRUE, m_bRes);

        m_sRes = flLog.sGetFilePath();
        xASSERT_EQUAL(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //bWrite
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_bRes = flLog.bWrite(xT("simple log string: %s"), xT("qwerty01234567890"));
            xASSERT_EQUAL(TRUE, m_bRes);
            xASSERT_LESS(0L, CxStdioFile::liGetSize( flLog.sGetFilePath()) );
        }
    }

    //--------------------------------------------------
    //bClear
    {
        m_bRes = flLog.bClear();
        xASSERT_EQUAL(TRUE, m_bRes);
        xASSERT_EQUAL(0, CxStdioFile::liGetSize( flLog.sGetFilePath()) );
    }

    //--------------------------------------------------
    //bDelete
    {
        m_bRes = flLog.bDelete();
        xASSERT_EQUAL(TRUE, m_bRes);
        xASSERT_EQUAL(FALSE, CxStdioFile::bIsExists( flLog.sGetFilePath()) );
    }

    return TRUE;
}
//---------------------------------------------------------------------------
