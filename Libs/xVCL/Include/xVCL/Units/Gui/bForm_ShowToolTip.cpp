/***********************************************************************
*   bForm_ShowToolTip - Анимац. открытия формы
*
************************************************************************/


//---------------------------------------------------------------------------
//TODO: bForm_ShowToolTip 
BOOL bForm_ShowToolTip(TForm *pfrmForm) {
	/*DEBUG*/xASSERT_RET(NULL != pfrmForm, FALSE);

	//Если таскали - вернуть обратно к таскбвру
    bForm_MoveToTaskbar(pfrmForm);
	
    //активируем форму
	////bForm_BringToFront(pfrmForm);
	HWND hCurrWnd = ::GetForegroundWindow();
	INT  iMyTID   = ::GetCurrentThreadId();
	INT  iCurrTID = ::GetWindowThreadProcessId(hCurrWnd, 0);

	::AttachThreadInput  (iMyTID, iCurrTID, TRUE);
	::SetForegroundWindow(pfrmForm->Handle);
	::AttachThreadInput  (iMyTID, iCurrTID, FALSE);
    
	//анимация
    ::AnimateWindow(pfrmForm->Handle, 280, AW_ACTIVATE  | AW_BLEND /*| AW_CENTER*/);
    
	pfrmForm->Visible = true;
    pfrmForm->Repaint();

	return TRUE;
}
//---------------------------------------------------------------------------