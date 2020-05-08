/**
 * \file  ISync.h
 * \brief Sync interface
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, interface)

template<typename T>
class xNO_VTABLE ISync
    /// handle interface
{
public:
             ISync() = default;
        ///< constructor
    virtual ~ISync() = default;
        ///< destructor

    virtual const T & handle() const = 0;
        ///< get handle
    virtual void_t    create() = 0;
        ///< create
    virtual void_t    close() = 0;
        ///< close
};

xNAMESPACE_END2(xl, interface)
//-------------------------------------------------------------------------------------------------
