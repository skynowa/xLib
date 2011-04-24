/***********************************************************************
*	поменять местами элементы ListView без мерцания
*
************************************************************************/


//---------------------------------------------------------------------------
void vListView_SwapItems(TListView *plvLV, const int &iItemIndex1, const int &iItemIndex2) {
	/*DEBUG*/xASSERT(NULL != plvLV);
	/*DEBUG*/xASSERT(NULL <= iItemIndex1);
	/*DEBUG*/xASSERT(NULL <= iItemIndex2);
	
	plvLV->Items->BeginUpdate();
	__try {
		plvLV->Items->Add();
		const int iItemIndexNew = plvLV->Items->Count - 1;
		plvLV->Items->Item[iItemIndexNew] = plvLV->Items->Item[iItemIndex1];
		plvLV->Items->Item[iItemIndex1]   = plvLV->Items->Item[iItemIndex2];
		plvLV->Items->Item[iItemIndex2]   = plvLV->Items->Item[iItemIndexNew];
		plvLV->Items->Delete(iItemIndexNew);

		//-------------------------------------
		//прокручиваем список
		plvLV->SetFocus();
		plvLV->ClearSelection();
		plvLV->Items->Item[iItemIndex2]->Selected = true;
		plvLV->Items->Item[iItemIndex2]->MakeVisible(true);
	} __finally {
		plvLV->Items->EndUpdate();
	}
}
//---------------------------------------------------------------------------