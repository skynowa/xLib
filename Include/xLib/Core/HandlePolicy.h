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
//-------------------------------------------------------------------------------------------------
template<typename T>
struct HandlePolicy<T, hvInvalid>
    /// handle error is hvInvalid
{
    static T null() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_INVALID;
    }

    static T dup(const T &a_handle) xWARN_UNUSED_RV
    {
        return _dup_impl(a_handle);
    }

    static bool_t isValid(const T &a_handle)
    {
        return _isValid_impl(a_handle);
    }

    static void_t close(T *a_handle)
    {
        return _close_impl(a_handle);
    }


xPLATFORM_IMPL:
    static T      _dup_impl(const T &handle);
    static bool_t _isValid_impl(const T &handle);
    static void_t _close_impl(T *handle);
};
//-------------------------------------------------------------------------------------------------
template<typename T>
struct HandlePolicy<T, hvNull>
    /// handle error is hvNull
{
    static
    T null() xWARN_UNUSED_RV
    {
        return xNATIVE_HANDLE_NULL;
    }

    static T dup(const T &a_handle) xWARN_UNUSED_RV
    {
        return _dup_impl(a_handle);
    }

    static bool_t isValid(const T &a_handle)
    {
        return _isValid_impl(a_handle);
    }

    static void_t close(T *a_handle)
    {
       return _close_impl(a_handle);
    }

xPLATFORM_IMPL:
    static T      _dup_impl(const T &handle);
    static bool_t _isValid_impl(const T &handle);
    static void_t _close_impl(T *handle);
};
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#if   xENV_WIN
    #include "Platform/Win/HandlePolicy_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/HandlePolicy_unix.inl"
#endif
//-------------------------------------------------------------------------------------------------
