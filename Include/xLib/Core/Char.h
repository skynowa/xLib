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
    explicit        Char(const T &ch, const xTLOCALE &locale = xTLOCALE());
    virtual        ~Char() {}

    T               character() const;
        ///< get character
    const xTLOCALE& locale() const;
        ///< get locale

    bool_t          isAlphaNum() const;
        ///< Check if ch is alphanumeric
    bool_t          isAlpha() const;
        ///< Check if ch is alphabetic
    bool_t          isControl() const;
        ///< Check if ch is a control ch
    bool_t          isDigitDec() const;
        ///< Check if ch is decimal digit
    bool_t          isDigitHex() const;
        ///< Check if ch is hexadecimal digit

    bool_t          isGraph() const;
        ///< Check if ch has graphical representation
    bool_t          isPrint() const;
        ///< Check if ch is printable
    bool_t          isPunct() const;
        ///< Check if ch is a punctuation ch
    bool_t          isSpace() const;
        ///< Check if ch is a white-space

    bool_t          isLower() const;
        ///< Check if ch is lowercase letter
    bool_t          isUpper() const;
        ///< Check if ch is uppercase letter

    T               toLower() const;
        ///< Convert uppercase letter to lowercase
    T               toUpper() const;
        ///< Convert lowercase letter to uppercase
    std::tstring_t  symbol();
        ///< char as symbol

private:
    const T         _ch {};
    const xTLOCALE &_locale;

    xNO_COPY_ASSIGN(Char)
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
