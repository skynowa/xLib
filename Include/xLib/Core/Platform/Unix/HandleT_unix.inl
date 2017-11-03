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
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
native_handle_t
HandleT<tagT>::_dup_impl() const
{
    native_handle_t hRv = error_value_t::get();

    hRv = ::dup(_handle);
    xTEST_DIFF(error_value_t::get(), hRv);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
bool_t
HandleT<tagT>::_isValid_impl() const
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
HandleT<tagT>::_close_impl()
{
    int_t iRv = ::close(_handle);
    xTEST_DIFF(iRv, - 1);

    _handle = error_value_t::get();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
