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

#if   xENV_WIN
    #include "Platform/Win/HandleT_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/HandleT_unix.inl"
#endif


xNAMESPACE_BEGIN2(xl, core)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
HandleT<T, valueT>::HandleT() :
    _handle( error_value_t::get() )
{
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
HandleT<T, valueT>::HandleT(
    const T &a_handle
) :
    _handle(a_handle)
{
    xTEST_NA(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
HandleT<T, valueT>::HandleT(
    const HandleT &a_handle
) :
    _handle( error_value_t::get() )
{
    xTEST_NA(a_handle);

    _handle = a_handle.dup();
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
HandleT<T, valueT>::~HandleT()
{
    close();
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    operators
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
HandleT<T, valueT> &
HandleT<T, valueT>::operator = (
    const T &a_handle
)
{
    xTEST_EQ(isValid(), false);
    xTEST_NA(a_handle);

    // Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(_handle == a_handle, *this);

    close();

    _handle = a_handle;

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
HandleT<T, valueT> &
HandleT<T, valueT>::operator = (
    const HandleT &a_handle
)
{
    xTEST_EQ(isValid(), false);
    xTEST_NA(a_handle);

    xCHECK_RET(this == &a_handle, *this);

    close();

    _handle = a_handle.dup();
    xTEST_NA(_handle);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
T
HandleT<T, valueT>::get() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
void_t
HandleT<T, valueT>::set(
    const T &a_handle
)
{
    xTEST_NA(a_handle);

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
T
HandleT<T, valueT>::dup() const
{
    xCHECK_RET(!isValid(), error_value_t::get());

    return _dup_impl();
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
bool_t
HandleT<T, valueT>::isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
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
template<typename T, ExHandleValue valueT>
T
HandleT<T, valueT>::detach()
{
    T hRv = _handle;

    _handle = error_value_t::get();

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<typename T, ExHandleValue valueT>
void_t
HandleT<T, valueT>::close()
{
    xCHECK_DO(!isValid(), _handle = error_value_t::get(); return);

    _close_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
