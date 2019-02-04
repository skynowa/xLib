/**
 * \file   Enum.h
 * \brief  Enumeration
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T>
class Enum
    /// Enumeration
{
public:
    static
    std::tstring_t toString(const T value);
    static
    T              fromString(std::ctstring_t &value);
    static
    std::tstring_t asString(const T value);

    // operators
    static
    T              inc(const T &value);
    static
    T              dec(const T &value);

private:
    xNO_INSTANCE(Enum<T>)
    xNO_COPY_ASSIGN(Enum<T>)
};

// template<typename T>
// std::tostream_t &
// operator << (std::tostream_t &os, const T value);

template<typename T>
xl::core::OStream &
operator << (OStream &os, const T value);

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Enum.inl"
