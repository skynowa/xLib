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

    virtual bool_t isOk() const = 0;
        ///< Result is success

public:
    bool_t isError() const;
        ///< Result is error
};

} // namespace
//-------------------------------------------------------------------------------------------------
