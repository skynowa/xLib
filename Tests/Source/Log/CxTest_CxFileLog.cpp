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
CxTest_CxFileLog::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.log");

    CxFileLog flLog(1);

    //--------------------------------------------------
    //bSetFilePath, sGetFilePath
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = flLog.bSetFilePath(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_sRes = flLog.sGetFilePath();
        xASSERT_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //bWrite
    xTEST_BLOCK(cullBlockLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_bRes = flLog.bWrite(xT("simple log string: %s"), xT("qwerty01234567890"));
            xASSERT_NOT_EQ(FALSE, m_bRes);
            xASSERT_LESS(0L, CxStdioFile::liGetSize( flLog.sGetFilePath()) );
        }
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = flLog.bClear();
        xASSERT_NOT_EQ(FALSE, m_bRes);
        xASSERT_EQ(0L, CxStdioFile::liGetSize( flLog.sGetFilePath()) );
    }

    //--------------------------------------------------
    //bDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = flLog.bDelete();
        xASSERT_NOT_EQ(FALSE, m_bRes);
        xASSERT_EQ(FALSE, CxStdioFile::bIsExists( flLog.sGetFilePath()) );
    }

    return TRUE;
}
//---------------------------------------------------------------------------
