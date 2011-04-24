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
		
		//������� ������ ������ �� ��������
		bSplit(sLine, csSeparator, apslLine.get());

		//���������� ������ TListView
		plvLV->Items->Add();

		//-------------------------------------
		//����� �����. ������ ��� �����
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

			plvLV->Items->Item[iLine]->ImageIndex  = iAssocFileIconIndex;         	 //������
		} else {
			plvLV->Items->Item[iLine]->ImageIndex  = - 1;          				     //��������� ������
		}			
		
		//-------------------------------------
		//��������� ������
		plvLV->Items->Item[iLine]->Data       = reinterpret_cast<void *>(iLine + 1);	//ID
		plvLV->Items->Item[iLine]->Checked    = (bool)StrToInt(apslLine->Strings[0]);
		plvLV->Items->Item[iLine]->Caption    = apslLine->Strings[1];
		for (int s = 0; s < apslLine->Count - 2/*� 3-��� ��������*/; s ++) {
    		plvLV->Items->Item[iLine]->SubItems->Add(_T(""));
			plvLV->Items->Item[iLine]->SubItems->Strings[s] = apslLine->Strings[s + 2/*� 3-��� ��������*/];
		}


		////////////////////////////////////////////////////////////////////////////////////////////
		//////-------------------------------------
		//////������� TProgressBar
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
		//////���������� TProgressBar
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