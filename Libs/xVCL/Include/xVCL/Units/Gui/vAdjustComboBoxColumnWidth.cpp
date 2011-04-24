/**********************************************************************
*	vAdjustComboBoxColumnWidth -
*
***********************************************************************/


//---------------------------------------------------------------------------
void __fastcall vAdjustComboBoxExColumnWidth(TComboBoxEx *pCbb) {
	/*DEBUG*/xASSERT(NULL != pCbb);

	pCbb->DroppedDown = true;

	int ItemWidth = 0;
    for (int i = 0; i < pCbb->Items->Count - 1; i ++) {
        if (pCbb->Canvas->TextWidth(pCbb->Items->Strings[i]) > ItemWidth) {
            ItemWidth = pCbb->Canvas->TextWidth(pCbb->Items->Strings[i]) + 0;
        }
    }

    pCbb->Perform(CB_SETDROPPEDWIDTH, ItemWidth * 1.7, 0);
}
//---------------------------------------------------------------------------

