/***********************************************************************
*	Подсчитать общее кол-во файлов,  линий, размеров
*
************************************************************************/


//---------------------------------------------------------------------------
void __fastcall vCountTotalForDicFile() {
    //обнуляем Total-ы
    lblTotalFiles->Caption = 0;
    lblTotalLines->Caption = 0;
    lblTotalSize->Caption  = "0 (Mb)";

    //подсчитуем
    for (int i = 0; i < lvwDicFiles->Items->Count; i ++) {  Application->ProcessMessages();
        //Всего файлов
        lblTotalFiles->Caption = lblTotalFiles->Caption.ToInt() + 1;
        //Всего линий
        lblTotalLines->Caption = lblTotalLines->Caption.ToInt() + lvwDicFiles->Items->Item[i]->SubItems->Strings[0].ToInt();
        //Всего размеров
        lblTotalSize->Caption = tString((lblTotalSize->Caption.SubString(0, lblTotalSize->Caption.Length() - 5)).ToDouble() + (lvwDicFiles->Items->Item[i]->SubItems->Strings[1]).ToDouble()) + " (Mb)";
    }
}
//---------------------------------------------------------------------------   
