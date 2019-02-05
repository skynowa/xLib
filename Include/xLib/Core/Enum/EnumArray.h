/**
 * \file   EnumArray.h
 * \brief  EnumArray
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T, const std::size_t N>
class EnumArray :
    public std::array<T, N>
    /// Enumeration container
{
public:
           EnumArray<T, N>(const std::array<T, N> &values);

    bool_t isValid(const ::ssize_t value) const;
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "EnumArray.inl"
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
std::tostream_t &
operator << (std::tostream_t &os, const typename xl::core::EnumArray<T, N> &values);
//-------------------------------------------------------------------------------------------------
