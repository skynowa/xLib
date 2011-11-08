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
CxTest_CxFileLog::CxTest_CxFileLog() {

}
//---------------------------------------------------------------------------
CxTest_CxFileLog::~CxTest_CxFileLog() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxFileLog::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::string_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.log");

    CxFileLog flLog(1);

    //--------------------------------------------------
    //bSetFilePath, sGetFilePath
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = flLog.bSetFilePath(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_sRes = flLog.sGetFilePath();
        xTEST_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //bWrite
    xTEST_BLOCK(cullBlockLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_bRes = flLog.bWrite(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_DIFF(FALSE, m_bRes);
            xTEST_LESS(0L, CxFile::liGetSize( flLog.sGetFilePath()) );
        }
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = flLog.bClear();
        xTEST_DIFF(FALSE, m_bRes);
        xTEST_EQ(0L, CxFile::liGetSize( flLog.sGetFilePath()) );
    }

    //--------------------------------------------------
    //bDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = flLog.bDelete();
        xTEST_DIFF(FALSE, m_bRes);
        xTEST_EQ(FALSE, CxFile::bIsExists( flLog.sGetFilePath()) );
    }

    return TRUE;
}
//---------------------------------------------------------------------------
