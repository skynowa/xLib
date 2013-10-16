/**
 * \file  CxHandleT.inl
 * \brief handle
 */


#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag>::CxHandleT() :
    _m_hHandle( error_value_t::get() )
{
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag>::CxHandleT(
    cnative_handle_t &a_handle
) :
    _m_hHandle(a_handle)
{
    xTEST_NA(a_handle);
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag>::CxHandleT(
    const CxHandleT &a_handle
) :
    _m_hHandle( error_value_t::get() )
{
    xTEST_NA(a_handle);

    _m_hHandle = a_handle.duplicate();
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag>::~CxHandleT()
{
    close();
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    operators
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag> &
CxHandleT<hvTag>::operator = (
    cnative_handle_t &a_handle
)
{
    ////xTEST_EQ(false, isValid(), *this);
    xTEST_NA(a_handle);

    // Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(_m_hHandle == a_handle, *this);

    close();

    _m_hHandle = a_handle;

    return *this;
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag> &
CxHandleT<hvTag>::operator = (
    const CxHandleT &a_handle
)
{
    //xTEST_EQ(false, isValid(), *this);
    xTEST_NA(a_handle);

    xCHECK_RET(this == &a_handle, *this);

    close();

    _m_hHandle = a_handle.duplicate();
    xTEST_NA(_m_hHandle);

    return *this;
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
native_handle_t
CxHandleT<hvTag>::get() const
{
    return _m_hHandle;
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
void_t
CxHandleT<hvTag>::set(
    cnative_handle_t &a_handle
)
{
    xTEST_NA(a_handle);

    _m_hHandle = a_handle;
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
native_handle_t
CxHandleT<hvTag>::duplicate() const
{
    xCHECK_RET(!isValid(), error_value_t::get());

    native_handle_t hRv = error_value_t::get();

#if   xOS_ENV_WIN
    native_handle_t hCurrentProcess = ::GetCurrentProcess();

    BOOL blRes = ::DuplicateHandle(
                    hCurrentProcess,
                    _m_hHandle,
                    hCurrentProcess,
                    &hRv,
                    DUPLICATE_SAME_ACCESS,
                    FALSE,
                    DUPLICATE_SAME_ACCESS
    );
    xUNUSED(blRes);

    ////xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    hRv = ::dup(_m_hHandle);
    ////xTEST_EQ(error_value_t::hGet() != hRv);
#endif

    return hRv;
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
bool_t
CxHandleT<hvTag>::isValid() const
{
    bool_t bRv = false;

#if   xOS_ENV_WIN
    bool_t bCond1 = (reinterpret_cast<native_handle_t>(0xCDCDCDCD) != _m_hHandle);   // created but not initialised
    bool_t bCond2 = (reinterpret_cast<native_handle_t>(0xCCCCCCCC) != _m_hHandle);   // uninitialized locals in VC6 when you compile w/ /GZ
    bool_t bCond3 = (reinterpret_cast<native_handle_t>(0xBAADF00D) != _m_hHandle);   // indicate an uninitialized variable
    bool_t bCond4 = (reinterpret_cast<native_handle_t>(0xFDFDFDFD) != _m_hHandle);   // no man's land (normally outside of a process)
    bool_t bCond5 = (reinterpret_cast<native_handle_t>(0xFEEEFEEE) != _m_hHandle);   // freed memory set by NT's heap manager
    bool_t bCond6 = (reinterpret_cast<native_handle_t>(0xDDDDDDDD) != _m_hHandle);   // deleted
    bool_t bCond7 = (error_value_t::get()                          != _m_hHandle);   // compare with error handle value

    bRv = bCond1 && bCond2 && bCond3 && bCond4 && bCond5 && bCond6 && bCond7;
#elif xOS_ENV_UNIX
    bool_t bCond1 = (error_value_t::get()                          != _m_hHandle);   // compare with error handle value
    bool_t bCond2 = (error_value_t::get()                          <  _m_hHandle);   // handle value is negative

    bRv = bCond1 && bCond2;
#endif

    return bRv;
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
void_t
CxHandleT<hvTag>::attach(
    cnative_handle_t &a_handle
)
{
    xTEST_NA(a_handle);
    xCHECK_DO(!isValid(), return);

    close();

    _m_hHandle = a_handle;
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
native_handle_t
CxHandleT<hvTag>::detach() {
    native_handle_t hHandle = _m_hHandle;

    _m_hHandle = error_value_t::get();

    return hHandle;
}
//------------------------------------------------------------------------------
template<ExHandleValue hvTag>
void_t
CxHandleT<hvTag>::close() {
    xCHECK_DO(!isValid(), _m_hHandle = error_value_t::get(); return);

#if   xOS_ENV_WIN
    BOOL blRes = ::CloseHandle(_m_hHandle);
    xUNUSED(blRes);

    ////xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int_t iRv = ::close(_m_hHandle);
    xUNUSED(iRv);
    ////xTEST_DIFF(- 1, iRv);
#endif

    _m_hHandle = error_value_t::get();
}
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

template<ExHandleValue hvTag>
ulong_t
CxHandleT<hvTag>::info() const
{
    ////xTEST_EQ(true, isValid(), 0UL);

    DWORD dwFlags = 0UL;

    BOOL blRes = ::GetHandleInformation(_m_hHandle, &dwFlags);
    xUNUSED(blRes);

    ////xTEST_DIFF(FALSE, blRes);
    ////xTEST_DIFF(0UL,   ulFlags);

    return dwFlags;
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

template<ExHandleValue hvTag>
void_t
CxHandleT<hvTag>::setInfo(
    culong_t &a_mask,
    culong_t &a_flags
)
{
    ////xTEST_EQ(true, isValid(), false);
    xTEST_NA(a_mask);
    xTEST_NA(a_flags);

    BOOL blRes = ::SetHandleInformation(_m_hHandle, a_mask, a_flags);
    xUNUSED(blRes);

    ////xTEST_DIFF(FALSE, blRes);
}

#endif
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
