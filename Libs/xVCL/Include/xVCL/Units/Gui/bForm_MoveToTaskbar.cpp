/***********************************************************************
*   суём форму к таскбару
*
************************************************************************/


//---------------------------------------------------------------------------
//TODO: bForm_MoveToTaskbar 
BOOL bForm_MoveToTaskbar(TForm *pfrmForm) {
	/*DEBUG*/xASSERT_RET(NULL != pfrmForm, FALSE);

	const INT ciMargins = 2;
	
    RECT rect = {0};
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	
    pfrmForm->Top  = rect.bottom   - pfrmForm->Height - ciMargins;
    pfrmForm->Left = Screen->Width - pfrmForm->Width  - ciMargins;

	return TRUE;
}
//---------------------------------------------------------------------------
