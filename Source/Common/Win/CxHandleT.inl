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
template<HANDLE hFailValueT>
CxHandleT<hFailValueT>::CxHandleT() :
	_m_bRes  (FALSE),
	m_hHandle(hFailValueT)
{
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: CxHandleT ()
template<HANDLE hFailValueT>
/*explicit*/
CxHandleT<hFailValueT>::CxHandleT(HANDLE hHandle) :
	m_hHandle(hHandle)
{
	/*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: CxHandleT ()
template<HANDLE hFailValueT>
CxHandleT<hFailValueT>::CxHandleT(const CxHandleT &hHandle) :
	m_hHandle(hHandle.hDuplicate(hGetCurrentProcess(), DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS))
{
	/*DEBUG*/
}
//---------------------------------------------------------------------------
//DONE: ~CxHandleT ()
template<HANDLE hFailValueT>
CxHandleT<hFailValueT>::~CxHandleT() {
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
template<HANDLE hFailValueT>
CxHandleT<hFailValueT> &
CxHandleT<hFailValueT>::operator = (HANDLE hHandle) {
	/*DEBUG*/xASSERT_DO(FALSE == bIsValid(), hFailValueT);
	/*DEBUG*///hHandle - n/a

	//Try m_Handle.Attach(other.Detach(), if you got an assertion here.

	if (this->m_hHandle != &hHandle) {
		//TODO:
		_m_bRes = bIsValid();
		if (TRUE == _m_bRes) {

			_m_bRes = bClose();
			if (FALSE == _m_bRes) {
				/*DEBUG*/xASSERT(FALSE);
			}
		}

		m_hHandle = hHandle;
	}

	return *this;
}
//---------------------------------------------------------------------------
//DONE: operator = ()
template<HANDLE hFailValueT>
CxHandleT<hFailValueT> &
CxHandleT<hFailValueT>::operator = (const CxHandleT &hHandle) {
	/*DEBUG*/xASSERT_DO(FALSE == bIsValid(), hFailValueT);
	/*DEBUG*///CxHandleT - n/a

	if (this != &hHandle) {
		//TODO:
		_m_bRes = bIsValid();
		if (TRUE == _m_bRes) {

			_m_bRes = bClose();
			if (FALSE == _m_bRes) {
				/*DEBUG*/xASSERT(FALSE);
			}
		}

		m_hHandle = hHandle.hDuplicate(hGetCurrentProcess(), DUPLICATE_SAME_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
		/*DEBUG*/xASSERT_RET(hFailValueT != m_hHandle, hFailValueT);
	}

	return *this;
}
//---------------------------------------------------------------------------
//DONE: operator HANDLE ()
template<HANDLE hFailValueT>
CxHandleT<hFailValueT>::operator HANDLE() const {
	/*DEBUG*///???

	return m_hHandle;
}
//---------------------------------------------------------------------------
//DONE: bIsValid ()
template<HANDLE hFailValueT>
BOOL
CxHandleT<hFailValueT>::bIsValid() const {
	/*DEBUG*///n/a

	//0XCDCDCDCD - Created but not initialised
	//0XDDDDDDDD - Deleted
	//0XFEEEFEEE - Freed memory set by NT's heap manager
	//0XCCCCCCCC - Uninitialized locals in VC6 when you compile w/ /GZ
	//0XABABABAB - Memory following a block allocated by LocalAlloc()


	//0xFDFDFDFD	No man's land (normally outside of a process)
	//0xDDDDDDDD	Freed memory
	//0xCDCDCDCD	Uninitialized (global)
	//0xCCCCCCCC	Uninitialized locals (on the stack)

	/*
	There are a few other special codes to look out for as well -
	values close to 0xCDCDCDCD, 0xCCCCCCCC or 0xBAADF00D indicate an uninitialised variable,
	while values close to 0xDDDDDDDD and 0xFEEEFEEE indicate recently deleted variables.
	If you see these in a pointer, it doesn't mean that the pointer is pointing
	to uninitialised or deleted memory - it means that the pointer itself is uninitialised
	or has been deleted. The other one to watch out for is 0xFDFDFDFD - it can indicate
	that you're reading past the beginning or end of a buffer.
	*/

	BOOL bCond1 = (reinterpret_cast<HANDLE>(3452816845UL) != m_hHandle);	//0XCDCDCDCD
	BOOL bCond2 = (reinterpret_cast<HANDLE>(3435973836UL) != m_hHandle);	//0xCCCCCCCC
	BOOL bCond3 = (reinterpret_cast<HANDLE>(3131961357UL) != m_hHandle);	//0xBAADF00D
	BOOL bCond4 = (reinterpret_cast<HANDLE>(4261281277UL) != m_hHandle);	//0xFDFDFDFD
	BOOL bCond5 = (reinterpret_cast<HANDLE>(4277075694UL) != m_hHandle);	//0XFEEEFEEE
	BOOL bCond6 = (reinterpret_cast<HANDLE>(3722304989UL) != m_hHandle);	//0XDDDDDDDD
	BOOL bCond7 = (hFailValueT                            != m_hHandle);	//hFailValueT

	return (TRUE == bCond1) &&
		   (TRUE == bCond2) &&
		   (TRUE == bCond3) &&
		   (TRUE == bCond4) &&
		   (TRUE == bCond5) &&
		   (TRUE == bCond6) &&
		   (TRUE == bCond7);
}
//---------------------------------------------------------------------------
//DONE: bAttach ()
template<HANDLE hFailValueT>
BOOL
CxHandleT<hFailValueT>::bAttach(HANDLE hHandle) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

	_m_bRes = bClose();
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	m_hHandle = hHandle;

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
template<HANDLE hFailValueT>
HANDLE
CxHandleT<hFailValueT>::hDetach() {
	/*DEBUG*///n/a

	HANDLE hHandle = m_hHandle;

	m_hHandle = hFailValueT;

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
template<HANDLE hFailValueT>
BOOL
CxHandleT<hFailValueT>::bClose() {
	/*DEBUG*/// n/a

	if (FALSE != bIsValid()) {
		_m_bRes = ::CloseHandle(m_hHandle);
		/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

		m_hHandle = hFailValueT;
	}

	return TRUE;
}
//---------------------------------------------------------------------------
#if (_WIN32_WINNT >= 0x0400)
//DONE: ulGetInformation (Retrieves certain properties of an object handle)
template<HANDLE hFailValueT>
ULONG
CxHandleT<hFailValueT>::ulGetInformation() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), 0);

	ULONG ulFlags = 0;

	_m_bRes = ::GetHandleInformation(m_hHandle, &ulFlags);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, 0);
	/*DEBUG*/xASSERT_RET(0     != ulFlags, 0);

	return ulFlags;
}
//---------------------------------------------------------------------------
//DONE: bSetInformation ()
template<HANDLE hFailValueT>
BOOL
CxHandleT<hFailValueT>::bSetInformation(ULONG ulMask, ULONG ulFlags) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);
	/*DEBUG*///ulMask  - n/a
	/*DEBUG*///ulFlags - ????

	_m_bRes = ::SetHandleInformation(m_hHandle, ulMask, ulFlags);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bIsFlagInherit ()
