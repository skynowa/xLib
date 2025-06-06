/**
 * \file  Test_Trace.cpp
 * \brief test Trace
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Trace)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Trace::unit()
{
    xTEST_CASE("write(...)")
    {
    #if 0 || xTEST_IGNORE
        Trace log;
        log.critical(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        log.warning(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Warning), 12345);
        log.critical(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Critical), 12345);
        log.error(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Error), 12345);
        log.warning(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Warning), 12345);
        log.trace(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Trace), 12345);
        log.info(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Info), 12345);
        log.debug(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Debug), 12345);
        log.trace(xT("%s, %d"), xLEX_TO_STR(ILog::Level::Trace), 12345);
    #endif
    }

    xTEST_CASE("TraceStream")
    {
		std::ctstring_t str     = xT("test");
		int_t           integer = 777;

		LogTrace() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer);
		LogTraceTrace() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer);
		LogTraceDebug() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer);
		LogTraceError() << "EOL->" << std::endl;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
