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
        ILog::cLevel logLevel[] =
        {
            ILog::Level::lvEmerg, ILog::Level::lvAlert,   ILog::Level::lvCritical,
            ILog::Level::lvError, ILog::Level::lvWarning, ILog::Level::lvNotice,
            ILog::Level::lvInfo,  ILog::Level::lvDebug
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
        SystemLog().write(ILog::Level::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvUnknown),  12345);
        SystemLog().write(ILog::Level::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvEmerg),    12345);
        SystemLog().write(ILog::Level::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvAlert),    12345);
        SystemLog().write(ILog::Level::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvCritical), 12345);
        SystemLog().write(ILog::Level::lvError,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvError),    12345);
        SystemLog().write(ILog::Level::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvWarning),  12345);
        SystemLog().write(ILog::Level::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvNotice),   12345);
        SystemLog().write(ILog::Level::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvInfo),     12345);
        SystemLog().write(ILog::Level::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvDebug),    12345);
        SystemLog().write(ILog::Level::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvPlain),    12345);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
