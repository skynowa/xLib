/**
 * \file  ILastError.h
 * \brief last error
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Interface/IValid.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template <typename ErrorT>
class ILastError :
	public IValid
    /// last error
{
public:
///\name ctors, dtor
///\{
			 ILastError() = default;
	virtual ~ILastError() = default;
///\}

    virtual ErrorT         code() const = 0;
        ///<
    virtual std::tstring_t str() const = 0;
		///<

protected:
	ErrorT         _code {};
	std::tstring_t _str;
};

} // namespace
//-------------------------------------------------------------------------------------------------
