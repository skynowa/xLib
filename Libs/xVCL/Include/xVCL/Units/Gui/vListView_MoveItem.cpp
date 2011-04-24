/***********************************************************************
*   vListView_MoveItem
*
************************************************************************/



//---------------------------------------------------------------------------
void vListView_MoveItem(TListView *plvLV, int iItemFrom, int iItemTo) {
	/*DEBUG*/xASSERT(NULL != plvLV);
	/*DEBUG*/xASSERT(NULL <= iItemFrom);
	/*DEBUG*/xASSERT(NULL <= iItemTo);
	
	TListItem *Source = NULL;
	TListItem *Target = NULL;

	plvLV->Items->BeginUpdate();
	__try {
		Source = plvLV->Items->Item[iItemFrom];
		Target = plvLV->Items->Insert(iItemTo);

		Target->Assign(Source);
		Source->Free();

		//-------------------------------------
		//прокручиваем список
		plvLV->ClearSelection();

		int SelIndex = - 1;
		if (0 == iItemTo) {
			SelIndex = 0;
		} else {
			SelIndex = iItemTo - 1;
		}

		plvLV->Items->Item[SelIndex]->Selected = true;
		plvLV->Items->Item[SelIndex]->MakeVisible(true);
	} __finally {
		plvLV->Items->EndUpdate();
	}
}
//---------------------------------------------------------------------------