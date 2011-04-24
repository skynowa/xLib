/***********************************************************************
*	поменять местами элементы ListView без мерцания
*
************************************************************************/


void __fastcall SwapLVItems(const int &a, const int &b) { 
    int iNew;
    lvwDicFiles->Items->BeginUpdate();
    {
        lvwDicFiles->Items->Add();
        iNew = lvwDicFiles->Items->Count - 1;
        lvwDicFiles->Items->Item[iNew] = lvwDicFiles->Items->Item[a];
        lvwDicFiles->Items->Item[a]    = lvwDicFiles->Items->Item[b];
        lvwDicFiles->Items->Item[b]    = lvwDicFiles->Items->Item[iNew];
        lvwDicFiles->Items->Delete(iNew);
    }
    lvwDicFiles->Items->EndUpdate();
}