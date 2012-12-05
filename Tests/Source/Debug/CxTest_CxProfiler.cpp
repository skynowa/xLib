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

        CxFile::vClear(csFilePath);

        CxProfiler pfP;

        pfP.vSetLogPath(csFilePath);

        m_sRv = pfP.sLogPath();
        xTEST_EQ(csFilePath, m_sRv);

        pfP.vStart();

        for (size_t i = 0; i < 10; ++ i) {
            CxCurrentThread::vSleep(5UL);

            pfP.vPulse(xT("\tVar i: %") xPR_SIZET, i);
        }

        pfP.vStop(xT(""));
    }
}
//---------------------------------------------------------------------------
