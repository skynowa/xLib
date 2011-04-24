/****************************************************************************
* Class name:  CxExcel
* Description: MS Excel
* File name:   CxExcel.cpp
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     11.10.2010 10:47:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xVCL/Ole/CxExcel.h>


/****************************************************************************
*    public                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxExcel 
CxExcel::CxExcel() :
	_m_bRes      (FALSE),
	_m_sRes      (),
	_m_vApp      (Unassigned),
	_m_vWorkbooks(Unassigned)
{
}
//---------------------------------------------------------------------------
//DONE: ~CxExcel
/*virtual*/ 
CxExcel::~CxExcel() {
	_m_vApp.Clear();  _m_vApp = Unassigned;	
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: application
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bCreate 
BOOL 
CxExcel::bCreate() {
	////*DEBUG*/xASSERT_RET(Unassigned == _m_vApp, FALSE);

	try {
		//если Excel запущен - подключиться к нему
		_m_vApp = Variant::GetActiveObject("Excel.Application");
		/*DEBUG*/// n/a
	}
	catch (...) {
		//Excel не запущен - запустить его
		_m_vApp = CreateOleObject("Excel.Application");
		/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);
	}

	xTRY_BOOL
		_m_vWorkbooks = _m_vApp.OlePropertyGet("Workbooks");
		/*DEBUG*/xASSERT_RET(false == _m_vWorkbooks.IsNull(), FALSE);

		////_m_bRes = bVisible(TRUE);
		/////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bVisible
BOOL 
CxExcel::bVisible(BOOL bVisible) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vApp.OlePropertySet("Visible", bVisible);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bActiveWindowZoom
BOOL 
CxExcel::bActiveWindowZoom(INT iPercent) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vApp.OlePropertyGet("ActiveWindow").OlePropertySet("Zoom", iPercent);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bActiveWindowDisplayHeadings
BOOL 
CxExcel::bActiveWindowDisplayHeadings(BOOL bVisible) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vApp.OlePropertyGet("ActiveWindow").OlePropertySet("DisplayHeadings", bVisible);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bDisplayFullScreen
BOOL 
CxExcel::bDisplayFullScreen(BOOL bFlag) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vApp.OlePropertySet("DisplayFullScreen", bFlag);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bWindowState
BOOL 
CxExcel::bWindowState(EWindowState wsState) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vApp.OlePropertySet("WindowState", wsState);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bWindowDimensions 
BOOL 
CxExcel::bWindowDimensions(double dWidth, double dHeight, double dLeft, double dTop) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_bRes = bDisplayFullScreen(FALSE);
		/*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

		_m_vApp.OlePropertySet("Width",  dWidth);
		_m_vApp.OlePropertySet("Height", dHeight);
		_m_vApp.OlePropertySet("Left",   dLeft);
		_m_vApp.OlePropertySet("Top",    dTop);
    xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bDisplayAlerts ()
BOOL 
CxExcel::bDisplayAlerts(BOOL bFlag) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vApp.OlePropertySet("DisplayAlerts", bFlag);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bEnableEvents ()
BOOL 
CxExcel::bEnableEvents(BOOL bFlag) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vApp.OlePropertySet("EnableEvents", bFlag);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bQuit 
BOOL 
CxExcel::bQuit() {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

    //Excel.OlePropertySet("Visible",true);
/*	
	DeleteFile(_m_sTemplatePath);
	_m_vApp.OlePropertyGet("Workbooks").OlePropertyGet("Item", 1).OleProcedure("SaveAs", xD2WD(_m_sTemplatePath));

    DeleteFile(_m_sTemplatePath);
    _m_vApp.OlePropertyGet("Workbooks").OleProcedure("Close");
*/

	xTRY_BOOL
		_m_vApp.OleProcedure("Quit");
		_m_vApp.Clear();	_m_vApp = Unassigned;
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: Workbooks
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bWorkbooksOpen 
BOOL 
CxExcel::bWorkbooksOpen(const String &csFilePath) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vWorkbooks.OleProcedure("Open", xD2WD(csFilePath));
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bWorkbooksAdd 
BOOL 
CxExcel::bWorkbooksAdd() {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vWorkbooks.OleProcedure("Add");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: liWorkbooksCount 
LONG 
CxExcel::liWorkbooksCount() {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_LONG(- 1)
		_m_vWorkbooks.OlePropertyGet("Count");
	xCATCH_LONG_RET
}
//---------------------------------------------------------------------------
//DONE: vWorkbooksItem
Variant 
CxExcel::vWorkbooksItem(LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);
	
	Variant vItem = Unassigned;

	vItem = _m_vWorkbooks.OlePropertyGet("Item", liIndex);
	/*DEBUG*/xASSERT_RET(false == vItem.IsNull(), Unassigned);

	return vItem;
}
//---------------------------------------------------------------------------
//DONE: bWorkbooksClose 
BOOL 
CxExcel::bWorkbooksClose() {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		_m_vWorkbooks.OleProcedure("Close");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------

/****************************************************************************
*	public: Workbook
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bBookActivate ()
BOOL 
CxExcel::bBookActivate(LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE); 

	xTRY_BOOL
		vWorkbooksItem(liIndex).OleProcedure("Activate");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bBookSave 
BOOL 
CxExcel::bBookSave(LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorkbooksItem(liIndex).OleProcedure("Save");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bBookSaveAs 
BOOL 
CxExcel::bBookSaveAs(LONG liIndex, const String &csName) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorkbooksItem(liIndex).OleProcedure("SaveAs", xD2WD(csName), - 4158 /*xlCurrentPlatformText*/, false);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bBookWorksheets ()
BOOL 
CxExcel::bBookWorksheets(LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL

	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bBookPrintPreview ()
BOOL 
CxExcel::bBookPrintPreview(LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorkbooksItem(liIndex).OleProcedure("PrintPreview");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bBookPrintOut ()
BOOL 
CxExcel::bBookPrintOut(LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorkbooksItem(liIndex).OleProcedure("PrintOut");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bBookClose 
BOOL 
CxExcel::bBookClose(LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		////_m_vWorkbooks.OlePropertyGet("Item", liIndex).OleProcedure("Close");
		vWorkbooksItem(liIndex).OleProcedure("Close");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: Worksheets - методы
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bWorksheetsAdd ()
BOOL 
CxExcel::bWorksheetsAdd(LONG liBookIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets").OleProcedure("Add");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bWorksheetsCopy ()
BOOL 
CxExcel::bWorksheetsCopy(LONG liBookIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		//vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets").OlePropertyGet("Item", iPageIndex).OleProcedure("Add");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bWorksheetsMove ()
BOOL 
CxExcel::bWorksheetsMove(LONG liBookIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		//
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bWorksheetsSelect ()
BOOL 
CxExcel::bWorksheetsSelect(LONG liBookIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets").OleProcedure("Select");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bWorksheetsDelete ()
BOOL 
CxExcel::bWorksheetsDelete(LONG liBookIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		//vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets").OleProcedure("Delete");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bWorksheetsPrintPreview ()
BOOL 
CxExcel::bWorksheetsPrintPreview(LONG liBookIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets").OleProcedure("PrintPreview");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bWorksheetsPrintOut ()
BOOL 
CxExcel::bWorksheetsPrintOut(LONG liBookIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets").OleProcedure("PrintOut");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: Worksheets - свойства
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bWorksheetsCount ()
LONG 
CxExcel::bWorksheetsCount(LONG liBookIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), 0);

	xTRY_LONG(- 1)
		vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets").OlePropertyGet("Count");
	xCATCH_LONG_RET
}
//---------------------------------------------------------------------------
//DONE: vWorksheetsItem ()
Variant 
CxExcel::vWorksheetsItem(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), Unassigned);
	
	////   vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets", liIndex)
	return vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets").OlePropertyGet("Item", liIndex);
}
//---------------------------------------------------------------------------
//TODO: bWorksheetsSetVisible ()
BOOL 
CxExcel::bWorksheetsSetVisible(LONG liBookIndex, BOOL bFlag) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorkbooksItem(liBookIndex).OlePropertyGet("Worksheets").OlePropertySet("Visible", bFlag);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: Worksheet - методы
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: - bSheetActivate ()
BOOL 
CxExcel::bSheetActivate(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure("Activate");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: - bSheetCalculate ()
BOOL 
CxExcel::bSheetCalculate(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure("Calculate");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: - bSheetCopy ()
BOOL 
CxExcel::bSheetCopy(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure("Copy");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: - bSheetDelete ()
BOOL 
CxExcel::bSheetDelete(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure("Delete");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: - bSheetEvaluate ()
BOOL 
CxExcel::bSheetEvaluate(LONG liBookIndex, LONG liIndex, const String &csObjName) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure("Evaluate", xD2WD(csObjName));
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: - bSheetMove ()
BOOL 
CxExcel::bSheetMove(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure("Move");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: - bSheetPaste ()
BOOL 
CxExcel::bSheetPaste(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure("Paste");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: - bSheetPrintPreview ()
BOOL 
CxExcel::bSheetPrintPreview(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure("PrintPreview");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: - bSheetPrintOut ()
BOOL 
CxExcel::bSheetPrintOut(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure("PrintOut");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: - bSheetProtect ()
BOOL 
CxExcel::bSheetProtect(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		/////////vWorksheetsItem(liBookIndex, liIndex).OleProcedure("Protect");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: - bSheetUnprotect ()
BOOL 
CxExcel::bSheetUnprotect(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		//////////////vWorksheetsItem(liBookIndex, liIndex).OleProcedure("Unprotect");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: - bSheetSaveAs ()
BOOL 
CxExcel::bSheetSaveAs(LONG liBookIndex, LONG liIndex, const String &csName) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OleProcedure  ("SaveAs",     xD2WD(csName));
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: - bSheetSelect ()
BOOL 
CxExcel::bSheetSelect(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		/////////////vWorksheetsItem(liBookIndex, liIndex).OleProcedure("Select");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: - bSheetSetupOrientation ()
BOOL 
CxExcel::bSheetSetupOrientation(LONG liBookIndex, LONG liIndex, EPageOrientation poOrientation) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).
			OlePropertyGet("PageSetup").
			OlePropertySet("Orientation", poOrientation);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: - bSheetSetupPrintTitleRows () 
BOOL 
CxExcel::bSheetSetupPrintTitleRows(LONG liBookIndex, LONG liIndex, const String &csRow) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		/*ActiveSheet.PageSetup.PrintTitleRows = "$1:$1"*/
		vWorksheetsItem(liBookIndex, liIndex).
			OlePropertyGet("PageSetup").
			OlePropertySet("PrintTitleRows", xD2WD(csRow));
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------


/****************************************************************************
*	public: Worksheet - свойства
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: vSheetGetCell
Variant 
CxExcel::vSheetGetCell(LONG liBookIndex, LONG liIndex, INT iRow, INT iColumn) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), Unassigned);
	/*DEBUG*/xASSERT_RET(0     <  liBookIndex,      Unassigned);
	/*DEBUG*/xASSERT_RET(0     <  liIndex,          Unassigned);
	/*DEBUG*/////////////////////////xASSERT_RET(0     <  iRow,             Unassigned);
	/*DEBUG*/////////////////////////xASSERT_RET(0     <= iColumn,          Unassigned);

	xTRY_VARIANT(Unassigned)
		vWorkbooksItem(liBookIndex).
			OlePropertyGet("Worksheets", liIndex).
			OlePropertyGet("Cells",      iRow, iColumn);
	xCATCH_VARIANT_RET
}
//---------------------------------------------------------------------------
//TODO: sSheetGetCell
String 
CxExcel::sSheetGetCell(LONG liBookIndex, LONG liIndex, INT iRow, INT iColumn) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), String());
	/*DEBUG*/xASSERT_RET(0     <  liBookIndex,      String());
	/*DEBUG*/xASSERT_RET(0     <  liIndex,          String());
	/*DEBUG*/////////////////////////xASSERT_RET(0     <  iRow,             String());
	/*DEBUG*/////////////////////////xASSERT_RET(0     <= iColumn,          String());

    return vSheetGetCell(liBookIndex, liIndex, iRow, iColumn).
				OlePropertyGet("Value");
}
//---------------------------------------------------------------------------
//TODO: bSheetSetCell 
BOOL 
CxExcel::bSheetSetCell(LONG liBookIndex, LONG liIndex, INT iRow, INT iColumn, const String &csValue) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);
	/*DEBUG*/xASSERT_RET(0     <  liBookIndex,      FALSE);
	/*DEBUG*/xASSERT_RET(0     <  liIndex,          FALSE);
	/*DEBUG*/////////////////////////xASSERT_RET(0     <  iRow,             FALSE);
	/*DEBUG*/////////////////////////xASSERT_RET(0     <  iColumn,          FALSE);    ///////////////////////
	/*DEBUG*/ //csValue - n/a 

	xTRY_BOOL
		vSheetGetCell(liBookIndex, liIndex, iRow, iColumn).
			OlePropertySet("Value", xD2WD(csValue));
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bSheetSetCell (различные комбинации стенок)
BOOL 
CxExcel::bSheetSetCell(
	LONG  liBookIndex, 
	LONG  liIndex, 
	INT   iRow, INT iColumn, 
	const String &csValue, 
	INT   iCellWidth, INT iCellHeight, 
	BOOL  bIsHorizAlign, BOOL bIsVertAlign, BOOL bIsWrapText, 
	INT   iFontSize/*TFont *Font*/, BOOL bIsBold, 
	INT   iBoxStyle/*= 1*/, BOOL bIsLeft, BOOL bIsTop, BOOL bIsRight, BOOL bIsBottom) 
{
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);
	/*DEBUG*/xASSERT_RET(0     <  liBookIndex,      FALSE);
	/*DEBUG*/xASSERT_RET(0     <  liIndex,          FALSE);
	/*DEBUG*/////////////////////////xASSERT_RET(0     <  iRow,             FALSE);
	/*DEBUG*//////////////////////////xASSERT_RET(0     <  iColumn,          FALSE);       /////////////////////
	/*DEBUG*/ //csValue       - n/a 
	/*DEBUG*/ //iCellHeight   - n/a 
	/*DEBUG*/ //iCellWidth    - n/a 
	/*DEBUG*/ //bIsHorizAlign - n/a 
	/*DEBUG*/ //bIsVertAlign  - n/a 
	/*DEBUG*/ //bIsWrapText   - n/a 
	/*DEBUG*/ //iFontSize     - n/a 
	/*DEBUG*/ //bIsBold       - n/a 
	/*DEBUG*/ //iBoxStyle
	/*DEBUG*/ //bIsLeft       - n/a 
	/*DEBUG*/ //bIsTop        - n/a 
	/*DEBUG*/ //bIsRight      - n/a 
	/*DEBUG*/ //bIsBottom     - n/a 

	xTRY_BOOL
		Variant vCellBegin = vSheetGetCell(liBookIndex, liIndex, iRow, iColumn);
		Variant vCellEnd   = vSheetGetCell(liBookIndex, liIndex, iRow, iColumn);
		Variant vRange     = vWorksheetsItem(liBookIndex, liIndex).OlePropertyGet("Range", vCellBegin, vCellEnd);

		vRange.OleProcedure  ("Merge"); 
		vRange.OlePropertySet("NumberFormat", "@");

		//габариты ячейки
		xCHECK_DO(- 1  != iCellWidth,    vRange.OlePropertySet("ColumnWidth", iCellWidth));
		xCHECK_DO(- 1  != iCellHeight,   vRange.OlePropertySet("RowHeight",   iCellHeight));

		//выравнивание
		xCHECK_DO(TRUE == bIsHorizAlign, vRange.OlePropertySet("HorizontalAlignment", 3));
		xCHECK_DO(TRUE == bIsVertAlign,  vRange.OlePropertySet("VerticalAlignment",   2));
		xCHECK_DO(TRUE == bIsWrapText,   vRange.OlePropertySet("WrapText",            true));

		//шрифт
		vRange.OlePropertyGet("Font").OlePropertySet("Size", iFontSize); 
		xCHECK_DO(TRUE == bIsBold,       vRange.OlePropertyGet("Font").OlePropertySet("Bold", true)); 

		//рамка
		xCHECK_DO(TRUE == bIsLeft,       vRange.OlePropertyGet("Borders", 1).OlePropertySet("LineStyle", iBoxStyle));
		xCHECK_DO(TRUE == bIsTop,	     vRange.OlePropertyGet("Borders", 3).OlePropertySet("LineStyle", iBoxStyle));
		xCHECK_DO(TRUE == bIsRight,      vRange.OlePropertyGet("Borders", 2).OlePropertySet("LineStyle", iBoxStyle));
		xCHECK_DO(TRUE == bIsBottom,     vRange.OlePropertyGet("Borders", 4).OlePropertySet("LineStyle", iBoxStyle));

		//текст
		vRange.OlePropertySet("Value", xD2WD(csValue));
    xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: - bSheetSetCells ()
BOOL     			  
CxExcel::bSheetSetCells(
		LONG liBookIndex, LONG liIndex, 
		INT  iRowBegin,   INT  iColumnBegin, 
		INT  iRowEnd,     INT  iColumnEnd, 
		const Variant &cvValueArray,
		INT   iCellWidth, INT iCellHeight, 
		BOOL  bIsHorizAlign, BOOL bIsVertAlign, BOOL bIsWrapText, 
		INT   iFontSize/*TFont *Font*/, BOOL bIsBold, 
		INT   iBoxStyle/*= 1*/, BOOL bIsLeft, BOOL bIsTop, BOOL bIsRight, BOOL bIsBottom) 
{
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);
	/*DEBUG*/xASSERT_RET(0     <  liBookIndex,      FALSE);
	/*DEBUG*/xASSERT_RET(0     <  liIndex,          FALSE);
	/*DEBUG*/////////////////////////xASSERT_RET(0     <  iRowBegin,        FALSE);
	/*DEBUG*/////////////////////////xASSERT_RET(0     <  iColumnBegin,     FALSE);      ////////////
	/*DEBUG*/////////////////////////xASSERT_RET(0     <  iRowEnd,          FALSE);
	/*DEBUG*/////////////////////////xASSERT_RET(0     <  iColumnEnd,       FALSE);       ////////////////////
	/*DEBUG*/ //cvValueArray  - n/a
	/*DEBUG*/ //iCellWidth    - n/a
	/*DEBUG*/ //iCellHeight   - n/a 
	/*DEBUG*/ //bIsHorizAlign - n/a
	/*DEBUG*/ //bIsVertAlign  - n/a
	/*DEBUG*/ //bIsWrapText   - n/a
	/*DEBUG*/ //iFontSize     - n/a
	/*DEBUG*/ //bIsBold       - n/a
	/*DEBUG*/ //iBoxStyle
	/*DEBUG*/ //bIsLeft       - n/a
	/*DEBUG*/ //bIsTop        - n/a
	/*DEBUG*/ //bIsRight      - n/a
	/*DEBUG*/ //bIsBottom     - n/a

	xTRY_BOOL
		Variant vCellBegin = vSheetGetCell(liBookIndex, liIndex, iRowBegin, iColumnBegin);
		Variant vCellEnd   = vSheetGetCell(liBookIndex, liIndex, iRowEnd,   iColumnEnd);
		Variant vRange     = vWorksheetsItem(liBookIndex, liIndex).OlePropertyGet("Range", vCellBegin, vCellEnd);

		//габариты ячейки
		xCHECK_DO(- 1  != iCellWidth,    vRange.OlePropertySet("ColumnWidth", iCellWidth));
		xCHECK_DO(- 1  != iCellHeight,   vRange.OlePropertySet("RowHeight",   iCellHeight));

		//выравнивание
		xCHECK_DO(TRUE == bIsHorizAlign, vRange.OlePropertySet("HorizontalAlignment", 3));
		xCHECK_DO(TRUE == bIsVertAlign,  vRange.OlePropertySet("VerticalAlignment",   2));
		xCHECK_DO(TRUE == bIsWrapText,   vRange.OlePropertySet("WrapText",            true));

		//шрифт
		vRange.OlePropertyGet("Font").OlePropertySet("Size", iFontSize); 
		////xCHECK_DO(TRUE == bIsBold,       vRange.OlePropertyGet("Font").OlePropertySet("Bold", true)); 

		//рамка
		xCHECK_DO(TRUE == bIsLeft,       vRange.OlePropertyGet("Borders", 1).OlePropertySet("LineStyle", iBoxStyle));
		xCHECK_DO(TRUE == bIsTop,	     vRange.OlePropertyGet("Borders", 3).OlePropertySet("LineStyle", iBoxStyle));
		xCHECK_DO(TRUE == bIsRight,      vRange.OlePropertyGet("Borders", 2).OlePropertySet("LineStyle", iBoxStyle));
		xCHECK_DO(TRUE == bIsBottom,     vRange.OlePropertyGet("Borders", 4).OlePropertySet("LineStyle", iBoxStyle));

		//текст
		vRange.OlePropertySet("Value", cvValueArray);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: - sSheetGetName ()
String 
CxExcel::sSheetGetName(LONG liBookIndex, LONG liIndex) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	_m_sRes = vWorksheetsItem(liBookIndex, liIndex).OlePropertyGet("Name");

	return _m_sRes;
}
//---------------------------------------------------------------------------
//TODO: - bSheetSetName ()
BOOL 
CxExcel::bSheetSetName(LONG liBookIndex, LONG liIndex, const String &csName) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

	xTRY_BOOL
		vWorksheetsItem(liBookIndex, liIndex).OlePropertySet("Name", xD2WD(csName));
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------



/****************************************************************************
*	public: Sheets - свойства
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bSheetSelect
BOOL 
CxExcel::bSheetSelect(const String &csPageName) {
	xTRY_BOOL
		_m_vApp.OlePropertyGet("Sheets", xD2WD(csPageName)).OleProcedure("Select");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bSheetSelect
BOOL 
CxExcel::bSheetSelect(INT iPageIndex) {
	xTRY_BOOL
		_m_vApp.OlePropertyGet("Sheets").OlePropertyGet("Item", iPageIndex).OleProcedure("Select");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bSheetPrint
BOOL 
CxExcel::bSheetPrint(const String &csPageName) {
	xTRY_BOOL
		_m_vApp.OlePropertyGet("Sheets", xD2WD(csPageName)).OleProcedure("PrintOut");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------






/****************************************************************************
*	public: cells
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: sGetCell
String 
CxExcel::sGetCell(INT iRow, INT iColumn) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);
	/*DEBUG*/xASSERT_RET(0     <  iRow,             FALSE);
	/*DEBUG*/xASSERT_RET(0     <= iColumn,          FALSE);

    return _m_vApp.OlePropertyGet("Cells", iRow, iColumn).OlePropertyGet("Value");
}
//---------------------------------------------------------------------------
//TODO: bSetCell 
BOOL 
CxExcel::bSetCell(INT iRow, INT iColumn, const String &csStr) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), FALSE);
	/*DEBUG*/xASSERT_RET(0     <  iRow,             FALSE);
	/*DEBUG*/xASSERT_RET(0     <= iColumn,          FALSE);

	xTRY_BOOL
		_m_vApp.OlePropertyGet("Cells", iRow, iColumn).OlePropertySet("Value", xD2WD(csStr));
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
//TODO: bAutoFitColumn
BOOL CxExcel::bAutoFitColumn(const String &csColumnRange) {
	xTRY_BOOL
		Variant vWorkbook  = _m_vApp.OlePropertyGet("ActiveWorkbook");
		Variant vWorksheet = vWorkbook.OlePropertyGet("ActiveSheet");
		Variant vRange     = vWorksheet.OlePropertyGet("Range", xD2WD(csColumnRange));
		Variant vColumns   = vRange.OlePropertyGet("EntireColumn");
		vColumns.OleProcedure("AutoFit");
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//TODO: bSmallScroll
BOOL CxExcel::bSmallScroll() {
	xTRY_BOOL
		//ActiveWindow.SmallScroll Down = 10
		//_m_vApp.OlePropertyGet("ActiveWindow").OlePropertySet("DisplayHeadings", bVisible);
		////_m_vApp.OlePropertyGet("ActiveWindow").OlePropertyGet("SmallScroll").OlePropertySet("Down", 10);
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------
//DONE: bSetColumnNumberFormat (http://ru.wikipedia.org/wiki/Календарная_дата)
BOOL CxExcel::bSetColumnNumberFormat(LONG liBookIndex, LONG liSheetIndex, LONG liColumnIndex, const String &csNumberFormat) {
	/*DEBUG*/xASSERT_RET(false == _m_vApp.IsNull(), 		FALSE);
	/*DEBUG*/xASSERT_RET(0     <  liBookIndex,      		FALSE);
	/*DEBUG*/xASSERT_RET(0     <  liSheetIndex,     		FALSE);
	/*DEBUG*/xASSERT_RET(0     <  liColumnIndex,    		FALSE);
	/*DEBUG*/xASSERT_RET(false == csNumberFormat.IsEmpty(), FALSE);

	xTRY_BOOL
		Variant vWorksheet  = vWorksheetsItem(liBookIndex, liSheetIndex);
		Variant vColumns    = vWorksheet.OlePropertyGet("Columns");
		Variant vColumnItem = vColumns.OlePropertyGet("Item", liColumnIndex);

		vColumnItem.OlePropertySet("NumberFormat", xD2WD(csNumberFormat));		//for example: "дд-ММ-гггг;@"
	xCATCH_BOOL_RET
}
//---------------------------------------------------------------------------



/*
//---------------------------------------------------------------------------
//TODO: bAddWorkbook 
BOOL CxExcel::bWorkbookAdd() {
	xASSERT_RET(false == _m_vApp.IsNull(), FALSE);

    _m_vApp.OlePropertyGet("Workbooks").OleProcedure("Add");

   //Удаляю лишние листы создаваему Excel
    bSheetSelect(3);
    _m_vApp.OlePropertyGet("ActiveWindow").OlePropertyGet("SelectedSheets").OleProcedure("Delete");

    bSheetSelect(2);
    _m_vApp.OlePropertyGet("ActiveWindow").OlePropertyGet("SelectedSheets").OleProcedure("Delete");

    //Меняем название "Закладки"
	bSheetSelect(1);
    _m_vApp.OlePropertyGet("Sheets").OlePropertyGet("Item", 1).OlePropertySet("Name", xD2WD(csPageName));

	return TRUE;
}
*/

