/**
 * \file  Test_Cout.cpp
 * \brief test Cout
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Cout)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Cout::unit()
{
    xTEST_CASE("write(...)")
    {
    #if 1 || xTEST_IGNORE
        Cout log;
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

    xTEST_CASE("LogStream")
    {
		std::ctstring_t str     = xT("test");
		int_t           integer = 777;

		LogCout() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer);
		LogCoutTrace() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer);
		LogCoutDebug() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer);
		LogCoutInfo() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer);
		LogCoutWarning() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer);
		LogCoutError() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer);
		LogCoutCritical() << xTRACE_VAR(str) << ", " << xTRACE_VAR(integer) << ", EOL->" << std::endl;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
