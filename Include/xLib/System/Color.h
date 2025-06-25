/**
 * \file  Color.h
 * \brief Shell console color
 *
 * \libs
 *
 * - https://github.com/ikalnytskyi/termcolor/blob/master/include/termcolor/termcolor.hpp
 * - https://github.com/yurablok/colored-cout/blob/master/colored_cout.h
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system
{

//-------------------------------------------------------------------------------------------------
class Color
	/// Shell console color
{
public:
	enum class FG
		/// foreground (text) color
	{
		Unknown  = 0,
		Default  = 1,
		Black    = 2,
		Red      = 3,
		Green    = 4,
		Yellow   = 5,
		Blue     = 6,
		Magenta  = 7,
		Cyan     = 8,
		White    = 9,
		Gray     = 10
    };
    xUSING_CONST(FG);

	enum class BG
		/// background color
	{
		Unknown  = 0,
		Default  = 1,
		Black    = 2,
		Red      = 3,
		Green    = 4,
		Yellow   = 5,
		Blue     = 6,
		Magenta  = 7,
		Cyan     = 8,
		White    = 9,
		Gray     = 10
    };
    xUSING_CONST(BG);

	enum class Attr
		/// text attribute
	{
		Unknown    = 0,      ///< Unknown
		AllOff     = 1 << 0, ///< Reset all attributes
		Bold       = 1 << 1, ///< Bold/Bright
		Dim        = 1 << 2, ///< Dim
		Underline  = 1 << 3, ///< Underlined
		Blink      = 1 << 4, ///< Blink (not work with most of the terminal emulators)
		Reverse    = 1 << 5, ///< Invert the foreground and background colors
		Hidden     = 1 << 6  ///< Hidden (useful for passwords)
	};
	xUSING_CONST(Attr);

///\name ctors, dtor
///\{
	constexpr Color(
		cbool_t a_isColorSupport, ///< force set color support (for PS1, etc)
		cbool_t a_isEscapeValues  ///< escaping values (UNIX only)
	) :
		Color(a_isColorSupport, a_isEscapeValues, FG::Default, BG::Default, Attr::AllOff)
	{
	};

	constexpr Color(
		cbool_t a_isColorSupport, ///< force set color support (for PS1, etc)
		cbool_t a_isEscapeValues, ///< escaping values (UNIX only)
		cFG     a_fg,             ///< foreground color
		cBG     a_bg,             ///< background color
		cAttr   a_attrs           ///< text attributes
	) :
		_isColorSupport{a_isColorSupport},
		_isEscapeValues{a_isEscapeValues},
		_fg            {a_fg},
		_bg            {a_bg},
		_attrs         {a_attrs}
	{
	}
   ~Color() = default;

	xNO_DEFAULT_CONSTRUCT(Color);
	xNO_COPY_ASSIGN(Color);
///\}

	std::tstring_t set() const;
		///< set text color
	std::tstring_t clear() const;
		///< reset text color to default
#if xENV_UNIX
	std::tstring_t setText(std::ctstring_t &str) const;
		///< set text color, text, reset text color to default
#endif
	std::tstring_t escape(std::ctstring_t &str) const;
		///< escape by "\[...\]"

private:
    cbool_t _isColorSupport {};
		///< Say whether a given stream should be colorized or not
	cbool_t _isEscapeValues {};
		///< escaping values

	cFG   _fg    {FG::Default};
	cBG   _bg    {BG::Default};
	cAttr _attrs {Attr::AllOff};

	std::tstring_t _set_impl(cFG fg, cBG bg, cAttr attrs) const;
	std::tstring_t _clear_impl() const;

    FILE  *        _getStdStream(std::ctostream_t &stream) const;
		///< Since C++ hasn't a true way to extract stream handler from the a given `std::ostream`
    bool_t         _isColorized(std::tostream_t &stream = std::tcout) const;
		///< Say whether a given stream should be colorized or not.
		///< It's always true for ATTY streams and may be true for streams marked with colorize flag
    bool_t         _isAtty(std::ctostream_t &stream) const;
        ///< Test whether a given `std::ostream` object refers to a terminal
};

} // namespace
//-------------------------------------------------------------------------------------------------
