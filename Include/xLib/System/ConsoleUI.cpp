/**
 * \file  ConsoleUI.cpp
 * \brief Shell console UI
 */


#include "ConsoleUI.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>

#if   xENV_WIN
	#include "Platform/Win/ConsoleUI_win.inl"
#elif xENV_UNIX
	#include "Platform/Unix/ConsoleUI_unix.inl"
#endif

namespace xl::system
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ConsoleUI::Result
ConsoleUI::msgBox(
	std::ctstring_t &a_title,
	std::ctstring_t &a_text
) const
{
	xTEST_NA(a_title);
	xTEST_NA(a_text);

	Result rRv {};

	std::csize_t width     {100};
	ctchar_t     cmdAbort  {xT('a')};
	ctchar_t     cmdIgnore {xT('i')};
	ctchar_t     cmdRetry  {xT('r')};

	std::ctstring_t title = _boxLine(a_title, width) + Const::nl();

	std::tstring_t multiText;
	{
		std::vec_tstring_t text;
		String::split(a_text, Const::nl(), &text);

		for (const auto &it : text) {
			multiText += _boxLine(it, width) + Const::nl();
		}
	}

	_console.writeNl();
	_console.writeLine(Format::str(xT("+{}+"), std::tstring_t(width - 2, xT('-'))));
	_console.writeLine(Format::str(xT("|{}|"), std::tstring_t(width - 2, xT(' '))));
	_console.write(title);
	_console.writeLine(Format::str(xT("|{}|"), std::tstring_t(width - 2, xT(' '))));
	_console.write(multiText);
	_console.writeLine(Format::str(xT("|{}|"), std::tstring_t(width - 2, xT(' '))));
	_console.writeLine(Format::str(xT("+{}+"), std::tstring_t(width - 2, xT('-'))));
	_console.writeNl();
	_console.write(Format::str(xT("\nAbort ({}), Ignore ({}), Retry ({}): "),
		cmdAbort, cmdIgnore, cmdRetry));

	const auto consoleCmd = CharT( static_cast<tchar_t>(std::tcin.get()) ).toLower().get();
	std::tcin.ignore();

	switch (consoleCmd) {
	case cmdAbort:
		rRv = Result::Abort;
		_console.writeLine(xT("Abort..."));
		break;
	case cmdIgnore:
		rRv = Result::Ignore;
		_console.writeLine(xT("Ignore..."));
		break;
	case cmdRetry:
		rRv = Result::Retry;
		_console.writeLine(xT("Retry..."));
		break;
	default:
		rRv = Result::Retry;
		_console.writeLine(xT("Retry..."));
		break;
	}

	return rRv;
}
//-------------------------------------------------------------------------------------------------
void_t
ConsoleUI::promptBox(
	std::ctstring_t &a_title,		///< title
	std::ctstring_t &a_text,		///< input text
	cbool_t          a_isVisible,	///< is input text visible
	std::tstring_t  *out_answer		///< [out] answer
) const
{
	xTEST_NA(a_title);
	xTEST_NA(a_text);
	xTEST_NA(a_isVisible);
	xTEST_PTR(out_answer);

	// Title
	_console.write(a_title);

	// Text
	_setStdinEcho(a_isVisible);

	ctchar_t keyEnter     {10};
	ctchar_t keyBackspace {0x8};

	for ( ; ; ) {
		_console.write(a_text + xT(": "));

		for ( ; ; ) {
			const auto ch = static_cast<tchar_t>( std::tcin.get() );
			xCHECK_DO(ch == keyEnter, break);
			xCHECK_DO(ch == keyBackspace, out_answer->clear(); continue);

			out_answer->push_back(ch);
		}

		_console.writeLine(Const::strEmpty());

		xCHECK_DO(out_answer->empty(), continue);

		break;
	}

	if ( !a_isVisible ) {
		_setStdinEcho(true);
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   ConsoleUI / private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
ConsoleUI::_boxLine(
	std::ctstring_t &a_text,	///< text
	std::csize_t     a_width	///< msgbox width
) const
{
	std::ctstring_t border      = xT("|");
	ctchar_t        space       = xT(' ');
	std::ctstring_t paddingLeft = border + space;
	std::ctstring_t padingRight = xT(" ") + border;
	std::ctstring_t dot3        = xT(" ...");

	std::tstring_t line = paddingLeft + a_text;

	auto delta = static_cast<std::ssize_t>(a_width - line.size());
	if (delta < 0) {
		line.resize(a_width - padingRight.size() - dot3.size());	// set padding
		line += dot3;
	} else {
		std::ctstring_t add(static_cast<std::size_t>(delta) - padingRight.size(), space);

		line += add;
	}

	line += padingRight;

	return line;
}
//-------------------------------------------------------------------------------------------------
void_t
ConsoleUI::_setStdinEcho(
	cbool_t a_isEnable
) const
{
	_setStdinEcho_impl(a_isEnable);
}
//-------------------------------------------------------------------------------------------------


} // namespace
