/**
 * \file   CxTest_CxProcessInfo.cpp
 * \brief  test CxProcessInfo
 */


#include <Test/Common/CxTest_CxProcessInfo.h>

#include <xLib/Sync/CxCurrentProcess.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>


//---------------------------------------------------------------------------
CxTest_CxProcessInfo::CxTest_CxProcessInfo() {

}
//---------------------------------------------------------------------------
CxTest_CxProcessInfo::~CxTest_CxProcessInfo() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxProcessInfo::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxProcessInfo::vCurrentIds, cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::vCurrentIds(&vidIds);
        #if xTEST_IGNORE
            CxTracer() << vidIds;
        #endif
    }

    xTEST_CASE(CxProcessInfo::ulCpuUsage, cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::vCurrentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_ulRv = CxProcessInfo::ulCpuUsage(*it);
            #if xTEST_IGNORE
                CxTracer() << xT("\tCxProcessInfo::ulCpuUsage(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE(CxProcessInfo::ulRamUsage, cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::vCurrentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_ulRv = CxProcessInfo::ulRamUsage(*it);
            #if xTEST_IGNORE
                CxTracer() << xT("\tCxProcessInfo::ulRamUsage(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE(CxProcessInfo::ulIOBytes, cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::vCurrentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_ulRv = CxProcessInfo::ulIOBytes(*it);
            #if xTEST_IGNORE
                CxTracer() << xT("\tCxProcessInfo::ulIOBytes(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE(CxProcessInfo::sExeName, cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::vCurrentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_sRv = CxProcessInfo::sExeName(/* *it */ CxCurrentProcess::ulId());
            xTEST_EQ(true,  CxFile::bIsExists(m_sRv));
            xTEST_EQ(m_sRv, CxPath::sExe());
        }
    }

    xTEST_CASE(CxProcessInfo::ulParentId, cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::vCurrentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_ulRv = CxProcessInfo::ulParentId(/* *it */ CxCurrentProcess::ulId());
            // xTEST_DIFF(0UL, m_ulRv);
        }
    }

    xTEST_CASE(CxProcessInfo::sCommandLine, cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::vCurrentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
        #if   xOS_ENV_WIN
            xCHECK_DO(0 == *it, continue);
            xCHECK_DO(4 == *it, continue);
            xCHECK_DO(344 == *it, continue);
        #elif xOS_ENV_UNIX

        #endif

            m_sRv = CxProcessInfo::sCommandLine(/* *it */ CxCurrentProcess::ulId());
            #if xTEST_IGNORE
                CxTracer() << m_sRv;
            #endif
        }
    }
}
//---------------------------------------------------------------------------
