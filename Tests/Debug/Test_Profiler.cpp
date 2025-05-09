/**
 * \file   Test_Profiler.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Profiler)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Profiler::unit()
{
    xTEST_CASE("ctor")
    {
        Profiler profiler;
        profiler.start();

        for (size_t i = 0; i < 4; ++ i) {
            Thread::currentSleep(5UL);
            m_stRv = profiler.restart(xT("\tVar i: %") xPR_SIZET, i);
        }

        m_stRv = profiler.stop(xT(""));
    }

    xTEST_CASE("setLogPath")
    {
        std::ctstring_t filePath = option().tempDirPath + Const::slash() + xT("ProfilerLog.log");

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::Write);
			file.clear();
		}

        Profiler profiler;
        profiler.setLogPath(filePath);

        m_sRv = profiler.logPath();
        xTEST_EQ(m_sRv, filePath);

        profiler.start();

        for (size_t i = 0; i < 4; ++ i) {
            Thread::currentSleep(5UL);
            m_stRv = profiler.restart(xT("\tVar i: %") xPR_SIZET, i);
        }

        m_stRv = profiler.stop(xT(""));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
