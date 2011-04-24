/**********************************************************************
*	������� URL	
*
***********************************************************************/

#include "Main.h"

extern TStringList *pDataBaseList;

void __fastcall doDeleteURL() {
    //--- �������� ---
    if (ListView1->Items->Count == 0 || ListView1->SelCount == 0) {
	    return;
    }
    //--- �������� ---
    
    TListItem *pLstItem;

    //���� �� pDataBaseList
    for (int i = 0; i < pDataBaseList->Count; i ++) {
        //�������� asNodeID (pDataBaseList � TreeView1)
        if (pMyRec(TreeView1->Selected->Data)->asNodeID == pDataBaseList->Strings[i + 1].SubString(4, pDataBaseList->Strings[i + 1].Length())) {
            int iSelIndex = ListView1->Selected->Index;    //ShowMessage(iSelIndex);
            for (int i = 0; i < pDataBaseList->Count; i ++) {    //ShowMessage(pDataBaseList->Strings[i]);
                if (pDataBaseList->Strings[i + 0 + 2] == "url="      + ListView1->Items->Item[iSelIndex]->Caption              &&
                    pDataBaseList->Strings[i + 1 + 2] == "download=" + ListView1->Items->Item[iSelIndex]->SubItems->Strings[0] &&
                    pDataBaseList->Strings[i + 2 + 2] == "comments=" + ListView1->Items->Item[iSelIndex]->SubItems->Strings[1]    )
                {
                    //1. ������� URL � pDataBaseList
                    pDataBaseList->Delete(i + 2);    //url
                    pDataBaseList->Delete(i + 2);    //download
                    pDataBaseList->Delete(i + 2);    //comments

                    //2. ������� URL � ListView1
                    ListView1->DeleteSelected();

                    return;
                }
            }
        }
    }
}

