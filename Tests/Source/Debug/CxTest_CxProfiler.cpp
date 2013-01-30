/**
 * \file   CxTest_CxProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxProfiler.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Filesystem/CxFile.h>


//---------------------------------------------------------------------------
CxTest_CxProfiler::CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
CxTest_CxProfiler::~CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxProfiler::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxProfiler::CxProfiler", cullCaseLoops)
    {
        const std::tstring_t csFilePath = sTempDirPath() + CxConst::xSLASH + xT("CxProfilerLog.log");

        CxFile::clear(csFilePath);

        CxProfiler pfP;

        pfP.setLogPath(csFilePath);

        m_sRv = pfP.logPath();
        xTEST_EQ(csFilePath, m_sRv);

        pfP.start();

        for (size_t i = 0; i < 10; ++ i) {
            CxCurrentThread::vSleep(5UL);

            pfP.pulse(xT("\tVar i: %") xPR_SIZET, i);
        }

        pfP.stop(xT(""));
    }
}
//---------------------------------------------------------------------------
