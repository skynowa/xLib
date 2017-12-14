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
*    public - HandleNative
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvNative>::_openMax_impl()
{
    rlimit limit;   xSTRUCT_ZERO(limit);

    int_t iRv = ::getrlimit(RLIMIT_NOFILE, &limit);
    xTEST_EQ(iRv, 0);
    xTEST_GR(limit.rlim_cur, 0L);

    return static_cast<std::size_t>( limit.rlim_cur );
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvNative>::_clone_impl(const T &a_handle)
{
    return ::dup(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvNative>::_isValid_impl(const T &a_handle)
{
    bool_t bRv = false;

    // compare with error handle value
    bool_t cond1 = (a_handle != null());
    // handle value is negative
    bool_t cond2 = (a_handle >  null());

    bRv = cond1 && cond2;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvNative>::_close_impl(T &a_handle)
{
    int_t iRv = ::close(a_handle);
    xTEST_DIFF(iRv, - 1);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandleNativeInvalid
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
std::size_t
HandlePolicy<T, hvNativeInvalid>::_openMax_impl()
{
    return HandlePolicy<native_handle_t, hvNative>::openMax();
}
//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvNativeInvalid>::_clone_impl(const T &a_handle)
{
    return ::dup(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvNativeInvalid>::_isValid_impl(const T &a_handle)
{
    bool_t bRv = false;

    // compare with error handle value
    bool_t cond1 = (a_handle != null());
    // handle value is negative
    bool_t cond2 = (a_handle >  null());

    bRv = cond1 && cond2;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T>
void_t
HandlePolicy<T, hvNativeInvalid>::_close_impl(T &a_handle)
{
    int_t iRv = ::close(a_handle);
    xTEST_DIFF(iRv, - 1);

    a_handle = null();
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
    int_t iRv = ::dlclose(a_handle);
    xTEST_EQ(iRv, 0);

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
    int_t iRv = ::closedir(a_handle);
    xTEST_DIFF(iRv, - 1);

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
    int_t iRv = ::close(a_handle);
    xTEST_DIFF(iRv, xSOCKET_ERROR);

    a_handle = null();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
