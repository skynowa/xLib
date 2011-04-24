/***********************************************************************
*   vListView_AppendFromFile
*
************************************************************************/


#include <vcl.h>
//---------------------------------------------------------------------------
void vListView_AppendFromFile(TListView *plvLV, const tString &csFilePath, TImageList *pilIL, const tString &csSeparator) {
	/*DEBUG*/xASSERT(NULL  != plvLV);
	/*DEBUG*/xASSERT(false == csFilePath.IsEmpty());
	/*DEBUG*/xASSERT(NULL  != pilIL);
	/*DEBUG*/xASSERT(true  == FileExists(csFilePath));
	/*DEBUG*/xASSERT(false == csSeparator.IsEmpty());
	
	std::auto_ptr<TStringList> apslFile(new TStringList());
    /*DEBUG*/xASSERT(NULL != apslFile.get());
	
	apslFile->LoadFromFile(csFilePath);	
	
	int j     = plvLV->Items->Count;   						   			//сколько строк в plvLV
	int iLine = 0;                                     					//счетчик строк	
	
	for (iLine = 0; iLine < apslFile->Count; iLine ++) {
		std::auto_ptr<TStringList> apslLine(new TStringList());
		/*DEBUG*/xASSERT(NULL != apslLine.get());
		
		tString sLine = apslFile->Strings[iLine];
		
		//деление строки списка на элементы
		bSplit(sLine, csSeparator, apslLine.get());

		//заполнение строки TListView
		plvLV->Items->Add();
		
		//-------------------------------------
		//мутим соотв. иконку для файла
		HICON   hAssocIcon = NULL;
		tString sFileExt   = ExtractFileExt(sExtractFullFileNameFromURL(apslLine->Strings[1/*1 - Caption*/]));

		hAssocIcon = hGetAssociatedIcon(sFileExt);
		/*DEBUG*///not need
		if (NULL != hAssocIcon) {
			std::auto_ptr<TIcon> apicoAssocIcon(new TIcon());
			/*DEBUG*/xASSERT(NULL != apicoAssocIcon.get());

			apicoAssocIcon->Handle = hAssocIcon;
			int iAssocFileIconIndex = pilIL->AddIcon(apicoAssocIcon.get());    
			::DestroyIcon(apicoAssocIcon->Handle);

			plvLV->Items->Item[j + iLine]->ImageIndex  = iAssocFileIconIndex;         	 //иконка
		} else {
			plvLV->Items->Item[j + iLine]->ImageIndex  = - 1;          				     //дефолтная иконка
		}

		//-------------------------------------
		//заполняем список
		plvLV->Items->Item[j + iLine]->Data       = reinterpret_cast<void *>(j + iLine + 1);	//ID
		plvLV->Items->Item[j + iLine]->Checked    = (bool)StrToInt(apslLine->Strings[0]);
		plvLV->Items->Item[j + iLine]->Caption    = apslLine->Strings[1];
		for (int s = 0; s < apslLine->Count - 2/*с 3-ого элемента*/; s ++) {
			plvLV->Items->Item[j + iLine]->SubItems->Add(_T(""));
			plvLV->Items->Item[j + iLine]->SubItems->Strings[s] = apslLine->Strings[s + 2/*со3-ого элемента*/];
		}
	}	
}
//---------------------------------------------------------------------------