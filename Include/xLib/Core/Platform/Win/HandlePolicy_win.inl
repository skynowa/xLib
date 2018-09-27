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
*    public - HandlePolicy<T, hvNative>
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, HandlePolicyType::hvNative>::_openMax_impl()
{
    cint_t iRv = _getmaxstdio();
    xTEST_GR(iRv, 0);

    return static_cast<std::size_t>(iRv);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, HandlePolicyType::hvNative>::_clone_impl(const T &a_handle)
{
    T hRv = null();

    BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), a_handle, ::GetCurrentProcess(), &hRv,
        DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
    xTEST_DIFF(blRes, FALSE);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, HandlePolicyType::hvNative>::_isValid_impl(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, HandlePolicyType::hvNative>::_close_impl(T *a_handle)
{
    BOOL blRes = ::CloseHandle(*a_handle);
    xTEST_DIFF(blRes, FALSE);

    *a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy<T, hvNativeInvalid>
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, HandlePolicyType::hvNativeInvalid>::_openMax_impl()
{
    return HandlePolicy<native_handle_t, HandlePolicyType::hvNative>::openMax();
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, HandlePolicyType::hvNativeInvalid>::_clone_impl(const T &a_handle)
{
    T hRv = null();

    BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), a_handle, ::GetCurrentProcess(), &hRv,
        DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
    xTEST_DIFF(blRes, FALSE);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, HandlePolicyType::hvNativeInvalid>::_isValid_impl(const T &a_handle)
{
    bool_t bRv = false;

    // created but not initialised
    bool_t cond1 = (a_handle != reinterpret_cast<T>(0xCDCDCDCD));
    // uninitialized locals in VC6 when you compile w/ /GZ
    bool_t cond2 = (a_handle != reinterpret_cast<T>(0xCCCCCCCC));
    // indicate an uninitialized variable
    bool_t cond3 = (a_handle != reinterpret_cast<T>(0xBAADF00D));
    // no man's land (normally outside of a process)
    bool_t cond4 = (a_handle != reinterpret_cast<T>(0xFDFDFDFD));
    // freed memory set by NT's heap manager
    bool_t cond5 = (a_handle != reinterpret_cast<T>(0xFEEEFEEE));
    // deleted
    bool_t cond6 = (a_handle != reinterpret_cast<T>(0xDDDDDDDD));
    // compare with error handle value
    bool_t cond7 = (a_handle != null());

    bRv = cond1 && cond2 && cond3 && cond4 && cond5 && cond6 && cond7;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvNativeInvalid>::_close_impl(T *a_handle)
{
    BOOL blRes = ::CloseHandle(*a_handle);
    xTEST_DIFF(blRes, FALSE);

    *a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandleDll
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvDll>::_openMax_impl()
{
    return HandlePolicy<native_handle_t, hvNative>::openMax();
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvDll>::_clone_impl(const T &a_handle)
{
    return a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvDll>::_isValid_impl(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvDll>::_close_impl(T &a_handle)
{
    BOOL blRv = ::FreeLibrary( a_handle.get() );
    xTEST_DIFF(blRv, FALSE);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy hvFindDir
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvFindDir>::_openMax_impl()
{
    return HandlePolicy<native_handle_t, hvNative>::openMax();
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvFindDir>::_clone_impl(const T &a_handle)
{
    return a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvFindDir>::_isValid_impl(const T &a_handle)
{
    return (a_handle != null());
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvFindDir>::_close_impl(T &a_handle)
{
    BOOL blRv = ::FindClose(a_handle);
    xTEST_DIFF(blRv, FALSE);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy hvSocket
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvSocket>::_openMax_impl()
{
    return HandlePolicy<native_handle_t, hvNative>::openMax();
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvSocket>::_clone_impl(const T &a_handle)
{
    return a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvSocket>::_isValid_impl(const T &a_handle)
{
    return (a_handle >= 0);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvSocket>::_close_impl(T &a_handle)
{
    int_t iRv = shutdown(a_handle, SD_BOTH);
    xTEST_DIFF(iRv, xSOCKET_ERROR);

    iRv = ::closesocket(a_handle);
    xTEST_DIFF(iRv, xSOCKET_ERROR);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
