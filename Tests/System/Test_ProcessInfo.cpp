/**
 * \file   Test_ProcessInfo.cpp
 * \brief  test ProcessInfo
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_ProcessInfo)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_ProcessInfo::unit()
{
	// TEST: Test_ProcessInfo

    xTEST_CASE("cpuUsage")
    {
        std::vector<Process::id_t> ids;
        Process::ids(&ids);

        for (const auto &it : ids) {
			// TODO: it
			xUNUSED(it);

            ProcessInfo info(/* it */ Process::currentId());
            m_ulRv = info.cpuUsage();
            // LogCout() << xT("\tProcessInfo::cpuUsage(): ") << m_ulRv;
        }
    }

    xTEST_CASE("ramUsage")
    {
        std::vector<Process::id_t> ids;
        Process::ids(&ids);

        for (const auto &it : ids) {
			// TODO: it
			xUNUSED(it);

            ProcessInfo info(/* it */ Process::currentId());
            m_ulRv = info.ramUsage();
            // LogCout() << xT("\tProcessInfo::ramUsage(): ") << m_ulRv;
        }
    }

    xTEST_CASE("ioBytes")
    {
        std::vector<Process::id_t> ids;
        Process::ids(&ids);

        for (const auto &it : ids) {
			// TODO: it
			xUNUSED(it);

            ProcessInfo info(/* it */ Process::currentId());
            m_ulRv = info.ioBytes();
            // LogCout() << xT("\tProcessInfo::ioBytes(): ") << m_ulRv;
        }
    }

    xTEST_CASE("exeName")
    {
        std::vector<Process::id_t> ids;
        Process::ids(&ids);

        for (const auto &it : ids) {
			// TODO: it
			xUNUSED(it);

            ProcessInfo info(/* it */ Process::currentId());
            m_sRv = info.exeName();
            xTEST(FileInfo(m_sRv).isExists());
            xTEST_EQ(m_sRv, Path::exe().str());
        }
    }

    xTEST_CASE("parentId")
    {
        std::vector<Process::id_t> ids;
        Process::ids(&ids);

        for (const auto &it : ids) {
			// TODO: it
			xUNUSED(it);

            ProcessInfo info(/* it */ Process::currentId());
            m_ulRv = info.parentId();
            /// xTEST_DIFF(m_ulRv, 0UL);
        }
    }

    xTEST_CASE("commandLine")
    {
        std::vector<Process::id_t> ids;
        Process::ids(&ids);

        for (const auto &it : ids) {
			// TODO: it
			xUNUSED(it);

        #if   xENV_WIN
            xCHECK_DO(it == 0 ,  continue);
            xCHECK_DO(it == 344, continue);
        #elif xENV_UNIX

        #endif
            ProcessInfo info(/* it */ Process::currentId());
            info.commandLine(&m_vsRv);
            xTEST(!m_vsRv.empty());
        }
    }

    xTEST_CASE("commandLineArgsMax")
    {
        m_liRv = ProcessInfo::commandLineArgsMax();
        xTEST_GR(m_liRv, 0L);
    }

    xTEST_CASE("commandLine")
    {
        cint_t        argsNum       = 5;
        cptr_ctchar_t args[argsNum] = {xT("./xLib_test"), xT("1"), xT("2"), xT("3"), xT("4")};

        ProcessInfo::commandLine(argsNum, args, &m_vsRv);
        xTEST_EQ(m_vsRv.size(), argsNum);
        xTEST_EQ(m_vsRv.at(0), std::tstring_t(xT("./xLib_test")));
        xTEST_EQ(m_vsRv.at(1), std::tstring_t(xT("1")));
        xTEST_EQ(m_vsRv.at(2), std::tstring_t(xT("2")));
        xTEST_EQ(m_vsRv.at(3), std::tstring_t(xT("3")));
        xTEST_EQ(m_vsRv.at(4), std::tstring_t(xT("4")));
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
