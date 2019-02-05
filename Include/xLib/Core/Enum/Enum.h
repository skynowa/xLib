/**
 * \file   Enum.h
 * \brief  Enumeration
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class Enum
    /// Enumeration
{
public:
    template<typename T>
    static
    std::tstring_t toString(const T &value);

    template<typename T>
    static
    T              fromString(std::ctstring_t &value);

    template<typename T>
    static
    std::tstring_t asString(const T &value);

    // operators
    template<typename T>
    static
    T              inc(const T &value);

    template<typename T>
    static
    T              dec(const T &value);

private:
    xNO_INSTANCE(Enum)
    xNO_COPY_ASSIGN(Enum)
};

// template<typename T>
// std::tostream_t &
// operator << (std::tostream_t &os, const typename Enum<T>::value_type &value);

// template<typename T>
// xl::core::OStream &
// operator << (OStream &os, const T value);

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Enum.inl"


// https://www.reddit.com/r/cpp/comments/48l2yo/automatically_printing_enum_names/
