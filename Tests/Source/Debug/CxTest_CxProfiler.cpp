/**
 * \file   CxTest_CxProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxProfiler.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Filesystem/CxFile.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxProfiler::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxProfiler::CxProfiler", a_caseLoops)
    {
        std::ctstring_t filePath = tempDirPath() + CxConst::slash() + xT("CxProfilerLog.log");

        CxFile::clear(filePath);

        CxProfiler profiler;
        profiler.setLogPath(filePath);

        m_sRv = profiler.logPath();
        xTEST_EQ(filePath, m_sRv);

        profiler.start();

        for (size_t i = 0; i < 10; ++ i) {
            CxThread::currentSleep(5UL);
            m_stRv = profiler.restart(xT("\tVar i: %") xPR_SIZET, i);
        }

        m_stRv = profiler.stop(xT(""));
    }

    xTEST_CASE("CxProfiler::CxProfiler", a_caseLoops)
    {
        CxProfiler profiler;
        profiler.start();

        for (size_t i = 0; i < 10; ++ i) {
            CxThread::currentSleep(5UL);
            m_stRv = profiler.restart(xT("\tVar i: %") xPR_SIZET, i);
        }

        m_stRv = profiler.stop(xT(""));
    }
}
//-------------------------------------------------------------------------------------------------
