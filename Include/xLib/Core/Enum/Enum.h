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

template<typename T>
class Enum
    /// Enumeration
{
public:
///@name ctors, dtor
///@{
	Enum(const T value);
	Enum(std::tstring_t a_value);
   ~Enum() = default;

	xNO_COPY_ASSIGN(Enum)
///@}

    T              get() const;
    std::tstring_t str() const;
    ::ssize_t      value() const;
    std::tstring_t name() const;

    // operators
    Enum<T>        inc() const;
    Enum<T>        dec() const;

    // TODO: toPrintable
    // TODO: fromPrintable

private:
    const T _value {};
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Enum.inl"
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - begin(), end()
 *
 * - template<typename T>
 *   std::tostream_t &
 *   operator << (std::tostream_t &os, const typename Enum<T>::value_type &value);
 *
 * - template<typename T>
 *   xl::core::OStream &
 *   operator << (OStream &os, const T value);
 */
//-------------------------------------------------------------------------------------------------
