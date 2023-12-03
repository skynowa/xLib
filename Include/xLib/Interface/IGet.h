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
class IGetValue
    /// Getter by value
{
public:
///\name ctors, dtor
///\{
             IGetValue() = default;
    virtual ~IGetValue() = default;
///\}

    virtual T get() const = 0;
        ///< getter
};
//-------------------------------------------------------------------------------------------------
template<typename T>
class IGetConstRef
    /// Getter by const reference
{
public:
///\name ctors, dtor
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
///\name ctors, dtor
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
///\name ctors, dtor
///\{
             IGet() = default;
    virtual ~IGet() = default;
///\}
};

} // namespace
//-------------------------------------------------------------------------------------------------
