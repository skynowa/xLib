/**
 * \file  xFunctors.h
 * \brief functors
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxChar.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

struct SCompareNoCase
    ///< case insensitive comparison
{
    // TODO: bool_t
    bool
    operator () (
        const std::tstring_t::value_type &a_value1,
        const std::tstring_t::value_type &a_value2) const
    {
        return CxChar::toUpper(a_value1) == CxChar::toUpper(a_value2);
    }

    // TODO: bool_t
    bool
    operator () (
        std::ctstring_t &a_value1,
        std::ctstring_t &a_value2) const
    {
        return CxString::compareNoCase(a_value1, a_value2);
    }
};

struct SDelete
    ///< container items deleter
{
    template<class T>
    void
    operator () (
        T* &a_ptr) const
    {
        T* tmp = NULL;
        std::swap(a_ptr, tmp);

        delete tmp; tmp = NULL;
    }
};

struct SNarrow
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

struct SWiden
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

xNAMESPACE_ANONYM_END
//------------------------------------------------------------------------------
