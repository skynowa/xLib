/**
 * \file  ISync.h
 * \brief Sync interface
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface
{

template<typename T>
class xNO_VTABLE ISync
    /// handle interface
{
public:
///@name ctors, dtor
///@{
			 ISync() = default;
	virtual ~ISync() = default;
///@}

    virtual const T & handle() const = 0;
        ///< get handle
    virtual void_t    create() = 0;
        ///< create
    virtual void_t    close() = 0;
        ///< close
};

} // namespace
//-------------------------------------------------------------------------------------------------
