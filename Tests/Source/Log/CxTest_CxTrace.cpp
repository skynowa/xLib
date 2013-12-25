/**
 * \file   CxTest_CxTrace.cpp
 * \brief  test CxTrace
 */


#include <Test/Log/CxTest_CxTrace.h>

#include <xLib/Core/CxString.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxTrace::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxTrace::operator <<", a_caseLoops)
    {
    #if xTEST_IGNORE
        CxTrace trace;

        trace << xT("\tMsg: ") << 12345 << xT(' ') << CxConst::dot3();
    #endif
    }

    xTEST_CASE("CxTrace::operator <<", a_caseLoops)
    {
    #if xTEST_IGNORE
        CxTrace() << xT("\tMsg: ") << 12345 << xT(' ') << CxConst::dot3();
    #endif
    }

    xTEST_CASE("CxTrace::write", a_caseLoops)
    {
    #if xTEST_IGNORE
        CxTrace::write(xT("\t%s: %d"), "test_str", 12345);
    #endif
    }

    xTEST_CASE("CxTrace::xTRACE_VAR_", a_caseLoops)
    {
    #if xTEST_IGNORE
        std::tstring_t sData  = xT("data1");
        ulong_t        ulData = 777UL;
        double         aData  = 4.4;
        ctchar_t *     szData = xT("data2");

        CxTrace() << xT("\t")
                   << xTRACE_VAR(sData)
                   << xTRACE_VAR(ulData)
                   << xTRACE_VAR(aData)
                   << xTRACE_VAR(szData);
    #endif
    }
}
//-------------------------------------------------------------------------------------------------
