/**
 * \file   Test_FileLog.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_FileLog)
xTEST_UNIT(Test_FileLog)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileLog::unit()
{
    std::ctstring_t filePath = getData().tempDirPath + Const::slash() + xT("FileLog.log");

    FileLog log(FileLog::LogSizes::lsDefaultMb);

    xTEST_CASE("setFilePath, filePath")
    {
        log.setFilePath(filePath);

        m_sRv = log.filePath();
        xTEST_EQ(filePath, m_sRv);
    }

    xTEST_CASE("write")
    {
        for (size_t i = 0; i < 10; ++ i) {
            log.write(xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_GR(FileInfo( log.filePath() ).size(), longlong_t(0));
        }
    }

    xTEST_CASE("write(...)")
    {
        log.write(ILog::Level::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvUnknown),  12345);
        log.write(ILog::Level::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvEmerg),    12345);
        log.write(ILog::Level::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvAlert),    12345);
        log.write(ILog::Level::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvCritical), 12345);
        log.write(ILog::Level::lvError,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvError),    12345);
        log.write(ILog::Level::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvWarning),  12345);
        log.write(ILog::Level::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvNotice),   12345);
        log.write(ILog::Level::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvInfo),     12345);
        log.write(ILog::Level::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvDebug),    12345);
        log.write(ILog::Level::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvPlain),    12345);
    }

    xTEST_CASE("clear")
    {
        log.clear();
        xTEST_EQ(FileInfo( log.filePath( )).size(), longlong_t(0));
    }

    xTEST_CASE("remove")
    {
        log.remove();
        xTEST(!FileInfo(log.filePath()).isExists() );
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
