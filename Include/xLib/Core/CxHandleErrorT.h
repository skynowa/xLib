/**
 * \file  CxHandleErrorT.h
 * \brief error handle value
 */


#pragma once

#ifndef xLib_CxHandleErrorTH
#define xLib_CxHandleErrorTH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, core)

enum ExHandleValue
    /// error handle type
{
    hvInvalid = - 1,    ///< like "invalid"
    hvNull    = 0       ///< like "null"
};

template<ExHandleValue tagT>
struct CxHandleErrorT;
    /// handle error

template<>
struct CxHandleErrorT<hvInvalid>
    /// handle error is hvInvalid
{
    static
    native_handle_t
    get() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_INVALID;
    }
};

template<>
struct CxHandleErrorT<hvNull>
    /// handle error is hvNull
{
    static
    native_handle_t
    get() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_NULL;
    }
};

xNAMESPACE2_END(xlib, core)
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxHandleErrorTH
