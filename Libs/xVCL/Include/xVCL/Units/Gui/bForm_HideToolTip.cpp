/***********************************************************************
*   bForm_HideToolTip - Анимац. закрытие формы
*
************************************************************************/


//---------------------------------------------------------------------------
//TODO: bForm_HideToolTip
BOOL bForm_HideToolTip(TForm *pfrmForm) {
	/*DEBUG*/xASSERT_RET(NULL != pfrmForm, FALSE);

    ::AnimateWindow(pfrmForm->Handle, 280, AW_HIDE | AW_BLEND | AW_CENTER);
    pfrmForm->Visible = false;
    pfrmForm->Repaint();

	return TRUE;
}
//---------------------------------------------------------------------------
