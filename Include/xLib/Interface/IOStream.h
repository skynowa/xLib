/**
 * \file  IOStream.h
 * \brief ostream
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template <typename StreamT>
class IOStream
	/// ostream
{
public:
///\name ctors, dtor
///\{
			 IOStream() = default;
	virtual ~IOStream() = default;
///\}

	virtual StreamT &print(StreamT& os) const = 0;
		///< print

///\name operators
///\{
	friend StreamT& operator << (StreamT &a_os, const IOStream &a_ios)
	{
		return a_ios.print(a_os);
	}
///\}
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * Print any object which has a member:
 *
 * void T::print(StreamT &) const
 */
template<class StreamT, class ValueT>
auto
operator << (
	StreamT      &a_os,
	const ValueT &a_value
) -> decltype(a_value.print(a_os), a_os)
{
	a_value.print(a_os);

	return a_os;
}
//-------------------------------------------------------------------------------------------------
