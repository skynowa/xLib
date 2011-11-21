/**
 * \file   CxTest_CxProcess.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxProcess.h>


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
    const ulonglong_t cullBlockLoops
)
{
    //--------------------------------------------------
    //bExec
    xTEST_CASE(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t csFilePath = xT("explorer.exe");
            const std::tstring_t csCmdLine  = xT("");
        #elif xOS_ENV_UNIX
            const std::tstring_t csFilePath = xT("dolphin");
            const std::tstring_t csCmdLine  = xT("");
        #endif

        ////m_bRes = CxProcess::bExec(csFilePath, csCmdLine.c_str(), 0);
        ////xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //bExit
    xTEST_CASE(cullBlockLoops)
    {
        ////m_bRes = CxProcess::bExit(CxProcess::ulGetCurrParentId(), 0);
        ////xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //bTerminate
    xTEST_CASE(cullBlockLoops)
    {
        //m_bRes = CxProcess::bTerminate(CxProcess::ulGetCurrParentId());
        //xTEST_DIFF(false, m_bRes);
    }

    return true;
}
//---------------------------------------------------------------------------
