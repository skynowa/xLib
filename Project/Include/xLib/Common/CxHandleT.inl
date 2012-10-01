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
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
/*explicit*/
CxHandleT<hvTag>::CxHandleT(
    const native_handle_t &chHandle
) :
    _m_hHandle(chHandle)
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
/*explicit*/
CxHandleT<hvTag>::CxHandleT(
    const CxHandleT &chHandle
) :
    _m_hHandle( error_value_t::hGet() )
{
    /*DEBUG*/

    _m_hHandle = chHandle.hDuplicate();
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag>::~CxHandleT() {
    /*DEBUG*/// n/a

    (bool)bClose();
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
    const native_handle_t &chHandle
)
{
    /////*DEBUG*/xTEST_EQ(false, bIsValid(), *this);
    /*DEBUG*///hHandle - n/a

    //Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(_m_hHandle == chHandle, *this);

    bool bRv = bClose();
    /////*DEBUG*/xTEST_EQ(true, bRv, *this);

    _m_hHandle = chHandle;

    return *this;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
CxHandleT<hvTag> &
CxHandleT<hvTag>::operator = (
    const CxHandleT &chHandle
)
{
    ///*DEBUG*/xTEST_EQ(false, bIsValid(), *this);
    /*DEBUG*///CxHandleT - n/a

    xCHECK_RET(this == &chHandle, *this);

    bool bRv = bClose();
    /////*DEBUG*/xTEST_EQ(true, bRv, *this);

    _m_hHandle = chHandle.hDuplicate();
    /*DEBUG*/// n/a;

    return *this;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
native_handle_t
CxHandleT<hvTag>::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
bool
CxHandleT<hvTag>::bSet(
    const native_handle_t &chHandle
)
{
    /*DEBUG*/

    _m_hHandle = chHandle;

    return true;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
native_handle_t
CxHandleT<hvTag>::hDuplicate() const {
    /*DEBUG*/// n/a
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
    /////*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    hRv = ::dup(_m_hHandle);
    /////*DEBUG*/xTEST_EQ(true == error_value_t::hGet() != hRv);
#endif

    return hRv;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
bool
CxHandleT<hvTag>::bIsValid() const {
    /*DEBUG*///n/a

    bool bRv = false;

#if   xOS_ENV_WIN
    bool bCond1 = (reinterpret_cast<native_handle_t>(0xCDCDCDCD) != _m_hHandle);   //created but not initialised
    bool bCond2 = (reinterpret_cast<native_handle_t>(0xCCCCCCCC) != _m_hHandle);   //uninitialized locals in VC6 when you compile w/ /GZ
    bool bCond3 = (reinterpret_cast<native_handle_t>(0xBAADF00D) != _m_hHandle);   //indicate an uninitialized variable
    bool bCond4 = (reinterpret_cast<native_handle_t>(0xFDFDFDFD) != _m_hHandle);   //no man's land (normally outside of a process)
    bool bCond5 = (reinterpret_cast<native_handle_t>(0xFEEEFEEE) != _m_hHandle);   //freed memory set by NT's heap manager
    bool bCond6 = (reinterpret_cast<native_handle_t>(0xDDDDDDDD) != _m_hHandle);   //deleted
    bool bCond7 = (error_value_t::hGet()                         != _m_hHandle);   //compare with error handle value

    bRv = bCond1 && bCond2 && bCond3 && bCond4 && bCond5 && bCond6 && bCond7;
#elif xOS_ENV_UNIX
    bool bCond1 = (error_value_t::hGet()                         != _m_hHandle);   //compare with error handle value
    bool bCond2 = (error_value_t::hGet()                         <  _m_hHandle);   //handle value is negative

    bRv = bCond1 && bCond2;
#endif

    return bRv;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
bool
CxHandleT<hvTag>::bAttach(
    const native_handle_t &chHandle
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(false == bIsValid(), true);

    bool bRv = bClose();
    /////*DEBUG*/xTEST_EQ(true, bRv);

    _m_hHandle = chHandle;

    return true;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
native_handle_t
CxHandleT<hvTag>::hDetach() {
    /*DEBUG*///n/a

    native_handle_t hHandle = _m_hHandle;

    _m_hHandle = error_value_t::hGet();

    return hHandle;
}
//---------------------------------------------------------------------------
template<ExHandleValue hvTag>
bool
CxHandleT<hvTag>::bClose() {
    /*DEBUG*/// n/a

    xCHECK_DO(false == bIsValid(), _m_hHandle = error_value_t::hGet(); return true);

#if   xOS_ENV_WIN
    BOOL blRes = ::CloseHandle(_m_hHandle);
    /////*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int  iRv  = ::close(_m_hHandle);
    /////*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif

    _m_hHandle = error_value_t::hGet();

    return true;
}
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

template<ExHandleValue hvTag>
ulong_t
CxHandleT<hvTag>::ulGetInfo() const {
    /////*DEBUG*/xTEST_EQ(true, bIsValid(), 0UL);

    DWORD dwFlags = 0UL;

    BOOL blRes = ::GetHandleInformation(_m_hHandle, &dwFlags);
    /////*DEBUG*/xTEST_DIFF(FALSE, blRes);
    /////*DEBUG*/xTEST_DIFF(0UL,   ulFlags);

    return dwFlags;
}

#endif
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

template<ExHandleValue hvTag>
bool
CxHandleT<hvTag>::bSetInfo(
    const ulong_t &culMask,
    const ulong_t &culFlags
)
{
    /////*DEBUG*/xTEST_EQ(true, bIsValid(), false);
    /*DEBUG*///ulMask  - n/a
    /*DEBUG*///ulFlags - ????

    BOOL blRes = ::SetHandleInformation(_m_hHandle, culMask, culFlags);
    /////*DEBUG*/xTEST_DIFF(FALSE, blRes);

    return true;
}

#endif
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
