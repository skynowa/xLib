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
    //--------------------------------------------------
    // bCreate, ulWait
    xTEST_CASE(cullCaseLoops)
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

            m_bRv = prProc.bCreate(csFilePath, xT("%s"), csCmdLine.c_str());
            xTEST_EQ(true, m_bRv);

            CxProcess::ExWaitResult wrRes = prProc.ulWait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrObject0, wrRes);
        #endif
    }

    //--------------------------------------------------
    // bKill
    xTEST_CASE(cullCaseLoops)
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

            m_bRv = prProc.bCreate(csFilePath, xT("%s"), csCmdLine.c_str());
            xTEST_EQ(true, m_bRv);

            m_bRv = prProc.bKill(10UL);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    // hGet, ulGetId
    xTEST_CASE(cullCaseLoops)
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

            m_bRv = prProc.bCreate(csFilePath, xT("%s"), csCmdLine.c_str());
            xTEST_EQ(true, m_bRv);

            CxProcess::handle_t hHandle = prProc.hGet();
            xTEST_DIFF(static_cast<CxProcess::handle_t>( NULL ), hHandle);

            CxProcess::id_t ulId = prProc.ulGetId();
            xTEST_LESS(static_cast<CxProcess::id_t>( 0 ), ulId);

            CxProcess::ExWaitResult wrRes = prProc.ulWait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrObject0, wrRes);
        #endif
    }

    //--------------------------------------------------
    // ulGetIdByHandle
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::id_t ulId = CxProcess::ulGetIdByHandle( CxCurrentProcess::hGetHandle() );
        xTEST_DIFF(0UL, static_cast<ulong_t>( ulId ));
    }

    //--------------------------------------------------
    // ulGetHandleById
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::handle_t hHandle = CxProcess::ulGetHandleById( CxCurrentProcess::ulGetId() );
        xTEST_EQ(true, CxHandle(hHandle).bIsValid());
    }

    //--------------------------------------------------
    // bIsRunning
    xTEST_CASE(cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            std::tstring_t sData[][2] = {
                {xT("explorer.exe"),  xT("true") },
                {xT("explorer.exe "), xT("false")},
                {xT("explorer."),     xT("false")},
                {xT("explorer"),      xT("false")},
                {xT("explore"),       xT("false")},
            };
        #elif xOS_ENV_UNIX
            // TODO: xTEST_CASE for CxProcess::bIsRunning
        #endif

        #if   xOS_ENV_WIN
            for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
                const std::tstring_t csProcName = sData[i][0];
                const bool           cbRv       = CxString::bStrToBool(sData[i][1]);

                m_bRv = CxProcess::bIsRunning(csProcName);
                xTEST_EQ(cbRv, cbRv);
            }

            {
                const std::tstring_t csProcName = CxPath::sGetFileName(CxPath::sGetExe());

                m_bRv = CxProcess::bIsRunning(csProcName);
                xTEST_EQ(true, m_bRv);
            }
        #elif xOS_ENV_UNIX
            // TODO: xTEST_CASE for CxProcess::bIsRunning
        #endif
    }
}
//---------------------------------------------------------------------------
