/**
 * \file   CxTest_CxProcess.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxProcess.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Sync/CxCurrentProcess.h>


//---------------------------------------------------------------------------
CxTest_CxProcess::CxTest_CxProcess() {

}
//---------------------------------------------------------------------------
CxTest_CxProcess::~CxTest_CxProcess() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxProcess::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxProcess::create CxProcess::wait", cullCaseLoops)
    {
        #if 0
            #if   xOS_ENV_WIN
                const std::tstring_t csFilePath = xT("C:\\Windows\\System32\\attrib.exe");
                const std::tstring_t csCmdLine  = xT("");
            #elif xOS_ENV_UNIX
                const std::tstring_t csFilePath = xT("/usr/ls");
                const std::tstring_t csCmdLine  = xT("-la");
            #endif

            CxProcess prProc;

            prProc.create(csFilePath, xT("%s"), csCmdLine.c_str());

            CxProcess::ExWaitResult wrRes = prProc.wait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrObject0, wrRes);
        #endif
    }

    xTEST_CASE("CxProcess::kill", cullCaseLoops)
    {
        #if 0
            #if   xOS_ENV_WIN
                const std::tstring_t csFilePath = xT("C:\\Windows\\System32\\attrib.exe");
                const std::tstring_t csCmdLine  = xT("/?");
            #elif xOS_ENV_UNIX
                const std::tstring_t csFilePath = xT("/usr/ls");
                const std::tstring_t csCmdLine  = xT("-la");
            #endif

            CxProcess prProc;

            prProc.create(csFilePath, xT("%s"), csCmdLine.c_str());
            prProc.kill(10UL);
        #endif
    }

    xTEST_CASE("CxProcess::handle CxProcess::id", cullCaseLoops)
    {
        #if 0
            #if   xOS_ENV_WIN
                const std::tstring_t csFilePath = xT("C:\\Windows\\System32\\attrib.exe");
                const std::tstring_t csCmdLine  = xT("/?");
            #elif xOS_ENV_UNIX
                const std::tstring_t csFilePath = xT("/usr/bin/nautilus");
                const std::tstring_t csCmdLine  = xT(">");
            #endif

            CxProcess prProc;

            prProc.create(csFilePath, xT("%s"), csCmdLine.c_str());

            CxProcess::handle_t hHandle = prProc.handle();
            xTEST_DIFF(static_cast<CxProcess::handle_t>( NULL ), hHandle);

            CxProcess::id_t id = prProc.id();
            xTEST_LESS(static_cast<CxProcess::id_t>( 0 ), id);

            CxProcess::ExWaitResult wrRes = prProc.wait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrObject0, wrRes);
        #endif
    }

    xTEST_CASE("CxProcess::idByHandle", cullCaseLoops)
    {
        CxProcess::id_t id = CxProcess::idByHandle( CxCurrentProcess::handle() );
        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));
    }

    xTEST_CASE("CxProcess::handleById", cullCaseLoops)
    {
        CxProcess::handle_t hHandle = CxProcess::handleById( CxCurrentProcess::id() );
        xTEST_EQ(true, CxHandle(hHandle).isValid());
    }

    xTEST_CASE("CxProcess::idByName", cullCaseLoops)
    {
        const std::tstring_t csProcessName = CxPath( CxPath::exe() ).fileName();

        CxProcess::id_t id = CxProcess::idByName(csProcessName);
        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));

        // CxTracer() << xTRACE_VAR(id);
    }

    xTEST_CASE("CxProcess::isRunning", cullCaseLoops)
    {
        m_bRv = CxProcess::isRunning( CxCurrentProcess::id() );
        xTEST_EQ(true, m_bRv);
    }
}
//---------------------------------------------------------------------------
