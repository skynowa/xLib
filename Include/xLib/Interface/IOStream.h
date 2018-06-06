/**
 * \file  IOStream.h
 * \brief ostream interface
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

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

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
