/**
 * \file   Enum.h
 * \brief  Enumeration
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Array.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T, const std::size_t N = 0>
class Enum :
    public Array<T, N>
    ///< Enumeration
{
public:
    Enum<T, N>();
    Enum<T, N>(const Array<T, N> &enumeration);

    static
    std::tstring_t toString(const T value);
    bool_t         isValid(const ssize_t value) const;

    // operators
    static
    T              inc(const T &value);
    static
    T              dec(const T &value);

    friend std::ostream & operator << (std::ostream &os, const T value);
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Enum.inl"
