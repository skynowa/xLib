/**
 * \file  CxHandleT.inl
 * \brief handle
 */


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<EHandleValue hvTag>
CxHandleT<hvTag>::CxHandleT() :
    _m_hHandle( TxFailValue::get() )
{
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
/*explicit*/
CxHandleT<hvTag>::CxHandleT(
    const HANDLE chHandle
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
    _m_hHandle( TxFailValue::get() )
{
    /*DEBUG*/

    _m_hHandle = chHandle.hDuplicate(hGetCurrentProcess(), DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
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
    const HANDLE chHandle
)
{
    /*DEBUG*/xASSERT_DO(FALSE == bIsValid(), TxFailValue::get());
    /*DEBUG*///hHandle - n/a

    //Try m_Handle.Attach(other.Detach(), if you got an assertion here.

    xCHECK_RET(this->_m_hHandle == &chHandle, *this);

    //TODO:
    BOOL bRes = bIsValid();
    if (TRUE == bRes) {
        bRes = bClose();
        if (FALSE == bRes) {
            /*DEBUG*/xASSERT(FALSE);
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
    /*DEBUG*/xASSERT_DO(FALSE == bIsValid(), TxFailValue::get());
    /*DEBUG*///CxHandleT - n/a

    xCHECK_RET(this == &chHandle, *this);

    //TODO:
    BOOL bRes = bIsValid();
    if (TRUE == bRes) {

        bRes = bClose();
        if (FALSE == bRes) {
            /*DEBUG*/xASSERT(FALSE);
        }
    }

    _m_hHandle = chHandle.hDuplicate(hGetCurrentProcess(), DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
    /*DEBUG*/xASSERT_RET(TxFailValue::get() != _m_hHandle, TxFailValue::get());

    return *this;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
CxHandleT<hvTag>::operator HANDLE() const {
    /*DEBUG*///???

    return _m_hHandle;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
HANDLE
CxHandleT<hvTag>::hGet() const {
    /*DEBUG*/

    return _m_hHandle;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bSet(
    const HANDLE chHandle
)
{
    /*DEBUG*/

    _m_hHandle = chHandle;

    return TRUE;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bIsValid() const {
    /*DEBUG*///n/a

    bool bCond1 = (reinterpret_cast<HANDLE>(0xCDCDCDCD) != _m_hHandle); //Created but not initialised
    bool bCond2 = (reinterpret_cast<HANDLE>(0xCCCCCCCC) != _m_hHandle);    //Uninitialized locals in VC6 when you compile w/ /GZ
    bool bCond3 = (reinterpret_cast<HANDLE>(0xBAADF00D) != _m_hHandle);    //indicate an uninitialised variable
    bool bCond4 = (reinterpret_cast<HANDLE>(0xFDFDFDFD) != _m_hHandle);    //No man's land (normally outside of a process)
    bool bCond5 = (reinterpret_cast<HANDLE>(0xFEEEFEEE) != _m_hHandle);    //Freed memory set by NT's heap manager
    bool bCond6 = (reinterpret_cast<HANDLE>(0xDDDDDDDD) != _m_hHandle);    //Deleted
    bool bCond7 = (TxFailValue::get()                   != _m_hHandle);

    return (true == bCond1) && (true == bCond2) && (true == bCond3) && (true == bCond4) &&
           (true == bCond5) && (true == bCond6) && (true == bCond7);
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bAttach(
    const HANDLE chHandle
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    BOOL bRes = bClose();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_hHandle = chHandle;

    return TRUE;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
HANDLE
CxHandleT<hvTag>::hDetach() {
    /*DEBUG*///n/a

    HANDLE hHandle = _m_hHandle;

    _m_hHandle = TxFailValue::get();

    return hHandle;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bClose() {
    /*DEBUG*/// n/a

    xCHECK_RET(FALSE == bIsValid(), TRUE);

    BOOL bRes = ::CloseHandle(_m_hHandle);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    _m_hHandle = TxFailValue::get();

    return TRUE;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
ULONG
CxHandleT<hvTag>::ulGetInformation() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0UL);

    ULONG ulFlags = 0UL;

    BOOL bRes = ::GetHandleInformation(_m_hHandle, &ulFlags);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,    0UL);
    /*DEBUG*/xASSERT_RET(0UL   != ulFlags, 0UL);

    return ulFlags;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bSetInformation(
    const ULONG culMask,
    const ULONG culFlags
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
    /*DEBUG*///ulMask  - n/a
    /*DEBUG*///ulFlags - ????

    BOOL bRes = ::SetHandleInformation(_m_hHandle, culMask, culFlags);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bIsFlagInherit() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    return 0UL != (ulGetInformation() & HANDLE_FLAG_INHERIT);
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bIsFlagProtectFromClose() const {
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    return 0UL != (ulGetInformation() & HANDLE_FLAG_PROTECT_FROM_CLOSE);
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bSetFlagInherit(
    const BOOL cbFlagInherit
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    return bSetInformation(HANDLE_FLAG_INHERIT, (TRUE == cbFlagInherit) ? HANDLE_FLAG_INHERIT : 0);
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bSetFlagProtectFromClose(
    const BOOL cbFlagProtectFromClose
)
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

    return bSetInformation(HANDLE_FLAG_PROTECT_FROM_CLOSE, (TRUE == cbFlagProtectFromClose) ? HANDLE_FLAG_PROTECT_FROM_CLOSE : 0UL);
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
HANDLE
CxHandleT<hvTag>::hDuplicate(
    const HANDLE chTargetProcess,
    const ULONG  culDesiredAccess,
    const BOOL   cbInheritHandle /* = FALSE*/,
    const ULONG  culOptions      /* = 0*/
) const
{
    /*DEBUG*/xASSERT_RET(FALSE != bIsValid(), TxFailValue::get());

    HANDLE hRes = TxFailValue::get();

    BOOL bRes = ::DuplicateHandle(hGetCurrentProcess(), _m_hHandle, chTargetProcess, &hRes, culDesiredAccess, cbInheritHandle, culOptions);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, TxFailValue::get());

    return hRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
template<EHandleValue hvTag>
const HANDLE
CxHandleT<hvTag>::_ms_chCurrProcessHandle = (HANDLE)- 1;
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
/*static*/
HANDLE
CxHandleT<hvTag>::hGetCurrentProcess() {
    /*DEBUG*///n/a

    HANDLE hRes = NULL;

#if xDEPRECIATE
    hRes = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, CxProcess::ulGetCurrId());
#else
    hRes = ::GetCurrentProcess();
#endif
    /*DEBUG*/xASSERT_RET(_ms_chCurrProcessHandle == hRes, NULL);

    return hRes;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
/*static*/
BOOL
CxHandleT<hvTag>::bIsValid(
    const HANDLE chHandle
)
{
    /*DEBUG*/// n/a

    return TxFailValue::get() != chHandle;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
