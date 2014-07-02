/**
 * \file  HandleErrorT.h
 * \brief error handle value
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

enum ExHandleValue
    /// error handle type
{
    hvInvalid = - 1,    ///< like "invalid"
    hvNull    = 0       ///< like "null"
};

template<ExHandleValue tagT>
struct HandleErrorT;
    /// handle error

template<>
struct HandleErrorT<hvInvalid>
    /// handle error is hvInvalid
{
    static
    native_handle_t get() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_INVALID;
    }
};

template<>
struct HandleErrorT<hvNull>
    /// handle error is hvNull
{
    static
    native_handle_t get() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_NULL;
    }
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
