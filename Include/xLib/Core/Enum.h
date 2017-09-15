/**
 * \file   Enum.h
 * \brief  Enumeration
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Array.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T>
class Enum
    ///< Enumeration
{
public:
    static
    std::tstring_t toString(const T value);
    static
    T              fromString(const std::tstring_t &value);
    static
    std::tstring_t asString(const T value);

    // operators
    static
    T              inc(const T &value);
    static
    T              dec(const T &value);

    // friend
    // std::ostream & operator << (std::ostream &os, const T value);

private:
    Enum<T>();
};
//-------------------------------------------------------------------------------------------------
template<typename T, const std::size_t N = 0>
class EnumContainer :
    public Array<T, N>
    ///< Enumeration container
{
public:
           EnumContainer<T, N>();
           EnumContainer<T, N>(const Array<T, N> &enumeration);

    bool_t isValid(const ssize_t value) const;
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Enum.inl"
#include "EnumContainer.inl"
