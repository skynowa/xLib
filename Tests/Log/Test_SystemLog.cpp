/**
 * \file   Test_SystemLog.cpp
 * \brief  test SystemLogs
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_SystemLog)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SystemLog::unit()
{
    xTEST_CASE("SystemLog")
    {
        SystemLog log;
    }

    xTEST_CASE("SystemLog")
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

    xTEST_CASE("write")
    {
        ILog::cLevel logLevel[]
        {
            ILog::Level::Fatal, ILog::Level::Warning,   ILog::Level::Fatal,
            ILog::Level::Error, ILog::Level::Warning, ILog::Level::Trace,
            ILog::Level::Info,  ILog::Level::Debug
        };

        SystemLog log;

        for (size_t i = 0; i < xARRAY_SIZE(logLevel); ++ i) {
        #if xTEST_IGNORE
            log.write(logLevel[i], xT("%s%")xPR_SIZET, xT("This is test system log message #"), i);
        #endif
        }
    }

    xTEST_CASE("write(...)")
    {
    #if xTEST_IGNORE
        SystemLog().write(ILog::Level::Off,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Off),  12345);
        SystemLog().write(ILog::Level::Fatal,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Fatal),    12345);
        SystemLog().write(ILog::Level::Warning,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Warning),    12345);
        SystemLog().write(ILog::Level::Fatal, xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Fatal), 12345);
        SystemLog().write(ILog::Level::Error,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Error),    12345);
        SystemLog().write(ILog::Level::Warning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Warning),  12345);
        SystemLog().write(ILog::Level::Trace,   xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Trace),   12345);
        SystemLog().write(ILog::Level::Info,     xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Info),     12345);
        SystemLog().write(ILog::Level::Debug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Debug),    12345);
        SystemLog().write(ILog::Level::Trace,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Trace),    12345);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
