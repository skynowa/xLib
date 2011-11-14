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
BOOL
CxTest_CxProcess::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bExec
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const std::string_t csFilePath = xT("explorer.exe");
            const std::string_t csCmdLine  = xT("");
        #elif defined(xOS_ENV_UNIX)
            const std::string_t csFilePath = xT("dolphin");
            const std::string_t csCmdLine  = xT("");
        #endif

        ////m_bRes = CxProcess::bExec(csFilePath, csCmdLine.c_str(), 0);
        ////xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bExit
    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_bRes = CxProcess::bExit(CxProcess::ulGetCurrParentId(), 0);
        ////xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bTerminate
    xTEST_BLOCK(cullBlockLoops)
    {
        //m_bRes = CxProcess::bTerminate(CxProcess::ulGetCurrParentId());
        //xTEST_DIFF(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
