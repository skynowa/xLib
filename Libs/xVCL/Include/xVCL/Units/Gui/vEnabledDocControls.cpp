/**********************************************************************
*   vEnabledDocControls
*
***********************************************************************/


//---------------------------------------------------------------------------
void __fastcall vEnabledDocControls(bool bFlag) {
    ////dbcbbFN_DOC_TYPE_NAME->Enabled = bFlag;
    dbedtFN_DOC_ID->Enabled        = bFlag;
    dbedtFN_CREATE_DATE->Enabled   = bFlag;
    pgc1->Enabled                  = bFlag;
    dbmmoFN_NOTE->Enabled          = bFlag;
    dbgrdArticles->Enabled         = bFlag;
    sbtnStart->Enabled             = bFlag;
}
//---------------------------------------------------------------------------
