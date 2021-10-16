/**
 * \file   EnumArray.h
 * \brief  EnumArray
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T, const std::size_t N>
class EnumArray :
    public std::array<T, N>
    /// Enumeration container
{
public:
           EnumArray<T, N>(const std::array<T, N> &values);

    bool_t isValid(const std::ssize_t value) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "EnumArray.inl"
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N>
std::tostream_t &
operator << (std::tostream_t &os, const typename xl::core::EnumArray<T, N> &values);
//-------------------------------------------------------------------------------------------------
