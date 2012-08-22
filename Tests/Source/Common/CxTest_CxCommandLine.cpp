/**
 * \file   CxTest_CxCommandLine.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxCommandLine.h>


//---------------------------------------------------------------------------
CxTest_CxCommandLine::CxTest_CxCommandLine() {

}
//---------------------------------------------------------------------------
CxTest_CxCommandLine::~CxTest_CxCommandLine() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxCommandLine::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //liGetArgsMax
    xTEST_CASE(cullCaseLoops)
    {
        m_liRv = CxCommandLine::liGetArgsMax();
        xTEST_LESS(0L, m_liRv);
        //xTRACEV(xT("\tCxCommandLine::liGetArgsMax() = %li"), m_liRv);
    }

    //-------------------------------------
    //sGet
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxCommandLine::sGet();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxCommandLine::sGet(): %s"), m_sRv.c_str());
        #endif
        xTEST_EQ(false, m_sRv.empty());
    }

    //-------------------------------------
    //bGetArgs
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxCommandLine::bGetArgs(&m_vsRv);
        xTEST_EQ(true,  m_bRv);
        xTEST_EQ(false, m_vsRv.empty());
    }

    //--------------------------------------------------
    //bSetArgs
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            m_bRv = CxCommandLine::bSetArgs(ciArgsCount, paszArgs);
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
