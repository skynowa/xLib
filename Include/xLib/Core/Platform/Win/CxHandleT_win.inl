/**
 * \file  CxHandleT.inl
 * \brief handle
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>


xNAMESPACE_BEGIN2(xlib, core)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
native_handle_t
CxHandleT<tagT>::_duplicate_impl() const
{
    native_handle_t hRv = error_value_t::get();

    BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &hRv,
        DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
    xTEST_DIFF(blRes, FALSE);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
bool_t
CxHandleT<tagT>::_isValid_impl() const
{
    bool_t bRv = false;

    // created but not initialised
    bool_t cond1 = (_handle != reinterpret_cast<native_handle_t>(0xCDCDCDCD));
    // uninitialized locals in VC6 when you compile w/ /GZ
    bool_t cond2 = (_handle != reinterpret_cast<native_handle_t>(0xCCCCCCCC));
    // indicate an uninitialized variable
    bool_t cond3 = (_handle != reinterpret_cast<native_handle_t>(0xBAADF00D));
    // no man's land (normally outside of a process)
    bool_t cond4 = (_handle != reinterpret_cast<native_handle_t>(0xFDFDFDFD));
    // freed memory set by NT's heap manager
    bool_t cond5 = (_handle != reinterpret_cast<native_handle_t>(0xFEEEFEEE));
    // deleted
    bool_t cond6 = (_handle != reinterpret_cast<native_handle_t>(0xDDDDDDDD));
    // compare with error handle value
    bool_t cond7 = (_handle != error_value_t::get());

    bRv = cond1 && cond2 && cond3 && cond4 && cond5 && cond6 && cond7;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
void_t
CxHandleT<tagT>::_close_impl()
{
    BOOL blRes = ::CloseHandle(_handle);
    xTEST_DIFF(blRes, FALSE);

    _handle = error_value_t::get();
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
ulong_t
CxHandleT<tagT>::info() const
{
    xTEST_EQ(isValid(), true);

    DWORD flags = 0UL;

    BOOL blRes = ::GetHandleInformation(_handle, &flags);
    xTEST_DIFF(blRes, FALSE);
    xTEST_DIFF(flags, 0UL);

    return flags;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
void_t
CxHandleT<tagT>::setInfo(
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

xNAMESPACE_END2(xlib, core)
