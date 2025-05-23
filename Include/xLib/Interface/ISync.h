/**
 * \file  ISync.h
 * \brief Sync
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface_
{

template<typename T>
class ISync
    /// handle
{
public:
///\name ctors, dtor
///\{
			 ISync() = default;
	virtual ~ISync() = default;
///\}

    virtual const T & handle() const = 0;
        ///< get handle
    virtual void_t    create() = 0;
        ///< create
    virtual void_t    close() = 0;
        ///< close
};

} // namespace
//-------------------------------------------------------------------------------------------------
