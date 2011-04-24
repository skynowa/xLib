/****************************************************************************
* Class name:  CxDBGrid
* Description: TDBGrid utils
* File name:   CxDBGrid.h
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     10.12.2010 11:23:40
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xVCL_DB_CxDBGridH
#define xVCL_DB_CxDBGridH
//---------------------------------------------------------------------------
#include <xVCL/xCommon.h>
#include <xVCL/Ole/CxExcel.h>

#include <JvDBUltimGrid.hpp>
//---------------------------------------------------------------------------
#define xSPECIAL_FOR_SAVITSKIY 1	//it must remove from working code
//---------------------------------------------------------------------------
class CxDBGrid {
	public:
		static BOOL bExcelExport     (TJvDBUltimGrid *pdbgDBGrid, BOOL bIsSilent, BOOL bIsPortraitOrientation, BOOL bIsLineNumbering, INT iFontSize, BOOL bIsPrintPreview);
		static BOOL bLineNumbering   (TDBGrid *pdbgDBGrid, const TRect &Rect, const String &csColumnTitleCaption, TColumn *pColumn);
		static VOID vMouseScrolling  (TDBGrid *pdbgDBGrid, tagMSG &Msg, bool &Handled);
		static BOOL bSort            (TDBGrid *pdbgDBGrid, const String &csTableName, TColumn *pColumn);
		static BOOL bUpdate          (TDBGrid *pdbgDBGrid);
		static BOOL bRowsFromClip    (TDBGrid *pdbgDBGrid);
		static BOOL bSelectAll       (TDBGrid *pdbgDBGrid);
		static BOOL bSelRowsToClip   (TDBGrid *pdbgDBGrid);
		static BOOL bColumnToPickList(TDBGrid *pdbgDBGrid, int iColumn, TADOConnection *pADOConnection, const String &csTableName, const String &csFieldName);

	private:
				    CxDBGrid         ();
		           ~CxDBGrid         ();
};
//---------------------------------------------------------------------------
#endif //CxDBGridH
