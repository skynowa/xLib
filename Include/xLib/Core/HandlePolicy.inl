/**
 * \file  HandleT.inl
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
T
HandlePolicy<T, hvStd>::_clone_impl(const T &a_handle)
{
    int_t handle = /*::*/fileno(a_handle);
    xTEST_DIFF(handle, - 1);

    native_handle_t nativeHandle = HandlePolicy<native_handle_t, hvInvalid>::clone(handle);

    return static_cast<T>( xTFDOPEN(nativeHandle, xT("r+")) );  // TODO: clone - open mode
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvStd>::_isValid_impl(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvStd>::_close_impl(T &a_handle)
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

xNAMESPACE_END2(xl, core)
