/**
 * \file   CxTest_CxProcessInfo.cpp
 * \brief  test CxProcessInfo
 */


#include <Test/System/CxTest_CxProcessInfo.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxProcess.h>

//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxProcessInfo::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxProcessInfo::cpuUsage", a_cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcess::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            CxProcessInfo info;
            info.setProcessId(/* *it */ CxProcess::currentId());

            m_ulRv = info.cpuUsage();
            #if xTEST_IGNORE
                CxTracer() << xT("\tCxProcessInfo::cpuUsage(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE("CxProcessInfo::ramUsage", a_cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcess::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            CxProcessInfo info;
            info.setProcessId(/* *it */ CxProcess::currentId());

            m_ulRv = info.ramUsage();
            #if xTEST_IGNORE
                CxTracer() << xT("\tCxProcessInfo::ramUsage(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE("CxProcessInfo::ioBytes", a_cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcess::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            CxProcessInfo info;
            info.setProcessId(/* *it */ CxProcess::currentId());

            m_ulRv = info.ioBytes();
            #if xTEST_IGNORE
                CxTracer() << xT("\tCxProcessInfo::ioBytes(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE("CxProcessInfo::exeName", a_cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcess::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            CxProcessInfo info;
            info.setProcessId(/* *it */ CxProcess::currentId());

            m_sRv = info.exeName();
            xTEST_EQ(true,  CxFile::isExists(m_sRv));
            xTEST_EQ(m_sRv, CxPath::exe());
        }
    }

    xTEST_CASE("CxProcessInfo::parentId", a_cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcess::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
            CxProcessInfo info;
            info.setProcessId(/* *it */ CxProcess::currentId());

            m_ulRv = info.parentId();
            // xTEST_DIFF(0UL, m_ulRv);
        }
    }

    xTEST_CASE("CxProcessInfo::commandLine", a_cullCaseLoops)
    {
        std::vector<CxProcess::id_t> vidIds;

        CxProcess::currentIds(&vidIds);

        xFOREACH_CONST(std::vector<CxProcess::id_t>, it, vidIds) {
        #if   xOS_ENV_WIN
            xCHECK_DO(0 == *it, continue);
            xCHECK_DO(344 == *it, continue);
        #elif xOS_ENV_UNIX

        #endif
            CxProcessInfo info;
            info.setProcessId(/* *it */ CxProcess::currentId());

            m_sRv = info.commandLine(&m_vsRv);
            xTEST_EQ(false, m_vsRv.empty());

            #if xTEST_IGNORE
                CxTracer() << m_sRv;
            #endif
        }
    }

    xTEST_CASE("CxProcessInfo::commandLineArgsMax", a_cullCaseLoops)
    {
        m_liRv = CxProcessInfo::commandLineArgsMax();
        xTEST_LESS(0L, m_liRv);
        //xTRACEV(xT("\CxProcessInfo::commandLineArgsMax() = %li"), m_liRv);
    }
}
//------------------------------------------------------------------------------
