/**
 * \file   CxTest_CxProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxProfiler.h>

#include <xLib/Common/CxConst.h>

//---------------------------------------------------------------------------
CxTest_CxProfiler::CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
CxTest_CxProfiler::~CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxProfiler::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const CxProfiler::ExMode pmPerformMode[] = {
            CxProfiler::pmStdClock,
            CxProfiler::pmDateTime,
        #if   xOS_ENV_WIN
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

        pfP.vSetLogPath(csFilePath);

        m_sRv = pfP.sGetLogPath();
        xTEST_EQ(csFilePath, m_sRv);

        pfP.vStart();

        for (size_t y = 0; y < 10; ++ y) {
            for (size_t j = 0; j < 2; ++ j) {
                size_t x = 0;

                x++; --x; x = x / 3;
            }

            pfP.vPulse(xT("Variable i: %zu"), y);
        }

        pfP.vStop(xT(""));
    }
}
//---------------------------------------------------------------------------
