/****************************************************************************
* Class name:  CxHandle
* Description: handle
* File name:   CxHandle.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.01.2010 14:12:26
*
*****************************************************************************/


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxHandleT ()
template<EHandleValue hvTag>
CxHandleT<hvTag>::CxHandleT() :
	_m_bRes   (FALSE),
    _m_hHandle( FailValue::get() )
{
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: CxHandleT ()
template<EHandleValue hvTag>
/*explicit*/
CxHandleT<hvTag>::CxHandleT(
    const HANDLE chHandle
) :
    _m_bRes   (FALSE),
	_m_hHandle(chHandle)
{
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: CxHandleT ()
template<EHandleValue hvTag>
/*explicit*/
CxHandleT<hvTag>::CxHandleT(
    const CxHandleT &chHandle
) :
    _m_bRes   (FALSE),
	_m_hHandle( FailValue::get() )
{
	/*DEBUG*/

	_m_hHandle = chHandle.hDuplicate(hGetCurrentProcess(), DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
}
//---------------------------------------------------------------------------
//DONE: ~CxHandleT ()
template<EHandleValue hvTag>
CxHandleT<hvTag>::~CxHandleT() {
	/*DEBUG*/// n/a

	_m_bRes = bClose();
	/*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    operators
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: operator = ()
template<EHandleValue hvTag>
CxHandleT<hvTag> &
CxHandleT<hvTag>::operator = (
    const HANDLE chHandle
)
{
	/*DEBUG*/xASSERT_DO(FALSE == bIsValid(), FailValue::get());
	/*DEBUG*///hHandle - n/a

	//Try m_Handle.Attach(other.Detach(), if you got an assertion here.

	xCHECK_RET(this->_m_hHandle == &chHandle, *this);

	//TODO:
	_m_bRes = bIsValid();
	if (TRUE == _m_bRes) {
    	_m_bRes = bClose();
		if (FALSE == _m_bRes) {
			/*DEBUG*/xASSERT(FALSE);
		}
	}

	_m_hHandle = chHandle;
	
	return *this;
}
//---------------------------------------------------------------------------
//DONE: operator = ()
template<EHandleValue hvTag>
CxHandleT<hvTag> &
CxHandleT<hvTag>::operator = (
	const CxHandleT &chHandle
)
{
	/*DEBUG*/xASSERT_DO(FALSE == bIsValid(), FailValue::get());
	/*DEBUG*///CxHandleT - n/a

	xCHECK_RET(this == &chHandle, *this);

	//TODO:
	_m_bRes = bIsValid();
	if (TRUE == _m_bRes) {

		_m_bRes = bClose();
		if (FALSE == _m_bRes) {
			/*DEBUG*/xASSERT(FALSE);
		}
	}

	_m_hHandle = chHandle.hDuplicate(hGetCurrentProcess(), DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
	/*DEBUG*/xASSERT_RET(FailValue::get() != _m_hHandle, FailValue::get());
    
	return *this;
}
//---------------------------------------------------------------------------
//DONE: operator HANDLE ()
template<EHandleValue hvTag>
CxHandleT<hvTag>::operator HANDLE() const {
	/*DEBUG*///???

	return _m_hHandle;
}
//---------------------------------------------------------------------------
//TODO: ()
template<EHandleValue hvTag>
HANDLE
CxHandleT<hvTag>::hGet() const {
	/*DEBUG*/

	return _m_hHandle;
}
//---------------------------------------------------------------------------
//TODO: ()
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
//DONE: bIsValid ()
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bIsValid() const {
	/*DEBUG*///n/a

	BOOL bCond1 = (reinterpret_cast<HANDLE>(0xCDCDCDCD) != _m_hHandle); //Created but not initialised
	BOOL bCond2 = (reinterpret_cast<HANDLE>(0xCCCCCCCC) != _m_hHandle);	//Uninitialized locals in VC6 when you compile w/ /GZ
	BOOL bCond3 = (reinterpret_cast<HANDLE>(0xBAADF00D) != _m_hHandle);	//indicate an uninitialised variable
	BOOL bCond4 = (reinterpret_cast<HANDLE>(0xFDFDFDFD) != _m_hHandle);	//No man's land (normally outside of a process)
	BOOL bCond5 = (reinterpret_cast<HANDLE>(0xFEEEFEEE) != _m_hHandle);	//Freed memory set by NT's heap manager
	BOOL bCond6 = (reinterpret_cast<HANDLE>(0xDDDDDDDD) != _m_hHandle);	//Deleted
	BOOL bCond7 = (FailValue::get()                     != _m_hHandle);

	return (TRUE == bCond1) && (TRUE == bCond2) && (TRUE == bCond3) && (TRUE == bCond4) && 
           (TRUE == bCond5) && (TRUE == bCond6) && (TRUE == bCond7);
}
//---------------------------------------------------------------------------
//DONE: bAttach ()
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bAttach(
    const HANDLE chHandle
)
{
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

	_m_bRes = bClose();
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_hHandle = chHandle;

	return TRUE;

	/*
	BOOL CxFile::bAttach(HANDLE hHandle) {
		//n/a

		_m_bRes  = bClose();
		_m_hFile = hHandle;

		return TRUE;
	}
	*/
}
//---------------------------------------------------------------------------
//DONE: hDetach ()
template<EHandleValue hvTag>
HANDLE
CxHandleT<hvTag>::hDetach() {
	/*DEBUG*///n/a

	HANDLE hHandle = _m_hHandle;

	_m_hHandle = FailValue::get();

	return hHandle;

	/*
	HANDLE CxFile::bDetach() {
		//n/a

		HANDLE hFile = _m_hFile;
		_m_hFile = INVALID_HANDLE_VALUE;

		return hFile;
	}
	*/
}
//---------------------------------------------------------------------------
//DONE: bClose ()
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bClose() {
	/*DEBUG*/// n/a

	xCHECK_RET(FALSE == bIsValid(), TRUE);

	_m_bRes = ::CloseHandle(_m_hHandle);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	_m_hHandle = FailValue::get();
    
	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: ulGetInformation (Retrieves certain properties of an object handle)
template<EHandleValue hvTag>
ULONG
CxHandleT<hvTag>::ulGetInformation() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

	ULONG ulFlags = 0;

	_m_bRes = ::GetHandleInformation(_m_hHandle, &ulFlags);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, 0);
	/*DEBUG*/xASSERT_RET(0     != ulFlags, 0);

	return ulFlags;
}
//---------------------------------------------------------------------------
//DONE: bSetInformation ()
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

	_m_bRes = ::SetHandleInformation(_m_hHandle, culMask, culFlags);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsFlagInherit ()
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bIsFlagInherit() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

	return 0 != (ulGetInformation() & HANDLE_FLAG_INHERIT);
}
//---------------------------------------------------------------------------
//DONE: bIsFlagProtectFromClose ()
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bIsFlagProtectFromClose() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

	return 0 != (ulGetInformation() & HANDLE_FLAG_PROTECT_FROM_CLOSE);
}
//---------------------------------------------------------------------------
//DONE: bSetFlagInherit ()
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
//DONE: bSetFlagProtectFromClose ()
template<EHandleValue hvTag>
BOOL
CxHandleT<hvTag>::bSetFlagProtectFromClose(
    const BOOL cbFlagProtectFromClose
)
{
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

	return bSetInformation(HANDLE_FLAG_PROTECT_FROM_CLOSE, (TRUE == cbFlagProtectFromClose) ? HANDLE_FLAG_PROTECT_FROM_CLOSE : 0);
}
//---------------------------------------------------------------------------
//DONE: hDuplicate (Duplicates an object handle)
template<EHandleValue hvTag>
HANDLE
CxHandleT<hvTag>::hDuplicate(
	const HANDLE chTargetProcess,
	const ULONG  culDesiredAccess,
	const BOOL   cbInheritHandle/* = FALSE*/,
	const ULONG  culOptions/* = 0*/
) const
{
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FailValue::get());

	HANDLE hRes = FailValue::get();

	_m_bRes = ::DuplicateHandle(hGetCurrentProcess(), _m_hHandle, chTargetProcess, &hRes, culDesiredAccess, cbInheritHandle, culOptions);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FailValue::get());

	return hRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: static
template<EHandleValue hvTag>
const HANDLE
CxHandleT<hvTag>::_ms_chCurrProcessHandle = (HANDLE)- 1;
//---------------------------------------------------------------------------
//DONE: hGetCurrent (Retrieves a pseudo handle for the current process)
template<EHandleValue hvTag>
/*static*/
HANDLE
CxHandleT<hvTag>::hGetCurrentProcess() {
	/*DEBUG*///n/a

	HANDLE hRes = NULL;

	hRes = ::GetCurrentProcess();
    ////hRes = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, CxProcess::ulGetCurrId());
    /*DEBUG*/xASSERT_RET(_ms_chCurrProcessHandle == hRes, NULL);

	return hRes;
}
//---------------------------------------------------------------------------
//DONE: bIsValid (is valid)
template<EHandleValue hvTag>
/*static*/
BOOL
CxHandleT<hvTag>::bIsValid(
	const HANDLE chHandle
)
{
	/*DEBUG*/// n/a

	return FailValue::get() != chHandle;
}
//---------------------------------------------------------------------------
