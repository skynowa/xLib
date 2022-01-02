/**
 * \file  IHandle.h
 * \brief handle interface
 */


#pragma once

#ifndef IHandle_H
#define IHandle_H

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::interface
{

template<typename T>
class xNO_VTABLE IHandle
    /// handle interface
{
public:
///\name operators
///\{
			 IHandle() = default;
	virtual ~IHandle() = default;
///\}

    virtual T      get() const = 0;
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

} // namespace
//-------------------------------------------------------------------------------------------------

#endif
