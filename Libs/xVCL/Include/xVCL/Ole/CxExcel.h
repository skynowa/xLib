/****************************************************************************
* Class name:  CxExcel
* Description: MS Excel
* File name:   CxExcel.h
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     11.10.2010 10:47:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XVCL_Classes_Ole_CxExcel_H
#define XVCL_Classes_Ole_CxExcel_H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xVCL/xCommon.h>

#include <ComObj.hpp>
#include <utilcls.h>
//---------------------------------------------------------------------------
class CxExcel : public CxNonCopyable {
    private:
		BOOL     _m_bRes;
		String   _m_sRes;
        Variant  _m_vApp;
		Variant  _m_vWorkbooks;
		Variant  _m_vCell;

    public:
		//состояния окна
		enum EWindowState {
			wsMinimized = - 4140, 
			wsMaximized = - 4137,
			wsNormal    = - 4143
		};

		//ориентация листа
		enum EPageOrientation {
			poPortrait  = 1, 
			poLandscape = 2
		};

				 CxExcel            	  ();
		virtual ~CxExcel            	  ();

		//---------------------------------------------------------------------------
		//application
        BOOL 	 bCreate            	  ();
        BOOL 	 bVisible           	  (BOOL bVisible);
		BOOL 	 bActiveWindowZoom  	  (INT iPercent);
        BOOL 	 bActiveWindowDisplayHeadings(BOOL bVisible);  
        BOOL 	 bDisplayFullScreen 	  (BOOL bFlag);                         
        BOOL 	 bWindowState       	  (EWindowState wsState);                         			
        BOOL 	 bWindowDimensions  	  (double dWidth, double dHeight, double dLeft, double dTop);	
        BOOL     bDisplayAlerts     	  (BOOL bFlag);
		BOOL     bEnableEvents            (BOOL bFlag);
		BOOL 	 bQuit              	  ();

		//---------------------------------------------------------------------------
		//Workbooks
		BOOL     bWorkbooksOpen     	  (const String &csFilePath);				
		BOOL     bWorkbooksAdd      	  ();				
		LONG     liWorkbooksCount   	  ();				
		Variant  vWorkbooksItem   	      (LONG liIndex);	 
		BOOL     bWorkbooksClose      	  ();				

		//---------------------------------------------------------------------------
		//Workbook
        BOOL 	 bBookActivate      	  (LONG liIndex);
		BOOL 	 bBookSave		    	  (LONG liIndex);
		BOOL 	 bBookSaveAs	    	  (LONG liIndex, const String &csName);
		BOOL 	 bBookWorksheets    	  (LONG liIndex);
		BOOL 	 bBookPrintPreview  	  (LONG liIndex);
		BOOL 	 bBookPrintOut	    	  (LONG liIndex);
		BOOL 	 bBookClose		    	  (LONG liIndex);

		//---------------------------------------------------------------------------
		//Worksheets
		
		//методы
		BOOL     bWorksheetsAdd           (LONG liBookIndex);
		BOOL     bWorksheetsCopy          (LONG liBookIndex);
		BOOL 	 bWorksheetsMove          (LONG liBookIndex);
		BOOL 	 bWorksheetsSelect        (LONG liBookIndex);
		BOOL	 bWorksheetsDelete        (LONG liBookIndex);
		BOOL 	 bWorksheetsPrintPreview  (LONG liBookIndex);
		BOOL     bWorksheetsPrintOut      (LONG liBookIndex);

		//свойства
		LONG     bWorksheetsCount		  (LONG liBookIndex);
		Variant  vWorksheetsItem		  (LONG liBookIndex, LONG liIndex);
		BOOL     bWorksheetsSetVisible    (LONG liBookIndex, BOOL bFlag);

		//---------------------------------------------------------------------------
		//Worksheet

		//методы
		BOOL     bSheetActivate			  (LONG liBookIndex, LONG liIndex);				
		BOOL     bSheetCalculate		  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetCopy				  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetDelete			  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetEvaluate			  (LONG liBookIndex, LONG liIndex, const String &csObjName);
		BOOL     bSheetMove				  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetPaste			  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetPrintOut			  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetPrintPreview		  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetProtect			  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetUnprotect		  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetSaveAs			  (LONG liBookIndex, LONG liIndex, const String &csName);
		BOOL     bSheetSelect			  (LONG liBookIndex, LONG liIndex);
		BOOL     bSheetSetupOrientation   (LONG liBookIndex, LONG liIndex, EPageOrientation poOrientation);
		BOOL     bSheetSetupPrintTitleRows(LONG liBookIndex, LONG liIndex, const String &csRow);
 
		//свойства
		//Columns        //Range
		//Rows				//Range
		Variant  vSheetGetCell			  (LONG liBookIndex, LONG liIndex, INT iRow, INT iColumn); 
		String   sSheetGetCell			  (LONG liBookIndex, LONG liIndex, INT iRow, INT iColumn); 
		BOOL     bSheetSetCell			  (LONG liBookIndex, LONG liIndex, INT iRow, INT iColumn, const String &csValue);
		BOOL     bSheetSetCell            (LONG liBookIndex, LONG liIndex, INT iRow, INT iColumn, const String &csValue, INT iCellWidth, INT iCellHeight, BOOL bIsHorizAlign, BOOL bIsVertAlign, BOOL bIsWrapText, INT iFontSize/*TFont *Font*/, BOOL bIsBold, INT iBoxStyle, BOOL bIsLeft, BOOL bIsTop, BOOL bIsRight, BOOL bIsBottom);
		BOOL     bSheetSetCells			  (LONG liBookIndex, LONG liIndex, INT iRowBegin, INT iColumnBegin, INT iRowEnd, INT iColumnEnd, const Variant &cvValueArray, INT iCellWidth, INT iCellHeight, BOOL bIsHorizAlign, BOOL bIsVertAlign, BOOL bIsWrapText, INT iFontSize/*TFont *Font*/, BOOL bIsBold, INT iBoxStyle/*= 1*/, BOOL bIsLeft, BOOL bIsTop, BOOL bIsRight, BOOL bIsBottom);
		
		///Range		
		////LONG     bSheetIndex
		String   sSheetGetName			  (LONG liBookIndex, LONG liIndex); 
		BOOL     bSheetSetName			  (LONG liBookIndex, LONG liIndex, const String &csName);
		////BOOL     bSetVisible

		//Sheets
        BOOL 	 bSheetSelect       	  (const String &csPage);
		BOOL 	 bSheetSelect       	  (INT iPageIndex);
        BOOL 	 bSheetPrint        	  (const String &csPage);

		//---------------------------------------------------------------------------
		//Cell
        String   sGetCell           	  (INT iRow, INT iColumn);
		BOOL     bSetCell           	  (INT iRow, INT iColumn, const String &csStr);
		
		//---------------------------------------------------------------------------
		//
        BOOL 	 bAutoFitColumn     	  (const String &csColumnRange);        
        BOOL 	 bSmallScroll       	  ();
		BOOL     bSetColumnNumberFormat   (LONG liBookIndex, LONG liSheetIndex, LONG liColumnIndex, const String &csNumberFormat);
        //BOOL   bCellColor         	  ();


		//---------------------------------------------------------------------------
		//utils
};
//---------------------------------------------------------------------------
#endif	//XVCL_Classes_Ole_CxExcel_H


/*
Установка свойства. 
vVarApp.OlePropertySet("имя", значение);  

Чтение значения свойства. 
переменная = app.OlePropertyGet("имя"); 

Вызов метода: 
vVarApp.OleProcedure("имя",список параметров метода);

*/
