/**
 * \file  ILastError.h
 * \brief last error interface
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface
{

template <typename ErrorT>
class xNO_VTABLE ILastError
    /// last error interface
{
public:
///@name ctors, dtor
///@{
			 ILastError() = default;
	virtual ~ILastError() = default;
///@}

    virtual ErrorT         code() const = 0;
        ///<
    virtual bool_t         isOk() const;
        ///<
    virtual bool_t         isError() const;
        ///<
    virtual std::tstring_t str() const = 0;
		///<

protected:
	ErrorT         _code {};
	std::tstring_t _str;
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "ILastError.inl"
//-------------------------------------------------------------------------------------------------
