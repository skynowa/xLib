/**
 * \file   Test_Trace.cpp
 * \brief  test Trace
 */


#include <Test/Log/Test_Trace.h>

#include <xLib/Core/String.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Trace::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Trace::operator <<", a_caseLoops)
    {
    #if xTEST_IGNORE
        Trace trace;

        trace << xT("\tMsg: ") << 12345 << xT(' ') << Const::dot3();
    #endif
    }

    xTEST_CASE("Trace::operator <<", a_caseLoops)
    {
    #if xTEST_IGNORE
        Trace() << xT("\tMsg: ") << 12345 << xT(' ') << Const::dot3();
    #endif
    }

    xTEST_CASE("Trace::write", a_caseLoops)
    {
    #if xTEST_IGNORE
        Trace::write(xT("\t%s: %d"), "test_str", 12345);
    #endif
    }

    xTEST_CASE("Trace::write(cExLevel &level, ...)", a_caseLoops)
    {
    #if xTEST_IGNORE
        Trace().write(IxLog::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvUnknown),  12345);
        Trace().write(IxLog::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvEmerg),    12345);
        Trace().write(IxLog::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvAlert),    12345);
        Trace().write(IxLog::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvCritical), 12345);
        Trace().write(IxLog::lvError,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvError),    12345);
        Trace().write(IxLog::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvWarning),  12345);
        Trace().write(IxLog::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvNotice),   12345);
        Trace().write(IxLog::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvInfo),     12345);
        Trace().write(IxLog::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvDebug),    12345);
        Trace().write(IxLog::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(IxLog::lvPlain),    12345);
    #endif
    }

    xTEST_CASE("Trace::xTRACE_VAR_", a_caseLoops)
    {
    #if xTEST_IGNORE
        std::tstring_t sData  = xT("data1");
        ulong_t        ulData = 777UL;
        double         aData  = 4.4;
        ctchar_t *     szData = xT("data2");

        Trace() << xT("\t")
                   << xTRACE_VAR(sData)
                   << xTRACE_VAR(ulData)
                   << xTRACE_VAR(aData)
                   << xTRACE_VAR(szData);
    #endif
    }
}
//-------------------------------------------------------------------------------------------------
