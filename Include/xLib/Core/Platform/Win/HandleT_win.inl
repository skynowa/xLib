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

/*******************************************************************************
*    public - HandlePolicy<T, hvInvalid>
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, ExHandlePolicyType valueT>
T
HandlePolicy<T, valueT>::_dup_impl(const T &a_handle) const
{
    T hRv = null();

    BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), a_handle, ::GetCurrentProcess(), &hRv,
        DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
    xTEST_DIFF(blRes, FALSE);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandlePolicyType valueT>
bool_t
HandlePolicy<T, valueT>::_isValid_impl(const T &a_handle) const
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
template<typename T, ExHandlePolicyType valueT>
void_t
HandlePolicy<T, valueT>::_close_impl(T *a_handle)
{
    BOOL blRes = ::CloseHandle(*a_handle);
    xTEST_DIFF(blRes, FALSE);

    *a_handle = null();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public - HandlePolicy<T, hvNull>
*
**************************************************************************************************/

// TODO: HandlePolicy<T, hvNull>

//-------------------------------------------------------------------------------------------------
template<typename T, ExHandlePolicyType valueT>
ulong_t
HandleT<T, valueT>::info() const
{
    xTEST_EQ(isValid(), true);

    DWORD flags = 0UL;

    BOOL blRes = ::GetHandleInformation(_handle, &flags);
    xTEST_DIFF(blRes, FALSE);
    xTEST_DIFF(flags, 0UL);

    return flags;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandlePolicyType valueT>
void_t
HandleT<T, valueT>::setInfo(
    culong_t &a_mask,
    culong_t &a_flags
)
{
    xTEST_EQ(isValid(), true);
    xTEST_NA(a_mask);
    xTEST_NA(a_flags);

    BOOL blRes = ::SetHandleInformation(_handle, a_mask, a_flags);
    xTEST_DIFF(blRes, FALSE);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
