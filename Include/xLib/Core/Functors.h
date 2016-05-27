/**
 * \file  Functors.h
 * \brief functors
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Char.h>
#include <xLib/Core/Utils.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)
//-------------------------------------------------------------------------------------------------
struct ToLower
    /// char to lower case
{
    explicit ToLower(const xTLOCALE &a_locale) :
        _locale(a_locale)
    {
    }

    tchar_t operator () (std::ctstring_t::value_type &a_ch) const
    {
        return xTTOLOWER_L(a_ch, _locale);
    }

private:
    const xTLOCALE &_locale;
};
//-------------------------------------------------------------------------------------------------
struct ToUpper
    /// char, std:tstring_t to upper case
{
    explicit ToUpper(const xTLOCALE &a_locale) :
        _locale(a_locale)
    {
    }

    tchar_t operator () (std::ctstring_t::value_type &a_ch) const
    {
        return xTTOUPPER_L(a_ch, _locale);
    }

private:
    const xTLOCALE &_locale;
};
//-------------------------------------------------------------------------------------------------
struct CompareCI
    /// case insensitive comparison
{
    explicit CompareCI(const xTLOCALE &a_locale) :
        _locale(a_locale)
    {
    }

    bool_t operator () (
        const std::tstring_t::value_type &a_ch1, const std::tstring_t::value_type &a_ch2) const
    {
        return Char(a_ch1, _locale).toLower() == Char(a_ch2, _locale).toLower();
    }

    bool_t operator () (
        std::ctstring_t &a_value1,
        std::ctstring_t &a_value2) const
    {
        return StringCI::compare(a_value1, a_value2);
    }

private:
    const xTLOCALE &_locale;
};
//-------------------------------------------------------------------------------------------------
struct Delete
    /// container items deleter
{
    template<class T>
    void_t operator () (T* &a_ptr) const
    {
        xPTR_DELETE(a_ptr);
    }
};
//-------------------------------------------------------------------------------------------------
struct Narrow
    ///
{
    explicit Narrow(const std::locale &a_locale) :
        _locale(a_locale)
    {
    }

    std::string::value_type operator () (const std::wstring::value_type &a_ch) const
    {
        return std::use_facet< std::ctype<std::wstring::value_type> >(_locale).narrow(a_ch, '@');
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
struct Widen
    ///
{
    explicit Widen(const std::locale &a_locale) :
        _locale(a_locale)
    {
    }

    std::wstring::value_type operator () (const std::string::value_type &a_ch) const
    {
        return std::use_facet< std::ctype<std::string::value_type> >(_locale).widen(a_ch);
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xlib, core)
