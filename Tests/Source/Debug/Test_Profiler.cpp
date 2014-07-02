/**
 * \file   Test_Profiler.cpp
 * \brief
 */


#include <Test/Debug/Test_Profiler.h>

#include <xLib/Core/Const.h>
#include <xLib/Sync/Thread.h>
#include <xLib/IO/File.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Profiler::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Profiler::setLogPath", a_caseLoops)
    {
        std::ctstring_t filePath = tempDirPath() + Const::slash() + xT("ProfilerLog.log");

        File::clear(filePath);

        Profiler profiler;
        profiler.setLogPath(filePath);

        m_sRv = profiler.logPath();
        xTEST_EQ(filePath, m_sRv);

        profiler.start();

        for (size_t i = 0; i < 10; ++ i) {
            Thread::currentSleep(5UL);
            m_stRv = profiler.restart(xT("\tVar i: %") xPR_SIZET, i);
        }

        m_stRv = profiler.stop(xT(""));
    }

    xTEST_CASE("Profiler::Profiler", a_caseLoops)
    {
        Profiler profiler;
        profiler.start();

        for (size_t i = 0; i < 10; ++ i) {
            Thread::currentSleep(5UL);
            m_stRv = profiler.restart(xT("\tVar i: %") xPR_SIZET, i);
        }

        m_stRv = profiler.stop(xT(""));
    }
}
//-------------------------------------------------------------------------------------------------
