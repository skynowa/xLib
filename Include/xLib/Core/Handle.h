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
#include <xLib/Core/HandlePolicy.h>
#include <xLib/Interface/IHandle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

template<typename T, HandlePolicyType valueT>
class Handle :
    public IHandle<T>
    /// handle
{
public:
///\name ctors, dtor
///\{
				Handle();
	explicit    Handle(const T &handle);
	explicit    Handle(const Handle &handle);
	virtual    ~Handle();
///\}

///\name operators
///\{
	Handle &    operator = (const T &handle);
	Handle &    operator = (const Handle &handle);
///\}

    static
    T           null();
        ///< get
    static
    std::size_t openMax();
		///< maximum open handles

    T           get() const;
        ///< get
    void_t      set(const T &handle);
        ///< set
    T           clone() const;
        ///< duplicate handle
    void_t      setCloseOnExec(cbool_t flag);
		///< duplicate file descriptors from sub-processes

    bool_t      isValid() const;
        ///< is valid
    void_t      attach(const T &handle);
        ///< attach
    T           detach();
        ///< detach
    void_t      close();
        ///< close

#if xENV_WIN
    ulong_t     info() const;
        ///< get certain properties of an object handle
    void_t      setInfo(culong_t &mask, culong_t &flags);
        ///< set information
#endif

private:
    using handle_policy_t = HandlePolicy<T, valueT>;

    T           _handle {};    ///< handle

xPLATFORM_IMPL:
    void_t      _setCloseOnExec_impl(cbool_t flag);
};
//-------------------------------------------------------------------------------------------------
///\name Aliases
///\{
using HandleNative        = Handle<native_handle_t,   HandlePolicyType::hvNative>;
xUSING_CONST(HandleNative);

using HandleNativeInvalid = Handle<native_handle_t,   HandlePolicyType::hvNativeInvalid>;
xUSING_CONST(HandleNativeInvalid);

using HandleDll           = Handle<dll_handle_t,      HandlePolicyType::hvDll>;
xUSING_CONST(HandleDll);

using HandleStdFile       = Handle<FILE *,            HandlePolicyType::hvStdFile>;
xUSING_CONST(HandleStdFile);

using HandleMySqlConn     = Handle<MYSQL *,           HandlePolicyType::hvMySqlConn>;
xUSING_CONST(HandleMySqlConn);

using HandleMySqlResult   = Handle<MYSQL_RES *,       HandlePolicyType::hvMySqlResult>;
xUSING_CONST(HandleMySqlResult);

using HandleCurl          = Handle<CURL *,            HandlePolicyType::hvCurl>;
xUSING_CONST(HandleCurl);

using HandleFindDir       = Handle<find_dir_handle_t, HandlePolicyType::hvFindDir>;
xUSING_CONST(HandleFindDir);

using HandleSocket        = Handle<socket_t,          HandlePolicyType::hvSocket>;
xUSING_CONST(HandleSocket);
///\}
//-------------------------------------------------------------------------------------------------
} // namespace
//-------------------------------------------------------------------------------------------------
#include "Handle.inl"

#if xENV_WIN
    #include "Platform/Win/Handle_win.inl"
#endif

