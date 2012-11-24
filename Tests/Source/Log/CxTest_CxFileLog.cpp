/**
 * \file   CxTest_CxFileLog.cpp
 * \brief
 */


#include <Test/Log/CxTest_CxFileLog.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Filesystem/CxFile.h>


//---------------------------------------------------------------------------
CxTest_CxFileLog::CxTest_CxFileLog() {

}
//---------------------------------------------------------------------------
CxTest_CxFileLog::~CxTest_CxFileLog() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxFileLog::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("Test.log");

    CxFileLog flLog(1);

    xTEST_CASE("CxFileLog::vSetFilePath FilePath", cullCaseLoops)
    {
        flLog.vSetFilePath(csFilePath);

        m_sRv = flLog.sFilePath();
        xTEST_EQ(csFilePath, m_sRv);
    }

    xTEST_CASE("CxFileLog::vWrite", cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            flLog.vWrite(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_LESS(0LL, CxFile::llSize( flLog.sFilePath()) );
        }
    }

    xTEST_CASE("CxFileLog::vClear", cullCaseLoops)
    {
        flLog.vClear();
        xTEST_EQ(0LL, CxFile::llSize( flLog.sFilePath()) );
    }

    xTEST_CASE("CxFileLog::vDelete", cullCaseLoops)
    {
        flLog.vDelete();
        xTEST_EQ(false, CxFile::bIsExists( flLog.sFilePath()) );
    }
}
//---------------------------------------------------------------------------
