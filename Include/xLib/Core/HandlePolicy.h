/**
 * \file  HandlePolicy.h
 * \brief error handle value
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Format.h>

#if   xENV_WIN
	#include <mysql.h>
	#include <errmsg.h>
	#include <mysqld_error.h>
#elif xENV_APPLE
	#include <mysql.h>
	#include <errmsg.h>
	#include <mysqld_error.h>
#else
	#include <mysql/mysql.h>
	#include <mysql/errmsg.h>
	#include <mysql/mysqld_error.h>
#endif

#include <curl/curl.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

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
//-------------------------------------------------------------------------------------------------
///\name Factory
///\{
template<typename T, HandlePolicyType type>
struct HandlePolicy
{
	static T null()
	{
		if      constexpr (type == HandlePolicyType::hvNative) {
			return xNATIVE_HANDLE_NULL;
		}
		else if constexpr (type == HandlePolicyType::hvNativeInvalid) {
			return xNATIVE_HANDLE_INVALID;
		}
		else if constexpr (type == HandlePolicyType::hvDll) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::hvStdFile) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::hvMySqlConn) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::hvMySqlResult) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::hvCurl) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::hvFindDir) {
			return xFIND_DIR_HANDLE_NULL;
		}
		else if constexpr (type == HandlePolicyType::hvSocket) {
			return xSOCKET_HANDLE_INVALID;
		}
		else {
			// n/a - as compile-time test
		}
	}

	static std::size_t openMax()
	{
		return _openMax_impl();
	}

	static T clone(const T a_handle)
	{
		return _clone_impl(a_handle);
	}

	static bool_t isValid(const T a_handle)
	{
		return _isValid_impl(a_handle);
	}

	static void close(T &a_handle)
	{
		_close_impl(a_handle);
	}

xPLATFORM_IMPL:
	static std::size_t _openMax_impl();
	static T           _clone_impl(const T handle);
	static bool_t      _isValid_impl(const T handle);
	static void_t      _close_impl(T &handle);
};
///\}
//-------------------------------------------------------------------------------------------------
///\name Aliases
///\{
using file_t      = FILE *;
using mysql_t     = MYSQL *;
using mysql_res_t = MYSQL_RES *;
using curl_t      = CURL *;

using HandleNative        = Handle<native_handle_t,   HandlePolicyType::hvNative>;
xUSING_CONST(HandleNative);

using HandleNativeInvalid = Handle<native_handle_t,   HandlePolicyType::hvNativeInvalid>;
xUSING_CONST(HandleNativeInvalid);

using HandleDll           = Handle<dll_handle_t,      HandlePolicyType::hvDll>;
xUSING_CONST(HandleDll);

using HandleStdFile       = Handle<file_t,            HandlePolicyType::hvStdFile>;
xUSING_CONST(HandleStdFile);

using HandleMySqlConn     = Handle<mysql_t,           HandlePolicyType::hvMySqlConn>;
xUSING_CONST(HandleMySqlConn);

using HandleMySqlResult   = Handle<mysql_res_t,       HandlePolicyType::hvMySqlResult>;
xUSING_CONST(HandleMySqlResult);

using HandleCurl          = Handle<curl_t,            HandlePolicyType::hvCurl>;
xUSING_CONST(HandleCurl);

using HandleFindDir       = Handle<find_dir_handle_t, HandlePolicyType::hvFindDir>;
xUSING_CONST(HandleFindDir);

using HandleSocket        = Handle<socket_t,          HandlePolicyType::hvSocket>;
xUSING_CONST(HandleSocket);
///\}
//-------------------------------------------------------------------------------------------------
} // namespace
//-------------------------------------------------------------------------------------------------
#include "HandlePolicy.inl"
//-------------------------------------------------------------------------------------------------

