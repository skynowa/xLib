//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) :
	TForm     (Owner),
	m_bRes    (FALSE),
	m_varRes  (Unassigned),
	m_liRes   ( - 1),
	m_sRes    (),
	m_exlExcel()
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender) {
	String sFilePath     = xT("C:\\Книга1.xls");
	String sWorkbookName = xT("Книга1.xls");
	String sCellValue    = xT("Cell_Value1");
	String sSheetName    = xT("Worksheet1");




	m_bRes = m_exlExcel.bCreate();
	xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//Workbooks
	m_bRes  = m_exlExcel.bWorkbooksOpen(sFilePath);
	xASSERT(FALSE != m_bRes);

    m_bRes  = m_exlExcel.bWorkbooksAdd();
	xASSERT(FALSE != m_bRes);

	m_liRes = m_exlExcel.liWorkbooksCount();
	xASSERT(0 < m_liRes);
				
	m_varRes  = m_exlExcel.vWorkbooksItem(1);
	xASSERT(false == m_varRes.IsNull());

	//-------------------------------------
	//Workbook
    m_bRes  = m_exlExcel.bBookActivate(1);
	xASSERT(FALSE != m_bRes);

//  m_bRes  = m_exlExcel.bBookSave(1);
//	xASSERT(FALSE != m_bRes);
//
//	m_bRes  = m_exlExcel.bBookSaveAs(1, xT("C:\\Book1.As.xls"));
//	xASSERT(FALSE != m_bRes);

    m_bRes  = m_exlExcel.bBookWorksheets(1);
	xASSERT(FALSE != m_bRes);

//  m_bRes  = m_exlExcel.bBookPrintPreview(1);
//	xASSERT(FALSE != m_bRes);

//  m_bRes  = m_exlExcel.bBookPrintOut(1);
//	xASSERT(FALSE != m_bRes);

	//-------------------------------------
	//Worksheets

	//методы
    m_bRes  = m_exlExcel.bWorksheetsAdd(1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bWorksheetsCopy(1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bWorksheetsMove(1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bWorksheetsSelect(1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bWorksheetsDelete(1);
	xASSERT(FALSE != m_bRes);

	////m_bRes  = m_exlExcel.bWorksheetsPrintPreview(1);
	////xASSERT(FALSE != m_bRes);

	////m_bRes  = m_exlExcel.bWorksheetsPrintOut(1);
	////xASSERT(FALSE != m_bRes);

	//Св-ва
	m_liRes  = m_exlExcel.bWorksheetsCount(1);
	xASSERT(- 1 < m_liRes);

	m_varRes = m_exlExcel.vWorksheetsItem(1, 1);
	xASSERT(false == m_varRes.IsNull());

	////m_bRes  = m_exlExcel.bWorksheetsSetVisible(1, FALSE);
	////xASSERT(FALSE != m_bRes);


	//-------------------------------------
	//Worksheet - методы
	m_bRes  = m_exlExcel.bSheetActivate(1, 1);				
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetCalculate(1, 1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetCopy(1, 1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetDelete(1, 1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetEvaluate(1, 1, xT("A1"));
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetMove(1, 1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetPaste(1, 1);
	xASSERT(FALSE != m_bRes);

	////m_bRes  = m_exlExcel.bSheetPrintPreview(1, 1);
	////xASSERT(FALSE != m_bRes);

	////m_bRes  = m_exlExcel.bSheetPrintOut(1, 1);
	////xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetProtect(1, 1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetUnprotect(1, 1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetSaveAs(1, 1, xT("C:\\Temp\\WorksheetSaveAs.xls"));
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bSheetSelect(1, 1);
	xASSERT(FALSE != m_bRes);


	//-------------------------------------
	//Worksheet - свойства
	m_bRes  = m_exlExcel.bSheetSetCell(1, 1, 1, 1, sCellValue);
	xASSERT(FALSE != m_bRes);
	m_sRes  = m_exlExcel.sSheetGetCell(1, 1, 1, 1);
	xASSERT(sCellValue == m_sRes);
 
	m_bRes  = m_exlExcel.bSheetSetName(1, 1, sSheetName);
	xASSERT(FALSE != m_bRes);
	m_sRes  = m_exlExcel.sSheetGetName(1, 1); 
	xASSERT(sSheetName == m_sRes);









	


	//-------------------------------------
	//
    m_bRes  = m_exlExcel.bBookClose(1);
	xASSERT(FALSE != m_bRes);

	m_bRes  = m_exlExcel.bWorkbooksClose();
	xASSERT(FALSE != m_bRes);

	m_bRes = m_exlExcel.bQuit();
	xASSERT(FALSE != m_bRes);

}
//---------------------------------------------------------------------------

