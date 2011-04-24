/**********************************************************************
*	������� ������ ������ � ��� ������ � ���
*
***********************************************************************/

#include "Main.h"

void __fastcall doDeleteGroup() {
    //--- �������� ---
    //--- �������� ---

    TTreeNode *pNode = TreeView1->Selected; //ShowMessage(pNode->Text);
    TListItem *pLstItem;
    
    if (pNode && (pNode->HasChildren || ListView1->Items->Count != 0)) {
        return; //���� ����� ����� ������ ��� �������� 
    } else {
        //1. ������� � pDataBaseList
        for (int i = 0; i < pDataBaseList->Count - 1; i ++) {
            //�������� asNodeID (pDataBaseList � TreeView1)
            if (pMyRec(TreeView1->Selected->Data)->asNodeID == pDataBaseList->Strings[i + 1].SubString(4, pDataBaseList->Strings[i + 1].Length())) {
	            //������� (�������� ������, ��������� id, level)
	            pDataBaseList->Delete(i);    //[�������� ������]
                pDataBaseList->Delete(i);    //[�������� id]
                pDataBaseList->Delete(i);    //[�������� level]
            }
        }

        //2. ������� � TreeView1
        pNode->Delete();
    }
}


	    /*int iResult = MessageBox(NULL, "������ �� �����, �������?", Application->Title.c_str(), 3 | 32 | 0 | 0 | 262144);   //ShowMessage(iResult);

		switch (iResult) {
			case 6: //��
                //� TreeView1
				pNode->Delete();

                //� pDataBaseList
		        for (int i = 0; i < pDataBaseList->Count - 1; i ++) {
                    ////���� ����[Visual C++] == ������[Visual C++] ShowMessage(pDataBaseList->Strings[i]);
	                ////if ("[" + pNode->Text + "]" == pDataBaseList->Strings[i]){

                    //�������� asNodeID (pDataBaseList � TreeView1)
                    if (pMyRec(frmMain->TreeView1->Selected->Data)->asNodeID == pDataBaseList->Strings[i + 1].SubString(4, pDataBaseList->Strings[i + 1].Length())) {
	                    //������� (�������� ������, ��������� id, level)
	                    pDataBaseList->Delete(i + 0);    //[�������� ������]
                        pDataBaseList->Delete(i + 1);    //[�������� id]
                        pDataBaseList->Delete(i + 2);    //[�������� level]
	                }
	            }

				break;
			case 7: //���
				//ShowMessage("���");
				break;
			case 2: //������
				//ShowMessage("������");
				break;
			default: //����������;
				break;
		}
	} else {
        pNode->Delete();
    }
	TreeView1->Update(); */
