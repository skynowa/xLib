/**
 * \file   Test_SystemLog.cpp
 * \brief  test SystemLogs
 */


#include "Test_SystemLog.h"

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
        ILog::cExLevel logLevel[] = {
            ILog::lvEmerg, ILog::lvAlert,   ILog::lvCritical,
            ILog::lvError, ILog::lvWarning, ILog::lvNotice,
            ILog::lvInfo,  ILog::lvDebug
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
        SystemLog().write(ILog::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(ILog::lvUnknown),  12345);
        SystemLog().write(ILog::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvEmerg),    12345);
        SystemLog().write(ILog::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvAlert),    12345);
        SystemLog().write(ILog::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(ILog::lvCritical), 12345);
        SystemLog().write(ILog::lvError,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvError),    12345);
        SystemLog().write(ILog::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::lvWarning),  12345);
        SystemLog().write(ILog::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(ILog::lvNotice),   12345);
        SystemLog().write(ILog::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(ILog::lvInfo),     12345);
        SystemLog().write(ILog::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvDebug),    12345);
        SystemLog().write(ILog::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvPlain),    12345);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
