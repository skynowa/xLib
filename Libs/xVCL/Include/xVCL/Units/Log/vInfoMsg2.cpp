/**********************************************************************
*	vMakeDocsReport -
*
***********************************************************************/


#include "uDM.h"        //frmDM
#include "uEToken.h"    //frmMain

//---------------------------------------------------------------------------
void __fastcall vInfoMsg2(TStatusBar *pStatusBar, int iPanel, const tString &asMsg, int iBeep, int iImg) {
    iBeep = 0;  //del

    //-------------------------------------
    //�����
    pStatusBar->Panels->Items[iPanel]->Text = " " + asMsg;
    //-------------------------------------
    //����
    switch (iBeep) {
        ////case 0: /*��� �����*/ ; break;
        case 1: Beep(100, 50 ); break;
        case 2: Beep(200, 200); break;
    }
}
//---------------------------------------------------------------------------
