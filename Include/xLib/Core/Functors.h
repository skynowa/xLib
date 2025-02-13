/**
 * \file  Functors.h
 * \brief functors
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Char.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{
//-------------------------------------------------------------------------------------------------
class ToLower
    /// char to lower case
{
public:
    explicit ToLower(const xTLOCALE &a_locale) :
        _locale(a_locale)
    {
    }

    std::tstring_t::value_type operator () (std::ctstring_t::value_type &a_ch) const
    {
        return xTTOLOWER_L(a_ch, _locale);
    }

private:
    const xTLOCALE _locale;
};
//-------------------------------------------------------------------------------------------------
class ToUpper
    /// char, std:tstring_t to upper case
{
public:
    explicit ToUpper(const xTLOCALE &a_locale) :
        _locale(a_locale)
    {
    }

    std::tstring_t::value_type operator () (std::ctstring_t::value_type &a_ch) const
    {
        return xTTOUPPER_L(a_ch, _locale);
    }

private:
    const xTLOCALE _locale;
};
//-------------------------------------------------------------------------------------------------
class CompareCI
    /// case insensitive comparison
{
public:
    explicit CompareCI(const xTLOCALE &a_locale) :
        _locale(a_locale)
    {
    }

    bool_t operator () (
        const std::tstring_t::value_type a_ch1,
        const std::tstring_t::value_type a_ch2) const
    {
        cCharT ch1(a_ch1, _locale);
        cCharT ch2(a_ch2, _locale);

        return (ch1.toLower().get() == ch2.toLower().get());
    }

    bool_t operator () (
        std::ctstring_t &a_value1,
        std::ctstring_t &a_value2) const
    {
        return StringCI::compare(a_value1, a_value2);
    }

private:
    const xTLOCALE _locale;
};
//-------------------------------------------------------------------------------------------------
class Narrow
    /// convert to std::string
{
public:
    explicit Narrow(const xTLOCALE &a_locale) :
        _locale(a_locale)
    {
    }

    std::string::value_type operator () (const std::wstring::value_type a_ch) const
    {
        return std::use_facet< std::ctype<std::wstring::value_type> >(_locale).narrow(a_ch, '@');
    }

private:
    const xTLOCALE _locale;
};
//-------------------------------------------------------------------------------------------------
class Widen
    /// convert to std::wstring
{
public:
    explicit Widen(const xTLOCALE &a_locale) :
        _locale(a_locale)
    {
    }

    std::wstring::value_type operator () (const std::string::value_type a_ch) const
    {
        return std::use_facet< std::ctype<std::string::value_type> >(_locale).widen(a_ch);
    }

private:
    const xTLOCALE _locale;
};
//-------------------------------------------------------------------------------------------------
} // namespace
