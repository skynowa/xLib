/**********************************************************************
*	vMethod.cpp	
*
***********************************************************************/


#include "uMailBrute.h"

//---------------------------------------------------------------------------
unsigned long int __fastcall ulListViewSelItems(TListView *pLV) {
    unsigned long int ulRes = 0;

    for (int i = 0; i < lvwDicFiles->Items->Count; i ++) {
        if (lvwDicFiles->Items->Item[i]->Checked == true) {
            ulRes ++;
        }
    }

    return ulRes;
}
//---------------------------------------------------------------------------
