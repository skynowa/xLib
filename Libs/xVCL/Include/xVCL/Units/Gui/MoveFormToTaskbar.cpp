/***********************************************************************
*   суём форму к таскбару
*
************************************************************************/


void __fastcall TfrmToolTip::MoveFormToTaskbar() {
    RECT rRect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rRect, 0);
    frmToolTip->Top  = rRect.bottom - frmToolTip->Height - 2;
    frmToolTip->Left = Screen->Width - frmToolTip->Width - 2;
}