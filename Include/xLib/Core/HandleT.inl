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
#include <xLib/Log/Trace.h>


xNAMESPACE_BEGIN2(xl, core)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
HandleT<T, valueT>::HandleT() :
    _handle( handle_policy_t::null() )
{
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
HandleT<T, valueT>::HandleT(
    const T &a_handle
) :
    _handle(a_handle)
{
    xTEST_NA(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
HandleT<T, valueT>::HandleT(
    const HandleT &a_handle
) :
    _handle( handle_policy_t::null() )
{
    xTEST_NA(a_handle);

    _handle = a_handle.dup();
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
HandleT<T, valueT>::~HandleT()
{
    close();

    xTRACE_FUNC;
    std::cout << xTRACE_VAR(_handle) << std::endl;
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    operators
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
HandleT<T, valueT> &
HandleT<T, valueT>::operator = (
    const T &a_handle
)
{
    xTEST_NA(a_handle);

    // Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(_handle == a_handle, *this);

    close();

    _handle = a_handle;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
HandleT<T, valueT> &
HandleT<T, valueT>::operator = (
    const HandleT &a_handle
)
{
    xTEST_NA(a_handle);

    xCHECK_RET(this == &a_handle, *this);

    close();

    _handle = a_handle.dup();
    xTEST_NA(_handle);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
T
HandleT<T, valueT>::get() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
void_t
HandleT<T, valueT>::set(
    const T &a_handle
)
{
    xTEST_NA(a_handle);

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
T
HandleT<T, valueT>::dup() const
{
    xCHECK_RET(!isValid(), handle_policy_t::null());

    return handle_policy_t::dup(_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
bool_t
HandleT<T, valueT>::isValid() const
{
    return handle_policy_t::isValid(_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
void_t
HandleT<T, valueT>::attach(
    const T &a_handle
)
{
    xTEST_NA(a_handle);
    xCHECK_DO(!isValid(), return);

    close();

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
T
HandleT<T, valueT>::detach()
{
    T hRv = _handle;

    _handle = handle_policy_t::null();

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T, HandlePolicyType valueT>
void_t
HandleT<T, valueT>::close()
{
    if ( !isValid() ) {
        _handle = handle_policy_t::null();
        return;
    }

    handle_policy_t::close(&_handle);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
