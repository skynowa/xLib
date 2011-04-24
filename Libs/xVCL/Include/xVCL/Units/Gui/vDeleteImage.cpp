/**********************************************************************
*	vDeleteImage.cpp	
*
***********************************************************************/


#include <vcl.h>
#pragma hdrstop

#include "uMain.h"
//---------------------------------------------------------------------------
void __fastcall vDeleteImage(TImage *pImage, TADOQuery *pADOQuery, const tString &csFieldName) {
	pADOQuery->Edit();
	pADOQuery->FieldByName(csFieldName)->Clear();
	pADOQuery->Post();

	//перерисовываем TImage
	pImage->Picture->Assign(NULL);
	pImage->Repaint();
}
//---------------------------------------------------------------------------

/*
UPDATE MyTable

Set MyBlobField = Null

WHERE SomeField = 'Somevalue'
*/
