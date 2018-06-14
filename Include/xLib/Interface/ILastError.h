/**
 * \file  ILastError.h
 * \brief last error interface
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, interface)

template <typename ErrorT>
class xNO_VTABLE ILastError
    /// last error interface
{
public:
    virtual ErrorT         lastError() const = 0;
    virtual std::tstring_t lastErrorStr() const = 0;

protected:
	ErrorT _lastError {};
};

xNAMESPACE_END2(xl, interface)
//-------------------------------------------------------------------------------------------------
