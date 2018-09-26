/**
 * \file  HandlePolicy.h
 * \brief error handle value
 */


#pragma once

#include <mysql/mysql.h>
#include <mysql/errmsg.h>
#include <mysql/mysqld_error.h>

#include <curl/curl.h>

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

enum class HandlePolicyType
    /// error handle type
{
    hvNative = 0,       ///< like "null"
    hvNativeInvalid,    ///< like "invalid" (-1)
    hvDll,              ///< DLL
    hvStdFile,          ///< like nullptr
    hvMySqlConn,        ///< MySQL connection
    hvMySqlResult,      ///< MySQL result
    hvCurl,             ///< CURL
    hvFindDir,          ///< Dir find
    hvSocket            ///< Socket
};

template<typename T, HandlePolicyType valueT>
class Handle;
    /// handle

template<typename T, HandlePolicyType valueT>
struct HandlePolicy;
    /// handle error
//-------------------------------------------------------------------------------------------------
#define xHANDLE_POLICY_FACTORY(type) \
    template<typename T> \
    struct HandlePolicy<T, type> \
    { \
        static T           null() xWARN_UNUSED_RV; \
        static std::size_t openMax() xWARN_UNUSED_RV; \
        static T           clone(const T &a_handle) xWARN_UNUSED_RV; \
        static bool_t      isValid(const T &a_handle) xWARN_UNUSED_RV; \
        static void_t      close(T &a_handle); \
    \
    xPLATFORM_IMPL: \
        static std::size_t _openMax_impl(); \
        static T           _clone_impl(const T &handle); \
        static bool_t      _isValid_impl(const T &handle); \
        static void_t      _close_impl(T &handle); \
    }

#define xHANDLE_POLICY_FACTORY_IMPL(type, null_value) \
    template<typename T> \
    T \
    HandlePolicy<T, type>::null() \
    { \
        return null_value; \
    } \
    \
    template<typename T> \
    std::size_t \
    HandlePolicy<T, type>::openMax() \
    { \
        return _openMax_impl(); \
    } \
    \
    template<typename T> \
    T \
    HandlePolicy<T, type>::clone(const T &a_handle) \
    { \
        return _clone_impl(a_handle); \
    } \
    \
    template<typename T> \
    bool_t \
    HandlePolicy<T, type>::isValid(const T &a_handle) \
    { \
        return _isValid_impl(a_handle); \
    } \
    \
    template<typename T> \
    void_t \
    HandlePolicy<T, type>::close(T &a_handle) \
    { \
        _close_impl(a_handle); \
    }
//-------------------------------------------------------------------------------------------------
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvNative);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvNativeInvalid);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvDll);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvStdFile);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvMySqlConn);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvMySqlResult);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvCurl);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvFindDir);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvSocket);

xHANDLE_POLICY_FACTORY_IMPL(HandlePolicyType::hvNative,        xNATIVE_HANDLE_NULL);
xHANDLE_POLICY_FACTORY_IMPL(HandlePolicyType::hvNativeInvalid, xNATIVE_HANDLE_INVALID);
xHANDLE_POLICY_FACTORY_IMPL(HandlePolicyType::hvDll,           nullptr);
xHANDLE_POLICY_FACTORY_IMPL(HandlePolicyType::hvStdFile,       nullptr);
xHANDLE_POLICY_FACTORY_IMPL(HandlePolicyType::hvMySqlConn,     nullptr);
xHANDLE_POLICY_FACTORY_IMPL(HandlePolicyType::hvMySqlResult,   nullptr);
xHANDLE_POLICY_FACTORY_IMPL(HandlePolicyType::hvCurl,          nullptr);
xHANDLE_POLICY_FACTORY_IMPL(HandlePolicyType::hvFindDir,       xFIND_DIR_HANDLE_NULL);
xHANDLE_POLICY_FACTORY_IMPL(HandlePolicyType::hvSocket,        xSOCKET_HANDLE_INVALID);

using HandleNative        = Handle<native_handle_t,   HandlePolicyType::hvNative>;
using HandleNativeInvalid = Handle<native_handle_t,   HandlePolicyType::hvNativeInvalid>;
using HandleDll           = Handle<dll_handle_t,      HandlePolicyType::hvDll>;
using HandleStdFile       = Handle<FILE *,            HandlePolicyType::hvStdFile>;
using HandleMySqlConn     = Handle<MYSQL *,           HandlePolicyType::hvMySqlConn>;
using HandleMySqlResult   = Handle<MYSQL_RES *,       HandlePolicyType::hvMySqlResult>;
using HandleCurl          = Handle<CURL *,            HandlePolicyType::hvCurl>;
using HandleFindDir       = Handle<find_dir_handle_t, HandlePolicyType::hvFindDir>;
using HandleSocket        = Handle<socket_t,          HandlePolicyType::hvSocket>;
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
