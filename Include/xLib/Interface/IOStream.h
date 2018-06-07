/**
 * \file  IOStream.h
 * \brief ostream interface
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, interface)

template <typename BaseT>
class xNO_VTABLE IOStream :
	public BaseT
	/// ostream interface
{
public:
	virtual std::tostream_t &print(std::tostream_t& os) const = 0;
		///<
	friend std::tostream_t& operator << (std::tostream_t &a_os, const IOStream &a_ios)
	{
		return a_ios.print(a_os);
	}
		///<
};

xNAMESPACE_END2(xl, interface)
//-------------------------------------------------------------------------------------------------
#if xLANG_CPP11

/**
 * Print any object which has a member:
 *
 * void T::print(std::tostream_t&) const;
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

#endif
//-------------------------------------------------------------------------------------------------
