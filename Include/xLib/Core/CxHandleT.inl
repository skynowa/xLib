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


xNAMESPACE2_BEGIN(xlib, core)

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

    native_handle_t hRv = error_value_t::get();

#if   xENV_WIN
    BOOL blRes = ::DuplicateHandle(::GetCurrentProcess(), _handle, ::GetCurrentProcess(), &hRv,
        DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
    xTEST_DIFF(FALSE, blRes);
#elif xENV_UNIX
    hRv = ::dup(_handle);
    xTEST_DIFF(error_value_t::get(), hRv);
#endif

    return hRv;
}
//-------------------------------------------------------------------------------------------------
template<ExHandleValue tagT>
bool_t
CxHandleT<tagT>::isValid() const
{
    bool_t bRv = false;

#if   xENV_WIN
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
#elif xENV_UNIX
    // compare with error handle value
    bool_t cond1 = (_handle != error_value_t::get());
    // handle value is negative
    bool_t cond2 = (_handle >  error_value_t::get());

    bRv = cond1 && cond2;
#endif

    return bRv;
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

#if   xENV_WIN
    BOOL blRes = ::CloseHandle(_handle);
    xTEST_DIFF(FALSE, blRes);
#elif xENV_UNIX
    int_t iRv = ::close(_handle);
    xTEST_DIFF(iRv, - 1);
#endif

    _handle = error_value_t::get();
}
//-------------------------------------------------------------------------------------------------
#if xENV_WIN

template<ExHandleValue tagT>
ulong_t
CxHandleT<tagT>::info() const
{
    xTEST_EQ(isValid(), true);

    DWORD flags = 0UL;

    BOOL blRes = ::GetHandleInformation(_handle, &flags);
    xTEST_DIFF(FALSE, blRes);
    xTEST_DIFF(0UL,   flags);

    return flags;
}

#endif
//-------------------------------------------------------------------------------------------------
#if xENV_WIN

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
    xTEST_DIFF(FALSE, blRes);
}

#endif
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, core)
