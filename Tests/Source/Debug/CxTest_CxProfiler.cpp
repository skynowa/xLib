/**
 * \file   CxTest_CxProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxProfiler.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Sync/CxCurrentThread.h>


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
    const CxProfiler::ExMode pmMode[] = {
            CxProfiler::pmStdClock,
            CxProfiler::pmDateTime,
            CxProfiler::pmGetTimeOfDay,
            CxProfiler::pmSystemTicks

        #if   xOS_ENV_WIN
            ,
            CxProfiler::pmPerformanceCount,
            CxProfiler::pmThreadTimes
        #elif xOS_ENV_UNIX

        #endif
    };

    for (size_t i = 0; i < xARRAY_SIZE(pmMode); ++ i) {
        const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("CxProfilerLog.log");

        CxProfiler pfP(pmMode[i]);

        pfP.vSetLogPath(csFilePath);

        m_sRv = pfP.sLogPath();
        xTEST_EQ(csFilePath, m_sRv);

        pfP.vStart();

        for (size_t y = 0; y < 10; ++ y) {
            CxCurrentThread::vSleep(2000UL);

            pfP.vPulse(xT("Variable y: %") xPR_SIZET, y);
        }

        pfP.vStop(xT(""));
    }
}
//---------------------------------------------------------------------------
