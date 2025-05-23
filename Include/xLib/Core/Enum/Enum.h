/**
 * \file   Enum.h
 * \brief  Enumeration
 *
 * \libs
 *
 * - http://www.yolinux.com/TUTORIALS/C++Enum.html\n
 * - https://www.reddit.com/r/cpp/comments/48l2yo/automatically_printing_enum_names/\n
 * - http://www.edm2.com/0405/enumeration.html\n
 * - https://docs.microsoft.com/en-us/dotnet/api/system.enum.getunderlyingtype?view=netframework-4.7.2\n
 * - https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Type_Safe_Enum\n
 * - https://github.com/shaovoon/EnumConvGen/blob/master/ParseEnum/ParseEnum/EnumStrConv.h
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
#include <xLib/Interface/IStr.h>
#include <xLib/Interface/IGet.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T>
class Enum :
	public IStr,
	public IGetValue<T>
    /// Enumeration
{
public:
	using value_type = T;

///\name ctors, dtor
///\{
	explicit Enum(const T value);
	explicit Enum(std::tstring_t value);
   ~Enum() = default;

	xNO_COPY_ASSIGN(Enum);
///\}

///\name Overrides
///\{
    T              get() const final;
	std::tstring_t str() const final;
///\}

    std::ssize_t   value() const;
    std::tstring_t name() const;
        ///< TODO: gen enum strs

    // operators
    Enum<T>        inc() const;
    Enum<T>        dec() const;

    // TODO: toPrintable
    // TODO: fromPrintable

private:
    const T _value {};

	template<typename EnumT>
	friend
	std::tostream_t &
	operator << (std::tostream_t &os, const Enum<EnumT> &value);
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Enum.inl"
//-------------------------------------------------------------------------------------------------
/**
 * \file Enum.h
 * \todo
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
