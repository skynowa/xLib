/**
 * \file   CxTest_CxSystemLog.cpp
 * \brief  test CxSystemLogs
 */


#include <Test/Log/CxTest_CxSystemLog.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSystemLog::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxSystemLog::CxSystemLog", a_caseLoops)
    {
        CxSystemLog slSytemLog;
    }

    xTEST_CASE("CxSystemLog::CxSystemLog", a_caseLoops)
    {
        std::tstring_t sLogName = xT("Simple_programm_name");

        CxSystemLog slSytemLog(sLogName);
    }

    xTEST_CASE("CxSystemLog::setEnabled", a_caseLoops)
    {
        CxSystemLog slSytemLog;

        slSytemLog.setEnabled(true);
        slSytemLog.setEnabled(false);
        slSytemLog.setEnabled(true);
        slSytemLog.setEnabled(false);
    }

    xTEST_CASE("CxSystemLog::write", a_caseLoops)
    {
        CxSystemLog::ExLevel alvLogLevel[] = {
            CxSystemLog::lvEmerg, CxSystemLog::lvAlert,   CxSystemLog::lvCritical,
            CxSystemLog::lvError, CxSystemLog::lvWarning, CxSystemLog::lvNotice,
            CxSystemLog::lvInfo,  CxSystemLog::lvDebug
        };

        CxSystemLog slSytemLog;

        for (size_t i = 0; i < xARRAY_SIZE(alvLogLevel); ++ i) {
            slSytemLog.write(alvLogLevel[i], xT("%s%")xPR_SIZET, xT("This is test system log message #"), i);
        }
    }
}
//------------------------------------------------------------------------------
