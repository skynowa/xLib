/**
 * \file   Test_Process.cpp
 * \brief
 */


#include <Test/Sync/Test_Process.h>

#include <xLib/Core/String.h>
#include <xLib/IO/Path.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Process::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Process::create wait", a_caseLoops)
    {
        #if 1
            #if   xENV_WIN
                std::ctstring_t filePath = xT("C:\\Windows\\System32\\attrib.exe");
                std::ctstring_t cmdLine  = xT("");
            #elif xENV_UNIX
                std::ctstring_t filePath = xT("/bin/ls");
                std::ctstring_t cmdLine  = xT("-la");
            #endif

            Process proc;

            proc.create(filePath, xT("%s"), cmdLine.c_str());

            Process::ExWaitResult wrRes = proc.wait(xTIMEOUT_INFINITE);
            xTEST_EQ(Process::wrAbandoned, wrRes);
        #endif
    }

    xTEST_CASE("Process::kill", a_caseLoops)
    {
        #if   xENV_WIN
            std::ctstring_t filePath = xT("C:\\Windows\\System32\\attrib.exe");
            std::ctstring_t cmdLine  = xT("/?");
        #elif xENV_UNIX
            std::ctstring_t filePath = xT("/usr/bin/xmessage");
            std::ctstring_t cmdLine  = xT("-print \"Test Message\"");
        #endif

        Process proc;

        proc.create(filePath, xT("%s"), cmdLine.c_str());
        proc.kill(10UL);
    }

    xTEST_CASE("Process::handle id", a_caseLoops)
    {
        #if   xENV_WIN
            std::ctstring_t filePath = xT("C:\\Windows\\System32\\attrib.exe");
            std::ctstring_t cmdLine  = xT("/?");
        #elif xENV_UNIX
            std::ctstring_t filePath = xT("/usr/bin/xmessage");
            std::ctstring_t cmdLine  = xT("-print \"Test Message\"");
        #endif

        Process proc;

        proc.create(filePath, xT("%s"), cmdLine.c_str());

        Process::handle_t hHandle = proc.handle();
        xTEST_DIFF(static_cast<Process::handle_t>( NULL ), hHandle);

        Process::id_t id = proc.id();
        xTEST_LESS(static_cast<Process::id_t>( 0 ), id);

        proc.kill(10UL);
    }

    xTEST_CASE("Process::idByHandle", a_caseLoops)
    {
        Process::id_t id = Process::idByHandle( Process::currentHandle() );
        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));
    }

    xTEST_CASE("Process::handleById", a_caseLoops)
    {
    #if xTODO
        Process::handle_t hHandle = Process::handleById( Process::currentId() );
        xTEST_EQ(true, Handle(hHandle).isValid());
    #endif
    }

    xTEST_CASE("Process::idByName", a_caseLoops)
    {
        std::ctstring_t procName = Path( Path::exe() ).fileName();

        Process::id_t id = Process::idByName(procName);
        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));

        // Tracer() << xTRACE_VAR(id);
    }

    xTEST_CASE("Process::ids", a_caseLoops)
    {
        std::vector<Process::id_t> ids;

        Process::ids(&ids);
        #if xTEST_IGNORE
            Tracer() << ids;
        #endif
    }

    xTEST_CASE("Process::isRunning", a_caseLoops)
    {
        m_bRv = Process::isRunning( Process::currentId() );
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("Process::currentId", a_caseLoops)
    {
        Process::id_t ulRv = Process::currentId();
        xTEST_LESS(0UL, static_cast<ulong_t>( ulRv ));
    }

    xTEST_CASE("Process::currentParentId", a_caseLoops)
    {
        Process::id_t ulRv = Process::currentParentId();
        xTEST_LESS(0UL, static_cast<ulong_t>( ulRv ));
    }
}
//-------------------------------------------------------------------------------------------------
