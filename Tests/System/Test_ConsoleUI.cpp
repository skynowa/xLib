/**
 * \file   Test_ConsoleUI.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_ConsoleUI)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Console::unit()
{
    xTEST_CASE("msgBox")
    {
	#if xTEST_IGNORE
		std::ctstring_t title = xT("iMsgBox_title");
		std::ctstring_t text  = xT("iMsgBox_text\nddddddddd\nRRRRRRRRRRRRR")
			xT(" AAAA BBBB CCCC DDDD EEEE FFFF GGGG HHHH JJJJ KKKK LLLL ZZZZ XXXX CCCC VVVV BBBB");
		cuint_t         type  = 0U;

		Console console;

		Console::Result mrRes = console.msgBox(title, text, type);
		xUNUSED(mrRes);
    #else
        Trace() << xT("[skip]");
	#endif
    }

    xTEST_CASE("promptBox")
    {
	#if xTEST_IGNORE
		std::ctstring_t title     = xT("Prompt_title");
		std::ctstring_t text      = xT("Prompt_simple_prompt");
		cbool_t         isVisible = false;
		std::tstring_t  answer    = xT("Answer_bla-bla-bla");

		Console console;

		console.promptBox(title, text, isVisible, &answer);
    #else
        Trace() << xT("[skip]");
	#endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
