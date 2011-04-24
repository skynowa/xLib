/**********************************************************************
*	Показываем колонки	
*
***********************************************************************/

#include "Main.h"

void __fastcall doDisplayColumns(TTreeNode *NodeSelected) {
	TListColumn *pCol;
	
	// Erase the previous columns so they would not be added to the new ones
	ListView1->Columns->Clear();
	
	// Find out what node was selected, the root or a continent
	if (NodeSelected == TreeView1->Items->Item[0]){   //URL
		pCol = ListView1->Columns->Add();
		pCol->Caption = "URL";
		pCol->Width = 200;
		
		pCol = ListView1->Columns->Add();
		pCol->Caption = "Download";
		pCol->Width = 60;

		pCol = ListView1->Columns->Add();
		pCol->Caption = "Comments";
		pCol->Width = 170;
	} else {
		pCol = ListView1->Columns->Add();
		pCol->Caption = "URL";
		pCol->Width = 200;
		
		pCol = ListView1->Columns->Add();
		pCol->Caption = "Download";
		pCol->Width = 60;

		pCol = ListView1->Columns->Add();
		pCol->Caption = "Comments";
		pCol->Width = 170;
	}
}

