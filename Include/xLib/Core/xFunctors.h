/**
 * \file  xFunctors.h
 * \brief functors
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxChar.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN3(xlib, core, functors)
//-------------------------------------------------------------------------------------------------
struct ToLower
    /// char to lower case
{
    ToLower(const std::locale &a_locale) :
        _locale(a_locale)
    {
    }

    tchar_t
    operator () (std::ctstring_t::value_type &a_ch) const
    {
        return xTTOLOWER(a_ch, _locale);
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
struct ToUpper
    /// char, std:tstring_t to upper case
{
    ToUpper(const std::locale &a_locale) :
        _locale(a_locale)
    {
    }

    tchar_t
    operator () (std::ctstring_t::value_type &a_ch) const
    {
        return xTTOUPPER(a_ch, _locale);
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
struct CompareCI
    /// case insensitive comparison
{
    CompareCI(const std::locale &a_locale) :
        _locale(a_locale)
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
        return CxStringCI::compare(a_value1, a_value2);
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
struct Delete
    /// container items deleter
{
    template<class T>
    void
    operator () (T* &a_ptr) const
    {
        xPTR_DELETE(a_ptr);
    }
};
//-------------------------------------------------------------------------------------------------
struct Narrow
    ///
{
    Narrow(const std::locale &a_locale) :
        _locale(a_locale)
    {
    }

    std::string::value_type
    operator () (const std::wstring::value_type &a_ch) const
    {
        return std::use_facet< std::ctype<std::wstring::value_type> >( _locale ).narrow(a_ch, '@');
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
struct Widen
    ///
{
    Widen(const std::locale &a_locale) :
        _locale(a_locale)
    {
    }

    std::wstring::value_type
    operator () (const std::string::value_type &a_ch) const
    {
        return std::use_facet< std::ctype<std::string::value_type> >( _locale ).widen(a_ch);
    }

private:
    const std::locale &_locale;
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END3(xlib, core, functors)
