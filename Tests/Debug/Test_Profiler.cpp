/**
 * \file   Test_Profiler.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Profiler)
xTEST_UNIT(Test_Profiler)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Profiler::unit()
{
    xTEST_CASE("setLogPath")
    {
        std::ctstring_t filePath = data.tempDirPath + Const::slash() + xT("ProfilerLog.log");

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

    xTEST_CASE("Profiler")
    {
        Profiler profiler;
        profiler.start();

        for (size_t i = 0; i < 10; ++ i) {
            Thread::currentSleep(5UL);
            m_stRv = profiler.restart(xT("\tVar i: %") xPR_SIZET, i);
        }

        m_stRv = profiler.stop(xT(""));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
