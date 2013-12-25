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
}
//-------------------------------------------------------------------------------------------------
