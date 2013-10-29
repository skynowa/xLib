/**
 * \file   CxTest_CxAutoProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxAutoProfiler.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Filesystem/CxFile.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxAutoProfiler::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxAutoProfiler::CxAutoProfiler", a_cullCaseLoops)
    {
        std::ctstring_t csFilePath = tempDirPath() + CxConst::xSLASH() + xT("CxAutoProfilerLog.log");

        CxFile::clear(csFilePath);

        for (size_t y = 0; y < 10; ++ y) {
            CxAutoProfiler apfP(csFilePath, xT("\tVar y: %") xPR_SIZET, y);

            CxThread::currentSleep(5UL);
        }
    }
}
//------------------------------------------------------------------------------
