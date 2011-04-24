/**********************************************************************
*	���������� �������	
*
***********************************************************************/

#include "Main.h"

extern TStringList *pDataBaseList;    //������ ���� � TStringList-������

void __fastcall doAddSubGroup() {
    tString asNameOfNewGroup = "����� ������ 0001";
    TTreeNode *pNode = TreeView1->Selected;

    //������ ������, ���� ���� ��������� ������ � pDataBaseList)
    int iIndexWhereInsert = 0;
    bool bFlag = false;
    for (int i = 0; i < pDataBaseList->Count; i ++) {   //ShowMessage(pBaseList->Strings[i]);
        if (pDataBaseList->Strings[i].Pos("[") == 1 && pDataBaseList->Strings[i].LastDelimiter("]")) {  //���� "[" ... "]"
            if (bFlag == true) {
                iIndexWhereInsert = i; break;
            }
            if (pDataBaseList->Strings[i] == "[" + pNode->Text + "]") {
                bFlag = true;
            }
        }
    }   //ShowMessage(iIndexWhereInsert);

    //��������� � pDataBaseList
    tString asSectionId = doGenerateRandomID();  //ShowMessage(asSectionId);
    pDataBaseList->Insert(iIndexWhereInsert + 0, "["      + asNameOfNewGroup + "]");
    pDataBaseList->Insert(iIndexWhereInsert + 1, "id="    + asSectionId);
    pDataBaseList->Insert(iIndexWhereInsert + 2, "level=" + tString(pNode->Level + 1));

    //��������� � TreeView1
	if (pNode) {
        ////pMyRec MyRecPtr = new TMyRec;
                                            //ShowMessage(asSectionId);
        MyRecPtr->asNodeID = asSectionId;   //ShowMessage(MyRecPtr->asNodeID); //id ����

        TreeView1->Items->AddChildObject(pNode, asNameOfNewGroup, MyRecPtr) ;
        pNode->Expand(true);
    }
	TreeView1->Update();
}

