/**
 * \file  IValid.h
 * \brief Validator
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

class IValid
    /// Validator
{
public:
///\name ctors, dtor
///\{
             IValid() = default;
    virtual ~IValid() = default;
///\}

    virtual explicit operator bool() const = 0;
        ///< Check result

public:
    bool_t isOk() const;
        ///< Result is success
    bool_t isError() const;
        ///< Result is error
};

} // namespace
//-------------------------------------------------------------------------------------------------
