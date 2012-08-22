/**
 * \file   CxTest_CxFileLog.cpp
 * \brief
 */


#include <Test/Log/CxTest_CxFileLog.h>

#include <xLib/Filesystem/CxFile.h>


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
    const ulonglong_t cullCaseLoops
)
{
    const std::tstring_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.log");

    CxFileLog flLog(1);

    //--------------------------------------------------
    //bSetFilePath, sGetFilePath
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = flLog.bSetFilePath(csFilePath);
        xTEST_EQ(true, m_bRv);

        m_sRv = flLog.sGetFilePath();
        xTEST_EQ(csFilePath, m_sRv);
    }

    //--------------------------------------------------
    //bWrite
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_bRv = flLog.bWrite(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_EQ(true, m_bRv);
            xTEST_LESS(0LL, CxFile::llGetSize( flLog.sGetFilePath()) );
        }
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = flLog.bClear();
        xTEST_EQ(true, m_bRv);
        xTEST_EQ(0LL, CxFile::llGetSize( flLog.sGetFilePath()) );
    }

    //--------------------------------------------------
    //bDelete
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = flLog.bDelete();
        xTEST_EQ(true, m_bRv);
        xTEST_EQ(false, CxFile::bIsExists( flLog.sGetFilePath()) );
    }

    return true;
}
//---------------------------------------------------------------------------
