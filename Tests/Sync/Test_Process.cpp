/**
 * \file   Test_Process.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Process)
xTEST_UNIT(Test_Process)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Process::unit()
{
//    xTEST_CASE("create, wait")
//    {
//    #if   xENV_WIN
//        std::ctstring_t     filePath = xT("C:\\Windows\\System32\\attrib.exe");
//        std::cvec_tstring_t cmdLine  = {xT("")};
//    #elif xENV_UNIX
//        std::ctstring_t     filePath = xT("/bin/ls");
//        std::cvec_tstring_t cmdLine  = {xT("-la")};
//    #endif
//
//        Process proc;
//
//    	std::tstring_t stdOut;
//    	std::tstring_t stdError;
//        proc.create(filePath, cmdLine, {}, &stdOut, &stdError);
//
//		Cout() << xTRACE_VAR(stdOut);
//		Cout() << xTRACE_VAR(stdError);
//
//        Process::WaitStatus wrRes = proc.wait(xTIMEOUT_INFINITE);
//        xTEST_EQ((int)Process::WaitStatus::Abandoned, (int)wrRes);
//    }
//
//    xTEST_CASE("kill")
//    {
//    #if   xENV_WIN
//        std::ctstring_t     filePath = xT("C:\\Windows\\System32\\attrib.exe");
//        std::cvec_tstring_t cmdLine  = {xT("/?")};
//    #elif xENV_UNIX
//        std::ctstring_t     filePath = xT("/usr/bin/xmessage");
//        std::cvec_tstring_t cmdLine  = {xT("-print"), xT("\"Test Message\"")};
//        // std::ctstring_t     filePath = xT("/usr/bin/man");
//        // td::cvec_tstring_t cmdLine  = {xT("ls")};
//    #endif
//
//        Process proc;
//
//        std::tstring_t stdOut;
//    	std::tstring_t stdError;
//        proc.create(filePath, cmdLine, {}, &stdOut, &stdError);
//
//       	proc.kill(10UL);
//    }
//
//    xTEST_CASE("handle, id, name, setName")
//    {
//    #if   xENV_WIN
//        std::ctstring_t     filePath = xT("C:\\Windows\\System32\\attrib.exe");
//        std::cvec_tstring_t cmdLine  = {xT("/?")};
//    #elif xENV_UNIX
//        std::ctstring_t     filePath = xT("/usr/bin/xmessage");
//        std::cvec_tstring_t cmdLine  = {xT("-print"), xT("\"Test Message\"")};
//    #endif
//
//        Process proc;
//
//    	std::tstring_t stdOut;
//    	std::tstring_t stdError;
//        proc.create(filePath, cmdLine, {}, &stdOut, &stdError);
//
//        Process::handle_t hHandle = proc.handle();
//        xTEST_DIFF(hHandle, static_cast<Process::handle_t>(0));
//
//        Process::id_t id = proc.id();
//        xTEST_LESS(static_cast<Process::id_t>(0), id);
//
//        // name, setName
//        std::ctstring_t procName = xT("Test_Process");
//        xTEST_EQ(proc.name(), procName);
//
//        std::ctstring_t procNameNew = xT("Test_Process_A");
//        proc.setName(procNameNew);
//        xTEST_EQ(proc.name(), procNameNew);
//
//        proc.setName(procName);
//        xTEST_EQ(proc.name(), procName);
//
//        proc.kill(10UL);
//    }
//
//    xTEST_CASE("idByHandle")
//    {
//        Process::id_t id = Process::idByHandle( Process::currentHandle() );
//        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));
//    }
//
//    xTEST_CASE("handleById")
//    {
//    #if xTODO
//        Process::handle_t hHandle = Process::handleById( Process::currentId() );
//        xTEST_EQ(true, Handle(hHandle).isValid());
//    #endif
//    }
//
//    xTEST_CASE("idByName")
//    {
//        std::ctstring_t procName = Path( Path::exe() ).fileName();
//
//        Process::id_t id = Process::idByName(procName);
//        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));
//
//        // Cout() << xTRACE_VAR(id);
//    }
//
//    xTEST_CASE("ids")
//    {
//        std::vector<Process::id_t> ids;
//
//        Process::ids(&ids);
//        #if xTEST_IGNORE
//            Cout() << ids;
//        #endif
//    }
//
//    xTEST_CASE("isRunning")
//    {
//        m_bRv = Process::isRunning( Process::currentId() );
//        xTEST_EQ(m_bRv, true);
//    }
//
//    xTEST_CASE("currentId")
//    {
//        Process::id_t ulRv = Process::currentId();
//        xTEST_LESS(0UL, static_cast<ulong_t>( ulRv ));
//    }
//
//    xTEST_CASE("currentParentId")
//    {
//        Process::id_t ulRv = Process::currentParentId();
//        xTEST_LESS(0UL, static_cast<ulong_t>( ulRv ));
//    }

	xTEST_CASE("execute")
	{
		struct Data
		{
			std::ctstring_t                     filePath;
			std::cvec_tstring_t                 params;
			const std::set<std::pair_tstring_t> envs;
			std::tstring_t                      stdOut;
			std::tstring_t                      stdError;
		};

		std::vector<Data> datas
		{
		#if   xENV_WIN
			{xT("C:\\Windows\\System32\\attrib.exe"), {}, {}, {}, {}}
		#elif xENV_UNIX
			{xT("/bin/ls"), {xT("-la")}, {}, {}, {}},
			{xT("/usr/bin/xmessage"), {xT("-print"), xT("\"Test Message\"")}, {}, {}, {}},
			{xT("badfile.txt"), {}, {}, {}, {}}
		#endif
		};

		for (auto &it_data : datas) {
			Process::execute(it_data.filePath, xTIMEOUT_INFINITE, it_data.params, it_data.envs,
				&it_data.stdOut, &it_data.stdError);
			// Cout() << xTRACE_VAR(it_data.stdOut);
			// Cout() << xTRACE_VAR(it_data.stdError);

			break;	///
		} // for (datas)
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
