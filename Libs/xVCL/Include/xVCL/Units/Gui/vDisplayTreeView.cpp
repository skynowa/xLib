/**********************************************************************
*	���������� �������	
*
***********************************************************************/


#include "uEToken.h"
//---------------------------------------------------------------------------
void __fastcall vDisplayTreeView(TTreeView *pTV, CYug_eToken &T/*, unsigned long int ulSlotId*/) {
    //������� TreeView
    tvReadInfo->Items->Clear();

    //���������
    unsigned long int i                = 0;
    unsigned long int ulInsertedTokens = T.ulInsertedTokens();
    for (i; i < ulInsertedTokens; i ++) {
        //eToken # ??? ��������� (TreeView)
        tvReadInfo->Items->Add(0, "eToken #" + IntToStr(T.ulGetSlotList()[i]));     //����� ����������
        tvReadInfo->Items->Item[tvReadInfo->Items->Count - 1]->ImageIndex    = 0;   //���� �����
        tvReadInfo->Items->Item[tvReadInfo->Items->Count - 1]->SelectedIndex = 0;
    }

    //���������� 1-�� ����
    tvReadInfo->SetFocus();
    if (tvReadInfo->Items->Count != 0) {
        tvReadInfo->Select(tvReadInfo->Items->Item[0]);
    }
}
//---------------------------------------------------------------------------

