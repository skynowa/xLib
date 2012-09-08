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
    #if xTEST_IGNORE
        CxTracer trTracer;

        trTracer << xT("\tMsg: ") << 12345 << xT(' ') << CxConst::x3DOT;
    #endif
    }

    //--------------------------------------------------
    // operator <<
    xTEST_CASE(cullCaseLoops)
    {
    #if xTEST_IGNORE
        CxTracer() << xT("\tMsg: ") << 12345 << xT(' ') << CxConst::x3DOT;
    #endif
    }

    //--------------------------------------------------
    // bWrite(...)
    xTEST_CASE(cullCaseLoops)
    {
    #if xTEST_IGNORE
        CxTracer::vWrite(xT("\t%s: %d"), "test_str", 12345);
    #endif
    }

    //--------------------------------------------------
    // bWrite
    xTEST_CASE(cullCaseLoops)
    {
    #if xTEST_IGNORE
        std::tstring_t sData = xT("\ttest_str");

        CxTracer::vWrite(sData);
    #endif
    }

    //--------------------------------------------------
    // xTRACE_VAR
    xTEST_CASE(cullCaseLoops)
    {
    #if xTEST_IGNORE
        std::tstring_t sData  = xT("data1");
        ulong_t        ulData = 777UL;
        double         aData  = 4.4;
        const tchar_t *szData = xT("data2");

        CxTracer() << xT("\t")
                    << xTRACE_VAR(sData)
                    << xTRACE_VAR(ulData) 
                    << xTRACE_VAR(aData)
                    << xTRACE_VAR(szData);
    #endif
    }

    return true;
}
//---------------------------------------------------------------------------
