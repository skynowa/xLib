/**
 * \file   CxTest_CxAutoProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxAutoProfiler.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Filesystem/CxFile.h>


//---------------------------------------------------------------------------
CxTest_CxAutoProfiler::CxTest_CxAutoProfiler() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoProfiler::~CxTest_CxAutoProfiler() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxAutoProfiler::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxAutoProfiler::CxAutoProfiler", cullCaseLoops)
    {
        const std::tstring_t csFilePath = tempDirPath() + CxConst::xSLASH + xT("CxAutoProfilerLog.log");

        CxFile::clear(csFilePath);

        for (size_t y = 0; y < 10; ++ y) {
            CxAutoProfiler apfP(csFilePath, xT("\tVar y: %") xPR_SIZET, y);

            CxCurrentThread::sleep(5UL);
        }
    }
}
//---------------------------------------------------------------------------
