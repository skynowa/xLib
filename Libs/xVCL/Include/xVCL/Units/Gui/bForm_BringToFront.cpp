/***********************************************************************
*	bForm_BringToFront - Создать текстовое поле
*
************************************************************************/


//---------------------------------------------------------------------------
//TODO: bForm_BringToFront
BOOL bForm_BringToFront(TForm *pfrmForm) {
	/*DEBUG*/xASSERT_RET(NULL != pfrmForm, FALSE);

	HWND hCurrWnd = ::GetForegroundWindow();
	INT  iMyTID   = ::GetCurrentThreadId();
	INT  iCurrTID = ::GetWindowThreadProcessId(hCurrWnd, 0);

	::AttachThreadInput  (iMyTID, iCurrTID, TRUE);
	::SetForegroundWindow(pfrmForm->Handle);
	::AttachThreadInput  (iMyTID, iCurrTID, FALSE);
	
	return TRUE;
}
//---------------------------------------------------------------------------
