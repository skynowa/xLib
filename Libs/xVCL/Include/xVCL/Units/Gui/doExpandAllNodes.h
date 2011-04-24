/**********************************************************************
*	Разворачиваем все узлы TreeView1
*
***********************************************************************/

#include "Main.h"

void __fastcall doExpandAllNodes() {
    //--- проверка ---
    if (TreeView1->Items->Count == 0) {return;}
    //--- проверка ---

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
    //выделяем корневой узел TreeView1
    TTreeNode *pNode = TreeView1->Items->Item[0];
    pNode->Selected = true;
}
