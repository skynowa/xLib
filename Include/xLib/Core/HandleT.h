/**
 * \file  HandleT.h
 * \brief handle
 */


#pragma once

//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

namespace debug
{

class NativeError;
class StackTrace;
class ErrorReport;
class Debugger;

}

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include <mysql/mysql.h>
#include <mysql/errmsg.h>
#include <mysql/mysqld_error.h>

#include <curl/curl.h>

#include <xLib/Core/Core.h>
#include <xLib/Interface/IHandle.h>
#include <xLib/Core/HandlePolicy.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T, HandlePolicyType valueT>
class HandleT :
    public IHandle<T>
    /// handle
{
public:
              HandleT();
        ///< constructor
    explicit  HandleT(const T &handle);
        ///< constructor
    explicit  HandleT(const HandleT &handle);
        ///< constructor
    virtual  ~HandleT();
        ///< destructor

    HandleT & operator = (const T &handle);
        ///< operator =
    HandleT & operator = (const HandleT &handle);
        ///< operator =

    static
    T         null() xWARN_UNUSED_RV;
        ///< get
    T         get() const xWARN_UNUSED_RV;
        ///< get
    void_t    set(const T &handle);
        ///< set
    T         clone() const xWARN_UNUSED_RV;
        ///< duplicate handle

    bool_t    isValid() const xWARN_UNUSED_RV;
        ///< is valid
    void_t    attach(const T &handle);
        ///< attach
    T         detach() xWARN_UNUSED_RV;
        ///< detach
    void_t    close();
        ///< close

#if xENV_WIN
    ulong_t   info() const xWARN_UNUSED_RV;
        ///< get certain properties of an object handle
    void_t    setInfo(culong_t &mask, culong_t &flags);
        ///< set information
#endif

private:
    typedef HandlePolicy<T, valueT> handle_policy_t;

    T         _handle;    ///< handle
};

typedef HandleT<native_handle_t, hvInvalid>     HandleInvalid;
typedef HandleT<native_handle_t, hvNull>        HandleNull;
typedef HandleT<dll_handle_t,    hvDll>         HandleDll;
typedef HandleT<FILE *,          hvStd>         HandleStd;
typedef HandleT<MYSQL *,         hvMySqlConn>   HandleMySqlConn;
typedef HandleT<MYSQL_RES *,     hvMySqlResult> HandleMySqlResult;
typedef HandleT<CURL *,          hvCurl>        HandleCurl;
typedef HandleT<DIR *,           hvFindDir>     HandleFindDir;
typedef HandleT<socket_t,        hvSocket>      HandleSocket;

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "HandleT.inl"

#if xENV_WIN
    #include "Platform/Win/HandleT_win.inl"
#endif
