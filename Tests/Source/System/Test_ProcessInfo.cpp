/**
 * \file   Test_ProcessInfo.cpp
 * \brief  test ProcessInfo
 */


#include <Test/System/Test_ProcessInfo.h>

#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/Sync/Process.h>

//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_ProcessInfo::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("cpuUsage", a_caseLoops)
    {
        std::vector<Process::id_t> vidIds;

        Process::ids(&vidIds);

        xFOREACH_CONST(std::vector<Process::id_t>, it, vidIds) {
            ProcessInfo info;
            info.setProcessId(/* *it */ Process::currentId());

            m_ulRv = info.cpuUsage();
            #if xTEST_IGNORE
                Tracer() << xT("\tProcessInfo::cpuUsage(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE("ramUsage", a_caseLoops)
    {
        std::vector<Process::id_t> vidIds;

        Process::ids(&vidIds);

        xFOREACH_CONST(std::vector<Process::id_t>, it, vidIds) {
            ProcessInfo info;
            info.setProcessId(/* *it */ Process::currentId());

            m_ulRv = info.ramUsage();
            #if xTEST_IGNORE
                Tracer() << xT("\tProcessInfo::ramUsage(): ") << m_ulRv;
            #endif
        }
    }

    xTEST_CASE("ioBytes", a_caseLoops)
    {
    #if 0
        std::vector<Process::id_t> vidIds;

        Process::ids(&vidIds);

        xFOREACH_CONST(std::vector<Process::id_t>, it, vidIds) {
            ProcessInfo info;
            info.setProcessId(/* *it */ Process::currentId());

            m_ulRv = info.ioBytes();
            #if xTEST_IGNORE
                Tracer() << xT("\tProcessInfo::ioBytes(): ") << m_ulRv;
            #endif
        }
    #endif
    }

    xTEST_CASE("exeName", a_caseLoops)
    {
        std::vector<Process::id_t> vidIds;

        Process::ids(&vidIds);

        xFOREACH_CONST(std::vector<Process::id_t>, it, vidIds) {
            ProcessInfo info;
            info.setProcessId(/* *it */ Process::currentId());

            m_sRv = info.exeName();
            xTEST_EQ(true,  File::isExists(m_sRv));
            xTEST_EQ(m_sRv, Path::exe());
        }
    }

    xTEST_CASE("parentId", a_caseLoops)
    {
        std::vector<Process::id_t> vidIds;

        Process::ids(&vidIds);

        xFOREACH_CONST(std::vector<Process::id_t>, it, vidIds) {
            ProcessInfo info;
            info.setProcessId(/* *it */ Process::currentId());

            m_ulRv = info.parentId();
            // xTEST_DIFF(0UL, m_ulRv);
        }
    }

    xTEST_CASE("commandLine", a_caseLoops)
    {
        std::vector<Process::id_t> vidIds;

        Process::ids(&vidIds);

        xFOREACH_CONST(std::vector<Process::id_t>, it, vidIds) {
        #if   xENV_WIN
            xCHECK_DO(0 == *it, continue);
            xCHECK_DO(344 == *it, continue);
        #elif xENV_UNIX

        #endif
            ProcessInfo info;
            info.setProcessId(/* *it */ Process::currentId());

            info.commandLine(&m_vsRv);
            xTEST_EQ(false, m_vsRv.empty());

            #if xTEST_IGNORE
                Tracer() << m_sRv;
            #endif
        }
    }

    xTEST_CASE("commandLineArgsMax", a_caseLoops)
    {
        m_liRv = ProcessInfo::commandLineArgsMax();
        xTEST_LESS(0L, m_liRv);
        //xTRACEV(xT("\ProcessInfo::commandLineArgsMax() = %li"), m_liRv);
    }
}
//-------------------------------------------------------------------------------------------------
