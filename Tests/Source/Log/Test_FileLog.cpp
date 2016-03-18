/**
 * \file   Test_FileLog.cpp
 * \brief
 */


#include <Test/Log/Test_FileLog.h>

#include <xLib/Core/Const.h>
#include <xLib/IO/File.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_FileLog)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_FileLog::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t filePath = tempDirPath() + Const::slash() + xT("FileLog.log");

    FileLog log(FileLog::lsDefaultMb);

    xTEST_CASE("setFilePath, filePath", a_caseLoops)
    {
        log.setFilePath(filePath);

        m_sRv = log.filePath();
        xTEST_EQ(filePath, m_sRv);
    }

    xTEST_CASE("write", a_caseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            log.write(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_GR(File::size(log.filePath()), longlong_t(0));
        }
    }

    xTEST_CASE("write(...)", a_caseLoops)
    {
        log.write(ILog::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(ILog::lvUnknown),  12345);
        log.write(ILog::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvEmerg),    12345);
        log.write(ILog::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvAlert),    12345);
        log.write(ILog::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(ILog::lvCritical), 12345);
        log.write(ILog::lvError,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvError),    12345);
        log.write(ILog::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::lvWarning),  12345);
        log.write(ILog::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(ILog::lvNotice),   12345);
        log.write(ILog::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(ILog::lvInfo),     12345);
        log.write(ILog::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvDebug),    12345);
        log.write(ILog::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvPlain),    12345);
    }

    xTEST_CASE("clear", a_caseLoops)
    {
        log.clear();
        xTEST_EQ(File::size( log.filePath()), longlong_t(0));
    }

    xTEST_CASE("remove", a_caseLoops)
    {
        log.remove();
        xTEST_EQ(false, File::isExists( log.filePath()) );
    }
}
//-------------------------------------------------------------------------------------------------
