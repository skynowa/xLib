/**
 * \file   Enum.h
 * \brief  Enumeration
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Array.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T, const std::size_t N>
class Enum :
    public Array<T, N>
    ///< Enumeration
{
public:
    std::tstring_t toString(const T value);
    // bool_t         isValid();

    // size_t         begin();
    // size_t         end();
    // size_t         size();

    // operators
    // iterators

    friend std::ostream & operator << (std::ostream &os, const T &value);

private:

};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Enum.inl"
