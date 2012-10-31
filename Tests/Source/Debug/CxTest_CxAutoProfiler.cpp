/**
 * \file   CxTest_CxAutoProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxAutoProfiler.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Sync/CxCurrentThread.h>


//---------------------------------------------------------------------------
CxTest_CxAutoProfiler::CxTest_CxAutoProfiler() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoProfiler::~CxTest_CxAutoProfiler() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxAutoProfiler::vUnit(
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
        const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("CxAutoProfilerLog.log");

        for (size_t y = 0; y < 10; ++ y) {
            CxAutoProfiler apfP(csFilePath, pmMode[i], xT("Variable i: %") xPR_SIZET, y);

            CxCurrentThread::vSleep(5UL);
        }
    }
}
//---------------------------------------------------------------------------
