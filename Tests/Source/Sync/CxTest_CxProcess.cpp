/**
 * \file   CxTest_CxProcess.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxProcess.h>

#include <xLib/Sync/CxCurrentProcess.h>


//---------------------------------------------------------------------------
CxTest_CxProcess::CxTest_CxProcess() {

}
//---------------------------------------------------------------------------
CxTest_CxProcess::~CxTest_CxProcess() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxProcess::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    // bCreate, ulWait
    xTEST_CASE(cullCaseLoops)
    {
        #if 1
            #if xOS_ENV_WIN
                const std::tstring_t csFilePath = xT("C:\\Windows\\System32\\attrib.exe");
                const std::tstring_t csCmdLine  = xT("/?");
            #elif xOS_ENV_UNIX
                const std::tstring_t csFilePath = xT("/usr/ls");
                const std::tstring_t csCmdLine  = xT("-la");
            #endif

            CxProcess prProc;

            m_bRv = prProc.bCreate(csFilePath, xT("%s"), csCmdLine.c_str());
            xTEST_EQ(true, m_bRv);

            CxProcess::EWaitResult wrRes = prProc.ulWait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrObject0, wrRes);
        #endif
    }

    //--------------------------------------------------
    // bKill
    xTEST_CASE(cullCaseLoops)
    {
        #if 1
            #if xOS_ENV_WIN
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
        #if 1
            #if xOS_ENV_WIN
                const std::tstring_t csFilePath = xT("C:\\Windows\\System32\\attrib.exe");
                const std::tstring_t csCmdLine  = xT("/?");
            #elif xOS_ENV_UNIX
                const std::tstring_t csFilePath = xT("/usr/bin/nautilus");
                const std::tstring_t csCmdLine  = xT("");
            #endif

            CxProcess prProc;

            m_bRv = prProc.bCreate(csFilePath, xT("%s"), csCmdLine.c_str());
            xTEST_EQ(true, m_bRv);

            CxProcess::TxHandle hHandle = prProc.hGet();
            xTEST_DIFF(static_cast<CxProcess::TxHandle>( NULL ), hHandle);

            CxProcess::TxId ulId = prProc.ulGetId();
            xTEST_LESS(static_cast<CxProcess::TxId>( 0 ), ulId);

            CxProcess::EWaitResult wrRes = prProc.ulWait(xTIMEOUT_INFINITE);
            xTEST_EQ(CxProcess::wrObject0, wrRes);
        #endif
    }

    //--------------------------------------------------
    // ulGetIdByHandle
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::TxId ulId = CxProcess::ulGetIdByHandle( CxCurrentProcess::hGetHandle() );
        xTEST_DIFF(0UL, static_cast<ulong_t>( ulId ));
    }

    //--------------------------------------------------
    // ulGetHandleById
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::TxHandle hHandle = CxProcess::ulGetHandleById( CxCurrentProcess::ulGetId() );
        xTEST_EQ(true, CxHandle(hHandle).bIsValid());
    }

    return true;
}
//---------------------------------------------------------------------------
