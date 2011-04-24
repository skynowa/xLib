/**********************************************************************
*	��������� ���� (��������� TreeView1 + ID)
*
***********************************************************************/

#include "Main.h"

extern TStringList *pDataBaseList;    //������ ���� � TStringList-������

void __fastcall doLoadBase(tString asFilePath) {
    TIniFile *pDataBaseIni = new TIniFile(ExtractFilePath(Application->ExeName) + "URLBase.ini");   //������ ���� � TIniFile-������
    ///////////////////////////////////////////////////////////////////////////////////////
    //������� ����� ������ � �� ����������
    TStringList *pSection = new TStringList;    //������ �������� ������ 
    TStringList *pBaseList = new TStringList;   //��� ���������� pSection (���������)
    pBaseList->LoadFromFile(asFilePath);

    //��������� ������
    for (int i = 0; i < pBaseList->Count; i ++) {   //ShowMessage(pBaseList->Strings[i]);
        if (pBaseList->Strings[i].Pos("[") == 1 && pBaseList->Strings[i].LastDelimiter("]")) {  //���� "[" ... "]"
            pSection->Add(pBaseList->Strings[i].SubString(2, pBaseList->Strings[i].Length() - 2));
        }
    }    //ShowMessage(pSection->Strings[0]); //--> _All

    //���������� ������
    TTreeNodes *pNodes = TreeView1->Items;
    TTreeNode  *pRootNode, *pNodeLevel_1, *pNodeLevel_2, *pNodeLevel_3, *pNodeLevel_4, *pNodeLevel_5, *pNodeLevel_6, *pNodeLevel_7, *pNodeLevel_8, *pNodeLevel_9, *pNodeLevel_10;
    for (int i = 0; i < pSection->Count; i ++) { //ShowMessage(pSection->Strings[i]);
        TStringList *pINIList = new TStringList;    //���������� �������� ������ � pINIList
        pDataBaseIni->ReadSectionValues(pSection->Strings[i], pINIList); //������ �������� � ������
          
        tString asSectionId, asSectionLevel, asSectionURL, asSectionDownload, asSectionComments = "";
        asSectionId       = pDataBaseIni->ReadString(pSection->Strings[i], "id",       pINIList->Values["id"]);       //ShowMessage(asSectionId); //id
        asSectionLevel    = pDataBaseIni->ReadString(pSection->Strings[i], "level",    pINIList->Values["level"]);    //ShowMessage(asSectionLevel); //level

        for (int j = 1; pDataBaseIni->ValueExists(pSection->Strings[i], "url" + tString(j)); j ++) {
            asSectionURL      = pDataBaseIni->ReadString(pSection->Strings[i], "url" + tString(j),      pINIList->Values["url"]);      //ShowMessage(asSectionURL);
            asSectionDownload = pDataBaseIni->ReadString(pSection->Strings[i], "download" + tString(j), pINIList->Values["download"]); //ShowMessage(asSectionDownload);
            asSectionComments = pDataBaseIni->ReadString(pSection->Strings[i], "comments" + tString(j), pINIList->Values["comments"]); //ShowMessage(asSectionComments);
        }
        delete pINIList;

        ///////////////////////////////////////////////////////////////////////////////////////
        //������ ���� + ID, ������ TreeView1 (���������� �����: ��� ����(pSection->Strings[i]), �������(Level))
        pMyRec MyRecPtr = new TMyRec;
        MyRecPtr->asNodeID = asSectionId; //id ����

        if (asSectionLevel == 0) {pRootNode    = pNodes->AddObject(NULL, pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 1) {pNodeLevel_1 = pNodes->AddChildObject(pRootNode,    pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 2) {pNodeLevel_2 = pNodes->AddChildObject(pNodeLevel_1, pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 3) {pNodeLevel_3 = pNodes->AddChildObject(pNodeLevel_2, pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 4) {pNodeLevel_4 = pNodes->AddChildObject(pNodeLevel_3, pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 5) {pNodeLevel_5 = pNodes->AddChildObject(pNodeLevel_4, pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 6) {pNodeLevel_6 = pNodes->AddChildObject(pNodeLevel_5, pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 7) {pNodeLevel_7 = pNodes->AddChildObject(pNodeLevel_6, pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 8) {pNodeLevel_8 = pNodes->AddChildObject(pNodeLevel_7, pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 9) {pNodeLevel_9 = pNodes->AddChildObject(pNodeLevel_8, pSection->Strings[i], MyRecPtr);}
        if (asSectionLevel == 10) {              pNodes->AddChildObject(pNodeLevel_9, pSection->Strings[i], MyRecPtr);}
        //...
    }
    delete pSection;
    delete pDataBaseIni;
}
