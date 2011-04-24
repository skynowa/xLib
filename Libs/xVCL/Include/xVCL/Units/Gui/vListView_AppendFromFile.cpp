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
	
	int j     = plvLV->Items->Count;   						   			//������� ����� � plvLV
	int iLine = 0;                                     					//������� �����	
	
	for (iLine = 0; iLine < apslFile->Count; iLine ++) {
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

			plvLV->Items->Item[j + iLine]->ImageIndex  = iAssocFileIconIndex;         	 //������
		} else {
			plvLV->Items->Item[j + iLine]->ImageIndex  = - 1;          				     //��������� ������
		}

		//-------------------------------------
		//��������� ������
		plvLV->Items->Item[j + iLine]->Data       = reinterpret_cast<void *>(j + iLine + 1);	//ID
		plvLV->Items->Item[j + iLine]->Checked    = (bool)StrToInt(apslLine->Strings[0]);
		plvLV->Items->Item[j + iLine]->Caption    = apslLine->Strings[1];
		for (int s = 0; s < apslLine->Count - 2/*� 3-��� ��������*/; s ++) {
			plvLV->Items->Item[j + iLine]->SubItems->Add(_T(""));
			plvLV->Items->Item[j + iLine]->SubItems->Strings[s] = apslLine->Strings[s + 2/*��3-��� ��������*/];
		}
	}	
}
//---------------------------------------------------------------------------