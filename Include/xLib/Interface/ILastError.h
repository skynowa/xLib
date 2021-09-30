/**
 * \file  ILastError.h
 * \brief last error interface_
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template <typename ErrorT>
class xNO_VTABLE ILastError
    /// last error interface_
{
public:
///@name ctors, dtor
///@{
			 ILastError() = default;
	virtual ~ILastError() = default;
///@}

    virtual ErrorT         lastError() const = 0;
    virtual std::tstring_t lastErrorStr() const = 0;

protected:
	ErrorT         _lastError {};
	std::tstring_t _lastErrorStr;
};

} // namespace
//-------------------------------------------------------------------------------------------------
