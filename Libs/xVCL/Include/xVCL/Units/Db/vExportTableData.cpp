/**********************************************************************
*	vExportTableData -
*
***********************************************************************/


//#include "uHomeDB.h"

//---------------------------------------------------------------------------
//таблица
void vExportTableData(TADOConnection *pADOConnection, const String &csTableName, const String &csFilePath, const String &csMode) {
    //-------------------------------------
    //название колонок -> TStringList
    TStringList *pFieldList = new TStringList;
	pADOConnection->GetFieldNames(csTableName, pFieldList);


    TStringList *pTableList = new TStringList();

    //-------------------------------------
    //запрос
	String sSQLStr = "SELECT * FROM " + csTableName + ";";

    //-------------------------------------
    //выполнить запрос
    TADOQuery *qryTmp =  new TADOQuery(NULL);
    qryTmp->Connection = pADOConnection;

    qryTmp->Close();
	qryTmp->SQL->Text = sSQLStr;

    try {
        //-------------------------------------
        //формируем хидер
		String asTableHeader;
        for (int i = 0; i < pFieldList->Count; i ++) {
            asTableHeader += pFieldList->Strings[i] + "|";
        }
        //удалить последний символ - разделитель
        asTableHeader.SetLength(asTableHeader.Length() - 1);

        pTableList->Add(asTableHeader);

        //-------------------------------------
        //формируем записи
        qryTmp->Open();
        qryTmp->First();
        while (! qryTmp->Eof) {
			String asTableLine;
            for (int i = 0; i < pFieldList->Count; i ++) {
                asTableLine += qryTmp->FieldByName(pFieldList->Strings[i])->AsString + "|";
            }
            //удалить последний символ - разделитель
            asTableLine.SetLength(asTableLine.Length() - 1);
            pTableList->Add(asTableLine);

            qryTmp->Next();
        }
    } catch (Exception &exception) {
        Application->ShowException(&exception); //дубликаты записей, и др.
    }

    pTableList->SaveToFile(csFilePath);

    delete qryTmp;      qryTmp     = NULL;
    delete pTableList;  pTableList = NULL;
    delete pFieldList;  pFieldList = NULL;
}
//---------------------------------------------------------------------------

