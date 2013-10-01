/**
 * \file   CxTest_CxProcess.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxProcess.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Sync/CxCurrentProcess.h>


//------------------------------------------------------------------------------
CxTest_CxProcess::CxTest_CxProcess() {

}
//------------------------------------------------------------------------------
CxTest_CxProcess::~CxTest_CxProcess() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxProcess::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxProcess::create CxProcess::wait", a_cullCaseLoops)
    {
        #if 0
            #if   xOS_ENV_WIN
                std::ctstring_t csFilePath = xT("C:\\Windows\\System32\\attrib.exe");
                std::ctstring_t csCmdLine  = xT("");
            #elif xOS_ENV_UNIX
                std::ctstring_t csFilePath = xT("/usr/ls");
                std::ctstring_t csCmdLine  = xT("-la");
            #endif

            CxProcess prProc;

            prProc.create(csFilePath, xT("%s"), csCmdLine.c_str());

            CxProcess::ExWaitResult wrRes = prProc.wait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrObject0, wrRes);
        #endif
    }

    xTEST_CASE("CxProcess::kill", a_cullCaseLoops)
    {
        #if 0
            #if   xOS_ENV_WIN
                std::ctstring_t csFilePath = xT("C:\\Windows\\System32\\attrib.exe");
                std::ctstring_t csCmdLine  = xT("/?");
            #elif xOS_ENV_UNIX
                std::ctstring_t csFilePath = xT("/usr/ls");
                std::ctstring_t csCmdLine  = xT("-la");
            #endif

            CxProcess prProc;

            prProc.create(csFilePath, xT("%s"), csCmdLine.c_str());
            prProc.kill(10UL);
        #endif
    }

    xTEST_CASE("CxProcess::handle CxProcess::id", a_cullCaseLoops)
    {
        #if 0
            #if   xOS_ENV_WIN
                std::ctstring_t csFilePath = xT("C:\\Windows\\System32\\attrib.exe");
                std::ctstring_t csCmdLine  = xT("/?");
            #elif xOS_ENV_UNIX
                std::ctstring_t csFilePath = xT("/usr/bin/nautilus");
                std::ctstring_t csCmdLine  = xT(">");
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

    xTEST_CASE("CxProcess::idByHandle", a_cullCaseLoops)
    {
        CxProcess::id_t id = CxProcess::idByHandle( CxCurrentProcess::handle() );
        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));
    }

    xTEST_CASE("CxProcess::handleById", a_cullCaseLoops)
    {
        CxProcess::handle_t hHandle = CxProcess::handleById( CxCurrentProcess::id() );
        xTEST_EQ(true, CxHandle(hHandle).isValid());
    }

    xTEST_CASE("CxProcess::idByName", a_cullCaseLoops)
    {
        std::ctstring_t csProcessName = CxPath( CxPath::exe() ).fileName();

        CxProcess::id_t id = CxProcess::idByName(csProcessName);
        xTEST_DIFF(0UL, static_cast<ulong_t>( id ));

        // CxTracer() << xTRACE_VAR(id);
    }

    xTEST_CASE("CxProcess::isRunning", a_cullCaseLoops)
    {
        m_bRv = CxProcess::isRunning( CxCurrentProcess::id() );
        xTEST_EQ(true, m_bRv);
    }
}
//------------------------------------------------------------------------------
