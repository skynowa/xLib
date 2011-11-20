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

    _m_hHandle = chHandle.hDuplicate(hGetCurrentProcess(), DUPLICATE_SAME_ACCESS, false, DUPLICATE_SAME_ACCESS);
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
    /*DEBUG*/xASSERT_DO(false == bIsValid(), TxFailValue::get());
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
    /*DEBUG*/xASSERT_DO(false == bIsValid(), TxFailValue::get());
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

    _m_hHandle = chHandle.hDuplicate(hGetCurrentProcess(), DUPLICATE_SAME_ACCESS, false, DUPLICATE_SAME_ACCESS);
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
bool
CxHandleT<hvTag>::bSet(
    const HANDLE chHandle
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
bool
CxHandleT<hvTag>::bAttach(
    const HANDLE chHandle
)
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    bool bRes = bClose();
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    _m_hHandle = chHandle;

    return true;
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
bool
CxHandleT<hvTag>::bClose() {
    /*DEBUG*/// n/a

    xCHECK_RET(false == bIsValid(), true);

    BOOL bRes = ::CloseHandle(_m_hHandle);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);

    _m_hHandle = TxFailValue::get();

    return true;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
ULONG
CxHandleT<hvTag>::ulGetInformation() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), 0UL);

    ULONG ulFlags = 0UL;

    bool bRes = ::GetHandleInformation(_m_hHandle, &ulFlags);
    /*DEBUG*/xASSERT_RET(false != bRes,    0UL);
    /*DEBUG*/xASSERT_RET(0UL   != ulFlags, 0UL);

    return ulFlags;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bSetInformation(
    const ULONG culMask,
    const ULONG culFlags
)
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);
    /*DEBUG*///ulMask  - n/a
    /*DEBUG*///ulFlags - ????

    bool bRes = ::SetHandleInformation(_m_hHandle, culMask, culFlags);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bIsFlagInherit() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    return 0UL != (ulGetInformation() & HANDLE_FLAG_INHERIT);
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bIsFlagProtectFromClose() const {
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    return 0UL != (ulGetInformation() & HANDLE_FLAG_PROTECT_FROM_CLOSE);
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bSetFlagInherit(
    const bool cbFlagInherit
)
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    return bSetInformation(HANDLE_FLAG_INHERIT, (true == cbFlagInherit) ? HANDLE_FLAG_INHERIT : 0);
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
bool
CxHandleT<hvTag>::bSetFlagProtectFromClose(
    const bool cbFlagProtectFromClose
)
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), false);

    return bSetInformation(HANDLE_FLAG_PROTECT_FROM_CLOSE, (true == cbFlagProtectFromClose) ? HANDLE_FLAG_PROTECT_FROM_CLOSE : 0UL);
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
HANDLE
CxHandleT<hvTag>::hDuplicate(
    const HANDLE chTargetProcess,
    const ULONG  culDesiredAccess,
    const bool   cbInheritHandle /* = false*/,
    const ULONG  culOptions      /* = 0*/
) const
{
    /*DEBUG*/xASSERT_RET(false != bIsValid(), TxFailValue::get());

    HANDLE hRes = TxFailValue::get();

    bool bRes = ::DuplicateHandle(hGetCurrentProcess(), _m_hHandle, chTargetProcess, &hRes, culDesiredAccess, cbInheritHandle, culOptions);
    /*DEBUG*/xASSERT_RET(false != bRes, TxFailValue::get());

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
    hRes = ::OpenProcess(PROCESS_ALL_ACCESS, false, CxProcess::ulGetCurrId());
#else
    hRes = ::GetCurrentProcess();
#endif
    /*DEBUG*/xASSERT_RET(_ms_chCurrProcessHandle == hRes, NULL);

    return hRes;
}
//---------------------------------------------------------------------------
template<EHandleValue hvTag>
/*static*/
bool
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
