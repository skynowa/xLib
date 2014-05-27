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

    hRv = ::dup(_handle);
    xTEST_DIFF(error_value_t::get(), hRv);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
bool_t
CxHandleT<tagT>::_isValid_impl() const
{
    bool_t bRv = false;

    // compare with error handle value
    bool_t cond1 = (_handle != error_value_t::get());
    // handle value is negative
    bool_t cond2 = (_handle >  error_value_t::get());

    bRv = cond1 && cond2;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
void_t
CxHandleT<tagT>::_close_impl()
{
    int_t iRv = ::close(_handle);
    xTEST_DIFF(iRv, - 1);

    _handle = error_value_t::get();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
