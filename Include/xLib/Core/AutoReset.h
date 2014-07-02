/**
 * \file   AutoReset.h
 * \brief  auto reset value
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

template <class T>
class AutoReset
    ///< auto reset value
{
public:
    AutoReset(
        T       *value,
        const T &reset_value
    ) :
        _value      (value),
        _reset_value(reset_value)
    {
    }
   ~AutoReset()
    {
        *_value = _reset_value;
    }

private:
    T *       _value;
    const T & _reset_value;

    xNO_COPY_ASSIGN(AutoReset)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
