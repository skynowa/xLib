/**
 * \file   CxTest_CxProfiler.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxProfiler.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Filesystem/CxFile.h>


//------------------------------------------------------------------------------
CxTest_CxProfiler::CxTest_CxProfiler() {

}
//------------------------------------------------------------------------------
CxTest_CxProfiler::~CxTest_CxProfiler() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxProfiler::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxProfiler::CxProfiler", a_cullCaseLoops)
    {
        std::ctstring_t csFilePath = tempDirPath() + CxConst::xSLASH + xT("CxProfilerLog.log");

        CxFile::clear(csFilePath);

        CxProfiler pfP;

        pfP.setLogPath(csFilePath);

        m_sRv = pfP.logPath();
        xTEST_EQ(csFilePath, m_sRv);

        pfP.start();

        for (size_t i = 0; i < 10; ++ i) {
            CxCurrentThread::sleep(5UL);

            pfP.pulse(xT("\tVar i: %") xPR_SIZET, i);
        }

        pfP.stop(xT(""));
    }
}
//------------------------------------------------------------------------------
