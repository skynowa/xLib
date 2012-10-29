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
    const CxProfiler::ExMode pmPerformMode[] = {
            CxProfiler::pmStdClock,
            CxProfiler::pmDateTime,
            CxProfiler::pmGetTimeOfDay,
            CxProfiler::pmSystemTicks

        #if   xOS_ENV_WIN
            ,
            CxProfiler::pmPerformanceCount,
            CxProfiler::pmThreadTimes
        #elif xOS_ENV_UNIX
            xNA;
        #endif
    };

    xTEST_CASE(CxAutoProfiler::CxAutoProfiler, cullCaseLoops)
    {
        for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
            CxAutoProfiler _apfAP(sTempDirPath() + CxConst::xSLASH + xT("__FuncLog.log"), pmPerformMode[i], xT("%i"), 777);

            CxCurrentThread::vSleep(5UL);
        }
    }
}
//---------------------------------------------------------------------------
