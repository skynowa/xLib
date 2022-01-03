/**
 * \file  IPrint.h
 * \brief Printable
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template <typename StreamT>
class xNO_VTABLE IPrint
    /// Printable
{
public:
///\name ctors, dtor
///\{
			 IPrint() = default;
	virtual ~IPrint() = default;
///\}

    virtual void_t print(StreamT &) const = 0;
};

} // namespace
//-------------------------------------------------------------------------------------------------