template<HANDLE hFailValueT>
BOOL
CxHandleT<hFailValueT>::bIsFlagInherit() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

	return 0 != (ulGetInformation() & HANDLE_FLAG_INHERIT);
}
//---------------------------------------------------------------------------
//DONE: bIsFlagProtectFromClose ()
template<HANDLE hFailValueT>
BOOL
CxHandleT<hFailValueT>::bIsFlagProtectFromClose() const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

	return 0 != (ulGetInformation() & HANDLE_FLAG_PROTECT_FROM_CLOSE);
}
//---------------------------------------------------------------------------
//DONE: bSetFlagInherit ()
template<HANDLE hFailValueT>
BOOL
CxHandleT<hFailValueT>::bSetFlagInherit(BOOL bFlagInherit) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

	return bSetInformation(HANDLE_FLAG_INHERIT, (bFlagInherit) ? HANDLE_FLAG_INHERIT : 0);;
}
//---------------------------------------------------------------------------
//DONE: bSetFlagProtectFromClose ()
template<HANDLE hFailValueT>
BOOL
CxHandleT<hFailValueT>::bSetFlagProtectFromClose(BOOL bFlagProtectFromClose) {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), FALSE);

	return bSetInformation(HANDLE_FLAG_PROTECT_FROM_CLOSE, (bFlagProtectFromClose) ? HANDLE_FLAG_PROTECT_FROM_CLOSE : 0);
}
#endif // (_WIN32_WINNT >= 0x0400)
//---------------------------------------------------------------------------
//DONE: hDuplicate (Duplicates an object handle)
template<HANDLE hFailValueT>
HANDLE
CxHandleT<hFailValueT>::hDuplicate(HANDLE hTargetProcess, ULONG ulDesiredAccess, BOOL bInheritHandle/* = FALSE*/, ULONG ulOptions/* = 0*/) const {
	/*DEBUG*/xASSERT_RET(FALSE != bIsValid(), hFailValueT);

	HANDLE hRes = hFailValueT;

	_m_bRes = ::DuplicateHandle(hGetCurrentProcess(), m_hHandle, hTargetProcess, &hRes, ulDesiredAccess, bInheritHandle, ulOptions);
	/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, hFailValueT);

	return hRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public, static
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: static
template<HANDLE hFailValueT>
const HANDLE
CxHandleT<hFailValueT>::_ms_chCurrProcessHandle = (HANDLE) - 1;
//---------------------------------------------------------------------------
//DONE: hGetCurrent (Retrieves a pseudo handle for the current process)
template<HANDLE hFailValueT>
/*static*/
HANDLE
CxHandleT<hFailValueT>::hGetCurrentProcess() {
	/*DEBUG*///n/a

	HANDLE hRes = hFailValueT;

	hRes = ::GetCurrentProcess();
	/*DEBUG*/xASSERT_RET(_ms_chCurrProcessHandle == hRes, hFailValueT);

	return hRes;
}
//---------------------------------------------------------------------------
//DONE: bIsValid (�������� ���������� ������)
template<HANDLE hFailValueT>
/*static*/
BOOL
CxHandleT<hFailValueT>::bIsValid(HANDLE hHandle) {
	/*DEBUG*/// n/a

	return hFailValueT != hHandle;
}
//---------------------------------------------------------------------------
