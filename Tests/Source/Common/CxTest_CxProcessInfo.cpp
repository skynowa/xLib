/**
 * \file   CxTest_CxProcessInfo.cpp
 * \brief  test CxProcessInfo
 */


#include <Test/Common/CxTest_CxProcessInfo.h>

#include <xLib/Sync/CxCurrentProcess.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>


//------------------------------------------------------------------------------
CxTest_CxProcessInfo::CxTest_CxProcessInfo() {

}
//------------------------------------------------------------------------------
CxTest_CxProcessInfo::~CxTest_CxProcessInfo() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxProcessInfo::unit(
    culonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxProcessInfo::currentIds", cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::currentIds(&vidIds);
        #if xTEST_IGNORE
            CxTracer() << vidIds;
        #endif
    }

    xTEST_CASE("CxProcessInfo::cpuUsage", cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_ulRv = CxProcessInfo::cpuUsage(*it);
            #if xTEST_IGNORE
                CxTracer() << xT("\tCxProcessInfo::cpuUsage(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE("CxProcessInfo::ramUsage", cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_ulRv = CxProcessInfo::ramUsage(*it);
            #if xTEST_IGNORE
                CxTracer() << xT("\tCxProcessInfo::ramUsage(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE("CxProcessInfo::ioBytes", cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_ulRv = CxProcessInfo::ioBytes(/* *it */ CxCurrentProcess::id());
            #if xTEST_IGNORE
                CxTracer() << xT("\tCxProcessInfo::ioBytes(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE("CxProcessInfo::exeName", cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_sRv = CxProcessInfo::exeName(/* *it */ CxCurrentProcess::id());
            xTEST_EQ(true,  CxFile::isExists(m_sRv));
            xTEST_EQ(m_sRv, CxPath::exe());
        }
    }

    xTEST_CASE("CxProcessInfo::parentId", cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            m_ulRv = CxProcessInfo::parentId(/* *it */ CxCurrentProcess::id());
            // xTEST_DIFF(0UL, m_ulRv);
        }
    }

    xTEST_CASE("CxProcessInfo::commandLine", cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcessInfo::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
        #if   xOS_ENV_WIN
            xCHECK_DO(0 == *it, continue);
            xCHECK_DO(344 == *it, continue);
        #elif xOS_ENV_UNIX

        #endif

            m_sRv = CxProcessInfo::commandLine(/* *it */ CxCurrentProcess::id());
            #if xTEST_IGNORE
                CxTracer() << m_sRv;
            #endif
        }
    }
}
//------------------------------------------------------------------------------
