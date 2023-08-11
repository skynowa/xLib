/**
 * \file  IStr.h
 * \brief Get as string
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

class IStr
    /// Get as string
{
public:
///\name ctors, dtor
///\{
             IStr() = default;
    virtual ~IStr() = default;
///\}

    virtual std::tstring_t str() const = 0;
        ///< Get as string
};

} // namespace
//-------------------------------------------------------------------------------------------------
