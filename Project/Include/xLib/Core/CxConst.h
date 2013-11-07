/**
 * \file  CxConst.h
 * \brief constants
 */


#include <xLib/Core/xCore.h>

#pragma once

//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxConst
    /// constants
{
public:
    // strEmpty
    static std::cstring_t &  strEmptyA();
        ///< empty string (ansi)
    static std::cwstring_t & strEmptyW();
        ///< empty string (unicode)
    static std::ctstring_t & strEmpty();
        ///< empty string (ansi or unicode)

    // cr
    static std::cstring_t &  crA();
        ///< carriage return (ansi)
    static std::cwstring_t & crW();
        ///< carriage return (unicode)
    static std::ctstring_t & cr();
        ///< carriage return (ansi or unicode)

    // nl
    static std::cstring_t &  nlA();
        ///< newline (ansi)
    static std::cwstring_t & nlW();
        ///< newline (unicode)
    static std::ctstring_t & nl();
        ///< newline (ansi or unicode)

    // crNl
    static std::cstring_t &  crNlA();
        ///< carriage return + newline (ansi)
    static std::cwstring_t & crNlW();
        ///< carriage return + newline (unicode)
    static std::ctstring_t & crNl();
        ///< carriage return + newline (ansi or unicode)

    // colon
    static std::cstring_t &  colonA();
        ///< colon (ansi)
    static std::cwstring_t & colonW();
        ///< colon (unicode)
    static std::ctstring_t & colon();
        ///< colon (ansi or unicode)

    // winSlash
    static std::cstring_t &  winSlashA();
        ///< windows backslash (ansi)
    static std::cwstring_t & winSlashW();
        ///< windows backslash (unicode)
    static std::ctstring_t & winSlash();
        ///< windows backslash (ansi or unicode)

    // unixSlash
    static std::cstring_t &  unixSlashA();
        ///< nix backslash (ansi)
    static std::cwstring_t & unixSlashW();
        ///< nix backslash (unicode)
    static std::ctstring_t & unixSlash();
        ///< nix backslash (ansi or unicode)

    // slash
    static std::cstring_t &  slashA();
        ///< backslash for specific OS (ansi)
    static std::cwstring_t & slashW();
        ///< backslash for specific OS (unicode)
    static std::ctstring_t & slash();
        ///< backslash for specific OS (ansi or unicode)

    // eol
    static std::cstring_t &  eolA();
        ///< end of line (ansi)
    static std::cwstring_t & eolW();
        ///< end of line (unicode)
    static std::ctstring_t & eol();
        ///< end of line (ansi or unicode)

    // semicolon
    static std::cstring_t &  semicolonA();
        ///< path separator (ansi)
    static std::cwstring_t & semicolonW();
        ///< path separator (unicode)
    static std::ctstring_t & semicolon();
        ///< path separator (ansi or unicode)

    // dot
    static std::cstring_t &  dotA();
        ///< 1 dot (ansi)
    static std::cwstring_t & dotW();
        ///< 1 dot (unicode)
    static std::ctstring_t & dot();
        ///< 1 dot (ansi or unicode)

    // dot2
    static std::cstring_t &  dot2A();
        ///< 2 dots (ansi)
    static std::cwstring_t & dot2W();
        ///< 2 dots (unicode)
    static std::ctstring_t & dot2();
        ///< 2 dots

    // dot3
    static std::cstring_t &  dot3A();
        ///< 3 dots (ansi)
    static std::cwstring_t & dot3W();
        ///< 3 dots (unicode)
    static std::ctstring_t & dot3();
        ///< 3 dots (ansi or unicode)

    // maskAll
    static std::cstring_t &  maskAllA();
        ///< all files mask (ansi)
    static std::cwstring_t & maskAllW();
        ///< all files mask (unicode)
    static std::ctstring_t & maskAll();
        ///< all files mask (ansi or unicode)

    // ht
    static std::cstring_t &  htA();
        ///< horizontal tab (ansi)
    static std::cwstring_t & htW();
        ///< horizontal tab (unicode)
    static std::ctstring_t & ht();
        ///< horizontal tab (ansi or unicode)

    // vt
    static std::cstring_t &  vtA();
        ///< vertical tab (ansi)
    static std::cwstring_t & vtW();
        ///< vertical tab (unicode)
    static std::ctstring_t & vt();
        ///< vertical tab (ansi or unicode)

    // space
    static std::cstring_t &  spaceA();
        ///< space (ansi)
    static std::cwstring_t & spaceW();
        ///< space (unicode)
    static std::ctstring_t & space();
        ///< space (ansi or unicode)

    // bell
    static std::cstring_t &  bellA();
        ///< alert (ansi)
    static std::cwstring_t & bellW();
        ///< alert (unicode)
    static std::ctstring_t & bell();
        ///< alert (ansi or unicode)

    // bs
    static std::cstring_t &  bsA();
        ///< backspace (ansi)
    static std::cwstring_t & bsW();
        ///< backspace (unicode)
    static std::ctstring_t & bs();
        ///< backspace (ansi or unicode)

    // ff
    static std::cstring_t &  ffA();
        ///< formfeed (ansi)
    static std::cwstring_t & ffW();
        ///< formfeed (unicode)
    static std::ctstring_t & ff();
        ///< formfeed (ansi or unicode)

    // qm
    static std::cstring_t &  qmA();
        ///< question mark (ansi)
    static std::cwstring_t & qmW();
        ///< question mark (unicode)
    static std::ctstring_t & qm();
        ///< question mark (ansi or unicode)

    // sqm
    static std::cstring_t &  sqmA();
        ///< single quotation mark (ansi)
    static std::cwstring_t & sqmW();
        ///< single quotation mark (unicode)
    static std::ctstring_t & sqm();
        ///< single quotation mark (ansi or unicode)

    // dqm
    static std::cstring_t &  dqmA();
        ///< double quotation mark (ansi)
    static std::cwstring_t & dqmW();
        ///< double quotation mark (unicode)
    static std::ctstring_t & dqm();
        ///< double quotation mark (ansi or unicode)

    // whiteSpaces
    static std::cstring_t &  whiteSpacesA();
        ///< white spaces (ansi)
    static std::cwstring_t & whiteSpacesW();
        ///< white spaces (unicode)
    static std::ctstring_t & whiteSpaces();
        ///< white spaces (ansi or unicode)

    // equal
    static std::cstring_t &  equalA();
        ///< equal sign (ansi)
    static std::cwstring_t & equalW();
        ///< equal sign (unicode)
    static std::ctstring_t & equal();
        ///< equal sign (ansi or unicode)

    // hyphen
    static std::cstring_t &  hyphenA();
        ///< hyphen (ansi)
    static std::cwstring_t & hyphenW();
        ///< hyphen (unicode)
    static std::ctstring_t & hyphen();
        ///< hyphen (ansi or unicode)

    // strUnknown
    static std::cstring_t &  strUnknownA();
        ///< unknown string value (ansi)
    static std::cwstring_t & strUnknownW();
        ///< unknown string value (unicode)
    static std::ctstring_t & strUnknown();
        ///< unknown string value (ansi or unicode)

private:
             CxConst();
    virtual ~CxConst();
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Core/CxConst.cpp>
#endif
