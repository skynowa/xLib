/**
 * \file   CxTest_CxFileLog.cpp
 * \brief
 */


#include <Test/Log/CxTest_CxFileLog.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Filesystem/CxFile.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxFileLog::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t filePath = tempDirPath() + CxConst::slash() + xT("Test.log");

    CxFileLog log(1);

    xTEST_CASE("CxFileLog::setFilePath filePath", a_caseLoops)
    {
        log.setFilePath(filePath);

        m_sRv = log.filePath();
        xTEST_EQ(filePath, m_sRv);
    }

    xTEST_CASE("CxFileLog::write", a_caseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            log.write(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_LESS(0LL, CxFile::size( log.filePath()) );
        }
    }

    xTEST_CASE("CxFileLog::clear", a_caseLoops)
    {
        log.clear();
        xTEST_EQ(0LL, CxFile::size( log.filePath()) );
    }

    xTEST_CASE("CxFileLog::remove", a_caseLoops)
    {
        log.remove();
        xTEST_EQ(false, CxFile::isExists( log.filePath()) );
    }
}
//-------------------------------------------------------------------------------------------------
