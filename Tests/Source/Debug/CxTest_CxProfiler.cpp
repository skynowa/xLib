/**
 * \file   CxTest_CxProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxProfiler.h>


//---------------------------------------------------------------------------
CxTest_CxProfiler::CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
CxTest_CxProfiler::~CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
/* virtual */
bool
CxTest_CxProfiler::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const CxProfiler::ExMode pmPerformMode[] = {
            CxProfiler::pmStdClock,
            CxProfiler::pmDateTime,
        #if xOS_ENV_WIN
            CxProfiler::pmTickCount,
            CxProfiler::pmPerformanceCount,
            CxProfiler::pmThreadTimes,
        #elif xOS_ENV_UNIX
            CxProfiler::pmGetTimeOfDay
        #endif
    };

    for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
        const std::tstring_t csFilePath = sGetTempDirPath() + CxConst::xSLASH + xT("___Log.log");

        CxProfiler pfP(pmPerformMode[i]);

        m_bRv = pfP.bSetLogPath(csFilePath);
        xTEST_EQ(true, m_bRv);

        m_sRv = pfP.sGetLogPath();
        xTEST_EQ(csFilePath, m_sRv);

        m_bRv = pfP.bStart();
        xTEST_EQ(true, m_bRv);

        for (size_t y = 0; y < 10; ++ y) {
            for (size_t j = 0; j < 2; ++ j) {
                size_t x = 0;

                x++; --x; x = x / 3;
            }

            pfP.bPulse(xT("Variable i: %zu"), y);
            xTEST_EQ(true, m_bRv);
        }

        pfP.bStop(xT(""));
        xTEST_EQ(true, m_bRv);
    }

    return true;
}
//---------------------------------------------------------------------------
