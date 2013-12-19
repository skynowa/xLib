/**
 * \file   CxTest_CxProcess.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxProcess.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxProcess::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxProcess::create CxProcess::wait", a_caseLoops)
    {
        #if 1
            #if   xOS_ENV_WIN
                std::ctstring_t filePath = xT("C:\\Windows\\System32\\attrib.exe");
                std::ctstring_t cmdLine  = xT("");
            #elif xOS_ENV_UNIX
                std::ctstring_t filePath = xT("/bin/ls");
                std::ctstring_t cmdLine  = xT("-la");
            #endif

            CxProcess proc;

            proc.create(filePath, xT("%s"), cmdLine.c_str());

            CxProcess::ExWaitResult wrRes = proc.wait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrAbandoned, wrRes);
        #endif
    }

    xTEST_CASE("CxProcess::kill", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t filePath = xT("C:\\Windows\\System32\\attrib.exe");
            std::ctstring_t cmdLine  = xT("/?");
        #elif xOS_ENV_UNIX
            std::ctstring_t filePath = xT("/usr/bin/xmessage");
            std::ctstring_t cmdLine  = xT("-print \"Test Message\"");
        #endif

        CxProcess proc;

        proc.create(filePath, xT("%s"), cmdLine.c_str());
        proc.kill(10UL);
    }

    xTEST_CASE("CxProcess::handle CxProcess::id", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t filePath = xT("C:\\Windows\\System32\\attrib.exe");
            std::ctstring_t cmdLine  = xT("/?");
        #elif xOS_ENV_UNIX
            std::ctstring_t filePath = xT("/usr/bin/xmessage");
            std::ctstring_t cmdLine  = xT("-print \"Test Message\"");
        #endif

        CxProcess proc;

        proc.create(filePath, xT("%s"), cmdLine.c_str());

        CxProcess::handle_t hHandle = proc.handle();
        xTEST_DIFF(static_cast<CxProcess::handle_t>( NULL ), hHandle);

        CxProcess::id_t id = proc.id();
        xTEST_LESS(static_cast<CxProcess::id_t>( 0 ), id);

        proc.kill(10UL);
    }

    xTEST_CASE("CxProcess::idByHandle", a_caseLoops)
    {
        CxProcess::id_t id = CxProcess::idByHandle( CxProcess::currentHandle() );
        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));
    }

    xTEST_CASE("CxProcess::handleById", a_caseLoops)
    {
    #if xTODO
        CxProcess::handle_t hHandle = CxProcess::handleById( CxProcess::currentId() );
        xTEST_EQ(true, CxHandle(hHandle).isValid());
    #endif
    }

    xTEST_CASE("CxProcess::idByName", a_caseLoops)
    {
        std::ctstring_t procName = CxPath( CxPath::exe() ).fileName();

        CxProcess::id_t id = CxProcess::idByName(procName);
        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));

        // CxTracer() << xTRACE_VAR(id);
    }

    xTEST_CASE("CxProcess::ids", a_caseLoops)
    {
        std::vector<CxProcess::id_t> ids;

        CxProcess::ids(&ids);
        #if xTEST_IGNORE
            CxTracer() << ids;
        #endif
    }

    xTEST_CASE("CxProcess::isRunning", a_caseLoops)
    {
        m_bRv = CxProcess::isRunning( CxProcess::currentId() );
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxProcess::currentId", a_caseLoops)
    {
        CxProcess::id_t ulRv = CxProcess::currentId();
        xTEST_LESS(0UL, static_cast<ulong_t>( ulRv ));
    }

    xTEST_CASE("CxProcess::currentParentId", a_caseLoops)
    {
        CxProcess::id_t ulRv = CxProcess::currentParentId();
        xTEST_LESS(0UL, static_cast<ulong_t>( ulRv ));
    }
}
//-------------------------------------------------------------------------------------------------
