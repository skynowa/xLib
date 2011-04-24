/***********************************************************************
*  Удаляем HTML тэги
*
************************************************************************/


//---------------------------------------------------------------------------
tString __fastcall asRemoveHtmlTag(tString &asInputStr, const tString &asRegExprRemoveTag) {   
    Application->ProcessMessages();
    
    TRegExpr *pR = new TRegExpr;
    {
        pR->ModifierI = true;
        pR->ModifierM = false;
        pR->ModifierS = true;
        pR->ModifierX = false;
        pR->ModifierG = false;
        pR->ModifierR = true;

        pR->Expression = asRegExprRemoveTag;
    }

    tString asOutStr = "";

	if (pR->Exec(asInputStr)) {
        asOutStr = pR->Replace(asInputStr, "", true);   //ShowMessage(asOutStr);
	} else {
        asOutStr = asInputStr;
    }
	pR->Free();

    return asOutStr;
}
//---------------------------------------------------------------------------