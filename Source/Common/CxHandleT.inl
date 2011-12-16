/**
 * \file  CxHandleT.inl
 * \brief handle
 */


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
    const TxHandle chHandle
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
    const TxHandle chHandle
)
{
    /*DEBUG*/xASSERT_DO(false == bIsValid(), TxErrorValue::hGet());
    /*DEBUG*///hHandle - n/a

    //Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(_m_hHandle == &chHandle, *this);

    bool bRes = bClose();
    /*DEBUG*/xASSERT_RET(true == bRes, *this);

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
    /*DEBUG*/xASSERT_DO(false == bIsValid(), TxErrorValue::hGet());
    /*DEBUG*///CxHandleT - n/a

    xCHECK_RET(this == &chHandle, *this);

    bool bRes = bClose();
    /*DEBUG*/xASSERT_RET(true == bRes, TxErrorValue::hGet());

    _m_hHandle = chHandle.hDuplicate();
    /*DEBUG*/xASSERT_RET(TxErrorValue::hGet() != _m_hHandle, TxErrorValue::hGet());

    return *this;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
CxHandleT<hvTag>::operator TxHandle() const {
    /*DEBUG*///???

    return _m_hHandle;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
TxHandle
CxHandleT<hvTag>::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bSet(
    const TxHandle chHandle
)
{
    /*DEBUG*/

    _m_hHandle = chHandle;

    return true;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
TxHandle
CxHandleT<hvTag>::hDuplicate() const {
    /*DEBUG*/xASSERT_RET(true == bIsValid(), TxErrorValue::hGet());

    TxHandle hRes = TxErrorValue::hGet();

#if defined(xOS_ENV_WIN)
    TxHandle hCurrentProcess = CxCurrentProcess::hGetHandle();

    BOOL blRes = ::DuplicateHandle(
                    hCurrentProcess, 
                    _m_hHandle, 
                    hCurrentProcess, 
                    &hRes, 
                    DUPLICATE_SAME_ACCESS, 
                    FALSE, 
                    DUPLICATE_SAME_ACCESS
    );
    /*DEBUG*/xASSERT_RET(FALSE != blRes, TxErrorValue::hGet());
#elif defined(xOS_ENV_UNIX)
    hRes = ::dup(_m_hHandle);
    /*DEBUG*/xASSERT_RET(TxErrorValue::hGet() != hRes, TxErrorValue::hGet());
#endif

    return hRes;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bIsValid() const {
    /*DEBUG*///n/a

    bool bRes = false;

#if defined(xOS_ENV_WIN)
    bool bCond1 = (reinterpret_cast<TxHandle>(0xCDCDCDCD) != _m_hHandle);   //created but not initialised
    bool bCond2 = (reinterpret_cast<TxHandle>(0xCCCCCCCC) != _m_hHandle);   //uninitialized locals in VC6 when you compile w/ /GZ
    bool bCond3 = (reinterpret_cast<TxHandle>(0xBAADF00D) != _m_hHandle);   //indicate an uninitialized variable
    bool bCond4 = (reinterpret_cast<TxHandle>(0xFDFDFDFD) != _m_hHandle);   //no man's land (normally outside of a process)
    bool bCond5 = (reinterpret_cast<TxHandle>(0xFEEEFEEE) != _m_hHandle);   //freed memory set by NT's heap manager
    bool bCond6 = (reinterpret_cast<TxHandle>(0xDDDDDDDD) != _m_hHandle);   //deleted
    bool bCond7 = (TxErrorValue::hGet()                   != _m_hHandle);   //compare with error handle value

    bRes = bCond1 && bCond2 && bCond3 && bCond4 && bCond5 && bCond6 && bCond7;
#elif defined(xOS_ENV_UNIX)
    bool bCond1 = (TxErrorValue::hGet()                   != _m_hHandle);   //compare with error handle value
    bool bCond2 = (TxErrorValue::hGet()                   <  _m_hHandle);   //handle value is negative

    bRes = bCond1 && bCond2;
#endif

    return bRes;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bAttach(
    const TxHandle chHandle
)
{
    /*DEBUG*/xASSERT_RET(true == bIsValid(), false);

    bool bRes = bClose();
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    _m_hHandle = chHandle;

    return true;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
TxHandle
CxHandleT<hvTag>::hDetach() {
    /*DEBUG*///n/a

    TxHandle hHandle = _m_hHandle;

    _m_hHandle = TxErrorValue::hGet();

    return hHandle;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bClose() {
    /*DEBUG*/// n/a

    xCHECK_DO(false == bIsValid(), _m_hHandle = TxErrorValue::hGet(); return true);

#if defined(xOS_ENV_WIN)
    BOOL blRes = ::CloseHandle(_m_hHandle);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif defined(xOS_ENV_UNIX)
    int  iRes  = ::close(_m_hHandle);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    _m_hHandle = TxErrorValue::hGet();

    return true;
}
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

template<EHandleValue hvTag>
ulong_t
CxHandleT<hvTag>::ulGetInformation() const {
    /*DEBUG*/xASSERT_RET(true == bIsValid(), 0UL);

    ulong_t ulFlags = 0UL;

    BOOL blRes = ::GetHandleInformation(_m_hHandle, &ulFlags);
    /*DEBUG*/xASSERT_RET(FALSE != blRes,   0UL);
    /*DEBUG*/xASSERT_RET(0UL   != ulFlags, 0UL);

    return ulFlags;
}

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bSetInformation(
    const ulong_t culMask,
    const ulong_t culFlags
)
{
    /*DEBUG*/xASSERT_RET(true == bIsValid(), false);
    /*DEBUG*///ulMask  - n/a
    /*DEBUG*///ulFlags - ????

    BOOL blRes = ::SetHandleInformation(_m_hHandle, culMask, culFlags);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bIsFlagInherit() const {
    /*DEBUG*/xASSERT_RET(true == bIsValid(), false);

    return (0UL != (ulGetInformation() & HANDLE_FLAG_INHERIT));
}

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bIsFlagProtectFromClose() const {
    /*DEBUG*/xASSERT_RET(true == bIsValid(), false);

    return (0UL != (ulGetInformation() & HANDLE_FLAG_PROTECT_FROM_CLOSE));
}

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bSetFlagInherit(
    const bool cbFlagInherit
)
{
    /*DEBUG*/xASSERT_RET(true == bIsValid(), false);

    return bSetInformation(HANDLE_FLAG_INHERIT, cbFlagInherit ? HANDLE_FLAG_INHERIT : 0);
}

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bSetFlagProtectFromClose(
    const bool cbFlagProtectFromClose
)
{
    /*DEBUG*/xASSERT_RET(true == bIsValid(), false);

    return bSetInformation(HANDLE_FLAG_PROTECT_FROM_CLOSE, cbFlagProtectFromClose ? HANDLE_FLAG_PROTECT_FROM_CLOSE : 0UL);
}

#endif
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
