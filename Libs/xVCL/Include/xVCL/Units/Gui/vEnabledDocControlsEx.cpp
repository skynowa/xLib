/**********************************************************************
*   vEnabledDocControlsEx
*
***********************************************************************/


void __fastcall vEnabledDocControlsEx(bool bFlag) {
    ////dbcbbFN_DOC_TYPE_NAME->Enabled           = bFlag;
    dbedtFN_DOC_ID->Enabled                  = bFlag;
    dbedtFN_CREATE_DATE->Enabled             = bFlag;
    pgc1->Enabled                            = bFlag;
    dbmmoFN_NOTE->Enabled                    = bFlag;
    //--dbgrdArticles->Enabled                   = bFlag;
    //--sbtnStart->Enabled                       = bFlag;
    btnApply->Enabled                        = bFlag;
    btnExit->Enabled                         = bFlag;

    //сделать кнопку закрытия программы, НЕАКТИВНОЙ
    if (bFlag == true) {
        EnableMenuItem(GetSystemMenu(Handle, 0), SC_CLOSE, 0);
    } else {
        EnableMenuItem(GetSystemMenu(Handle, 0), SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
    }                
}
