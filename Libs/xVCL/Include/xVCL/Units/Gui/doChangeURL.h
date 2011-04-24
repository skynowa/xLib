				/**********************************************************************
*	������ URL
*
***********************************************************************/

#include "Main.h"

void __fastcall doChangeURL() {
    //--- �������� ---
    if (ListView1->Items->Count == 0 || ListView1->SelCount == 0) {
        return;
    }
    //--- �������� ---

    //1. � pDataBaseList
    //...

    //2. � ListView1
    int iSelIndex = ListView1->Selected->Index;
    frmURLProperty->edtURL->Text      = ListView1->Items->Item[iSelIndex]->Caption;               //url
    frmURLProperty->edtDownload->Text = ListView1->Items->Item[iSelIndex]->SubItems->Strings[0];  //download
    frmURLProperty->edtComments->Text = ListView1->Items->Item[iSelIndex]->SubItems->Strings[1];  //comments

	frmURLProperty->ShowModal();
}
