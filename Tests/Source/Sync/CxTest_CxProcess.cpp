/****************************************************************************
* Class name:  CxTest_CxProcess
* Description: test CxTest_CxProcess
* File name:   CxTest_CxProcess.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


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
    //ulGetCurrId
    xTEST_BLOCK(cullBlockLoops)
    {
        CxProcess::TxId ulRes = CxProcess::ulGetCurrId();
        xASSERT_LESS_EQ(0UL, (ULONG)ulRes);
    }

    //--------------------------------------------------
    //ulGetCurrParentId
    xTEST_BLOCK(cullBlockLoops)
    {
        CxProcess::TxId ulRes = CxProcess::ulGetCurrParentId();
        xASSERT_LESS_EQ(0UL, (ULONG)ulRes);
    }

    //--------------------------------------------------
    //bExec
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const std::tstring csFilePath = xT("explorer.exe");
            const std::tstring csCmdLine  = xT("");
        #elif defined(xOS_ENV_UNIX)
            const std::tstring csFilePath = xT("dolphin");
            const std::tstring csCmdLine  = xT("");
        #endif

        ////m_bRes = CxProcess::bExec(csFilePath, csCmdLine.c_str(), 0);
        ////xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bExit
    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_bRes = CxProcess::bExit(CxProcess::ulGetCurrParentId(), 0);
        ////xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bTerminate
    xTEST_BLOCK(cullBlockLoops)
    {
        //m_bRes = CxProcess::bTerminate(CxProcess::ulGetCurrParentId());
        //xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
