/**
 * \file  HandleErrorT.h
 * \brief error handle value
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

enum ExHandleValue
    /// error handle type
{
    hvInvalid = - 1,    ///< like "invalid"
    hvNull    = 0       ///< like "null"
};

template<typename T, ExHandleValue valueT>
struct HandleErrorT;
    /// handle error

template<typename T>
struct HandleErrorT<T, hvInvalid>
    /// handle error is hvInvalid
{
    static
    T get() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_INVALID;
    }
};

template<typename T>
struct HandleErrorT<T, hvNull>
    /// handle error is hvNull
{
    static
    T get() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_NULL;
    }
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
