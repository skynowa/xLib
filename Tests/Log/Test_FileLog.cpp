/**
 * \file   Test_FileLog.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
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
        log.write(ILog::Level::Unknown,  xT("\t%s, %d"), xLEX_TO_STR(ILog::L::::Unknown),    12345);
        log.write(ILog::Level::Emerg,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Emerg),    12345);
        log.write(ILog::Level::Alert,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Alert),    12345);
        log.write(ILog::Level::Critical, xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        log.write(ILog::Level::Error,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Error),    12345);
        log.write(ILog::Level::Warning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Warning),  12345);
        log.write(ILog::Level::Notice,   xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Notice),   12345);
        log.write(ILog::Level::Info,     xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Info),     12345);
        log.write(ILog::Level::Debug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Debug),    12345);
        log.write(ILog::Level::Plain,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Plain),    12345);
    }

    xTEST_CASE("clear")
    {
        log.clear();
        xTEST_EQ(FileInfo( log.filePath( )).size(), longlong_t(0));
    }

    xTEST_CASE("remove")
    {
        log.remove();
        xTEST(!FileInfo(log.filePath()).isExists());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
