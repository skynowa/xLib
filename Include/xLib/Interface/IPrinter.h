/**
 * \file  IPrinter.h
 * \brief Printable
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template <typename StreamT>
class xNO_VTABLE IPrinter
    /// Printable
{
public:
///\name ctors, dtor
///\{
			 IPrinter() = default;
	virtual ~IPrinter() = default;
///\}

    virtual void_t print(StreamT &) const = 0;
};

} // namespace
//-------------------------------------------------------------------------------------------------
