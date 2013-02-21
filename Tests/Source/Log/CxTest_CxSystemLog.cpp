/**
 * \file   CxTest_CxSystemLog.cpp
 * \brief  test CxSystemLogs
 */


#include <Test/Log/CxTest_CxSystemLog.h>


//------------------------------------------------------------------------------
CxTest_CxSystemLog::CxTest_CxSystemLog() {

}
//------------------------------------------------------------------------------
CxTest_CxSystemLog::~CxTest_CxSystemLog() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxSystemLog::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxSystemLog::CxSystemLog", cullCaseLoops)
    {
        CxSystemLog slSytemLog;
    }

    xTEST_CASE("CxSystemLog::CxSystemLog", cullCaseLoops)
    {
        std::tstring_t sLogName = xT("Simple_programm_name");

        CxSystemLog slSytemLog(sLogName);
    }

    xTEST_CASE("CxSystemLog::setEnabled", cullCaseLoops)
    {
        CxSystemLog slSytemLog;

        slSytemLog.setEnabled(true);
        slSytemLog.setEnabled(false);
        slSytemLog.setEnabled(true);
        slSytemLog.setEnabled(false);
    }

    xTEST_CASE("CxSystemLog::write", cullCaseLoops)
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
