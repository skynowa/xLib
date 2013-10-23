/**
 * \file  xFunctors.h
 * \brief functors
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

struct SCompareNoCase
{
    // TODO: bool_t
    bool
    operator () (
        const std::tstring_t::value_type &a_value1,
        const std::tstring_t::value_type &a_value2
    )  const
    {
        return CxChar::toUpper(a_value1) == CxChar::toUpper(a_value2);
    }

    // TODO: bool_t
    bool
    operator() (std::ctstring_t &a_value1, std::ctstring_t &a_value2) const
    {
        return CxString::compareNoCase(a_value1, a_value2);
    }
};

xNAMESPACE_ANONYM_END
//------------------------------------------------------------------------------
