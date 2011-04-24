/**********************************************************************
*	TStringList_sGetName - получение имени поля по значению
*
***********************************************************************/


#include <vcl.h>
//---------------------------------------------------------------------------
//TODO: TStringList_sGetName (получение имени поля по значению)
String TStringList_sGetName(TStringList *pslList, const String &csValue) {
	/*DEBUG*/xASSERT(NULL  != pslList);
	/*DEBUG*/xASSERT(false == csValue.IsEmpty());

	for (INT i = 0; i < pslList->Count; ++ i) {
		xCHECK_RET(csValue == pslList->ValueFromIndex[i], pslList->Names[i]);
    }

	return String();
}
//---------------------------------------------------------------------------

