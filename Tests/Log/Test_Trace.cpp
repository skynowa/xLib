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
        Trace().write(ILog::Level::Off,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Off),  12345);
        Trace().write(ILog::Level::Fatal,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Fatal),    12345);
        Trace().write(ILog::Level::Warning,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Warning),    12345);
        Trace().write(ILog::Level::Fatal, xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Fatal), 12345);
        Trace().write(ILog::Level::Error,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Error),    12345);
        Trace().write(ILog::Level::Warning,  xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Warning),  12345);
        Trace().write(ILog::Level::Trace,   xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Trace),   12345);
        Trace().write(ILog::Level::Info,     xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Info),     12345);
        Trace().write(ILog::Level::Debug,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Debug),    12345);
        Trace().write(ILog::Level::Trace,    xT("\t%s, %d"), xLEX_TO_STR(ILog::Level::Trace),    12345);
    #endif
    }

    xTEST_CASE("xTRACE_VAR")
    {
    #if xTEST_IGNORE
        std::tstring_t sData  = xT("data1");
        ulong_t        ulData = 777UL;
        double         aData  = 4.4;
        cptr_ctchar_t  szData = xT("data2");

        Trace()
			<< xT("\t")
			<< xTRACE_VAR(sData)
			<< xTRACE_VAR(ulData)
			<< xTRACE_VAR(aData)
			<< xTRACE_VAR(szData);
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
