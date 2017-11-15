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
*    public - HandlePolicy Invalid
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvInvalid>::null()
{
    return xNATIVE_HANDLE_INVALID;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvInvalid>::clone(const T &a_handle)
{
    return _clone_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvInvalid>::isValid(const T &a_handle)
{
    return _isValid_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvInvalid>::close(T &a_handle)
{
    _close_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy Null
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvNull>::null()
{
    return xNATIVE_HANDLE_NULL;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvNull>::clone(const T &a_handle)
{
    return _clone_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvNull>::isValid(const T &a_handle)
{
    return _isValid_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvNull>::close(T &a_handle)
{
    _close_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy hvDll
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvDll>::null()
{
    return static_cast<T>(xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvDll>::clone(const T &a_handle)
{
    return _clone_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvDll>::isValid(const T &a_handle)
{
    return _isValid_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvDll>::close(T &a_handle)
{
    _close_impl(a_handle);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy Std
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvStd>::null()
{
    return static_cast<T>(xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvStd>::clone(const T &a_handle)
{
    int_t handle = /*::*/fileno(a_handle);
    xTEST_DIFF(handle, - 1);

    native_handle_t nativeHandle = HandlePolicy<native_handle_t, hvInvalid>::clone(handle);

    return static_cast<T>( xTFDOPEN(nativeHandle, xT("r+")) );  // TODO: clone - open mode
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvStd>::isValid(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvStd>::close(T &a_handle)
{
    int_t iRv = std::fclose(a_handle);
    xTEST_DIFF(iRv, xTEOF);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
