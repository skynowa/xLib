/**
 * \file  HandlePolicy.h
 * \brief error handle value
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

enum HandlePolicyType
    /// error handle type
{
    hvInvalid = - 1,    ///< like "invalid"
    hvNull    = 0,      ///< like "null"
    hvStd     = 1       ///< like xPTR_NULL
};

template<typename T, HandlePolicyType valueT>
struct HandlePolicy;
    /// handle error
//-------------------------------------------------------------------------------------------------
template<typename T>
struct HandlePolicy<T, hvInvalid>
    /// handle error is hvInvalid
{
    static T      null() xWARN_UNUSED_RV;
    static T      dup(const T &a_handle) xWARN_UNUSED_RV;
    static bool_t isValid(const T &a_handle) xWARN_UNUSED_RV;
    static void_t close(T &a_handle);

xPLATFORM_IMPL:
    static T      _dup_impl(const T &handle);
    static bool_t _isValid_impl(const T &handle);
    static void_t _close_impl(T &handle);
};
//-------------------------------------------------------------------------------------------------
template<typename T>
struct HandlePolicy<T, hvNull>
    /// handle error is hvNull
{
    static T      null() xWARN_UNUSED_RV;
    static T      dup(const T &a_handle) xWARN_UNUSED_RV;
    static bool_t isValid(const T &a_handle) xWARN_UNUSED_RV;
    static void_t close(T &a_handle);

xPLATFORM_IMPL:
    static T      _dup_impl(const T &handle);
    static bool_t _isValid_impl(const T &handle);
    static void_t _close_impl(T &handle);
};
//-------------------------------------------------------------------------------------------------
template<typename T>
struct HandlePolicy<T, hvStd>
    /// handle error is hvStd
{
    static T      null() xWARN_UNUSED_RV;
    static T      dup(const T &a_handle) xWARN_UNUSED_RV;
    static bool_t isValid(const T &a_handle) xWARN_UNUSED_RV;
    static void_t close(T &a_handle);
};
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "HandlePolicy.inl"

#if   xENV_WIN
    #include "Platform/Win/HandlePolicy_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/HandlePolicy_unix.inl"
#endif
//-------------------------------------------------------------------------------------------------
