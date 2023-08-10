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
class IGetConstRef
    /// Getter by const reference
{
public:
///\name operators
///\{
             IGetConstRef() = default;
    virtual ~IGetConstRef() = default;
///\}

    virtual const T &get() const = 0;
        ///< getter
};
//-------------------------------------------------------------------------------------------------
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

    virtual T &get() = 0;
        ///< getter
};
//-------------------------------------------------------------------------------------------------
template<typename T>
class IGet :
	public IGetConstRef<T>,
	public IGetRef<T>
    /// Getter by const reference, reference
{
public:
///\name operators
///\{
             IGet() = default;
    virtual ~IGet() = default;
///\}
};

} // namespace
//-------------------------------------------------------------------------------------------------
