/**
 * \file  HandlePolicy.h
 * \brief error handle value
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

enum ExHandlePolicyType
    /// error handle type
{
    hvInvalid = - 1,    ///< like "invalid"
    hvNull    = 0,      ///< like "null"
    hvStd     = 1       ///< like xPTR_NULL
};

template<typename T, ExHandlePolicyType valueT>
struct HandlePolicy;
    /// handle error

template<typename T>
struct HandlePolicy<T, hvInvalid>
    /// handle error is hvInvalid
{
    static
    T null() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_INVALID;
    }
};

template<typename T>
struct HandlePolicy<T, hvNull>
    /// handle error is hvNull
{
    static
    T null() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_NULL;
    }
};

template<typename T>
struct HandlePolicy<T, hvStd>
    /// handle error is hvStd
{
    static
    T null() xWARN_UNUSED_RV
    {
        return xPTR_NULL;
    }
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
