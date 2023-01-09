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
    Native        = 0, ///< like "null"
    NativeInvalid = 1, ///< like "invalid" (-1)
    Dll           = 2, ///< DLL
    StdFile       = 3, ///< like nullptr
    MySqlConn     = 4, ///< MySQL connection
    MySqlResult   = 5, ///< MySQL result
    Curl          = 6, ///< CURL
    FindDir       = 7, ///< Dir find
    Socket        = 8  ///< Socket
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

	static T null()
	{
		if      constexpr (type == HandlePolicyType::Native) {
			return xNATIVE_HANDLE_NULL;
		}
		else if constexpr (type == HandlePolicyType::NativeInvalid) {
			return xNATIVE_HANDLE_INVALID;
		}
		else if constexpr (type == HandlePolicyType::Dll) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::StdFile) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::MySqlConn) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::MySqlResult) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::Curl) {
			return nullptr;
		}
		else if constexpr (type == HandlePolicyType::FindDir) {
			return xFIND_DIR_HANDLE_NULL;
		}
		else if constexpr (type == HandlePolicyType::Socket) {
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

using HandleNative        = Handle<native_handle_t,   HandlePolicyType::Native>;
xUSING_CONST(HandleNative);

using HandleNativeInvalid = Handle<native_handle_t,   HandlePolicyType::NativeInvalid>;
xUSING_CONST(HandleNativeInvalid);

using HandleDll           = Handle<dll_handle_t,      HandlePolicyType::Dll>;
xUSING_CONST(HandleDll);

using HandleStdFile       = Handle<file_t,            HandlePolicyType::StdFile>;
xUSING_CONST(HandleStdFile);

using HandleMySqlConn     = Handle<mysql_t,           HandlePolicyType::MySqlConn>;
xUSING_CONST(HandleMySqlConn);

using HandleMySqlResult   = Handle<mysql_res_t,       HandlePolicyType::MySqlResult>;
xUSING_CONST(HandleMySqlResult);

using HandleCurl          = Handle<curl_t,            HandlePolicyType::Curl>;
xUSING_CONST(HandleCurl);

using HandleFindDir       = Handle<find_dir_handle_t, HandlePolicyType::FindDir>;
xUSING_CONST(HandleFindDir);

using HandleSocket        = Handle<socket_t,          HandlePolicyType::Socket>;
xUSING_CONST(HandleSocket);
///\}
//-------------------------------------------------------------------------------------------------
} // namespace
//-------------------------------------------------------------------------------------------------
#include "HandlePolicy.inl"
//-------------------------------------------------------------------------------------------------

