/**
 * \file  IGet.h
 * \brief Getter
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template<typename T>
class IGet
    /// Getter
{
public:
///\name operators
///\{
             IGet() = default;
    virtual ~IGet() = default;
///\}

    virtual const T &get() const = 0;
        ///< getter
};

template<typename T>
class IGetRef
    /// Getter by reference
{
public:
///\name operators
///\{
             IGetRef() = default;
    virtual ~IGetRef() = default;
///\}

    virtual T &get() const = 0;
        ///< getter
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - T &get()
 */
//-------------------------------------------------------------------------------------------------
