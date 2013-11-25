/**
 * \file   CxTest_CxTracer.cpp
 * \brief  test CxTracer
 */


#include <Test/Log/CxTest_CxTracer.h>

#include <xLib/Core/CxString.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxTracer::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxTracer::operator <<", a_caseLoops)
    {
    #if xTEST_IGNORE
        CxTracer trTracer;

        trTracer << xT("\tMsg: ") << 12345 << xT(' ') << CxConst::dot3();
    #endif
    }

    xTEST_CASE("CxTracer::operator <<", a_caseLoops)
    {
    #if xTEST_IGNORE
        CxTracer() << xT("\tMsg: ") << 12345 << xT(' ') << CxConst::dot3();
    #endif
    }

    xTEST_CASE("CxTracer::write", a_caseLoops)
    {
    #if xTEST_IGNORE
        CxTracer::write(xT("\t%s: %d"), "test_str", 12345);
    #endif
    }

    xTEST_CASE("CxTracer::write", a_caseLoops)
    {
    #if xTEST_IGNORE
        std::tstring_t sData = xT("\ttest_str");

        CxTracer::write(sData);
    #endif
    }

    xTEST_CASE("CxTracer::xTRACE_VAR_", a_caseLoops)
    {
    #if xTEST_IGNORE
        std::tstring_t sData  = xT("data1");
        ulong_t        ulData = 777UL;
        double         aData  = 4.4;
        ctchar_t *szData = xT("data2");

        CxTracer() << xT("\t")
                   << xTRACE_VAR(sData)
                   << xTRACE_VAR(ulData)
                   << xTRACE_VAR(aData)
                   << xTRACE_VAR(szData);
    #endif
    }
}
//------------------------------------------------------------------------------
