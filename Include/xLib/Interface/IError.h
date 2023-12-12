/**
 * \file  IError.h
 * \brief Error
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template <typename CodeT>
class IError
    /// last error
{
public:
///\name ctors, dtor
///\{
			 IError() = default;
	virtual ~IError() = default;
///\}

    virtual CodeT          code() const = 0;
        ///< Code
    virtual bool_t         isOk() const = 0;
        ///< Check for success
    virtual std::tstring_t category() const = 0;
        ///< Category (type)
    virtual std::tstring_t message() const = 0;
        ///< Detail message

public:
    bool_t         isFail() const;
        ///< Check for error
    std::tstring_t str() const;
        ///< Formatted message
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "IError.inl"
//-------------------------------------------------------------------------------------------------
