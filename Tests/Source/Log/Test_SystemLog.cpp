/**
 * \file   Test_SystemLog.cpp
 * \brief  test SystemLogs
 */


#include <Test/Log/Test_SystemLog.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_SystemLog::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("SystemLog::SystemLog", a_caseLoops)
    {
        SystemLog log;
    }

    xTEST_CASE("SystemLog::SystemLog", a_caseLoops)
    {
        std::tstring_t logName = xT("Simple_programm_name");

        SystemLog log(logName);
    }

    xTEST_CASE("SystemLog::setEnabled", a_caseLoops)
    {
        SystemLog log;

        log.setEnabled(true);
        log.setEnabled(false);
        log.setEnabled(true);
        log.setEnabled(false);
    }

    xTEST_CASE("SystemLog::write", a_caseLoops)
    {
        IxLog::cExLevel logLevel[] = {
            IxLog::lvEmerg, IxLog::lvAlert,   IxLog::lvCritical,
            IxLog::lvError, IxLog::lvWarning, IxLog::lvNotice,
            IxLog::lvInfo,  IxLog::lvDebug
        };

        SystemLog log;

        for (size_t i = 0; i < xARRAY_SIZE(logLevel); ++ i) {
            log.write(logLevel[i], xT("%s%")xPR_SIZET, xT("This is test system log message #"), i);
        }
    }

    xTEST_CASE("SystemLog::write(cExLevel &level, ...)", a_caseLoops)
    {
        SystemLog().write(IxLog::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvUnknown),  12345);
        SystemLog().write(IxLog::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvEmerg),    12345);
        SystemLog().write(IxLog::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvAlert),    12345);
        SystemLog().write(IxLog::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvCritical), 12345);
        SystemLog().write(IxLog::lvError,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvError),    12345);
        SystemLog().write(IxLog::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvWarning),  12345);
        SystemLog().write(IxLog::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvNotice),   12345);
        SystemLog().write(IxLog::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvInfo),     12345);
        SystemLog().write(IxLog::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvDebug),    12345);
        SystemLog().write(IxLog::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvPlain),    12345);
    }
}
//-------------------------------------------------------------------------------------------------
