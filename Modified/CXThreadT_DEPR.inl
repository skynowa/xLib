/****************************************************************************
* Class name:  CXThreadT
* Description: работа с потоками
* File name:   CXThreadT.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     17.05.2009 17:20:09
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


//---------------------------------------------------------------------------
template<class T, class P>
CXThreadT<T, P>::CXThreadT() : 
	_m_hThread   (NULL),
	_m_uiID      ((UINT) - 1),
	_m_pInstance (NULL),
	_m_pfFunc    (NULL)
{
	//Create the Exit Event - Should the args to CreateEvent be
	//customizable?  What should be done if CreateEvent() fails?
	//NOTE: Since we will have only one consumer of the exit event,
	//it is safe to make the event an auto-reset event
	if (FALSE == _m_ExitEvent.bCreate(NULL, FALSE, FALSE, NULL)) {
		return;
	}
}
//---------------------------------------------------------------------------
template<class T, class P>
CXThreadT<T, P>::~CXThreadT()	{
	/*DEBUG*///not need

	if (TRUE == bIsActive()) {
		bKill();
	}
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bRun(T *pClass, ThreadFunc pfFunc, P param, BOOL bCreateSuspended) {
	/*DEBUG*/xASSERT_RET(FALSE == CHECK_HANDLE(_m_hThread), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pClass,                   FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pfFunc,                   FALSE);
	
	//Store the values in this class instance so
	//the static ulThreadProc() function can call
	//the appropriate method on the object
	_m_pInstance = pClass;
	_m_pfFunc    = pfFunc;
	_m_iParam    = param; 

	UINT uiGreationFlag = bCreateSuspended ? CREATE_SUSPENDED : 0;
	/*DEBUG*/xASSERT_RET((0 == uiGreationFlag) || (CREATE_SUSPENDED == uiGreationFlag), FALSE);

	_m_hThread = (HANDLE)_beginthreadex(NULL, 0, _s_uiThreadProc, this, uiGreationFlag, &_m_uiID);
	/*DEBUG*/xASSERT_RET(NULL != _m_hThread, FALSE);		
	
	return TRUE;
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bSetPriority(INT iPriority) {
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE); 

	BOOL bRes = FALSE;

	bRes = ::SetThreadPriority(_m_hThread, iPriority);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
template<class T, class P>
INT CXThreadT<T, P>::iGetPriority() {
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), THREAD_PRIORITY_ERROR_RETURN); 

	INT iRes = THREAD_PRIORITY_ERROR_RETURN;

	iRes = ::GetThreadPriority(_m_hThread);
	/*DEBUG*/xASSERT_RET(THREAD_PRIORITY_ERROR_RETURN != iRes, THREAD_PRIORITY_ERROR_RETURN);

	return iRes;
}
//---------------------------------------------------------------------------
template<class T, class P>
ULONG CXThreadT<T, P>::ulGetId() {
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), 0); 

	ULONG ulRes = 0;

	ulRes = ::GetCurrentThreadId();
	/*DEBUG*/xASSERT_RET(0 != ulRes, 0);
	/*DEBUG*///TODO: - xASSERT_RET(static_cast<ULONG>(_m_uiID) == ulRes, 0);
	

	return ulRes;
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bSuspend() {
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE); 
		
	ULONG ulRes = (ULONG) -1;
	
	ulRes = ::SuspendThread(_m_hThread);
	/*DEBUG*/xASSERT_RET((ULONG) -1 != ulRes, FALSE);
	
	return TRUE;
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bResume()	{
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE);
		
    ULONG ulResumeCount = (DWORD) -1;
    
	ulResumeCount = ::ResumeThread(_m_hThread);
	/*DEBUG*/xASSERT_RET((ULONG) - 1 != ulResumeCount, FALSE);

	while (ulResumeCount > 1) {
		ulResumeCount = ::ResumeThread(_m_hThread);
		/*DEBUG*/xASSERT_RET((ULONG) - 1 != ulResumeCount, FALSE);
	}
	
	return TRUE;
}
//---------------------------------------------------------------------------
//vExecute - функция потока
template<class T, class P>
/*virtual*/ VOID CXThreadT<T, P>::vExecute(VOID *pvParam) {
	/*DEBUG*/xASSERT_DO(CHECK_HANDLE(_m_hThread), return);

	return;
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bKill() {
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE); 
	
	BOOL bRes = FALSE;  

    bRes = ::TerminateThread(_m_hThread, 0);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    bRes = ::CloseHandle(_m_hThread);	_m_hThread = NULL;
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    
    return TRUE;
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bIsActive() const {
    /*DEBUG*///not need
       
	return (CHECK_HANDLE(_m_hThread) && (WAIT_OBJECT_0 != ::WaitForSingleObject(_m_hThread, 0)));            	//debug
}
//---------------------------------------------------------------------------
template<class T, class P>
/*static*/UINT WINAPI CXThreadT<T, P>::_s_uiThreadProc(VOID *pvParam) {
	/*DEBUG*///not need

	CXThreadT *pInstance = reinterpret_cast<CXThreadT *>(pvParam);
	/*DEBUG*/xASSERT_RET(NULL != pInstance, (ULONG) - 1);

	//Get the invoketion variables so we don't have to use even more funky syntax
	T         *pClassInstance = pInstance->_m_pInstance;
	ThreadFunc pfFunc         = pInstance->_m_pfFunc;
	P          param          = pInstance->_m_iParam;
	/*DEBUG*/xASSERT_RET(NULL != pClassInstance, (ULONG) - 1);
	/*DEBUG*/xASSERT_RET(NULL != pfFunc,         (ULONG) - 1);

	//We have a valid instance of the CXThreadT class, use
	//the thread's stored parameters to call the client
	//(worker) function.  This will continue to run in
	//the context of this (seperate) thread until finished
	((*pClassInstance).*pfFunc)(param);

	return 0;
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bExit()	{
    /*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE);

	return _m_ExitEvent.bSet();
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bExitAndWait(ULONG ulTimeoutMS) {
    /*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE);
    
	BOOL bRes = FALSE;
	
	//Set the event telling the thread to exit
	bRes = _m_ExitEvent.bSet();
	xCHECK_RET(FALSE == bRes, FALSE);

	//Wait for the thread to actually exit
	ULONG ulRes = ::WaitForSingleObject(_m_hThread, ulTimeoutMS);            //debug

	//Cleanup handle
	/*DEBUG*/xASSERT(NULL != _m_hThread);
	bRes = ::CloseHandle(_m_hThread);	_m_hThread = NULL;
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return (WAIT_OBJECT_0 == ulRes);
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bIsExitEventSet()	{
    /*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE);
        
	ULONG ulRes = _m_ExitEvent.ulWaitForSingleObject(0);
	
	return (WAIT_OBJECT_0 == ulRes);
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bWait(ULONG ulWaitTime) {
    /*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE);
        
	ULONG ulRes = ::WaitForSingleObject(_m_hThread, ulWaitTime);					//debug

	return (WAIT_OBJECT_0 == ulRes);
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bPostMessage(HWND hHwnd, UINT uiMsg, INT iParam1, INT iParam2) {
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread),  FALSE);
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(hHwnd),       FALSE);

	BOOL bRes = FALSE;

	bRes = ::PostMessage(hHwnd, uiMsg, static_cast<WPARAM>(iParam1), static_cast<WPARAM>(iParam2));
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);	

	return TRUE;
}
//---------------------------------------------------------------------------
template<class T, class P>	
BOOL CXThreadT<T, P>::bSendMessage(HWND hHwnd, UINT uiMsg, INT iParam1, INT iParam2) {
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE);
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(hHwnd),      FALSE);

	::SendMessage(hHwnd, uiMsg, static_cast<WPARAM>(iParam1), static_cast<WPARAM>(iParam2));
	/*DEBUG*///- not need 

	return TRUE;
}
//---------------------------------------------------------------------------
template<class T, class P>	
BOOL CXThreadT<T, P>::bPostThreadMessage(ULONG ulThreadId, UINT uiMsg, INT iParam1, INT iParam2) {
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE);

	BOOL bRes = FALSE;

	bRes = ::PostThreadMessage(ulThreadId, uiMsg, static_cast<WPARAM>(iParam1), static_cast<WPARAM>(iParam2));
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);	

	return TRUE;
}
//---------------------------------------------------------------------------
template<class T, class P>
BOOL CXThreadT<T, P>::bMessageWaitQueue(INT iMsg, INT *piParam1, INT *piParam2) {
	/*DEBUG*/xASSERT_RET(CHECK_HANDLE(_m_hThread), FALSE);
	/*DEBUG*/xASSERT_RET(0    <  iMsg,             FALSE);

	BOOL bRes   = - 1;
	MSG  msgMsg = {0};

	while (bRes = ::GetMessage(&msgMsg, NULL, 0, 0 )) {
		if (- 1 == bRes) {
			/*DEBUG*/xASSERT_RET(false, false);
			break;
		}

		if (iMsg == msgMsg.message) {
			if (NULL != piParam1) {
				*piParam1 = static_cast<INT>(msgMsg.lParam);
			}

			if (NULL != piParam2) {
				*piParam2 = static_cast<INT>(msgMsg.wParam);
			}

			break;
		}

		::TranslateMessage(&msgMsg);
		::DispatchMessage (&msgMsg);
	}

	return TRUE;
}