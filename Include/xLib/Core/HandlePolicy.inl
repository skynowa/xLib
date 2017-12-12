/**
 * \file  Handle.inl
 * \brief handle
 */


#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*    public - HandlePolicy Std
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvStdFile>::_openMax_impl()
{
	std::size_t uiRv = 0;

#if   xENV_WIN
    int_t iRv = _getmaxstdio();
    xTEST_GR(iRv, 0);

    uiRv = static_cast<std::size_t>(iRv);
#elif xENV_UNIX
    rlimit limit;   xSTRUCT_ZERO(limit);

    #if xENV_BSD
        cint_t resource = RLIMIT_OFILE;
    #else
        cint_t resource = RLIMIT_NOFILE;
    #endif

    int_t iRv = ::getrlimit(resource, &limit);
    xTEST_EQ(iRv, 0);

    uiRv = limit.rlim_cur;
    xTEST_GR(uiRv, 0);
#endif

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvStdFile>::_clone_impl(const T &a_handle)
{
    int_t handle = /*::*/fileno(a_handle);
    xTEST_DIFF(handle, - 1);

    native_handle_t nativeHandle = HandlePolicy<native_handle_t, hvInvalid>::clone(handle);

    return static_cast<T>( xTFDOPEN(nativeHandle, xT("r+")) );  // TODO: clone - open mode
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvStdFile>::_isValid_impl(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvStdFile>::_close_impl(T &a_handle)
{
    int_t iRv = std::fclose(a_handle);
    xTEST_DIFF(iRv, xTEOF);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy hvMySqlConn
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvMySqlConn>::_openMax_impl()
{
	// TODO: _openMax_impl

   /**
	* show variables like "max_connections"
	*
    * +-----------------+-------+
    * | Variable_name   | Value |
    * +-----------------+-------+
    * | max_connections | 100   |
    * +-----------------+-------+
    *
    * set global max_connections = 200;
    */

    return 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvMySqlConn>::_clone_impl(const T &a_handle)
{
    return a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvMySqlConn>::_isValid_impl(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvMySqlConn>::_close_impl(T &a_handle)
{
    (void_t)::mysql_close(a_handle);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy hvMySqlResult
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvMySqlResult>::_openMax_impl()
{
	// TODO: _openMax_impl

    return 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvMySqlResult>::_clone_impl(const T &a_handle)
{
    return a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvMySqlResult>::_isValid_impl(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvMySqlResult>::_close_impl(T &a_handle)
{
    (void_t)::mysql_free_result(a_handle);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy hvCurl
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvCurl>::_openMax_impl()
{
    return static_cast<std::size_t>(CURLOPT_MAXCONNECTS);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvCurl>::_clone_impl(const T &a_handle)
{
    return ::curl_easy_duphandle(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvCurl>::_isValid_impl(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvCurl>::_close_impl(T &a_handle)
{
    (void_t)::curl_easy_cleanup(a_handle);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------


#if 0

/**************************************************************************************************
*    public - HandlePolicy hvXXXXXXXXXX
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvXXXXXXXXXX>::_openMax_impl()
{
	// TODO: _openMax_impl

    return 0;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvXXXXXXXXXX>::_clone_impl(const T &a_handle)
{
    return a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvXXXXXXXXXX>::_isValid_impl(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvXXXXXXXXXX>::_close_impl(T &a_handle)
{
    // (void_t)::mysql_free_result(a_handle);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------

#endif

xNAMESPACE_END2(xl, core)
