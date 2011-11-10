/****************************************************************************
* Class name:  CxTest_CxProfiler
* Description: test CxProfiler
* File name:   CxTest_CxProfiler.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Debug/CxTest_CxProfiler.h>


//---------------------------------------------------------------------------
CxTest_CxProfiler::CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
CxTest_CxProfiler::~CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxProfiler::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const CxProfiler::EMode pmPerformMode[] = {
            CxProfiler::pmStdClock,
            CxProfiler::pmDateTime,
        #if defined(xOS_ENV_WIN)
            CxProfiler::pmTickCount,
            CxProfiler::pmPerformanceCount,
            CxProfiler::pmThreadTimes,
        #elif defined(xOS_ENV_UNIX)
            CxProfiler::pmGetTimeOfDay
        #endif
    };

    for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
        const std::string_t csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("___Log.log");

        CxProfiler pfP(pmPerformMode[i]);

        m_bRes = pfP.bSetLogPath(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_sRes = pfP.sGetLogPath();
        xTEST_EQ(csFilePath, m_sRes);

        m_bRes = pfP.bStart();
        xTEST_DIFF(FALSE, m_bRes);

        for (size_t y = 0; y < 10; ++ y) {
            for (size_t j = 0; j < 2; ++ j) {
                size_t x = 0;

                x++; --x; x = x / 3;
            }

            pfP.bPulse(xT("Variable i: %zu"), y);
            xTEST_DIFF(FALSE, m_bRes);
        }

        pfP.bStop(xT(""));
        xTEST_DIFF(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
