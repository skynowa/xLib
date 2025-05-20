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
    std::ctstring_t filePath = option().tempDirPath + Const::slash() + xT("FileLog.log");

    FileLog log(filePath, FileLog::LogSizes::DefaultMb);

    xTEST_CASE("write")
    {
        for (size_t i = 0; i < 10; ++ i) {
            log.write(ILog::Level::Trace, xT("simple log string: %s"), xT("qwerty01234567890"));
            xTEST_GR(FileInfo(filePath).size(), longlong_t(0));
        }
    }

    xTEST_CASE("write(...)")
    {
        log.write(ILog::Level::Off,      xT("%s, %d"), xLEX_TO_STR(ILog::Level::Unknown), 12345);
        log.write(ILog::Level::Critical, xT("%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        log.write(ILog::Level::Warning,  xT("%s, %d"), xLEX_TO_STR(ILog::Level::Warning), 12345);
        log.write(ILog::Level::Critical, xT("%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        log.write(ILog::Level::Error,    xT("%s, %d"), xLEX_TO_STR(ILog::Level::Error), 12345);
        log.write(ILog::Level::Warning,  xT("%s, %d"), xLEX_TO_STR(ILog::Level::Warning), 12345);
        log.write(ILog::Level::Trace,    xT("%s, %d"), xLEX_TO_STR(ILog::Level::Trace), 12345);
        log.write(ILog::Level::Info,     xT("%s, %d"), xLEX_TO_STR(ILog::Level::Info), 12345);
        log.write(ILog::Level::Debug,    xT("%s, %d"), xLEX_TO_STR(ILog::Level::Debug), 12345);
        log.write(ILog::Level::Trace,    xT("%s, %d"), xLEX_TO_STR(ILog::Level::Trace), 12345);
    }

    xTEST_CASE("clear")
    {
		log.clear();
		xTEST_EQ(FileInfo(filePath).size(), longlong_t(0));
    }

    xTEST_CASE("remove")
    {
		log.remove();
		xTEST(!FileInfo(filePath).isExists());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
