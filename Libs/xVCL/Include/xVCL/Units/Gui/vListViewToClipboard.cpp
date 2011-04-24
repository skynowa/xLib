/**********************************************************************
*	vListViewToCliboard - ���������� ListView ����� � ����� ������ 
*
***********************************************************************/


#include "uEToken.h"        //frmMain
#include <Clipbrd.hpp>

//---------------------------------------------------------------------------
void __fastcall vListViewToCliboard(TListView *pListView) {
    //-------------------------------------
    //CHECK


    //-------------------------------------
    //��������� ���������� ListView � ����������
    tString       asContent    = "";
    const tString casDelimiter = "\t";

    //���������
    for (int i = 0; i < pListView->Columns->Count; i ++) {
        asContent += pListView->Column[i]->Caption;
        if (i < pListView->Columns->Count - 1) {
            asContent += casDelimiter;
        } else {
            asContent += "\n";
        }
    }   //DEBUG(asContent);

    //����
    for (int i = 0; i < pListView->Items->Count; i ++) {
        asContent += pListView->Items->Item[i]->Caption;
        if (i < pListView->Items->Count - 1) {
            asContent += casDelimiter;
        }

        for (int j = 0; j < pListView->Items->Item[i]->SubItems->Count; j ++) {
            asContent += pListView->Items->Item[i]->SubItems->Strings[j];
            if (j < pListView->Items->Item[i]->SubItems->Count - 1) {
                asContent += casDelimiter;
            } else {
                asContent += "\n";
            }
        } 
    }   //DEBUG(asContent);


    //-------------------------------------
    //���������� � �����
    try {
        ActivateKeyboardLayout(LoadKeyboardLayout(IntToHex(MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT), 8).c_str(), 0), 0);
        Clipboard()->SetTextBuf(asContent.c_str());
        MessageBox(0, "������ ������� �������������� � ����� ������", Application->Title.c_str(), MB_OK + MB_ICONINFORMATION + MB_TOPMOST);
    } catch (Exception &exception) {
        Application->ShowException(&exception);
    }
}
//---------------------------------------------------------------------------
