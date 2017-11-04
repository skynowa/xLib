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
template<typename T, ExHandlePolicyType valueT>
T
HandleT<T, valueT>::_dup_impl() const
{
    T hRv = handle_policy_t::null();

    hRv = ::dup(_handle);
    xTEST_DIFF(handle_policy_t::null(), hRv);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandlePolicyType valueT>
bool_t
HandleT<T, valueT>::_isValid_impl() const
{
    bool_t bRv = false;

    // compare with error handle value
    bool_t cond1 = (_handle != handle_policy_t::null());
    // handle value is negative
    bool_t cond2 = (_handle >  handle_policy_t::null());

    bRv = cond1 && cond2;

    return bRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandlePolicyType valueT>
void_t
HandleT<T, valueT>::_close_impl()
{
    int_t iRv = ::close(_handle);
    xTEST_DIFF(iRv, - 1);

    _handle = handle_policy_t::null();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
