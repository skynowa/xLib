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
    #if   xENV_LINUX
        #include "Platform/Unix/HandleT_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/HandleT_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/HandleT_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, core)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
HandleT<tagT>::HandleT() :
    _handle( error_value_t::get() )
{
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
HandleT<tagT>::HandleT(
    cnative_handle_t &a_handle
) :
    _handle(a_handle)
{
    xTEST_NA(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
HandleT<tagT>::HandleT(
    const HandleT &a_handle
) :
    _handle( error_value_t::get() )
{
    xTEST_NA(a_handle);

    _handle = a_handle.duplicate();
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
HandleT<tagT>::~HandleT()
{
    close();
}
//-------------------------------------------------------------------------------------------------


/*******************************************************************************
*    operators
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
HandleT<tagT> &
HandleT<tagT>::operator = (
    cnative_handle_t &a_handle
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
template<ExHandleValue tagT>
HandleT<tagT> &
HandleT<tagT>::operator = (
    const HandleT &a_handle
)
{
    xTEST_EQ(isValid(), false);
    xTEST_NA(a_handle);

    xCHECK_RET(this == &a_handle, *this);

    close();

    _handle = a_handle.duplicate();
    xTEST_NA(_handle);

    return *this;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
native_handle_t
HandleT<tagT>::get() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
void_t
HandleT<tagT>::set(
    cnative_handle_t &a_handle
)
{
    xTEST_NA(a_handle);

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
native_handle_t
HandleT<tagT>::duplicate() const
{
    xCHECK_RET(!isValid(), error_value_t::get());

    return _duplicate_impl();
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
bool_t
HandleT<tagT>::isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
void_t
HandleT<tagT>::attach(
    cnative_handle_t &a_handle
)
{
    xTEST_NA(a_handle);
    xCHECK_DO(!isValid(), return);

    close();

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
native_handle_t
HandleT<tagT>::detach()
{
    native_handle_t hRv = _handle;

    _handle = error_value_t::get();

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
void_t
HandleT<tagT>::close()
{
    xCHECK_DO(!isValid(), _handle = error_value_t::get(); return);

    _close_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
