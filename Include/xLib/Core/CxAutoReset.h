/**
 * \file   CxAutoReset.h
 * \brief  auto reset value
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

template <class T>
class CxAutoReset
    ///< auto reset value
{
public:
    CxAutoReset(
        T       *value,
        const T &reset_value
    ) :
        _value      (value),
        _reset_value(reset_value)
    {
    }
   ~CxAutoReset()
    {
        *_value = _reset_value;
    }

private:
    T *       _value;
    const T & _reset_value;

    xNO_COPY_ASSIGN(CxAutoReset)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
