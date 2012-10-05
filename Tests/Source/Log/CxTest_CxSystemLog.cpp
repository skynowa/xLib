/**
 * \file   CxTest_CxSystemLog.cpp
 * \brief  test CxSystemLogs
 */


#include <Test/Log/CxTest_CxSystemLog.h>


//---------------------------------------------------------------------------
CxTest_CxSystemLog::CxTest_CxSystemLog() {

}
//---------------------------------------------------------------------------
CxTest_CxSystemLog::~CxTest_CxSystemLog() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxSystemLog::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    //--------------------------------------------------
    // CxSystemLog()
    xTEST_CASE(cullCaseLoops)
    {
        CxSystemLog slSytemLog;
    }

    //--------------------------------------------------
    // CxSystemLog(const std::tstring_t &csLogName)
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sLogName = xT("Simple_programm_name");

        CxSystemLog slSytemLog(sLogName);
    }

    //--------------------------------------------------
    // bSetEnabled
    xTEST_CASE(cullCaseLoops)
    {
        CxSystemLog slSytemLog;

        slSytemLog.vSetEnabled(true);
        slSytemLog.vSetEnabled(false);
        slSytemLog.vSetEnabled(true);
        slSytemLog.vSetEnabled(false);
    }

    //--------------------------------------------------
    // bWrite
    xTEST_CASE(cullCaseLoops)
    {
        CxSystemLog::ExLevel alvLogLevel[] = {
            CxSystemLog::lvEmerg, CxSystemLog::lvAlert, CxSystemLog::lvCritical,
            CxSystemLog::lvError, CxSystemLog::lvWarning, CxSystemLog::lvNotice,
            CxSystemLog::lvInfo, CxSystemLog::lvDebug
        };

        CxSystemLog slSytemLog;

        for (size_t i = 0; i < xARRAY_SIZE(alvLogLevel); ++ i) {
            slSytemLog.vWrite(alvLogLevel[i], xT("%s%")xPR_SIZET, xT("This is test system log message #"), i);
        }
    }
}
//---------------------------------------------------------------------------
