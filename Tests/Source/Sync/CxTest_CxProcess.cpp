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
//DONE: CxTest_CxProcess
CxTest_CxProcess::CxTest_CxProcess() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxProcess
CxTest_CxProcess::~CxTest_CxProcess() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
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
        m_ulRes = CxProcess::ulGetCurrId();
        xASSERT_LESS_EQUAL(0UL, m_ulRes);
    }

    //--------------------------------------------------
    //ulGetCurrParentId
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = CxProcess::ulGetCurrParentId();
        xASSERT_LESS_EQUAL(0UL, m_ulRes);
    }

    //--------------------------------------------------
    //bExec
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_WIN)
            const tString csFilePath = xT("explorer.exe");
            const tString csCmdLine  = xT("");
        #elif defined(xOS_LINUX)
            const tString csFilePath = xT("dolphin");
            const tString csCmdLine  = xT("");
        #endif

        ////m_bRes = CxProcess::bExec(csFilePath, csCmdLine.c_str(), 0);
        ////xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bExit
    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_bRes = CxProcess::bExit(CxProcess::ulGetCurrParentId(), 0);
        ////xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bTerminate
    xTEST_BLOCK(cullBlockLoops)
    {
        //m_bRes = CxProcess::bTerminate(CxProcess::ulGetCurrParentId());
        //xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
