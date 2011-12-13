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
    _m_hHandle( TxErrorValue::get() )
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
    _m_hHandle( TxErrorValue::get() )
{
    /*DEBUG*/

    #if xTODO
        _m_hHandle = chHandle.hDuplicate(CxCurrentProcess::hGetHandle(), DUPLICATE_SAME_ACCESS, false, DUPLICATE_SAME_ACCESS);
    #endif
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
    /*DEBUG*/xASSERT_DO(false == bIsValid(), TxErrorValue::get());
    /*DEBUG*///hHandle - n/a

    //Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(this->_m_hHandle == &chHandle, *this);

    //TODO:
    bool bRes = bIsValid();
    if (true == bRes) {
        bRes = bClose();
        if (false == bRes) {
            /*DEBUG*/xASSERT(false);
        }
    }

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
    /*DEBUG*/xASSERT_DO(false == bIsValid(), TxErrorValue::get());
    /*DEBUG*///CxHandleT - n/a

    xCHECK_RET(this == &chHandle, *this);

    //TODO:
    bool bRes = bIsValid();
    if (true == bRes) {

        bRes = bClose();
        if (false == bRes) {
            /*DEBUG*/xASSERT(false);
        }
    }

    #if xTODO
        _m_hHandle = chHandle.hDuplicate(CxCurrentProcess::hGetHandle(), DUPLICATE_SAME_ACCESS, false, DUPLICATE_SAME_ACCESS);
        /*DEBUG*/xASSERT_RET(TxErrorValue::get() != _m_hHandle, TxErrorValue::get());
    #endif

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
bool
CxHandleT<hvTag>::bIsValid() const {
    /*DEBUG*///n/a

    bool bCond1 = (reinterpret_cast<TxHandle>(0xCDCDCDCD) != _m_hHandle); //Created but not initialised
    bool bCond2 = (reinterpret_cast<TxHandle>(0xCCCCCCCC) != _m_hHandle);    //Uninitialized locals in VC6 when you compile w/ /GZ
    bool bCond3 = (reinterpret_cast<TxHandle>(0xBAADF00D) != _m_hHandle);    //indicate an uninitialised variable
    bool bCond4 = (reinterpret_cast<TxHandle>(0xFDFDFDFD) != _m_hHandle);    //No man's land (normally outside of a process)
    bool bCond5 = (reinterpret_cast<TxHandle>(0xFEEEFEEE) != _m_hHandle);    //Freed memory set by NT's heap manager
    bool bCond6 = (reinterpret_cast<TxHandle>(0xDDDDDDDD) != _m_hHandle);    //Deleted
    bool bCond7 = (TxErrorValue::get()                    != _m_hHandle);

    return (true == bCond1) && (true == bCond2) && (true == bCond3) && (true == bCond4) &&
           (true == bCond5) && (true == bCond6) && (true == bCond7);
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

    _m_hHandle = TxErrorValue::get();

    return hHandle;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
TxHandle
CxHandleT<hvTag>::hDuplicate(
    const TxHandle chTargetProcess,
    const ulong_t  culDesiredAccess,
    const bool     cbInheritHandle /* = false*/,
    const ulong_t  culOptions      /* = 0*/
) const
{
    /*DEBUG*/xASSERT_RET(true == bIsValid(), TxErrorValue::get());

    TxHandle hRes = TxErrorValue::get();

#if defined(xOS_ENV_WIN)
    BOOL blRes = ::DuplicateHandle(CxCurrentProcess::hGetHandle(), _m_hHandle, chTargetProcess, &hRes, culDesiredAccess, cbInheritHandle, culOptions);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, TxErrorValue::get());
#elif defined(xOS_ENV_UNIX)
    //int iRes dup(int oldfd);
#endif

    return hRes;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bClose() {
    /*DEBUG*/// n/a

    xCHECK_RET(false == bIsValid(), true);

#if defined(xOS_ENV_WIN)
    BOOL blRes = ::CloseHandle(_m_hHandle);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif defined(xOS_ENV_UNIX)
    int iRes = ::close(_m_hHandle);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    _m_hHandle = TxErrorValue::get();

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

    return bSetInformation(HANDLE_FLAG_INHERIT, (true == cbFlagInherit) ? HANDLE_FLAG_INHERIT : 0);
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

    return bSetInformation(HANDLE_FLAG_PROTECT_FROM_CLOSE, (true == cbFlagProtectFromClose) ? HANDLE_FLAG_PROTECT_FROM_CLOSE : 0UL);
}

#endif
//---------------------------------------------------------------------------


/****************************************************************************
*    public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<EHandleValue hvTag>
/*static*/
bool
CxHandleT<hvTag>::bIsValid(
    const TxHandle chHandle
)
{
    /*DEBUG*/// n/a

    return (TxErrorValue::get() != chHandle);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
