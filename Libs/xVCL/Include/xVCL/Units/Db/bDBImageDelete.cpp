/**********************************************************************
*	vDeleteImage.cpp	
*
***********************************************************************/


//---------------------------------------------------------------------------
void vDeleteImage(TImage *pImage, TADOQuery *pADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT(NULL  != pImage);
	/*DEBUG*/xASSERT(NULL  != pADOQuery);
	/*DEBUG*/xASSERT(false == csFieldName.IsEmpty());

	pADOQuery->Edit();
	pADOQuery->FieldByName(csFieldName)->Clear();
	pADOQuery->Post();

    //-------------------------------------
	//перерисовываем TImage  (BC++ 6.0 - RAD2009: работает, RAD2010 - ошибка)
	pImage->Picture->Assign(NULL);
	pImage->Repaint();
}
//---------------------------------------------------------------------------

/*
UPDATE MyTable

Set MyBlobField = Null

WHERE SomeField = 'Somevalue'
*/
