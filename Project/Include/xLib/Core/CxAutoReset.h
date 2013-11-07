/**
 * \file   CxAutoReset.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template <class T>
class CxAutoReset :
    public CxNonCopyable
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
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
