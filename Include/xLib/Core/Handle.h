/**
 * \file  Handle.h
 * \brief handle
 */


#pragma once

//-------------------------------------------------------------------------------------------------
namespace xl::core
{

namespace debug
{

class NativeError;
class StackTrace;
class ErrorReport;
class Debugger;

}

} // namespace
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Core/Format.h>
#include <xLib/Interface/IHandle.h>

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

enum class HandleType
	/// Handle type
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

template<typename T, HandleType typeT>
class Handle final :
    public IHandle<T>
    /// handle
{
public:
///\name ctors, dtor
///\{
              Handle();
    explicit  Handle(const T &handle);
    explicit  Handle(const Handle &handle);
    virtual  ~Handle();
///\}

///\name operators
///\{
	Handle & operator = (const T &handle);
	Handle & operator = (const Handle &handle);
///\}

    T      get() const final;
        ///< get
    void_t set(const T &handle) final;
        ///< set
    T      clone() const final;
        ///< duplicate handle
    void_t setCloseOnExec(cbool_t flag);
		///< duplicate file descriptors from sub-processes

    bool_t isValid() const final;
        ///< is valid
    void_t attach(const T &handle) final;
        ///< attach
    T      detach() final;
        ///< detach
    void_t close() final;
        ///< close

#if xENV_WIN
    ulong_t info() const;
        ///< get certain properties of an object handle
    void_t  setInfo(culong_t mask, culong_t flags);
        ///< set information
#endif

xPUBLIC_STATIC:
	static T           null();
		///< get "null" value
	static std::size_t openMax();
		///< maximum open handles

private:
    T _handle {}; ///< handle

xPLATFORM_IMPL:
    void_t _setCloseOnExec_impl(cbool_t flag);
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Handle.inl"

#if xENV_WIN
    #include "Platform/Win/Handle_win.inl"
#endif
//-------------------------------------------------------------------------------------------------
///\name Aliases
///\{
using HandleNative        = Handle<xl::native_handle_t,   HandleType::Native>;
xUSING_CONST(HandleNative);

using HandleNativeInvalid = Handle<xl::native_handle_t,   HandleType::NativeInvalid>;
xUSING_CONST(HandleNativeInvalid);

using HandleDll           = Handle<xl::dll_handle_t,      HandleType::Dll>;
xUSING_CONST(HandleDll);

using HandleStdFile       = Handle<std::FILE *,           HandleType::StdFile>;
xUSING_CONST(HandleStdFile);

using HandleMySqlConn     = Handle<::MYSQL *,             HandleType::MySqlConn>;
xUSING_CONST(HandleMySqlConn);

using HandleMySqlResult   = Handle<::MYSQL_RES *,         HandleType::MySqlResult>;
xUSING_CONST(HandleMySqlResult);

using HandleCurl          = Handle<::CURL *,              HandleType::Curl>;
xUSING_CONST(HandleCurl);

using HandleFindDir       = Handle<xl::find_dir_handle_t, HandleType::FindDir>;
xUSING_CONST(HandleFindDir);

using HandleSocket        = Handle<xl::socket_t,          HandleType::Socket>;
xUSING_CONST(HandleSocket);
///\}
//-------------------------------------------------------------------------------------------------
