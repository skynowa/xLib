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

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag>::CxHandleT() :
    _m_hHandle( error_value_t::hGet() )
{
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag>::CxHandleT(
    const native_handle_t &a_chHandle
) :
    _m_hHandle(a_chHandle)
{
    xTEST_NA(a_chHandle);
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag>::CxHandleT(
    const CxHandleT &a_chHandle
) :
    _m_hHandle( error_value_t::hGet() )
{
    xTEST_NA(a_chHandle);

    _m_hHandle = a_chHandle.hDuplicate();
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag>::~CxHandleT() {
    vClose();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    operators
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag> &
CxHandleT<hvTag>::operator = (
    const native_handle_t &a_chHandle
)
{
    ////xTEST_EQ(false, bIsValid(), *this);
    xTEST_NA(a_chHandle);

    // Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(_m_hHandle == a_chHandle, *this);

    vClose();

    _m_hHandle = a_chHandle;

    return *this;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag> &
CxHandleT<hvTag>::operator = (
    const CxHandleT &a_chHandle
)
{
    //xTEST_EQ(false, bIsValid(), *this);
    xTEST_NA(a_chHandle);

    xCHECK_RET(this == &a_chHandle, *this);

    vClose();

    _m_hHandle = a_chHandle.hDuplicate();
    xTEST_NA(_m_hHandle);

    return *this;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
native_handle_t
CxHandleT<hvTag>::hGet() const {
    return _m_hHandle;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
void
CxHandleT<hvTag>::vSet(
    const native_handle_t &a_chHandle
)
{
    xTEST_NA(a_chHandle);

    _m_hHandle = a_chHandle;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
native_handle_t
CxHandleT<hvTag>::hDuplicate() const {
    xCHECK_RET(false == bIsValid(), error_value_t::hGet());

    native_handle_t hRv = error_value_t::hGet();

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
    ////xTEST_EQ(true == error_value_t::hGet() != hRv);
#endif

    return hRv;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
bool
CxHandleT<hvTag>::bIsValid() const {
    bool bRv = false;

#if   xOS_ENV_WIN
    bool bCond1 = (reinterpret_cast<native_handle_t>(0xCDCDCDCD) != _m_hHandle);   // created but not initialised
    bool bCond2 = (reinterpret_cast<native_handle_t>(0xCCCCCCCC) != _m_hHandle);   // uninitialized locals in VC6 when you compile w/ /GZ
    bool bCond3 = (reinterpret_cast<native_handle_t>(0xBAADF00D) != _m_hHandle);   // indicate an uninitialized variable
    bool bCond4 = (reinterpret_cast<native_handle_t>(0xFDFDFDFD) != _m_hHandle);   // no man's land (normally outside of a process)
    bool bCond5 = (reinterpret_cast<native_handle_t>(0xFEEEFEEE) != _m_hHandle);   // freed memory set by NT's heap manager
    bool bCond6 = (reinterpret_cast<native_handle_t>(0xDDDDDDDD) != _m_hHandle);   // deleted
    bool bCond7 = (error_value_t::hGet()                         != _m_hHandle);   // compare with error handle value

    bRv = bCond1 && bCond2 && bCond3 && bCond4 && bCond5 && bCond6 && bCond7;
#elif xOS_ENV_UNIX
    bool bCond1 = (error_value_t::hGet()                         != _m_hHandle);   // compare with error handle value
    bool bCond2 = (error_value_t::hGet()                         <  _m_hHandle);   // handle value is negative

    bRv = bCond1 && bCond2;
#endif

    return bRv;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
void
CxHandleT<hvTag>::vAttach(
    const native_handle_t &a_chHandle
)
{
    xTEST_NA(a_chHandle);
    xCHECK_DO(false == bIsValid(), return);

    vClose();

    _m_hHandle = a_chHandle;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
native_handle_t
CxHandleT<hvTag>::hDetach() {
    native_handle_t hHandle = _m_hHandle;

    _m_hHandle = error_value_t::hGet();

    return hHandle;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
void
CxHandleT<hvTag>::vClose() {
    xCHECK_DO(false == bIsValid(), _m_hHandle = error_value_t::hGet(); return);

#if   xOS_ENV_WIN
    BOOL blRes = ::CloseHandle(_m_hHandle);
    xUNUSED(blRes);

    ////xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::close(_m_hHandle);
    xUNUSED(iRv);
    ////xTEST_DIFF(- 1, iRv);
#endif

    _m_hHandle = error_value_t::hGet();
}
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

template<ExHandleValue hvTag>
ulong_t
CxHandleT<hvTag>::ulInfo() const {
    ////xTEST_EQ(true, bIsValid(), 0UL);

    DWORD dwFlags = 0UL;

    BOOL blRes = ::GetHandleInformation(_m_hHandle, &dwFlags);
    xUNUSED(blRes);

    ////xTEST_DIFF(FALSE, blRes);
    ////xTEST_DIFF(0UL,   ulFlags);

    return dwFlags;
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

template<ExHandleValue hvTag>
void
CxHandleT<hvTag>::vSetInfo(
    const ulong_t &a_culMask,
    const ulong_t &a_culFlags
)
{
    ////xTEST_EQ(true, bIsValid(), false);
    xTEST_NA(a_culMask);
    xTEST_NA(a_culFlags);

    BOOL blRes = ::SetHandleInformation(_m_hHandle, a_culMask, a_culFlags);
    xUNUSED(blRes);

    ////xTEST_DIFF(FALSE, blRes);
}

#endif
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
