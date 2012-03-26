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
        #if xOS_ENV_WIN
            const std::tstring_t csFilePath = xT("explorer.exe");
            const std::tstring_t csCmdLine  = xT("");
        #elif xOS_ENV_UNIX
            const std::tstring_t csFilePath = xT("/usr/bin/nautilus");
            const std::tstring_t csCmdLine  = xT("");
        #endif


        CxProcess prProc;

        m_bRes = prProc.bCreate(csFilePath, xT("%s"), csCmdLine.c_str());
        xTEST_EQ(true, m_bRes);

        m_ulRes = prProc.ulWait(xTIMEOUT_INFINITE);
        #if xTEST_IGNORE
            xTRACEV(xT("CxProcess::ulWait: %lu"), m_ulRes);

            ::sleep(10);
        #endif
    }

    //--------------------------------------------------
    // TODO: ulWait
    xTEST_CASE(cullCaseLoops)
    {
        //m_bRes = CxProcess::ulWait();
        //xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    // TODO: bKill
    xTEST_CASE(cullCaseLoops)
    {
        //m_bRes = CxProcess::bKill();
        //xTEST_EQ(true, m_bRes);
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
