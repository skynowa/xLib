/**
 * \file  Char.h
 * \brief character
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T>
class Char
    /// character
{
public:
///@name ctors, dtor
///@{
	explicit  Char(const T ch);
              Char(const T ch, const xTLOCALE &locale);
	virtual  ~Char() {}

	xNO_COPY_ASSIGN(Char)
///@}

    T               character() const;
        ///< get character
    const xTLOCALE& locale() const;
        ///< get locale

    bool_t          isAlphaNum() const;
        ///< Check is alphanumeric
    bool_t          isAlpha() const;
        ///< Check is alphabetic
    bool_t          isControl() const;
        ///< Check is a control ch
    bool_t          isDigitDec() const;
        ///< Check is decimal digit
    bool_t          isDigitHex() const;
        ///< Check is hexadecimal digit

    bool_t          isGraph() const;
        ///< Check has graphical representation
    bool_t          isPrint() const;
        ///< Check is printable
    bool_t          isPunct() const;
        ///< Check is a punctuation
    bool_t          isSpace() const;
        ///< Check is a white-space

    bool_t          isLower() const;
        ///< Check is lowercase letter
    bool_t          isUpper() const;
        ///< Check is uppercase letter

    T               toLower() const;
        ///< Convert to lowercase
    T               toUpper() const;
        ///< Convert to uppercase
    std::tstring_t  symbol();
        ///< char as symbol

private:
    const T         _char {};
    const xTLOCALE  _locale;
};

using CharA = Char<char>;
xUSING_CONST(CharA);

using CharW = Char<wchar_t>;
xUSING_CONST(CharW);

using CharU = Char<uchar_t>;
xUSING_CONST(CharU);

using CharT = Char<tchar_t>;
xUSING_CONST(CharT);

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Char.inl"
