/**********************************************************************
*	bDBFieldToClipboard -
*
***********************************************************************/



#include <Clipbrd.hpp>

//---------------------------------------------------------------------------
BOOL bDBFieldToClipboard(TADOQuery *pADOQuery, const String &csFieldName) {
	/*DEBUG*/xASSERT(NULL  != pADOQuery);
	/*DEBUG*/xASSERT(false == csFieldName.IsEmpty());

	BOOL bRes = FALSE;

	const std::auto_ptr<TClipboard> apCB(new TClipboard());
	/*DEBUG*/xASSERT(NULL != apCB.get());

	try {
		apCB->AsText = pADOQuery->FieldByName(csFieldName)->Value;

		bRes = TRUE;
	} catch (...) {
		bRes = FALSE;
	}

	return bRes;
}
//---------------------------------------------------------------------------