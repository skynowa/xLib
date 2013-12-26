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

    xTEST_CASE("CxTrace::write(cExLevel &level, ...)", a_caseLoops)
    {
    #if xTEST_IGNORE
        CxTrace().write(IxLog::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvUnknown),  12345);
        CxTrace().write(IxLog::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvEmerg),    12345);
        CxTrace().write(IxLog::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvAlert),    12345);
        CxTrace().write(IxLog::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvCritical), 12345);
        CxTrace().write(IxLog::lvError,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvError),    12345);
        CxTrace().write(IxLog::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvWarning),  12345);
        CxTrace().write(IxLog::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvNotice),   12345);
        CxTrace().write(IxLog::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvInfo),     12345);
        CxTrace().write(IxLog::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvDebug),    12345);
        CxTrace().write(IxLog::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvPlain),    12345);
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
