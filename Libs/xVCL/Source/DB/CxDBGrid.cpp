/****************************************************************************
* Class name:  CxDBGrid
* Description: TDBGrid utils
* File name:   CxDBGrid.cpp
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     10.12.2010 11:23:40
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xVCL/DB/CxDBGrid.h>


/****************************************************************************
*    public                                                           
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bExcelExport (export to MS Excel)
/*static*/
BOOL 
CxDBGrid::bExcelExport(
	TJvDBUltimGrid *pdbgDBGrid, 
	BOOL            bIsSilent,
	BOOL            bIsPortraitOrientation,
	BOOL            bIsLineNumbering, 
	INT             iFontSize,
	BOOL            bIsPrintPreview) 
{
	/*DEBUG*/xASSERT_RET(NULL != pdbgDBGrid, FALSE);
	/*DEBUG*/// bIsLineNumbering - n/a
	/*DEBUG*/xASSERT_RET(0     < iFontSize, FALSE);

	BOOL bRes      = FALSE;
	INT  iRowCount = pdbgDBGrid->DataSource->DataSet->RecordCount;
	INT  iColCount = pdbgDBGrid->Columns->Count;

	//-------------------------------------
	//excel launch
	CxExcel exlExcel;
	LONG    liBookIndex  = - 1;
	LONG    liSheetIndex = 1;

	bRes = exlExcel.bCreate();
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	bRes = exlExcel.bVisible(!bIsSilent);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	bRes = exlExcel.bEnableEvents(FALSE);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	bRes = exlExcel.bWorkbooksAdd();
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	liBookIndex = exlExcel.liWorkbooksCount();
	/*DEBUG*/xASSERT_RET(0 < liBookIndex, FALSE);

	bRes = exlExcel.bSheetSetupOrientation(liBookIndex, liSheetIndex, (TRUE == bIsPortraitOrientation) ? (CxExcel::poPortrait) : (CxExcel::poLandscape));
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	bRes = exlExcel.bSheetSetupPrintTitleRows(liBookIndex, liSheetIndex, xT("$1:$1"));
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	//-------------------------------------
	//table header
	for (INT r = 1, c = 0; c < iColCount; ++ c) {
		xCHECK_DO(false == pdbgDBGrid->Columns->Items[c]->Visible, continue);

		String sHeader = pdbgDBGrid->Columns->Items[c]->Title->Caption;

		bRes = exlExcel.bSheetSetCell(liBookIndex, liSheetIndex, r, c, sHeader, pdbgDBGrid->Columns->Items[c]->Width / 7, pdbgDBGrid->RowsHeight / 1.5, TRUE, TRUE, TRUE, iFontSize, TRUE, 1, TRUE, TRUE, TRUE, TRUE);
		/*DEBUG*/xASSERT_DO(FALSE != bRes, FALSE);
	}

	//-------------------------------------
	//table data
	if (0 < iRowCount) {
		const INT ciBounds[4] = {0, iRowCount, 0, iColCount};
		Variant   vDataArray  = VarArrayCreate(ciBounds, 3, varVariant);

		try {
			TADOQuery *pqryADO = static_cast<TADOQuery *>(pdbgDBGrid->DataSource->DataSet);
			/*DEBUG*/xASSERT_RET(NULL != pqryADO, FALSE);

			TBookmark bmSavePlace = pqryADO->GetBookmark();

			pqryADO->First();

			for (INT r = 0, iSkippedCols = 0; r < iRowCount; ++ r) {
				for (INT c = 0; c < iColCount; ++ c) {
					String sData;
					
					//field is hidden
					if (false == pdbgDBGrid->Columns->Items[c]->Visible) {	
						++ iSkippedCols;
						continue;
					} 
					//field is not tied to the DB
					else if (NULL == pdbgDBGrid->Fields[c]) {				
						//if the column "№", then enumerate the rows of
						if (xT("№") == pdbgDBGrid->Columns->Items[c]->Title->Caption && TRUE == bIsLineNumbering) {
							sData = IntToStr(r + 1);
						} else {
							//or skipping
							++ iSkippedCols;
							continue;
						}
					}
					//field is empty
					else if (true == pdbgDBGrid->Fields[c]->IsNull) {		
						sData = xT("");
					}
					//field is filled
					else {
						sData = pdbgDBGrid->Fields[c]->AsString.Trim();         	
					}

					//value to an array
					vDataArray.PutElement(sData, r, c - iSkippedCols);
				}
				pqryADO->Next();
				iSkippedCols = 0;
			}

			pqryADO->GotoBookmark(bmSavePlace);
			pqryADO->FreeBookmark(bmSavePlace);
		} catch (Exception &e) {
			/*DEBUG*/xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());
		} catch (...) {
			/*DEBUG*/xASSERT_MSG(FALSE, xT("Uknown error"));
		}

		//-------------------------------------
		//filling the table data
		INT  iBeginRow = 1 + 1;		//data starts from 2-d row
		INT  iBeginCol = 1;

		INT  iEndRow   = iBeginRow + iRowCount - 1;
		INT  iEndCol   = iBeginCol + iColCount - 2;

		bRes = exlExcel.bSheetSetCells(liBookIndex, liSheetIndex, iBeginRow, iBeginCol, iEndRow, iEndCol, vDataArray, - 1, pdbgDBGrid->RowsHeight / 1.5, TRUE, TRUE, TRUE, iFontSize, TRUE, 1, TRUE, TRUE, TRUE, TRUE);
		/*DEBUG*/xASSERT_DO(FALSE != bRes, FALSE);

		//-------------------------------------
		//TODO: special for Savitskiy V.
		#if defined(xSPECIAL_FOR_SAVITSKIY)
		{
			#pragma message("[CxExcel::bSetColumnNumberFormat] special for Savitskiy V., it must remove from working code")

			const LONG   cliDateColumn  = 2;
			const String csNumberFormat = xT("дд.ММ.гггг;@");

			bRes = exlExcel.bSetColumnNumberFormat(liBookIndex, liSheetIndex, cliDateColumn, csNumberFormat);
			/*DEBUG*/xASSERT_DO(FALSE != bRes, FALSE);		
		}
		#endif
	}

	//-------------------------------------
	//showing
	bRes = exlExcel.bVisible(TRUE);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	if (TRUE == bIsPrintPreview) {
		bRes = exlExcel.bWorksheetsPrintPreview(liBookIndex);
		/*DEBUG*/xASSERT_DO(FALSE != bRes, FALSE);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bLineNumbering (line numbering)
/*static*/
BOOL 
CxDBGrid::bLineNumbering(TDBGrid *pdbgDBGrid, const TRect &Rect, const String &csColumnTitleCaption, TColumn *pColumn) {
	/*DEBUG*/xASSERT_RET(NULL != pdbgDBGrid,                         FALSE);
	/*DEBUG*/// Rect - n/a
	/*DEBUG*/xASSERT_RET(false == csColumnTitleCaption.IsEmpty(), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pColumn,                        FALSE);

	xCHECK_RET(0 > pdbgDBGrid->DataSource->DataSet->RecNo, TRUE);

	if (csColumnTitleCaption == pColumn->Title->Caption) {
		INT iLineNo = pdbgDBGrid->DataSource->DataSet->RecNo;

		////pdbgDBGrid->Canvas->Brush->Color = clYellow;
		////pdbgDBGrid->Canvas->Font->Color  = clBlack;
		////pdbgDBGrid->Canvas->TextOut(Rect.Left + 2, Rect.Top, IntToStr(iLineNo));
		pdbgDBGrid->Canvas->TextOut(Rect.Width() / 4 + 2, Rect.Top, IntToStr(iLineNo));
		
		//TODO: запоминание номера строки
		
	}

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: vMouseScrolling (mouse scrolling)
/*static*/
VOID 
CxDBGrid::vMouseScrolling(TDBGrid *pdbgDBGrid, tagMSG &Msg, bool &Handled) {
    /*DEBUG*/xASSERT_DO(NULL != pdbgDBGrid, return);

	if (WM_MOUSEWHEEL == Msg.message) {
        Msg.message = WM_KEYDOWN;
        Msg.lParam  = 0;

		INT i = DWORD(Msg.wParam);
		if (i > 0) {
            Msg.wParam = VK_UP;
        } else {
            Msg.wParam = VK_DOWN; 
		}

        Handled = false;
	}
}
//---------------------------------------------------------------------------
//TODO: bSort (sorting)
/*static*/
BOOL 
CxDBGrid::bSort(TDBGrid *pdbgDBGrid, const String &csTableName, TColumn *pColumn) {
    /*DEBUG*/xASSERT_RET(NULL  != pdbgDBGrid,          FALSE);
	/*DEBUG*/xASSERT_RET(false == csTableName.IsEmpty(), FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pColumn,               FALSE);

	//некоторые поле не сортируются
	INT iRes = pColumn->Field->DataType;
	switch (iRes) {
		case ftBlob:	{return FALSE;}		break;
		default:        {/*пропуск*/  }  	break;
	}

	static INT s_iPriorClick  = 0;  		//по какой колонке мы кликали прошлый раз
	static INT s_iCountClicks = 1;  		//сколько раз мы кликали по одной и той же колонке
	String     sSortDirection = xT("ASC");  //направление сортировки

    //если мы кликаем по той же колонке больше 2-х раз
    if (s_iPriorClick == pColumn->Index) {   //ShowMessage("==");
        ++ s_iCountClicks;

        if (0 != (s_iCountClicks % 2)) {
			sSortDirection = xT("ASC");
		} else {
			sSortDirection = xT("DESC");
		}
	}

	//смена колонки (или 1-я колонка по которой кликнули)
	if (s_iPriorClick != pColumn->Index) {    //ShowMessage("!=");
		sSortDirection = xT("ASC");
        s_iCountClicks = 1;
    }

    //выборка с сортировкой по sSortDirection
	TADOQuery *pqryADOQuery = static_cast<TADOQuery *>( pdbgDBGrid->DataSource->DataSet );
	/*DEBUG*/xASSERT_RET(NULL  != pqryADOQuery, FALSE);

	if (true == pqryADOQuery->Active) {
		pqryADOQuery->DisableControls();
        try {
			//--String sSqlStr = xT("SELECT * FROM ") + csTableName + xT(" ORDER BY ") + pColumn->FieldName + xT(" ") + sSortDirection;

			//если есть фрагмент [ ORDER BY ...] - удаление от начала фрагмента и до конца строки

			//sBasicSqlStr
			String sBasicSqlStr = pqryADOQuery->SQL->Text;
			int    iOrderByPos  = sBasicSqlStr.UpperCase().Pos(xT(" ORDER BY "));
			xCHECK_DO(0 != iOrderByPos, sBasicSqlStr = sBasicSqlStr.SubString(1, iOrderByPos));

			//sOrderBySqlStr
			String sOrderBySqlStr = xT(" ORDER BY ") + pColumn->FieldName + xT(" ") + sSortDirection;

			pqryADOQuery->Close();
			pqryADOQuery->SQL->Text = sBasicSqlStr + sOrderBySqlStr;
			pqryADOQuery->Open();

			////ADOCommand1->CommandText = sSqlStr;
            ////ADOCommand1->Execute();
        }
        __finally {
			pqryADOQuery->EnableControls(); 
        }
    }

    s_iPriorClick = pColumn->Index;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bUpdate (update records)
/*static*/
BOOL 
CxDBGrid::bUpdate(TDBGrid *pdbgDBGrid) {
	/*DEBUG*/xASSERT_RET(NULL != pdbgDBGrid, FALSE);

	TADOQuery *pAQ = static_cast<TADOQuery *>(pdbgDBGrid->DataSource->DataSet);
	/*DEBUG*/xASSERT_RET(NULL != pAQ, FALSE);

	TBookmark bmSavePlace = pAQ->GetBookmark();

	pAQ->Requery();

	pAQ->GotoBookmark(bmSavePlace);
	pAQ->FreeBookmark(bmSavePlace);	

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bRowsFromClip ()
/*static*/
BOOL 
CxDBGrid::bRowsFromClip(TDBGrid *pdbgDBGrid) {
	xNOT_IMPLEMENTED_RET(FALSE);

////    TStringList *pslArticles = new TStringList();
////
////	//-------------------------------------
////	//копируем с буфера обмена артикула
////	OpenClipboard(NULL);
////	HANDLE h = GetClipboardData(CF_TEXT);
////	char *cText = (char *)GlobalLock(h);
////	pslArticles->Text = cText;
////	GlobalUnlock(h);
////	CloseClipboard();   //DEBUG(pslArticles->Text);
////
////    for (int i = 0; i < pslArticles->Count; i ++) {   //DEBUG(pslArticles->Strings[i]);
////		//проверка для каждого артикула
////		//...
////
////		//вставить в БД артикула
////		////TStringList *pList = new TStringList();
////        //pList->Add();   //pList->Values["TOKEN_ID"]
////        //pList->Add();   //pList->Values["FN_ETOKEN_ID"]
////
////		////DBAction_Reception2();
////		////pList->Free();
////
////		//-------------------------------------
////		//записать в TN_ORDERS_MOVING (арт, номер док)
////        String asSQLStr1 =
////            xT("INSERT
////                INTO
////             TN_ORDERS_MOVING
////                 (
////                 FN_ORDERS_MOVING_ART_ID,
////                 FN_ORDERS_MOVING_DOC_ID
////                 )
////             VALUES
////                ('") +
////                 pslArticles->Strings[i]                        + xT("','") +
////                 dmDM->qryDocs->FieldByName(xT("FN_DOC_ID"))->Value + xT("')");    //DEBUG(asSQLStr1);
////
////        dmDM->vExecSQLStr(dmDM->conMain, asSQLStr1, false);
////    }
////	//-------------------------------------
////	//восстановить запрос  (убрать если выборка большая)
////	////vFillDocByOrders();
////
////	delete pslArticles; pslArticles = NULL;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSelectAll ()
/*static*/
BOOL 
CxDBGrid::bSelectAll(TDBGrid *pdbgDBGrid) {
    pdbgDBGrid->SelectedRows->Clear();

    pdbgDBGrid->DataSource->DataSet->First();
    pdbgDBGrid->DataSource->DataSet->DisableControls();
    try {
        while (! pdbgDBGrid->DataSource->DataSet->Eof) {
            pdbgDBGrid->SelectedRows->CurrentRowSelected = true;   
            pdbgDBGrid->DataSource->DataSet->Next();
        }
    } __finally {
        pdbgDBGrid->DataSource->DataSet->EnableControls();
    }

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bSelRowsToClip ()
/*static*/
BOOL 
CxDBGrid::bSelRowsToClip(TDBGrid *pdbgDBGrid) {
	xNOT_IMPLEMENTED_RET(FALSE);

////	tString   asDocId            = dmDM->qryDocs->FieldByName(xT("FN_DOC_ID"))->Value;
////	TStringList *pslSelectedRows = new TStringList();
////	TBookmark    SavePlace       = pdbgDBGrid->DataSource->DataSet->GetBookmark();
////
////	pdbgDBGrid->DataSource->DataSet->First();
////	pdbgDBGrid->DataSource->DataSet->DisableControls();
////	try {
////		while (! pdbgDBGrid->DataSource->DataSet->Eof) {
////			if (pdbgDBGrid->SelectedRows->CurrentRowSelected) {
////				//DEBUG(pdbgDBGrid->DataSource->DataSet->FieldByName("FN_ETOKEN_ID")->Value);
////                pslSelectedRows->Add(pdbgDBGrid->DataSource->DataSet->FieldByName(xT("FN_ETOKEN_ID"))->Value);
////            }
////            pdbgDBGrid->DataSource->DataSet->Next();
////        }
////        pdbgDBGrid->DataSource->DataSet->GotoBookmark(SavePlace);
////        pdbgDBGrid->DataSource->DataSet->FreeBookmark(SavePlace);
////    } __finally {
////        pdbgDBGrid->DataSource->DataSet->EnableControls();
////    }   //DEBUG(pslSelectedRows->Text);
////
////    //-------------------------------------
////    //сохранение в буфер
////    try {
////        ActivateKeyboardLayout(LoadKeyboardLayout(IntToHex(MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT), 8).c_str(), 0), 0);
////        Clipboard()->SetTextBuf(pslSelectedRows->Text.c_str());
////        //--MSG_BOX_INFO("Данные успешно экспортированы в буфер обмена");
////    } catch (Exception &exception) {
////        Application->ShowException(&exception);
////    }
////
////    delete pslSelectedRows; pslSelectedRows = NULL;

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bColumnToPickList ()
/*static*/
BOOL 
CxDBGrid::bColumnToPickList(TDBGrid *pdbgDBGrid, int iColumn, TADOConnection *pADOConnection, const String &csTableName, const String &csFieldName) {
	/*DEBUG*/xASSERT_RET(NULL  != pdbgDBGrid,            FALSE);
	/*DEBUG*/xASSERT_RET(0     <= iColumn,               FALSE);
	/*DEBUG*/xASSERT_RET(NULL  != pADOConnection,        FALSE);
	/*DEBUG*/xASSERT_RET(false == csTableName.IsEmpty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csFieldName.IsEmpty(), FALSE);

	std::auto_ptr<TADOQuery> apqryTmp(new TADOQuery(NULL));
    /*DEBUG*/xASSERT_RET(NULL != apqryTmp.get(), FALSE);

	try {
		apqryTmp->Connection = pADOConnection;
		apqryTmp->Close();
		apqryTmp->SQL->Text = xT("SELECT ") + csFieldName + xT(" FROM ") + csTableName + xT("  ORDER BY ") + csFieldName + xT(" ASC;"); 	//ShowMessage(apqryTmp->SQL->Text);
		apqryTmp->Open();
        apqryTmp->First();
        pdbgDBGrid->Columns->Items[iColumn]->PickList->Clear();
		while (! apqryTmp->Eof) {
			if (false == apqryTmp->FieldByName(csFieldName)->IsNull) {
                pdbgDBGrid->Columns->Items[iColumn]->PickList->Add(apqryTmp->FieldByName(csFieldName)->Value);
            }
            apqryTmp->Next();
		}
        apqryTmp->Close();

        pdbgDBGrid->Columns->Items[iColumn]->DropDownRows = 20;
    } catch (Exception &exception) {
        Application->ShowException(&exception); //дубликаты записей, и др.
    }

	return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxDBGrid (comment)
CxDBGrid::CxDBGrid() {

}
//---------------------------------------------------------------------------
//TODO: - ~CxDBGrid (comment)
CxDBGrid::~CxDBGrid() {

}
//---------------------------------------------------------------------------