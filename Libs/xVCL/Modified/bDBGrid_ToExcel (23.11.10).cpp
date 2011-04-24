/**********************************************************************
*	bDBGrid_ToExcel
*
***********************************************************************/



#include "bDBGrid_ToExcel.h"

#include <ADODB.hpp>
#include <DB.hpp>
#include <XVCL/Classes/Ole/CxExcel.h>
#include <JvDBUltimGrid.hpp>


//---------------------------------------------------------------------------
//TODO: bDBGrid_ToExcel
BOOL bDBGrid_ToExcel(TJvDBUltimGrid *dbgrdGrid, CxExcel *pexlExcel, BOOL bIsLineNumbering, INT iFontSize) {
	/*DEBUG*/

	BOOL bRes      = FALSE;

	INT  iRowCount = dbgrdGrid->DataSource->DataSet->RecordCount;
	INT  iColCount = dbgrdGrid->Columns->Count;

	INT  iBeginRow = 1;
	INT  iBeginCol = 1;

	INT  iEndRow   = iBeginRow + iRowCount;
	INT  iEndCol   = iBeginCol + iColCount;

	const INT ciBounds[4] = {0, iRowCount, 0, iColCount};
	Variant   vDataArray  = VarArrayCreate(ciBounds, 3, varVariant);

	//-------------------------------------
	//заголовок
	for (INT c = 0, r = 0; c < iColCount; ++ c) {
		xCHECK_DO(false == dbgrdGrid->Columns->Items[c]->Visible, continue);

		String sHeader = dbgrdGrid->Columns->Items[c]->Title->Caption;

		vDataArray.PutElement(sHeader, r, c);
	}

	//-------------------------------------
	//данные
	try {
		TADOQuery *pqryADO = static_cast<TADOQuery *>(dbgrdGrid->DataSource->DataSet);
		/*DEBUG*/xASSERT_RET(NULL != pqryADO, FALSE);

		TBookmark bmSavePlace = pqryADO->GetBookmark();

		pqryADO->First();
		for (INT r = 1; ! pqryADO->Eof; ++ r) {
			for (INT c = 0; c < iColCount; ++ c) {
				String sData;

				if (false == dbgrdGrid->Columns->Items[c]->Visible) {	//поле скрыто
					continue; 
				} 
				else if (NULL == dbgrdGrid->Fields[c]) {				//поле не прив€зано к Ѕƒ
					continue;
				}
				else if (true == dbgrdGrid->Fields[c]->IsNull) {		//поле пустое
					sData = xT("");
				}
				else {
					sData = dbgrdGrid->Fields[c]->AsString;         	//поле заполнено
				}

				vDataArray.PutElement(sData, r, c);
			}
			pqryADO->Next();
		}

        pqryADO->GotoBookmark(bmSavePlace);
        pqryADO->FreeBookmark(bmSavePlace);
	} catch (Exception &e) {
		/*DEBUG*/xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());
	} catch (...) {
		/*DEBUG*/xASSERT_MSG(FALSE, xT("Uknown error"));
	}

	//-------------------------------------
	//вывод
	LONG liBookIndex = - 1;

	bRes = pexlExcel->bCreate();
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	bRes = pexlExcel->bEnableEvents(FALSE);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	bRes = pexlExcel->bWorkbooksAdd();
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	liBookIndex = pexlExcel->liWorkbooksCount();
	/*DEBUG*/xASSERT_RET(0 < liBookIndex, FALSE);

	bRes = pexlExcel->bSheetSetupOrientation(liBookIndex, 1, CxExcel::poLandscape);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	bRes = pexlExcel->bSheetSetupPrintTitleRows(liBookIndex, 1, xT("$1:$1"));
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	bRes = pexlExcel->bSheetSetCells(liBookIndex, 1, iBeginRow, iBeginCol, iEndRow, iEndCol, vDataArray, 15, dbgrdGrid->RowsHeight / 1.5, TRUE, TRUE, TRUE, iFontSize, TRUE, 1, TRUE, TRUE, TRUE, TRUE);
	/*DEBUG*/xASSERT_DO(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------