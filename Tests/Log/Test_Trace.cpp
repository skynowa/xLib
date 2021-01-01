/**
 * \file   Test_Trace.cpp
 * \brief  test Trace
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Trace)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
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
        Trace().write(ILog::Level::lvUnknown,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvUnknown),  12345);
        Trace().write(ILog::Level::lvEmerg,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvEmerg),    12345);
        Trace().write(ILog::Level::lvAlert,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvAlert),    12345);
        Trace().write(ILog::Level::lvCritical, xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvCritical), 12345);
        Trace().write(ILog::Level::lvError,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvError),    12345);
        Trace().write(ILog::Level::lvWarning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvWarning),  12345);
        Trace().write(ILog::Level::lvNotice,   xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvNotice),   12345);
        Trace().write(ILog::Level::lvInfo,     xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvInfo),     12345);
        Trace().write(ILog::Level::lvDebug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvDebug),    12345);
        Trace().write(ILog::Level::lvPlain,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::lvPlain),    12345);
    #endif
    }

    xTEST_CASE("xTRACE_VAR")
    {
    #if xTEST_IGNORE
        std::tstring_t sData  = xT("data1");
        ulong_t        ulData = 777UL;
        double         aData  = 4.4;
        cptr_ctchar_t  szData = xT("data2");

        Trace() << xT("\t")
                   << xTRACE_VAR(sData)
                   << xTRACE_VAR(ulData)
                   << xTRACE_VAR(aData)
                   << xTRACE_VAR(szData);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
