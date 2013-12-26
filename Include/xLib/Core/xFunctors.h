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
xNAMESPACE2_BEGIN(NxLib, NxFunctors)

struct CompareNoCase
    ///< case insensitive comparison
{
    // TODO: bool_t
    bool
    operator () (
        const std::tstring_t::value_type &a_value1,
        const std::tstring_t::value_type &a_value2) const
    {
        return CxChar::toLower(a_value1) == CxChar::toLower(a_value2);
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

xNAMESPACE2_END(NxLib, NxFunctors)
//-------------------------------------------------------------------------------------------------
#endif // xLib_xFunctorsH
