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
*    public - HandlePolicy<T, hvInvalid>
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvInvalid>::_dup_impl(const T &a_handle)
{
    return ::dup(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvInvalid>::_isValid_impl(const T &a_handle)
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
HandlePolicy<T, hvInvalid>::_close_impl(T *&a_handle)
{
    int_t iRv = ::close(*a_handle);
    xTEST_DIFF(iRv, - 1);

    *a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy<T, hvInvalid>
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T>
T
HandlePolicy<T, hvNull>::_dup_impl(const T &a_handle)
{
    return ::dup(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T>
bool_t
HandlePolicy<T, hvNull>::_isValid_impl(const T &a_handle)
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
HandlePolicy<T, hvNull>::_close_impl(T *&a_handle)
{
    int_t iRv = ::close(*a_handle);
    xTEST_DIFF(iRv, - 1);

    *a_handle = null();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
