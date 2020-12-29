/**
 * \file  IPrint.h
 * \brief Printable interface
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface
{

template <typename StreamT>
class xNO_VTABLE IPrint
    /// Printable interface
{
public:
///@name ctors, dtor
///@{
			 IPrint() = default;
	virtual ~IPrint() = default;
///@}

    virtual void_t print(StreamT &) const = 0;
};

} // namespace
//-------------------------------------------------------------------------------------------------
