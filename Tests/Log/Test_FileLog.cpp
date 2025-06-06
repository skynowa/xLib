/**
 * \file  Test_FileLog.cpp
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

    xTEST_CASE("write(...)")
    {
        log.critical(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        log.warning(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Warning), 12345);
        log.critical(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        log.error(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Error), 12345);
        log.warning(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Warning), 12345);
        log.trace(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Trace), 12345);
        log.info(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Info), 12345);
        log.debug(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Debug), 12345);
        log.trace(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Trace), 12345);
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
