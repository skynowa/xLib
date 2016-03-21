/**
 * \file   Test_Trace.cpp
 * \brief  test Trace
 */


#include <Test/Log/Test_Trace.h>

#include <xLib/Core/String.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Trace)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Trace::unit()
{
    xTEST_CASE("operator <<")
    {
    #if xTEST_IGNORE
        Trace trace;

        trace << xT("\tMsg: ") << 12345 << xT(' ') << Const::dot3();
    #endif
    }

    xTEST_CASE("operator <<")
    {
    #if xTEST_IGNORE
        Trace() << xT("\tMsg: ") << 12345 << xT(' ') << Const::dot3();
    #endif
    }

    xTEST_CASE("write")
    {
    #if xTEST_IGNORE
        Trace::write(xT("\t%s: %d"), "test_str", 12345);
    #endif
    }

    xTEST_CASE("write(...)")
    {
    #if xTEST_IGNORE
        Trace().write(ILog::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(ILog::lvUnknown),  12345);
        Trace().write(ILog::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvEmerg),    12345);
        Trace().write(ILog::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvAlert),    12345);
        Trace().write(ILog::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(ILog::lvCritical), 12345);
        Trace().write(ILog::lvError,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvError),    12345);
        Trace().write(ILog::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::lvWarning),  12345);
        Trace().write(ILog::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(ILog::lvNotice),   12345);
        Trace().write(ILog::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(ILog::lvInfo),     12345);
        Trace().write(ILog::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvDebug),    12345);
        Trace().write(ILog::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(ILog::lvPlain),    12345);
    #endif
    }

    xTEST_CASE("xTRACE_VAR")
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
