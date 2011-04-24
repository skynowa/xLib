/***********************************************************************
*   vListView_LoadFromFile
*
************************************************************************/


#include <vcl.h>
//---------------------------------------------------------------------------
void vListView_LoadFromFile(TListView *plvLV, const tString &csFilePath, TImageList *pilIL, const tString &csSeparator) {
	/*DEBUG*/xASSERT(NULL  != plvLV);
	/*DEBUG*/xASSERT(false == csFilePath.IsEmpty());
	/*DEBUG*/xASSERT(NULL  != pilIL);
	/*DEBUG*/xASSERT(true  == FileExists(csFilePath));
	/*DEBUG*/xASSERT(false == csSeparator.IsEmpty());
	
	std::auto_ptr<TStringList> apslFile(new TStringList());
    /*DEBUG*/xASSERT(NULL != apslFile.get());
	
	apslFile->LoadFromFile(csFilePath);
	
	plvLV->Clear();

	for (int iLine = 0; iLine < apslFile->Count; iLine ++) {
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

			plvLV->Items->Item[iLine]->ImageIndex  = iAssocFileIconIndex;         	 //иконка
		} else {
			plvLV->Items->Item[iLine]->ImageIndex  = - 1;          				     //дефолтная иконка
		}			
		
		//-------------------------------------
		//заполняем список
		plvLV->Items->Item[iLine]->Data       = reinterpret_cast<void *>(iLine + 1);	//ID
		plvLV->Items->Item[iLine]->Checked    = (bool)StrToInt(apslLine->Strings[0]);
		plvLV->Items->Item[iLine]->Caption    = apslLine->Strings[1];
		for (int s = 0; s < apslLine->Count - 2/*с 3-ого элемента*/; s ++) {
    		plvLV->Items->Item[iLine]->SubItems->Add(_T(""));
			plvLV->Items->Item[iLine]->SubItems->Strings[s] = apslLine->Strings[s + 2/*с 3-ого элемента*/];
		}


		////////////////////////////////////////////////////////////////////////////////////////////
		//////-------------------------------------
		//////создаем TProgressBar
		////TCGauge *pPB = new TCGauge(plvLV/*frmMain*/);
		/////*DEBUG*/xASSERT(NULL != pPB);
		////pPB->Visible          = false;
		////pPB->Parent           = plvLV/*frmMain->lvQueue*/;
		////pPB->Progress         = 20;
		//////pPB->Smooth         = true;
		//////::PostMessage(pPB->Handle, 0x0409, 0, clBlue);
		////pPB->AlignWithMargins = true;
		////
		//////-------------------------------------
		//////размещение TProgressBar
		////plvLV->Items->Item[iLine]->Data = pPB;
		////
		////TRect r;
		////r = plvLV->Items->Item[iLine]->DisplayRect(drBounds);
		////
		////frmMain->vAdjustProgressBar(plvLV->Items->Item[iLine], r);
		////
		////Application->ProcessMessages();
		////
		////frmMain->m_vecpProgressBars.push_back(pPB);
		///////////////////////////////////////////////////////////////////////////////////////////////
	}	
}
//---------------------------------------------------------------------------