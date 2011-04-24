/***********************************************************************
*   Добавляем строку в lvwLog с сообщением
*
************************************************************************/


void __fastcall AddToLog(const int &iImageIndex, const tString &asLine) {
    lvwLog->Items->Add();
    lvwLog->Items->Item[lvwLog->Items->Count - 1]->StateIndex = iImageIndex;    //системное сообщение
    lvwLog->Items->Item[lvwLog->Items->Count - 1]->SubItems->Add(Now().CurrentTime());
    lvwLog->Items->Item[lvwLog->Items->Count - 1]->SubItems->Add(asLine);

    //прокручиваем список вниз
    SendMessage(lvwLog->Handle, WM_VSCROLL, MAKEWORD(SB_LINEDOWN, 0), 0);
}
