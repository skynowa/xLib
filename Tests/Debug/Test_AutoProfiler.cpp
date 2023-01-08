/**
 * \file   Test_AutoProfiler.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_AutoProfiler)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_AutoProfiler::unit()
{
    xTEST_CASE("AutoProfiler")
    {
        std::ctstring_t filePath = data().tempDirPath + Const::slash() + xT("AutoProfilerLog.log");

		{
			FileIO file(filePath);
			file.open(FileIO::OpenMode::Write);
			file.clear();
		}

        for (size_t y = 0; y < 10; ++ y) {
            AutoProfiler apfP(filePath, xT("\tVar y: %") xPR_SIZET, y);

            Thread::currentSleep(5UL);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
