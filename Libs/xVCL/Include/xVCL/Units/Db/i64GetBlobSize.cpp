/**********************************************************************
*	i64GetBlobSize - размер блоб поля
*
***********************************************************************/


//---------------------------------------------------------------------------
//TODO: i64GetBlobSize
__int64 i64GetBlobSize(TADOQuery *pADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT(NULL  != pADOQuery);
	/*DEBUG*/xASSERT(false == csFieldName.IsEmpty());
	
	__int64 i64Res = 0;

	TField *pField = pADOQuery->FieldByName(csFieldName);
	/*DEBUG*/xASSERT(NULL  != pField);
	
	std::auto_ptr</*TBlobStream*/TStream> apBlobStream(/*(TBlobStream *)*/pADOQuery->CreateBlobStream(pField, bmRead));

	i64Res = apBlobStream->Size; 	//Indicates the size in bytes of the stream.
	//i64Res = apBlobStream->Seek(0, soFromEnd);

	return i64Res;
}
//---------------------------------------------------------------------------
