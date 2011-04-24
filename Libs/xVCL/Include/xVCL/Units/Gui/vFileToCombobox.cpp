/***********************************************************************
*   vFileToCombobox	
*
************************************************************************/



//---------------------------------------------------------------------------
void __fastcall vFileToCombobox(TComboBox *pCB, int iItemIndex, const tString &csFilePath) {
	TStringList *pSL = new TStringList();
	pSL->LoadFromFile(csFilePath);

    pCB->Clear();
    pCB->Items->AddStrings(pSL);
    pCB->ItemIndex = iItemIndex;
    
    delete pSL;  pSL = NULL;
}
//---------------------------------------------------------------------------
