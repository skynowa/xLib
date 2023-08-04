/**
 * \file  ILastError.h
 * \brief Last error
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template <typename CodeT>
class ILastError
    /// last error
{
public:
///\name ctors, dtor
///\{
			 ILastError() = default;
	virtual ~ILastError() = default;
///\}

    virtual CodeT          code() const = 0;
        ///< Code
    virtual bool_t         isOk() const = 0;
        ///< Check for success
    virtual std::tstring_t str() const = 0;
        ///< Detail message

public:
    bool_t isError() const;
        ///< Check for error

protected:
    CodeT          _code {};
	std::tstring_t _str;
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "ILastError.inl"
//-------------------------------------------------------------------------------------------------
