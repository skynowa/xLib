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
    //bExec
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t csFilePath = xT("explorer.exe");
            const std::tstring_t csCmdLine  = xT("");
        #elif xOS_ENV_UNIX
            const std::tstring_t csFilePath = xT("dolphin");
            const std::tstring_t csCmdLine  = xT("");
        #endif

        ////m_bRes = CxProcess::bExec(csFilePath, csCmdLine.c_str(), 0);
        ////xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bExit
    xTEST_CASE(cullCaseLoops)
    {
        ////m_bRes = CxProcess::bExit(CxProcess::ulGetCurrParentId(), 0);
        ////xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bTerminate
    xTEST_CASE(cullCaseLoops)
    {
        //m_bRes = CxProcess::bTerminate(CxProcess::ulGetCurrParentId());
        //xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //ulGetIdByHandle
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::TxId ulId = CxProcess::ulGetIdByHandle( CxCurrentProcess::hGetHandle() );
        xTEST_DIFF(0UL, ulId);
    }

    //--------------------------------------------------
    //ulGetHandleById
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::TxHandle hHandle = CxProcess::ulGetHandleById( CxCurrentProcess::ulGetId() );
        xTEST_EQ(true, CxHandle(hHandle).bIsValid());
    }

    return true;
}
//---------------------------------------------------------------------------
