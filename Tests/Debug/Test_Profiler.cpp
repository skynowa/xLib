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
        	ThreadCurrent::currentSleep(5UL);
            m_stRv = profiler.restart();
        }

        m_stRv = profiler.stop();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
