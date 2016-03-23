/**
 * \file   Test_ProcessInfo.cpp
 * \brief  test ProcessInfo
 */


#include <Test/System/Test_ProcessInfo.h>

#include <xLib/IO/Path.h>
#include <xLib/IO/File.h>
#include <xLib/Sync/Process.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_ProcessInfo)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_ProcessInfo::unit()
{
    xTEST_CASE("cpuUsage")
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

    xTEST_CASE("ramUsage")
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

    xTEST_CASE("ioBytes")
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

    xTEST_CASE("exeName")
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

    xTEST_CASE("parentId")
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

    xTEST_CASE("commandLine")
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

    xTEST_CASE("commandLineArgsMax")
    {
        m_liRv = ProcessInfo::commandLineArgsMax();
        xTEST_LESS(0L, m_liRv);
        //xTRACEV(xT("\ProcessInfo::commandLineArgsMax() = %li"), m_liRv);
    }

    xTEST_CASE("commandLine")
    {
        cint_t    argsNum       = 5;
        ctchar_t *args[argsNum] = {xT("./xLib_test"), xT("1"), xT("2"), xT("3"), xT("4")};

        ProcessInfo::commandLine(argsNum, args, &m_vsRv);
        xTEST_EQ(m_vsRv.size(), (std::size_t)argsNum);
        xTEST_EQ(m_vsRv.at(0), std::tstring_t(xT("./xLib_test")));
        xTEST_EQ(m_vsRv.at(1), std::tstring_t(xT("1")));
        xTEST_EQ(m_vsRv.at(2), std::tstring_t(xT("2")));
        xTEST_EQ(m_vsRv.at(3), std::tstring_t(xT("3")));
        xTEST_EQ(m_vsRv.at(4), std::tstring_t(xT("4")));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
