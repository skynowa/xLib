/**
 * \file   Enum.h
 * \brief  Enumeration
 *
 * http://www.yolinux.com/TUTORIALS/C++Enum.html
 * https://www.reddit.com/r/cpp/comments/48l2yo/automatically_printing_enum_names/
 * http://www.edm2.com/0405/enumeration.html
 * https://docs.microsoft.com/en-us/dotnet/api/system.enum.getunderlyingtype?view=netframework-4.7.2
 * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Type_Safe_Enum
 * https://github.com/shaovoon/EnumConvGen/blob/master/ParseEnum/ParseEnum/EnumStrConv.h
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

class Enum
    /// Enumeration
{
public:
    template<typename T>
    static
    std::tstring_t str(const T &value);

    template<typename T>
    static
    ::ssize_t      value(const T &value);

    template<typename T>
    static
    T              cast(std::ctstring_t &value);

    template<typename T>
    static
    std::tstring_t name(const T &value);

    // operators
    template<typename T>
    static
    T              inc(const T &value);

    template<typename T>
    static
    T              dec(const T &value);

    template<typename StreamT, typename T>
    static
    void_t         print(StreamT &os, const T &value);

    // TODO: toPrintable
    // TODO: fromPrintable

private:
    xNO_DEFAULT_CONSTRUCT(Enum)
    xNO_COPY_ASSIGN(Enum)
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Enum.inl"
//-------------------------------------------------------------------------------------------------
// template<typename T>
// std::tostream_t &
// operator << (std::tostream_t &os, const typename Enum<T>::value_type &value);

// template<typename T>
// xl::core::OStream &
// operator << (OStream &os, const T value);
//-------------------------------------------------------------------------------------------------
