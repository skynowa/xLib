/****************************************************************************
* Class name:  CxTest_CxCommandLine
* Description: test CxCommandLine
* File name:   CxTest_CxCommandLine.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxCommandLine.h>


//---------------------------------------------------------------------------
CxTest_CxCommandLine::CxTest_CxCommandLine() {

}
//---------------------------------------------------------------------------
CxTest_CxCommandLine::~CxTest_CxCommandLine() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxCommandLine::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //liGetArgsMax
    xTEST_BLOCK(cullBlockLoops)
    {
        m_liRes = CxCommandLine::liGetArgsMax();
        xTEST_LESS(0L, m_liRes);
        //xTRACEV(xT("\tCxCommandLine::liGetArgsMax() = %li"), m_liRes);
    }

    //-------------------------------------
    //sGet
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxCommandLine::sGet();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxCommandLine::sGet(): %s"), m_sRes.c_str());
        #endif
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //bGetArgs
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxCommandLine::bGetArgs(&m_vsRes);
        xTEST_DIFF(FALSE,  m_bRes);
        xTEST_EQ(false, m_vsRes.empty());
    }

    //--------------------------------------------------
    //bSetArgs
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            m_bRes = CxCommandLine::bSetArgs(ciArgsCount, paszArgs);
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
