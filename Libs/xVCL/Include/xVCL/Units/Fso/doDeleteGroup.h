/**********************************************************************
*	Удаляем группу группу и все ссылки в ней
*
***********************************************************************/

#include "Main.h"

void __fastcall doDeleteGroup() {
    //--- проверка ---
    //--- проверка ---

    TTreeNode *pNode = TreeView1->Selected; //ShowMessage(pNode->Text);
    TListItem *pLstItem;
    
    if (pNode && (pNode->HasChildren || ListView1->Items->Count != 0)) {
        return; //если група имеет ссылки или подгрупы 
    } else {
        //1. удаляем в pDataBaseList
        for (int i = 0; i < pDataBaseList->Count - 1; i ++) {
            //сравнить asNodeID (pDataBaseList и TreeView1)
            if (pMyRec(TreeView1->Selected->Data)->asNodeID == pDataBaseList->Strings[i + 1].SubString(4, pDataBaseList->Strings[i + 1].Length())) {
	            //удалить (название секции, параметры id, level)
	            pDataBaseList->Delete(i);    //[название секции]
                pDataBaseList->Delete(i);    //[параметр id]
                pDataBaseList->Delete(i);    //[параметр level]
            }
        }

        //2. удаляем в TreeView1
        pNode->Delete();
    }
}


	    /*int iResult = MessageBox(NULL, "Группа не пуста, удалить?", Application->Title.c_str(), 3 | 32 | 0 | 0 | 262144);   //ShowMessage(iResult);

		switch (iResult) {
			case 6: //да
                //в TreeView1
				pNode->Delete();

                //в pDataBaseList
		        for (int i = 0; i < pDataBaseList->Count - 1; i ++) {
                    ////если узел[Visual C++] == массив[Visual C++] ShowMessage(pDataBaseList->Strings[i]);
	                ////if ("[" + pNode->Text + "]" == pDataBaseList->Strings[i]){

                    //сравнить asNodeID (pDataBaseList и TreeView1)
                    if (pMyRec(frmMain->TreeView1->Selected->Data)->asNodeID == pDataBaseList->Strings[i + 1].SubString(4, pDataBaseList->Strings[i + 1].Length())) {
	                    //удалить (название секции, параметры id, level)
	                    pDataBaseList->Delete(i + 0);    //[название секции]
                        pDataBaseList->Delete(i + 1);    //[параметр id]
                        pDataBaseList->Delete(i + 2);    //[параметр level]
	                }
	            }

				break;
			case 7: //нет
				//ShowMessage("нет");
				break;
			case 2: //отмена
				//ShowMessage("отмена");
				break;
			default: //инструкции;
				break;
		}
	} else {
        pNode->Delete();
    }
	TreeView1->Update(); */
