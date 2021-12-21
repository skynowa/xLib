/**
 * \file  Const.h
 * \brief Constants
 *
 * \see https://www.ascii-code.com/
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

/**
 * Method's postfix:
 * - "A" - ansi
 * - "W" - unicode
 * - Without - ansi or unicode depends on configs (\see Macro xUNICODE)
 */
class Const
    /// Constants
{
public:
///@name ctors, dtor
///@{
	xNO_DEFAULT_CONSTRUCT(Const)
	xNO_COPY_ASSIGN(Const)
///@}

	// strEmpty (empty string)
	static std::cstring_t &  strEmptyA();
	static std::cwstring_t & strEmptyW();
	static std::ctstring_t & strEmpty();

	// cr (carriage return)
	static std::cstring_t &  crA();
	static std::cwstring_t & crW();
	static std::ctstring_t & cr();

	// nl (newline)
	static std::cstring_t &  nlA();
	static std::cwstring_t & nlW();
	static std::ctstring_t & nl();

	// crNl (carriage return + newline)
	static std::cstring_t &  crNlA();
	static std::cwstring_t & crNlW();
	static std::ctstring_t & crNl();

	// colon (colon)
	static std::cstring_t &  colonA();
	static std::cwstring_t & colonW();
	static std::ctstring_t & colon();

	// winSlash (windows backslash)
	static std::cstring_t &  winSlashA();
	static std::cwstring_t & winSlashW();
	static std::ctstring_t & winSlash();

	// unixSlash (Unix backslash)
	static std::cstring_t &  unixSlashA();
	static std::cwstring_t & unixSlashW();
	static std::ctstring_t & unixSlash();

	// slash (backslash for specific OS)
	static std::cstring_t &  slashA();
	static std::cwstring_t & slashW();
	static std::ctstring_t & slash();

	// eol (end of line)
	static std::cstring_t &  eolA();
	static std::cwstring_t & eolW();
	static std::ctstring_t & eol();

	// semicolon (path separator)
	static std::cstring_t &  semicolonA();
	static std::cwstring_t & semicolonW();
	static std::ctstring_t & semicolon();

	// dot (1 dot)
	static std::cstring_t &  dotA();
	static std::cwstring_t & dotW();
	static std::ctstring_t & dot();

	// dot2 (2 dots)
	static std::cstring_t &  dot2A();
	static std::cwstring_t & dot2W();
	static std::ctstring_t & dot2();

	// dot3 (3 dots)
	static std::cstring_t &  dot3A();
	static std::cwstring_t & dot3W();
	static std::ctstring_t & dot3();

	// maskAll (all files mask)
	static std::cstring_t &  maskAllA();
	static std::cwstring_t & maskAllW();
	static std::ctstring_t & maskAll();

	// ht (horizontal tab)
	static std::cstring_t &  htA();
	static std::cwstring_t & htW();
	static std::ctstring_t & ht();

	// vt
	static std::cstring_t &  vtA();
	static std::cwstring_t & vtW();
	static std::ctstring_t & vt();

	// space (space)
	static std::cstring_t &  spaceA();
	static std::cwstring_t & spaceW();
	static std::ctstring_t & space();

	// bell (alert)
	static std::cstring_t &  bellA();
	static std::cwstring_t & bellW();
	static std::ctstring_t & bell();

	// bs (backspace)
	static std::cstring_t &  bsA();
	static std::cwstring_t & bsW();
	static std::ctstring_t & bs();

	// ff (formfeed)
	static std::cstring_t &  ffA();
	static std::cwstring_t & ffW();
	static std::ctstring_t & ff();

	// qm (question mark)
	static std::cstring_t &  qmA();
	static std::cwstring_t & qmW();
	static std::ctstring_t & qm();

	// sqm (single quotation mark)
	static std::cstring_t &  sqmA();
	static std::cwstring_t & sqmW();
	static std::ctstring_t & sqm();

	// dqm (double quotation mark)
	static std::cstring_t &  dqmA();
	static std::cwstring_t & dqmW();
	static std::ctstring_t & dqm();

	// ga (Grave accent)
	static std::cstring_t &  gaA();
	static std::cwstring_t & gaW();
	static std::ctstring_t & ga();

	// whiteSpaces (white spaces)
	static std::cstring_t &  whiteSpacesA();
	static std::cwstring_t & whiteSpacesW();
	static std::ctstring_t & whiteSpaces();

	// equal (equal sign)
	static std::cstring_t &  equalA();
	static std::cwstring_t & equalW();
	static std::ctstring_t & equal();

	// hyphen (hyphen)
	static std::cstring_t &  hyphenA();
	static std::cwstring_t & hyphenW();
	static std::ctstring_t & hyphen();

	// strUnknown (unknown string value)
	static std::cstring_t &  strUnknownA();
	static std::cwstring_t & strUnknownW();
	static std::ctstring_t & strUnknown();
};

} // namespace
//-------------------------------------------------------------------------------------------------
