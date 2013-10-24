/**
 * \file   CxTest_CxFileLog.cpp
 * \brief
 */


#include <Test/Log/CxTest_CxFileLog.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Filesystem/CxFile.h>


//------------------------------------------------------------------------------
CxTest_CxFileLog::CxTest_CxFileLog() {

}
//------------------------------------------------------------------------------
CxTest_CxFileLog::~CxTest_CxFileLog() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxFileLog::unit(
    culonglong_t &a_cullCaseLoops
)
{
    std::ctstring_t csFilePath = tempDirPath() + CxConst::xSLASH() + xT("Test.log");

    CxFileLog flLog(1);

    xTEST_CASE("CxFileLog::setFilePath filePath", a_cullCaseLoops)
    {
        flLog.setFilePath(csFilePath);

        m_sRv = flLog.filePath();
        xTEST_EQ(csFilePath, m_sRv);
    }

    xTEST_CASE("CxFileLog::write", a_cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            flLog.write(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_LESS(0LL, CxFile::size( flLog.filePath()) );
        }
    }

    xTEST_CASE("CxFileLog::clear", a_cullCaseLoops)
    {
        flLog.clear();
        xTEST_EQ(0LL, CxFile::size( flLog.filePath()) );
    }

    xTEST_CASE("CxFileLog::remove", a_cullCaseLoops)
    {
        flLog.remove();
        xTEST_EQ(false, CxFile::isExists( flLog.filePath()) );
    }
}
//------------------------------------------------------------------------------
