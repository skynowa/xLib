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

#if   xENV_WIN
    #include "Platform/Win/CxHandleT_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxHandleT_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxHandleT_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxHandleT_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, core)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
CxHandleT<tagT>::CxHandleT() :
    _handle( error_value_t::get() )
{
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
CxHandleT<tagT>::CxHandleT(
    cnative_handle_t &a_handle
) :
    _handle(a_handle)
{
    xTEST_NA(a_handle);
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
CxHandleT<tagT>::CxHandleT(
    const CxHandleT &a_handle
) :
    _handle( error_value_t::get() )
{
    xTEST_NA(a_handle);

    _handle = a_handle.duplicate();
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
CxHandleT<tagT>::~CxHandleT()
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
CxHandleT<tagT> &
CxHandleT<tagT>::operator = (
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
CxHandleT<tagT> &
CxHandleT<tagT>::operator = (
    const CxHandleT &a_handle
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
CxHandleT<tagT>::get() const
{
    return _handle;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
void_t
CxHandleT<tagT>::set(
    cnative_handle_t &a_handle
)
{
    xTEST_NA(a_handle);

    _handle = a_handle;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
native_handle_t
CxHandleT<tagT>::duplicate() const
{
    xCHECK_RET(!isValid(), error_value_t::get());

    return _duplicate_impl();
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
bool_t
CxHandleT<tagT>::isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
void_t
CxHandleT<tagT>::attach(
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
CxHandleT<tagT>::detach()
{
    native_handle_t hRv = _handle;

    _handle = error_value_t::get();

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
void_t
CxHandleT<tagT>::close()
{
    xCHECK_DO(!isValid(), _handle = error_value_t::get(); return);

    _close_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
