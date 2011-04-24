/***********************************************************************
*   Анимац. открытия формы
*
************************************************************************/


extern TfrmToolTip *frmToolTip;

void __fastcall TfrmToolTip::ShowToolTip() {
    //Если таскали - вернуть обратно к таскбвру
    frmToolTip->MoveFormToTaskbar();
    //активируем форму
    frmToolTip->BringToFrontWindow(frmToolTip->Handle);
    //анимация
    AnimateWindow(frmToolTip->Handle, 280, AW_ACTIVATE  | AW_BLEND /*| AW_CENTER*/);
    frmToolTip->Show();
    frmToolTip->Repaint();
}
