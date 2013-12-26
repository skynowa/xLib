/**
 * \file   CxTest_CxSystemLog.cpp
 * \brief  test CxSystemLogs
 */


#include <Test/Log/CxTest_CxSystemLog.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSystemLog::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxSystemLog::CxSystemLog", a_caseLoops)
    {
        CxSystemLog log;
    }

    xTEST_CASE("CxSystemLog::CxSystemLog", a_caseLoops)
    {
        std::tstring_t logName = xT("Simple_programm_name");

        CxSystemLog log(logName);
    }

    xTEST_CASE("CxSystemLog::setEnabled", a_caseLoops)
    {
        CxSystemLog log;

        log.setEnabled(true);
        log.setEnabled(false);
        log.setEnabled(true);
        log.setEnabled(false);
    }

    xTEST_CASE("CxSystemLog::write", a_caseLoops)
    {
        IxLog::cExLevel logLevel[] = {
            IxLog::lvEmerg, IxLog::lvAlert,   IxLog::lvCritical,
            IxLog::lvError, IxLog::lvWarning, IxLog::lvNotice,
            IxLog::lvInfo,  IxLog::lvDebug
        };

        CxSystemLog log;

        for (size_t i = 0; i < xARRAY_SIZE(logLevel); ++ i) {
            log.write(logLevel[i], xT("%s%")xPR_SIZET, xT("This is test system log message #"), i);
        }
    }

    xTEST_CASE("CxSystemLog::write(cExLevel &level, ...)", a_caseLoops)
    {
        CxSystemLog().write(IxLog::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvUnknown),  12345);
        CxSystemLog().write(IxLog::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvEmerg),    12345);
        CxSystemLog().write(IxLog::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvAlert),    12345);
        CxSystemLog().write(IxLog::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvCritical), 12345);
        CxSystemLog().write(IxLog::lvError,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvError),    12345);
        CxSystemLog().write(IxLog::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvWarning),  12345);
        CxSystemLog().write(IxLog::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvNotice),   12345);
        CxSystemLog().write(IxLog::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvInfo),     12345);
        CxSystemLog().write(IxLog::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvDebug),    12345);
        CxSystemLog().write(IxLog::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvPlain),    12345);
    }
}
//-------------------------------------------------------------------------------------------------
