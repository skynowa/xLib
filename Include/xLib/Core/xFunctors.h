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
    CompareNoCase(const std::locale &a_loc = std::locale()) :
        _loc(a_loc)
    {
    }

    bool_t
    operator () (
        const std::tstring_t::value_type &a_value1,
        const std::tstring_t::value_type &a_value2) const
    {
    #if 1
        return CxChar::toLower(a_value1, _loc) == CxChar::toLower(a_value2, _loc);
    #else
        return std::tolower(a_value1, _loc) == std::toupper(a_value2, _loc);
    #endif
    }

    bool_t
    operator () (
        std::ctstring_t &a_value1,
        std::ctstring_t &a_value2) const
    {
        return CxString::compareNoCase(a_value1, a_value2);
    }

private:
    const std::locale &_loc;
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
