/**
 * \file   AutoReset.h
 * \brief  auto reset value
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

template<typename T>
class AutoReset
    ///< auto reset value
{
public:
    AutoReset(
        T       *a_value,
        const T &a_resetValue
    ) :
        _value     (a_value),
        _resetValue(a_resetValue)
    {
    }
   ~AutoReset()
    {
        *_value = _resetValue;
    }

private:
    T       *_value;
    const T &_resetValue;

    xNO_COPY_ASSIGN(AutoReset)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
