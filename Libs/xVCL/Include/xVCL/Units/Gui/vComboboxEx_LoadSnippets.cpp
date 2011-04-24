/***********************************************************************
*   vComboboxEx_LoadSnippets
*
************************************************************************/


//--------------------------------------------------------------------------- 
void vComboboxEx_LoadSnippets(TComboBoxEx *pCBEx, const tString &csFoderPath, const tString &csClickedItemCaption, int iSelectedItemIndex) {
	/*DEBUG*/xASSERT(NULL  != pCBEx);
	/*DEBUG*/xASSERT(false == csFoderPath.IsEmpty());
	/*DEBUG*/xASSERT(true  == DirectoryExists(csFoderPath));
	/*DEBUG*/xASSERT(0     <  iSelectedItemIndex);

	TSearchRec SR = {0};

	if (0 == FindFirst(csFoderPath + _T("*.*"), faAnyFile, SR)) {      ////ShowMessage(SysErrorMessage(GetLastError()));
        do {
            if (! (SR.Attr & faDirectory)) {    //ShowMessage(SR.Name);
				if (_T(".snippet") == ExtractFileExt(SR.Name).LowerCase()) {    //ShowMessage(ExtractFileExt(SR.Name).LowerCase());
                    pCBEx->Items->Add(SR.Name.SetLength(SR.Name.Length() - ExtractFileExt(SR.Name).Length()));    //удаляем расширение
                    pCBEx->ItemsEx->Items[pCBEx->ItemsEx->Count - 1]->ImageIndex = 0;
                }
            }
        }
		while (0 == FindNext(SR));

        FindClose(SR);
	}

    pCBEx->ItemIndex = iSelectedItemIndex;
}
//---------------------------------------------------------------------------
