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

enum HandlePolicyType
    /// error handle type
{
    hvInvalid = -1, ///< like "invalid"
    hvNull,         ///< like "null"
    hvDll,          ///< DLL
    hvStdFile,          ///< like xPTR_NULL
    hvMySqlConn,    ///< MySQL connection
    hvMySqlResult,  ///< MySQL result
    hvCurl,         ///< CURL
    hvFindDir,      ///< Dir find
    hvSocket        ///< Socket
};

template<typename T, HandlePolicyType valueT>
class HandleT;
    /// handle

template<typename T, HandlePolicyType valueT>
struct HandlePolicy;
    /// handle error
//-------------------------------------------------------------------------------------------------
#define xHANDLE_POLICY_FACTORY(type) \
    template<typename T> \
    struct HandlePolicy<T, type> \
    { \
        static T      null() xWARN_UNUSED_RV; \
        static T      clone(const T &a_handle) xWARN_UNUSED_RV; \
        static bool_t isValid(const T &a_handle) xWARN_UNUSED_RV; \
        static void_t close(T &a_handle); \
    \
    xPLATFORM_IMPL: \
        static T      _clone_impl(const T &handle); \
        static bool_t _isValid_impl(const T &handle); \
        static void_t _close_impl(T &handle); \
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
xHANDLE_POLICY_FACTORY(hvInvalid);
xHANDLE_POLICY_FACTORY(hvNull);
xHANDLE_POLICY_FACTORY(hvDll);
xHANDLE_POLICY_FACTORY(hvStdFile);
xHANDLE_POLICY_FACTORY(hvMySqlConn);
xHANDLE_POLICY_FACTORY(hvMySqlResult);
xHANDLE_POLICY_FACTORY(hvCurl);
xHANDLE_POLICY_FACTORY(hvFindDir);
xHANDLE_POLICY_FACTORY(hvSocket);

xHANDLE_POLICY_FACTORY_IMPL(hvInvalid,     xNATIVE_HANDLE_INVALID);
xHANDLE_POLICY_FACTORY_IMPL(hvNull,        xNATIVE_HANDLE_NULL);
xHANDLE_POLICY_FACTORY_IMPL(hvDll,         xPTR_NULL);
xHANDLE_POLICY_FACTORY_IMPL(hvStdFile,     xPTR_NULL);
xHANDLE_POLICY_FACTORY_IMPL(hvMySqlConn,   xPTR_NULL);
xHANDLE_POLICY_FACTORY_IMPL(hvMySqlResult, xPTR_NULL);
xHANDLE_POLICY_FACTORY_IMPL(hvCurl,        xPTR_NULL);
xHANDLE_POLICY_FACTORY_IMPL(hvFindDir,     xFIND_DIR_HANDLE_NULL);
xHANDLE_POLICY_FACTORY_IMPL(hvSocket,      xSOCKET_HANDLE_INVALID);

typedef HandleT<native_handle_t, hvInvalid>     HandleInvalid;
typedef HandleT<native_handle_t, hvNull>        HandleNull;
typedef HandleT<dll_handle_t,    hvDll>         HandleDll;
typedef HandleT<FILE *,          hvStdFile>     HandleStdFile;
typedef HandleT<MYSQL *,         hvMySqlConn>   HandleMySqlConn;
typedef HandleT<MYSQL_RES *,     hvMySqlResult> HandleMySqlResult;
typedef HandleT<CURL *,          hvCurl>        HandleCurl;
typedef HandleT<DIR *,           hvFindDir>     HandleFindDir;
typedef HandleT<socket_t,        hvSocket>      HandleSocket;
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
