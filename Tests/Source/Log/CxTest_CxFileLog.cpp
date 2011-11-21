/**
 * \file   CxTest_CxFileLog.cpp
 * \brief
 */


#include <Test/Log/CxTest_CxFileLog.h>


//---------------------------------------------------------------------------
CxTest_CxFileLog::CxTest_CxFileLog() {

}
//---------------------------------------------------------------------------
CxTest_CxFileLog::~CxTest_CxFileLog() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxFileLog::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::tstring csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.log");

    CxFileLog flLog(1);

    //--------------------------------------------------
    //bSetFilePath, sGetFilePath
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = flLog.bSetFilePath(csFilePath);
        xTEST_DIFF(false, m_bRes);

        m_sRes = flLog.sGetFilePath();
        xTEST_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //bWrite
    xTEST_CASE(cullBlockLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_bRes = flLog.bWrite(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_DIFF(false, m_bRes);
            xTEST_LESS(0L, CxFile::liGetSize( flLog.sGetFilePath()) );
        }
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = flLog.bClear();
        xTEST_DIFF(false, m_bRes);
        xTEST_EQ(0L, CxFile::liGetSize( flLog.sGetFilePath()) );
    }

    //--------------------------------------------------
    //bDelete
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = flLog.bDelete();
        xTEST_DIFF(false, m_bRes);
        xTEST_EQ(false, CxFile::bIsExists( flLog.sGetFilePath()) );
    }

    return true;
}
//---------------------------------------------------------------------------
