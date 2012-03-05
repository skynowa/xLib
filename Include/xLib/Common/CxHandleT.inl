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
template<EHandleValue hvTag>
CxHandleT<hvTag>::CxHandleT() :
    _m_hHandle( TxErrorValue::hGet() )
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
/*explicit*/
CxHandleT<hvTag>::CxHandleT(
    const TxNativeHandle chHandle
) :
    _m_hHandle(chHandle)
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
/*explicit*/
CxHandleT<hvTag>::CxHandleT(
    const CxHandleT &chHandle
) :
    _m_hHandle( TxErrorValue::hGet() )
{
    /*DEBUG*/

    _m_hHandle = chHandle.hDuplicate();
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
CxHandleT<hvTag>::~CxHandleT() {
    /*DEBUG*/// n/a

    (void)bClose();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    operators
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<EHandleValue hvTag>
CxHandleT<hvTag> &
CxHandleT<hvTag>::operator = (
    const TxNativeHandle chHandle
)
{
    /////*DEBUG*/xASSERT_RET(false == bIsValid(), *this);
    /*DEBUG*///hHandle - n/a

    //Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(_m_hHandle == chHandle, *this);

    bool bRes = bClose();
    /////*DEBUG*/xASSERT_RET(true == bRes, *this);

    _m_hHandle = chHandle;

    return *this;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
CxHandleT<hvTag> &
CxHandleT<hvTag>::operator = (
    const CxHandleT &chHandle
)
{
    ///*DEBUG*/xASSERT_RET(false == bIsValid(), *this);
    /*DEBUG*///CxHandleT - n/a

    xCHECK_RET(this == &chHandle, *this);

    bool bRes = bClose();
    /////*DEBUG*/xASSERT_RET(true == bRes, *this);

    _m_hHandle = chHandle.hDuplicate();
    /*DEBUG*/// n/a;

    return *this;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
TxNativeHandle
CxHandleT<hvTag>::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bSet(
    const TxNativeHandle chHandle
)
{
    /*DEBUG*/

    _m_hHandle = chHandle;

    return true;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
TxNativeHandle
CxHandleT<hvTag>::hDuplicate() const {
    /*DEBUG*/// n/a
    xCHECK_RET(false == bIsValid(), TxErrorValue::hGet());

    TxNativeHandle hRes = TxErrorValue::hGet();

#if xOS_ENV_WIN
    TxNativeHandle hCurrentProcess = ::GetCurrentProcess();

    BOOL blRes = ::DuplicateHandle(
                    hCurrentProcess,
                    _m_hHandle,
                    hCurrentProcess,
                    &hRes,
                    DUPLICATE_SAME_ACCESS,
                    FALSE,
                    DUPLICATE_SAME_ACCESS
    );
    /////*DEBUG*/xASSERT_RET(FALSE != blRes, TxErrorValue::hGet());
#elif xOS_ENV_UNIX
    hRes = ::dup(_m_hHandle);
    /////*DEBUG*/xASSERT_RET(TxErrorValue::hGet() != hRes, TxErrorValue::hGet());
#endif

    return hRes;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bIsValid() const {
    /*DEBUG*///n/a

    bool bRes = false;

#if xOS_ENV_WIN
    bool bCond1 = (reinterpret_cast<TxNativeHandle>(0xCDCDCDCD) != _m_hHandle);   //created but not initialised
    bool bCond2 = (reinterpret_cast<TxNativeHandle>(0xCCCCCCCC) != _m_hHandle);   //uninitialized locals in VC6 when you compile w/ /GZ
    bool bCond3 = (reinterpret_cast<TxNativeHandle>(0xBAADF00D) != _m_hHandle);   //indicate an uninitialized variable
    bool bCond4 = (reinterpret_cast<TxNativeHandle>(0xFDFDFDFD) != _m_hHandle);   //no man's land (normally outside of a process)
    bool bCond5 = (reinterpret_cast<TxNativeHandle>(0xFEEEFEEE) != _m_hHandle);   //freed memory set by NT's heap manager
    bool bCond6 = (reinterpret_cast<TxNativeHandle>(0xDDDDDDDD) != _m_hHandle);   //deleted
    bool bCond7 = (TxErrorValue::hGet()                         != _m_hHandle);   //compare with error handle value

    bRes = bCond1 && bCond2 && bCond3 && bCond4 && bCond5 && bCond6 && bCond7;
#elif xOS_ENV_UNIX
    bool bCond1 = (TxErrorValue::hGet()                         != _m_hHandle);   //compare with error handle value
    bool bCond2 = (TxErrorValue::hGet()                         <  _m_hHandle);   //handle value is negative

    bRes = bCond1 && bCond2;
#endif

    return bRes;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bAttach(
    const TxNativeHandle chHandle
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(false == bIsValid(), true);

    bool bRes = bClose();
    /////*DEBUG*/xASSERT_RET(true == bRes, false);

    _m_hHandle = chHandle;

    return true;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
TxNativeHandle
CxHandleT<hvTag>::hDetach() {
    /*DEBUG*///n/a

    TxNativeHandle hHandle = _m_hHandle;

    _m_hHandle = TxErrorValue::hGet();

    return hHandle;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bClose() {
    /*DEBUG*/// n/a

    xCHECK_DO(false == bIsValid(), _m_hHandle = TxErrorValue::hGet(); return true);

#if xOS_ENV_WIN
    BOOL blRes = ::CloseHandle(_m_hHandle);
    /////*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int  iRes  = ::close(_m_hHandle);
    /////*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    _m_hHandle = TxErrorValue::hGet();

    return true;
}
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

template<EHandleValue hvTag>
ulong_t
CxHandleT<hvTag>::ulGetInformation() const {
    /////*DEBUG*/xASSERT_RET(true == bIsValid(), 0UL);

    DWORD ulFlags = 0UL;

    BOOL blRes = ::GetHandleInformation(_m_hHandle, &ulFlags);
    /////*DEBUG*/xASSERT_RET(FALSE != blRes,   0UL);
    /////*DEBUG*/xASSERT_RET(0UL   != ulFlags, 0UL);

    return ulFlags;
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bSetInformation(
    const ulong_t culMask,
    const ulong_t culFlags
)
{
    /////*DEBUG*/xASSERT_RET(true == bIsValid(), false);
    /*DEBUG*///ulMask  - n/a
    /*DEBUG*///ulFlags - ????

    BOOL blRes = ::SetHandleInformation(_m_hHandle, culMask, culFlags);
    /////*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}

#endif
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
