/**********************************************************************
*	bDbFilter.cpp - фильтр
*
***********************************************************************/


#include <vcl.h>
#pragma hdrstop

//#include "uMain.h"
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>

//---------------------------------------------------------------------------
//TODO: фильтр
BOOL bDbFilter(
	TADOQuery    *pqryADOQuery, 
	const String &csTableName, 
	TStringList  *pslFieldsAndControls, 
	const String &csSqlStrJoin,
	const String &csSqlStrWhere,
	const String &csSqlStrOrderBy
) 
{
	String _sSql = "csSqlStrJoin:    " + csSqlStrJoin    + "\n"
				   "csSqlStrWhere:   " + csSqlStrWhere   + "\n"
				   "csSqlStrOrderBy: " + csSqlStrOrderBy;
	/*
	csSqlStrJoin:    (F_OTHER_DATE_CREATE_RECORD BETWEEN #2004/01/01# AND #2011/09/28#)
	csSqlStrWhere:
	csSqlStrOrderBy:
	*/
	CxMsgBoxT::iShow(xD2S(_sSql));

	/*DEBUG*/xASSERT_RET(NULL  != pqryADOQuery,          false);
    /*DEBUG*/xASSERT_RET(false == csTableName.IsEmpty(), false);
	/*DEBUG*/xASSERT_RET(NULL  != pslFieldsAndControls,  false);

	String sSqlStr;

	//-------------------------------------
	//пусты ли все поля?
	BOOL bIsAllFieldsEmpty = TRUE;

	for (INT i = 0; i < pslFieldsAndControls->Count; ++ i) {
		String sCtrlValue = pslFieldsAndControls->Values[pslFieldsAndControls->Names[i]];
		
		xCHECK_DO(false == sCtrlValue.IsEmpty(), bIsAllFieldsEmpty = false; break);
    }
    
	//-------------------------------------
	//составляем запрос
	if (TRUE == bIsAllFieldsEmpty) {
    	sSqlStr = xT("SELECT * FROM ") + csTableName + xT(" ") + csSqlStrJoin;
    } else {
    	sSqlStr = xT("SELECT * FROM ") + csTableName + xT(" ") + csSqlStrJoin + xT(" WHERE");
	}

	BOOL bIsFirstNotEmptyField = TRUE;

	for (INT i = 0; i < pslFieldsAndControls->Count; ++ i) {
		String sFieldName = pslFieldsAndControls->Names[i];
		String sCtrlValue = pslFieldsAndControls->Values[pslFieldsAndControls->Names[i]];
		//ShowMessage(sName + " __ " + sValue);

		xCHECK_DO(true == sCtrlValue.IsEmpty(), continue);

		//1-ое непустое поле
		if (TRUE == bIsFirstNotEmptyField) {
			sSqlStr += xT(" (") + sFieldName + xT(" LIKE '%");
			sSqlStr += sCtrlValue;
			sSqlStr += xT("%')");

			bIsFirstNotEmptyField = FALSE;
			continue;
		}

		sSqlStr += xT(" AND (") + sFieldName + xT(" LIKE '%");    // sSqlStr += " AND (FN_NIK = '";
		sSqlStr += sCtrlValue;
		sSqlStr += xT("%')");
	}

	//-------------------------------------
	//вставка csSqlStrWhere
	if (false == csSqlStrWhere.IsEmpty()) {
		if (TRUE == bIsAllFieldsEmpty) {
			sSqlStr += xT(" WHERE (") + csSqlStrWhere + xT(")");
		} else {
			sSqlStr += xT(" AND (")   + csSqlStrWhere + xT(")");
		}			    
	}


	//-------------------------------------
	//ORDER BY
	sSqlStr += xT(" ") + csSqlStrOrderBy + xT(";");
	
	CxMsgBoxT::iShow(xD2S(sSqlStr));
	//SELECT * FROM T_XXXDb (F_OTHER_DATE_CREATE_RECORD BETWEEN #2004/01/01# AND #2011/09/28#) ;

	//-------------------------------------
	//выполнить запрос
	pqryADOQuery->Close();
	pqryADOQuery->SQL->Text = sSqlStr;
	pqryADOQuery->Open();
	pqryADOQuery->Last();

	return true;
}
//---------------------------------------------------------------------------
