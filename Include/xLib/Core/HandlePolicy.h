/**
 * \file  HandlePolicy.h
 * \brief error handle value
 */


#pragma once

#if xENV_WIN
	#include <mysql.h>
	#include <errmsg.h>
	#include <mysqld_error.h>
#else
	#include <mysql/mysql.h>
	#include <mysql/errmsg.h>
	#include <mysql/mysqld_error.h>
#endif

#include <curl/curl.h>

#include <xLib/Core/Core.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/HandlePolicyType.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T, HandlePolicyType valueT>
struct HandlePolicy;
    /// handle error
//-------------------------------------------------------------------------------------------------
///\name Factory
///\{
// TODO: isValid - add const
#define xHANDLE_POLICY_FACTORY(type, null_value) \
	template<typename T> \
	class HandlePolicy<T, type> \
	{ \
	public: \
		static \
		T \
		null() \
		{ \
			return null_value; \
		} \
		\
		static \
		std::size_t \
		openMax() \
		{ \
			return _openMax_impl(); \
		} \
		\
		static \
		T \
		clone(const T a_handle) \
		{ \
			return _clone_impl(a_handle); \
		} \
		\
		static \
		bool_t \
		isValid(const T a_handle) \
		{ \
			return _isValid_impl(a_handle); \
		} \
		\
		static \
		void \
		close(T &a_handle) \
		{ \
			_close_impl(a_handle); \
		} \
	\
	xPLATFORM_IMPL: \
		static std::size_t _openMax_impl(); \
		static T           _clone_impl(const T handle); \
		static bool_t      _isValid_impl(const T handle); \
		static void_t      _close_impl(T &handle); \
	}
///\}
//-------------------------------------------------------------------------------------------------
///\name Impl
///\{
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvNative,        xNATIVE_HANDLE_NULL);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvNativeInvalid, xNATIVE_HANDLE_INVALID);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvDll,           nullptr);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvStdFile,       nullptr);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvMySqlConn,     nullptr);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvMySqlResult,   nullptr);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvCurl,          nullptr);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvFindDir,       xFIND_DIR_HANDLE_NULL);
xHANDLE_POLICY_FACTORY(HandlePolicyType::hvSocket,        xSOCKET_HANDLE_INVALID);
///\}
//-------------------------------------------------------------------------------------------------
} // namespace
//-------------------------------------------------------------------------------------------------
#include "HandlePolicy.inl"

#if   xENV_WIN
    #include "Platform/Win/HandlePolicy_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/HandlePolicy_unix.inl"
#endif
//-------------------------------------------------------------------------------------------------

