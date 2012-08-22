/**
 * \file   CxTest_CxTracer.cpp
 * \brief  test CxTracer
 */


#include <Test/Log/CxTest_CxTracer.h>


//---------------------------------------------------------------------------
CxTest_CxTracer::CxTest_CxTracer() {

}
//---------------------------------------------------------------------------
CxTest_CxTracer::~CxTest_CxTracer() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxTracer::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    // operator <<
    xTEST_CASE(cullCaseLoops)
    {
        CxTracer trTracer;

        trTracer << xT("\tMsg: ") << 12345 << xT(' ') << CxConst::x3DOT;
    }

    //--------------------------------------------------
    // operator <<
    xTEST_CASE(cullCaseLoops)
    {
        CxTracer() << xT("\tMsg: ") << 12345 << xT(' ') << CxConst::x3DOT;
    }

    //--------------------------------------------------
    // bWrite(...)
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxTracer::bWrite(xT("\t%s: %d"), "test_str", 12345);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    // bWrite
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sData = xT("\ttest_str");

        m_bRv = CxTracer::bWrite(sData);
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    // xTRACE_VAR
    xTEST_CASE(cullCaseLoops)
    {
        std::tstring_t sData  = xT("data1");
        ulong_t        ulData = 777UL;
        double         aData  = 4.4;
        const tchar_t *szData = xT("data2");

        CxTracer() << xT("\t")
                   << xTRACE_VAR(sData)
                   << xTRACE_VAR(ulData) 
                   << xTRACE_VAR(aData)
                   << xTRACE_VAR(szData);
    }

    return true;
}
//---------------------------------------------------------------------------
