/**
 * \file   EnumArray.h
 * \brief  EnumArray
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T, const std::size_t N = 0>
class EnumArray :
    public std::array<T, N>
    /// Enumeration container
{
public:
           EnumArray<T, N>();
           EnumArray<T, N>(const std::array<T, N> &enums);

    bool_t isValid(const ::ssize_t value) const;
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "EnumArray.inl"
