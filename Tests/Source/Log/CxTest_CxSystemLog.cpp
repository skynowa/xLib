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
/*virtual*/
bool
CxTest_CxSystemLog::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    //--------------------------------------------------
    // CxSystemLog()
    xTEST_CASE(cullBlockLoops)
    {
        CxSystemLog slSytemLog;
    }

    //--------------------------------------------------
    // CxSystemLog(const std::tstring_t &csLogName)
    xTEST_CASE(cullBlockLoops)
    {
        std::tstring_t sLogName = xT("Simple_programm_name");

        CxSystemLog slSytemLog(sLogName);
    }

    //--------------------------------------------------
    // bSetEnabled
    xTEST_CASE(cullBlockLoops)
    {
        CxSystemLog slSytemLog;

        m_bRv = slSytemLog.bSetEnabled(true);
        xTEST_EQ(true, m_bRv);

        m_bRv = slSytemLog.bSetEnabled(false);
        xTEST_EQ(true, m_bRv);

        m_bRv = slSytemLog.bSetEnabled(true);
        xTEST_EQ(true, m_bRv);

        m_bRv = slSytemLog.bSetEnabled(false);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    // bWrite
    xTEST_CASE(cullBlockLoops)
    {
        CxSystemLog::ExLevel alvLogLevel[] = {
            CxSystemLog::lvEmerg, CxSystemLog::lvAlert, CxSystemLog::lvCritical,
            CxSystemLog::lvError, CxSystemLog::lvWarning, CxSystemLog::lvNotice,
            CxSystemLog::lvInfo, CxSystemLog::lvDebug
        };

        CxSystemLog slSytemLog;

        for (size_t i = 0; i < xARRAY_SIZE(alvLogLevel); ++ i) {
            m_bRv = slSytemLog.bWrite(alvLogLevel[i], xT("%s%")xPR_SIZET, xT("This is test system log message #"), i);
            xTEST_EQ(true, m_bRv);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
