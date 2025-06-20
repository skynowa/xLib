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
Test_ConsoleUI::unit()
{
	ConsoleUI ui;

	xTEST_CASE("msgBox")
	{
	#if xTEST_IGNORE
		std::ctstring_t title = xT("iMsgBox_title");
		std::ctstring_t text  = xT("iMsgBox_text\nddddddddd\nRRRRRRRRRRRRR")
			xT(" AAAA BBBB CCCC DDDD EEEE FFFF GGGG HHHH JJJJ KKKK LLLL ZZZZ XXXX CCCC VVVV BBBB");
		ConsoleUI::cResult rRes = ui.msgBox(title, text);
		xUNUSED(rRes);
	#else
		LogCout() << xT("[skip]");
	#endif
	}

	xTEST_CASE("promptBox")
	{
	#if xTEST_IGNORE
		std::ctstring_t title     = xT("Prompt_title");
		std::ctstring_t text      = xT("Prompt_simple_prompt");
		cbool_t         isVisible = false;
		std::tstring_t  answer    = xT("Answer_bla-bla-bla");

		ui.promptBox(title, text, isVisible, &answer);
	#else
		LogCout() << xT("[skip]");
	#endif
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
