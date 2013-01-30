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
CxTest_CxProcess::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxProcess::create CxProcess::ulWait", cullCaseLoops)
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

            CxProcess::ExWaitResult wrRes = prProc.ulWait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrObject0, wrRes);
        #endif
    }

    xTEST_CASE("CxProcess::vKill", cullCaseLoops)
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
            prProc.vKill(10UL);
        #endif
    }

    xTEST_CASE("CxProcess::hGet CxProcess::ulGetId", cullCaseLoops)
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

            CxProcess::handle_t hHandle = prProc.hGet();
            xTEST_DIFF(static_cast<CxProcess::handle_t>( NULL ), hHandle);

            CxProcess::id_t ulId = prProc.ulGetId();
            xTEST_LESS(static_cast<CxProcess::id_t>( 0 ), ulId);

            CxProcess::ExWaitResult wrRes = prProc.ulWait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrObject0, wrRes);
        #endif
    }

    xTEST_CASE("CxProcess::ulIdByHandle", cullCaseLoops)
    {
        CxProcess::id_t ulId = CxProcess::ulIdByHandle( CxCurrentProcess::hHandle() );
        xTEST_DIFF(0UL, static_cast<ulong_t>( ulId ));
    }

    xTEST_CASE("CxProcess::ulGetHandleById", cullCaseLoops)
    {
        CxProcess::handle_t hHandle = CxProcess::ulHandleById( CxCurrentProcess::ulId() );
        xTEST_EQ(true, CxHandle(hHandle).isValid());
    }

    xTEST_CASE("CxProcess::ulIdByName", cullCaseLoops)
    {
        const std::tstring_t csProcessName = CxPath( CxPath::exe() ).fileName();

        CxProcess::id_t ulId = CxProcess::ulIdByName(csProcessName);
        xTEST_DIFF(0UL, static_cast<ulong_t>( ulId ));

        // CxTracer() << xTRACE_VAR(ulId);
    }

    xTEST_CASE("CxProcess::bIsRunning", cullCaseLoops)
    {
        m_bRv = CxProcess::bIsRunning( CxCurrentProcess::ulId() );
        xTEST_EQ(true, m_bRv);
    }
}
//---------------------------------------------------------------------------
