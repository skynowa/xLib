/**
 * \file  IHandle.h
 * \brief handle interface
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T>
class xNO_VTABLE IHandle
    /// handle interface
{
public:
                   IHandle() {};
        ///< constructor
    virtual       ~IHandle() {};
        ///< destructor

    virtual T      get() const = 0 ;
        ///< get
    virtual void_t set(const T &handle) = 0;
        ///< set
    virtual T      clone() const = 0;
        ///< duplicate handle

    virtual bool_t isValid() const = 0;
        ///< is valid
    virtual void_t attach(const T &handle) = 0;
        ///< attach
    virtual T      detach() = 0;
        ///< detach
    virtual void_t close() = 0;
        ///< close
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
