/**
 * \file  xFunctors.h
 * \brief functors
 */


#pragma once

#ifndef xLib_xFunctorsH
#define xLib_xFunctorsH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Core/CxChar.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, functors)
//-------------------------------------------------------------------------------------------------
struct ToLower
    ///< char to lower case
{
public:
    ToLower(const std::locale &a_loc = std::locale()) :
        _locale(a_loc)
    {
    }

    tchar_t
    operator () (
        std::ctstring_t::value_type &a_ch
    ) const
    {
        return xTTOLOWER(a_ch, _locale);
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
struct ToUpper
    ///< char to upper case
{
public:
    ToUpper(const std::locale &a_loc = std::locale()) :
        _locale(a_loc)
    {
    }

    tchar_t
    operator () (
        std::ctstring_t::value_type &a_ch
    ) const
    {
        return xTTOUPPER(a_ch, _locale);
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
struct CompareNoCase
    ///< case insensitive comparison
{
public:
    CompareNoCase(const std::locale &a_loc = std::locale()) :
        _locale(a_loc)
    {
    }

    bool_t
    operator () (
        const std::tstring_t::value_type &a_ch1,
        const std::tstring_t::value_type &a_ch2) const
    {
        return CxChar(a_ch1, _locale).toLower() == CxChar(a_ch2, _locale).toLower();
    }

    bool_t
    operator () (
        std::ctstring_t &a_value1,
        std::ctstring_t &a_value2) const
    {
        return CxString::compareNoCase(a_value1, a_value2);
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
struct Delete
    ///< container items deleter
{
    template<class T>
    void
    operator () (
        T* &a_ptr) const
    {
        xPTR_DELETE(a_ptr);
    }
};
//-------------------------------------------------------------------------------------------------
struct Narrow
    ///<
{
    std::string::value_type
    operator () (
        const std::wstring::value_type &a_char
    ) const
    {
        return std::use_facet< std::ctype<std::wstring::value_type> >( std::locale() )
                    .narrow(a_char, '@');
    }
};
//-------------------------------------------------------------------------------------------------
struct Widen
    ///<
{
    std::wstring::value_type
    operator () (
        const std::string::value_type &a_char
    ) const
    {
        return std::use_facet< std::ctype<std::string::value_type> >( std::locale() )
                    .widen(a_char);
    }
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_END(xlib, functors)
//-------------------------------------------------------------------------------------------------
#endif // xLib_xFunctorsH
