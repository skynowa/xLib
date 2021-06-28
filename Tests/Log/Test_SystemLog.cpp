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
            ILog::Level::Emerg, ILog::Level::Alert,   ILog::Level::Critical,
            ILog::Level::Error, ILog::Level::Warning, ILog::Level::Notice,
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
        SystemLog().write(ILog::Level::Unknown,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Unknown),  12345);
        SystemLog().write(ILog::Level::Emerg,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Emerg),    12345);
        SystemLog().write(ILog::Level::Alert,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Alert),    12345);
        SystemLog().write(ILog::Level::Critical, xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        SystemLog().write(ILog::Level::Error,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Error),    12345);
        SystemLog().write(ILog::Level::Warning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Warning),  12345);
        SystemLog().write(ILog::Level::Notice,   xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Notice),   12345);
        SystemLog().write(ILog::Level::Info,     xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Info),     12345);
        SystemLog().write(ILog::Level::Debug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Debug),    12345);
        SystemLog().write(ILog::Level::Plain,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Plain),    12345);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
