/**********************************************************************
*    Удаляем скрипты
*
***********************************************************************/


//---------------------------------------------------------------------------
tString __fastcall asRemoveScripts(tString &asInputStr, const tString &asRegExprRemoveTag) {   
    Application->ProcessMessages();

    tString asT = asInputStr;

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

    if (pR->Exec(asT)) {
        while (pR->Match[0] != "") {    //ShowMessage(pR->Match[0]);
            //если попались влож. теги - пропускаем
            tString asTemp = pR->Match[0].Delete(1, 1).LowerCase().Pos("<script");
            if (asTemp != 0) {
                //если попались влож. "document.write" - удаляем
                if (asTemp.LowerCase().Pos("document.write") == 0) {
                    ShowMessage(asTemp.LowerCase().Pos("document.write"));
                    asOutStr = pR->Replace(pR->Match[0], "", true);
                }
            } else {
                 asOutStr = pR->Replace(pR->Match[0], "", true);
            }

            pR->ExecNext();
        }

    } else {
        asOutStr = asT;
    }
    pR->Free();

    return asOutStr;
}
//---------------------------------------------------------------------------