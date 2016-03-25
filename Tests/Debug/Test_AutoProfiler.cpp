/**
 * \file   Test_AutoProfiler.cpp
 * \brief
 */


#include "Test_AutoProfiler.h"

#include <xLib/Core/Const.h>
#include <xLib/Sync/Thread.h>
#include <xLib/IO/File.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_AutoProfiler)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_AutoProfiler::unit()
{
    xTEST_CASE("AutoProfiler")
    {
        std::ctstring_t csFilePath = tempDirPath() + Const::slash() + xT("AutoProfilerLog.log");

        File::clear(csFilePath);

        for (size_t y = 0; y < 10; ++ y) {
            AutoProfiler apfP(csFilePath, xT("\tVar y: %") xPR_SIZET, y);

            Thread::currentSleep(5UL);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
