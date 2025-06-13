/**
 * \file   Test_Process.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Process)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Process::unit()
{
	if ( isGithubCI() ) {
		LogCout() << "GithubCI - skip";
		return true;
	}

    xTEST_CASE("create, wait")
    {
		struct Data
		{
			std::ctstring_t     filePath;
			std::cvec_tstring_t params;
			bool_t              isEnable; // UI test - false
		};

		cbool_t isUiTests {true};

		std::vector<Data> datas
		{
		#if   xENV_WIN
			{xT("C:\\Windows\\System32\\attrib.exe"), {}, true}
		#elif xENV_UNIX
			{xT("/bin/ls"), {xT("-la")}, true}
		#endif
		};

		for (const auto &[it_filePath, it_params, it_isEnable] : datas) {
			if (!it_isEnable) {
				LogCout() << xT("Skip UI test: ") << xTRACE_VAR(it_filePath);
				continue;
			}

			Process proc;

			std::tstring_t stdOut;
			std::tstring_t stdError;
			proc.create(it_filePath, it_params, {}, &stdOut, &stdError);

			Process::WaitStatus wrRes = proc.wait(xTIMEOUT_INFINITE);
			xTEST_EQ((int)wrRes,   (int)Process::WaitStatus::Ok);
			xTEST_DIFF((int)wrRes, (int)Process::WaitStatus::Abandoned);
		} // for (datas)
    }

    xTEST_CASE("kill")
    {
		struct Data
		{
			std::ctstring_t     filePath;
			std::cvec_tstring_t params;
			bool_t              isEnable; // UI test - false
		};

		cbool_t isUiTests {false};

		std::vector<Data> datas
		{
		#if   xENV_WIN
			{xT("C:\\Windows\\System32\\attrib.exe"), {xT("/?")}, true}
		#elif xENV_UNIX
			{xT("/usr/bin/xmessage"), {xT("-print"), xT("\"Test Message\"")}, isUiTests},
			{xT("/usr/bin/man"), {xT("ls")}, true}
		#endif
		};

		for (const auto &[it_filePath, it_params, it_isEnable] : datas) {
			if (!it_isEnable) {
				LogCout() << xT("Skip UI test: ") << xTRACE_VAR(it_filePath);
				continue;
			}

			Process proc;

			std::tstring_t stdOut;
			std::tstring_t stdError;
			proc.create(it_filePath, it_params, {}, &stdOut, &stdError);

			proc.kill(10UL);
		} // for (datas)
    }

    xTEST_CASE("handle, id, name, setName")
    {
		struct Data
		{
			std::ctstring_t     filePath;
			std::cvec_tstring_t params;
			bool_t              isEnable; // UI test - false
		};

		cbool_t isUiTests {false};

		std::vector<Data> datas
		{
		#if   xENV_WIN
			{xT("C:\\Windows\\System32\\attrib.exe"), {xT("/?")}, false}
		#elif xENV_UNIX
			{xT("/usr/bin/xmessage"), {xT("-print"), xT("\"Test Message\"")}, isUiTests}
		#endif
		};

		for (const auto &[it_filePath, it_params, it_isEnable] : datas) {
			if (!it_isEnable) {
				LogCout() << xT("Skip UI test: ") << xTRACE_VAR(it_filePath);
				continue;
			}

			Process proc;

			std::tstring_t stdOut;
			std::tstring_t stdError;
			proc.create(it_filePath, it_params, {}, &stdOut, &stdError);

			Process::handle_t hHandle = proc.handle();
			xTEST_DIFF(hHandle, static_cast<Process::handle_t>(0));

			Process::id_t id = proc.id();
			xTEST_GR_EQ(id, static_cast<Process::id_t>(0));

			// name, setName
			std::ctstring_t procName = xT("Test_Process");
			xTEST_EQ(proc.name(), procName);

			std::ctstring_t procNameNew = xT("Test_Process_A");
			proc.setName(procNameNew);
			xTEST_EQ(proc.name(), procNameNew);

			proc.setName(procName);
			xTEST_EQ(proc.name(), procName);

			proc.kill(10UL);
		} // for (vars)
    }

    xTEST_CASE("idByHandle")
    {
        Process::id_t id = Process::idByHandle( Process::currentHandle() );
        xTEST_DIFF(static_cast<ulong_t>(id), 0UL);
    }

    xTEST_CASE("handleById")
    {
		Process::handle_t handle = Process::handleById( Process::currentId() );
		xTEST_GR_EQ(handle, 0);
    }

    xTEST_CASE("idByName")
    {
        std::ctstring_t procName = Path::exe().fileName();

        Process::id_t id = Process::idByName(procName);
        xTEST_GR_EQ(id, 0UL);
    }

    xTEST_CASE("ids")
    {
        std::vector<Process::id_t> ids;

        Process::ids(&ids);
        xTEST(!ids.empty());
    }

    xTEST_CASE("isRunning")
    {
        m_bRv = Process::isRunning( Process::currentId() );
        xTEST(m_bRv);
    }

    xTEST_CASE("currentId")
    {
        Process::id_t ulRv = Process::currentId();
        xTEST_GR_EQ(static_cast<ulong_t>(ulRv), 0UL);
    }

    xTEST_CASE("currentParentId")
    {
        Process::id_t ulRv = Process::currentParentId();
        xTEST_GR_EQ(static_cast<ulong_t>(ulRv), 0UL);
    }

	xTEST_CASE("execute")
	{
		struct Data
		{
			std::ctstring_t                     filePath;
			std::cvec_tstring_t                 params;
			const std::set<std::pair_tstring_t> envs;
			std::tstring_t                      stdOut;
			std::tstring_t                      stdError;
			bool_t                              isEnable; // UI test - false
		};

		cbool_t isUiTests {false};

		std::vector<Data> datas
		{
		#if   xENV_WIN
			{xT("C:\\Windows\\System32\\attrib.exe"), {}, {}, {}, {}, true}
		#elif xENV_UNIX
			{xT("/bin/ls"), {xT("-la")}, {}, {}, {}, true},
			{xT("/usr/bin/xmessage"), {xT("-print"), xT("\"Test Message\"")}, {}, {}, {}, isUiTests},
			{xT("badfile.txt"), {}, {}, {}, {}, true}
		#endif
		};

		for (auto &[it_filePath, it_params, it_envs, it_stdOut, it_stdError, it_isEnable] : datas) {
			if (!it_isEnable) {
				LogCout() << xT("Skip UI test: ") << xTRACE_VAR(it_filePath);
				continue;
			}

			Process::execute(it_filePath, it_params, it_envs, xTIMEOUT_INFINITE, &it_stdOut,
				&it_stdError);
		} // for (datas)
	}

	xTEST_CASE("shellExecute")
	{
		struct Data
		{
			std::tstring_t     cmdLine;
			std::vec_tstring_t params;
			bool_t             isEnable; // UI test - false
		};

		cbool_t isUiTests {false};

		const std::vector<Data> datas
		{
			{xT("/home/skynowa/Projects/xLib/TODO.md"), {}, isUiTests},
			{xT("https://stackoverflow.com"), {}, isUiTests},

		#if   xENV_WIN
			{xT("C:\\Windows\\System32\\attrib.exe")}, {}, true}
		#elif xENV_UNIX
			{xT("/bin/ls"), {}, true},
			{xT("/usr/bin/xmessage"), {xT("-print"), xT("\"Test Message\"")}, isUiTests}
		#endif
		};

		for (const auto &[it_cmdLine, it_params, it_isEnable] : datas) {
			if (!it_isEnable) {
				LogCout() << xT("Skip UI test: ") << xTRACE_VAR(it_cmdLine);
				continue;
			}

			Process::shellExecute(it_cmdLine, it_params);
		} // for (datas)
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
