/**********************************************************************
*	������������� ��� ���� TreeView1
*
***********************************************************************/

#include "Main.h"

void __fastcall doExpandAllNodes() {
    //--- �������� ---
    if (TreeView1->Items->Count == 0) {return;}
    //--- �������� ---

    for (int i = 0; i < TreeView1->Items->Count; i ++) {
        TTreeNode *pNode = TreeView1->Items->Item[i];
        if (pNode->HasChildren) {
            TTreeNode *pNode = TreeView1->Items->Item[i];
            if (pNode) {
                pNode->Expand(true);
            }
            TreeView1->Update();
        }
    }
    //�������� �������� ���� TreeView1
    TTreeNode *pNode = TreeView1->Items->Item[0];
    pNode->Selected = true;
}
