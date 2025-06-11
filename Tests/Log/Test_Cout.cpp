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
        log.trace(xT("%s-%d"), xT("Trace"), 12345);
        log.debug(xT("%s-%d"), xT("Debug"), 12345);
        log.info(xT("%s-%d"), xT("Info"), 12345);
        log.warning(xT("%s-%d"), xT("Warning"), 12345);
        log.error(xT("%s-%d"), xT("Error"), 12345);
        log.critical(xT("%s-%d"), xT("Critical"), 12345);
    #endif
    }

    xTEST_CASE("LogStream")
    {
		std::ctstring_t str     = xT("test");
		std::csize_t    integer = 777;

		LogCout() << str << "-" << integer;
		LogCoutTrace() << str << "-" << integer;
		LogCoutDebug() << str << "-" << integer;
		LogCoutInfo() << str << "-" << integer;
		LogCoutWarning() << str << "-" << integer;
		LogCoutError() << str << "-" << integer;
		LogCoutCritical() << str << "-" << integer << ", EOL->" << std::endl;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
