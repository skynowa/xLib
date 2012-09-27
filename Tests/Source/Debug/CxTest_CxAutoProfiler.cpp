/**
 * \file   CxTest_CxAutoProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxAutoProfiler.h>

#include <xLib/Common/CxConst.h>


//---------------------------------------------------------------------------
CxTest_CxAutoProfiler::CxTest_CxAutoProfiler() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoProfiler::~CxTest_CxAutoProfiler() {

}
//---------------------------------------------------------------------------
/* virtual */
bool
CxTest_CxAutoProfiler::bUnit(
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

    //-------------------------------------
    //CxAutoProfiler
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
            CxAutoProfiler _apfAP(sGetTempDirPath() + CxConst::xSLASH + xT("__FuncLog.log"), pmPerformMode[i], xT("%i"), 777);

            for (size_t x = 0; x < 2; ++ x) {
                for (size_t y = 0; y < 2; ++ y) {
                    size_t z = 0;

                    z++; --z; z = z / 7;
                }
            }
        }
    }

    //-------------------------------------
    //xAUTO_PERFORM_FUNC
    xTEST_CASE(cullCaseLoops) {
        for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
            xAUTO_PROFILER_FUNC(sGetTempDirPath() + CxConst::xSLASH + xT("__FuncLog.log"), pmPerformMode[i]);

            for (size_t x = 0; x < 2; ++ x) {
                for (size_t y = 0; y < 2; ++ y) {
                    size_t z = 0;

                    z++; --z; z = z / 13;
                }
            }
        }
    }

    return true;
}
//---------------------------------------------------------------------------
