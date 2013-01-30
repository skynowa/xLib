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

    xTEST_CASE("CxFileLog::setFilePath filePath", cullCaseLoops)
    {
        flLog.setFilePath(csFilePath);

        m_sRv = flLog.filePath();
        xTEST_EQ(csFilePath, m_sRv);
    }

    xTEST_CASE("CxFileLog::write", cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            flLog.write(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_LESS(0LL, CxFile::size( flLog.filePath()) );
        }
    }

    xTEST_CASE("CxFileLog::clear", cullCaseLoops)
    {
        flLog.clear();
        xTEST_EQ(0LL, CxFile::size( flLog.filePath()) );
    }

    xTEST_CASE("CxFileLog::remove", cullCaseLoops)
    {
        flLog.remove();
        xTEST_EQ(false, CxFile::isExists( flLog.filePath()) );
    }
}
//---------------------------------------------------------------------------
