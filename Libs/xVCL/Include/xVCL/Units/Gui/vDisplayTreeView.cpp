/**********************************************************************
*	ѕоказываем колонки	
*
***********************************************************************/


#include "uEToken.h"
//---------------------------------------------------------------------------
void __fastcall vDisplayTreeView(TTreeView *pTV, CYug_eToken &T/*, unsigned long int ulSlotId*/) {
    //очищаем TreeView
    tvReadInfo->Items->Clear();

    //заполн€ем
    unsigned long int i                = 0;
    unsigned long int ulInsertedTokens = T.ulInsertedTokens();
    for (i; i < ulInsertedTokens; i ++) {
        //eToken # ??? заголовок (TreeView)
        tvReadInfo->Items->Add(0, "eToken #" + IntToStr(T.ulGetSlotList()[i]));     //убить указательы
        tvReadInfo->Items->Item[tvReadInfo->Items->Count - 1]->ImageIndex    = 0;   //есть токен
        tvReadInfo->Items->Item[tvReadInfo->Items->Count - 1]->SelectedIndex = 0;
    }

    //фокусируем 1-ый слот
    tvReadInfo->SetFocus();
    if (tvReadInfo->Items->Count != 0) {
        tvReadInfo->Select(tvReadInfo->Items->Item[0]);
    }
}
//---------------------------------------------------------------------------

