/**
 * \file  Test_SystemLog.cpp
 * \brief test SystemLogs
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_SystemLog)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SystemLog::unit()
{
    xTEST_CASE("ctor")
    {
        SystemLog log;
    }

    xTEST_CASE("ctor")
    {
        std::tstring_t logName = xT("Simple_programm_name");

        SystemLog log(logName);
    }

    xTEST_CASE("setEnabled")
    {
        SystemLog log;
        log.setEnabled(true);
        log.setEnabled(false);
        log.setEnabled(true);
        log.setEnabled(false);
    }

    xTEST_CASE("write(...)")
    {
    #if xTEST_IGNORE
        SystemLog log;
        log.critical(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        log.warning(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Warning), 12345);
        log.critical(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        log.error(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Error), 12345);
        log.warning(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Warning), 12345);
        log.trace(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Trace), 12345);
        log.info(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Info), 12345);
        log.debug(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Debug), 12345);
        log.trace(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Trace), 12345);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
